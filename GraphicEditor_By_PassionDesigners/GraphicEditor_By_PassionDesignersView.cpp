//**************************************************************************************************************
// public of Passion Designers
// GraphicEditor program
// 2010253009 �̰迬
//**************************************************************************************************************
// GraphicEditor_By_PassionDesignersView.cpp : CGraphicEditor_By_PassionDesignersView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "GraphicEditor_By_PassionDesigners.h"
#endif

#include "GraphicEditor_By_PassionDesignersDoc.h"
#include "GraphicEditor_By_PassionDesignersView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicEditor_By_PassionDesignersView

IMPLEMENT_DYNCREATE(CGraphicEditor_By_PassionDesignersView, CScrollView)

BEGIN_MESSAGE_MAP(CGraphicEditor_By_PassionDesignersView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicEditor_By_PassionDesignersView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGraphicEditor_By_PassionDesignersView ����/�Ҹ�

CGraphicEditor_By_PassionDesignersView::CGraphicEditor_By_PassionDesignersView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CGraphicEditor_By_PassionDesignersView::~CGraphicEditor_By_PassionDesignersView()
{
}

BOOL CGraphicEditor_By_PassionDesignersView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CGraphicEditor_By_PassionDesignersView �׸���

void CGraphicEditor_By_PassionDesignersView::OnDraw(CDC* /*pDC*/)
{
	CGraphicEditor_By_PassionDesignersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}

void CGraphicEditor_By_PassionDesignersView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �� ���� ��ü ũ�⸦ ����մϴ�.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CGraphicEditor_By_PassionDesignersView �μ�


void CGraphicEditor_By_PassionDesignersView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphicEditor_By_PassionDesignersView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CGraphicEditor_By_PassionDesignersView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CGraphicEditor_By_PassionDesignersView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CGraphicEditor_By_PassionDesignersView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphicEditor_By_PassionDesignersView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGraphicEditor_By_PassionDesignersView ����

#ifdef _DEBUG
void CGraphicEditor_By_PassionDesignersView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphicEditor_By_PassionDesignersView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGraphicEditor_By_PassionDesignersDoc* CGraphicEditor_By_PassionDesignersView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditor_By_PassionDesignersDoc)));
	return (CGraphicEditor_By_PassionDesignersDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicEditor_By_PassionDesignersView �޽��� ó����
