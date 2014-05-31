//**************************************************************************************************************
// public of Passion Designers
// GraphicEditor program
// 2010253009 이계연
// 2010253026 박현태
//**************************************************************************************************************
// GraphicEditorView.cpp : CGraphicEditorView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GraphicEditor.h"
#endif

#include "GraphicEditorDoc.h"
#include "GraphicEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicEditorView

IMPLEMENT_DYNCREATE(CGraphicEditorView, CScrollView)

BEGIN_MESSAGE_MAP(CGraphicEditorView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DrawLine, &CGraphicEditorView::OnDrawline)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_DrawRec, &CGraphicEditorView::OnDrawrec)
	ON_COMMAND(ID_DrawPoly, &CGraphicEditorView::OnDrawpoly)
	ON_COMMAND(ID_DrawEllipse, &CGraphicEditorView::OnDrawellipse)
	ON_COMMAND(ID_SelectObject, &CGraphicEditorView::OnSelectobject)
	ON_COMMAND(ID_ChangeColor, &CGraphicEditorView::OnChangecolor)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_ChangeFillColor, &CGraphicEditorView::OnChangefillcolor)
END_MESSAGE_MAP()

// CGraphicEditorView 생성/소멸

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

	IsNormal = 'o' ;
	m_IsColor = 'x' ;
	m_IsFillColor = 'x' ;

	// 선 그리기에 필요한 변수들 초기화
	L_IsDraw = 'x' ;
	L_CanMove = 'x' ;

	// 상자 그리기에 필요한 변수들 초기화
	R_IsDraw = 'x' ;
	R_CanMove = 'x' ;

	// PolyLine 그리기에 필요한 변수들 초기화
	P_IsDraw = 'x' ;
	P_CanMove = 'x' ;
	P_DrawContinue = 'x' ;
	P_CurrentPoint = 0 ;
	P_IsContinue = 'x' ;
	P_IsStart = 'x' ;
	P_IsMove = 'x' ;
	P_ChangeSkeleton = 0 ;

	// 원 그리기에 필요한 변수들 초기화
	E_IsDraw = 'x' ;
	E_CanMove = 'x' ;
}

CGraphicEditorView::~CGraphicEditorView()
{
}

BOOL CGraphicEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CGraphicEditorView 그리기

