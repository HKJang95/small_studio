
// Small_StudioDlg.h : 헤더 파일
//

#pragma once
#include "CrevisCtrl.h"
#include "Small_StudioDlg.h"
#include "Small_Studio.h"
#include "OptionDlg.h"


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

private:
	BOOL			camOpenSeq(int dispNum);
	CString			GetExePath();
	BOOL			GetOptionValue(int mode);
	BOOL			GetOptionValue(int mode, int dispNum);
	BOOL			DrawImageSeq(int dispNum);
	BOOL			DIBMake(int dispNum);
	BOOL			hbitmap2CImage(int dispNum);

public:
	bool			m_IsSystemInit;		// Camera SDK Init 상태 점검입니다.
	BOOL			m_IsOpen[MAXCAM];	// 카메라 Open 여부
	BOOL			m_IsPlay[MAXCAM];	// Play 여부 (Grab & Show)
	CCrevisCtrl*	m_pCamCtrl[MAXCAM]; // 카메라용 Class 객체 포인터입니다. 
	INT32			m_statusCode;		// 프로그램 에러 코드를 저장하는 변수입니다.
	CString			m_strErr;			// 출력할 에러 String입니다

	CString			m_optionPath;		// option.ini 파일의 path (초기 실행시 한 번만 받아옴)

	HBITMAP			m_hBmp[MAXCAM];
	CImage*			m_pCOriImage[MAXCAM]; // 이미지 객체

	//option.ini 파일에서 read할 변수 20201103 장한결
	CString			m_ComPort;			// 조명 Controller에서 사용할 port number입니다.
	CString			m_BaudRate;			// 조명 Controller에서 사용할 baud rate입니다.
	CString			m_CamIP[MAXCAM];	// IP 주소 String입니다.
	DOUBLE			m_CamExposure[MAXCAM]; // Exposure time입니다.
	INT32			m_CamTrig[MAXCAM]; // 카메라의 Trigger mode 입니다.



	CRITICAL_SECTION mSc;
};
