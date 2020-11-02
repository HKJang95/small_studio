// OptionDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "OptionDlg.h"

#include "afxdialogex.h"


// COptionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COptionDlg, CDialogEx)

COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COptionDlg::IDD, pParent)
{

}

COptionDlg::~COptionDlg()
{
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAM1MODE, m_Cam1ModeCombo);
	DDX_Control(pDX, IDC_CAM2MODE, m_Cam2ModeCombo);
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &COptionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &COptionDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// COptionDlg 메시지 처리기입니다.

BOOL COptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString cstr;
	
	cstr.Format(_T("Software Trigger"));
	m_Cam1ModeCombo.InsertString(CAMERA_TRIG_SW, cstr);
	m_Cam2ModeCombo.InsertString(CAMERA_TRIG_SW, cstr);

	cstr.Format(_T("Continuous"));
	m_Cam1ModeCombo.InsertString(CAMERA_TRIG_CONTINUOUS, cstr);
	m_Cam2ModeCombo.InsertString(CAMERA_TRIG_CONTINUOUS, cstr);

	m_Cam1ModeCombo.SetCurSel(_ttoi(m_CamTrig[0])); 
	m_Cam2ModeCombo.SetCurSel(_ttoi(m_CamTrig[1]));

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	GetDlgItem(IDC_CAM1IPCONTROL)->SetWindowTextW(m_CamIP[0]);
	GetDlgItem(IDC_CAM2IPCONTROL)->SetWindowTextW(m_CamIP[1]);
	GetDlgItem(IDC_CAM1EXPEDIT)->SetWindowTextW(m_CamExposure[0]);
	GetDlgItem(IDC_CAM2EXPEDIT)->SetWindowTextW(m_CamExposure[1]);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COptionDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_CAM1IPCONTROL, m_CamIP[0]);
	GetDlgItemText(IDC_CAM2IPCONTROL, m_CamIP[1]);
	GetDlgItemText(IDC_CAM1EXPEDIT, m_CamExposure[0]);
	GetDlgItemText(IDC_CAM2EXPEDIT, m_CamExposure[1]);
	
	CString grabmode;

	grabmode.Format(_T("%d"), m_Cam1ModeCombo.GetCurSel());
	m_CamTrig[0] = grabmode;
	
	grabmode.Format(_T("%d"), m_Cam2ModeCombo.GetCurSel());
	m_CamTrig[1] = grabmode;
	
	for (int i = 0; i < MAXCAM; i++)
	{
		if (_ttof(m_CamExposure[i]) > 65555.0f || _ttof(m_CamExposure[i]) < 0.0f)
		{
			AfxMessageBox(_T("Exposure Time은 0~65535 사이의 값을 입력 바랍니다."));
			return;
		}

		CString camnum;
		camnum.Format(_T("CAMERA%d"), i + 1);
		WritePrivateProfileString(camnum, _T("IP"), m_CamIP[i], m_optionPath);
		WritePrivateProfileString(camnum, _T("Exposure"), m_CamExposure[i], m_optionPath);
		WritePrivateProfileString(camnum, _T("GRAB_MODE"), m_CamTrig[i], m_optionPath);
	}

	CDialogEx::OnOK();
}

void COptionDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

void COptionDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}