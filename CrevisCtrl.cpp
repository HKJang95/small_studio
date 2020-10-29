#include "stdafx.h"
#include "CrevisCtrl.h"

CCrevisCtrl::CCrevisCtrl(int camnum)
{
	m_IsDeviceOpen = FALSE;
	m_IsInitSystem = false;
	m_CamNum = camnum;
	m_AvailCams = 0;
}


CCrevisCtrl::~CCrevisCtrl()
{
	bool isopen = false;
	ST_IsOpenDevice(m_hDevice, &isopen);
	if (isopen)
	{
		CloseDevice();
	}
}

// 생성자에서 지정해 준 camnum 번 째 카메라를 Open합니다. 20201029 장한결
INT32 CCrevisCtrl::OpenDevice()
{
	m_status = ST_IsInitSystem(&m_IsInitSystem);
	if (m_status != MCAM_ERR_SUCCESS)
	{
		
	}

	if (!m_IsInitSystem)
	{
		return SYSTEM_NOT_INIT;
	}
	m_status = ST_GetAvailableCameraNum(&m_AvailCams);	

	if (m_AvailCams < 0)
	{
		return NO_CAMERA_DETECTED;
	}
	
	m_status = ST_OpenDevice(m_CamNum, &m_hDevice);

	if (m_status != MCAM_ERR_SUCCESS)
	{
		return CAMERA_OPEN_ERROR;
	}
	m_IsDeviceOpen = TRUE;
	return CAMERA_OPEN_SUCCESS;
}

// 객체를 생성할 때 Open한 카메라를 Close합니다. 20201029 장한결
INT32 CCrevisCtrl::CloseDevice()
{
	m_status = ST_CloseDevice(m_hDevice);
	m_IsDeviceOpen = FALSE;
	if (m_status != MCAM_ERR_SUCCESS)
	{
		return CAMERA_CLOSE_FAIL;
	}
	return CAMERA_CLOSE_SUCCESS;
}