void CGraphicEditorView::OnDraw(CDC* pDC)
{
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// 그린 선을 모두 화면에 띄웁니다.
	for ( int i = 0 ; i < pDoc -> L_Line.GetCount () ; i++ ) {
		// 색상을 가지지 않을 경우의 출력
		if ( pDoc -> L_Line.GetAt (i).L_Color == RGB (0,0,0) ) {
			CPen pen ( PS_SOLID, 1, RGB (0, 0, 0) ) ;
			CPen *Draw_Pen = pDC -> SelectObject(&pen);
			L_Insert.Start = pDoc -> L_Line.GetAt (i).Start ;
			L_Insert.Last = pDoc -> L_Line.GetAt (i).Last ;
			pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
			pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
			pDC->SelectObject(Draw_Pen);
		}
		// 특정 색상을 가졌을 경우의 출력
		else {
			CPen pen ( PS_SOLID, 1, pDoc -> L_Line.GetAt (i).L_Color ) ;
			CPen *Draw_Pen = pDC -> SelectObject(&pen);
			L_Insert.Start = pDoc -> L_Line.GetAt (i).Start ;
			L_Insert.Last = pDoc -> L_Line.GetAt (i).Last ;
			pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
			pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
			pDC->SelectObject(Draw_Pen);
		}
	}

	// 그린 상자를 모두 화면에 띄웁니다.
	for ( int i = 0 ; i < pDoc -> R_Rec.GetCount () ; i++ ) {
		// 선 색을 가지지 않았을 경우의 출력
		if ( pDoc -> R_Color.GetAt (i) == RGB (0,0,0) ) {

			// 채우기 색상을 가지지 않았을 경우의 출력
			if ( pDoc -> R_FillColor.GetAt (i) == RGB (0,0,0) ) {
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( pDoc -> R_Rec [i].left, pDoc -> R_Rec [i].top, pDoc -> R_Rec [i].right, pDoc -> R_Rec [i].bottom ) ;
			}
			// 채우기 색상을 가졌을 경우의 출력
			else {
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;
				pDC -> Rectangle ( pDoc -> R_Rec [i].left, pDoc -> R_Rec [i].top, pDoc -> R_Rec [i].right, pDoc -> R_Rec [i].bottom ) ;
				pDC -> SelectObject ( oldBrush ) ;
			}
		}
		// 특정 선 색상을 가졌을 경우의 출력
		else {
			
			// 채우기 색상을 가지지 않았을 경우의 출력
			if ( pDoc -> R_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen;
				pen.CreatePen( PS_SOLID, 1, pDoc ->R_Color.GetAt (i) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( pDoc -> R_Rec [i].left, pDoc -> R_Rec [i].top, pDoc -> R_Rec [i].right, pDoc -> R_Rec [i].bottom ) ;
				pDC ->SelectObject ( oldPen ) ;
			}
			// 채우기 색상을 가졌을 경우의 출력
			else {
				CPen pen;
				pen.CreatePen( PS_SOLID, 1, pDoc ->R_Color.GetAt (i) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;
				pDC -> Rectangle ( pDoc -> R_Rec [i].left, pDoc -> R_Rec [i].top, pDoc -> R_Rec [i].right, pDoc -> R_Rec [i].bottom ) ;
				pDC -> SelectObject ( oldPen ) ;
				pDC -> SelectObject ( oldBrush ) ;
			}
		}
	}
	
	// 그린 PolyLine을 모두 화면에 띄웁니다.
	for ( int i = 0 ; i < pDoc -> P_Poly.GetCount () ; i++ ) {
		for ( int j = 0 ; j < pDoc -> P_Poly.GetAt (i).Poly_point.GetCount () - 1 ; j++ ) {

			// PolyLine이 색상을 가지지 않을 경우의 출력
			if ( pDoc -> P_Poly.GetAt (i).P_Color == RGB (0,0,0) ) {
				CPen pen ( PS_SOLID, 1, RGB (0, 0, 0) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				P_PointStart = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j) ;
				P_PointLast = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j+1) ;
				pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
				pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
				pDC->SelectObject(Draw_Pen);
			}
			// PolyLine이 지정된 색상을 가졌을 경우의 출력
			else {
				CPen pen ( PS_SOLID, 1, pDoc -> P_Poly.GetAt (i).P_Color );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				P_PointStart = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j) ;
				P_PointLast = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j+1) ;
				pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
				pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
				pDC->SelectObject(Draw_Pen);
			}

			// 현재 그리고 있는 PolyLine의 Skeleton을 보여줍니다.
			if ( i == pDoc -> P_Poly.GetCount () - 1 && P_IsDraw == 'o' && P_Insert.Poly_point.GetCount () != 0 && P_CanMove == 'o' ) {
				ChangeRect.left = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j).x - 3 ;
				ChangeRect.right = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j).x + 3 ;
				ChangeRect.top = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j).y - 3 ;
				ChangeRect.bottom = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j).y + 3 ;

				pDC -> Rectangle ( ChangeRect ) ;

				ChangeRect.left = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j+1).x - 3 ;
				ChangeRect.right = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j+1).x + 3 ;
				ChangeRect.top = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j+1).y - 3 ;
				ChangeRect.bottom = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j+1).y + 3 ;

				pDC -> Rectangle ( ChangeRect ) ;
			}
		}
	}

	// 그린 원을 모두 화면에 띄웁니다.
	for ( int i = 0 ; i < pDoc -> E_Ellipse.GetCount () ; i++ ) {

		// 선 색을 가지지 않았을 경우의 출력
		if ( pDoc -> E_Color.GetAt (i) == RGB (0,0,0) ) {
			// 채우기 색상을 가지지 않았을 경우의 출력
			if ( pDoc -> E_FillColor.GetAt (i) == RGB (0,0,0) ) {
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Ellipse ( pDoc -> E_Ellipse [i].left, pDoc -> E_Ellipse [i].top, pDoc -> E_Ellipse [i].right, pDoc -> E_Ellipse [i].bottom ) ;
			}
			// 채우기 색상을 가졌을 경우의 출력
			else {
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;
				pDC -> Ellipse ( pDoc -> E_Ellipse [i].left, pDoc -> E_Ellipse [i].top, pDoc -> E_Ellipse [i].right, pDoc -> E_Ellipse [i].bottom ) ;
				pDC -> SelectObject ( oldBrush ) ;
			}
		}
		// 특정 선 색상을 가졌을 경우의 출력
		else {
			// 채우기 색상을 가지지 않았을 경우의 출력
			if ( pDoc -> E_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen;
				pen.CreatePen( PS_SOLID, 1, pDoc ->E_Color.GetAt (i) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				pDC -> Ellipse ( pDoc -> E_Ellipse [i].left, pDoc -> E_Ellipse [i].top, pDoc -> E_Ellipse [i].right, pDoc -> E_Ellipse [i].bottom ) ;
				pDC -> SelectObject ( oldPen ) ;
			}
			// 채우기 색상을 가졌을 경우의 출력
			else {
				CPen pen;
				pen.CreatePen( PS_SOLID, 1, pDoc ->E_Color.GetAt (i) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;
				pDC -> Ellipse ( pDoc -> E_Ellipse [i].left, pDoc -> E_Ellipse [i].top, pDoc -> E_Ellipse [i].right, pDoc -> E_Ellipse [i].bottom ) ;
				pDC -> SelectObject ( oldPen ) ;
				pDC -> SelectObject ( oldBrush ) ;
			}
		}

		// 만약 원을 그리고 있는 상태라면 테두리 직사각형을 그려줍니다.
		if ( pDoc -> E_Ellipse.GetCount () - 1 == i && E_CanMove == 'o' ) {
			CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
			CPen *Draw_Pen = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> E_Ellipse.GetAt (i).left  ;
			P_PointStart.y = pDoc -> E_Ellipse.GetAt (i).top  ;
			P_PointLast.x = pDoc -> E_Ellipse.GetAt (i).right ;
			P_PointLast.y = pDoc -> E_Ellipse.GetAt (i).top ;
			pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
			pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
			pDC->SelectObject(Draw_Pen);

			CPen pen2 ( PS_DOT, 1.8, RGB (100, 100, 255) );
			CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> E_Ellipse.GetAt (i).left  ;
			P_PointStart.y = pDoc -> E_Ellipse.GetAt (i).top  ;
			P_PointLast.x = pDoc -> E_Ellipse.GetAt (i).left ;
			P_PointLast.y = pDoc -> E_Ellipse.GetAt (i).bottom ;
			pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
			pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
			pDC->SelectObject(Draw_Pen2);

			CPen pen3 ( PS_DOT, 1.8, RGB (100, 100, 255) );
			CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> E_Ellipse.GetAt (i).left  ;
			P_PointStart.y = pDoc -> E_Ellipse.GetAt (i).bottom  ;
			P_PointLast.x = pDoc -> E_Ellipse.GetAt (i).right ;
			P_PointLast.y = pDoc -> E_Ellipse.GetAt (i).bottom ;
			pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
			pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
			pDC->SelectObject(Draw_Pen3);

			CPen pen4 ( PS_DOT, 1.8, RGB (100, 100, 255) );
			CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> E_Ellipse.GetAt (i).right  ;
			P_PointStart.y = pDoc -> E_Ellipse.GetAt (i).top  ;
			P_PointLast.x = pDoc -> E_Ellipse.GetAt (i).right ;
			P_PointLast.y = pDoc -> E_Ellipse.GetAt (i).bottom ;
			pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
			pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
			pDC->SelectObject(Draw_Pen4);
		}
	}

}

void CGraphicEditorView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CGraphicEditorView 인쇄

BOOL CGraphicEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGraphicEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGraphicEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGraphicEditorView 진단

#ifdef _DEBUG
void CGraphicEditorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphicEditorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGraphicEditorDoc* CGraphicEditorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditorDoc)));
	return (CGraphicEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicEditorView 메시지 처리기

void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 선을 그리는 경우
	if ( L_IsDraw == 'o' ) {
		L_Insert.Start = L_Insert.Last = point ;
		pDoc->L_Line.Add ( L_Insert ) ;
		L_Current = pDoc -> L_Line.GetCount () - 1 ;
		L_CanMove = 'o' ;
	}
	// 상자를 그리는 경우
	else if ( R_IsDraw == 'o' ) {
		R_Rect.left = point.x ;
		R_Rect.right = point.x ;
		R_Rect.top = point.y ;
		R_Rect.bottom = point.y ;

		pDoc -> R_Rec.Add ( R_Rect ) ;
		R_Current = pDoc -> R_Rec.GetCount () - 1 ;
		R_CanMove = 'o' ;

		if ( m_IsColor == 'o' )
			pDoc -> R_Color.Add ( m_Color ) ;
		else if ( m_IsColor == 'x' )
			pDoc -> R_Color.Add ( RGB(0,0,0) ) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> R_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> R_FillColor.Add ( RGB(0,0,0) ) ;
	}
	// PolyLine을 계속해서 그리는 경우
	else if ( P_IsContinue == 'o') {
		// PolyLine의 Skeleton이 2개일 경우
		if ( P_CurrentPoint == 1 ) {
			// 원점과 마지막점에서 변경하려는 경우엔 계속 그릴수 있게 한다.
			if ( ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 8 &&
				P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 8 &&
				P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 8 &&
				P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 8) ||
				(P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 8 &&
				P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 8 &&
				P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 8 &&
				P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 8) ) ) {

					if ( (P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 8 &&
						  P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 8 &&
						  P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 8 &&
						  P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 8) )
						P_IsStart = 'o' ;
					else
						P_CurrentPoint++ ;

					P_CanMove = 'o' ;
			}
		}
		// PolyLine의 Skeleton이 3개 이상인 경우
		else {
			// 원점, 마지막 Skeleton을 제외한 모든 Skeleton을 검사하여
			// 클릭한 좌표가 해당 Skeleton 중에 있는지 확인한다.
			char P_Flag = 'x' ;
			for ( int i = 1 ; i <= P_CurrentPoint - 1 ; i++ ) {
				if ( P_Insert.Poly_point.GetAt (i).x <= point.x + 8 &&
					 P_Insert.Poly_point.GetAt (i).x >= point.x - 8 &&
					 P_Insert.Poly_point.GetAt (i).y <= point.y + 8 &&
					 P_Insert.Poly_point.GetAt (i).y >= point.y - 8 ) {
					P_ChangeSkeleton = i ;
					P_CanMove = 'o' ;
					P_Flag = 'o' ;
				}
			}

			if ( P_Flag == 'x' ) {
				// 원점 Skeleton을 건드리면 시작 점을 변경한다.
				if ( (P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 8 &&
					P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 8 &&
					P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 8 &&
					P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 8) ) {
						P_IsStart = 'o' ;
						P_CanMove = 'o' ;
				}
				// 마지막 Skeleton을 건드리면 그 Skeleton을 변경한다.
				else if ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 8 &&
					P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 8 &&
					P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 8 &&
					P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 8) ) {
						P_CanMove = 'o' ;
						P_CurrentPoint++ ;
				}
			}
		}
	}
	// PolyLine 그리기 시, 맨 처음 Skeleton을 클릭하여 만들 경우입니다.
	else if ( P_IsDraw == 'o' && P_IsContinue == 'x' ) {
		P_Insert.Poly_point.Add ( point ) ;
		P_Current = pDoc -> P_Poly.GetCount () ;
		pDoc -> P_Poly.SetSize (P_Current + 1) ;
		pDoc -> P_Poly.GetAt (P_Current).Poly_point.Add ( point ) ;
		P_CurrentPoint = P_Insert.Poly_point.GetCount () ;
		P_CanMove = 'o' ;
		P_IsContinue = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> P_Poly.GetAt ( P_Current ).P_Color = m_Color ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> P_Poly.GetAt ( P_Current ).P_Color = RGB (0,0,0) ;
	}
	// 원을 그리는 경우
	else if ( E_IsDraw == 'o' ) {
		E_Insert.left = point.x ;
		E_Insert.right = point.x ;
		E_Insert.top = point.y ;
		E_Insert.bottom = point.y ;

		pDoc -> E_Ellipse.Add ( R_Rect ) ;
		R_Current = pDoc -> E_Ellipse.GetCount () - 1 ;
		E_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> E_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> E_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> E_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> E_FillColor.Add ( RGB(0,0,0) ) ;
	}

	CScrollView::OnLButtonDown(nFlags, point);
}


