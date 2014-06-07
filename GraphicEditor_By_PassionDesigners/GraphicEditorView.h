//**************************************************************************************************************
// public of Passion Designers
// GraphicEditor program
// 2010253009 �̰迬
// 2010253026 ������
//**************************************************************************************************************
// GraphicEditorView.h : CGraphicEditorView Ŭ������ �������̽�
//
#include "CLine.h"	// ���� �׸��� ���� ������� ����
#include "CPolyLine.h"	// PolyLine�� �׸��� ���� ������� ����
#include "CText.h"		// �ؽ�Ʈ ������ ���� ������� ����
#include "GraphicEditorDoc.h"

#pragma once


class CGraphicEditorView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CGraphicEditorView();
	DECLARE_DYNCREATE(CGraphicEditorView)

// Ư���Դϴ�.
public:
	CGraphicEditorDoc* GetDocument() const;
	CRect ChangeRect ;
	int PSkeleton ;
	char IsNormal ;
	COLORREF m_Color ;
	COLORREF m_FillColor ;
	CFont m_Font ;
	char m_IsColor ;
	char m_IsFillColor ;
	char m_IsThickness ;
	char m_Thickness ;
	char m_IsFillPattern ;
	char m_IsLinePattern ;
	char m_PSkeleton ;
	int m_FillPattern ;
	int m_LinePattern ;

	// �̵� ���ٿ� �ʿ��� ������
	CRect M_Rect ;
	CRect M_ChangeRect ;
	CPoint M_Start ;
	int M_Number ;
	int M_PMin_x ;
	int M_PMax_x ;
	int M_PMin_y ;
	int M_PMax_y ;
	CString M_What ;
	char M_IsMove ;
	char M_IsSelect ;
	char M_IsDraw ;
	char M_IsLineSelect ;
	char M_ChangeLineOnePoint ;
	char M_IsChangeLineStart ;
	char M_IsRectSelect ;
	char M_ChangeRectSize ;
	char M_IsChangeRectSide ;
	char M_IsChangeRectNW ;
	char M_IsChangeRectNE ;
	char M_IsChangeRectSW ;
	char M_IsChangeRectSE ;
	char M_IsChangeRectVerticalTop ;
	char M_IsChangeRectVerticalBottom ;
	char M_IsChangeRectWidthLeft ;
	char M_IsChangeRectWidthRight ;
	char M_IsEllipseSelect ;
	char M_ChangeEllipseSize ;
	char M_IsChangeEllipseSide ;
	char M_IsChangeEllipseNW ;
	char M_IsChangeEllipseNE ;
	char M_IsChangeEllipseSW ;
	char M_IsChangeEllipseSE ;
	char M_IsChangeEllipseVerticalTop ;
	char M_IsChangeEllipseVerticalBottom ;
	char M_IsChangeEllipseWidthLeft ;
	char M_IsChangeEllipseWidthRight ;

	// �ؽ�Ʈ ���Կ� �ʿ��� ������
	LOGFONT Text_lf ;
	LOGFONT Text_Each ;
	CPoint Text_CurPoint ;
	int Text_Current ;
	char Text_IsText ;
	char Text_IsKeyDown ;
	char Text_IsFont ;

	// �� �׸��⿡ �ʿ��� ������
	CLine L_Insert ;
	int L_Current ;
	char L_IsDraw ;
	char L_CanMove ;

	// ���� �׸��⿡ �ʿ��� ������
	CRect R_Rect ;
	int R_FillPattern ;
	int R_Current ;
	char R_IsDraw ;
	char R_CanMove ;

	// PolyLine �׸��⿡ �ʿ��� ������
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

	// �� �׸��⿡ �ʿ��� ������
	CRect E_Insert ;
	int E_Current ;
	int E_FillPattern ;
	char E_IsDraw ;
	char E_CanMove ;

	// ���� �׸��⿡ �ʿ��� ������
	CRect T_Insert ;
	int T_Current ;
	int T_FillPattern ;
	char T_IsDraw ;
	char T_CanMove ;

	// �� �ﰢ�� �׸��⿡ �ʿ��� ������
	CRect RT_Insert ;
	int RT_Current ;
	int RT_FillPattern ;
	char RT_IsDraw ;
	char RT_CanMove ;

	// ���� �ﰢ�� �׸��⿡ �ʿ��� ������
	CRect RightT_Insert ;
	int RightT_Current ;
	int RightT_FillPattern ;
	char RightT_IsDraw ;
	char RightT_CanMove ;

	// �� ���� �ﰢ�� �׸��⿡ �ʿ��� ������
	CRect RRightT_Insert ;
	int RRightT_Current ;
	int RRightT_FillPattern ;
	char RRightT_IsDraw ;
	char RRightT_CanMove ;

	// ������ -> ���� �ﰢ�� �׸��⿡ �ʿ��� ������
	CRect RTLT_Insert ;
	int RTLT_Current ;
	int RTLT_FillPattern ;
	char RTLT_IsDraw ;
	char RTLT_CanMove ;

	// ���� -> ������ �ﰢ�� �׸��⿡ �ʿ��� ������
	CRect LTRT_Insert ;
	int LTRT_Current ;
	int LTRT_FillPattern ;
	char LTRT_IsDraw ;
	char LTRT_CanMove ;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CGraphicEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnFillpattern();
	afx_msg void OnLinepattern();
};

#ifndef _DEBUG  // GraphicEditorView.cpp�� ����� ����
inline CGraphicEditorDoc* CGraphicEditorView::GetDocument() const
   { return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument); }
#endif

