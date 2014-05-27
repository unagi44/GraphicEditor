//**************************************************************************************************************
// public of Passion Designers
// GraphicEditor program
// 2010253009 �̰迬
// 2010253026 ������
//**************************************************************************************************************
// GraphicEditor_By_PassionDesignersView.h : CGraphicEditor_By_PassionDesignersView Ŭ������ �������̽�
//

#pragma once


class CGraphicEditor_By_PassionDesignersView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CGraphicEditor_By_PassionDesignersView();
	DECLARE_DYNCREATE(CGraphicEditor_By_PassionDesignersView)

// Ư���Դϴ�.
public:
	CGraphicEditor_By_PassionDesignersDoc* GetDocument() const;

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
	virtual ~CGraphicEditor_By_PassionDesignersView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // GraphicEditor_By_PassionDesignersView.cpp�� ����� ����
inline CGraphicEditor_By_PassionDesignersDoc* CGraphicEditor_By_PassionDesignersView::GetDocument() const
   { return reinterpret_cast<CGraphicEditor_By_PassionDesignersDoc*>(m_pDocument); }
#endif