void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 선 그리기 선택후 드래그 하는 경우
	if ( L_CanMove == 'o' ) {
		L_Insert.Last = point ;
		if ( m_IsColor == 'o' )
			L_Insert.L_Color = m_Color ;
		else
			L_Insert.L_Color = RGB (0,0,0) ;

		if ( m_IsFillColor == 'o' )
			L_Insert.L_FillColor = m_Color ;
		else
			L_Insert.L_FillColor = RGB (0,0,0) ;

		pDoc->L_Line.SetAt ( L_Current, L_Insert ) ;
		Invalidate () ;
	}
	// 상자 그리기 선택후 드래그 하는 경우
	else if ( R_CanMove == 'o' ) {
		R_Rect.right = point.x ;
		R_Rect.bottom = point.y ;

		if ( R_Rect.left > R_Rect.right ) {
			int temp = R_Rect.right ;
			R_Rect.right = R_Rect.left ;
			R_Rect.left = temp ;
		}
		if ( R_Rect.top > R_Rect.bottom ) {
			int temp = R_Rect.bottom ;
			R_Rect.bottom = R_Rect.top ;
			R_Rect.top = temp ;
		}

		pDoc->R_Rec.SetAt ( R_Current, R_Rect ) ;
		Invalidate () ;
	}
	// PolyLine 그리기 선택후 드래그 하는 경우
	else if ( P_CanMove == 'o' ) {

		// 마지막 Skeleton을 클릭하여 변형 하는 경우
		if ( P_IsStart == 'x' && P_ChangeSkeleton == 0 ) {
			if ( P_Insert.Poly_point.GetSize () == P_CurrentPoint )
				P_Insert.Poly_point.SetSize ( P_CurrentPoint + 1 ) ;
			P_Insert.Poly_point.SetAt ( P_CurrentPoint, point ) ;
			if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetSize () == P_CurrentPoint )
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetSize ( P_CurrentPoint + 1 ) ;
			pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( P_CurrentPoint, point ) ;
			Invalidate () ;
			P_IsMove = 'o' ;
		}

		// 첫 번째, 마지막 Skeleton을 제외한 부분을 변형 하는 경우
		else if ( P_ChangeSkeleton > 0 ) {
			P_Insert.Poly_point.SetAt ( P_ChangeSkeleton, point ) ;
			pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( P_ChangeSkeleton, point ) ;
			Invalidate () ;
			P_IsMove = 'o' ;
		}

		// 첫 번째 Skeleton을 변형 하는 경우
		else if ( P_IsStart == 'o' ) {
			P_Insert.Poly_point.SetAt ( 0, point ) ;
			pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( 0, point ) ;
			Invalidate () ;
			P_IsMove = 'o' ;
		}
	}
	// 원 그리기 선택후 드래그 하는 경우
	else if ( E_CanMove == 'o' ) {
		E_Insert.right = point.x ;
		E_Insert.bottom = point.y ;

		if ( E_Insert.left > E_Insert.right ) {
			int temp = E_Insert.right ;
			E_Insert.right = E_Insert.left ;
			E_Insert.left = temp ;
		}
		if ( E_Insert.top > E_Insert.bottom ) {
			int temp = E_Insert.bottom ;
			E_Insert.bottom = E_Insert.top ;
			E_Insert.top = temp ;
		}

		pDoc->E_Ellipse.SetAt ( R_Current, E_Insert ) ;
		Invalidate () ;
	}
	
	CScrollView::OnMouseMove(nFlags, point);
}


