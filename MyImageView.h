#pragma once
#include "stdafx.h"



// CMyImageView

class CMyImageView : public CWnd
{
	DECLARE_DYNAMIC(CMyImageView)

public:
	CMyImageView();
	virtual ~CMyImageView();

private:
	CRect			m_DispRect;
	INT				m_DispID;
	int				m_rawWidth;
	int				m_rawHeight;

public:
	BOOL			m_Islarger;
	BOOL			m_IsMove;
	cv::Mat			m_OriMat; // OpenCV Mat
	cv::Mat			m_DrawMat;
	BITMAPINFO*		m_pBitmapInfo;
	cv::Point		m_largerTopLeft;
	int				m_showWidth; // 최종적으로 Out되는 이미지의 Size
	int				m_showHeight;

public:
	void			largerScreen(cv::Point pt);
	void			pByteToMat(BYTE* imgbits, int width, int height); // m_pMat 생성 후 변환
	void			cvCursorRGB(CPoint point, cv::Point textPoint, CPoint rectTopLeft, CPoint rectBottomRight);
	void			createBitmapInfo(cv::Mat mat);
	
// GDIPlus 관련 : 사용 금지 20201113 장한결
private:
	Bitmap*			m_pBitmap; // 원본 이미지를 clone할 Bitmap* 주소
	void			MatToBitmap(); // Mat의 내용을 Gdiplus::Bitmap으로 변환 (m_pBitmap에 주소)
	void			cloneBitmap(Bitmap* oriBitmap);
	void			cursorRGB(CPoint point, CPoint rectTopLeft, CPoint rectBottomRight);	// 영상 RGB값과 마우스 포인터 좌표 표시
////////////////////////////////////////////

protected:
	DECLARE_MESSAGE_MAP()
};


