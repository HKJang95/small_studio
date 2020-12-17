
// Small_StudioDlg.h : 헤더 파일
//

#pragma once
#include "CrevisCtrl.h"
#include "LightCtrl.h"
#include "Small_StudioDlg.h"
#include "Small_Studio.h"
#include "OptionDlg.h"
#include "MyImageView.h"
#include "afxwin.h"

// CSmall_StudioDlg 대화 상자
class CSmall_StudioDlg : public CDialogEx
{
	// 생성입니다.
public:
	CSmall_StudioDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMALL_STUDIO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCam1open();
	afx_msg void OnBnClickedCam2open();
	afx_msg void OnBnClickedOptionbtn();
	afx_msg void OnBnClickedLightopen();
	afx_msg void OnBnClickedCam1play();
	afx_msg void OnBnClickedCam2play();
	afx_msg void OnDestroy();

//////////////////////////////////// 함수 (private) ////////////////////////////////////////////////////
private:
	BOOL			camOpenSeq(int dispNum); // 카메라 open 시퀀스
	CString			GetExePath();			 // option.ini 사용 위한 실행파일 위치 얻기
	BOOL			GetOptionValue(int mode);// option값 획득 (전부)
	BOOL			GetOptionValue(int mode, int dispNum); // option값 획득 (play / open시 필요한 값들)
	BOOL			LightSend(int dispNum, BOOL OnOff); // 조명에 명령 전송
	LRESULT			OnMyMsg(WPARAM length, LPARAM lpara); // RS232 명령 수신기
	CPoint			m_CurSor; // 현 커서위치
/////////////////////////////////////////////////////////////////////////////////////////////////////////


public:
//////////////////////////////////// 카메라 관련 변수 ////////////////////////////////////////////////////
	bool			m_IsSystemInit;		// Camera SDK Init 상태 점검입니다.
	BOOL			m_IsOpen[MAXCAM];	// 카메라 Open 여부
	BOOL			m_IsPlay[MAXCAM];	// Play 여부 (Grab & Show)
	CCrevisCtrl*	m_pCamCtrl[MAXCAM]; // 카메라용 Class 객체 포인터입니다. 
	HANDLE			m_hPlayThread[MAXCAM];		// Continuous mode용 thread
	HANDLE			m_hPlayTerminate[MAXCAM];	// Continuous mode stop용 event
	HANDLE			m_hOpenThread[MAXCAM];		// open 작업용 thread
	DOUBLE			m_CamExposure[MAXCAM]; // Exposure time입니다.
	CString			m_CamIP[MAXCAM];	// IP 주소 String입니다.
	INT32			m_CamTrig[MAXCAM]; // 카메라의 Trigger mode 입니다.
	CString			m_CamLightCh[MAXCAM]; // 카메라 별 사용할 Light Channel number입니다.
///////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////이미지 뷰어 관련 변수/////////////////////////////////////////////////////
	CMyImageView*	m_pImageView[MAXCAM];// 이미지 뷰어 객체
	INT32			m_statusCode;		// 프로그램 에러 코드를 저장하는 변수입니다.
	CString			m_strErr;			// 출력할 에러 String입니다
	CString			m_optionPath;		// option.ini 파일의 path (초기 실행시 한 번만 받아옴)
	CString			m_exePath;
	CClientDC*		m_pDC[MAXCAM];
	CRect			m_rcDisp[MAXCAM];
	HDC				m_hDC[MAXCAM];
///////////////////////////////////조명 컨트롤러 관련 변수/////////////////////////////////////
	CLightCtrl*		m_pLightCtrl;		 // Serial port Control용 객체
	BOOL			m_IsSerialOpen;		// Seiral Port Open여부
	BOOL			m_optionmodal;
	CString			m_ComPort;			// 조명 Controller에서 사용할 port number입니다.
	CString			m_BaudRate;			// 조명 Controller에서 사용할 baud rate입니다.
	CString			m_OptionBright[LIGHTCH];
////////////////////////////////////////////////////////////////////////////////////////////////

	

///////////////////////////////////비젼 알고리즘 관련 변수/////////////////////////////////////
	BOOL			m_IsAlgoMod[MAXCAM];		// 알고리즘 모드 OnOff
	CHVisionLibWrapper* m_pHVSWrapper[MAXCAM];			// HVS Wrapper
//////////////////////////////////////////////////////////////////////////////////////////

	CRITICAL_SECTION mSc; // 스레드 동작 Critical section

	BOOL			DrawImageContinuous(int dispNum);	// continuous mode용 시퀀스
	BOOL			GrabImageSWTrigger(int dispNum);	// SW Trigger 이용 이미지 Grab
	BOOL			DrawSingleImage(int dispNum);		// single frame draw
	BOOL			DrawProcessed(int dispNum);			// 이미지 뷰어 기능 적용된 Image draw
	void			thread1proc();						// Screen1ThreadProc에서 실행되는 스레드 프로세스 (1번 Screen grab -> draw)
	void			thread2proc();						// Screen2ThreadProc에서 실행되는 스레드 프로세스 (2번 Screen grab -> draw)
	void			Cam1OpenProc();						// 1번 cam open용 스레드 프로세스
	void			Cam2OpenProc();						// 2번 cam open용 스레드 프로세스
	
	// Context menu 클릭시 동작들
	void			OnCtxtClickedLarg1();
	void			OnCtxtClickedBin1();
	void			OnCtxtClickedLarg2();
	void			OnCtxtClickedBin2();
	void			OnCtxtClickedOvrly1();
	void			OnCtxtClickedOvrly2();
	
	afx_msg void OnBnClickedDebugdragon();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnBnClickedAlgomod();
	afx_msg void OnBnClickedAlgomod2();
	afx_msg void OnBnClickedAlgoadd1();
	afx_msg void OnBnClickedAlgoedit1();
	afx_msg void OnBnClickedAlgodel1();
	CListBox m_AlgoList1;
	CListBox m_TacTimeList1;
	CListBox m_OutputList1;
	afx_msg void OnBnClickedAlgoadd2();
	afx_msg void OnBnClickedAlgoedit2();
	afx_msg void OnBnClickedAlgodel2();
	afx_msg void OnBnClickedRun2();
	afx_msg void OnBnClickedSavercd2();
	afx_msg void OnBnClickedClearrcd2();
	afx_msg void OnBnClickedLoadrcd1();
	afx_msg void OnBnClickedLoadrcd2();
	CListBox m_AlgoLlist2;
	CListBox m_OutputList2;
	CListBox m_TacTimeList2;
	
};