void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 선을 그리다 클릭을 땐 경우
	if ( L_IsDraw == 'o' ) {
		L_Insert.Last = point ;
		if ( m_IsColor == 'o' )
			L_Insert.L_Color = m_Color ;
		else
			L_Insert.L_Color = RGB (0,0,0) ;

		pDoc->L_Line.SetAt ( L_Current, L_Insert ) ;
		Invalidate (false) ;
		L_IsDraw = 'x' ;
		L_CanMove = 'x' ;
		IsNormal = 'o' ;
		m_IsColor = 'x' ;
		m_IsFillColor = 'x' ;
	}
	// 상자를 그리다 클릭을 땐 경우
	else if ( R_IsDraw == 'o' ) {
		R_Rect.right = point.x ;
		R_Rect.bottom = point.y ;

		if ( R_Rect.left > R_Rect.right ) {
			int temp = R_Rect.right ;
			R_Rect.right = R_Rect.left ;
			R_Rect.left = temp ;
		}
		if ( R_Rect.top > R_Rect.bottom ) {
			int temp = R_Rect.bottom ;
			R_Rect.bottom = R_Rect.top ;
			R_Rect.top = temp ;
		}

		pDoc->R_Rec.SetAt ( R_Current, R_Rect ) ;
		Invalidate () ;
		R_IsDraw = 'x' ;
		R_CanMove = 'x' ;
		IsNormal = 'o' ;
		m_IsColor = 'x' ;
		m_IsFillColor = 'x' ;
	}
	// PolyLine을 그리다 클릭을 땐 경우
	else if ( P_IsDraw == 'o' ) {
		// 만약 같은 좌표에 클릭, 땠을 경우 그리기 취소
		if ( P_IsMove == 'x' ) {
			P_CanMove = 'x' ; P_IsStart = 'x' ;
			P_Insert.Poly_point.RemoveAll () ;
			P_CanMove = 'x' ;
			P_IsContinue = 'x' ;
			P_IsDraw = 'x' ;
			IsNormal = 'o' ;
			m_IsColor = 'x' ;
			m_IsFillColor = 'x' ;
		}
		// 같은 좌표에 클릭, 땐 경우가 아니라면 그리기 모드
		else {
			// 만약 마지막 Skeleton을 변경한 경우
			if ( P_IsStart == 'x' && P_ChangeSkeleton == 0 ) {
				P_Insert.Poly_point.SetAt ( P_CurrentPoint, point ) ;
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( P_CurrentPoint, point ) ;
				Invalidate (false) ;
			}
			// 만약 첫번째 Skeleton을 변경한 경우
			else if ( P_IsStart == 'o' ) {
				P_Insert.Poly_point.SetAt ( 0, point ) ;
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( 0, point ) ;
				Invalidate (false) ;
				P_IsStart = 'x' ;
			}
			// 만약 첫번째, 마지막 Skeleton외 다른 Skeleton을 변경한 경우
			else if ( P_ChangeSkeleton > 0 ) {
				P_Insert.Poly_point.SetAt ( P_ChangeSkeleton, point ) ;
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( P_ChangeSkeleton, point ) ;
				Invalidate (false) ;
				P_ChangeSkeleton = 0 ;
			}
			P_CanMove = 'x' ;
			P_IsMove = 'x' ;
		}
	}
	// 원을 그리다 클릭을 땐 경우
	else if ( E_IsDraw == 'o' ) {
		E_Insert.right = point.x ;
		E_Insert.bottom = point.y ;

		if ( E_Insert.left > E_Insert.right ) {
			int temp = E_Insert.right ;
			E_Insert.right = E_Insert.left ;
			E_Insert.left = temp ;
		}
		if ( E_Insert.top > E_Insert.bottom ) {
			int temp = E_Insert.bottom ;
			E_Insert.bottom = E_Insert.top ;
			E_Insert.top = temp ;
		}

		pDoc->E_Ellipse.SetAt ( R_Current, E_Insert ) ;
		Invalidate () ;
		E_IsDraw = 'x' ;
		E_CanMove = 'x' ;
		IsNormal = 'o' ;
		m_IsColor = 'x' ;
		m_IsFillColor = 'x' ;
	}

	CScrollView::OnLButtonUp(nFlags, point);
}

