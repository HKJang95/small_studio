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
	Graphics*		m_pGraphics;
	Bitmap*			m_pBitmap; // 원본 이미지를 clone할 Bitmap* 주소
	CRect			m_rcDisp;

public:
	Bitmap*			pointerRGB();	// RGB값과 마우스 포인터 좌표가 표시된 이미지의 포인터를 반환

protected:
	DECLARE_MESSAGE_MAP()
};


