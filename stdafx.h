
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.
#define MAXCAM 2
#define LIGHTCH 4



// 카메라 관련 에러코드 20201030 장한결
enum CAMERA_ERRCODE 
{ 
	CAMERA_OPEN_SUCCESS		= 0, 
	CAMSYS_NOT_INIT			= -1000, 
	CAMERA_OPEN_ERROR		= -1001, 
	NO_CAMERA_DETECTED		= -1002, 
	CAMERA_CLOSE_SUCCESS	= 0,
	CAMERA_CLOSE_FAIL		= -1003,
	CAMERA_CLOSE_NOTOPEN	= -1004,
	CAMERA_IP_NOTFOUND		= -1,
	CAMERA_MODCH_FAIL		= -1005,
	CAMERA_INFOGET_FAIL		= -1006,
	CAMERA_ACQ_FAIL			= -1007,
	CAMERA_TRIG_SW			= 0,
	CAMERA_TRIG_CONTINUOUS	= 1
};

enum OPTION_READ_MODE
{
	OPT_READ_ALL			= 0,
	OPT_READ_CAM			= 1,
	OPT_READ_PLAY			= 2,
	OPT_READ_LIGHT			= 3
};
#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원


// GDI+
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;
//

#include "VirtualFG40.h" // Crevis Camera용 SDK include

#pragma warning (disable:4819)
#pragma warning (disable:4996)

#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


#include "HVisionErrCode.h"
#include "HVisionLibWrapper.h"
#include "HVisionParameter.h"


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' nae='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