// 선 그리기 툴바를 선택한 경우 불리어 집니다.
void CGraphicEditorView::OnDrawline()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	R_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	L_IsDraw = 'o' ;
	IsNormal = 'x' ;

	Invalidate (false) ;
}


BOOL CGraphicEditorView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nHitTest == HTCLIENT) {
		CPoint point ;
		::GetCursorPos ( &point ) ;	// 스크린 좌표
		ScreenToClient ( &point ) ;	// 클라이언트 좌표로 변환

		// 평상시엔 기본 커서로 변환 합니다.
		if ( IsNormal == 'o' )
			::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_ARROW)) ;
		// PolyLine을 계속해서 그리는 경우
		else if ( P_IsContinue == 'o' && P_CanMove == 'x' ) {
			// PolyLine의 Skeleton이 2개일 경우
			if ( P_CurrentPoint == 1 ) {
				// 원점과 마지막점에서 변경하려는 경우에 변형 커서로 변경 한다.
				if ( ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 8 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 8 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 8 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 8) ||
						(P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 8 &&
						P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 8 &&
						P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 8 &&
						P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 8) ) ) {
					::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
				}
				// 아닌 경우엔 십자가 커서로 변경
				else {
					::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_CROSS)) ;
				}
			}
			// PolyLine의 Skeleton이 3개 이상인 경우
			else {
				// 원점, 마지막 Skeleton을 제외한 모든 Skeleton을 검사하여
				// 커서의 좌표가 해당 Skeleton 중에 있는지 확인한다.
				char P_Flag = 'x' ;
				for ( int i = 1 ; i <= P_CurrentPoint - 1 ; i++ ) {
					if ( P_Insert.Poly_point.GetAt (i).x <= point.x + 8 &&
						P_Insert.Poly_point.GetAt (i).x >= point.x - 8 &&
						P_Insert.Poly_point.GetAt (i).y <= point.y + 8 &&
						P_Insert.Poly_point.GetAt (i).y >= point.y - 8 ) {
							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
							P_Flag = 'o' ;
					}
				}

				if ( P_Flag == 'x' ) {
					// 원점 Skeleton을 찾으면 커서를 4방향 커서로 변경한다.
					if ( (P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 8 &&
						P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 8 &&
						P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 8 &&
						P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 8) ) {
							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
					}
					// 마지막 Skeleton을 찾으면 커서를 4방향 커서로 변경한다.
					else if ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 8 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 8 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 8 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 8) ) {
							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
					}
					// Skeleton 주변에 없다면 십자가형 커서로 변환한다.
					else {
						::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_CROSS)) ;
					}
				}
			}
		}
		// 그리기 모드에선 커서가 십자형으로 변합니다.
		else if ( IsNormal == 'x' ) {
			::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_CROSS)) ;
		}
		return TRUE ;
	}

	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

