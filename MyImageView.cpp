// MyImageView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Small_Studio.h"
#include "MyImageView.h"


// CMyImageView

IMPLEMENT_DYNAMIC(CMyImageView, CWnd)

CMyImageView::CMyImageView()
{
	m_OriMat = cv::Mat();
	m_DrawMat = cv::Mat();
	m_rawHeight = -1;
	m_rawWidth = -1;
	m_Islarger = FALSE;
	m_pBitmapInfo = NULL;
	m_largerTopLeft = cv::Point(-1, -1);
	m_RealLargeTopLeft = cv::Point(-1, -1);
	m_IsMove = FALSE;
	m_prevMouse = CPoint(0, 0);
	m_IsCursorBin = FALSE;
	m_IsCursorLarger = FALSE;
	m_IsOverlay = TRUE;
}

CMyImageView::~CMyImageView()
{
	if (m_pBitmapInfo != NULL)
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}
}
BEGIN_MESSAGE_MAP(CMyImageView, CWnd)
END_MESSAGE_MAP()

// 이미지 re-capture시 BOOL 값들 Reset
void CMyImageView::ImageViewerReset()
{
	m_Islarger = FALSE;
	m_IsMove = FALSE;
	m_IsCursorLarger = FALSE;
	m_IsCursorBin = FALSE;
}

// BYTE (이미지) -> Mat 20201113 장한결
void CMyImageView::pByteToMat(BYTE* imgbits, int width, int height)
{
	m_OriMat = cv::Mat();
	if (imgbits != NULL)
	{
		m_OriMat = cv::Mat(height, width, CV_8UC1, imgbits).clone();
		m_rawWidth = width;
		m_rawHeight = height;
	}
}

// 이미지 Drag 시 좌표를 "이동" 해주는 함수 20201117 장한결
void CMyImageView::largerTopLeftMover(CPoint mpoint)
{
	if (m_Islarger && m_IsMove)
	{ 
		// + 방향 이동
		if (mpoint.x > m_prevMouse.x)
		{
			m_RealLargeTopLeft.x += abs(mpoint.x - m_prevMouse.x);		
		}
		if (mpoint.y > m_prevMouse.y)
		{
			m_RealLargeTopLeft.y += abs(mpoint.y - m_prevMouse.y);
		}
		// - 방향 이동
		if (mpoint.x < m_prevMouse.x)
		{
			m_RealLargeTopLeft.x -= abs(m_prevMouse.x - mpoint.x);
		}
		if (mpoint.y < m_prevMouse.y)
		{
			m_RealLargeTopLeft.y -= abs(m_prevMouse.x - mpoint.x);
		}

		// - 좌표방향 Lock
		if (m_RealLargeTopLeft.x < 0)
		{
			m_RealLargeTopLeft.x = 0;
		}
		if (m_RealLargeTopLeft.y < 0)
		{
			m_RealLargeTopLeft.y = 0;
		}
		// + 좌표방향 Lock
		if (m_RealLargeTopLeft.x > m_DrawMat.cols / 2)
		{
			m_RealLargeTopLeft.x = m_DrawMat.cols / 2;
		}

		if (m_RealLargeTopLeft.y > m_DrawMat.rows / 2)
		{
			m_RealLargeTopLeft.y = m_DrawMat.rows / 2;
		}

	}
	m_prevMouse = mpoint;
}

// 이미지 확대 시 좌표를 "변환" 해주는 함수 20201117 장한결
void CMyImageView::largerScreen(cv::Point pt)
{
	if (m_OriMat.empty())
	{
		return;
	}
	else
	{
		if (pt.x < 0)
		{
			m_RealLargeTopLeft.x = 0;
			m_RealLargeTopLeft.y = 0;
			m_largerTopLeft.x = 0;
			m_largerTopLeft.y = m_DrawMat.rows / 2;
		}
		else
		{
			// 실제 확대 영역의 Rect 왼쪽 상단 좌표
			m_RealLargeTopLeft.x = pt.x;
			m_RealLargeTopLeft.y = pt.y;

			// 영상 정 가운데점이 왼쪽 상단 좌표로 가질 수 있는 최댓값 (Lock)
			if (m_RealLargeTopLeft.x > m_DrawMat.cols / 2)
			{
				m_RealLargeTopLeft.x = m_DrawMat.cols / 2;
			}

			if (m_RealLargeTopLeft.y > m_DrawMat.rows / 2)
			{
				m_RealLargeTopLeft.y = m_DrawMat.rows / 2;
			}

			// 실제 StretchDIBits에서 사용될 좌표값 (환산이 필요함)
			m_largerTopLeft.x = m_RealLargeTopLeft.x;
			m_largerTopLeft.y = m_DrawMat.rows / 2 - m_RealLargeTopLeft.y;
		}
	}
}

