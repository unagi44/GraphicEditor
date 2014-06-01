//**************************************************************************************************************
// public of Passion Designers
// GraphicEditor program
// 2010253009 �̰迬
// 2010253026 ������
//**************************************************************************************************************
// GraphicEditorView.cpp : CGraphicEditorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
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
END_MESSAGE_MAP()

// CGraphicEditorView ����/�Ҹ�

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

	IsNormal = 'o' ;
	m_IsColor = 'x' ;
	m_IsFillColor = 'x' ;
	m_IsThickness = 'x' ;

	// �� �׸��⿡ �ʿ��� ������ �ʱ�ȭ
	L_IsDraw = 'x' ;
	L_CanMove = 'x' ;

	// ���� �׸��⿡ �ʿ��� ������ �ʱ�ȭ
	R_IsDraw = 'x' ;
	R_CanMove = 'x' ;

	// PolyLine �׸��⿡ �ʿ��� ������ �ʱ�ȭ
	P_IsDraw = 'x' ;
	P_CanMove = 'x' ;
	P_DrawContinue = 'x' ;
	P_CurrentPoint = 0 ;
	P_IsContinue = 'x' ;
	P_IsStart = 'x' ;
	P_IsMove = 'x' ;
	P_ChangeSkeleton = 0 ;

	// �� �׸��⿡ �ʿ��� ������ �ʱ�ȭ
	E_IsDraw = 'x' ;
	E_CanMove = 'x' ;

	// ���� �׸��⿡ �ʿ��� ������ �ʱ�ȭ
	T_IsDraw = 'x' ;
	T_CanMove = 'x' ;

	// �� �ﰢ�� �׸��⿡ �ʿ��� ������ �ʱ�ȭ
	RT_IsDraw = 'x' ;
	RT_CanMove = 'x' ;

	// ���� �ﰢ�� �׸��⿡ �ʿ��� ������ �ʱ�ȭ
	RightT_IsDraw = 'x' ;
	RightT_CanMove = 'x' ;

	// �� ���� �ﰢ�� �׸��⿡ �ʿ��� ������ �ʱ�ȭ
	RRightT_IsDraw = 'x' ;
	RRightT_CanMove = 'x' ;
}

CGraphicEditorView::~CGraphicEditorView()
{
}

BOOL CGraphicEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CGraphicEditorView �׸���

