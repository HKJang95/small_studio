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
	INT32 OpenDevice();
	INT32 CloseDevice();
	BOOL SetDeviceIP(CString IPCStr);
	DOUBLE GetDeviceExposure();
	BOOL SetDeviceExposure(CString IPCStr);

public:
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
										// 20201030 장한결
};

