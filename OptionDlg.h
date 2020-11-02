#pragma once
#include "stdafx.h"
#include "Small_StudioDlg.h"
#include "Small_Studio.h"
#include "afxwin.h"

// COptionDlg 대화 상자입니다.

class COptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COptionDlg)

public:
	COptionDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COptionDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OPTIONDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCam1ipsetbtn();
	afx_msg void OnBnClickedCam2ipsetbtn();
	afx_msg void OnBnClickedCam1expset();
	afx_msg void OnBnClickedCam2expset();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();

public:
	CString			m_CamIP[MAXCAM];
	CString			m_CamExposure[MAXCAM];
	CString			m_CamTrig[MAXCAM];
	CString			m_optionPath;
	afx_msg void OnBnClickedSerialsetbtn();
	// 카메라 Grab Mode 설정용 콤보박스 20201102 장한결
	CComboBox m_Cam1ModeCombo;
	CComboBox m_Cam2ModeCombo;
};