void CGraphicEditorView::OnDraw(CDC* pDC)
{
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// �׸� ���� ��� ȭ�鿡 ���ϴ�.
	for ( int i = 0 ; i < pDoc -> L_Line.GetCount () ; i++ ) {
		// ������ ������ ���� ����� ���
		if ( pDoc -> L_Line.GetAt (i).L_Color == RGB (0,0,0) ) {
			CPen pen ( PS_SOLID, 1, RGB (0, 0, 0) ) ;
			CPen *Draw_Pen = pDC -> SelectObject(&pen);
			L_Insert.Start = pDoc -> L_Line.GetAt (i).Start ;
			L_Insert.Last = pDoc -> L_Line.GetAt (i).Last ;
			pDC -> MoveTo ( L_Insert.Start ) ;	// ���� ������ġ
			pDC -> LineTo ( L_Insert.Last ) ;	// ���� ������
			pDC->SelectObject(Draw_Pen);
		}
		// Ư�� ������ ������ ����� ���
		else {
			CPen pen ( PS_SOLID, 1, pDoc -> L_Line.GetAt (i).L_Color ) ;
			CPen *Draw_Pen = pDC -> SelectObject(&pen);
			L_Insert.Start = pDoc -> L_Line.GetAt (i).Start ;
			L_Insert.Last = pDoc -> L_Line.GetAt (i).Last ;
			pDC -> MoveTo ( L_Insert.Start ) ;	// ���� ������ġ
			pDC -> LineTo ( L_Insert.Last ) ;	// ���� ������
			pDC->SelectObject(Draw_Pen);
		}
	}

	// �׸� ���ڸ� ��� ȭ�鿡 ���ϴ�.
	for ( int i = 0 ; i < pDoc -> R_Rec.GetCount () ; i++ ) {
		// �� ���� ������ �ʾ��� ����� ���
		if ( pDoc -> R_Color.GetAt (i) == RGB (0,0,0) ) {

			// ä��� ������ ������ �ʾ��� ����� ���
			if ( pDoc -> R_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen;
				pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (i), RGB (0,0,0) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( pDoc -> R_Rec [i].left, pDoc -> R_Rec [i].top, pDoc -> R_Rec [i].right, pDoc -> R_Rec [i].bottom ) ;
				pDC -> SelectObject ( oldPen ) ;
			}
			// ä��� ������ ������ ����� ���
			else {
				CPen pen;
				pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (i), RGB (0,0,0) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;
				pDC -> Rectangle ( pDoc -> R_Rec [i].left, pDoc -> R_Rec [i].top, pDoc -> R_Rec [i].right, pDoc -> R_Rec [i].bottom ) ;
				pDC -> SelectObject ( oldBrush ) ;
				pDC -> SelectObject ( oldPen ) ;
			}
		}
		// Ư�� �� ������ ������ ����� ���
		else {
			
			// ä��� ������ ������ �ʾ��� ����� ���
			if ( pDoc -> R_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen;
				pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (i), pDoc -> R_Color.GetAt (i) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( pDoc -> R_Rec [i].left, pDoc -> R_Rec [i].top, pDoc -> R_Rec [i].right, pDoc -> R_Rec [i].bottom ) ;
				pDC ->SelectObject ( oldPen ) ;
			}
			// ä��� ������ ������ ����� ���
			else {
				CPen pen;
				pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (i), pDoc -> R_Color.GetAt (i) ) ;
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
	
	// �׸� PolyLine�� ��� ȭ�鿡 ���ϴ�.
	for ( int i = 0 ; i < pDoc -> P_Poly.GetCount () ; i++ ) {
		for ( int j = 0 ; j < pDoc -> P_Poly.GetAt (i).Poly_point.GetCount () - 1 ; j++ ) {

			// PolyLine�� ������ ������ ���� ����� ���
			if ( pDoc -> P_Poly.GetAt (i).P_Color == RGB (0,0,0) ) {
				CPen pen ( PS_SOLID, 1, RGB (0, 0, 0) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				P_PointStart = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j) ;
				P_PointLast = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j+1) ;
				pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
				pDC -> LineTo ( P_PointLast ) ;		// ���� ������
				pDC->SelectObject(Draw_Pen);
			}
			// PolyLine�� ������ ������ ������ ����� ���
			else {
				CPen pen ( PS_SOLID, 1, pDoc -> P_Poly.GetAt (i).P_Color ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
				P_PointStart = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j) ;
				P_PointLast = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j+1) ;
				pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
				pDC -> LineTo ( P_PointLast ) ;		// ���� ������
				pDC->SelectObject(Draw_Pen);
			}

			// ���� �׸��� �ִ� PolyLine�� Skeleton�� �����ݴϴ�.
			if ( pDoc -> P_Poly.GetCount () - 1 == i && P_IsDraw == 'o' && P_Insert.Poly_point.GetSize () > 0 ) {
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

	// �׸� ���� ��� ȭ�鿡 ���ϴ�.
	for ( int i = 0 ; i < pDoc -> E_Ellipse.GetCount () ; i++ ) {

		// �� ���� ������ �ʾ��� ����� ���
		if ( pDoc -> E_Color.GetAt (i) == RGB (0,0,0) ) {
			// ä��� ������ ������ �ʾ��� ����� ���
			if ( pDoc -> E_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen;
				pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (i), RGB (0,0,0) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Ellipse ( pDoc -> E_Ellipse [i].left, pDoc -> E_Ellipse [i].top, pDoc -> E_Ellipse [i].right, pDoc -> E_Ellipse [i].bottom ) ;
				pDC -> SelectObject ( oldPen ) ;
			}
			// ä��� ������ ������ ����� ���
			else {
				CPen pen;
				pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (i), RGB (0,0,0) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;
				pDC -> Ellipse ( pDoc -> E_Ellipse [i].left, pDoc -> E_Ellipse [i].top, pDoc -> E_Ellipse [i].right, pDoc -> E_Ellipse [i].bottom ) ;
				pDC -> SelectObject ( oldBrush ) ;
				pDC -> SelectObject ( oldPen ) ;
			}
		}
		// Ư�� �� ������ ������ ����� ���
		else {
			// ä��� ������ ������ �ʾ��� ����� ���
			if ( pDoc -> E_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen;
				pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (i), pDoc -> E_Color.GetAt (i) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Ellipse ( pDoc -> E_Ellipse [i].left, pDoc -> E_Ellipse [i].top, pDoc -> E_Ellipse [i].right, pDoc -> E_Ellipse [i].bottom ) ;
				pDC -> SelectObject ( oldPen ) ;
			}
			// ä��� ������ ������ ����� ���
			else {
				CPen pen;
				pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (i), pDoc -> E_Color.GetAt (i) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;
				pDC -> Ellipse ( pDoc -> E_Ellipse [i].left, pDoc -> E_Ellipse [i].top, pDoc -> E_Ellipse [i].right, pDoc -> E_Ellipse [i].bottom ) ;
				pDC -> SelectObject ( oldPen ) ;
				pDC -> SelectObject ( oldBrush ) ;
			}
		}

		// ���� ���� �׸��� �ִ� ���¶�� �׵θ� ���簢���� �׷��ݴϴ�.
		if ( pDoc -> E_Ellipse.GetCount () - 1 == i && E_CanMove == 'o' ) {
			CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
			CPen *Draw_Pen = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> E_Ellipse.GetAt (i).left - pDoc -> E_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> E_Ellipse.GetAt (i).top  - pDoc -> E_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> E_Ellipse.GetAt (i).right + pDoc -> E_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> E_Ellipse.GetAt (i).top - pDoc -> E_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen);
;
			CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> E_Ellipse.GetAt (i).left - pDoc -> E_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> E_Ellipse.GetAt (i).top - pDoc -> E_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> E_Ellipse.GetAt (i).left - pDoc -> E_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> E_Ellipse.GetAt (i).bottom + pDoc -> E_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen2);

			CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> E_Ellipse.GetAt (i).left - pDoc -> E_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> E_Ellipse.GetAt (i).bottom + pDoc -> E_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> E_Ellipse.GetAt (i).right + pDoc -> E_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> E_Ellipse.GetAt (i).bottom + pDoc -> E_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen3);

			CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> E_Ellipse.GetAt (i).right + pDoc -> E_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> E_Ellipse.GetAt (i).top - pDoc -> E_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> E_Ellipse.GetAt (i).right + pDoc -> E_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> E_Ellipse.GetAt (i).bottom + pDoc -> E_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen4);
		}
	}

	// �׸� ���� ��� ȭ�鿡 ���ϴ�.
	for ( int i = 0 ; i < pDoc -> T_Triangle.GetCount () ; i++ ) {

		// �׸� ������ �� Point ��ǥ
		POINT T_Point[3] = { {pDoc -> T_Triangle.GetAt (i).left + (pDoc -> T_Triangle.GetAt (i).right - pDoc -> T_Triangle.GetAt (i).left) / 2,
							  pDoc -> T_Triangle.GetAt (i).top}, {pDoc -> T_Triangle.GetAt (i).left, pDoc -> T_Triangle.GetAt (i).bottom},
							 {pDoc -> T_Triangle.GetAt (i).right, pDoc -> T_Triangle.GetAt (i).bottom} } ;

		// �� ���� ������ �ʾ��� ����� ���
		if ( pDoc -> T_Color.GetAt (i) == RGB (0,0,0) ) {

			// ä��� ������ ������ �ʾ��� ����� ���
			if ( pDoc -> T_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen;
				pen.CreatePen( PS_SOLID, pDoc -> T_Thickness.GetAt (i), RGB (0,0,0) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Polygon ( T_Point, 3 ) ;
				pDC -> SelectObject ( oldPen ) ;
			}
			// ä��� ������ ������ ����� ���
			else {
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> T_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;
				CPen pen ( PS_SOLID, pDoc -> T_Thickness.GetAt (i), RGB (0, 0, 0) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);

				pDC -> Polygon ( T_Point, 3 ) ;

				pDC->SelectObject ( Draw_Pen ) ;
				pDC -> SelectObject ( oldBrush ) ;
			}
		}
		// Ư�� �� ������ ������ ����� ���
		else {
			
			// ä��� ������ ������ �ʾ��� ����� ���
			if ( pDoc -> T_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen ( PS_SOLID, pDoc -> T_Thickness.GetAt (i), pDoc -> T_Color.GetAt (i) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Polygon ( T_Point, 3 ) ;

				pDC->SelectObject(Draw_Pen);
			}
			// ä��� ������ ������ ����� ���
			else {

				CPen pen ( PS_SOLID, pDoc -> T_Thickness.GetAt (i), pDoc -> T_Color.GetAt (i) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> T_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;

				pDC -> Polygon ( T_Point, 3 ) ;

				pDC->SelectObject(Draw_Pen);
				pDC -> SelectObject ( oldBrush ) ;		
			}
		}

		// ���� ���� �׸��� �ִ� ���¶�� �׵θ� ���簢���� �׷��ݴϴ�.
		if ( pDoc -> T_Triangle.GetCount () - 1 == i && T_CanMove == 'o' ) {
			CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
			CPen *Draw_Pen = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> T_Triangle.GetAt (i).left - pDoc -> T_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> T_Triangle.GetAt (i).top - pDoc -> T_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> T_Triangle.GetAt (i).right + pDoc -> T_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> T_Triangle.GetAt (i).top - pDoc -> T_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen);
;
			CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> T_Triangle.GetAt (i).left - pDoc -> T_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> T_Triangle.GetAt (i).top - pDoc -> T_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> T_Triangle.GetAt (i).left - pDoc -> T_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> T_Triangle.GetAt (i).bottom + pDoc -> T_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen2);

			CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> T_Triangle.GetAt (i).right + pDoc -> T_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> T_Triangle.GetAt (i).top - pDoc -> T_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> T_Triangle.GetAt (i).right + pDoc -> T_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> T_Triangle.GetAt (i).bottom + pDoc -> T_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen4);
		}
	}

	// �׸� �� �ﰢ���� ��� ȭ�鿡 ���ϴ�.
	for ( int i = 0 ; i < pDoc -> RT_Triangle.GetCount () ; i++ ) {

		// �׸� ������ �� Point ��ǥ
		POINT RT_Point[3] = { {pDoc -> RT_Triangle.GetAt (i).left + (pDoc -> RT_Triangle.GetAt (i).right - pDoc -> RT_Triangle.GetAt (i).left) / 2,
							   pDoc -> RT_Triangle.GetAt (i).bottom}, {pDoc -> RT_Triangle.GetAt (i).left, pDoc -> RT_Triangle.GetAt (i).top},
							  {pDoc -> RT_Triangle.GetAt (i).right, pDoc -> RT_Triangle.GetAt (i).top} } ;

		// �� ���� ������ �ʾ��� ����� ���
		if ( pDoc -> RT_Color.GetAt (i) == RGB (0,0,0) ) {

			// ä��� ������ ������ �ʾ��� ����� ���
			if ( pDoc -> RT_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen;
				pen.CreatePen( PS_SOLID, pDoc -> RT_Thickness.GetAt (i), RGB (0,0,0) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Polygon ( RT_Point, 3 ) ;
				pDC -> SelectObject ( oldPen ) ;
			}
			// ä��� ������ ������ ����� ���
			else {
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> RT_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;
				CPen pen ( PS_SOLID, pDoc -> RT_Thickness.GetAt (i), RGB (0, 0, 0) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);

				pDC -> Polygon ( RT_Point, 3 ) ;

				pDC->SelectObject ( Draw_Pen ) ;
				pDC -> SelectObject ( oldBrush ) ;
			}
		}
		// Ư�� �� ������ ������ ����� ���
		else {
			
			// ä��� ������ ������ �ʾ��� ����� ���
			if ( pDoc -> RT_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen ( PS_SOLID, pDoc -> RT_Thickness.GetAt (i), pDoc -> RT_Color.GetAt (i) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Polygon ( RT_Point, 3 ) ;

				pDC->SelectObject(Draw_Pen);
			}
			// ä��� ������ ������ ����� ���
			else {

				CPen pen ( PS_SOLID, pDoc -> RT_Thickness.GetAt (i), pDoc -> RT_Color.GetAt (i) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
				CBrush brush;
				brush.CreateSolidBrush ( pDoc -> RT_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;

				pDC -> Polygon ( RT_Point, 3 ) ;

				pDC->SelectObject(Draw_Pen);
				pDC -> SelectObject ( oldBrush ) ;		
			}
		}

		// ���� �� �ﰢ���� �׸��� �ִ� ���¶�� �׵θ� ���簢���� �׷��ݴϴ�.
		if ( pDoc -> RT_Triangle.GetCount () - 1 == i && RT_CanMove == 'o' ) {
			CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
			CPen *Draw_Pen = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> RT_Triangle.GetAt (i).left - pDoc -> RT_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> RT_Triangle.GetAt (i).bottom + pDoc -> RT_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> RT_Triangle.GetAt (i).right + pDoc -> RT_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> RT_Triangle.GetAt (i).bottom + pDoc -> RT_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen);
;
			CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> RT_Triangle.GetAt (i).left - pDoc -> RT_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> RT_Triangle.GetAt (i).top - pDoc -> RT_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> RT_Triangle.GetAt (i).left - pDoc -> RT_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> RT_Triangle.GetAt (i).bottom + pDoc -> RT_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen2);

			CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> RT_Triangle.GetAt (i).right + pDoc -> RT_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> RT_Triangle.GetAt (i).top - pDoc -> RT_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> RT_Triangle.GetAt (i).right + pDoc -> RT_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> RT_Triangle.GetAt (i).bottom + pDoc -> RT_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen4);
		}
	}

	// �׸� ���� �ﰢ���� ��� ȭ�鿡 ���ϴ�.
	for ( int i = 0 ; i < pDoc -> RightT_Triangle.GetCount () ; i++ ) {

		// �׸� ���� �ﰢ���� �� Point ��ǥ
		POINT RightT_Point[3] = { {pDoc -> RightT_Triangle.GetAt (i).right, pDoc -> RightT_Triangle.GetAt (i).top},
								  {pDoc -> RightT_Triangle.GetAt (i).left, pDoc -> RightT_Triangle.GetAt (i).bottom},
								  {pDoc -> RightT_Triangle.GetAt (i).right, pDoc -> RightT_Triangle.GetAt (i).bottom} } ;

		// �� ���� ������ �ʾ��� ����� ���
		if ( pDoc -> RightT_Color.GetAt (i) == RGB (0,0,0) ) {

			// ä��� ������ ������ �ʾ��� ����� ���
			if ( pDoc -> RightT_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen;
				pen.CreatePen( PS_SOLID, pDoc -> RightT_Thickness.GetAt (i), RGB (0,0,0) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Polygon ( RightT_Point, 3 ) ;
				pDC -> SelectObject ( oldPen ) ;
			}
			// ä��� ������ ������ ����� ���
			else {
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> RightT_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;
				CPen pen ( PS_SOLID, pDoc -> RightT_Thickness.GetAt (i), RGB (0, 0, 0) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);

				pDC -> Polygon ( RightT_Point, 3 ) ;

				pDC->SelectObject ( Draw_Pen ) ;
				pDC -> SelectObject ( oldBrush ) ;
			}
		}
		// Ư�� �� ������ ������ ����� ���
		else {
			
			// ä��� ������ ������ �ʾ��� ����� ���
			if ( pDoc -> RightT_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen ( PS_SOLID, pDoc -> RightT_Thickness.GetAt (i), pDoc -> RightT_Color.GetAt (i) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Polygon ( RightT_Point, 3 ) ;

				pDC->SelectObject(Draw_Pen);
			}
			// ä��� ������ ������ ����� ���
			else {

				CPen pen ( PS_SOLID, pDoc -> RightT_Thickness.GetAt (i), pDoc -> RightT_Color.GetAt (i) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> RightT_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;

				pDC -> Polygon ( RightT_Point, 3 ) ;

				pDC->SelectObject(Draw_Pen);
				pDC -> SelectObject ( oldBrush ) ;		
			}
		}

		// ���� ���� �ﰢ���� �׸��� �ִ� ���¶�� �׵θ� ���簢���� �׷��ݴϴ�.
		if ( pDoc -> RightT_Triangle.GetCount () - 1 == i && RightT_CanMove == 'o' ) {
			CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
			CPen *Draw_Pen = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> RightT_Triangle.GetAt (i).left - pDoc -> RightT_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> RightT_Triangle.GetAt (i).top - pDoc -> RightT_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> RightT_Triangle.GetAt (i).right + pDoc -> RightT_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> RightT_Triangle.GetAt (i).top - pDoc -> RightT_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen);
;
			CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> RightT_Triangle.GetAt (i).left - pDoc -> RightT_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> RightT_Triangle.GetAt (i).top - pDoc -> RightT_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> RightT_Triangle.GetAt (i).left - pDoc -> RightT_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> RightT_Triangle.GetAt (i).bottom + pDoc -> RightT_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen2);
		}
	}

	// �׸� �� ���� �ﰢ���� ��� ȭ�鿡 ���ϴ�.
	for ( int i = 0 ; i < pDoc -> RRightT_Triangle.GetCount () ; i++ ) {

		// �׸� �� ���� ������ �� Point ��ǥ
		POINT RRightT_Point[3] = { {pDoc -> RRightT_Triangle.GetAt (i).left, pDoc -> RRightT_Triangle.GetAt (i).top},
								   {pDoc -> RRightT_Triangle.GetAt (i).left, pDoc -> RRightT_Triangle.GetAt (i).bottom},
								   {pDoc -> RRightT_Triangle.GetAt (i).right, pDoc -> RRightT_Triangle.GetAt (i).top} } ;

		// �� ���� ������ �ʾ��� ����� ���
		if ( pDoc -> RRightT_Color.GetAt (i) == RGB (0,0,0) ) {

			// ä��� ������ ������ �ʾ��� ����� ���
			if ( pDoc -> RRightT_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen;
				pen.CreatePen( PS_SOLID, pDoc -> RRightT_Thickness.GetAt (i), RGB (0,0,0) ) ;
				CPen* oldPen = pDC->SelectObject( &pen ) ;
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Polygon ( RRightT_Point, 3 ) ;
				pDC -> SelectObject ( oldPen ) ;
			}
			// ä��� ������ ������ ����� ���
			else {
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> RRightT_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;
				CPen pen ( PS_SOLID, pDoc -> RRightT_Thickness.GetAt (i), RGB (0, 0, 0) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);

				pDC -> Polygon ( RRightT_Point, 3 ) ;

				pDC->SelectObject ( Draw_Pen ) ;
				pDC -> SelectObject ( oldBrush ) ;
			}
		}
		// Ư�� �� ������ ������ ����� ���
		else {
			
			// ä��� ������ ������ �ʾ��� ����� ���
			if ( pDoc -> RRightT_FillColor.GetAt (i) == RGB (0,0,0) ) {
				CPen pen ( PS_SOLID, pDoc -> RRightT_Thickness.GetAt (i), pDoc -> RRightT_Color.GetAt (i) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Polygon ( RRightT_Point, 3 ) ;

				pDC->SelectObject(Draw_Pen);
			}
			// ä��� ������ ������ ����� ���
			else {

				CPen pen ( PS_SOLID, pDoc -> RRightT_Thickness.GetAt (i), pDoc -> RRightT_Color.GetAt (i) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				CBrush brush;
				brush.CreateSolidBrush( pDoc -> RRightT_FillColor.GetAt (i) ) ;
				CBrush* oldBrush = pDC->SelectObject( &brush ) ;

				pDC -> Polygon ( RRightT_Point, 3 ) ;

				pDC->SelectObject(Draw_Pen);
				pDC -> SelectObject ( oldBrush ) ;		
			}
		}

		// ���� �� ���� �ﰢ���� �׸��� �ִ� ���¶�� �׵θ� ���簢���� �׷��ݴϴ�.
		if ( pDoc -> RRightT_Triangle.GetCount () - 1 == i && RRightT_CanMove == 'o' ) {
			CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
			CPen *Draw_Pen = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (i).right + pDoc -> RRightT_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (i).top - pDoc -> RRightT_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (i).right + pDoc -> RRightT_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (i).bottom + pDoc -> RRightT_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen);
;
			CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (i).left - pDoc -> RRightT_Thickness.GetAt (i) / 2 ;
			P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (i).bottom + pDoc -> RRightT_Thickness.GetAt (i) / 2 ;
			P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (i).right + pDoc -> RRightT_Thickness.GetAt (i) / 2 ;
			P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (i).bottom + pDoc -> RRightT_Thickness.GetAt (i) / 2 ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen2);
		}
	}
}

void CGraphicEditorView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �� ���� ��ü ũ�⸦ ����մϴ�.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CGraphicEditorView �μ�

BOOL CGraphicEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CGraphicEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CGraphicEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CGraphicEditorView ����

#ifdef _DEBUG
void CGraphicEditorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphicEditorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGraphicEditorDoc* CGraphicEditorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditorDoc)));
	return (CGraphicEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicEditorView �޽��� ó����

void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// ���� �׸��� ���
	if ( L_IsDraw == 'o' ) {
		L_Insert.Start = L_Insert.Last = point ;
		pDoc->L_Line.Add ( L_Insert ) ;
		L_Current = pDoc -> L_Line.GetCount () - 1 ;
		L_CanMove = 'o' ;
	}
	// ���ڸ� �׸��� ���
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

		// �β� ������ �� ���
		if ( m_IsThickness == 'o' )
			pDoc -> R_Thickness.Add ( m_Thickness ) ;
		// �β� ������ ���� ���� ���
		else if ( m_IsThickness == 'x' )
			pDoc -> R_Thickness.Add (1) ;
	}
	// PolyLine�� ����ؼ� �׸��� ���
	else if ( P_IsContinue == 'o') {
		// PolyLine�� Skeleton�� 2���� ���
		if ( P_CurrentPoint == 1 ) {
			// ������ ������������ �����Ϸ��� ��쿣 ��� �׸��� �ְ� �Ѵ�.
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
		// PolyLine�� Skeleton�� 3�� �̻��� ���
		else {
			// ����, ������ Skeleton�� ������ ��� Skeleton�� �˻��Ͽ�
			// Ŭ���� ��ǥ�� �ش� Skeleton �߿� �ִ��� Ȯ���Ѵ�.
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
				// ���� Skeleton�� �ǵ帮�� ���� ���� �����Ѵ�.
				if ( (P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 8 &&
					P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 8 &&
					P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 8 &&
					P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 8) ) {
						P_IsStart = 'o' ;
						P_CanMove = 'o' ;
				}
				// ������ Skeleton�� �ǵ帮�� �� Skeleton�� �����Ѵ�.
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
	// PolyLine �׸��� ��, �� ó�� Skeleton�� Ŭ���Ͽ� ���� ����Դϴ�.
	else if ( P_IsDraw == 'o' && P_IsContinue == 'x' ) {
		P_Insert.Poly_point.Add ( point ) ;
		P_Current = pDoc -> P_Poly.GetCount () ;
		pDoc -> P_Poly.SetSize (P_Current + 1) ;
		pDoc -> P_Poly.GetAt (P_Current).Poly_point.Add ( point ) ;
		P_CurrentPoint = P_Insert.Poly_point.GetCount () ;
		P_CanMove = 'o' ;
		P_IsContinue = 'o' ;

		// ���� ������ �����ϰ� �׷��� ��� ���� ������ ���.
		if ( m_IsColor == 'o' )
			pDoc -> P_Poly.GetAt ( P_Current ).P_Color = m_Color ;
		// ������ �������� �ʰ� �׷��� ��� ǥ�� ���� ���.
		else if ( m_IsColor == 'x' )
			pDoc -> P_Poly.GetAt ( P_Current ).P_Color = RGB (0,0,0) ;
	}
	// ���� �׸��� ���
	else if ( E_IsDraw == 'o' ) {
		E_Insert.left = point.x ;
		E_Insert.right = point.x ;
		E_Insert.top = point.y ;
		E_Insert.bottom = point.y ;

		pDoc -> E_Ellipse.Add ( E_Insert ) ;
		R_Current = pDoc -> E_Ellipse.GetCount () - 1 ;
		E_CanMove = 'o' ;

		// ���� ������ �����ϰ� �׷��� ��� ���� ������ ���.
		if ( m_IsColor == 'o' )
			pDoc -> E_Color.Add ( m_Color ) ;
		// ������ �������� �ʰ� �׷��� ��� ǥ�� ���� ���.
		else if ( m_IsColor == 'x' )
			pDoc -> E_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> E_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> E_FillColor.Add ( RGB(0,0,0) ) ;

		// �β� ������ �� ���
		if ( m_IsThickness == 'o' )
			pDoc -> E_Thickness.Add ( m_Thickness ) ;
		// �β� ������ ���� ���� ���
		else if ( m_IsThickness == 'x' )
			pDoc -> E_Thickness.Add (1) ;
	}
	// ���� �׸��� ���
	else if ( T_IsDraw == 'o' ) {
		T_Insert.left = point.x ;
		T_Insert.right = point.x ;
		T_Insert.top = point.y ;
		T_Insert.bottom = point.y ;

		pDoc -> T_Triangle.Add ( T_Insert ) ;
		T_Current = pDoc -> T_Triangle.GetCount () - 1 ;
		T_CanMove = 'o' ;

		// ���� ������ �����ϰ� �׷��� ��� ���� ������ ���.
		if ( m_IsColor == 'o' )
			pDoc -> T_Color.Add ( m_Color ) ;
		// ������ �������� �ʰ� �׷��� ��� ǥ�� ���� ���.
		else if ( m_IsColor == 'x' )
			pDoc -> T_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> T_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> T_FillColor.Add ( RGB(0,0,0) ) ;

		// �β� ������ �� ���
		if ( m_IsThickness == 'o' )
			pDoc -> T_Thickness.Add ( m_Thickness ) ;
		// �β� ������ ���� ���� ���
		else if ( m_IsThickness == 'x' )
			pDoc -> T_Thickness.Add (1) ;
	}
	// �� �ﰢ���� �׸��� ���
	else if ( RT_IsDraw == 'o' ) {
		RT_Insert.left = point.x ;
		RT_Insert.right = point.x ;
		RT_Insert.top = point.y ;
		RT_Insert.bottom = point.y ;

		pDoc -> RT_Triangle.Add ( RT_Insert ) ;
		RT_Current = pDoc -> RT_Triangle.GetCount () - 1 ;
		RT_CanMove = 'o' ;

		// ���� ������ �����ϰ� �׷��� ��� ���� ������ ���.
		if ( m_IsColor == 'o' )
			pDoc -> RT_Color.Add ( m_Color ) ;
		// ������ �������� �ʰ� �׷��� ��� ǥ�� ���� ���.
		else if ( m_IsColor == 'x' )
			pDoc -> RT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> RT_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> RT_FillColor.Add ( RGB(0,0,0) ) ;

		// �β� ������ �� ���
		if ( m_IsThickness == 'o' )
			pDoc -> RT_Thickness.Add ( m_Thickness ) ;
		// �β� ������ ���� ���� ���
		else if ( m_IsThickness == 'x' )
			pDoc -> RT_Thickness.Add (1) ;
	}
	// ���� �ﰢ���� �׸��� ���
	else if ( RightT_IsDraw == 'o' ) {
		RightT_Insert.left = point.x ;
		RightT_Insert.right = point.x ;
		RightT_Insert.top = point.y ;
		RightT_Insert.bottom = point.y ;

		pDoc -> RightT_Triangle.Add ( RightT_Insert ) ;
		RightT_Current = pDoc -> RightT_Triangle.GetCount () - 1 ;
		RightT_CanMove = 'o' ;

		// ���� ������ �����ϰ� �׷��� ��� ���� ������ ���.
		if ( m_IsColor == 'o' )
			pDoc -> RightT_Color.Add ( m_Color ) ;
		// ������ �������� �ʰ� �׷��� ��� ǥ�� ���� ���.
		else if ( m_IsColor == 'x' )
			pDoc -> RightT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> RightT_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> RightT_FillColor.Add ( RGB(0,0,0) ) ;

		// �β� ������ �� ���
		if ( m_IsThickness == 'o' )
			pDoc -> RightT_Thickness.Add ( m_Thickness ) ;
		// �β� ������ ���� ���� ���
		else if ( m_IsThickness == 'x' )
			pDoc -> RightT_Thickness.Add (1) ;
	}
	// �� ���� �ﰢ���� �׸��� ���
	else if ( RRightT_IsDraw == 'o' ) {
		RRightT_Insert.left = point.x ;
		RRightT_Insert.right = point.x ;
		RRightT_Insert.top = point.y ;
		RRightT_Insert.bottom = point.y ;

		pDoc -> RRightT_Triangle.Add ( RRightT_Insert ) ;
		RRightT_Current = pDoc -> RRightT_Triangle.GetCount () - 1 ;
		RRightT_CanMove = 'o' ;

		// ���� ������ �����ϰ� �׷��� ��� ���� ������ ���.
		if ( m_IsColor == 'o' )
			pDoc -> RRightT_Color.Add ( m_Color ) ;
		// ������ �������� �ʰ� �׷��� ��� ǥ�� ���� ���.
		else if ( m_IsColor == 'x' )
			pDoc -> RRightT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> RRightT_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> RRightT_FillColor.Add ( RGB(0,0,0) ) ;

		// �β� ������ �� ���
		if ( m_IsThickness == 'o' )
			pDoc -> RRightT_Thickness.Add ( m_Thickness ) ;
		// �β� ������ ���� ���� ���
		else if ( m_IsThickness == 'x' )
			pDoc -> RRightT_Thickness.Add (1) ;
	}

	CScrollView::OnLButtonDown(nFlags, point);
}


void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// �� �׸��� ������ �巡�� �ϴ� ���
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
	// ���� �׸��� ������ �巡�� �ϴ� ���
	else if ( R_CanMove == 'o' ) {
		R_Rect.right = point.x ;
		R_Rect.bottom = point.y ;

		pDoc->R_Rec.SetAt ( R_Current, R_Rect ) ;
		Invalidate () ;
	}
	// PolyLine �׸��� ������ �巡�� �ϴ� ���
	else if ( P_CanMove == 'o' ) {

		// ������ Skeleton�� Ŭ���Ͽ� ���� �ϴ� ���
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

		// ù ��°, ������ Skeleton�� ������ �κ��� ���� �ϴ� ���
		else if ( P_ChangeSkeleton > 0 ) {
			P_Insert.Poly_point.SetAt ( P_ChangeSkeleton, point ) ;
			pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( P_ChangeSkeleton, point ) ;
			Invalidate () ;
			P_IsMove = 'o' ;
		}

		// ù ��° Skeleton�� ���� �ϴ� ���
		else if ( P_IsStart == 'o' ) {
			P_Insert.Poly_point.SetAt ( 0, point ) ;
			pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( 0, point ) ;
			Invalidate () ;
			P_IsMove = 'o' ;
		}
	}
	// �� �׸��� ������ �巡�� �ϴ� ���
	else if ( E_CanMove == 'o' ) {
		E_Insert.right = point.x ;
		E_Insert.bottom = point.y ;

		pDoc->E_Ellipse.SetAt ( R_Current, E_Insert ) ;
		Invalidate () ;
	}
	// ���� �׸��� ������ �巡�� �ϴ� ���
	else if ( T_CanMove == 'o' ) {
		T_Insert.right = point.x ;
		T_Insert.bottom = point.y ;

		pDoc->T_Triangle.SetAt ( T_Current, T_Insert ) ;
		Invalidate () ;
	}
	// �� �ﰢ�� �׸��� ������ �巡�� �ϴ� ���
	else if ( RT_CanMove == 'o' ) {
		RT_Insert.right = point.x ;
		RT_Insert.bottom = point.y ;

		pDoc->RT_Triangle.SetAt ( RT_Current, RT_Insert ) ;
		Invalidate () ;
	}
	// ���� �ﰢ�� �׸��� ������ �巡�� �ϴ� ���
	else if ( RightT_CanMove == 'o' ) {
		RightT_Insert.right = point.x ;
		RightT_Insert.bottom = point.y ;

		pDoc->RightT_Triangle.SetAt ( RightT_Current, RightT_Insert ) ;
		Invalidate () ;
	}
	// �� ���� �ﰢ�� �׸��� ������ �巡�� �ϴ� ���
	else if ( RRightT_CanMove == 'o' ) {
		RRightT_Insert.right = point.x ;
		RRightT_Insert.bottom = point.y ;

		pDoc->RRightT_Triangle.SetAt ( RRightT_Current, RRightT_Insert ) ;
		Invalidate () ;
	}
	
	CScrollView::OnMouseMove(nFlags, point);
}


void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// ���� �׸��� Ŭ���� �� ���
	if ( L_IsDraw == 'o' ) {
		L_Insert.Last = point ;
		if ( m_IsColor == 'o' )
			L_Insert.L_Color = m_Color ;
		else
			L_Insert.L_Color = RGB (0,0,0) ;

		pDoc->L_Line.SetAt ( L_Current, L_Insert ) ;
		Invalidate () ;
		L_IsDraw = 'x' ;
		L_CanMove = 'x' ;
		IsNormal = 'o' ;
	}
	// ���ڸ� �׸��� Ŭ���� �� ���
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
	// PolyLine�� �׸��� Ŭ���� �� ���
	else if ( P_IsDraw == 'o' ) {
		// ���� ���� ��ǥ�� Ŭ��, ���� ��� �׸��� ���
		if ( P_IsMove == 'x' ) {
			P_CanMove = 'x' ; P_IsStart = 'x' ;
			P_Insert.Poly_point.RemoveAll () ;
			P_CanMove = 'x' ;
			P_IsContinue = 'x' ;
			P_IsDraw = 'x' ;
			IsNormal = 'o' ;
			Invalidate () ;
		}
		// ���� ��ǥ�� Ŭ��, �� ��찡 �ƴ϶�� �׸��� ���
		else {
			// ���� ������ Skeleton�� ������ ���
			if ( P_IsStart == 'x' && P_ChangeSkeleton == 0 ) {
				P_Insert.Poly_point.SetAt ( P_CurrentPoint, point ) ;
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( P_CurrentPoint, point ) ;
				Invalidate () ;
			}
			// ���� ù��° Skeleton�� ������ ���
			else if ( P_IsStart == 'o' ) {
				P_Insert.Poly_point.SetAt ( 0, point ) ;
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( 0, point ) ;
				Invalidate () ;
				P_IsStart = 'x' ;
			}
			// ���� ù��°, ������ Skeleton�� �ٸ� Skeleton�� ������ ���
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
	// ���� �׸��� Ŭ���� �� ���
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
	// ���� �׸��� Ŭ���� �� ���
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
	// �� �ﰢ���� �׸��� Ŭ���� �� ���
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
	// ���� �ﰢ���� �׸��� Ŭ���� �� ���
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
	// �� ���� �ﰢ���� �׸��� Ŭ���� �� ���
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

	CScrollView::OnLButtonUp(nFlags, point);
}

// �� �׸��� ���ٸ� ������ ��� �Ҹ��� ���ϴ�.
void CGraphicEditorView::OnDrawline()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (nHitTest == HTCLIENT) {
		CPoint point ;
		::GetCursorPos ( &point ) ;	// ��ũ�� ��ǥ
		ScreenToClient ( &point ) ;	// Ŭ���̾�Ʈ ��ǥ�� ��ȯ

		// ���ÿ� �⺻ Ŀ���� ��ȯ �մϴ�.
		if ( IsNormal == 'o' )
			::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_ARROW)) ;
		// PolyLine�� ����ؼ� �׸��� ���
		else if ( P_IsContinue == 'o' && P_CanMove == 'x' ) {
			// PolyLine�� Skeleton�� 2���� ���
			if ( P_CurrentPoint == 1 ) {
				// ������ ������������ �����Ϸ��� ��쿡 ���� Ŀ���� ���� �Ѵ�.
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
				// �ƴ� ��쿣 ���ڰ� Ŀ���� ����
				else {
					::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_CROSS)) ;
				}
			}
			// PolyLine�� Skeleton�� 3�� �̻��� ���
			else {
				// ����, ������ Skeleton�� ������ ��� Skeleton�� �˻��Ͽ�
				// Ŀ���� ��ǥ�� �ش� Skeleton �߿� �ִ��� Ȯ���Ѵ�.
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
					// ���� Skeleton�� ã���� Ŀ���� 4���� Ŀ���� �����Ѵ�.
					if ( (P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 8 &&
						P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 8 &&
						P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 8 &&
						P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 8) ) {
							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
					}
					// ������ Skeleton�� ã���� Ŀ���� 4���� Ŀ���� �����Ѵ�.
					else if ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 8 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 8 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 8 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 8) ) {
							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
					}
					// Skeleton �ֺ��� ���ٸ� ���ڰ��� Ŀ���� ��ȯ�Ѵ�.
					else {
						::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_CROSS)) ;
					}
				}
			}
		}
		// �׸��� ��忡�� Ŀ���� ���������� ���մϴ�.
		else if ( IsNormal == 'x' ) {
			::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_CROSS)) ;
		}
		return TRUE ;
	}

	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

