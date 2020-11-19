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
	int				m_rawWidth;		// original Mat width
	int				m_rawHeight;	// original Mat Height

public:
	BOOL			m_Islarger;		// 이미지 확대여부
	BOOL			m_IsMove;		// 이미지 드래그 여부
	BOOL			m_IsCursorLarger;// 커서 가리키는 부분 확대 여부
	BOOL			m_IsCursorBin;	// 커서 가리키는 부분 확대후 이진화 여부
	BOOL			m_IsOverlay;	// 이미지 뷰어 기능 중 overlay 기능들 사용할지
	cv::Mat			m_OriMat;		// 원본 이미지 담는 Mat
	cv::Mat			m_DrawMat;		// 이미지 뷰어용 Mat
	BITMAPINFO*		m_pBitmapInfo;	// picture control draw용 bitmapinfo
	cv::Point		m_largerTopLeft;// 확대시 왼쪽상단 좌표 (CreateDIBitmap용 변환된 좌표)
	cv::Point		m_RealLargeTopLeft; // 확대시 왼쪽상단 좌표 (실제)
	CPoint			m_prevMouse; // 마우스 포인터 이동을 판단할 좌표값
	int				m_showWidth; // 최종적으로 Out되는 이미지의 Size
	int				m_showHeight;

public:
	void			pByteToMat(BYTE* imgbits, int width, int height);							// m_pOriMat 생성 (Image BYTE -> cv::Mat m_pOriMat)
	cv::Point		cursorPtToImage(CPoint point, CPoint rectTopLeft, CPoint rectBottomRight);	// 클라이언트 마우스 좌표 -> 이미지 실제좌표 환산기
	void			cursorLarger(CPoint mpoint, CPoint rectTopLeft, CPoint rectBottomRight);	// 커서 가리키는 부분 확대 기능
	void			largerTopLeftMover(CPoint mpoint);											// 드래그시 확대할 부분 왼쪽 상단 좌표 변경
	void			largerScreen(cv::Point pt);													// 확대할 시 CreateDIBitmap 사용 가능하도록 좌표 변환
	void			cvCursorRGB(CPoint point, cv::Point textPoint, CPoint rectTopLeft, CPoint rectBottomRight); // cursor부분 Gray LV value 출력
	void			createBitmapInfo(cv::Mat mat);												// CreateDIBitmap용 bitmapinfo 생성
	void			ImageViewerReset();															// BOOL값들 전부 FALSE SET (m_IsOverlay 제외)

protected:
	DECLARE_MESSAGE_MAP()
};


