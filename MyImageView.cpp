// MyImageView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Small_Studio.h"
#include "MyImageView.h"


// CMyImageView

IMPLEMENT_DYNAMIC(CMyImageView, CWnd)

CMyImageView::CMyImageView()
{
	m_pBitmap = NULL;
}

CMyImageView::~CMyImageView()
{

}

// Clone 떠서 Mat으로 변환시킴
void CMyImageView::cloneBitmap(Bitmap* oriBitmap)
{
	if (oriBitmap != NULL)
	{
		m_pBitmap = oriBitmap->Clone(0, 0, oriBitmap->GetWidth(), oriBitmap->GetHeight(), oriBitmap->GetPixelFormat());
	}
	else return;
}

// Image quality 문제로 미사용.
// MemDC를 활용, text를 이미지 위에 띄워줌 20201112 장한결
void CMyImageView::cursorRGB(CPoint point, CPoint rectTopLeft, CPoint rectBottomRight)
{
	if (m_pBitmap != NULL)
	{
		CPoint imgPoint;
		CPoint insidePoint;
		CPoint RealPoint;
		Color color;
		CString textToDraw = _T("");
		if (point.x >= rectTopLeft.x && point.y >= rectTopLeft.y)
		{
			if (point.x <= rectBottomRight.x && point.y <= rectBottomRight.y)
			{
				StringFormat SF;

				imgPoint.x = m_pBitmap->GetWidth();
				imgPoint.y = m_pBitmap->GetHeight();

				insidePoint.x = point.x - rectTopLeft.x;
				insidePoint.y = point.y - rectTopLeft.y;

				RealPoint.x = abs(imgPoint.x * insidePoint.x / rectBottomRight.x);
				RealPoint.y = abs(imgPoint.y * insidePoint.y / rectBottomRight.y);

				Graphics textG(m_pBitmap);
				textG.SetTextRenderingHint(TextRenderingHintAntiAlias);
				Gdiplus::Font F(L"Palatino Linotype Bold", 15, FontStyleBold, UnitPixel);
				RectF R(10, 10, 150, 20);

				SF.SetAlignment(StringAlignmentNear);
				SF.SetLineAlignment(StringAlignmentNear);

				SolidBrush B(Color(0, 0, 0));
				m_pBitmap->GetPixel(RealPoint.x, RealPoint.y, &color);
				textToDraw.Format(_T("%d, %d : %d"), RealPoint.x, RealPoint.y, color.GetR());
				textG.DrawString(textToDraw, -1, &F, R, &SF, &B);
			}
		}
	}
	else
		return;
}

// Mat을 Bitmap* 형식으로
Bitmap*	CMyImageView::returnBitmap()
{
	if (m_pBitmap != NULL)
	{
		return m_pBitmap;
	}
	else
		return NULL;
}


BEGIN_MESSAGE_MAP(CMyImageView, CWnd)
END_MESSAGE_MAP()



// CMyImageView 메시지 처리기입니다.


