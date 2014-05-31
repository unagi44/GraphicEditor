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

	// �� �׸��⿡ �ʿ��� ������
	CRect E_Insert ;
	int E_Current ;
	char E_IsDraw ;
	char E_CanMove ;

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
};

#ifndef _DEBUG  // GraphicEditorView.cpp�� ����� ����
inline CGraphicEditorDoc* CGraphicEditorView::GetDocument() const
   { return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument); }
#endif

