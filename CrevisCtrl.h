#pragma once
#define BUFSIZE 100;

// Crevis Camera Control을 위한 Class입니다.
// 카메라 1개당 1개의 객체를 갖습니다.
// 20201029 장한결
class CCrevisCtrl
{
public:
	CCrevisCtrl(CString InputIP);
	~CCrevisCtrl();
	CAMERA_ERRCODE  OpenDevice();
	CAMERA_ERRCODE	CloseDevice();
	DOUBLE			GetDeviceExposure();
	BOOL			SetDeviceExposure(DOUBLE ExposeTime);
	BOOL			TriggerSet(INT32 Trigger);
	BOOL			TriggerOff();
	BOOL			GrabImageSW();
	BOOL			SetSWTrigger();
	BOOL			GrabImageContinuous();

private:
	CAMERA_ERRCODE	GetTriggerStatus();

public:
	CRITICAL_SECTION mSc;
	BYTE*			m_pImage;			// 이미지 버퍼
	BOOL			m_IsDeviceOpen;		// Device Open 상태 체크
	BOOL			m_IsAcq;			// Device Acquisition on 체크
	bool			m_IsInitSystem;		// SDK Init 상태 체크
	INT32			m_status;			// Device 명령 송신 후 응답
	int				m_hDevice;			// Device 핸들
	CString			m_deviceIPCStr;		// Device 통신으로 얻은 IP 주소
	INT32			m_camWidth;			// Image 폭
	INT32			m_camHeight;		// Image 높이
	UINT32			m_camNum;			// Device 번호
	INT32			m_bufferSize;		// 영상 버퍼 사이즈 (width * height)
										// 20201030 장한결
};

