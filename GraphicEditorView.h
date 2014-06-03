//**************************************************************************************************************
// public of Passion Designers
// GraphicEditor program
// 2010253009 이계연
// 2010253026 박현태
//**************************************************************************************************************
// GraphicEditorView.h : CGraphicEditorView 클래스의 인터페이스
//
#include "CLine.h"	// 선을 그리기 위한 헤더파일 참조
#include "CPolyLine.h"	// PolyLine을 그리기 위한 헤더파일 참조
#include "CText.h"		// 텍스트 삽입을 위한 헤더파일 참조

#pragma once


class CGraphicEditorView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CGraphicEditorView();
	DECLARE_DYNCREATE(CGraphicEditorView)

// 특성입니다.
public:
	CGraphicEditorDoc* GetDocument() const;
	CRect ChangeRect ;
	char IsNormal ;
	COLORREF m_Color ;
	COLORREF m_FillColor ;
	CFont m_Font ;
	char m_IsColor ;
	char m_IsFillColor ;
	char m_IsThickness ;
	char m_Thickness ;


	// 이동 툴바에 필요한 변수들
	CRect M_Rect ;
	CPoint M_Start ;
	int M_Number ;
	CString M_What ;
	char M_IsMove ;
	char M_IsSelect ;
	char M_IsDraw ;

	// 텍스트 삽입에 필요한 변수들
	LOGFONT Text_lf ;
	CRect Text_Rect ;
	char Text_IsText ;
	char Text_IsFont ;
	char Text_IsContinue ;

	// 선 그리기에 필요한 변수들
	CLine L_Insert ;
	int L_Current ;
	char L_IsDraw ;
	char L_CanMove ;

	// 상자 그리기에 필요한 변수들
	CRect R_Rect ;
	int R_Current ;
	char R_IsDraw ;
	char R_CanMove ;

	// PolyLine 그리기에 필요한 변수들
	CPolyLine P_Insert ;
	CPoint P_PointStart ;
	CPoint P_PointLast ;
	int P_ChangeSkeleton ;
	int P_Current ;
	int P_CurrentPoint ;
	char P_IsDraw ;
	char P_CanMove ;
	char P_DrawContinue ;
	char P_IsContinue ;
	char P_IsStart ;
	char P_IsMove ;
	char P_IsSkeletonStart ;

	// 원 그리기에 필요한 변수들
	CRect E_Insert ;
	int E_Current ;
	char E_IsDraw ;
	char E_CanMove ;

	// 세모 그리기에 필요한 변수들
	CRect T_Insert ;
	int T_Current ;
	char T_IsDraw ;
	char T_CanMove ;

	// 역 삼각형 그리기에 필요한 변수들
	CRect RT_Insert ;
	int RT_Current ;
	char RT_IsDraw ;
	char RT_CanMove ;

	// 직각 삼각형 그리기에 필요한 변수들
	CRect RightT_Insert ;
	int RightT_Current ;
	char RightT_IsDraw ;
	char RightT_CanMove ;

	// 역 직각 삼각형 그리기에 필요한 변수들
	CRect RRightT_Insert ;
	int RRightT_Current ;
	char RRightT_IsDraw ;
	char RRightT_CanMove ;

	// 오른쪽 -> 왼쪽 삼각형 그리기에 필요한 변수들
	CRect RTLT_Insert ;
	int RTLT_Current ;
	char RTLT_IsDraw ;
	char RTLT_CanMove ;

	// 왼쪽 -> 오른쪽 삼각형 그리기에 필요한 변수들
	CRect LTRT_Insert ;
	int LTRT_Current ;
	char LTRT_IsDraw ;
	char LTRT_CanMove ;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGraphicEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDrawline();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnDrawrec();
	afx_msg void OnDrawpoly();
	afx_msg void OnDrawellipse();
	afx_msg void OnSelectobject();
	afx_msg void OnChangecolor();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnChangefillcolor();
	afx_msg void OnNofillcolor();
	afx_msg void OnDrawtriangle();
	afx_msg void OnDrawreversetri();
	afx_msg void OnThickness();
	afx_msg void OnRightangledtri();
//	afx_msg void OnRrightangledtri();
	afx_msg void OnRRrightangledtri();
	afx_msg void OnRighttolefttri();
	afx_msg void OnLefttorighttri();
	afx_msg void OnFont();
//	afx_msg void OnUpdateFont(CCmdUI *pCmdUI);
	afx_msg void OnText();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // GraphicEditorView.cpp의 디버그 버전
inline CGraphicEditorDoc* CGraphicEditorView::GetDocument() const
   { return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument); }
#endif

