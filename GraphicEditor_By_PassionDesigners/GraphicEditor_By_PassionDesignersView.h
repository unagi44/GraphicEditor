//**************************************************************************************************************
// public of Passion Designers
// GraphicEditor program
// 2010253009 이계연
// 2010253026 박현태
//**************************************************************************************************************
// GraphicEditor_By_PassionDesignersView.h : CGraphicEditor_By_PassionDesignersView 클래스의 인터페이스
//

#pragma once


class CGraphicEditor_By_PassionDesignersView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CGraphicEditor_By_PassionDesignersView();
	DECLARE_DYNCREATE(CGraphicEditor_By_PassionDesignersView)

// 특성입니다.
public:
	CGraphicEditor_By_PassionDesignersDoc* GetDocument() const;

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
	virtual ~CGraphicEditor_By_PassionDesignersView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // GraphicEditor_By_PassionDesignersView.cpp의 디버그 버전
inline CGraphicEditor_By_PassionDesignersDoc* CGraphicEditor_By_PassionDesignersView::GetDocument() const
   { return reinterpret_cast<CGraphicEditor_By_PassionDesignersDoc*>(m_pDocument); }
#endif

