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
	Graphics*		m_pGraphics[MAXCAM];
	Bitmap*			m_pBitmap[MAXCAM];
	CRect			m_rcDisp[MAXCAM];

protected:
	DECLARE_MESSAGE_MAP()
};


