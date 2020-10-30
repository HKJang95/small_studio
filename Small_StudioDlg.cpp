
// Small_StudioDlg.cpp : 구현 파일
//

#include "stdafx.h"

#include "Small_Studio.h"
#include "Small_StudioDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSmall_StudioDlg 대화 상자



CSmall_StudioDlg::CSmall_StudioDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSmall_StudioDlg::IDD, pParent)
	, m_IsSystemInit(false)
	, m_statusCode(-99999)
	, m_strErr(_T(""))
	, m_optionPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for (int i = 0; i < MAXCAM; i++)
	{
		m_pCamCtrl[i] = NULL;
		m_CamIP[i] = _T("");
		m_IsOpen[i] = FALSE;
	}
}

void CSmall_StudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSmall_StudioDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CAM1OPEN, &CSmall_StudioDlg::OnBnClickedCam1open)
	ON_BN_CLICKED(IDC_CAM2OPEN, &CSmall_StudioDlg::OnBnClickedCam2open)
	ON_BN_CLICKED(IDC_OPTIONBTN, &CSmall_StudioDlg::OnBnClickedOptionbtn)
	ON_BN_CLICKED(IDC_LIGHTOPEN, &CSmall_StudioDlg::OnBnClickedLightopen)
	ON_BN_CLICKED(IDC_CAM1PLAY, &CSmall_StudioDlg::OnBnClickedCam1play)
	ON_BN_CLICKED(IDC_CAM2PLAY, &CSmall_StudioDlg::OnBnClickedCam2play)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CSmall_StudioDlg 메시지 처리기

BOOL CSmall_StudioDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_optionPath.Format(_T("%s\\option.ini"), GetExePath());
	GetOptionValue();

	if (ST_InitSystem() != MCAM_ERR_SUCCESS)
	{
		AfxMessageBox(_T("주의 ! Crevis Camera 라이브러리를 초기화 할 수 없습니다."));
		m_IsSystemInit = false;
	}
	else
	{
		m_IsSystemInit = true;
	}

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSmall_StudioDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSmall_StudioDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSmall_StudioDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSmall_StudioDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	

	if (m_IsSystemInit)
	{
		ST_FreeSystem();
	}
}

BOOL CSmall_StudioDlg::camOpenSeq(int dispNum)
{
	if (!m_IsSystemInit)
	{
		AfxMessageBox(_T("System Init이 되지 않았습니다. 카메라를 사용할 수 없습니다."));
		return FALSE;
	}
	m_pCamCtrl[dispNum] = new CCrevisCtrl(m_CamIP[dispNum]);
	m_statusCode = m_pCamCtrl[dispNum]->OpenDevice();
	m_strErr.Format(_T("!!!!!!!!!!!!!!!!!!!!! DEBUG %d Cam status : %d !!!!!!!!!!!!!!!!!\n"),dispNum, m_statusCode);
	OutputDebugString(m_strErr);
	if (m_statusCode != CAMERA_OPEN_SUCCESS)
	{
		delete m_pCamCtrl[dispNum];
		m_CamIP[dispNum] = _T("");
		WritePrivateProfileString(_T("CAMERA_1"), _T("IP"), NULL, _T("Option.ini"));
		return FALSE;
	}
	return TRUE;
}


void CSmall_StudioDlg::OnBnClickedCam1open()
{
	GetDlgItem(IDC_CAM1OPEN)->EnableWindow(FALSE);
	if (!m_IsOpen[0])
	{
		if (camOpenSeq(0))
		{
			m_IsOpen[0] = TRUE;
			GetDlgItem(IDC_CAM1OPEN)->SetWindowTextW(_T("Camera 1 Open"));
		}
		else
		{
			m_strErr.Format(_T("카메라 Open 실패!"));
			AfxMessageBox(m_strErr);
		}
	}
	else
	{
		delete m_pCamCtrl[0];
		GetDlgItem(IDC_CAM1OPEN)->SetWindowTextW(_T("Camera 1 Closed"));
	}
	GetDlgItem(IDC_CAM1OPEN)->EnableWindow(TRUE);
}


void CSmall_StudioDlg::OnBnClickedCam2open()
{
	GetDlgItem(IDC_CAM2OPEN)->EnableWindow(FALSE);
	if (!m_IsOpen[1])
	{
		if (camOpenSeq(1))
		{
			m_IsOpen[1] = TRUE;
			GetDlgItem(IDC_CAM2OPEN)->SetWindowTextW(_T("Camera 2 Open"));
		}
		else
		{
			m_strErr.Format(_T("카메라 Open 실패!"));
			AfxMessageBox(m_strErr);
		}
	}
	else
	{
		delete m_pCamCtrl[1];
		GetDlgItem(IDC_CAM2OPEN)->SetWindowTextW(_T("Camera 2 Closed"));
	}
	GetDlgItem(IDC_CAM2OPEN)->EnableWindow(TRUE);
}


void CSmall_StudioDlg::OnBnClickedOptionbtn()
{
	COptionDlg optiondlg;
	GetOptionValue();
	
	for (int i = 0; i < MAXCAM; i++)
	{
		optiondlg.m_CamIP[i] = m_CamIP[i];
		optiondlg.m_CamExposure[i] = m_CamExposure[i];
	}
	optiondlg.m_optionPath = m_optionPath;
	if (IDOK == optiondlg.DoModal())
	{
		for (int i = 0; i < MAXCAM; i++)
		{
			m_CamIP[i] = optiondlg.m_CamIP[i];
			m_CamExposure[i] = optiondlg.m_CamExposure[i];
			// !!!!!!!!!!!!!!!!!!!! EXPOSURE TIME SET 꾸현하끼끼끼 !!!!!!!!!!!!!!!!!!!!!!
		}
	}

	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CSmall_StudioDlg::OnBnClickedLightopen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CSmall_StudioDlg::OnBnClickedCam1play()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CSmall_StudioDlg::OnBnClickedCam2play()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

// Option값 설정을 위한 현재 실행파일 경로 반환 20201030 장한결
CString CSmall_StudioDlg::GetExePath()
{
	static TCHAR pBuf[256] = { 0, };
	memset(pBuf, NULL, sizeof(pBuf));
	GetModuleFileName(NULL, pBuf, sizeof(pBuf));
	CString strFilePath;
	strFilePath.Format(_T("%s"), pBuf);
	strFilePath = strFilePath.Left(strFilePath.ReverseFind(_T('\\')));
	return strFilePath;
}

// option.ini 파일에서 값 읽어오는 함수 20201030 장한결
BOOL CSmall_StudioDlg::GetOptionValue()
{
	LPWSTR cBuf;
	cBuf = new WCHAR[256];
	for (int i = 0; i < MAXCAM; i++)
	{
		CString camnum;
		camnum.Format(_T("CAMERA%d"), i + 1);
		GetPrivateProfileStringW(camnum, _T("IP"), _T(""), cBuf, 256, m_optionPath);
		m_CamIP[i] = cBuf;
		GetPrivateProfileStringW(camnum, _T("Exposure"), _T(""), cBuf, 256, m_optionPath);
		m_CamExposure[i] = cBuf;
	}
	delete cBuf;

	return TRUE;
}

