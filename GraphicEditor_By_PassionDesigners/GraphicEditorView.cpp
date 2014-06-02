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
#include "Thickness.h"

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
	ON_COMMAND(ID_NoFillColor, &CGraphicEditorView::OnNofillcolor)
	ON_COMMAND(ID_DrawTriangle, &CGraphicEditorView::OnDrawtriangle)
	ON_COMMAND(ID_DrawReverseTri, &CGraphicEditorView::OnDrawreversetri)
	ON_COMMAND(ID_Thickness, &CGraphicEditorView::OnThickness)
	ON_COMMAND(ID_RightAngledTri, &CGraphicEditorView::OnRightangledtri)
//	ON_COMMAND(ID_RRightAngledTri, &CGraphicEditorView::OnRrightangledtri)
ON_COMMAND(ID_RRightAngledTri, &CGraphicEditorView::OnRRrightangledtri)
ON_COMMAND(ID_RightToLeftTri, &CGraphicEditorView::OnRighttolefttri)
ON_COMMAND(ID_LeftToRightTri, &CGraphicEditorView::OnLefttorighttri)
END_MESSAGE_MAP()

// CGraphicEditorView 생성/소멸

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

	IsNormal = 'o' ;
	m_IsColor = 'x' ;
	m_IsFillColor = 'x' ;
	m_IsThickness = 'x' ;

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
	P_IsSkeletonStart = 'x' ;

	// 원 그리기에 필요한 변수들 초기화
	E_IsDraw = 'x' ;
	E_CanMove = 'x' ;

	// 세모 그리기에 필요한 변수들 초기화
	T_IsDraw = 'x' ;
	T_CanMove = 'x' ;

	// 역 삼각형 그리기에 필요한 변수들 초기화
	RT_IsDraw = 'x' ;
	RT_CanMove = 'x' ;

	// 직각 삼각형 그리기에 필요한 변수들 초기화
	RightT_IsDraw = 'x' ;
	RightT_CanMove = 'x' ;

	// 역 직각 삼각형 그리기에 필요한 변수들 초기화
	RRightT_IsDraw = 'x' ;
	RRightT_CanMove = 'x' ;

	// 왼쪽 -> 오른쪽 삼각형 그리기에 필요한 변수들 초기화
	LTRT_IsDraw = 'x' ;
	LTRT_CanMove = 'x' ;

	// 오른쪽 -> 왼쪽 삼각형 그리기에 필요한 변수들 초기화
	RTLT_IsDraw = 'x' ;
	RTLT_CanMove = 'x' ;
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
	
	int L_Number = 0 ;
	int R_Number = 0 ;
	int P_Number = 0 ;
	int E_Number = 0 ;
	int T_Number = 0 ;
	int RT_Number = 0 ;
	int RightT_Number = 0 ;
	int RRightT_Number = 0 ;
	int LTRT_Number = 0 ;
	int RTLT_Number = 0 ;

	// 모든 객체의 수만큼 출력을 합니다.
	// 그린 순서에 따라 출력됩니다.
	for ( int i = 0 ; i < pDoc->What.GetCount () ; i++ ) {

		// 선 객체일 경우
		if ( pDoc -> What.GetAt (i) == _T ("L") ) {
			// 색상을 가지지 않을 경우의 출력
			if ( pDoc -> L_Line.GetAt (L_Number).L_Color == RGB (0,0,0) ) {
				CPen pen ( PS_SOLID, pDoc -> L_Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
				L_Insert.Last = pDoc -> L_Line.GetAt (L_Number++).Last ;
				pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
				pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
				pDC->SelectObject(Draw_Pen);
			}
			// 특정 색상을 가졌을 경우의 출력
			else {
				CPen pen ( PS_SOLID, pDoc -> L_Line.GetAt (L_Number).Thickness, pDoc -> L_Line.GetAt (L_Number).L_Color ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
				L_Insert.Last = pDoc -> L_Line.GetAt (L_Number++).Last ;
				pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
				pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
				pDC->SelectObject(Draw_Pen);
			}
		}

		// 상자 객체일 경우
		else if ( pDoc -> What.GetAt (i) == _T ("R") ) {
			// 선 색을 가지지 않았을 경우의 출력
			if ( pDoc -> R_Color.GetAt (R_Number) == RGB (0,0,0) ) {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> R_FillColor.GetAt (R_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
					pDC -> SelectObject ( oldPen ) ; R_Number++ ;
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;
					pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
					pDC -> SelectObject ( oldBrush ) ;
					pDC -> SelectObject ( oldPen ) ; R_Number++ ;
				}
			}
			// 특정 선 색상을 가졌을 경우의 출력
			else {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> R_FillColor.GetAt (R_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
					pDC ->SelectObject ( oldPen ) ; R_Number++ ;
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;
					pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
					pDC -> SelectObject ( oldPen ) ;
					pDC -> SelectObject ( oldBrush ) ; R_Number++ ;
				}
			}
		}

		// PolyLine 객체인 경우
		else if ( pDoc -> What.GetAt (i) == _T ("P") ) {
			for ( int j = 0 ; j < pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetCount () - 1 ; j++ ) {

				// PolyLine이 색상을 가지지 않을 경우의 출력
				if ( pDoc -> P_Poly.GetAt (P_Number).P_Color == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> P_Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
					P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen);
				}
				// PolyLine이 지정된 색상을 가졌을 경우의 출력
				else {
					CPen pen ( PS_SOLID, pDoc -> P_Poly.GetAt (P_Number).thickness, pDoc -> P_Poly.GetAt (P_Number).P_Color ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
					P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
					P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen);
				}

				// 현재 그리고 있는 PolyLine의 Skeleton을 보여줍니다.
				if ( pDoc -> P_Poly.GetCount ()  == P_Number + 1 && P_IsDraw == 'o' && P_Insert.Poly_point.GetSize () > 0 ) {
					ChangeRect.left = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).x - 4 ;
					ChangeRect.right = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).x + 4 ;
					ChangeRect.top = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).y - 4 ;
					ChangeRect.bottom = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).y + 4 ;

					pDC -> Rectangle ( ChangeRect ) ;

					ChangeRect.left = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1).x - 4 ;
					ChangeRect.right = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1).x + 4 ;
					ChangeRect.top = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1).y - 4 ;
					ChangeRect.bottom = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1).y + 4 ;

					pDC -> Rectangle ( ChangeRect ) ;
				}
			}
			P_Number++ ;
		}

		// 원 객체일 경우
		else if ( pDoc -> What.GetAt (i) == _T ("E") ) {
			// 선 색을 가지지 않았을 경우의 출력
			if ( pDoc -> E_Color.GetAt (E_Number) == RGB (0,0,0) ) {
				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> E_FillColor.GetAt (E_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (E_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;
					pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
					pDC -> SelectObject ( oldBrush ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
			}
			// 특정 선 색상을 가졌을 경우의 출력
			else {
				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> E_FillColor.GetAt (E_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (E_Number), pDoc -> E_Color.GetAt (E_Number) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (E_Number), pDoc -> E_Color.GetAt (E_Number) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (E_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;
					pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
					pDC -> SelectObject ( oldPen ) ;
					pDC -> SelectObject ( oldBrush ) ;
				}
			}

			// 만약 원을 그리고 있는 상태라면 테두리 직사각형을 그려줍니다.
			if ( pDoc -> E_Ellipse.GetCount () - 1 == E_Number && E_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				P_PointStart.x = pDoc -> E_Ellipse.GetAt (E_Number).left - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointStart.y = pDoc -> E_Ellipse.GetAt (E_Number).top  - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.x = pDoc -> E_Ellipse.GetAt (E_Number).right + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.y = pDoc -> E_Ellipse.GetAt (E_Number).top - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
				pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
				pDC->SelectObject(Draw_Pen);
				;
				CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
				P_PointStart.x = pDoc -> E_Ellipse.GetAt (E_Number).left - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointStart.y = pDoc -> E_Ellipse.GetAt (E_Number).top - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.x = pDoc -> E_Ellipse.GetAt (E_Number).left - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.y = pDoc -> E_Ellipse.GetAt (E_Number).bottom + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
				pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
				pDC->SelectObject(Draw_Pen2);

				CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
				P_PointStart.x = pDoc -> E_Ellipse.GetAt (E_Number).left - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointStart.y = pDoc -> E_Ellipse.GetAt (E_Number).bottom + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.x = pDoc -> E_Ellipse.GetAt (E_Number).right + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.y = pDoc -> E_Ellipse.GetAt (E_Number).bottom + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
				pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
				pDC->SelectObject(Draw_Pen3);

				CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
				P_PointStart.x = pDoc -> E_Ellipse.GetAt (E_Number).right + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointStart.y = pDoc -> E_Ellipse.GetAt (E_Number).top - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.x = pDoc -> E_Ellipse.GetAt (E_Number).right + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.y = pDoc -> E_Ellipse.GetAt (E_Number).bottom + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
				pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
				pDC->SelectObject(Draw_Pen4);
			}
			E_Number++ ;
		}

		// 세모 객체일 경우
		else if ( pDoc -> What.GetAt (i) == _T ("T") ) {
			// 그릴 세모의 각 Point 좌표
			POINT T_Point[3] = { {pDoc -> T_Triangle.GetAt (T_Number).left + (pDoc -> T_Triangle.GetAt (T_Number).right - pDoc -> T_Triangle.GetAt (T_Number).left) / 2,
								  pDoc -> T_Triangle.GetAt (T_Number).top}, {pDoc -> T_Triangle.GetAt (T_Number).left, pDoc -> T_Triangle.GetAt (T_Number).bottom},
								 {pDoc -> T_Triangle.GetAt (T_Number).right, pDoc -> T_Triangle.GetAt (T_Number).bottom} } ;

			// 상단 꼭지점이 bottom에 생기는 경우
			if ( pDoc -> T_Triangle.GetAt (T_Number).top > pDoc -> T_Triangle.GetAt (T_Number).bottom ) {
				T_Point[0].y = pDoc -> T_Triangle.GetAt (T_Number).bottom ;
				T_Point[1].y = pDoc -> T_Triangle.GetAt (T_Number).top ;
				T_Point[2].y = pDoc -> T_Triangle.GetAt (T_Number).top ;
			}

			// 선 색을 가지지 않았을 경우의 출력
			if ( pDoc -> T_Color.GetAt (T_Number) == RGB (0,0,0) ) {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> T_FillColor.GetAt (T_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> T_Thickness.GetAt (T_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( T_Point, 3 ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> T_FillColor.GetAt (T_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;
					CPen pen ( PS_SOLID, pDoc -> T_Thickness.GetAt (T_Number), RGB (0, 0, 0) ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);

					pDC -> Polygon ( T_Point, 3 ) ;

					pDC->SelectObject ( Draw_Pen ) ;
					pDC -> SelectObject ( oldBrush ) ;
				}
			}
			// 특정 선 색상을 가졌을 경우의 출력
			else {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> T_FillColor.GetAt (T_Number) == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> T_Thickness.GetAt (T_Number), pDoc -> T_Color.GetAt (T_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( T_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {

					CPen pen ( PS_SOLID, pDoc -> T_Thickness.GetAt (T_Number), pDoc -> T_Color.GetAt (T_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> T_FillColor.GetAt (T_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Polygon ( T_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
					pDC -> SelectObject ( oldBrush ) ;		
				}
			}

			// 만약 세모를 그리고 있는 상태라면 테두리 직사각형을 그려줍니다.
			if ( pDoc -> T_Triangle.GetCount () - 1 == T_Number && T_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				if ( pDoc -> T_Triangle.GetAt (T_Number).top > pDoc -> T_Triangle.GetAt (T_Number).bottom ) {

					P_PointStart.x = pDoc -> T_Triangle.GetAt (T_Number).left + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointStart.y = pDoc -> T_Triangle.GetAt (T_Number).bottom + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.x = pDoc -> T_Triangle.GetAt (T_Number).right - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.y = pDoc -> T_Triangle.GetAt (T_Number).bottom + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen);
					;
					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> T_Triangle.GetAt (T_Number).left + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointStart.y = pDoc -> T_Triangle.GetAt (T_Number).top + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.x = pDoc -> T_Triangle.GetAt (T_Number).left + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.y = pDoc -> T_Triangle.GetAt (T_Number).bottom - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> T_Triangle.GetAt (T_Number).right - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointStart.y = pDoc -> T_Triangle.GetAt (T_Number).top + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.x = pDoc -> T_Triangle.GetAt (T_Number).right - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.y = pDoc -> T_Triangle.GetAt (T_Number).bottom - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen4);
				}
				else {
					P_PointStart.x = pDoc -> T_Triangle.GetAt (T_Number).left - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointStart.y = pDoc -> T_Triangle.GetAt (T_Number).top - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.x = pDoc -> T_Triangle.GetAt (T_Number).right + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.y = pDoc -> T_Triangle.GetAt (T_Number).top - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen);
					;
					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> T_Triangle.GetAt (T_Number).left - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointStart.y = pDoc -> T_Triangle.GetAt (T_Number).top - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.x = pDoc -> T_Triangle.GetAt (T_Number).left - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.y = pDoc -> T_Triangle.GetAt (T_Number).bottom + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> T_Triangle.GetAt (T_Number).right + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointStart.y = pDoc -> T_Triangle.GetAt (T_Number).top - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.x = pDoc -> T_Triangle.GetAt (T_Number).right + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.y = pDoc -> T_Triangle.GetAt (T_Number).bottom + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen4);
				}
			}
			T_Number++ ;
		}

		// 역 삼각형 객체인 경우
		else if ( pDoc -> What.GetAt (i) == _T ("RT") ) {
			// 그릴 세모의 각 Point 좌표
			POINT RT_Point[3] = { {pDoc -> RT_Triangle.GetAt (RT_Number).left + (pDoc -> RT_Triangle.GetAt (RT_Number).right - pDoc -> RT_Triangle.GetAt (RT_Number).left) / 2,
								   pDoc -> RT_Triangle.GetAt (RT_Number).bottom}, {pDoc -> RT_Triangle.GetAt (RT_Number).left, pDoc -> RT_Triangle.GetAt (RT_Number).top},
								  {pDoc -> RT_Triangle.GetAt (RT_Number).right, pDoc -> RT_Triangle.GetAt (RT_Number).top} } ;

			// 상단 꼭지점이 top에 생기는 경우
			if ( pDoc -> RT_Triangle.GetAt (RT_Number).top > pDoc -> RT_Triangle.GetAt (RT_Number).bottom ) {
				RT_Point[0].y = pDoc -> RT_Triangle.GetAt (RT_Number).top ;
				RT_Point[1].y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom ;
				RT_Point[2].y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom ;
			}

			// 선 색을 가지지 않았을 경우의 출력
			if ( pDoc -> RT_Color.GetAt (RT_Number) == RGB (0,0,0) ) {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> RT_FillColor.GetAt (RT_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> RT_Thickness.GetAt (RT_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RT_Point, 3 ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;
					CPen pen ( PS_SOLID, pDoc -> RT_Thickness.GetAt (RT_Number), RGB (0, 0, 0) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);

					pDC -> Polygon ( RT_Point, 3 ) ;

					pDC->SelectObject ( Draw_Pen ) ;
					pDC -> SelectObject ( oldBrush ) ;
				}
			}
			// 특정 선 색상을 가졌을 경우의 출력
			else {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> RT_FillColor.GetAt (RT_Number) == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> RT_Thickness.GetAt (RT_Number), pDoc -> RT_Color.GetAt (RT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {

					CPen pen ( PS_SOLID, pDoc -> RT_Thickness.GetAt (RT_Number), pDoc -> RT_Color.GetAt (RT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
					CBrush brush;
					brush.CreateSolidBrush ( pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Polygon ( RT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
					pDC -> SelectObject ( oldBrush ) ;		
				}
			}

			// 만약 역 삼각형을 그리고 있는 상태라면 테두리 직사각형을 그려줍니다.
			if ( pDoc -> RT_Triangle.GetCount () - 1 == RT_Number && RT_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				// 상단 꼭지점이 top에 생기는 경우
				if ( pDoc -> RT_Triangle.GetAt (RT_Number).top > pDoc -> RT_Triangle.GetAt (RT_Number).bottom ) {
					P_PointStart.x = pDoc -> RT_Triangle.GetAt (RT_Number).left + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointStart.y = pDoc -> RT_Triangle.GetAt (RT_Number).top - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.x = pDoc -> RT_Triangle.GetAt (RT_Number).right - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.y = pDoc -> RT_Triangle.GetAt (RT_Number).top - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen);
					;
					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RT_Triangle.GetAt (RT_Number).left + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointStart.y = pDoc -> RT_Triangle.GetAt (RT_Number).top + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.x = pDoc -> RT_Triangle.GetAt (RT_Number).left + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RT_Triangle.GetAt (RT_Number).right - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointStart.y = pDoc -> RT_Triangle.GetAt (RT_Number).top + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.x = pDoc -> RT_Triangle.GetAt (RT_Number).right - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen4);
				}
				// 정상인 경우
				else {
					P_PointStart.x = pDoc -> RT_Triangle.GetAt (RT_Number).left - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointStart.y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.x = pDoc -> RT_Triangle.GetAt (RT_Number).right + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen);
					;
					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RT_Triangle.GetAt (RT_Number).left - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointStart.y = pDoc -> RT_Triangle.GetAt (RT_Number).top - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.x = pDoc -> RT_Triangle.GetAt (RT_Number).left - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RT_Triangle.GetAt (RT_Number).right + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointStart.y = pDoc -> RT_Triangle.GetAt (RT_Number).top - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.x = pDoc -> RT_Triangle.GetAt (RT_Number).right + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen4);
				}
			}
			RT_Number++ ;
		}

		// 직각 삼각형 객체인 경우
		else if ( pDoc -> What.GetAt (i) == _T ("RightT") ) {
			// 그릴 직각 삼각형의 각 Point 좌표
			POINT RightT_Point[3] = { {pDoc -> RightT_Triangle.GetAt (RightT_Number).right, pDoc -> RightT_Triangle.GetAt (RightT_Number).top},
									  {pDoc -> RightT_Triangle.GetAt (RightT_Number).left, pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom},
									  {pDoc -> RightT_Triangle.GetAt (RightT_Number).right, pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom} } ;

			if ( pDoc -> RightT_Triangle.GetAt (RightT_Number).left > pDoc -> RightT_Triangle.GetAt (RightT_Number).right ) {
				RightT_Point[0].x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left ;
				RightT_Point[1].x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right ;
				RightT_Point[2].x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left ;
			}

			if ( pDoc -> RightT_Triangle.GetAt (RightT_Number).top > pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom ) {
				RightT_Point[0].y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom ;
				RightT_Point[1].y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top ;
				RightT_Point[2].y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top ;
			}

			// 선 색을 가지지 않았을 경우의 출력
			if ( pDoc -> RightT_Color.GetAt (RightT_Number) == RGB (0,0,0) ) {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> RightT_FillColor.GetAt (RightT_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> RightT_Thickness.GetAt (RightT_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RightT_Point, 3 ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;
					CPen pen ( PS_SOLID, pDoc -> RightT_Thickness.GetAt (RightT_Number), RGB (0, 0, 0) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);

					pDC -> Polygon ( RightT_Point, 3 ) ;

					pDC->SelectObject ( Draw_Pen ) ;
					pDC -> SelectObject ( oldBrush ) ;
				}
			}
			// 특정 선 색상을 가졌을 경우의 출력
			else {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> RightT_FillColor.GetAt (RightT_Number) == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> RightT_Thickness.GetAt (RightT_Number), pDoc -> RightT_Color.GetAt (RightT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RightT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {

					CPen pen ( PS_SOLID, pDoc -> RightT_Thickness.GetAt (RightT_Number), pDoc -> RightT_Color.GetAt (RightT_Number) ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Polygon ( RightT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
					pDC -> SelectObject ( oldBrush ) ;		
				}
			}

			// 만약 직각 삼각형을 그리고 있는 상태라면 테두리 직사각형을 그려줍니다.
			if ( pDoc -> RightT_Triangle.GetCount () - 1 == RightT_Number && RightT_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) ) ;
				if ( pDoc -> RightT_Triangle.GetAt (RightT_Number).top > pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom ) {
					if ( pDoc -> RightT_Triangle.GetAt (RightT_Number).left > pDoc -> RightT_Triangle.GetAt (RightT_Number).right ) {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen2);
					}
					else {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen2);
					}
				}
				else {
					if ( pDoc -> RightT_Triangle.GetAt (RightT_Number).left > pDoc -> RightT_Triangle.GetAt (RightT_Number).right ) {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen2);
					}
					else {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen2);
					}
				}
			}
			RightT_Number++ ;
		}

		// 역 직각 삼각형 객체인 경우
		else if ( pDoc -> What.GetAt (i) == _T ("RRightT") ) {
			// 그릴 역 직각 상각형의 각 Point 좌표
			POINT RRightT_Point[3] = { {pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left, pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top},
									   {pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left, pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom},
									   {pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right, pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top} } ;

			if ( pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left > pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right ) {
				RRightT_Point[0].x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right ;
				RRightT_Point[1].x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right ;
				RRightT_Point[2].x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left ;
			}

			if ( pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top > pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom ) {
				RRightT_Point[0].y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom ;
				RRightT_Point[1].y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top ;
				RRightT_Point[2].y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom ;
			}

			// 선 색을 가지지 않았을 경우의 출력
			if ( pDoc -> RRightT_Color.GetAt (RRightT_Number) == RGB (0,0,0) ) {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> RRightT_FillColor.GetAt (RRightT_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> RRightT_Thickness.GetAt (RRightT_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RRightT_Point, 3 ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;
					CPen pen ( PS_SOLID, pDoc -> RRightT_Thickness.GetAt (RRightT_Number), RGB (0, 0, 0) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);

					pDC -> Polygon ( RRightT_Point, 3 ) ;

					pDC->SelectObject ( Draw_Pen ) ;
					pDC -> SelectObject ( oldBrush ) ;
				}
			}
			// 특정 선 색상을 가졌을 경우의 출력
			else {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> RRightT_FillColor.GetAt (RRightT_Number) == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> RRightT_Thickness.GetAt (RRightT_Number), pDoc -> RRightT_Color.GetAt (RRightT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RRightT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {

					CPen pen ( PS_SOLID, pDoc -> RRightT_Thickness.GetAt (RRightT_Number), pDoc -> RRightT_Color.GetAt (RRightT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Polygon ( RRightT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
					pDC -> SelectObject ( oldBrush ) ;		
				}
			}

			// 만약 역 직각 삼각형을 그리고 있는 상태라면 테두리 직사각형을 그려줍니다.
			if ( pDoc -> RRightT_Triangle.GetCount () - 1 == RRightT_Number && RRightT_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );

				if ( pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top > pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom ) {
					if ( pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left > pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right ) {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen2);
					}
					else {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen2);
					}
				}
				else {
					if ( pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left > pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right ) {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen2);
					}
					else {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen2);
					}
				}
			}
			RRightT_Number++ ;
		}

		// 왼쪽 -> 오른쪽 삼각형 객체인 경우
		else if ( pDoc -> What.GetAt (i) == _T ("LTRT") ) {
			// 그릴 왼쪽 -> 오른쪽 삼각형의 각 Point 좌표
			POINT LTRT_Point[3] = { {pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right,
									 pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top + (pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom - pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top) / 2 },
									{pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left, pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top},
									{pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left, pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom} } ;

			if ( pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left > pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right ) {
				LTRT_Point[0].x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left ;
				LTRT_Point[1].x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right ;
				LTRT_Point[2].x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right ;
			}

			// 선 색을 가지지 않았을 경우의 출력
			if ( pDoc -> LTRT_Color.GetAt (LTRT_Number) == RGB (0,0,0) ) {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> LTRT_FillColor.GetAt (LTRT_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> LTRT_Thickness.GetAt (LTRT_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( LTRT_Point, 3 ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;
					CPen pen ( PS_SOLID, pDoc -> LTRT_Thickness.GetAt (LTRT_Number), RGB (0, 0, 0) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);

					pDC -> Polygon ( LTRT_Point, 3 ) ;

					pDC->SelectObject ( Draw_Pen ) ;
					pDC -> SelectObject ( oldBrush ) ;
				}
			}
			// 특정 선 색상을 가졌을 경우의 출력
			else {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> LTRT_FillColor.GetAt (LTRT_Number) == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> LTRT_Thickness.GetAt (LTRT_Number), pDoc -> LTRT_Color.GetAt (LTRT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( LTRT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {

					CPen pen ( PS_SOLID, pDoc -> LTRT_Thickness.GetAt (LTRT_Number), pDoc -> LTRT_Color.GetAt (LTRT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Polygon ( LTRT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
					pDC -> SelectObject ( oldBrush ) ;		
				}
			}

			// 만약 왼쪽 -> 오른쪽 삼각형을 그리고 있는 상태라면 테두리 직사각형을 그려줍니다.
			if ( pDoc -> LTRT_Triangle.GetCount () - 1 == LTRT_Number && LTRT_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );

				if ( pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left > pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right ) {
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen);

					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen3);
				}
				else {
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen);

					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen3);
				}
			}
			LTRT_Number++ ;
		}

		// 오른쪽 -> 왼쪽 삼각형 객체인 경우
		else if ( pDoc -> What.GetAt (i) == _T ("RTLT") ) {
			// 그릴 오른쪽 -> 왼쪽 삼각형의 각 Point 좌표
			POINT RTLT_Point[3] = { {pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left,
									 pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top + (pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom - pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top) / 2 },
									{pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right, pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top},
									{pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right, pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom} } ;

			if ( pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left > pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right ) {
				RTLT_Point[0].x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right ;
				RTLT_Point[1].x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left ;
				RTLT_Point[2].x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left ;
			}

			// 선 색을 가지지 않았을 경우의 출력
			if ( pDoc -> RTLT_Color.GetAt (RTLT_Number) == RGB (0,0,0) ) {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> RTLT_FillColor.GetAt (RTLT_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> RTLT_Thickness.GetAt (RTLT_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RTLT_Point, 3 ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;
					CPen pen ( PS_SOLID, pDoc -> RTLT_Thickness.GetAt (RTLT_Number), RGB (0, 0, 0) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);

					pDC -> Polygon ( RTLT_Point, 3 ) ;

					pDC->SelectObject ( Draw_Pen ) ;
					pDC -> SelectObject ( oldBrush ) ;
				}
			}
			// 특정 선 색상을 가졌을 경우의 출력
			else {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> RTLT_FillColor.GetAt (RTLT_Number) == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> RTLT_Thickness.GetAt (RTLT_Number), pDoc -> RTLT_Color.GetAt (RTLT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RTLT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {

					CPen pen ( PS_SOLID, pDoc -> RTLT_Thickness.GetAt (RTLT_Number), pDoc -> RTLT_Color.GetAt (RTLT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Polygon ( RTLT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
					pDC -> SelectObject ( oldBrush ) ;		
				}
			}

			// 만약 왼쪽 -> 오른쪽 삼각형을 그리고 있는 상태라면 테두리 직사각형을 그려줍니다.
			if ( pDoc -> RTLT_Triangle.GetCount () - 1 == RTLT_Number && RTLT_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );

				if ( pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left > pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right ) {
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen);

					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen3);
				}
				else {
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen);

					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen3);
				}
			}
			RTLT_Number++ ;
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
		pDoc->What.Add ( _T("L") ) ;
		pDoc->L_Count++ ;
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
		pDoc->What.Add ( _T("R") ) ;
		pDoc->R_Count++ ;
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

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> R_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> R_Thickness.Add (1) ;
	}
	// PolyLine을 계속해서 그리는 경우
	else if ( P_IsContinue == 'o') {
		// PolyLine의 Skeleton이 2개일 경우
		if ( P_CurrentPoint == 1 ) {
			// 원점과 마지막점에서 변경하려는 경우엔 계속 그릴수 있게 한다.
			if ( ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 15 &&
				P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 15 &&
				P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 15 &&
				P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 15) ||
				(P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 15 &&
				P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 15 &&
				P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 15 &&
				P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 15) ) ) {

					if ( (P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 15 &&
						  P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 15 &&
						  P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 15 &&
						  P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 15) )
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
				if ( P_Insert.Poly_point.GetAt (i).x <= point.x + 15 &&
					 P_Insert.Poly_point.GetAt (i).x >= point.x - 15 &&
					 P_Insert.Poly_point.GetAt (i).y <= point.y + 15 &&
					 P_Insert.Poly_point.GetAt (i).y >= point.y - 15 ) {
					P_ChangeSkeleton = i ;
					P_CanMove = 'o' ;
					P_Flag = 'o' ;
				}
			}

			if ( P_Flag == 'x' ) {
				// 원점 Skeleton을 건드리면 시작 점을 변경한다.
				if ( (P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 15 &&
					P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 15 &&
					P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 15 &&
					P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 15) ) {
						P_IsStart = 'o' ;
						P_CanMove = 'o' ;
				}
				// 마지막 Skeleton을 건드리면 그 Skeleton을 변경한다.
				else if ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 15 &&
					P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 15 &&
					P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 15 &&
					P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 15) ) {
						P_CanMove = 'o' ;
						P_CurrentPoint++ ;
				}
			}
		}
	}
	// PolyLine 그리기 시, 맨 처음 Skeleton을 클릭하여 만들 경우입니다.
	else if ( P_IsDraw == 'o' && P_IsContinue == 'x' ) {
		P_Insert.Poly_point.Add ( point ) ;
		pDoc->What.Add ( _T("P") ) ;
		pDoc -> P_Count = P_Current = pDoc -> P_Poly.GetCount () ;
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

		if ( m_IsThickness == 'o' )
			pDoc -> P_Poly.GetAt ( P_Current ).thickness = m_Thickness ;
		else if ( m_IsThickness == 'x' )
			pDoc -> P_Poly.GetAt ( P_Current ).thickness = 1 ;
	}
	// 원을 그리는 경우
	else if ( E_IsDraw == 'o' ) {
		E_Insert.left = point.x ;
		E_Insert.right = point.x ;
		E_Insert.top = point.y ;
		E_Insert.bottom = point.y ;

		pDoc -> E_Ellipse.Add ( E_Insert ) ;
		pDoc->What.Add ( _T("E") ) ;
		pDoc->E_Count++ ;
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

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> E_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> E_Thickness.Add (1) ;
	}
	// 세모를 그리는 경우
	else if ( T_IsDraw == 'o' ) {
		T_Insert.left = point.x ;
		T_Insert.right = point.x ;
		T_Insert.top = point.y ;
		T_Insert.bottom = point.y ;

		pDoc -> T_Triangle.Add ( T_Insert ) ;
		pDoc->What.Add ( _T("T") ) ;
		pDoc->T_Count++ ;
		T_Current = pDoc -> T_Triangle.GetCount () - 1 ;
		T_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> T_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> T_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> T_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> T_FillColor.Add ( RGB(0,0,0) ) ;

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> T_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> T_Thickness.Add (1) ;
	}
	// 역 삼각형을 그리는 경우
	else if ( RT_IsDraw == 'o' ) {
		RT_Insert.left = point.x ;
		RT_Insert.right = point.x ;
		RT_Insert.top = point.y ;
		RT_Insert.bottom = point.y ;

		pDoc -> RT_Triangle.Add ( RT_Insert ) ;
		pDoc->What.Add ( _T("RT") ) ;
		pDoc->RT_Count++ ;
		RT_Current = pDoc -> RT_Triangle.GetCount () - 1 ;
		RT_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> RT_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> RT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> RT_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> RT_FillColor.Add ( RGB(0,0,0) ) ;

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> RT_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> RT_Thickness.Add (1) ;
	}
	// 직각 삼각형을 그리는 경우
	else if ( RightT_IsDraw == 'o' ) {
		RightT_Insert.left = point.x ;
		RightT_Insert.right = point.x ;
		RightT_Insert.top = point.y ;
		RightT_Insert.bottom = point.y ;

		pDoc -> RightT_Triangle.Add ( RightT_Insert ) ;
		pDoc->What.Add ( _T("RightT") ) ;
		pDoc->RightT_Count++ ;
		RightT_Current = pDoc -> RightT_Triangle.GetCount () - 1 ;
		RightT_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> RightT_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> RightT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> RightT_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> RightT_FillColor.Add ( RGB(0,0,0) ) ;

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> RightT_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> RightT_Thickness.Add (1) ;
	}
	// 역 직각 삼각형을 그리는 경우
	else if ( RRightT_IsDraw == 'o' ) {
		RRightT_Insert.left = point.x ;
		RRightT_Insert.right = point.x ;
		RRightT_Insert.top = point.y ;
		RRightT_Insert.bottom = point.y ;

		pDoc -> RRightT_Triangle.Add ( RRightT_Insert ) ;
		pDoc->What.Add ( _T("RRightT") ) ;
		pDoc->RRightT_Count++ ;
		RRightT_Current = pDoc -> RRightT_Triangle.GetCount () - 1 ;
		RRightT_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> RRightT_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> RRightT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> RRightT_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> RRightT_FillColor.Add ( RGB(0,0,0) ) ;

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> RRightT_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> RRightT_Thickness.Add (1) ;
	}
	// 왼쪽 -> 오른쪽 삼각형을 그리는 경우
	else if ( LTRT_IsDraw == 'o' ) {
		LTRT_Insert.left = point.x ;
		LTRT_Insert.right = point.x ;
		LTRT_Insert.top = point.y ;
		LTRT_Insert.bottom = point.y ;

		pDoc -> LTRT_Triangle.Add ( LTRT_Insert ) ;
		pDoc->What.Add ( _T("LTRT") ) ;
		pDoc->LTRT_Count++ ;
		LTRT_Current = pDoc -> LTRT_Triangle.GetCount () - 1 ;
		LTRT_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> LTRT_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> LTRT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> LTRT_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> LTRT_FillColor.Add ( RGB(0,0,0) ) ;

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> LTRT_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> LTRT_Thickness.Add (1) ;
	}
	// 오른쪽 -> 왼쪽 삼각형을 그리는 경우
	else if ( RTLT_IsDraw == 'o' ) {
		RTLT_Insert.left = point.x ;
		RTLT_Insert.right = point.x ;
		RTLT_Insert.top = point.y ;
		RTLT_Insert.bottom = point.y ;

		pDoc -> RTLT_Triangle.Add ( RTLT_Insert ) ;
		pDoc->What.Add ( _T("RTLT") ) ;
		pDoc->RTLT_Count++ ;
		RTLT_Current = pDoc -> RTLT_Triangle.GetCount () - 1 ;
		RTLT_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> RTLT_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> RTLT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> RTLT_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> RTLT_FillColor.Add ( RGB(0,0,0) ) ;

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> RTLT_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> RTLT_Thickness.Add (1) ;
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

		if ( m_IsThickness == 'o' )
			L_Insert.Thickness = m_Thickness ;
		else
			L_Insert.Thickness = 1 ;

		pDoc->L_Line.SetAt ( L_Current, L_Insert ) ;
		Invalidate () ;
	}
	// 상자 그리기 선택후 드래그 하는 경우
	else if ( R_CanMove == 'o' ) {
		R_Rect.right = point.x ;
		R_Rect.bottom = point.y ;

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
			if ( P_IsSkeletonStart != 'o' )
				P_CurrentPoint++ ;

			pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetSize ( P_CurrentPoint+1 ) ;
			pDoc -> P_Poly.GetAt ( P_Current).Poly_point.SetAt ( 0, point ) ;
			P_Insert.Poly_point.SetSize ( P_CurrentPoint+1 ) ;

			if ( P_IsSkeletonStart != 'o' ) {
				for ( int i = 1 ; i < P_CurrentPoint + 1 ; i++ ) {
					pDoc -> P_Poly.GetAt ( P_Current).Poly_point.SetAt ( i, P_Insert.Poly_point.GetAt (i-1) ) ;
					P_Insert.Poly_point.SetAt ( i-1, pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i-1) ) ;
				}

				P_Insert.Poly_point.SetAt ( P_CurrentPoint, pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (P_CurrentPoint) ) ;
			}

			Invalidate () ;
			P_IsMove = 'o' ;
			P_IsSkeletonStart = 'o' ;
		}
	}
	// 원 그리기 선택후 드래그 하는 경우
	else if ( E_CanMove == 'o' ) {
		E_Insert.right = point.x ;
		E_Insert.bottom = point.y ;

		pDoc->E_Ellipse.SetAt ( R_Current, E_Insert ) ;
		Invalidate () ;
	}
	// 세모 그리기 선택후 드래그 하는 경우
	else if ( T_CanMove == 'o' ) {
		T_Insert.right = point.x ;
		T_Insert.bottom = point.y ;

		pDoc->T_Triangle.SetAt ( T_Current, T_Insert ) ;
		Invalidate () ;
	}
	// 역 삼각형 그리기 선택후 드래그 하는 경우
	else if ( RT_CanMove == 'o' ) {
		RT_Insert.right = point.x ;
		RT_Insert.bottom = point.y ;

		pDoc->RT_Triangle.SetAt ( RT_Current, RT_Insert ) ;
		Invalidate () ;
	}
	// 직각 삼각형 그리기 선택후 드래그 하는 경우
	else if ( RightT_CanMove == 'o' ) {
		RightT_Insert.right = point.x ;
		RightT_Insert.bottom = point.y ;

		pDoc->RightT_Triangle.SetAt ( RightT_Current, RightT_Insert ) ;
		Invalidate () ;
	}
	// 역 직각 삼각형 그리기 선택후 드래그 하는 경우
	else if ( RRightT_CanMove == 'o' ) {
		RRightT_Insert.right = point.x ;
		RRightT_Insert.bottom = point.y ;

		pDoc->RRightT_Triangle.SetAt ( RRightT_Current, RRightT_Insert ) ;
		Invalidate () ;
	}
	// 왼쪽 -> 오른쪽 삼각형 그리기 선택후 드래그 하는 경우
	else if ( LTRT_CanMove == 'o' ) {
		LTRT_Insert.right = point.x ;
		LTRT_Insert.bottom = point.y ;

		pDoc->LTRT_Triangle.SetAt ( LTRT_Current, LTRT_Insert ) ;
		Invalidate () ;
	}
	// 오른쪽 -> 왼쪽 삼각형 그리기 선택후 드래그 하는 경우
	else if ( RTLT_CanMove == 'o' ) {
		RTLT_Insert.right = point.x ;
		RTLT_Insert.bottom = point.y ;

		pDoc->RTLT_Triangle.SetAt ( RTLT_Current, RTLT_Insert ) ;
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

		if ( m_IsThickness == 'o' )
			L_Insert.Thickness = m_Thickness ;
		else
			L_Insert.Thickness = 1 ;

		pDoc->L_Line.SetAt ( L_Current, L_Insert ) ;
		Invalidate () ;
		L_IsDraw = 'x' ;
		L_CanMove = 'x' ;
		IsNormal = 'o' ;
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
			Invalidate () ;
		}
		// 같은 좌표에 클릭, 땐 경우가 아니라면 그리기 모드
		else {
			// 만약 마지막 Skeleton을 변경한 경우
			if ( P_IsStart == 'x' && P_ChangeSkeleton == 0 ) {
				P_Insert.Poly_point.SetAt ( P_CurrentPoint, point ) ;
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( P_CurrentPoint, point ) ;
				Invalidate () ;
			}
			// 만약 첫번째 Skeleton을 변경한 경우
			else if ( P_IsStart == 'o' ) {
				P_Insert.Poly_point.SetAt ( 0, point ) ;
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( 0, point ) ;
				Invalidate () ;
				P_IsStart = 'x' ;
				P_IsSkeletonStart = 'x' ;
			}
			// 만약 첫번째, 마지막 Skeleton외 다른 Skeleton을 변경한 경우
			else if ( P_ChangeSkeleton > 0 ) {
				P_Insert.Poly_point.SetAt ( P_ChangeSkeleton, point ) ;
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( P_ChangeSkeleton, point ) ;
				Invalidate () ;
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
	}
	// 세모를 그리다 클릭을 땐 경우
	else if ( T_IsDraw == 'o' ) {
		T_Insert.right = point.x ;
		T_Insert.bottom = point.y ;

		if ( T_Insert.left > T_Insert.right ) {
			int temp = T_Insert.right ;
			T_Insert.right = T_Insert.left ;
			T_Insert.left = temp ;
		}
		if ( T_Insert.top > T_Insert.bottom ) {
			int temp = T_Insert.bottom ;
			T_Insert.bottom = T_Insert.top ;
			T_Insert.top = temp ;
		}

		pDoc -> T_Triangle.SetAt ( T_Current, T_Insert ) ;
		Invalidate () ;
		T_IsDraw = 'x' ;
		T_CanMove = 'x' ;
		IsNormal = 'o' ;
	}
	// 역 삼각형을 그리다 클릭을 땐 경우
	else if ( RT_IsDraw == 'o' ) {
		RT_Insert.right = point.x ;
		RT_Insert.bottom = point.y ;

		if ( RT_Insert.left > RT_Insert.right ) {
			int temp = RT_Insert.right ;
			RT_Insert.right = RT_Insert.left ;
			RT_Insert.left = temp ;
		}
		if ( RT_Insert.top > RT_Insert.bottom ) {
			int temp = RT_Insert.bottom ;
			RT_Insert.bottom = RT_Insert.top ;
			RT_Insert.top = temp ;
		}

		pDoc -> RT_Triangle.SetAt ( RT_Current, RT_Insert ) ;
		Invalidate () ;
		RT_IsDraw = 'x' ;
		RT_CanMove = 'x' ;
		IsNormal = 'o' ;
	}
	// 직각 삼각형을 그리다 클릭을 땐 경우
	else if ( RightT_IsDraw == 'o' ) {
		RightT_Insert.right = point.x ;
		RightT_Insert.bottom = point.y ;

		if ( RightT_Insert.left > RightT_Insert.right ) {
			int temp = RightT_Insert.right ;
			RightT_Insert.right = RightT_Insert.left ;
			RightT_Insert.left = temp ;
		}
		if ( RightT_Insert.top > RightT_Insert.bottom ) {
			int temp = RightT_Insert.bottom ;
			RightT_Insert.bottom = RightT_Insert.top ;
			RightT_Insert.top = temp ;
		}

		pDoc -> RightT_Triangle.SetAt ( RightT_Current, RightT_Insert ) ;
		Invalidate () ;
		RightT_IsDraw = 'x' ;
		RightT_CanMove = 'x' ;
		IsNormal = 'o' ;
	}
	// 역 직각 삼각형을 그리다 클릭을 땐 경우
	else if ( RRightT_IsDraw == 'o' ) {
		RRightT_Insert.right = point.x ;
		RRightT_Insert.bottom = point.y ;

		if ( RRightT_Insert.left > RRightT_Insert.right ) {
			int temp = RRightT_Insert.right ;
			RRightT_Insert.right = RRightT_Insert.left ;
			RRightT_Insert.left = temp ;
		}
		if ( RRightT_Insert.top > RRightT_Insert.bottom ) {
			int temp = RRightT_Insert.bottom ;
			RRightT_Insert.bottom = RRightT_Insert.top ;
			RRightT_Insert.top = temp ;
		}

		pDoc -> RRightT_Triangle.SetAt ( RRightT_Current, RRightT_Insert ) ;
		Invalidate () ;
		RRightT_IsDraw = 'x' ;
		RRightT_CanMove = 'x' ;
		IsNormal = 'o' ;
	}
	// 왼쪽 -> 오른쪽 직각 삼각형을 그리다 클릭을 땐 경우
	else if ( LTRT_IsDraw == 'o' ) {
		LTRT_Insert.right = point.x ;
		LTRT_Insert.bottom = point.y ;

		if ( LTRT_Insert.left > LTRT_Insert.right ) {
			int temp = LTRT_Insert.right ;
			LTRT_Insert.right = LTRT_Insert.left ;
			LTRT_Insert.left = temp ;
		}
		if ( LTRT_Insert.top > LTRT_Insert.bottom ) {
			int temp = LTRT_Insert.bottom ;
			LTRT_Insert.bottom = LTRT_Insert.top ;
			LTRT_Insert.top = temp ;
		}

		pDoc -> LTRT_Triangle.SetAt ( LTRT_Current, LTRT_Insert ) ;
		Invalidate () ;
		LTRT_IsDraw = 'x' ;
		LTRT_CanMove = 'x' ;
		IsNormal = 'o' ;
	}
	// 오른쪽 -> 왼쪽 직각 삼각형을 그리다 클릭을 땐 경우
	else if ( RTLT_IsDraw == 'o' ) {
		RTLT_Insert.right = point.x ;
		RTLT_Insert.bottom = point.y ;

		if ( RTLT_Insert.left > RTLT_Insert.right ) {
			int temp = RTLT_Insert.right ;
			RTLT_Insert.right = RTLT_Insert.left ;
			RTLT_Insert.left = temp ;
		}
		if ( RTLT_Insert.top > RTLT_Insert.bottom ) {
			int temp = RTLT_Insert.bottom ;
			RTLT_Insert.bottom = RTLT_Insert.top ;
			RTLT_Insert.top = temp ;
		}

		pDoc -> RTLT_Triangle.SetAt ( RTLT_Current, RTLT_Insert ) ;
		Invalidate () ;
		RTLT_IsDraw = 'x' ;
		RTLT_CanMove = 'x' ;
		IsNormal = 'o' ;
	}

	CScrollView::OnLButtonUp(nFlags, point);
}

// 선 그리기 툴바를 선택한 경우 불리어 집니다.
void CGraphicEditorView::OnDrawline()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	LTRT_IsDraw = 'x' ;
	RTLT_IsDraw = 'x' ;
	RRightT_IsDraw = 'x' ;
	RightT_IsDraw = 'x' ;
	RT_IsDraw = 'x' ;
	R_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	L_IsDraw = 'o' ;
	IsNormal = 'x' ;

	Invalidate () ;
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
				if ( ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 15 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 15 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 15 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 15) ||
						(P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 15 &&
						P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 15 &&
						P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 15 &&
						P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 15) ) ) {
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
					if ( P_Insert.Poly_point.GetAt (i).x <= point.x + 15 &&
						P_Insert.Poly_point.GetAt (i).x >= point.x - 15 &&
						P_Insert.Poly_point.GetAt (i).y <= point.y + 15 &&
						P_Insert.Poly_point.GetAt (i).y >= point.y - 15 ) {
							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
							P_Flag = 'o' ;
					}
				}

				if ( P_Flag == 'x' ) {
					// 원점 Skeleton을 찾으면 커서를 4방향 커서로 변경한다.
					if ( (P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 15 &&
						P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 15 &&
						P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 15 &&
						P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 15) ) {
							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
					}
					// 마지막 Skeleton을 찾으면 커서를 4방향 커서로 변경한다.
					else if ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 15 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 15 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 15 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 15) ) {
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

	LTRT_IsDraw = 'x' ;
	RTLT_IsDraw = 'x' ;
	RRightT_IsDraw = 'x' ;
	RightT_IsDraw = 'x' ;
	RT_IsDraw = 'x' ;
	T_IsDraw = 'x' ;
	L_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	R_IsDraw = 'o' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

// PolyLine 그리기 툴바를 선택한 경우 불리어 집니다.
void CGraphicEditorView::OnDrawpoly()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	LTRT_IsDraw = 'x' ;
	RTLT_IsDraw = 'x' ;
	RRightT_IsDraw = 'x' ;
	RightT_IsDraw = 'x' ;
	RT_IsDraw = 'x' ;
	T_IsDraw = 'x' ;
	L_IsDraw = 'x' ;
	R_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	Invalidate () ;

	P_IsDraw = 'o' ;
	IsNormal = 'x' ;
}

// 원 그리기 툴바를 선택한 경우 불리어 집니다.
void CGraphicEditorView::OnDrawellipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	LTRT_IsDraw = 'x' ;
	RTLT_IsDraw = 'x' ;
	RRightT_IsDraw = 'x' ;
	RightT_IsDraw = 'x' ;
	RT_IsDraw = 'x' ;
	T_IsDraw = 'x' ;
	L_IsDraw = 'x' ;
	R_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'o' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

void CGraphicEditorView::OnSelectobject()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	LTRT_IsDraw = 'x' ;
	RTLT_IsDraw = 'x' ;
	RRightT_IsDraw = 'x' ;
	RightT_IsDraw = 'x' ;
	RT_IsDraw = 'x' ;
	T_IsDraw = 'x' ;
	L_IsDraw = 'x' ;
	R_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	//IsNormal = 'x' ;

	Invalidate () ;
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


void CGraphicEditorView::OnNofillcolor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_IsFillColor = 'x' ;
}

// 세모 그리기 모드
void CGraphicEditorView::OnDrawtriangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	LTRT_IsDraw = 'x' ;
	RTLT_IsDraw = 'x' ;
	RRightT_IsDraw = 'x' ;
	RightT_IsDraw = 'x' ;
	RT_IsDraw = 'x' ;
	T_IsDraw = 'o' ;
	L_IsDraw = 'x' ;
	R_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

// 역 삼각형 그리기 모드
void CGraphicEditorView::OnDrawreversetri()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	LTRT_IsDraw = 'x' ;
	RTLT_IsDraw = 'x' ;
	RRightT_IsDraw = 'x' ;
	RightT_IsDraw = 'x' ;
	RT_IsDraw = 'o' ;
	T_IsDraw = 'x' ;
	L_IsDraw = 'x' ;
	R_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

// 두께 지정 버튼 처리기
void CGraphicEditorView::OnThickness()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CThickness dlg ;

	if( dlg.DoModal() == IDOK )
	{
		m_Thickness = dlg.GetThickness () ;
		m_IsThickness = 'o' ;
	}
}