// ���� �׸��� ���ٸ� ������ ��� �Ҹ��� ���ϴ�.
void CGraphicEditorView::OnDrawrec()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

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

// PolyLine �׸��� ���ٸ� ������ ��� �Ҹ��� ���ϴ�.
void CGraphicEditorView::OnDrawpoly()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

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

// �� �׸��� ���ٸ� ������ ��� �Ҹ��� ���ϴ�.
void CGraphicEditorView::OnDrawellipse()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlgColor(0, CC_FULLOPEN, NULL);
	if( dlgColor.DoModal() == IDOK )
	{
		m_Color = dlgColor.GetColor();
		m_IsColor = 'o' ;
	}
}


void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	// ���� Ŭ���� ��� PolyLine�� ������.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlgColor(0, CC_FULLOPEN, NULL);
	if( dlgColor.DoModal() == IDOK )
	{
		m_FillColor = dlgColor.GetColor();
		m_IsFillColor = 'o' ;
	}
}


void CGraphicEditorView::OnNofillcolor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_IsFillColor = 'x' ;
}


void CGraphicEditorView::OnDrawtriangle()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
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


void CGraphicEditorView::OnDrawreversetri()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

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

void CGraphicEditorView::OnThickness()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CThickness dlg ;

	if( dlg.DoModal() == IDOK )
	{
		m_Thickness = dlg.GetThickness () ;
		m_IsThickness = 'o' ;
	}
}


void CGraphicEditorView::OnRightangledtri()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

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

void CGraphicEditorView::OnRRrightangledtri()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

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