// 디스플레이 내부 마우스 좌표 -> 이미지 실제 좌표 변환식
cv::Point CMyImageView::cursorPtToImage(CPoint point, CPoint rectTopLeft, CPoint rectBottomRight)
{
	cv::Point insidePoint;
	cv::Point imgPoint;
	cv::Point displaySize(rectBottomRight.x - rectTopLeft.x, rectBottomRight.y - rectTopLeft.y);
	// 이미지 확대 시
	if (m_Islarger)
	{
		// 확대 시작지점 ~ 이미지 사이즈 / 2 길이 폭|높이
		// 이부분 현재 작동 이상하게 함.......
		insidePoint.x = point.x - (rectTopLeft.x + m_RealLargeTopLeft.x);
		insidePoint.y = point.y - (rectTopLeft.y + m_RealLargeTopLeft.y);
		imgPoint.x = m_DrawMat.cols / 2;
		imgPoint.y = m_DrawMat.rows / 2;
	}
	else
	{
		// 마우스 좌표 - 디스플레이 좌측상단 좌표 = 이미지 내부 좌표
		insidePoint.x = point.x - rectTopLeft.x; // 0,0 기준 좌표
		insidePoint.y = point.y - rectTopLeft.y;
		imgPoint.x = m_DrawMat.cols;
		imgPoint.y = m_DrawMat.rows;
	}
	return cv::Point
		(
		int(imgPoint.x * insidePoint.x / displaySize.x), // 변환된 x
		int(imgPoint.y * insidePoint.y / displaySize.y)  // 변환된 y
		);

	// 디스플레이 좌표 != 이미지 좌표이므로 환산식이 필요함
	// 그려질 이미지 길이 : 디스플레이 길이 = 이미지에서 좌표 (구할 값) : 측정된 좌표
	// 이미지에서 좌표 = 측정된 좌표 * 그려질 이미지 길이 / 디스플레이 길이
}

// Mat 에 마우스 포인터가 가르키는 위치의 RGB값 출력 20201116 장한결
void CMyImageView::cvCursorRGB(CPoint point, cv::Point textPoint , CPoint rectTopLeft, CPoint rectBottomRight)
{
	CString textToDraw = _T("");
	// 그려질 이미지 끝부분 X,Y 좌표
	int fontSize = 0;
	if (m_OriMat.empty())
	{
		return;
	}
	else
	{
		if (m_Islarger == FALSE)
		{
			m_DrawMat = m_OriMat.clone();
			m_showWidth = m_rawWidth;
			m_showHeight = m_rawHeight;
			fontSize = 2;
		}
		else
		{
			m_DrawMat = m_OriMat.clone();
			fontSize = 1;
		}
	}
	// 커서 위치가 display rect 내부에 있을때만 동작
	if (point.x >= rectTopLeft.x && point.y >= rectTopLeft.y)
	{
		if (point.x <= rectBottomRight.x && point.y <= rectBottomRight.y)
		{
			// 이미지 기준으로 마우스 포인터 위치 변환
			cv::Point RealPoint = cursorPtToImage(point, rectTopLeft, rectBottomRight);
		
			// 해당 위치 gray lv value 획득
			int rgbv = m_OriMat.at<uchar>(RealPoint);

			// Text 출력
			CString stringToDraw;
			stringToDraw.Format(_T("%d %d / : %d"), RealPoint.x, RealPoint.y,rgbv);
			cv::String str = CT2A(stringToDraw);
			cv::putText(m_DrawMat, str, textPoint, cv::FONT_HERSHEY_SIMPLEX, fontSize, cv::Scalar(155, 0, 0), fontSize);
		}
	}
}