// 직각 삼각형 그리기 모드
void CGraphicEditorView::OnRightangledtri()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	LTRT_IsDraw = 'x' ;
	RTLT_IsDraw = 'x' ;
	RRightT_IsDraw = 'x' ;
	RightT_IsDraw = 'o' ;
	RT_IsDraw = 'x' ;
	T_IsDraw = 'x' ;
	L_IsDraw = 'x' ;
	R_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

// 역 직각 삼각형 그리기 모드
void CGraphicEditorView::OnRRrightangledtri()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	LTRT_IsDraw = 'x' ;
	RTLT_IsDraw = 'x' ;
	RRightT_IsDraw = 'o' ;
	RightT_IsDraw = 'x' ;
	RT_IsDraw = 'x' ;
	T_IsDraw = 'x' ;
	L_IsDraw = 'x' ;
	R_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

// 오른쪽 -> 왼쪽 삼각형 그리기 모드
void CGraphicEditorView::OnRighttolefttri()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	LTRT_IsDraw = 'x' ;
	RTLT_IsDraw = 'o' ;
	RRightT_IsDraw = 'x' ;
	RightT_IsDraw = 'x' ;
	RT_IsDraw = 'x' ;
	T_IsDraw = 'x' ;
	L_IsDraw = 'x' ;
	R_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

// 왼쪽 -> 오른쪽 삼각형 그리기 모드
void CGraphicEditorView::OnLefttorighttri()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	LTRT_IsDraw = 'o' ;
	RTLT_IsDraw = 'x' ;
	RRightT_IsDraw = 'x' ;
	RightT_IsDraw = 'x' ;
	RT_IsDraw = 'x' ;
	T_IsDraw = 'x' ;
	L_IsDraw = 'x' ;
	R_IsDraw = 'x' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}