#pragma once
#include "stdafx.h"



// CMyImageView

class CMyImageView : public CWnd
{
	DECLARE_DYNAMIC(CMyImageView)

public:
	CMyImageView();
	virtual ~CMyImageView();

public:
	Bitmap*			m_pBitmap; // 원본 이미지를 clone할 Bitmap* 주소

public:
	void			cursorRGB(CPoint point, CPoint rectTopLeft, CPoint rectBottomRight);	// 영상 RGB값과 마우스 포인터 좌표 표시
	Bitmap*			returnBitmap(); // 이미지 뷰어 작업이 완료된 이미지의 주소 반환
	void			cloneBitmap(Bitmap* oriBitmap);

protected:
	DECLARE_MESSAGE_MAP()
};


