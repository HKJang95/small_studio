
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
	BOOL camOpenSeq(int dispNum);
	CString GetExePath();
	BOOL GetOptionValue();
	BOOL GetOptionValue(int dispNum);

public:
	bool			m_IsSystemInit;		// Camera SDK Init 상태 점검입니다.
	BOOL			m_IsOpen[MAXCAM];
	CCrevisCtrl*	m_pCamCtrl[MAXCAM]; // 카메라용 Class 객체 포인터입니다. 
	INT32			m_statusCode;		// 프로그램 에러 코드를 저장하는 변수입니다.
	CString			m_strErr;			// 출력할 에러 String입니다
	CString			m_CamIP[MAXCAM];	// 사용자로부터 입력받을 IP 주소 String입니다.
	DOUBLE			m_CamExposure[MAXCAM];
	CString			m_optionPath;
};
