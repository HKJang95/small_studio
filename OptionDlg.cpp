// OptionDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "OptionDlg.h"

#include "afxdialogex.h"

#define BAUD 17
#define MAXLIGHT 255


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
	DDX_Control(pDX, IDC_CAM1LIGHTCH, m_Cam1LightCH);
	DDX_Control(pDX, IDC_CAM2LIGHTCH, m_Cam2LightCH);
	DDX_Control(pDX, IDC_LIGHTPORT, m_LightPortCombo);
	DDX_Control(pDX, IDC_BAUDRATE, m_BaudRateCombo);
	DDX_Control(pDX, IDC_CH1LV, m_Chan1Combo);
	DDX_Control(pDX, IDC_CH2LV, m_Chan2Combo);
	DDX_Control(pDX, IDC_CH3LV, m_Chan3Combo);
	DDX_Control(pDX, IDC_CH4LV, m_Chan4Combo);
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &COptionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &COptionDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_LTESTBTN, &COptionDlg::OnBnClickedLtestbtn)
END_MESSAGE_MAP()


// COptionDlg 메시지 처리기입니다.

BOOL COptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString cstr;
	CString baudrate[BAUD] = { _T("300"), _T("600"), _T("900"), _T("1200"), _T("2400"), _T("4800"), _T("9600"), _T("14400"), _T("19200"), _T("28800"),
		_T("33600"), _T("38400"), _T("56000"), _T("57600"), _T("115200"), _T("128000"), _T("256000") };
	
	cstr.Format(_T("Software Trigger"));
	m_Cam1ModeCombo.InsertString(CAMERA_TRIG_SW, cstr);
	m_Cam2ModeCombo.InsertString(CAMERA_TRIG_SW, cstr);

	cstr.Format(_T("Continuous"));
	m_Cam1ModeCombo.InsertString(CAMERA_TRIG_CONTINUOUS, cstr);
	m_Cam2ModeCombo.InsertString(CAMERA_TRIG_CONTINUOUS, cstr);

	m_Cam1ModeCombo.SetCurSel(_ttoi(m_CamTrig[0])); 
	m_Cam2ModeCombo.SetCurSel(_ttoi(m_CamTrig[1]));

	for (int i = 0; i < LIGHTCH; i++)
	{
		cstr.Format(_T("%d"), i+1);
		m_Cam1LightCH.InsertString(i, cstr);
		m_Cam2LightCH.InsertString(i, cstr);

		if (m_CamLightCh[0] == cstr)
		{
			m_Cam1LightCH.SetCurSel(i);
		}

		if (m_CamLightCh[1] == cstr)
		{
			m_Cam2LightCH.SetCurSel(i);
		}
	}

	for (int i = 0; i < 20; i++)
	{
		cstr.Format(_T("COM%d"), i+1);
		m_LightPortCombo.InsertString(i, cstr);

		if (m_ComPort == cstr)
		{
			m_LightPortCombo.SetCurSel(i);
		}
	}

	for (int i = 0; i < BAUD; i++)
	{
		m_BaudRateCombo.InsertString(i, baudrate[i]);

		if (m_BaudRate == baudrate[i])
		{
			m_BaudRateCombo.SetCurSel(i);
		}
	}

	for (int i = 0; i <= MAXLIGHT; i++)
	{
		cstr.Format(_T("%d"), i);
		m_Chan1Combo.InsertString(i, cstr);
		m_Chan2Combo.InsertString(i, cstr);
		m_Chan3Combo.InsertString(i, cstr);
		m_Chan4Combo.InsertString(i, cstr);
	}

	m_Chan1Combo.SetCurSel(_ttoi(m_OptionBright[0]));
	m_Chan2Combo.SetCurSel(_ttoi(m_OptionBright[1]));
	m_Chan3Combo.SetCurSel(_ttoi(m_OptionBright[2]));
	m_Chan4Combo.SetCurSel(_ttoi(m_OptionBright[3]));

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

	// 콤보박스 setting 가져오기 20201105 장한결
	grabmode.Format(_T("%d"), m_Cam1ModeCombo.GetCurSel());
	m_CamTrig[0] = grabmode;
	
	grabmode.Format(_T("%d"), m_Cam2ModeCombo.GetCurSel());
	m_CamTrig[1] = grabmode;

	m_Cam1LightCH.GetLBText(m_Cam1LightCH.GetCurSel(), m_CamLightCh[0]);
	m_Cam1LightCH.GetLBText(m_Cam1LightCH.GetCurSel(), m_CamLightCh[1]);
	
	m_BaudRateCombo.GetLBText(m_BaudRateCombo.GetCurSel(), m_BaudRate);
	m_LightPortCombo.GetLBText(m_LightPortCombo.GetCurSel(), m_ComPort);
	m_Chan1Combo.GetLBText(m_Chan1Combo.GetCurSel(), m_OptionBright[0]);
	m_Chan2Combo.GetLBText(m_Chan2Combo.GetCurSel(), m_OptionBright[1]);
	m_Chan3Combo.GetLBText(m_Chan3Combo.GetCurSel(), m_OptionBright[2]);
	m_Chan4Combo.GetLBText(m_Chan4Combo.GetCurSel(), m_OptionBright[3]);

	// 카메라 옵션 ini 저장 20201105 장한결
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
		WritePrivateProfileString(camnum, _T("LIGHTCH"), m_CamLightCh[i], m_optionPath);
	}

	WritePrivateProfileString(_T("LLIGHT4CH"), _T("PORT"), m_ComPort, m_optionPath);
	WritePrivateProfileString(_T("LLIGHT4CH"), _T("BAUD"), m_BaudRate, m_optionPath);

	INT32 brightness[LIGHTCH] = { 0 };

	for (int i = 0; i < LIGHTCH; i++)
	{
		brightness[i] = _ttoi(m_OptionBright[i]);
		if (brightness[i] > 99)
		{

		}
		else if (brightness[i] < 100 && brightness[i] > 9)
		{
			m_OptionBright[i].Format(_T("0%d"), brightness[i]);
		}
		else
		{
			m_OptionBright[i].Format(_T("00%d"), brightness[i]);
		}

		CString cstr;
		cstr.Format(_T("CH%d"), i + 1);
		WritePrivateProfileString(_T("LLIGHT4CH"), cstr, m_OptionBright[i], m_optionPath);
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

void COptionDlg::OnBnClickedLtestbtn()
{
	CString checkProtocol;
	char stx = 0x02;
	char etx = 0x03;
	INT32 brightness[LIGHTCH] = { 0 };
	CString testBright[LIGHTCH] = { _T("") };

	m_Chan1Combo.GetLBText(m_Chan1Combo.GetCurSel(), testBright[0]);
	m_Chan2Combo.GetLBText(m_Chan2Combo.GetCurSel(), testBright[1]);
	m_Chan3Combo.GetLBText(m_Chan3Combo.GetCurSel(), testBright[2]);
	m_Chan4Combo.GetLBText(m_Chan4Combo.GetCurSel(), testBright[3]);

	for (int i = 0; i < LIGHTCH; i++)
	{
		brightness[i] = _ttoi(testBright[i]);
		if (brightness[i] > 99)
		{

		}
		else if (brightness[i] < 100 && brightness[i] > 9)
		{
			m_OptionBright[i].Format(_T("0%d"), brightness[i]);
		}
		else
		{
			m_OptionBright[i].Format(_T("00%d"), brightness[i]);
		}
	}

	checkProtocol.Format(_T("CHAS%s%s%s%s"), m_OptionBright[0], m_OptionBright[1], m_OptionBright[2], m_OptionBright[3]);

	CString sendASCII = (CString)(stx + checkProtocol + etx);
	GetDlgItem(IDC_LTESTSEND)->SetWindowText(sendASCII);

	if (m_pLightCtrl != NULL)
	{
		m_pLightCtrl->Send(sendASCII);
		Sleep(10);
		checkProtocol.Format(_T("CHAS000000000000"));
		sendASCII = (CString)(stx + checkProtocol + etx);
		m_pLightCtrl->Send(sendASCII);
		Sleep(10);
	}
	else
	{
		AfxMessageBox(_T("Light Controller가 연결되지 않았습니다."));
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


LRESULT	COptionDlg::OnReceive(WPARAM length, LPARAM lpara)
{
	CString str;
	char data[10000];
	if (m_pLightCtrl)
	{
		m_pLightCtrl->Receive(data, (int)length);
		data[length] = '\0';
		str = data;
		GetDlgItem(IDC_LTESTRCV)->SetWindowTextW(str);
		str = "";
	}

	return 0;
}
