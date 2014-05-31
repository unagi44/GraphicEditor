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
END_MESSAGE_MAP()

// CGraphicEditorView ����/�Ҹ�

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

	IsNormal = 'o' ;

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
		CPen pen ( PS_SOLID, 1, RGB (0, 0, 0) );
		CPen *Draw_Pen = pDC -> SelectObject(&pen);
		L_Insert.Start = pDoc -> L_Line.GetAt (i).Start ;
		L_Insert.Last = pDoc -> L_Line.GetAt (i).Last ;
		pDC -> MoveTo ( L_Insert.Start ) ;	// ���� ������ġ
		pDC -> LineTo ( L_Insert.Last ) ;	// ���� ������
		pDC->SelectObject(Draw_Pen);
	}

	// �׸� ���ڸ� ��� ȭ�鿡 ���ϴ�.
	for ( int i = 0 ; i < pDoc -> R_Rec.GetCount () ; i++ ) {
		pDC -> SelectStockObject ( NULL_BRUSH ) ;
		pDC -> Rectangle ( pDoc -> R_Rec [i].left, pDoc -> R_Rec [i].top, pDoc -> R_Rec [i].right, pDoc -> R_Rec [i].bottom ) ;
	}
	
	// �׸� PolyLine�� ��� ȭ�鿡 ���ϴ�.
	for ( int i = 0 ; i < pDoc -> P_Poly.GetCount () ; i++ ) {
		for ( int j = 0 ; j < pDoc -> P_Poly.GetAt (i).Poly_point.GetCount () - 1 ; j++ ) {

			CPen pen ( PS_SOLID, 1, RGB (0, 0, 0) );
			CPen *Draw_Pen = pDC -> SelectObject(&pen);
			P_PointStart = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j) ;
			P_PointLast = pDoc -> P_Poly.GetAt (i).Poly_point.GetAt (j+1) ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen);

			// ���� �׸��� �ִ� PolyLine�� Skeleton�� �����ݴϴ�.
			if ( i == pDoc -> P_Poly.GetCount () - 1 && P_IsDraw == 'o' && P_Insert.Poly_point.GetCount () != 0 ) {
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
		pDC -> SelectStockObject ( NULL_BRUSH ) ;
		pDC -> Ellipse ( pDoc -> E_Ellipse [i].left, pDoc -> E_Ellipse [i].top, pDoc -> E_Ellipse [i].right, pDoc -> E_Ellipse [i].bottom ) ;

		// ���� ���� �׸��� �ִ� ���¶�� �׵θ� ���簢���� �׷��ݴϴ�.
		if ( pDoc -> E_Ellipse.GetCount () - 1 == i && E_CanMove == 'o' ) {
			CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
			CPen *Draw_Pen = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> E_Ellipse.GetAt (i).left  ;
			P_PointStart.y = pDoc -> E_Ellipse.GetAt (i).top  ;
			P_PointLast.x = pDoc -> E_Ellipse.GetAt (i).right ;
			P_PointLast.y = pDoc -> E_Ellipse.GetAt (i).top ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen);

			CPen pen2 ( PS_DOT, 1.8, RGB (100, 100, 255) );
			CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> E_Ellipse.GetAt (i).left  ;
			P_PointStart.y = pDoc -> E_Ellipse.GetAt (i).top  ;
			P_PointLast.x = pDoc -> E_Ellipse.GetAt (i).left ;
			P_PointLast.y = pDoc -> E_Ellipse.GetAt (i).bottom ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen2);

			CPen pen3 ( PS_DOT, 1.8, RGB (100, 100, 255) );
			CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> E_Ellipse.GetAt (i).left  ;
			P_PointStart.y = pDoc -> E_Ellipse.GetAt (i).bottom  ;
			P_PointLast.x = pDoc -> E_Ellipse.GetAt (i).right ;
			P_PointLast.y = pDoc -> E_Ellipse.GetAt (i).bottom ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen3);

			CPen pen4 ( PS_DOT, 1.8, RGB (100, 100, 255) );
			CPen *Draw_Pen4 = pDC -> SelectObject(&pen);
			P_PointStart.x = pDoc -> E_Ellipse.GetAt (i).right  ;
			P_PointStart.y = pDoc -> E_Ellipse.GetAt (i).top  ;
			P_PointLast.x = pDoc -> E_Ellipse.GetAt (i).right ;
			P_PointLast.y = pDoc -> E_Ellipse.GetAt (i).bottom ;
			pDC -> MoveTo ( P_PointStart ) ;		// ���� ������ġ
			pDC -> LineTo ( P_PointLast ) ;		// ���� ������
			pDC->SelectObject(Draw_Pen4);
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
	}
	// PolyLine�� ����ؼ� �׸��� ���
	else if ( P_IsContinue == 'o') {
		// PolyLine�� Skeleton�� 2���� ���
		if ( P_CurrentPoint == 1 ) {
			// ������ ������������ �����Ϸ��� ��쿣 ��� �׸��� �ְ� �Ѵ�.
			if ( ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 5 &&
				P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 5 &&
				P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 5 &&
				P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 5) ||
				(P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 5 &&
				P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 5 &&
				P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 5 &&
				P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 5) ) ) {

					if ( (P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 5 &&
						  P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 5 &&
						  P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 5 &&
						  P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 5) )
						P_IsStart = 'o' ;
					else
						P_CurrentPoint++ ;

					P_CanMove = 'o' ;
			}
			// PolyLine�� ���������� ����� �״�� ������.
			else if ( P_Insert.Poly_point.GetAt ( P_CurrentPoint ) != point ) {
				P_CanMove = 'x' ;
				P_IsDraw = 'x' ;
				IsNormal = 'o' ;
				P_Insert.Poly_point.RemoveAll () ;
				P_IsContinue = 'x' ;
				Invalidate () ;
			}
		}
		// PolyLine�� Skeleton�� 3�� �̻��� ���
		else {
			// ����, ������ Skeleton�� ������ ��� Skeleton�� �˻��Ͽ�
			// Ŭ���� ��ǥ�� �ش� Skeleton �߿� �ִ��� Ȯ���Ѵ�.
			char P_Flag = 'x' ;
			for ( int i = 1 ; i <= P_CurrentPoint - 1 ; i++ ) {
				if ( P_Insert.Poly_point.GetAt (i).x <= point.x + 5 &&
					 P_Insert.Poly_point.GetAt (i).x >= point.x - 5 &&
					 P_Insert.Poly_point.GetAt (i).y <= point.y + 5 &&
					 P_Insert.Poly_point.GetAt (i).y >= point.y - 5 ) {
					P_ChangeSkeleton = i ;
					P_CanMove = 'o' ;
					P_Flag = 'o' ;
				}
			}

			if ( P_Flag == 'x' ) {
				// ���� Skeleton�� �ǵ帮�� ���� ���� �����Ѵ�.
				if ( (P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 5 &&
					P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 5 &&
					P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 5 &&
					P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 5) ) {
						P_IsStart = 'o' ;
						P_CanMove = 'o' ;
				}
				// ������ Skeleton�� �ǵ帮�� �� Skeleton�� �����Ѵ�.
				else if ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 5 &&
					P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 5 &&
					P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 5 &&
					P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 5) ) {
						P_CanMove = 'o' ;
						P_CurrentPoint++ ;
				}
				// PolyLine�� ���������� ����� �״�� ������.
				else if ( P_Insert.Poly_point.GetAt ( P_CurrentPoint ) != point ) {
					P_CanMove = 'x' ;
					P_IsDraw = 'x' ;
					IsNormal = 'o' ;
					P_Insert.Poly_point.RemoveAll () ;
					P_IsContinue = 'x' ;
					Invalidate () ;
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
	}
	// ���� �׸��� ���
	else if ( E_IsDraw == 'o' ) {
		E_Insert.left = point.x ;
		E_Insert.right = point.x ;
		E_Insert.top = point.y ;
		E_Insert.bottom = point.y ;

		pDoc -> E_Ellipse.Add ( R_Rect ) ;
		R_Current = pDoc -> E_Ellipse.GetCount () - 1 ;
		E_CanMove = 'o' ;
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
		pDoc->L_Line.SetAt ( L_Current, L_Insert ) ;
		Invalidate () ;
	}
	// ���� �׸��� ������ �巡�� �ϴ� ���
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// ���� �׸��� Ŭ���� �� ���
	if ( L_IsDraw == 'o' ) {
		L_Insert.Last = point ;
		pDoc->L_Line.SetAt ( L_Current, L_Insert ) ;
		Invalidate (false) ;
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
		}
		// ���� ��ǥ�� Ŭ��, �� ��찡 �ƴ϶�� �׸��� ���
		else {
			// ���� ������ Skeleton�� ������ ���
			if ( P_IsStart == 'x' && P_ChangeSkeleton == 0 ) {
				P_Insert.Poly_point.SetAt ( P_CurrentPoint, point ) ;
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( P_CurrentPoint, point ) ;
				Invalidate (false) ;
			}
			// ���� ù��° Skeleton�� ������ ���
			else if ( P_IsStart == 'o' ) {
				P_Insert.Poly_point.SetAt ( 0, point ) ;
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( 0, point ) ;
				Invalidate (false) ;
				P_IsStart = 'x' ;
			}
			// ���� ù��°, ������ Skeleton�� �ٸ� Skeleton�� ������ ���
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

	CScrollView::OnLButtonUp(nFlags, point);
}

