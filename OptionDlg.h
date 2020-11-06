#pragma once
#include "stdafx.h"
#include "Small_StudioDlg.h"
#include "Small_Studio.h"
#include "LightCtrl.h"
#include "afxwin.h"

// COptionDlg 대화 상자입니다.

class COptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COptionDlg)

public:
	LRESULT	OnReceive(WPARAM length, LPARAM lpara);
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
	
	// main dialog 변수
	CString			m_optionPath;
	CLightCtrl*		m_pLightCtrl;

	// 카메라
	CString			m_CamIP[MAXCAM];
	CString			m_CamExposure[MAXCAM];
	CString			m_CamTrig[MAXCAM];
	CString			m_CamLightCh[MAXCAM];

	// 조명
	CString			m_ComPort;
	CString			m_BaudRate;
	CString			m_OptionBright[LIGHTCH];
	
	// 콤보 Booox
	CComboBox m_Cam1ModeCombo;
	CComboBox m_Cam2ModeCombo;
	CComboBox m_Cam1LightCH;
	CComboBox m_Cam2LightCH;
	CComboBox m_LightPortCombo;
	CComboBox m_BaudRateCombo;
	CComboBox m_Chan1Combo;
	CComboBox m_Chan2Combo;
	CComboBox m_Chan3Combo;
	CComboBox m_Chan4Combo;
	afx_msg void OnBnClickedLtestbtn();
};
