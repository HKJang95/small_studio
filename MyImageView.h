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
	BOOL			m_IsCursorLarger;
	BOOL			m_IsCursorBin;
	BOOL			m_IsOverlay;
	cv::Mat			m_OriMat; // OpenCV Mat
	cv::Mat			m_DrawMat;
	BITMAPINFO*		m_pBitmapInfo;
	cv::Point		m_largerTopLeft;
	cv::Point		m_RealLargeTopLeft;
	CPoint			m_prevMouse; // 마우스 포인터 이동을 판단할 좌표값
	int				m_showWidth; // 최종적으로 Out되는 이미지의 Size
	int				m_showHeight;

public:
	cv::Point		cursorPtToImage(CPoint point, CPoint rectTopLeft, CPoint rectBottomRight);
	void			cursorLarger(CPoint mpoint, CPoint rectTopLeft, CPoint rectBottomRight);
	void			largerTopLeftMover(CPoint mpoint);
	void			largerScreen(cv::Point pt);
	void			pByteToMat(BYTE* imgbits, int width, int height); // m_pMat 생성 후 변환
	void			cvCursorRGB(CPoint point, cv::Point textPoint, CPoint rectTopLeft, CPoint rectBottomRight);
	void			createBitmapInfo(cv::Mat mat);
	void			ImageViewerReset();

protected:
	DECLARE_MESSAGE_MAP()
};