// �� �׸��� ���ٸ� ������ ��� �Ҹ��� ���ϴ�.
void CGraphicEditorView::OnDrawline()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

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
				if ( ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 5 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 5 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 5 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 5) ||
						(P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 5 &&
						P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 5 &&
						P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 5 &&
						P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 5) ) ) {
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
					if ( P_Insert.Poly_point.GetAt (i).x <= point.x + 5 &&
						P_Insert.Poly_point.GetAt (i).x >= point.x - 5 &&
						P_Insert.Poly_point.GetAt (i).y <= point.y + 5 &&
						P_Insert.Poly_point.GetAt (i).y >= point.y - 5 ) {
							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
							P_Flag = 'o' ;
					}
				}

				if ( P_Flag == 'x' ) {
					// ���� Skeleton�� ã���� Ŀ���� 4���� Ŀ���� �����Ѵ�.
					if ( (P_Insert.Poly_point.GetAt ( 0 ).x <= point.x + 5 &&
						P_Insert.Poly_point.GetAt ( 0 ).x >= point.x - 5 &&
						P_Insert.Poly_point.GetAt ( 0 ).y <= point.y + 5 &&
						P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 5) ) {
							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
					}
					// ������ Skeleton�� ã���� Ŀ���� 4���� Ŀ���� �����Ѵ�.
					else if ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 5 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 5 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 5 &&
						P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 5) ) {
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

// PolyLine �׸��� ���ٸ� ������ ��� �Ҹ��� ���ϴ�.
void CGraphicEditorView::OnDrawpoly()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

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

// �� �׸��� ���ٸ� ������ ��� �Ҹ��� ���ϴ�.
void CGraphicEditorView::OnDrawellipse()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
	P_Insert.Poly_point.RemoveAll () ;
	P_CanMove = 'x' ;
	P_IsContinue = 'x' ;
	P_IsDraw = 'x' ;
	//IsNormal = 'x' ;

	Invalidate (false) ;
}