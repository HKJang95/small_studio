
#pragma once

#define	MAXBUF		50000
#define	InBufSize	50000
#define	OutBufSize	50000
#define ASCII_XON	0x11
#define ASCII_XOFF	0x13
#define	WM_MYRECEIVE	(WM_USER+1)

// CLightCtrl 명령 대상입니다.

class CLightCtrl : public CCmdTarget
{
	DECLARE_DYNAMIC(CLightCtrl)

public:
	CLightCtrl(CString port, CString baudrate, CString parity, CString databit, CString stopbit);
	virtual ~CLightCtrl();

public:
	HANDLE	m_hComDev;
	HWND	m_hWnd;

	BOOL	m_bIsOpenned;
	CString	m_sComPort;
	CString	m_sBaudRate;
	CString	m_sParity;
	CString	m_sDataBit;
	CString	m_sStopBit;
	CString m_rcvData;
	BOOL	m_bFlowChk;
	BOOL	m_hTerminated;

	OVERLAPPED m_OLR, m_OLW;
	char	m_sInBuf[MAXBUF * 2];
	char*	m_rcvbuf;
	int		m_nLength;
	CEvent*	m_pEvent;

	void Clear();
	int Receive(LPSTR inbuf, int len);
	BOOL Send(CString outbuf);
	BOOL Create(HWND hWnd);
	void HandleClose();
	void Close();
	void ResetSerial();

protected:
	DECLARE_MESSAGE_MAP()
};