// 상자 그리기 툴바를 선택한 경우 불리어 집니다.
void CGraphicEditorView::OnDrawrec()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	L_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	R_IsDraw = 'o' ;
	IsNormal = 'x' ;

	Invalidate (false) ;
}

// PolyLine 그리기 툴바를 선택한 경우 불리어 집니다.
void CGraphicEditorView::OnDrawpoly()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	L_IsDraw = 'x' ;
	R_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	Invalidate (false) ;

	P_IsDraw = 'o' ;
	IsNormal = 'x' ;
}

// 원 그리기 툴바를 선택한 경우 불리어 집니다.
void CGraphicEditorView::OnDrawellipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	L_IsDraw = 'x' ;
	R_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'o' ;
	IsNormal = 'x' ;

	Invalidate (false) ;
}

void CGraphicEditorView::OnSelectobject()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	//IsNormal = 'x' ;

	Invalidate (false) ;
}

void CGraphicEditorView::OnChangecolor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlgColor(0, CC_FULLOPEN, NULL);
	if( dlgColor.DoModal() == IDOK )
	{
		m_Color = dlgColor.GetColor();
		m_IsColor = 'o' ;
	}
}


void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 더블 클릭할 경우 PolyLine을 끝낸다.
	if ( P_IsDraw == 'o' ) {
		P_CanMove = 'x' ;
		P_IsDraw = 'x' ;
		IsNormal = 'o' ;
		P_Insert.Poly_point.RemoveAll () ;
		P_ChangeSkeleton = 0 ;
		P_IsContinue = 'x' ;
		m_IsColor = 'x' ;
		m_IsFillColor = 'x' ;
		P_DrawContinue = 'x' ;
		P_IsStart = 'x' ;
		P_IsMove = 'x' ;

		Invalidate () ;
	}

	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CGraphicEditorView::OnChangefillcolor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlgColor(0, CC_FULLOPEN, NULL);
	if( dlgColor.DoModal() == IDOK )
	{
		m_FillColor = dlgColor.GetColor();
		m_IsFillColor = 'o' ;
	}
}