// 생성될 때 지정된 디스플레이에 Mat 출력 시 필요한 bitmapinfo 20201113 장한결
void CMyImageView::createBitmapInfo(cv::Mat mat)
{
	if (m_pBitmapInfo != NULL)
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}
	int w = mat.cols;
	int h = mat.rows;
	int bpp = 8;

	if (bpp == 8)
		m_pBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	else // 24 or 32bit
		m_pBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biBitCount = bpp;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;

	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	}
	m_pBitmapInfo->bmiHeader.biWidth = w;
	m_pBitmapInfo->bmiHeader.biHeight = -h;
}

// 커서부분 확대가 활성화 될 시 작동 20201118 장한결
void CMyImageView::cursorLarger(CPoint mpoint, CPoint rectTopLeft, CPoint rectBottomRight)
{
	if (m_OriMat.empty() || m_DrawMat.empty())
	{
		return;
	}

	// ROI칠 폭/높이
	int width = 150;
	int height = 100;

	// resize 할 배율
	int resizeVal = 1;
	// 마우스 포인터에서 떨어뜨릴 x,y축의 값
	int drawPosit = 0;

	// 영상 전체 확대 / 미확대 둘다 영상배율 같음
	if (m_Islarger)
	{
		// 확대시 영상 2배확대
		// 전체 뷰어 이미 2배 되어있음 (2x2 = 4배)
		resizeVal = 2;
		drawPosit = 25;
	}
	else
	{
		// 확대하지 않을 시 영상 4배확대
		resizeVal = 4;
		drawPosit = 50;
	}



	// 커서위치 이미지 기준으로 변환
	cv::Point RealPoint = cursorPtToImage(mpoint, rectTopLeft, rectBottomRight);

	// Mat 가 그려질 수 있는 최대범위
	cv::Point subImgBottomRight(RealPoint.x + (width * 4 + 4) + drawPosit, RealPoint.y + (height * 4 + 4) + drawPosit);
	// ROI 영역이 그려질 위치
	cv::Point drawPoint(RealPoint.x + drawPosit, RealPoint.y + drawPosit);

	// ROI영역이 그려질 때
	// ROI 영역의 끝이 x,y limit에 닿을 경우 마우스 포인터 기준 반대방향에 draw
	if (subImgBottomRight.x > m_DrawMat.cols)
	{
		drawPoint.x = RealPoint.x - (width * 4 + 4) - drawPosit;
	}

	if (subImgBottomRight.y > m_DrawMat.rows)
	{
		drawPoint.y = RealPoint.y - (height * 4 + 4) - drawPosit;
	}

	// ROI 영역 기준점을 잡을 때
	// 기준점이 영상 영역을 벗어나면 Lock
	if (RealPoint.x + width >= m_DrawMat.cols)
	{
		return;
	}

	if (RealPoint.y + height >= m_DrawMat.rows)
	{
		return;
	}

	if (RealPoint.x < 0 || RealPoint.y < 0)
	{
		return;
	}

	// ROI칠 위치, 사이즈 지정
	cv::Rect ROIrect(RealPoint.x, RealPoint.y, width, height);
	cv::Mat subImage = m_OriMat(ROIrect);
	// 확대
	cv::resize(subImage, subImage, cv::Size(), resizeVal, resizeVal);

	// 해당 영역 이진화 선택시 이진화
	if (m_IsCursorBin)
	{
		cv::threshold(subImage, subImage, 127, 255, cv::THRESH_BINARY);
	}
	
	// ROI친 이미지에 Border 삽입 (구분 잘 되기 위함)
	cv::copyMakeBorder(subImage, subImage, 2, 2, 2, 2, cv::BORDER_CONSTANT, cv::Scalar(155, 0, 0));

	
	// (큰 이미지 + ROI친 이미지) 합성
	for (int i = 0; i < subImage.cols; i++)
	{
		for (int j = 0; j < subImage.rows; j++)
		{
			int x = i + drawPoint.x;
			int y = j + drawPoint.y;
			m_DrawMat.at<uchar>(y,x) = subImage.at<uchar>(j,i);
		}
	}
}