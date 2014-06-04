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
	char IsNormal ;
	COLORREF m_Color ;
	COLORREF m_FillColor ;
	CFont m_Font ;
	char m_IsColor ;
	char m_IsFillColor ;
	char m_IsThickness ;
	char m_Thickness ;


	// �̵� ���ٿ� �ʿ��� ������
	CRect M_Rect ;
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

	// �ؽ�Ʈ ���Կ� �ʿ��� ������
	LOGFONT Text_lf ;
	CRect Text_Rect ;
	char Text_IsText ;
	char Text_IsFont ;
	char Text_IsContinue ;

	// �� �׸��⿡ �ʿ��� ������
	CLine L_Insert ;
	int L_Current ;
	char L_IsDraw ;
	char L_CanMove ;

	// ���� �׸��⿡ �ʿ��� ������
	CRect R_Rect ;
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
	char E_IsDraw ;
	char E_CanMove ;

	// ���� �׸��⿡ �ʿ��� ������
	CRect T_Insert ;
	int T_Current ;
	char T_IsDraw ;
	char T_CanMove ;

	// �� �ﰢ�� �׸��⿡ �ʿ��� ������
	CRect RT_Insert ;
	int RT_Current ;
	char RT_IsDraw ;
	char RT_CanMove ;

	// ���� �ﰢ�� �׸��⿡ �ʿ��� ������
	CRect RightT_Insert ;
	int RightT_Current ;
	char RightT_IsDraw ;
	char RightT_CanMove ;

	// �� ���� �ﰢ�� �׸��⿡ �ʿ��� ������
	CRect RRightT_Insert ;
	int RRightT_Current ;
	char RRightT_IsDraw ;
	char RRightT_CanMove ;

	// ������ -> ���� �ﰢ�� �׸��⿡ �ʿ��� ������
	CRect RTLT_Insert ;
	int RTLT_Current ;
	char RTLT_IsDraw ;
	char RTLT_CanMove ;

	// ���� -> ������ �ﰢ�� �׸��⿡ �ʿ��� ������
	CRect LTRT_Insert ;
	int LTRT_Current ;
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
};

#ifndef _DEBUG  // GraphicEditorView.cpp�� ����� ����
inline CGraphicEditorDoc* CGraphicEditorView::GetDocument() const
   { return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument); }
#endif

