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
ON_COMMAND(ID_RightToLeftTri, &CGraphicEditorView::OnRighttolefttri)
ON_COMMAND(ID_LeftToRightTri, &CGraphicEditorView::OnLefttorighttri)
ON_COMMAND(ID_Font, &CGraphicEditorView::OnFont)
//ON_UPDATE_COMMAND_UI(ID_Font, &CGraphicEditorView::OnUpdateFont)
ON_COMMAND(ID_Text, &CGraphicEditorView::OnText)
ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGraphicEditorView ����/�Ҹ�

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

	IsNormal = 'o' ;
	m_IsColor = 'x' ;
	m_IsFillColor = 'x' ;
	m_IsThickness = 'x' ;

	// �̵� ���ٿ� �ʿ��� ���� �ʱ�ȭ
	M_IsMove = 'x' ;
	M_IsSelect = 'x' ;

	// �ؽ�Ʈ ���Կ� �ʿ��� ���� �ʱ�ȭ
	Text_IsText = 'x' ;
	Text_IsFont = 'x' ;

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
	P_IsSkeletonStart = 'x' ;

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

	// ���� -> ������ �ﰢ�� �׸��⿡ �ʿ��� ������ �ʱ�ȭ
	LTRT_IsDraw = 'x' ;
	LTRT_CanMove = 'x' ;

	// ������ -> ���� �ﰢ�� �׸��⿡ �ʿ��� ������ �ʱ�ȭ
	RTLT_IsDraw = 'x' ;
	RTLT_CanMove = 'x' ;
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
	int Text_Number = 0 ;

	// ��� ��ü�� ����ŭ ����� �մϴ�.
	// �׸� ������ ���� ��µ˴ϴ�.
	for ( int i = 0 ; i < pDoc->What.GetCount () ; i++ ) {

		// �� ��ü�� ���
		if ( pDoc -> What.GetAt (i) == _T ("L") ) {
			// ������ ������ ���� ����� ���
			if ( pDoc -> L_Line.GetAt (L_Number).L_Color == RGB (0,0,0) ) {
				CPen pen ( PS_SOLID, pDoc -> L_Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
				L_Insert.Last = pDoc -> L_Line.GetAt (L_Number).Last ;
				pDC -> MoveTo ( L_Insert.Start ) ;	// ���� ������ġ
				pDC -> LineTo ( L_Insert.Last ) ;	// ���� ������
				pDC->SelectObject(Draw_Pen);

				// ���� �̵���Ű�� �ִ� ���̶��
				if ( M_Number == L_Number && M_IsDraw == 'o' ) {
					CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
					pDC -> SelectObject ( Draw_Pen ) ;
				}
				L_Number++ ;
			}
			// Ư�� ������ ������ ����� ���
			else {
				CPen pen ( PS_SOLID, pDoc -> L_Line.GetAt (L_Number).Thickness, pDoc -> L_Line.GetAt (L_Number).L_Color ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
				L_Insert.Last = pDoc -> L_Line.GetAt (L_Number).Last ;
				pDC -> MoveTo ( L_Insert.Start ) ;	// ���� ������ġ
				pDC -> LineTo ( L_Insert.Last ) ;	// ���� ������
				pDC->SelectObject(Draw_Pen);

				// ���� �̵���Ű�� �ִ� ���̶��
				if ( M_Number == L_Number && M_IsDraw == 'o' && M_What == _T ("L") ) {
					CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
					pDC -> SelectObject ( Draw_Pen ) ;
				}
				L_Number++ ;
			}
		}

		// ���� ��ü�� ���
		else if ( pDoc -> What.GetAt (i) == _T ("R") ) {
			// �� ���� ������ �ʾ��� ����� ���
			if ( pDoc -> R_Color.GetAt (R_Number) == RGB (0,0,0) ) {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> R_FillColor.GetAt (R_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
					pDC -> SelectObject ( oldPen ) ;

					// ���� �̵���Ű�� �ִ� ���̶��
					if ( M_Number == R_Number && M_IsDraw == 'o' && M_What == _T ("R") ) {
						CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
						CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
						pDC -> SelectObject ( Draw_Pen ) ;
					}
					R_Number++ ;
				}
				// ä��� ������ ������ ����� ���
				else {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;
					pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
					pDC -> SelectObject ( oldBrush ) ;
					pDC -> SelectObject ( oldPen ) ;

					// ���� �̵���Ű�� �ִ� ���̶��
					if ( M_Number == R_Number && M_IsDraw == 'o' && M_What == _T ("R") ) {
						CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
						pDC -> SelectObject ( Draw_Pen ) ;
					}
					R_Number++ ;
				}
			}
			// Ư�� �� ������ ������ ����� ���
			else {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> R_FillColor.GetAt (R_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
					pDC ->SelectObject ( oldPen ) ;

					// ���� �̵���Ű�� �ִ� ���̶��
					if ( M_Number == R_Number && M_IsDraw == 'o' && M_What == _T ("R") ) {
						CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
						pDC -> SelectObject ( Draw_Pen ) ;
					}
					R_Number++ ;
				}
				// ä��� ������ ������ ����� ���
				else {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					CBrush brush;
					brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;
					pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
					pDC -> SelectObject ( oldPen ) ;
					pDC -> SelectObject ( oldBrush ) ;

					// ���� �̵���Ű�� �ִ� ���̶��
					if ( M_Number == R_Number && M_IsDraw == 'o' && M_What == _T ("R") ) {
						CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
						pDC -> SelectObject ( Draw_Pen ) ;
					}
					R_Number++ ;
				}
			}
		}

		// PolyLine ��ü�� ���
		else if ( pDoc -> What.GetAt (i) == _T ("P") ) {
			for ( int j = 0 ; j < pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetCount () - 1 ; j++ ) {

				// PolyLine�� ������ ������ ���� ����� ���
				if ( pDoc -> P_Poly.GetAt (P_Number).P_Color == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> P_Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
					P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen);

				}
				// PolyLine�� ������ ������ ������ ����� ���
				else {
					CPen pen ( PS_SOLID, pDoc -> P_Poly.GetAt (P_Number).thickness, pDoc -> P_Poly.GetAt (P_Number).P_Color ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
					P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
					P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen);
				}

				// ���� �׸��� �ִ� PolyLine�� Skeleton�� �����ݴϴ�.
				if ( pDoc -> P_Poly.GetCount ()  == P_Number + 1 && P_IsDraw == 'o' && P_Insert.Poly_point.GetSize () > 0 ) {
					CPen pen ( PS_SOLID, 1.8, RGB (0,0,150) ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen) ;

					ChangeRect.left = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).x - 4 ;
					ChangeRect.right = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).x + 4 ;
					ChangeRect.top = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).y - 4 ;
					ChangeRect.bottom = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).y + 4 ;

					pDC -> Rectangle ( ChangeRect ) ;
					pDC->SelectObject(Draw_Pen);

					CPen *Draw_Pen2 = pDC -> SelectObject(&pen) ;
					ChangeRect.left = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1).x - 4 ;
					ChangeRect.right = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1).x + 4 ;
					ChangeRect.top = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1).y - 4 ;
					ChangeRect.bottom = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1).y + 4 ;
					pDC->SelectObject(Draw_Pen2);

					pDC -> Rectangle ( ChangeRect ) ;
				}
			}

			// ���� �̵���Ű�� �ִ� ���̶��
			if ( M_Number == P_Number && M_IsDraw == 'o' && M_What == _T ("P") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;
			}

			P_Number++ ;
		}

		// �� ��ü�� ���
		else if ( pDoc -> What.GetAt (i) == _T ("E") ) {
			// �� ���� ������ �ʾ��� ����� ���
			if ( pDoc -> E_Color.GetAt (E_Number) == RGB (0,0,0) ) {
				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> E_FillColor.GetAt (E_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// ä��� ������ ������ ����� ���
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
			// Ư�� �� ������ ������ ����� ���
			else {
				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> E_FillColor.GetAt (E_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (E_Number), pDoc -> E_Color.GetAt (E_Number) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// ä��� ������ ������ ����� ���
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

			// ���� �̵���Ű�� �ִ� ���̶��
			if ( M_Number == E_Number && M_IsDraw == 'o' && M_What == _T ("E") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;
			}

			// ���� ���� �׸��� �ִ� ���¶�� �׵θ� ���簢���� �׷��ݴϴ�.
			if ( pDoc -> E_Ellipse.GetCount () - 1 == E_Number && E_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				P_PointStart.x = pDoc -> E_Ellipse.GetAt (E_Number).left - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointStart.y = pDoc -> E_Ellipse.GetAt (E_Number).top  - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.x = pDoc -> E_Ellipse.GetAt (E_Number).right + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.y = pDoc -> E_Ellipse.GetAt (E_Number).top - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
				pDC -> LineTo ( P_PointLast ) ;		// ���� ������
				pDC->SelectObject(Draw_Pen);
				;
				CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
				P_PointStart.x = pDoc -> E_Ellipse.GetAt (E_Number).left - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointStart.y = pDoc -> E_Ellipse.GetAt (E_Number).top - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.x = pDoc -> E_Ellipse.GetAt (E_Number).left - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.y = pDoc -> E_Ellipse.GetAt (E_Number).bottom + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
				pDC -> LineTo ( P_PointLast ) ;		// ���� ������
				pDC->SelectObject(Draw_Pen2);

				CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
				P_PointStart.x = pDoc -> E_Ellipse.GetAt (E_Number).left - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointStart.y = pDoc -> E_Ellipse.GetAt (E_Number).bottom + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.x = pDoc -> E_Ellipse.GetAt (E_Number).right + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.y = pDoc -> E_Ellipse.GetAt (E_Number).bottom + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
				pDC -> LineTo ( P_PointLast ) ;		// ���� ������
				pDC->SelectObject(Draw_Pen3);

				CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
				P_PointStart.x = pDoc -> E_Ellipse.GetAt (E_Number).right + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointStart.y = pDoc -> E_Ellipse.GetAt (E_Number).top - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.x = pDoc -> E_Ellipse.GetAt (E_Number).right + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				P_PointLast.y = pDoc -> E_Ellipse.GetAt (E_Number).bottom + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
				pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
				pDC -> LineTo ( P_PointLast ) ;		// ���� ������
				pDC->SelectObject(Draw_Pen4);
			}
			E_Number++ ;
		}

		// ���� ��ü�� ���
		else if ( pDoc -> What.GetAt (i) == _T ("T") ) {
			// �׸� ������ �� Point ��ǥ
			POINT T_Point[3] = { {pDoc -> T_Triangle.GetAt (T_Number).left + (pDoc -> T_Triangle.GetAt (T_Number).right - pDoc -> T_Triangle.GetAt (T_Number).left) / 2,
								  pDoc -> T_Triangle.GetAt (T_Number).top}, {pDoc -> T_Triangle.GetAt (T_Number).left, pDoc -> T_Triangle.GetAt (T_Number).bottom},
								 {pDoc -> T_Triangle.GetAt (T_Number).right, pDoc -> T_Triangle.GetAt (T_Number).bottom} } ;

			// ��� �������� bottom�� ����� ���
			if ( pDoc -> T_Triangle.GetAt (T_Number).top > pDoc -> T_Triangle.GetAt (T_Number).bottom ) {
				T_Point[0].y = pDoc -> T_Triangle.GetAt (T_Number).bottom ;
				T_Point[1].y = pDoc -> T_Triangle.GetAt (T_Number).top ;
				T_Point[2].y = pDoc -> T_Triangle.GetAt (T_Number).top ;
			}

			// �� ���� ������ �ʾ��� ����� ���
			if ( pDoc -> T_Color.GetAt (T_Number) == RGB (0,0,0) ) {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> T_FillColor.GetAt (T_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> T_Thickness.GetAt (T_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( T_Point, 3 ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// ä��� ������ ������ ����� ���
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
			// Ư�� �� ������ ������ ����� ���
			else {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> T_FillColor.GetAt (T_Number) == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> T_Thickness.GetAt (T_Number), pDoc -> T_Color.GetAt (T_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( T_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
				}
				// ä��� ������ ������ ����� ���
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

			// ���� �̵���Ű�� �ִ� ���̶��
			if ( M_Number == T_Number && M_IsDraw == 'o' && M_What == _T ("T") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;
			}

			// ���� ���� �׸��� �ִ� ���¶�� �׵θ� ���簢���� �׷��ݴϴ�.
			if ( pDoc -> T_Triangle.GetCount () - 1 == T_Number && T_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				if ( pDoc -> T_Triangle.GetAt (T_Number).top > pDoc -> T_Triangle.GetAt (T_Number).bottom ) {

					P_PointStart.x = pDoc -> T_Triangle.GetAt (T_Number).left + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointStart.y = pDoc -> T_Triangle.GetAt (T_Number).bottom + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.x = pDoc -> T_Triangle.GetAt (T_Number).right - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.y = pDoc -> T_Triangle.GetAt (T_Number).bottom + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen);
					;
					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> T_Triangle.GetAt (T_Number).left + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointStart.y = pDoc -> T_Triangle.GetAt (T_Number).top + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.x = pDoc -> T_Triangle.GetAt (T_Number).left + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.y = pDoc -> T_Triangle.GetAt (T_Number).bottom - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> T_Triangle.GetAt (T_Number).right - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointStart.y = pDoc -> T_Triangle.GetAt (T_Number).top + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.x = pDoc -> T_Triangle.GetAt (T_Number).right - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.y = pDoc -> T_Triangle.GetAt (T_Number).bottom - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen4);
				}
				else {
					P_PointStart.x = pDoc -> T_Triangle.GetAt (T_Number).left - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointStart.y = pDoc -> T_Triangle.GetAt (T_Number).top - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.x = pDoc -> T_Triangle.GetAt (T_Number).right + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.y = pDoc -> T_Triangle.GetAt (T_Number).top - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen);
					;
					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> T_Triangle.GetAt (T_Number).left - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointStart.y = pDoc -> T_Triangle.GetAt (T_Number).top - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.x = pDoc -> T_Triangle.GetAt (T_Number).left - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.y = pDoc -> T_Triangle.GetAt (T_Number).bottom + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> T_Triangle.GetAt (T_Number).right + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointStart.y = pDoc -> T_Triangle.GetAt (T_Number).top - pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.x = pDoc -> T_Triangle.GetAt (T_Number).right + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					P_PointLast.y = pDoc -> T_Triangle.GetAt (T_Number).bottom + pDoc -> T_Thickness.GetAt (T_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen4);
				}
			}
			T_Number++ ;
		}

		// �� �ﰢ�� ��ü�� ���
		else if ( pDoc -> What.GetAt (i) == _T ("RT") ) {
			// �׸� ������ �� Point ��ǥ
			POINT RT_Point[3] = { {pDoc -> RT_Triangle.GetAt (RT_Number).left + (pDoc -> RT_Triangle.GetAt (RT_Number).right - pDoc -> RT_Triangle.GetAt (RT_Number).left) / 2,
								   pDoc -> RT_Triangle.GetAt (RT_Number).bottom}, {pDoc -> RT_Triangle.GetAt (RT_Number).left, pDoc -> RT_Triangle.GetAt (RT_Number).top},
								  {pDoc -> RT_Triangle.GetAt (RT_Number).right, pDoc -> RT_Triangle.GetAt (RT_Number).top} } ;

			// ��� �������� top�� ����� ���
			if ( pDoc -> RT_Triangle.GetAt (RT_Number).top > pDoc -> RT_Triangle.GetAt (RT_Number).bottom ) {
				RT_Point[0].y = pDoc -> RT_Triangle.GetAt (RT_Number).top ;
				RT_Point[1].y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom ;
				RT_Point[2].y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom ;
			}

			// �� ���� ������ �ʾ��� ����� ���
			if ( pDoc -> RT_Color.GetAt (RT_Number) == RGB (0,0,0) ) {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> RT_FillColor.GetAt (RT_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> RT_Thickness.GetAt (RT_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RT_Point, 3 ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// ä��� ������ ������ ����� ���
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
			// Ư�� �� ������ ������ ����� ���
			else {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> RT_FillColor.GetAt (RT_Number) == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> RT_Thickness.GetAt (RT_Number), pDoc -> RT_Color.GetAt (RT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
				}
				// ä��� ������ ������ ����� ���
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

			// ���� �̵���Ű�� �ִ� ���̶��
			if ( M_Number == RT_Number && M_IsDraw == 'o' && M_What == _T ("RT") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;
			}

			// ���� �� �ﰢ���� �׸��� �ִ� ���¶�� �׵θ� ���簢���� �׷��ݴϴ�.
			if ( pDoc -> RT_Triangle.GetCount () - 1 == RT_Number && RT_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				// ��� �������� top�� ����� ���
				if ( pDoc -> RT_Triangle.GetAt (RT_Number).top > pDoc -> RT_Triangle.GetAt (RT_Number).bottom ) {
					P_PointStart.x = pDoc -> RT_Triangle.GetAt (RT_Number).left + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointStart.y = pDoc -> RT_Triangle.GetAt (RT_Number).top - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.x = pDoc -> RT_Triangle.GetAt (RT_Number).right - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.y = pDoc -> RT_Triangle.GetAt (RT_Number).top - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen);
					;
					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RT_Triangle.GetAt (RT_Number).left + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointStart.y = pDoc -> RT_Triangle.GetAt (RT_Number).top + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.x = pDoc -> RT_Triangle.GetAt (RT_Number).left + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RT_Triangle.GetAt (RT_Number).right - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointStart.y = pDoc -> RT_Triangle.GetAt (RT_Number).top + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.x = pDoc -> RT_Triangle.GetAt (RT_Number).right - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen4);
				}
				// ������ ���
				else {
					P_PointStart.x = pDoc -> RT_Triangle.GetAt (RT_Number).left - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointStart.y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.x = pDoc -> RT_Triangle.GetAt (RT_Number).right + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen);
					;
					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RT_Triangle.GetAt (RT_Number).left - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointStart.y = pDoc -> RT_Triangle.GetAt (RT_Number).top - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.x = pDoc -> RT_Triangle.GetAt (RT_Number).left - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RT_Triangle.GetAt (RT_Number).right + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointStart.y = pDoc -> RT_Triangle.GetAt (RT_Number).top - pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.x = pDoc -> RT_Triangle.GetAt (RT_Number).right + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					P_PointLast.y = pDoc -> RT_Triangle.GetAt (RT_Number).bottom + pDoc -> RT_Thickness.GetAt (RT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen4);
				}
			}
			RT_Number++ ;
		}

		// ���� �ﰢ�� ��ü�� ���
		else if ( pDoc -> What.GetAt (i) == _T ("RightT") ) {
			// �׸� ���� �ﰢ���� �� Point ��ǥ
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

			// �� ���� ������ �ʾ��� ����� ���
			if ( pDoc -> RightT_Color.GetAt (RightT_Number) == RGB (0,0,0) ) {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> RightT_FillColor.GetAt (RightT_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> RightT_Thickness.GetAt (RightT_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RightT_Point, 3 ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// ä��� ������ ������ ����� ���
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
			// Ư�� �� ������ ������ ����� ���
			else {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> RightT_FillColor.GetAt (RightT_Number) == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> RightT_Thickness.GetAt (RightT_Number), pDoc -> RightT_Color.GetAt (RightT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RightT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
				}
				// ä��� ������ ������ ����� ���
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

			// ���� �̵���Ű�� �ִ� ���̶��
			if ( M_Number == RightT_Number && M_IsDraw == 'o' && M_What == _T ("RightT") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;
			}

			// ���� ���� �ﰢ���� �׸��� �ִ� ���¶�� �׵θ� ���簢���� �׷��ݴϴ�.
			if ( pDoc -> RightT_Triangle.GetCount () - 1 == RightT_Number && RightT_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) ) ;
				if ( pDoc -> RightT_Triangle.GetAt (RightT_Number).top > pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom ) {
					if ( pDoc -> RightT_Triangle.GetAt (RightT_Number).left > pDoc -> RightT_Triangle.GetAt (RightT_Number).right ) {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen2);
					}
					else {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
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
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen2);
					}
					else {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).right + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).top - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RightT_Triangle.GetAt (RightT_Number).left - pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RightT_Triangle.GetAt (RightT_Number).bottom + pDoc -> RightT_Thickness.GetAt (RightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen2);
					}
				}
			}
			RightT_Number++ ;
		}

		// �� ���� �ﰢ�� ��ü�� ���
		else if ( pDoc -> What.GetAt (i) == _T ("RRightT") ) {
			// �׸� �� ���� ������ �� Point ��ǥ
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

			// �� ���� ������ �ʾ��� ����� ���
			if ( pDoc -> RRightT_Color.GetAt (RRightT_Number) == RGB (0,0,0) ) {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> RRightT_FillColor.GetAt (RRightT_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> RRightT_Thickness.GetAt (RRightT_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RRightT_Point, 3 ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// ä��� ������ ������ ����� ���
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
			// Ư�� �� ������ ������ ����� ���
			else {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> RRightT_FillColor.GetAt (RRightT_Number) == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> RRightT_Thickness.GetAt (RRightT_Number), pDoc -> RRightT_Color.GetAt (RRightT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RRightT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
				}
				// ä��� ������ ������ ����� ���
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

			// ���� �̵���Ű�� �ִ� ���̶��
			if ( M_Number == RRightT_Number && M_IsDraw == 'o' && M_What == _T ("RRightT") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;
			}

			// ���� �� ���� �ﰢ���� �׸��� �ִ� ���¶�� �׵θ� ���簢���� �׷��ݴϴ�.
			if ( pDoc -> RRightT_Triangle.GetCount () - 1 == RRightT_Number && RRightT_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );

				if ( pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top > pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom ) {
					if ( pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left > pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right ) {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen2);
					}
					else {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
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
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen2);
					}
					else {
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).top - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen);
						;
						CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
						P_PointStart.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).left - pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointStart.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.x = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).right + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						P_PointLast.y = pDoc -> RRightT_Triangle.GetAt (RRightT_Number).bottom + pDoc -> RRightT_Thickness.GetAt (RRightT_Number) / 2 ;
						pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
						pDC -> LineTo ( P_PointLast ) ;		// ���� ������
						pDC->SelectObject(Draw_Pen2);
					}
				}
			}
			RRightT_Number++ ;
		}

		// ���� -> ������ �ﰢ�� ��ü�� ���
		else if ( pDoc -> What.GetAt (i) == _T ("LTRT") ) {
			// �׸� ���� -> ������ �ﰢ���� �� Point ��ǥ
			POINT LTRT_Point[3] = { {pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right,
									 pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top + (pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom - pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top) / 2 },
									{pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left, pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top},
									{pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left, pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom} } ;

			if ( pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left > pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right ) {
				LTRT_Point[0].x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left ;
				LTRT_Point[1].x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right ;
				LTRT_Point[2].x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right ;
			}

			// �� ���� ������ �ʾ��� ����� ���
			if ( pDoc -> LTRT_Color.GetAt (LTRT_Number) == RGB (0,0,0) ) {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> LTRT_FillColor.GetAt (LTRT_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> LTRT_Thickness.GetAt (LTRT_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( LTRT_Point, 3 ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// ä��� ������ ������ ����� ���
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
			// Ư�� �� ������ ������ ����� ���
			else {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> LTRT_FillColor.GetAt (LTRT_Number) == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> LTRT_Thickness.GetAt (LTRT_Number), pDoc -> LTRT_Color.GetAt (LTRT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( LTRT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
				}
				// ä��� ������ ������ ����� ���
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

			// ���� �̵���Ű�� �ִ� ���̶��
			if ( M_Number == LTRT_Number && M_IsDraw == 'o' && M_What == _T ("LTRT") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;
			}

			// ���� ���� -> ������ �ﰢ���� �׸��� �ִ� ���¶�� �׵θ� ���簢���� �׷��ݴϴ�.
			if ( pDoc -> LTRT_Triangle.GetCount () - 1 == LTRT_Number && LTRT_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );

				if ( pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left > pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right ) {
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen);

					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen3);
				}
				else {
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen);

					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).bottom + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen3);
				}
			}
			LTRT_Number++ ;
		}

		// ������ -> ���� �ﰢ�� ��ü�� ���
		else if ( pDoc -> What.GetAt (i) == _T ("RTLT") ) {
			// �׸� ������ -> ���� �ﰢ���� �� Point ��ǥ
			POINT RTLT_Point[3] = { {pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left,
									 pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top + (pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom - pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top) / 2 },
									{pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right, pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top},
									{pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right, pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom} } ;

			if ( pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left > pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right ) {
				RTLT_Point[0].x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right ;
				RTLT_Point[1].x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left ;
				RTLT_Point[2].x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left ;
			}

			// �� ���� ������ �ʾ��� ����� ���
			if ( pDoc -> RTLT_Color.GetAt (RTLT_Number) == RGB (0,0,0) ) {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> RTLT_FillColor.GetAt (RTLT_Number) == RGB (0,0,0) ) {
					CPen pen;
					pen.CreatePen( PS_SOLID, pDoc -> RTLT_Thickness.GetAt (RTLT_Number), RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RTLT_Point, 3 ) ;
					pDC -> SelectObject ( oldPen ) ;
				}
				// ä��� ������ ������ ����� ���
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
			// Ư�� �� ������ ������ ����� ���
			else {

				// ä��� ������ ������ �ʾ��� ����� ���
				if ( pDoc -> RTLT_FillColor.GetAt (RTLT_Number) == RGB (0,0,0) ) {
					CPen pen ( PS_SOLID, pDoc -> RTLT_Thickness.GetAt (RTLT_Number), pDoc -> RTLT_Color.GetAt (RTLT_Number) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Polygon ( RTLT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
				}
				// ä��� ������ ������ ����� ���
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

			// ���� �̵���Ű�� �ִ� ���̶��
			if ( M_Number == RTLT_Number && M_IsDraw == 'o' && M_What == _T ("RTLT") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;
			}

			// ���� ������ -> ���� �ﰢ���� �׸��� �ִ� ���¶�� �׵θ� ���簢���� �׷��ݴϴ�.
			if ( pDoc -> RTLT_Triangle.GetCount () - 1 == RTLT_Number && RTLT_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );

				if ( pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left > pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right ) {
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen);

					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen3);
				}
				else {
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen);

					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
					pDC -> LineTo ( P_PointLast ) ;		// ���� ������
					pDC->SelectObject(Draw_Pen3);
				}
			}
			RTLT_Number++ ;
		}

		// �ؽ�Ʈ ��ü�� ���
		else if ( pDoc -> What.GetAt (i) == _T ("Text") ) {
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
		pDoc->What.Add ( _T("L") ) ;
		pDoc->L_Count++ ;
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
		// PolyLine�� Skeleton�� 3�� �̻��� ���
		else {
			// ����, ������ Skeleton�� ������ ��� Skeleton�� �˻��Ͽ�
			// Ŭ���� ��ǥ�� �ش� Skeleton �߿� �ִ��� Ȯ���Ѵ�.
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
				// ���� Skeleton�� �ǵ帮�� ���� ���� �����Ѵ�.
				if ( (P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 15 &&
					P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 15 &&
					P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 15 &&
					P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 15) ) {
						P_IsStart = 'o' ;
						P_CanMove = 'o' ;
				}
				// ������ Skeleton�� �ǵ帮�� �� Skeleton�� �����Ѵ�.
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
	// PolyLine �׸��� ��, �� ó�� Skeleton�� Ŭ���Ͽ� ���� ����Դϴ�.
	else if ( P_IsDraw == 'o' && P_IsContinue == 'x' ) {
		P_Insert.Poly_point.Add ( point ) ;
		pDoc->What.Add ( _T("P") ) ;
		pDoc -> P_Count = P_Current = pDoc -> P_Poly.GetCount () ;
		pDoc -> P_Count++ ;
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

		if ( m_IsThickness == 'o' )
			pDoc -> P_Poly.GetAt ( P_Current ).thickness = m_Thickness ;
		else if ( m_IsThickness == 'x' )
			pDoc -> P_Poly.GetAt ( P_Current ).thickness = 1 ;
	}
	// ���� �׸��� ���
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
		pDoc->What.Add ( _T("T") ) ;
		pDoc->T_Count++ ;
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
		pDoc->What.Add ( _T("RT") ) ;
		pDoc->RT_Count++ ;
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
		pDoc->What.Add ( _T("RightT") ) ;
		pDoc->RightT_Count++ ;
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
		pDoc->What.Add ( _T("RRightT") ) ;
		pDoc->RRightT_Count++ ;
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
	// ���� -> ������ �ﰢ���� �׸��� ���
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

		// ���� ������ �����ϰ� �׷��� ��� ���� ������ ���.
		if ( m_IsColor == 'o' )
			pDoc -> LTRT_Color.Add ( m_Color ) ;
		// ������ �������� �ʰ� �׷��� ��� ǥ�� ���� ���.
		else if ( m_IsColor == 'x' )
			pDoc -> LTRT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> LTRT_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> LTRT_FillColor.Add ( RGB(0,0,0) ) ;

		// �β� ������ �� ���
		if ( m_IsThickness == 'o' )
			pDoc -> LTRT_Thickness.Add ( m_Thickness ) ;
		// �β� ������ ���� ���� ���
		else if ( m_IsThickness == 'x' )
			pDoc -> LTRT_Thickness.Add (1) ;
	}
	// ������ -> ���� �ﰢ���� �׸��� ���
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

		// ���� ������ �����ϰ� �׷��� ��� ���� ������ ���.
		if ( m_IsColor == 'o' )
			pDoc -> RTLT_Color.Add ( m_Color ) ;
		// ������ �������� �ʰ� �׷��� ��� ǥ�� ���� ���.
		else if ( m_IsColor == 'x' )
			pDoc -> RTLT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' )
			pDoc -> RTLT_FillColor.Add ( m_FillColor ) ;
		else if ( m_IsFillColor == 'x' )
			pDoc -> RTLT_FillColor.Add ( RGB(0,0,0) ) ;

		// �β� ������ �� ���
		if ( m_IsThickness == 'o' )
			pDoc -> RTLT_Thickness.Add ( m_Thickness ) ;
		// �β� ������ ���� ���� ���
		else if ( m_IsThickness == 'x' )
			pDoc -> RTLT_Thickness.Add (1) ;
	}
	// �ؽ�Ʈ�� �׸� �Է� �� ���
	if ( Text_IsContinue == 'o' ) {
		if ( pDoc -> Text_Text.GetAt ( pDoc -> Text_Count - 1 ).Rect.top <= point.y && pDoc -> Text_Text.GetAt ( pDoc -> Text_Count - 1 ).Rect.bottom >= point.y
			 && pDoc -> Text_Text.GetAt ( pDoc -> Text_Count - 1 ).Rect.left <= point.x && pDoc -> Text_Text.GetAt ( pDoc -> Text_Count - 1 ).Rect.right >= point.x )
		{}
		else {
			Text_IsText = 'x' ;
			Text_IsContinue = 'x' ;
		}
	}
	// �ؽ�Ʈ�� �Է� �ϴ� ���
	else if ( Text_IsText == 'o' ) {
		pDoc -> What.Add ( _T("Text") ) ;
		pDoc -> Text_Count++ ;
		pDoc -> Text_Text.SetSize ( pDoc -> Text_Count ) ;
		if ( Text_IsFont == 'o' )
			pDoc -> Text_Text.GetAt ( pDoc -> Text_Count - 1 ).Font.CreateFontIndirect ( &Text_lf ) ;
		else if ( Text_IsFont == 'x' ) {
			pDoc -> Text_Text.GetAt ( pDoc -> Text_Count - 1 ).Rect.top = point.y - 13 ;
			pDoc -> Text_Text.GetAt ( pDoc -> Text_Count - 1 ).Rect.right = point.x + 100 ;
			pDoc -> Text_Text.GetAt ( pDoc -> Text_Count - 1 ).Rect.bottom = point.y + 13 ;
			pDoc -> Text_Text.GetAt ( pDoc -> Text_Count - 1 ).Rect.left = point.x - 4 ;
		}
		pDoc -> Text_Text.GetAt ( pDoc -> Text_Count - 1 ).Text.Format ( _T("") ) ;

		if ( Text_IsContinue != 'o' )
			Text_IsContinue = 'o' ;
	}
	// ��ü�� �̵�, �����ϴ� ���
	else if ( M_IsMove == 'o' ) {

		int L_Number = pDoc -> L_Count - 1;
		int R_Number = pDoc -> R_Count - 1;
		int P_Number = pDoc -> P_Count - 1;
		int E_Number = pDoc -> E_Count - 1;
		int T_Number = pDoc -> T_Count - 1;
		int RT_Number = pDoc -> RT_Count - 1;
		int RightT_Number = pDoc -> RightT_Count - 1;
		int RRightT_Number = pDoc -> RRightT_Count - 1;
		int LTRT_Number = pDoc -> LTRT_Count - 1;
		int RTLT_Number = pDoc -> RTLT_Count - 1;

		// ������ ��ǥ�� ��ü�� �ִ��� ���� Ȯ���մϴ�.
		// �ʰ� �׸� ��ü���� Ȯ���մϴ�.
		for ( int i = pDoc->What.GetCount () ; i > 0  ; i-- ) {

			// �� ��ü�� ���
			if ( pDoc -> What.GetAt (i-1) == _T ("L") ) {
				if ( pDoc -> L_Line.GetAt ( L_Number ).Start.x >= pDoc -> L_Line.GetAt ( L_Number ).Last.x ) {
					if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y >= pDoc -> L_Line.GetAt ( L_Number ).Last.y ) {
						if ( point.x >= pDoc -> L_Line.GetAt ( L_Number ).Last.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.x <= pDoc -> L_Line.GetAt ( L_Number ).Start.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 &&
							 point.y >= pDoc -> L_Line.GetAt ( L_Number ).Last.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.y <= pDoc -> L_Line.GetAt ( L_Number ).Start.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ) {

							M_Rect.top = pDoc -> L_Line.GetAt ( L_Number ).Last.y ;
							M_Rect.bottom = pDoc -> L_Line.GetAt ( L_Number ).Start.y ;
							M_Rect.left = pDoc -> L_Line.GetAt ( L_Number ).Last.x ;
							M_Rect.right = pDoc -> L_Line.GetAt ( L_Number ).Start.x ;
							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("L") ) ; M_Number = L_Number ;
							M_IsDraw = 'o' ;
							if ( M_Rect.left <= M_Rect.right ) {
								M_Rect.right += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								M_Rect.left -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								if ( M_Rect.top <= M_Rect.bottom ) {
									M_Rect.top -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}
								else if ( M_Rect.top > M_Rect.bottom ) {
									M_Rect.top += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									int temp = M_Rect.top ;
									M_Rect.top = M_Rect.bottom ;
									M_Rect.bottom = temp ;
								}
							}
							else if ( M_Rect.left > M_Rect.right ) {
								M_Rect.right -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								M_Rect.left += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								if ( M_Rect.top <= M_Rect.bottom ) {
									M_Rect.top -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									int temp = M_Rect.left ;
									M_Rect.left = M_Rect.right ;
									M_Rect.right = temp ;
								}
								else if ( M_Rect.top > M_Rect.bottom ) {
									M_Rect.top += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									int temp = M_Rect.top ;
									M_Rect.top = M_Rect.bottom ;
									M_Rect.bottom = temp ;
									temp = M_Rect.left ;
									M_Rect.left = M_Rect.right ;
									M_Rect.right = temp ;
								}
							}
							Invalidate () ; break ;
						}
					}
					else if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y < pDoc -> L_Line.GetAt ( L_Number ).Last.y ) {
						if ( point.x >= pDoc -> L_Line.GetAt ( L_Number ).Last.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.x <= pDoc -> L_Line.GetAt ( L_Number ).Start.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 &&
							 point.y >= pDoc -> L_Line.GetAt ( L_Number ).Start.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.y <= pDoc -> L_Line.GetAt ( L_Number ).Last.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ) {

							M_Rect.top = pDoc -> L_Line.GetAt ( L_Number ).Start.y ;
							M_Rect.bottom = pDoc -> L_Line.GetAt ( L_Number ).Last.y ;
							M_Rect.left = pDoc -> L_Line.GetAt ( L_Number ).Last.x ;
							M_Rect.right = pDoc -> L_Line.GetAt ( L_Number ).Start.x ;
							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("L") ) ; M_Number = L_Number ;
							M_IsDraw = 'o' ;
							if ( M_Rect.left <= M_Rect.right ) {
								M_Rect.right += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								M_Rect.left -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								if ( M_Rect.top <= M_Rect.bottom ) {
									M_Rect.top -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}
								else if ( M_Rect.top > M_Rect.bottom ) {
									M_Rect.top += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									int temp = M_Rect.top ;
									M_Rect.top = M_Rect.bottom ;
									M_Rect.bottom = temp ;
								}
							}
							else if ( M_Rect.left > M_Rect.right ) {
								M_Rect.right -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								M_Rect.left += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								if ( M_Rect.top <= M_Rect.bottom ) {
									M_Rect.top -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									int temp = M_Rect.left ;
									M_Rect.left = M_Rect.right ;
									M_Rect.right = temp ;
								}
								else if ( M_Rect.top > M_Rect.bottom ) {
									M_Rect.top += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									int temp = M_Rect.top ;
									M_Rect.top = M_Rect.bottom ;
									M_Rect.bottom = temp ;
									temp = M_Rect.left ;
									M_Rect.left = M_Rect.right ;
									M_Rect.right = temp ;
								}
							}
							Invalidate () ; break ;
						}
					}
				}
				else if ( pDoc -> L_Line.GetAt ( L_Number ).Start.x < pDoc -> L_Line.GetAt ( L_Number ).Last.x ) {
					if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y >= pDoc -> L_Line.GetAt ( L_Number ).Last.y ) {
						if ( point.x >= pDoc -> L_Line.GetAt ( L_Number ).Start.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.x <= pDoc -> L_Line.GetAt ( L_Number ).Last.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 &&
							 point.y >= pDoc -> L_Line.GetAt ( L_Number ).Last.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.y <= pDoc -> L_Line.GetAt ( L_Number ).Start.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ) {

							M_Rect.top = pDoc -> L_Line.GetAt ( L_Number ).Last.y ;
							M_Rect.bottom = pDoc -> L_Line.GetAt ( L_Number ).Start.y ;
							M_Rect.left = pDoc -> L_Line.GetAt ( L_Number ).Start.x ;
							M_Rect.right = pDoc -> L_Line.GetAt ( L_Number ).Last.x ;
							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("L") ) ; M_Number = L_Number ;
							M_IsDraw = 'o' ;
							if ( M_Rect.left <= M_Rect.right ) {
								M_Rect.right += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								M_Rect.left -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								if ( M_Rect.top <= M_Rect.bottom ) {
									M_Rect.top -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}
								else if ( M_Rect.top > M_Rect.bottom ) {
									M_Rect.top += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}
							}
							else if ( M_Rect.left > M_Rect.right ) {
								M_Rect.right -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								M_Rect.left += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								if ( M_Rect.top <= M_Rect.bottom ) {
									M_Rect.top -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}
								else if ( M_Rect.top > M_Rect.bottom ) {
									M_Rect.top += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}
							}
							Invalidate () ; break ;
						}
					}
					else if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y < pDoc -> L_Line.GetAt ( L_Number ).Last.y ) {
						if ( point.x >= pDoc -> L_Line.GetAt ( L_Number ).Start.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.x <= pDoc -> L_Line.GetAt ( L_Number ).Last.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 &&
							 point.y >= pDoc -> L_Line.GetAt ( L_Number ).Start.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.y <= pDoc -> L_Line.GetAt ( L_Number ).Last.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ) {

							M_Rect.top = pDoc -> L_Line.GetAt ( L_Number ).Start.y ;
							M_Rect.bottom = pDoc -> L_Line.GetAt ( L_Number ).Last.y ;
							M_Rect.left = pDoc -> L_Line.GetAt ( L_Number ).Start.x ;
							M_Rect.right = pDoc -> L_Line.GetAt ( L_Number ).Last.x ;
							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("L") ) ; M_Number = L_Number ;
							M_IsDraw = 'o' ;
							if ( M_Rect.left <= M_Rect.right ) {
								M_Rect.right += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								M_Rect.left -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								if ( M_Rect.top <= M_Rect.bottom ) {
									M_Rect.top -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}
								else if ( M_Rect.top > M_Rect.bottom ) {
									M_Rect.top += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}
							}
							else if ( M_Rect.left > M_Rect.right ) {
								M_Rect.right -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								M_Rect.left += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								if ( M_Rect.top <= M_Rect.bottom ) {
									M_Rect.top -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}
								else if ( M_Rect.top > M_Rect.bottom ) {
									M_Rect.top += pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									M_Rect.bottom -= pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}
							}
							Invalidate () ; break ;
						}
					}
				}
				L_Number-- ;
			}

			// ���� ��ü�� ���
			else if ( pDoc -> What.GetAt (i-1) == _T ("R") ) {
				if ( pDoc -> R_Rec.GetAt ( R_Number ).left - 2 <= point.x && pDoc -> R_Rec.GetAt ( R_Number ).right + 2 >= point.x &&
					 pDoc -> R_Rec.GetAt ( R_Number ).top - 2 <= point.y && pDoc -> R_Rec.GetAt ( R_Number ).bottom + 2 >= point.y ) {
				
					M_Rect.top = pDoc -> R_Rec.GetAt ( R_Number ).top - pDoc -> R_Thickness.GetAt ( R_Number ) / 2 - 2 ;
					M_Rect.bottom = pDoc -> R_Rec.GetAt ( R_Number ).bottom + pDoc -> R_Thickness.GetAt ( R_Number ) / 2 + 2 ;
					M_Rect.left = pDoc -> R_Rec.GetAt ( R_Number ).left - pDoc -> R_Thickness.GetAt ( R_Number ) / 2 - 2 ;
					M_Rect.right = pDoc -> R_Rec.GetAt ( R_Number ).right + pDoc -> R_Thickness.GetAt ( R_Number ) / 2 + 2 ;

					M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
					M_What.Format ( _T ("R") ) ; M_Number = R_Number ;
					M_IsDraw = 'o' ;
					Invalidate () ; break ;
				}
				R_Number-- ;
			}

			// PolyLine ��ü�� ���
			else if ( pDoc -> What.GetAt (i-1) == _T ("P") ) {
				int MAX_x = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (0).x ;
				int MAX_y = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (0).y ;
				int MIN_x = MAX_x ;
				int MIN_y = MAX_y ;

				for ( int i = 1 ; i < pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetCount () ; i++ ) {
					if ( MAX_x < pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x )
						MAX_x = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x ;
					else if ( MIN_x > pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x )
						MIN_x = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x ;

					if ( MAX_y < pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y )
						MAX_y = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y ;
					else if ( MIN_y > pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y )
						MIN_y = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y ;
				}

				if ( MAX_x >= point.x && MIN_x <= point.x && MAX_y >= point.y && MIN_y <= point.y ) {
					M_Rect.top = MIN_y ;
					M_Rect.bottom = MAX_y ;
					M_Rect.left = MIN_x ;
					M_Rect.right = MAX_x ;

					M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
					M_What.Format ( _T ("P") ) ; M_Number = P_Number ;
					M_IsDraw = 'o' ;
					Invalidate () ; break ;
				}
				P_Number-- ;
			}

			// �� ��ü�� ���
			else if ( pDoc -> What.GetAt (i-1) == _T ("E") ) {
				if ( pDoc -> E_Ellipse.GetAt ( E_Number ).left <= point.x && pDoc -> E_Ellipse.GetAt ( E_Number ).right >= point.x &&
					 pDoc -> E_Ellipse.GetAt ( E_Number ).top <= point.y && pDoc -> E_Ellipse.GetAt ( E_Number ).bottom >= point.y ) {
				
					M_Rect.top = pDoc -> E_Ellipse.GetAt ( E_Number ).top - pDoc -> E_Thickness.GetAt ( E_Number ) / 2 ;
					M_Rect.bottom = pDoc -> E_Ellipse.GetAt ( E_Number ).bottom + pDoc -> E_Thickness.GetAt ( E_Number ) / 2 ;
					M_Rect.left = pDoc -> E_Ellipse.GetAt ( E_Number ).left - pDoc -> E_Thickness.GetAt ( E_Number ) / 2 ;
					M_Rect.right = pDoc -> E_Ellipse.GetAt ( E_Number ).right + pDoc -> E_Thickness.GetAt ( E_Number ) / 2 ;

					M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
					M_What.Format ( _T ("E") ) ; M_Number = E_Number ;
					M_IsDraw = 'o' ;
					Invalidate () ; break ;
				}
				E_Number-- ;
				
			}

			// ���� ��ü�� ���
			else if ( pDoc -> What.GetAt (i-1) == _T ("T") ) {
				if ( pDoc -> T_Triangle.GetAt ( T_Number ).left <= point.x && pDoc -> T_Triangle.GetAt ( T_Number ).right >= point.x &&
					 pDoc -> T_Triangle.GetAt ( T_Number ).top <= point.y && pDoc -> T_Triangle.GetAt ( T_Number ).bottom >= point.y ) {
				
					M_Rect.top = pDoc -> T_Triangle.GetAt ( T_Number ).top - pDoc -> T_Thickness.GetAt ( T_Number ) / 2 ;
					M_Rect.bottom = pDoc -> T_Triangle.GetAt ( T_Number ).bottom + pDoc -> T_Thickness.GetAt ( T_Number ) / 2 ;
					M_Rect.left = pDoc -> T_Triangle.GetAt ( T_Number ).left - pDoc -> T_Thickness.GetAt ( T_Number ) / 2 ;
					M_Rect.right = pDoc -> T_Triangle.GetAt ( T_Number ).right + pDoc -> T_Thickness.GetAt ( T_Number ) / 2 ;

					M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
					M_What.Format ( _T ("T") ) ; M_Number = T_Number ;
					M_IsDraw = 'o' ;
					Invalidate () ; break ;
				}
				T_Number-- ;
			}

			// �� �ﰢ�� ��ü�� ���
			else if ( pDoc -> What.GetAt (i-1) == _T ("RT") ) {
				if ( pDoc -> RT_Triangle.GetAt ( RT_Number ).left <= point.x && pDoc -> RT_Triangle.GetAt ( RT_Number ).right >= point.x &&
					 pDoc -> RT_Triangle.GetAt ( RT_Number ).top <= point.y && pDoc -> RT_Triangle.GetAt ( RT_Number ).bottom >= point.y ) {
				
					M_Rect.top = pDoc -> RT_Triangle.GetAt ( RT_Number ).top - pDoc -> RT_Thickness.GetAt ( RT_Number ) / 2 ;
					M_Rect.bottom = pDoc -> RT_Triangle.GetAt ( RT_Number ).bottom + pDoc -> RT_Thickness.GetAt ( RT_Number ) / 2 ;
					M_Rect.left = pDoc -> RT_Triangle.GetAt ( RT_Number ).left - pDoc -> RT_Thickness.GetAt ( RT_Number ) / 2 ;
					M_Rect.right = pDoc -> RT_Triangle.GetAt ( RT_Number ).right + pDoc -> RT_Thickness.GetAt ( RT_Number ) / 2 ;

					M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
					M_What.Format ( _T ("RT") ) ; M_Number = RT_Number ;
					M_IsDraw = 'o' ;
					Invalidate () ; break ;
				}
				RT_Number-- ;
			}

			// ���� �ﰢ�� ��ü�� ���
			else if ( pDoc -> What.GetAt (i-1) == _T ("RightT") ) {
				if ( pDoc -> RightT_Triangle.GetAt ( RightT_Number ).left <= point.x && pDoc -> RightT_Triangle.GetAt ( RightT_Number ).right >= point.x &&
					 pDoc -> RightT_Triangle.GetAt ( RightT_Number ).top <= point.y && pDoc -> RightT_Triangle.GetAt ( RightT_Number ).bottom >= point.y ) {
				
					M_Rect.top = pDoc -> RightT_Triangle.GetAt ( RightT_Number ).top - pDoc -> RightT_Thickness.GetAt ( RightT_Number ) / 2 ;
					M_Rect.bottom = pDoc -> RightT_Triangle.GetAt ( RightT_Number ).bottom + pDoc -> RightT_Thickness.GetAt ( RightT_Number ) / 2 ;
					M_Rect.left = pDoc -> RightT_Triangle.GetAt ( RightT_Number ).left - pDoc -> RightT_Thickness.GetAt ( RightT_Number ) / 2 ;
					M_Rect.right = pDoc -> RightT_Triangle.GetAt ( RightT_Number ).right + pDoc -> RightT_Thickness.GetAt ( RightT_Number ) / 2 ;

					M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
					M_What.Format ( _T ("RightT") ) ; M_Number = RightT_Number ;
					M_IsDraw = 'o' ;
					Invalidate () ; break ;
				}
				RightT_Number-- ;
			}

			// �� ���� �ﰢ�� ��ü�� ���
			else if ( pDoc -> What.GetAt (i-1) == _T ("RRightT") ) {
				if ( pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).left <= point.x && pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).right >= point.x &&
					 pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).top <= point.y && pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).bottom >= point.y ) {
				
					M_Rect.top = pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).top - pDoc -> RRightT_Thickness.GetAt ( RRightT_Number ) / 2 ;
					M_Rect.bottom = pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).bottom + pDoc -> RRightT_Thickness.GetAt ( RRightT_Number ) / 2 ;
					M_Rect.left = pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).left - pDoc -> RRightT_Thickness.GetAt ( RRightT_Number ) / 2 ;
					M_Rect.right = pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).right + pDoc -> RRightT_Thickness.GetAt ( RRightT_Number ) / 2 ;

					M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
					M_What.Format ( _T ("RRightT") ) ; M_Number = RRightT_Number ;
					M_IsDraw = 'o' ;
					Invalidate () ; break ;
				}
				RRightT_Number-- ;
			}

			// ���� -> ������ �ﰢ�� ��ü�� ���
			else if ( pDoc -> What.GetAt (i-1) == _T ("LTRT") ) {
				if ( pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).left <= point.x && pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).right >= point.x &&
					 pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).top <= point.y && pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).bottom >= point.y ) {
				
					M_Rect.top = pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).top - pDoc -> LTRT_Thickness.GetAt ( LTRT_Number ) / 2 ;
					M_Rect.bottom = pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).bottom + pDoc -> LTRT_Thickness.GetAt ( LTRT_Number ) / 2 ;
					M_Rect.left = pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).left - pDoc -> LTRT_Thickness.GetAt ( LTRT_Number ) / 2 ;
					M_Rect.right = pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).right + pDoc -> LTRT_Thickness.GetAt ( LTRT_Number ) / 2 ;

					M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
					M_What.Format ( _T ("LTRT") ) ; M_Number = LTRT_Number ;
					M_IsDraw = 'o' ;
					Invalidate () ; break ;
				}
				LTRT_Number-- ;
			}

			// ������ -> ���� �ﰢ�� ��ü�� ���
			else if ( pDoc -> What.GetAt (i-1) == _T ("RTLT") ) {
				if ( pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).left <= point.x && pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).right >= point.x &&
					 pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).top <= point.y && pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).bottom >= point.y ) {
				
					M_Rect.top = pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).top - pDoc -> RTLT_Thickness.GetAt ( RTLT_Number ) / 2 ;
					M_Rect.bottom = pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).bottom + pDoc -> RTLT_Thickness.GetAt ( RTLT_Number ) / 2 ;
					M_Rect.left = pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).left - pDoc -> RTLT_Thickness.GetAt ( RTLT_Number ) / 2 ;
					M_Rect.right = pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).right + pDoc -> RTLT_Thickness.GetAt ( RTLT_Number ) / 2 ;

					M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
					M_What.Format ( _T ("RTLT") ) ; M_Number = RTLT_Number ;
					M_IsDraw = 'o' ;
					Invalidate () ; break ;
				}
				RTLT_Number-- ;
			}

		}
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

		if ( m_IsThickness == 'o' )
			L_Insert.Thickness = m_Thickness ;
		else
			L_Insert.Thickness = 1 ;

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
	// ���� -> ������ �ﰢ�� �׸��� ������ �巡�� �ϴ� ���
	else if ( LTRT_CanMove == 'o' ) {
		LTRT_Insert.right = point.x ;
		LTRT_Insert.bottom = point.y ;

		pDoc->LTRT_Triangle.SetAt ( LTRT_Current, LTRT_Insert ) ;
		Invalidate () ;
	}
	// ������ -> ���� �ﰢ�� �׸��� ������ �巡�� �ϴ� ���
	else if ( RTLT_CanMove == 'o' ) {
		RTLT_Insert.right = point.x ;
		RTLT_Insert.bottom = point.y ;

		pDoc->RTLT_Triangle.SetAt ( RTLT_Current, RTLT_Insert ) ;
		Invalidate () ;
	}
	// ��ü�� �̵���Ű�� ���
	else if ( M_IsSelect == 'o' ) {
		M_Rect.top += point.y - M_Start.y ;
		M_Rect.bottom += point.y - M_Start.y ;
		M_Rect.left += point.x - M_Start.x ;
		M_Rect.right += point.x - M_Start.x ;

		// ���� �̵��ϴ� ���
		if ( M_What == _T ("L") ) {
			pDoc -> L_Line.GetAt ( M_Number ).Start.x += point.x - M_Start.x ;
			pDoc -> L_Line.GetAt ( M_Number ).Last.x += point.x - M_Start.x ;
			pDoc -> L_Line.GetAt ( M_Number ).Start.y += point.y - M_Start.y ;
			pDoc -> L_Line.GetAt ( M_Number ).Last.y += point.y - M_Start.y ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// ���ڸ� �̵��ϴ� ���
		else if ( M_What == _T ("R") ) {
			pDoc -> R_Rec.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> R_Rec.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> R_Rec.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> R_Rec.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// PolyLine�� �̵��ϴ� ���
		else if ( M_What == _T ("P") ) {
			for ( int i = 0 ; i < pDoc -> P_Poly.GetAt ( M_Number ).Poly_point.GetCount () ; i++ ) {
				pDoc -> P_Poly.GetAt ( M_Number).Poly_point.GetAt (i).x += point.x - M_Start.x ;
				pDoc -> P_Poly.GetAt ( M_Number).Poly_point.GetAt (i).y += point.y - M_Start.y ;
			}

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// ���� �̵��ϴ� ���
		else if ( M_What == _T ("E") ) {
			pDoc -> E_Ellipse.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> E_Ellipse.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> E_Ellipse.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> E_Ellipse.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// ���� �̵��ϴ� ���
		else if ( M_What == _T ("T") ) {
			pDoc -> T_Triangle.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> T_Triangle.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> T_Triangle.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> T_Triangle.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// �� �ﰢ���� �̵��ϴ� ���
		else if ( M_What == _T ("RT") ) {
			pDoc -> RT_Triangle.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> RT_Triangle.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> RT_Triangle.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> RT_Triangle.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// ���� �ﰢ���� �̵��ϴ� ���
		else if ( M_What == _T ("RightT") ) {
			pDoc -> RightT_Triangle.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> RightT_Triangle.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> RightT_Triangle.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> RightT_Triangle.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// �� ���� �ﰢ���� �̵��ϴ� ���
		else if ( M_What == _T ("RRightT") ) {
			pDoc -> RRightT_Triangle.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> RRightT_Triangle.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> RRightT_Triangle.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> RRightT_Triangle.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// ���� -> ������ �ﰢ���� �̵��ϴ� ���
		else if ( M_What == _T ("LTRT") ) {
			pDoc -> LTRT_Triangle.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> LTRT_Triangle.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> LTRT_Triangle.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> LTRT_Triangle.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// ������ -> ���� �ﰢ���� �̵��ϴ� ���
		else if ( M_What == _T ("RTLT") ) {
			pDoc -> RTLT_Triangle.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> RTLT_Triangle.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> RTLT_Triangle.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> RTLT_Triangle.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}

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

	// ��ü�� �̵���Ű�� Ŭ���� �� ���
	if ( M_IsMove == 'o' ) {
		Invalidate () ;
		M_IsSelect = 'x' ;
	}
	// ���� �׸��� Ŭ���� �� ���
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
		L_CanMove = 'x' ;
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
		R_CanMove = 'x' ;
	}
	// PolyLine�� �׸��� Ŭ���� �� ���
	else if ( P_IsDraw == 'o' ) {
		// ���� ���� ��ǥ�� Ŭ��, ���� ��� �׸��� ���
		if ( P_IsMove == 'x' ) {
			P_CanMove = 'x' ; P_IsStart = 'x' ;
			P_Insert.Poly_point.RemoveAll () ;
			P_CanMove = 'x' ;
			P_IsContinue = 'x' ;
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
				P_IsSkeletonStart = 'x' ;
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
		E_CanMove = 'x' ;
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
		T_CanMove = 'x' ;
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
		RT_CanMove = 'x' ;
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
		RightT_CanMove = 'x' ;
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
		RRightT_CanMove = 'x' ;
	}
	// ���� -> ������ ���� �ﰢ���� �׸��� Ŭ���� �� ���
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
		LTRT_CanMove = 'x' ;
	}
	// ������ -> ���� ���� �ﰢ���� �׸��� Ŭ���� �� ���
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
		RTLT_CanMove = 'x' ;
	}

	CScrollView::OnLButtonUp(nFlags, point);
}

// �� �׸��� ���ٸ� ������ ��� �Ҹ��� ���ϴ�.
void CGraphicEditorView::OnDrawline()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return CScrollView::OnSetCursor(pWnd, nHitTest, message);

	if (nHitTest == HTCLIENT) {
		CPoint point ;
		::GetCursorPos ( &point ) ;	// ��ũ�� ��ǥ
		ScreenToClient ( &point ) ;	// Ŭ���̾�Ʈ ��ǥ�� ��ȯ

		// ���ÿ� �⺻ Ŀ���� ��ȯ �մϴ�.
		if ( IsNormal == 'o' )
			::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_ARROW)) ;
		else if ( M_IsMove == 'o' ) {

			int L_Number = pDoc -> L_Count - 1;
			int R_Number = pDoc -> R_Count - 1;
			int P_Number = pDoc -> P_Count - 1;
			int E_Number = pDoc -> E_Count - 1;
			int T_Number = pDoc -> T_Count - 1;
			int RT_Number = pDoc -> RT_Count - 1;
			int RightT_Number = pDoc -> RightT_Count - 1;
			int RRightT_Number = pDoc -> RRightT_Count - 1;
			int LTRT_Number = pDoc -> LTRT_Count - 1;
			int RTLT_Number = pDoc -> RTLT_Count - 1;

			if ( M_IsDraw == 'o' ) {
				if ( M_Rect.top <= point.y && M_Rect.bottom >= point.y && M_Rect.left <= point.x && M_Rect.right >= point.x ) {
					::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
				}
				else {
					::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_ARROW)) ;

					// ������ ��ǥ�� ��ü�� �ִ��� ���� Ȯ���մϴ�.
					// �ʰ� �׸� ��ü���� Ȯ���մϴ�.
					for ( int i = pDoc->What.GetCount () ; i > 0  ; i-- ) {

						// �� ��ü�� ���
						if ( pDoc -> What.GetAt (i-1) == _T ("L") ) {
							if ( pDoc -> L_Line.GetAt ( L_Number ).Start.x >= pDoc -> L_Line.GetAt ( L_Number ).Last.x ) {
								if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y >= pDoc -> L_Line.GetAt ( L_Number ).Last.y ) {
									if ( point.x >= pDoc -> L_Line.GetAt ( L_Number ).Last.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.x <= pDoc -> L_Line.GetAt ( L_Number ).Start.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 &&
										point.y >= pDoc -> L_Line.GetAt ( L_Number ).Last.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.y <= pDoc -> L_Line.GetAt ( L_Number ).Start.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ) {

											::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
									}
								}
								else if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y < pDoc -> L_Line.GetAt ( L_Number ).Last.y ) {
									if ( point.x >= pDoc -> L_Line.GetAt ( L_Number ).Last.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.x <= pDoc -> L_Line.GetAt ( L_Number ).Start.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 &&
										point.y >= pDoc -> L_Line.GetAt ( L_Number ).Start.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.y <= pDoc -> L_Line.GetAt ( L_Number ).Last.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ) {

											::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
									}
								}
							}
							else if ( pDoc -> L_Line.GetAt ( L_Number ).Start.x < pDoc -> L_Line.GetAt ( L_Number ).Last.x ) {
								if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y >= pDoc -> L_Line.GetAt ( L_Number ).Last.y ) {
									if ( point.x >= pDoc -> L_Line.GetAt ( L_Number ).Start.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.x <= pDoc -> L_Line.GetAt ( L_Number ).Last.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 &&
										point.y >= pDoc -> L_Line.GetAt ( L_Number ).Last.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.y <= pDoc -> L_Line.GetAt ( L_Number ).Start.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ) {

											::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
									}
								}
								else if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y < pDoc -> L_Line.GetAt ( L_Number ).Last.y ) {
									if ( point.x >= pDoc -> L_Line.GetAt ( L_Number ).Start.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.x <= pDoc -> L_Line.GetAt ( L_Number ).Last.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 &&
										point.y >= pDoc -> L_Line.GetAt ( L_Number ).Start.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.y <= pDoc -> L_Line.GetAt ( L_Number ).Last.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ) {

											::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
									}
								}
							}
							L_Number-- ;
						}

						// ���� ��ü�� ���
						else if ( pDoc -> What.GetAt (i-1) == _T ("R") ) {
							if ( pDoc -> R_Rec.GetAt ( R_Number ).left - 2 <= point.x && pDoc -> R_Rec.GetAt ( R_Number ).right + 2 >= point.x &&
								pDoc -> R_Rec.GetAt ( R_Number ).top - 2 <= point.y && pDoc -> R_Rec.GetAt ( R_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							R_Number-- ;
						}

						// PolyLine ��ü�� ���
						else if ( pDoc -> What.GetAt (i-1) == _T ("P") ) {
							int MAX_x = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (0).x ;
							int MAX_y = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (0).y ;
							int MIN_x = MAX_x ;
							int MIN_y = MAX_y ;

							for ( int i = 1 ; i < pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetCount () ; i++ ) {
								if ( MAX_x < pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x )
									MAX_x = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x ;
								else if ( MIN_x > pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x )
									MIN_x = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x ;

								if ( MAX_y < pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y )
									MAX_y = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y ;
								else if ( MIN_y > pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y )
									MIN_y = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y ;
							}

							if ( MAX_x >= point.x && MIN_x <= point.x && MAX_y >= point.y && MIN_y <= point.y ) {
								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							P_Number-- ;
						}

						// �� ��ü�� ���
						else if ( pDoc -> What.GetAt (i-1) == _T ("E") ) {
							if ( pDoc -> E_Ellipse.GetAt ( E_Number ).left <= point.x && pDoc -> E_Ellipse.GetAt ( E_Number ).right >= point.x &&
								pDoc -> E_Ellipse.GetAt ( E_Number ).top <= point.y && pDoc -> E_Ellipse.GetAt ( E_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							E_Number-- ;
						}

						// ���� ��ü�� ���
						else if ( pDoc -> What.GetAt (i-1) == _T ("T") ) {
							if ( pDoc -> T_Triangle.GetAt ( T_Number ).left <= point.x && pDoc -> T_Triangle.GetAt ( T_Number ).right >= point.x &&
								pDoc -> T_Triangle.GetAt ( T_Number ).top <= point.y && pDoc -> T_Triangle.GetAt ( T_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							T_Number-- ;
						}

						// �� �ﰢ�� ��ü�� ���
						else if ( pDoc -> What.GetAt (i-1) == _T ("RT") ) {
							if ( pDoc -> RT_Triangle.GetAt ( RT_Number ).left <= point.x && pDoc -> RT_Triangle.GetAt ( RT_Number ).right >= point.x &&
								pDoc -> RT_Triangle.GetAt ( RT_Number ).top <= point.y && pDoc -> RT_Triangle.GetAt ( RT_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							RT_Number-- ;
						}

						// ���� �ﰢ�� ��ü�� ���
						else if ( pDoc -> What.GetAt (i-1) == _T ("RightT") ) {
							if ( pDoc -> RightT_Triangle.GetAt ( RightT_Number ).left <= point.x && pDoc -> RightT_Triangle.GetAt ( RightT_Number ).right >= point.x &&
								pDoc -> RightT_Triangle.GetAt ( RightT_Number ).top <= point.y && pDoc -> RightT_Triangle.GetAt ( RightT_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							RightT_Number-- ;
						}

						// �� ���� �ﰢ�� ��ü�� ���
						else if ( pDoc -> What.GetAt (i-1) == _T ("RRightT") ) {
							if ( pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).left <= point.x && pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).right >= point.x &&
								pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).top <= point.y && pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							RRightT_Number-- ;
						}

						// ���� -> ������ �ﰢ�� ��ü�� ���
						else if ( pDoc -> What.GetAt (i-1) == _T ("LTRT") ) {
							if ( pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).left <= point.x && pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).right >= point.x &&
								pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).top <= point.y && pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							LTRT_Number-- ;
						}

						// ������ -> ���� �ﰢ�� ��ü�� ���
						else if ( pDoc -> What.GetAt (i-1) == _T ("RTLT") ) {
							if ( pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).left <= point.x && pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).right >= point.x &&
								pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).top <= point.y && pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							RTLT_Number-- ;
						}

					}
				}
			}
			else if ( M_IsDraw == 'x' ) {
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_ARROW)) ;

				// ������ ��ǥ�� ��ü�� �ִ��� ���� Ȯ���մϴ�.
				// �ʰ� �׸� ��ü���� Ȯ���մϴ�.
				for ( int i = pDoc->What.GetCount () ; i > 0  ; i-- ) {

					// �� ��ü�� ���
					if ( pDoc -> What.GetAt (i-1) == _T ("L") ) {
						if ( pDoc -> L_Line.GetAt ( L_Number ).Start.x >= pDoc -> L_Line.GetAt ( L_Number ).Last.x ) {
							if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y >= pDoc -> L_Line.GetAt ( L_Number ).Last.y ) {
								if ( point.x >= pDoc -> L_Line.GetAt ( L_Number ).Last.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.x <= pDoc -> L_Line.GetAt ( L_Number ).Start.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 &&
									point.y >= pDoc -> L_Line.GetAt ( L_Number ).Last.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.y <= pDoc -> L_Line.GetAt ( L_Number ).Start.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ) {

									::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
								}
							}
							else if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y < pDoc -> L_Line.GetAt ( L_Number ).Last.y ) {
								if ( point.x >= pDoc -> L_Line.GetAt ( L_Number ).Last.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.x <= pDoc -> L_Line.GetAt ( L_Number ).Start.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 &&
									point.y >= pDoc -> L_Line.GetAt ( L_Number ).Start.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.y <= pDoc -> L_Line.GetAt ( L_Number ).Last.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ) {
								
									::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
								}
							}
						}
						else if ( pDoc -> L_Line.GetAt ( L_Number ).Start.x < pDoc -> L_Line.GetAt ( L_Number ).Last.x ) {
							if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y >= pDoc -> L_Line.GetAt ( L_Number ).Last.y ) {
								if ( point.x >= pDoc -> L_Line.GetAt ( L_Number ).Start.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.x <= pDoc -> L_Line.GetAt ( L_Number ).Last.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 &&
									point.y >= pDoc -> L_Line.GetAt ( L_Number ).Last.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.y <= pDoc -> L_Line.GetAt ( L_Number ).Start.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ) {

									::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
								}
							}
							else if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y < pDoc -> L_Line.GetAt ( L_Number ).Last.y ) {
								if ( point.x >= pDoc -> L_Line.GetAt ( L_Number ).Start.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.x <= pDoc -> L_Line.GetAt ( L_Number ).Last.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 &&
									point.y >= pDoc -> L_Line.GetAt ( L_Number ).Start.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 && point.y <= pDoc -> L_Line.GetAt ( L_Number ).Last.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ) {

									::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
								}
							}
						}
						L_Number-- ;
					}

					// ���� ��ü�� ���
					else if ( pDoc -> What.GetAt (i-1) == _T ("R") ) {
						if ( pDoc -> R_Rec.GetAt ( R_Number ).left - 2 <= point.x && pDoc -> R_Rec.GetAt ( R_Number ).right + 2 >= point.x &&
							pDoc -> R_Rec.GetAt ( R_Number ).top - 2 <= point.y && pDoc -> R_Rec.GetAt ( R_Number ).bottom + 2 >= point.y ) {

							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						R_Number-- ;
					}

					// PolyLine ��ü�� ���
					else if ( pDoc -> What.GetAt (i-1) == _T ("P") ) {
						int MAX_x = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (0).x ;
						int MAX_y = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (0).y ;
						int MIN_x = MAX_x ;
						int MIN_y = MAX_y ;

						for ( int i = 1 ; i < pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetCount () ; i++ ) {
							if ( MAX_x < pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x )
								MAX_x = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x ;
							else if ( MIN_x > pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x )
								MIN_x = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x ;

							if ( MAX_y < pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y )
								MAX_y = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y ;
							else if ( MIN_y > pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y )
								MIN_y = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y ;
						}

						if ( MAX_x >= point.x && MIN_x <= point.x && MAX_y >= point.y && MIN_y <= point.y ) {
							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						P_Number-- ;
					}

					// �� ��ü�� ���
					else if ( pDoc -> What.GetAt (i-1) == _T ("E") ) {
						if ( pDoc -> E_Ellipse.GetAt ( E_Number ).left <= point.x && pDoc -> E_Ellipse.GetAt ( E_Number ).right >= point.x &&
							pDoc -> E_Ellipse.GetAt ( E_Number ).top <= point.y && pDoc -> E_Ellipse.GetAt ( E_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						E_Number-- ;
					}

					// ���� ��ü�� ���
					else if ( pDoc -> What.GetAt (i-1) == _T ("T") ) {
						if ( pDoc -> T_Triangle.GetAt ( T_Number ).left <= point.x && pDoc -> T_Triangle.GetAt ( T_Number ).right >= point.x &&
							pDoc -> T_Triangle.GetAt ( T_Number ).top <= point.y && pDoc -> T_Triangle.GetAt ( T_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						T_Number-- ;
					}

					// �� �ﰢ�� ��ü�� ���
					else if ( pDoc -> What.GetAt (i-1) == _T ("RT") ) {
						if ( pDoc -> RT_Triangle.GetAt ( RT_Number ).left <= point.x && pDoc -> RT_Triangle.GetAt ( RT_Number ).right >= point.x &&
							pDoc -> RT_Triangle.GetAt ( RT_Number ).top <= point.y && pDoc -> RT_Triangle.GetAt ( RT_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						RT_Number-- ;
					}

					// ���� �ﰢ�� ��ü�� ���
					else if ( pDoc -> What.GetAt (i-1) == _T ("RightT") ) {
						if ( pDoc -> RightT_Triangle.GetAt ( RightT_Number ).left <= point.x && pDoc -> RightT_Triangle.GetAt ( RightT_Number ).right >= point.x &&
							pDoc -> RightT_Triangle.GetAt ( RightT_Number ).top <= point.y && pDoc -> RightT_Triangle.GetAt ( RightT_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						RightT_Number-- ;
					}

					// �� ���� �ﰢ�� ��ü�� ���
					else if ( pDoc -> What.GetAt (i-1) == _T ("RRightT") ) {
						if ( pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).left <= point.x && pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).right >= point.x &&
							pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).top <= point.y && pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						RRightT_Number-- ;
					}

					// ���� -> ������ �ﰢ�� ��ü�� ���
					else if ( pDoc -> What.GetAt (i-1) == _T ("LTRT") ) {
						if ( pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).left <= point.x && pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).right >= point.x &&
							pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).top <= point.y && pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						LTRT_Number-- ;
					}

					// ������ -> ���� �ﰢ�� ��ü�� ���
					else if ( pDoc -> What.GetAt (i-1) == _T ("RTLT") ) {
						if ( pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).left <= point.x && pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).right >= point.x &&
							pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).top <= point.y && pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						RTLT_Number-- ;
					}

				}
			}
		}
		// PolyLine�� ����ؼ� �׸��� ���
		else if ( P_IsContinue == 'o' && P_CanMove == 'x' ) {
			// PolyLine�� Skeleton�� 2���� ���
			if ( P_CurrentPoint == 1 ) {
				// ������ ������������ �����Ϸ��� ��쿡 ���� Ŀ���� ���� �Ѵ�.
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
					if ( P_Insert.Poly_point.GetAt (i).x <= point.x + 15 &&
						P_Insert.Poly_point.GetAt (i).x >= point.x - 15 &&
						P_Insert.Poly_point.GetAt (i).y <= point.y + 15 &&
						P_Insert.Poly_point.GetAt (i).y >= point.y - 15 ) {
							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
							P_Flag = 'o' ;
					}
				}

				if ( P_Flag == 'x' ) {
					// ���� Skeleton�� ã���� Ŀ���� 4���� Ŀ���� �����Ѵ�.
					if ( (P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 15 &&
						P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 15 &&
						P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 15 &&
						P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 15) ) {
							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
					}
					// ������ Skeleton�� ã���� Ŀ���� 4���� Ŀ���� �����Ѵ�.
					else if ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 15 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 15 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 15 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 15) ) {
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

	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
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

// PolyLine �׸��� ���ٸ� ������ ��� �Ҹ��� ���ϴ�.
void CGraphicEditorView::OnDrawpoly()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
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

// �� �׸��� ���ٸ� ������ ��� �Ҹ��� ���ϴ�.
void CGraphicEditorView::OnDrawellipse()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	Text_IsText = 'x' ;
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
	IsNormal = 'x' ;
	M_IsMove = 'o' ;

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
		IsNormal = 'o' ;
		P_Insert.Poly_point.RemoveAll () ;
		P_ChangeSkeleton = 0 ;
		P_IsContinue = 'x' ;
		P_DrawContinue = 'x' ;
		P_IsStart = 'x' ;
		P_IsMove = 'x' ;
	}

	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
	LTRT_IsDraw = 'x' ;
	RTLT_IsDraw = 'x' ;
	RRightT_IsDraw = 'x' ;
	RightT_IsDraw = 'x' ;
	RT_IsDraw = 'x' ;
	T_IsDraw = 'x' ;
	L_IsDraw = 'x' ;
	R_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'o' ;

	Invalidate () ;

	CScrollView::OnLButtonDblClk(nFlags, point);
}

// ä��� �� �����ϴ� ��ư
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

// ä��� ���� �������� �ϴ� ��ư
void CGraphicEditorView::OnNofillcolor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_IsFillColor = 'x' ;
}

// ���� �׸��� ���
void CGraphicEditorView::OnDrawtriangle()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
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

// �� �ﰢ�� �׸��� ���
void CGraphicEditorView::OnDrawreversetri()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
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

// �β� ���� ��ư ó����
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

// ���� �ﰢ�� �׸��� ���
void CGraphicEditorView::OnRightangledtri()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
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

// �� ���� �ﰢ�� �׸��� ���
void CGraphicEditorView::OnRRrightangledtri()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
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

// ������ -> ���� �ﰢ�� �׸��� ���
void CGraphicEditorView::OnRighttolefttri()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
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

// ���� -> ������ �ﰢ�� �׸��� ���
void CGraphicEditorView::OnLefttorighttri()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
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

// ��Ʈ �ٲٱ� ��ư
void CGraphicEditorView::OnFont()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFontDialog dlg ;
	if( dlg.DoModal() == IDOK )
	{
		dlg.GetCurrentFont (&Text_lf) ;
		Text_Rect.top = Text_lf.lfHeight / 2 ;
		Text_Rect.bottom = Text_lf.lfHeight / 2 ;
		Text_IsFont = 'o' ;
	}
}

// �ؽ�Ʈ ���� ���
void CGraphicEditorView::OnText()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'o' ;
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
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}


void CGraphicEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if ( Text_IsContinue == 'o' ) {
	}

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}