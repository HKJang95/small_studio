#pragma once

// Crevis Camera Control을 위한 Class입니다.
// 카메라 1개당 1개의 객체를 갖습니다.
// 20201029 장한결
class CCrevisCtrl
{
public:
	CCrevisCtrl(int camnum);
	~CCrevisCtrl();

	// Camera Open | Close용 함수입니다 20201029 장한결
	INT32 OpenDevice();
	INT32 CloseDevice();
	

public:
	BOOL			m_IsDeviceOpen;
	bool			m_IsInitSystem;
	int				m_CamNum;
	UINT			m_AvailCams;
	INT32			m_status;
	INT32			m_hDevice;

};

