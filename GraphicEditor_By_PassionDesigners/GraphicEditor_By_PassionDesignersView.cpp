//**************************************************************************************************************
// public of Passion Designers
// GraphicEditor program
// 2010253009 이계연
//**************************************************************************************************************
// GraphicEditor_By_PassionDesignersView.cpp : CGraphicEditor_By_PassionDesignersView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicEditor_By_PassionDesignersView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGraphicEditor_By_PassionDesignersView 생성/소멸

CGraphicEditor_By_PassionDesignersView::CGraphicEditor_By_PassionDesignersView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGraphicEditor_By_PassionDesignersView::~CGraphicEditor_By_PassionDesignersView()
{
}

BOOL CGraphicEditor_By_PassionDesignersView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CGraphicEditor_By_PassionDesignersView 그리기

void CGraphicEditor_By_PassionDesignersView::OnDraw(CDC* /*pDC*/)
{
	CGraphicEditor_By_PassionDesignersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CGraphicEditor_By_PassionDesignersView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CGraphicEditor_By_PassionDesignersView 인쇄


void CGraphicEditor_By_PassionDesignersView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphicEditor_By_PassionDesignersView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGraphicEditor_By_PassionDesignersView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGraphicEditor_By_PassionDesignersView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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


// CGraphicEditor_By_PassionDesignersView 진단

#ifdef _DEBUG
void CGraphicEditor_By_PassionDesignersView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphicEditor_By_PassionDesignersView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGraphicEditor_By_PassionDesignersDoc* CGraphicEditor_By_PassionDesignersView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditor_By_PassionDesignersDoc)));
	return (CGraphicEditor_By_PassionDesignersDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicEditor_By_PassionDesignersView 메시지 처리기
