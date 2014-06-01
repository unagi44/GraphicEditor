//**************************************************************************************************************
// public of Passion Designers
// GraphicEditor program
// 2010253009 이계연
// 2010253026 박현태
//**************************************************************************************************************
// GraphicEditorDoc.h : CGraphicEditorDoc 클래스의 인터페이스
//
#include "CLine.h"	// 선을 그리기 위한 헤더파일 참조
#include "CPolyLine.h"	// PolyLine을 그리기 위한 헤더파일 참조

#pragma once

class CGraphicEditorDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CGraphicEditorDoc();
	DECLARE_DYNCREATE(CGraphicEditorDoc)

// 특성입니다.
public:
	CArray < CLine, CLine& > L_Line ;	// 선 그리기 배열
	CArray < CRect, CRect& > R_Rec ;	// 상자 그리기 배열
	CArray < CPolyLine, CPolyLine& > P_Poly ;	// PolyLine 그리기 배열
	int CPolyCount ;
	CArray < CRect, CRect& > E_Ellipse ;		// 원 그리기 배열
	CArray < CRect, CRect& > T_Triangle ;		// 세모 그리기 배열
	CArray < CRect, CRect& > RT_Triangle ;		// 역 삼각형 그리기 배열
	CArray < CRect, CRect& > RightT_Triangle ;	// 직각 삼각형 그리기 배열
	CArray < CRect, CRect& > RRightT_Triangle ;	// 역 직각 삼각형 그리기 배열
// 작업입니다.
public:
	CArray < int, int > R_Color ;		// 상자 선 색
	CArray < int, int > R_FillColor ;	// 상자 채우기 색
	CArray < int, int > E_Color ;		// 원 선 색
	CArray < int, int > E_FillColor ;	// 원 채우기 색
	CArray < int, int > T_Color ;		// 세모 선 색
	CArray < int, int > T_FillColor ;	// 세모 채우기 색
	CArray < int, int > RT_Color ;		// 역 삼각형 선 색
	CArray < int, int > RT_FillColor ;	// 역 삼각형 채우기 색
	CArray < int, int > RightT_Color ;	// 직각 삼각형 선 색
	CArray < int, int > RightT_FillColor ;	// 직각 삼각형 채우기 색
	CArray < int, int > RRightT_Color ;		// 역 직각 삼각형 선 색
	CArray < int, int > RRightT_FillColor ;	// 역 직각 삼각형 채우기 색
	CArray < int, int > R_Thickness ;			// 상자의 선 두께
	CArray < int, int > E_Thickness ;			// 원의 선 두께
	CArray < int, int > T_Thickness ;			// 세모의 선 두께
	CArray < int, int > RT_Thickness ;			// 역 삼각형의 선 두께
	CArray < int, int > RightT_Thickness ;		// 직각 삼각형의 선 두께
	CArray < int, int > RRightT_Thickness ;		// 역 직각 삼각형의 선 두께
// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CGraphicEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
