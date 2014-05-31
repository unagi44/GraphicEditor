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
// 작업입니다.
public:
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
