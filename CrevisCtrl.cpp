#include "stdafx.h"
#include "CrevisCtrl.h"

// 생성 시 연결할 카메라의 IP 주소를 입력해야 합니다. 20201029 장한결
CCrevisCtrl::CCrevisCtrl(CString InputIP)
{
	m_IsDeviceOpen = FALSE;
	m_IsInitSystem = false;
	m_status = 0;
	m_hDevice = 0;
	m_deviceIPCStr = InputIP;
	m_IsAcq = FALSE;
}

// 소멸자 생성 시 카메라 Close를 해주지 않았다면 자동으로 Close를 진행합니다. 20201029 장한결
CCrevisCtrl::~CCrevisCtrl()
{
	bool isopen = false;
	ST_IsOpenDevice(m_hDevice, &isopen);
	if (isopen)
	{
		CloseDevice();
	}
}

// 생성자에서 지정해 준 IP 주소로 카메라를 Open합니다. 20201029 장한결
INT32 CCrevisCtrl::OpenDevice()
{
	// System Init 체크입니다 20201029 장한결
	m_status = ST_IsInitSystem(&m_IsInitSystem);
	if (m_status != MCAM_ERR_SUCCESS)
	{
		return CAMSYS_NOT_INIT;
	}

	if (!m_IsInitSystem)
	{
		return CAMSYS_NOT_INIT;
	}

	m_status = ST_UpdateDevice();
	if (m_status != MCAM_ERR_SUCCESS)
	{
		m_deviceIPCStr = _T("");
		return CAMERA_OPEN_ERROR;
	}
	UINT AvailCams;
	// 현재 연결할 수 있는 카메라 댓수만큼 IP 주소 검색을 돌려
	// 일치하는 카메라를 연결합니다. 20201029 장한결
	m_status = ST_GetAvailableCameraNum(&AvailCams);
	if (m_status != MCAM_ERR_SUCCESS)
	{
		return CAMERA_INFOGET_FAIL;
	}
	if (AvailCams == 0)
	{
		return NO_CAMERA_DETECTED;
	}

	unsigned int bufsize = 100;
	char * deviceIp = new char[100];
	CString deviceIPCstr = _T("");

	// 연결할 수 있는 카메라를 순회, 입력한 IP 주소에 해당하는 카메라를 찾습니다. 20201029 장한결
	for (int i = 0; i < AvailCams; i++)
	{
		m_status = ST_GetEnumDeviceInfo(i, MCAM_DEVICEINFO_IP_ADDRESS, deviceIp, &bufsize);
		if (m_status != MCAM_ERR_SUCCESS)
		{
			delete deviceIp;
			return CAMERA_INFOGET_FAIL;
		}
		else
		{
			deviceIPCstr = deviceIp;
		}
		// 일치하는 카메라를 찾으면 연결을 진행합니다. 20201029 장한결
		if (deviceIPCstr == m_deviceIPCStr)
		{
			delete deviceIp;
			m_status = ST_OpenDevice(i, &m_hDevice);
			if (m_status != MCAM_ERR_SUCCESS)
			{
				return CAMERA_OPEN_ERROR;
			}
			m_status = ST_GetIntReg(m_hDevice, MCAM_WIDTH, &m_camWidth);
			if (m_status != MCAM_ERR_SUCCESS)
			{
				return CAMERA_INFOGET_FAIL;
			}

			m_status = ST_GetIntReg(m_hDevice, MCAM_HEIGHT, &m_camHeight);
			if (m_status != MCAM_ERR_SUCCESS)
			{
				return CAMERA_INFOGET_FAIL;
			}

			m_status = ST_AcqStart(m_hDevice);
			if (m_status != MCAM_ERR_SUCCESS)
			{
				return CAMERA_ACQ_FAIL;
			}
			else
			{
				m_IsAcq = TRUE;
			}
			m_IsDeviceOpen = TRUE;
			return CAMERA_OPEN_SUCCESS;
		}
	}
	delete deviceIp;
	return CAMERA_IP_NOTFOUND;
}

// 카메라를 Close합니다. 20201029 장한결
INT32 CCrevisCtrl::CloseDevice()
{
	if (m_IsDeviceOpen)
	{
		if (m_IsAcq)
		{
			ST_AcqStop(m_hDevice);
			m_IsAcq = FALSE;
		}

		m_status = ST_CloseDevice(m_hDevice);
		m_IsDeviceOpen = FALSE;
		if (m_status != MCAM_ERR_SUCCESS)
		{
			return CAMERA_CLOSE_FAIL;
		}
		return CAMERA_CLOSE_SUCCESS;
	}
	return CAMERA_CLOSE_NOTOPEN;
}



