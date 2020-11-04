#include "stdafx.h"
#include "CrevisCtrl.h"

// 생성 시 연결할 카메라의 IP 주소를 입력해야 합니다. 20201029 장한결
CCrevisCtrl::CCrevisCtrl(CString InputIP)
{
	m_IsDeviceOpen = FALSE;
	m_IsInitSystem = false;
	m_status = 0;
	m_hDevice = 0;
	m_IsAcq = FALSE;
	m_pImage = NULL;
	m_bufferSize = 0;
	
	// 생성 시 option.ini의 내용을 읽음. 읽는 부분은 Main(Small_StudioDlg)에서 정의 20201102 장한결
	m_deviceIPCStr = InputIP;
}

// 소멸자 생성 시 카메라 Close를 해주지 않았다면 자동으로 Close를 진행합니다. 20201029 장한결
CCrevisCtrl::~CCrevisCtrl()
{
	ST_AcqStop(m_hDevice);
	CloseDevice();
}

CAMERA_ERRCODE CCrevisCtrl::GetTriggerStatus()
{
	char* reg;
	UINT32 regSize = 32;
	reg = new char[regSize];
	if (m_IsDeviceOpen)
	{
		m_status = ST_GetEnumReg(m_hDevice, MCAM_TRIGGER_MODE, reg, &regSize);
		if (m_status != MCAM_ERR_SUCCESS)
		{
			delete reg;
			return CAMERA_INFOGET_FAIL;
		}

		if (strcmp(reg, TRIGGER_MODE_ON))
		{
			delete reg;
			return CAMERA_TRIG_SW;
		}
		else if (strcmp(reg, TRIGGER_MODE_OFF))
		{
			delete reg;
			return CAMERA_TRIG_CONTINUOUS;
		}
	}
	delete reg;
	return CAMERA_INFOGET_FAIL;
}

// 생성자에서 지정해 준 IP 주소로 카메라를 Open합니다. 20201029 장한결
CAMERA_ERRCODE CCrevisCtrl::OpenDevice()
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
				m_IsAcq = FALSE;
				return CAMERA_ACQ_FAIL;
			}
			else
			{
				m_IsAcq = TRUE;
			}
			
			m_bufferSize = m_camWidth * m_camHeight;
			m_pImage = new BYTE[m_bufferSize];
			::ZeroMemory(m_pImage, m_bufferSize);

			m_IsDeviceOpen = TRUE;
			return CAMERA_OPEN_SUCCESS;
		}
	}
	delete deviceIp;
	return CAMERA_IP_NOTFOUND;
}

BOOL CCrevisCtrl::TriggerSet(INT32 Trigger)
{
	INT32 currentTrig;
	if (m_IsDeviceOpen)
	{
		if (Trigger == CAMERA_TRIG_CONTINUOUS)
		{
			currentTrig = GetTriggerStatus();
			if (currentTrig == CAMERA_TRIG_CONTINUOUS)
			{
				return TRUE;
			}
			else if (currentTrig == CAMERA_TRIG_SW)
			{
				TriggerOff();
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}

		else if (Trigger == CAMERA_TRIG_SW)
		{
			currentTrig = GetTriggerStatus();
			if (currentTrig == CAMERA_TRIG_SW)
			{
				return TRUE;
			}
			else if (currentTrig == CAMERA_TRIG_CONTINUOUS)
			{
				SetSWTrigger();
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CCrevisCtrl::TriggerOff()
{
	if (m_IsDeviceOpen)
	{
		m_status = ST_SetEnumReg(m_hDevice, MCAM_TRIGGER_MODE, TRIGGER_MODE_OFF);
		if (m_status != MCAM_ERR_SUCCESS)
		{
			return FALSE;
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// Trigger mode setting 입니다. 20201102 장한결
BOOL CCrevisCtrl::SetSWTrigger()
{
	// SW Trigger set
	// Trigger mode on 후 SW Trigger로 set 합니다. 20201102 장한결
	if (m_IsDeviceOpen)
	{
		m_status = ST_SetEnumReg(m_hDevice, MCAM_TRIGGER_MODE, TRIGGER_MODE_ON);
		if (m_status != MCAM_ERR_SUCCESS)
		{
			return FALSE;
		}
		m_status = ST_SetEnumReg(m_hDevice, MCAM_TRIGGER_SOURCE, TRIGGER_SOURCE_SOFTWARE);
		if (m_status != MCAM_ERR_SUCCESS)
		{
			return FALSE;
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// 카메라를 Close합니다. 20201029 장한결
CAMERA_ERRCODE CCrevisCtrl::CloseDevice()
{
	if (m_IsDeviceOpen)
	{
		delete m_pImage;
		m_pImage = NULL;

		if (m_IsAcq)
		{
			ST_AcqStop(m_hDevice);
			m_IsAcq = FALSE;
		}

		m_status = ST_CloseDevice(m_hDevice);
		if (m_status != MCAM_ERR_SUCCESS)
		{
			return CAMERA_CLOSE_FAIL;
		}
		m_IsDeviceOpen = FALSE;
		return CAMERA_CLOSE_SUCCESS;
	}
	return CAMERA_CLOSE_NOTOPEN;
}
// Exposure time을 구해주는 함수. 20201030 장한결
// Device의 상태만 받아올 뿐 Device의 상태에 반영되지 않습니다.
DOUBLE CCrevisCtrl::GetDeviceExposure()
{
	DOUBLE exposetime = 0.0f;

	if (m_IsDeviceOpen)
	{
		m_status = ST_GetFloatReg(m_hDevice, MCAM_EXPOSURE_TIME, &exposetime);
		if (m_status != MCAM_ERR_SUCCESS)
		{
			return -1.0f;
		}
	}
	return exposetime;
}

BOOL CCrevisCtrl::SetDeviceExposure(DOUBLE ExposeTime)
{
	if (m_IsDeviceOpen)
	{
		m_status = ST_SetFloatReg(m_hDevice, MCAM_EXPOSURE_TIME, ExposeTime);
		if (m_status != MCAM_ERR_SUCCESS)
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CCrevisCtrl::GrabImageSW()
{
	if (m_IsDeviceOpen)
	{
		m_status = ST_SetCmdReg(m_hDevice, MCAM_TRIGGER_SOFTWARE);
		if (m_status != MCAM_ERR_SUCCESS)
		{
			return FALSE;
		}

		Sleep(1);

		m_status = ST_GrabImageAsync(m_hDevice, m_pImage, m_bufferSize, -1);
		if (m_status != MCAM_ERR_SUCCESS)
		{
			return FALSE;
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

