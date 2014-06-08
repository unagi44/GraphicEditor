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
#include "FillPattern.h"
#include "LinePattern.h"

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
ON_COMMAND(ID_RRightAngledTri, &CGraphicEditorView::OnRRrightangledtri)
ON_COMMAND(ID_RightToLeftTri, &CGraphicEditorView::OnRighttolefttri)
ON_COMMAND(ID_LeftToRightTri, &CGraphicEditorView::OnLefttorighttri)
ON_COMMAND(ID_Font, &CGraphicEditorView::OnFont)
ON_COMMAND(ID_Text, &CGraphicEditorView::OnText)
ON_WM_KEYDOWN()
ON_WM_CHAR()
ON_COMMAND(ID_FillPattern, &CGraphicEditorView::OnFillpattern)
ON_COMMAND(ID_LinePattern, &CGraphicEditorView::OnLinepattern)
ON_COMMAND(ID_TextBGColor, &CGraphicEditorView::OnTextbgcolor)
ON_COMMAND(ID_Group, &CGraphicEditorView::OnGroup)
ON_COMMAND(ID_GroupX, &CGraphicEditorView::OnGroupx)
END_MESSAGE_MAP()

// CGraphicEditorView 생성/소멸

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

	IsNormal = 'o' ;
	m_IsColor = 'x' ;
	m_IsFillColor = 'x' ;
	m_IsThickness = 'x' ;
	m_PSkeleton = 'x' ;
	m_Thickness = 1 ;
	m_IsSelectGroup = 'x' ;

	// 그룹화에 필요한 변수 초기화
	G_IsMakeGroup = 'x' ;
	G_ViewSelection = 'x' ;

	// 이동 툴바에 필요한 변수 초기화
	M_IsMove = 'x' ;
	M_IsSelect = 'x' ;
	M_ChangeLineOnePoint = 'x' ;
	M_IsLineSelect = 'x' ;
	M_IsRectSelect = 'x' ;
	M_ChangeRectSize = 'x' ;
	M_IsChangeRectVerticalTop = 'x' ;
	M_IsChangeRectVerticalBottom = 'x' ;
	M_IsChangeRectSide = 'x' ;
	M_IsChangeRectNW = 'x' ;
	M_IsChangeRectNE = 'x' ;
	M_IsChangeRectSW = 'x' ;
	M_IsChangeRectSE = 'x' ;
	M_IsChangeRectWidthLeft = 'x' ;
	M_IsChangeRectWidthRight = 'x' ;
	M_IsEllipseSelect = 'x' ;
	M_ChangeEllipseSize = 'x' ;
	M_IsChangeEllipseSide = 'x' ;
	M_IsChangeEllipseNW = 'x' ;
	M_IsChangeEllipseNE = 'x' ;
	M_IsChangeEllipseSW = 'x' ;
	M_IsChangeEllipseSE = 'x' ;
	M_IsChangeEllipseVerticalTop = 'x' ;
	M_IsChangeEllipseVerticalBottom = 'x' ;
	M_IsChangeEllipseWidthLeft = 'x' ;
	M_IsChangeEllipseWidthRight = 'x' ;

	// 텍스트 삽입에 필요한 변수 초기화
	Text_IsText = 'x' ;
	Text_IsFont = 'x' ;
	Text_IsKeyDown = 'x' ;
	Text_IsChange = 'x' ;
	Text_IsBGColor = 'x' ;

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
	int Text_Number = 0 ;
	int G_Number = 0 ;

	// 모든 객체의 수만큼 출력을 합니다.
	// 그린 순서에 따라 출력됩니다.
	for ( int i = 0 ; i < pDoc->What.GetCount () ; i++ ) {

		// 선 객체일 경우
		if ( pDoc -> What.GetAt (i) == _T ("L") ) {
			// 색상을 가지지 않을 경우의 출력
			if ( pDoc -> L_Line.GetAt (L_Number).L_Color == RGB (0,0,0) ) {
				if ( pDoc -> L_Line.GetAt (L_Number).Pattern == 1 ) {
					CPen pen ( PS_SOLID, pDoc -> L_Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
					L_Insert.Last = pDoc -> L_Line.GetAt (L_Number).Last ;
					pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
					pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
					pDC->SelectObject(Draw_Pen);
				}
				else if ( pDoc -> L_Line.GetAt (L_Number).Pattern == 2 ) {
					CPen pen ( PS_DASH, pDoc -> L_Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
					L_Insert.Last = pDoc -> L_Line.GetAt (L_Number).Last ;
					pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
					pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
					pDC->SelectObject(Draw_Pen);
				}
				else if ( pDoc -> L_Line.GetAt (L_Number).Pattern == 3 ) {
					CPen pen ( PS_DOT, pDoc -> L_Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
					L_Insert.Last = pDoc -> L_Line.GetAt (L_Number).Last ;
					pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
					pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
					pDC->SelectObject(Draw_Pen);
				}
				else if ( pDoc -> L_Line.GetAt (L_Number).Pattern == 4 ) {
					CPen pen ( PS_DASHDOT, pDoc -> L_Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
					L_Insert.Last = pDoc -> L_Line.GetAt (L_Number).Last ;
					pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
					pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
					pDC->SelectObject(Draw_Pen);
				}
				else if ( pDoc -> L_Line.GetAt (L_Number).Pattern == 5 ) {
					CPen pen ( PS_DASHDOTDOT, pDoc -> L_Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
					L_Insert.Last = pDoc -> L_Line.GetAt (L_Number).Last ;
					pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
					pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
					pDC->SelectObject(Draw_Pen);
				}
			}
			// 특정 색상을 가졌을 경우의 출력
			else {
				if ( pDoc -> L_Line.GetAt (L_Number).Pattern == 1 ) {
					CPen pen ( PS_SOLID, pDoc -> L_Line.GetAt (L_Number).Thickness, pDoc -> L_Line.GetAt (L_Number).L_Color ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
					L_Insert.Last = pDoc -> L_Line.GetAt (L_Number).Last ;
					pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
					pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
					pDC->SelectObject(Draw_Pen);
				}
				else if (pDoc -> L_Line.GetAt (L_Number).Pattern == 2 ) {
					CPen pen ( PS_DASH, pDoc -> L_Line.GetAt (L_Number).Thickness, pDoc -> L_Line.GetAt (L_Number).L_Color ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
					L_Insert.Last = pDoc -> L_Line.GetAt (L_Number).Last ;
					pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
					pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
					pDC->SelectObject(Draw_Pen);
				}
				else if (pDoc -> L_Line.GetAt (L_Number).Pattern == 3 ) {
					CPen pen ( PS_DOT, pDoc -> L_Line.GetAt (L_Number).Thickness, pDoc -> L_Line.GetAt (L_Number).L_Color ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
					L_Insert.Last = pDoc -> L_Line.GetAt (L_Number).Last ;
					pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
					pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
					pDC->SelectObject(Draw_Pen);
				}
				else if (pDoc -> L_Line.GetAt (L_Number).Pattern == 4 ) {
					CPen pen ( PS_DASHDOT, pDoc -> L_Line.GetAt (L_Number).Thickness, pDoc -> L_Line.GetAt (L_Number).L_Color ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
					L_Insert.Last = pDoc -> L_Line.GetAt (L_Number).Last ;
					pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
					pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
					pDC->SelectObject(Draw_Pen);
				}
				else if (pDoc -> L_Line.GetAt (L_Number).Pattern == 5 ) {
					CPen pen ( PS_DASHDOTDOT, pDoc -> L_Line.GetAt (L_Number).Thickness, pDoc -> L_Line.GetAt (L_Number).L_Color ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					L_Insert.Start = pDoc -> L_Line.GetAt (L_Number).Start ;
					L_Insert.Last = pDoc -> L_Line.GetAt (L_Number).Last ;
					pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
					pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
					pDC->SelectObject(Draw_Pen);
				}
			}

			// 만약 이동시키고 있는 중이라면
			if ( M_Number == L_Number && M_IsDraw == 'o' && M_What == _T ("L") && M_ChangeLineOnePoint == 'x' ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;

				pDC -> SelectStockObject ( NULL ) ;
				CRect Rect, Rect2 ;
				Rect.top = pDoc -> L_Line.GetAt ( L_Number ).Start.y - 4 ;
				Rect.bottom = pDoc -> L_Line.GetAt ( L_Number ).Start.y + 4 ;
				Rect.left = pDoc -> L_Line.GetAt ( L_Number ).Start.x - 4 ;
				Rect.right = pDoc -> L_Line.GetAt ( L_Number ).Start.x + 4 ;

				Rect2.top = pDoc -> L_Line.GetAt ( L_Number ).Last.y - 4 ;
				Rect2.bottom = pDoc -> L_Line.GetAt ( L_Number ).Last.y + 4 ;
				Rect2.left = pDoc -> L_Line.GetAt ( L_Number ).Last.x - 4 ;
				Rect2.right = pDoc -> L_Line.GetAt ( L_Number ).Last.x + 4 ;

				pDC -> Rectangle ( Rect.left, Rect.top, Rect.right, Rect.bottom ) ;
				pDC -> Rectangle ( Rect2.left, Rect2.top, Rect2.right, Rect2.bottom ) ;
			}
			L_Number++ ;
		}

		// 상자 객체일 경우
		else if ( pDoc -> What.GetAt (i) == _T ("R") ) {

			// 만약 변경 시키는 중이라면
			if ( M_Number == R_Number && M_IsDraw == 'o' && M_What == _T ("R") ) {
				if ( M_ChangeRectSize == 'o' ) {
					CPen pen;
					pen.CreatePen( PS_DOT, 1.8, RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					M_ChangeRect.left -= pDoc -> R_Thickness.GetAt ( M_Number ) / 2 ;
					M_ChangeRect.right += pDoc -> R_Thickness.GetAt ( M_Number ) / 2 ;
					M_ChangeRect.top -= pDoc -> R_Thickness.GetAt ( M_Number ) / 2 ;
					M_ChangeRect.bottom += pDoc -> R_Thickness.GetAt ( M_Number ) / 2 ;
					pDC -> Rectangle ( M_ChangeRect.left, M_ChangeRect.top, M_ChangeRect.right, M_ChangeRect.bottom ) ;
					pDC -> SelectObject ( oldPen ) ;
					M_ChangeRect.left += pDoc -> R_Thickness.GetAt ( M_Number ) / 2 ;
					M_ChangeRect.right -= pDoc -> R_Thickness.GetAt ( M_Number ) / 2 ;
					M_ChangeRect.top += pDoc -> R_Thickness.GetAt ( M_Number ) / 2 ;
					M_ChangeRect.bottom -= pDoc -> R_Thickness.GetAt ( M_Number ) / 2 ;
				}
			}

			// 선 색을 가지지 않았을 경우의 출력
			if ( pDoc -> R_Color.GetAt (R_Number) == RGB (0,0,0) ) {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> R_IsNoFill.GetAt (R_Number) == 'o' ) {
					if ( pDoc -> R_LinePattern.GetAt (R_Number) == 1 ) {
						CPen pen;
						pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 2 ) {
						CPen pen;
						pen.CreatePen( PS_DASH, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 3 ) {
						CPen pen;
						pen.CreatePen( PS_DOT, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 4 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOT, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 5 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOTDOT, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					if ( pDoc -> R_LinePattern.GetAt (R_Number) == 1 ) {
						CPen pen;
						pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> R_FillPattern.GetAt (R_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldBrush ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 2 ) {
						CPen pen;
						pen.CreatePen( PS_DASH, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> R_FillPattern.GetAt (R_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldBrush ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 3 ) {
						CPen pen;
						pen.CreatePen( PS_DOT, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> R_FillPattern.GetAt (R_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldBrush ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 4 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOT, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> R_FillPattern.GetAt (R_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldBrush ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 5 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOTDOT, pDoc -> R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> R_FillPattern.GetAt (R_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldBrush ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
				}
			}
			// 특정 선 색상을 가졌을 경우의 출력
			else {

				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> R_IsNoFill.GetAt (R_Number) == 'o' ) {
					if ( pDoc -> R_LinePattern.GetAt (R_Number) == 1 ) {
						CPen pen;
						pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC ->SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 2 ) {
						CPen pen;
						pen.CreatePen( PS_DASH, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC ->SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 3 ) {
						CPen pen;
						pen.CreatePen( PS_DOT, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC ->SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 4 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOT, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC ->SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 5 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOTDOT, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC ->SelectObject ( oldPen ) ;
					}
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					if ( pDoc -> R_LinePattern.GetAt (R_Number) == 1 ) {
						CPen pen;
						pen.CreatePen( PS_SOLID, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> R_FillPattern.GetAt (R_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
						pDC -> SelectObject ( oldBrush ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 2 ) {
						CPen pen;
						pen.CreatePen( PS_DASH, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> R_FillPattern.GetAt (R_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
						pDC -> SelectObject ( oldBrush ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 3 ) {
						CPen pen;
						pen.CreatePen( PS_DOT, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> R_FillPattern.GetAt (R_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
						pDC -> SelectObject ( oldBrush ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 4 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOT, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> R_FillPattern.GetAt (R_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
						pDC -> SelectObject ( oldBrush ) ;
					}
					else if ( pDoc -> R_LinePattern.GetAt (R_Number) == 5 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOTDOT, pDoc -> R_Thickness.GetAt (R_Number), pDoc -> R_Color.GetAt (R_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> R_FillPattern.GetAt (R_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;
						else if ( pDoc -> R_FillPattern.GetAt (R_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> R_FillColor.GetAt (R_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Rectangle ( pDoc -> R_Rec [R_Number].left, pDoc -> R_Rec [R_Number].top, pDoc -> R_Rec [R_Number].right, pDoc -> R_Rec [R_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
						pDC -> SelectObject ( oldBrush ) ;
					}
				}
			}

			// 만약 이동시키고 있는 중이라면
			if ( M_Number == R_Number && M_IsDraw == 'o' && M_What == _T ("R") ) {
				if ( M_ChangeRectSize == 'x' ) {
					CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
					pDC -> SelectObject ( Draw_Pen ) ;

					CRect Rect, Rect2, Rect3, Rect4, Rect5, Rect6, Rect7, Rect8 ;
					Rect.top = M_Rect.top - 4 ;
					Rect.bottom = M_Rect.top + 4 ;
					Rect.left = M_Rect.left - 4 ;
					Rect.right = M_Rect.left + 4 ;

					Rect2.top = M_Rect.bottom - 4 ;
					Rect2.bottom = M_Rect.bottom + 4 ;
					Rect2.left = M_Rect.right - 4 ;
					Rect2.right = M_Rect.right + 4 ;

					Rect3.top = M_Rect.top - 4 ;
					Rect3.bottom = M_Rect.top + 4 ;
					Rect3.left = M_Rect.right - 4 ;
					Rect3.right = M_Rect.right + 4 ;

					Rect4.top = M_Rect.bottom - 4 ;
					Rect4.bottom = M_Rect.bottom + 4 ;
					Rect4.left = M_Rect.left - 4 ;
					Rect4.right = M_Rect.left + 4 ;

					Rect5.left = M_Rect.left + (M_Rect.right - M_Rect.left) / 2 - 4 ;
					Rect5.right = M_Rect.left + (M_Rect.right - M_Rect.left) / 2 + 4 ;
					Rect5.top = M_Rect.bottom - 4 ;
					Rect5.bottom = M_Rect.bottom + 4 ;

					Rect6.left = M_Rect.left + (M_Rect.right - M_Rect.left) / 2 - 4 ;
					Rect6.right = M_Rect.left + (M_Rect.right - M_Rect.left) / 2 + 4 ;
					Rect6.top = M_Rect.top - 4 ;
					Rect6.bottom = M_Rect.top + 4 ;

					Rect7.left = M_Rect.left - 4 ;
					Rect7.right = M_Rect.left + 4 ;
					Rect7.top = M_Rect.top + (M_Rect.bottom - M_Rect.top) / 2 - 4 ;
					Rect7.bottom = M_Rect.top + (M_Rect.bottom - M_Rect.top) / 2 + 4 ;

					Rect8.left = M_Rect.right - 4 ;
					Rect8.right = M_Rect.right + 4 ;
					Rect8.top = M_Rect.top + (M_Rect.bottom - M_Rect.top) / 2 - 4 ;
					Rect8.bottom = M_Rect.top + (M_Rect.bottom - M_Rect.top) / 2 + 4 ;

					pDC -> SelectStockObject ( NULL ) ;

					pDC -> Rectangle ( Rect.left, Rect.top, Rect.right, Rect.bottom ) ;
					pDC -> Rectangle ( Rect2.left, Rect2.top, Rect2.right, Rect2.bottom ) ;
					pDC -> Rectangle ( Rect3.left, Rect3.top, Rect3.right, Rect3.bottom ) ;
					pDC -> Rectangle ( Rect4.left, Rect4.top, Rect4.right, Rect4.bottom ) ;
					pDC -> Rectangle ( Rect5.left, Rect5.top, Rect5.right, Rect5.bottom ) ;
					pDC -> Rectangle ( Rect6.left, Rect6.top, Rect6.right, Rect6.bottom ) ;
					pDC -> Rectangle ( Rect7.left, Rect7.top, Rect7.right, Rect7.bottom ) ;
					pDC -> Rectangle ( Rect8.left, Rect8.top, Rect8.right, Rect8.bottom ) ;
				}
			}
			R_Number++ ;
		}

		// PolyLine 객체인 경우
		else if ( pDoc -> What.GetAt (i) == _T ("P") ) {
			int j ;
			for ( j = 0 ; j < pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetCount () - 1 ; j++ ) {

				// PolyLine이 색상을 가지지 않을 경우의 출력
				if ( pDoc -> P_Poly.GetAt (P_Number).P_Color == RGB (0,0,0) ) {
					if ( pDoc -> P_Poly.GetAt (P_Number).Pattern == 1 ) {
						CPen pen ( PS_SOLID, pDoc -> P_Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
						P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
					}
					else if ( pDoc -> P_Poly.GetAt (P_Number).Pattern == 2 ) {
						CPen pen ( PS_DASH, pDoc -> P_Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
						P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
					}
					else if ( pDoc -> P_Poly.GetAt (P_Number).Pattern == 3 ) {
						CPen pen ( PS_DOT, pDoc -> P_Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
						P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
					}
					else if ( pDoc -> P_Poly.GetAt (P_Number).Pattern == 4 ) {
						CPen pen ( PS_DASHDOT, pDoc -> P_Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
						P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
					}
					else if ( pDoc -> P_Poly.GetAt (P_Number).Pattern == 5 ) {
						CPen pen ( PS_DASHDOTDOT, pDoc -> P_Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
						CPen *Draw_Pen = pDC -> SelectObject(&pen);
						P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
						P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
					}

				}
				// PolyLine이 지정된 색상을 가졌을 경우의 출력
				else {
					if ( pDoc -> P_Poly.GetAt (P_Number).Pattern == 1 ) {
						CPen pen ( PS_SOLID, pDoc -> P_Poly.GetAt (P_Number).thickness, pDoc -> P_Poly.GetAt (P_Number).P_Color ) ;
						CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
						P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
						P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
					}
					else if ( pDoc -> P_Poly.GetAt (P_Number).Pattern == 2 ) {
						CPen pen ( PS_DASH, pDoc -> P_Poly.GetAt (P_Number).thickness, pDoc -> P_Poly.GetAt (P_Number).P_Color ) ;
						CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
						P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
						P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
					}
					else if ( pDoc -> P_Poly.GetAt (P_Number).Pattern == 3 ) {
						CPen pen ( PS_DOT, pDoc -> P_Poly.GetAt (P_Number).thickness, pDoc -> P_Poly.GetAt (P_Number).P_Color ) ;
						CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
						P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
						P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
					}
					else if ( pDoc -> P_Poly.GetAt (P_Number).Pattern == 4 ) {
						CPen pen ( PS_DASHDOT, pDoc -> P_Poly.GetAt (P_Number).thickness, pDoc -> P_Poly.GetAt (P_Number).P_Color ) ;
						CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
						P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
						P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
					}
					else if ( pDoc -> P_Poly.GetAt (P_Number).Pattern == 5 ) {
						CPen pen ( PS_DASHDOTDOT, pDoc -> P_Poly.GetAt (P_Number).thickness, pDoc -> P_Poly.GetAt (P_Number).P_Color ) ;
						CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
						P_PointStart = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
						P_PointLast = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
						pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
						pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
						pDC->SelectObject(Draw_Pen);
					}
				}
				
				// 만약 이동시키고 있는 중이라면
				if ( M_Number == P_Number && M_IsDraw == 'o' && M_What == _T ("P") ) {
					CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
					pDC -> SelectObject ( Draw_Pen ) ;
				}

				// 현재 그리고 있거나 PolyLine을 변경하는 상태라면 Skeleton을 보여줍니다.
				if ( (pDoc -> P_Poly.GetCount ()  == P_Number + 1 && P_IsDraw == 'o' && P_Insert.Poly_point.GetSize () > 0)
					 || (M_Number == P_Number && M_IsDraw == 'o' && M_What == _T ("P")) ) {

					pDC -> SelectStockObject ( NULL ) ;
					CPen pen ( PS_SOLID, 1.8, RGB (0,0,0) ) ;
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

					pDC -> Rectangle ( ChangeRect ) ;
					pDC->SelectObject(Draw_Pen2);

					if ( m_PSkeleton == 'o' && j == PSkeleton ) {
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						CPen pen2 ( PS_DOT, 1.8, RGB (150,0,0) ) ;
						CPen *Draw_Pen2 = pDC -> SelectObject (&pen2) ;
						ChangeRect.left = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).x - 8 ;
						ChangeRect.right = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).x + 8 ;
						ChangeRect.top = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).y - 8 ;
						ChangeRect.bottom = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).y + 8 ;

						pDC -> Rectangle ( ChangeRect ) ;
						pDC->SelectObject(Draw_Pen2);
					}
				}
			}
			if ( m_PSkeleton == 'o' && j == PSkeleton && M_Number == P_Number ) {
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				CPen pen2 ( PS_DOT, 1.8, RGB (150,0,0) ) ;
				CPen *Draw_Pen2 = pDC -> SelectObject (&pen2) ;
				ChangeRect.left = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).x - 8 ;
				ChangeRect.right = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).x + 8 ;
				ChangeRect.top = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).y - 8 ;
				ChangeRect.bottom = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (j).y + 8 ;

				pDC -> Rectangle ( ChangeRect ) ;
				pDC->SelectObject(Draw_Pen2);
			}

			P_Number++ ;
		}

		// 원 객체일 경우
		else if ( pDoc -> What.GetAt (i) == _T ("E") ) {

			// 만약 변경 시키는 중이라면
			if ( M_Number == E_Number && M_IsDraw == 'o' && M_What == _T ("E") ) {
				if ( M_ChangeEllipseSize == 'o' ) {
					CPen pen;
					pen.CreatePen( PS_DOT, 1.8, RGB (0,0,0) ) ;
					CPen* oldPen = pDC->SelectObject( &pen ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					M_ChangeRect.left -= pDoc -> E_Thickness.GetAt ( M_Number ) / 2 ;
					M_ChangeRect.right += pDoc -> E_Thickness.GetAt ( M_Number ) / 2 ;
					M_ChangeRect.top -= pDoc -> E_Thickness.GetAt ( M_Number ) / 2 ;
					M_ChangeRect.bottom += pDoc -> E_Thickness.GetAt ( M_Number ) / 2 ;
					pDC -> Ellipse ( M_ChangeRect.left, M_ChangeRect.top, M_ChangeRect.right, M_ChangeRect.bottom ) ;
					pDC -> SelectObject ( oldPen ) ;
					M_ChangeRect.left += pDoc -> E_Thickness.GetAt ( M_Number ) / 2 ;
					M_ChangeRect.right -= pDoc -> E_Thickness.GetAt ( M_Number ) / 2 ;
					M_ChangeRect.top += pDoc -> E_Thickness.GetAt ( M_Number ) / 2 ;
					M_ChangeRect.bottom -= pDoc -> E_Thickness.GetAt ( M_Number ) / 2 ;
				}
			}

			// 선 색을 가지지 않았을 경우의 출력
			if ( pDoc -> E_Color.GetAt (E_Number) == RGB (0,0,0) ) {
				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> E_IsNoFill.GetAt (E_Number) == 'o' ) {
					if ( pDoc -> E_LinePattern.GetAt (E_Number) == 1 ) {
						CPen pen;
						pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 2 ) {
						CPen pen;
						pen.CreatePen( PS_DASH, pDoc -> E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 3 ) {
						CPen pen;
						pen.CreatePen( PS_DOT, pDoc -> E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 4 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOT, pDoc -> E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 5 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOTDOT, pDoc -> E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					if ( pDoc -> E_LinePattern.GetAt (E_Number) == 1 ) {
						CPen pen;
						pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> E_FillPattern.GetAt (E_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldBrush ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 2 ) {
						CPen pen;
						pen.CreatePen( PS_DASH, pDoc -> E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> E_FillPattern.GetAt (E_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldBrush ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 3 ) {
						CPen pen;
						pen.CreatePen( PS_DOT, pDoc -> E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> E_FillPattern.GetAt (E_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldBrush ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 4 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOT, pDoc -> E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> E_FillPattern.GetAt (E_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldBrush ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 5 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOTDOT, pDoc -> E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> E_FillPattern.GetAt (E_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldBrush ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
				}
			}
			// 특정 선 색상을 가졌을 경우의 출력
			else {
				// 채우기 색상을 가지지 않았을 경우의 출력
				if ( pDoc -> E_IsNoFill.GetAt (E_Number) == 'o' ) {
					if ( pDoc -> E_LinePattern.GetAt (E_Number) == 1 ) {
						CPen pen;
						pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (E_Number), pDoc -> E_Color.GetAt (E_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 2 ) {
						CPen pen;
						pen.CreatePen( PS_DASH, pDoc -> E_Thickness.GetAt (E_Number), pDoc -> E_Color.GetAt (E_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 3 ) {
						CPen pen;
						pen.CreatePen( PS_DOT, pDoc -> E_Thickness.GetAt (E_Number), pDoc -> E_Color.GetAt (E_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 4 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOT, pDoc -> E_Thickness.GetAt (E_Number), pDoc -> E_Color.GetAt (E_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 5 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOTDOT, pDoc -> E_Thickness.GetAt (E_Number), pDoc -> E_Color.GetAt (E_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						pDC -> SelectStockObject ( NULL_BRUSH ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
					}
				}
				// 채우기 색상을 가졌을 경우의 출력
				else {
					if ( pDoc -> E_LinePattern.GetAt (E_Number) == 1 ) {
						CPen pen;
						pen.CreatePen( PS_SOLID, pDoc -> E_Thickness.GetAt (E_Number), pDoc -> E_Color.GetAt (E_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> E_FillPattern.GetAt (E_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
						pDC -> SelectObject ( oldBrush ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 2 ) {
						CPen pen;
						pen.CreatePen( PS_DASH, pDoc -> E_Thickness.GetAt (E_Number), pDoc -> E_Color.GetAt (E_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> E_FillPattern.GetAt (E_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
						pDC -> SelectObject ( oldBrush ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 3 ) {
						CPen pen;
						pen.CreatePen( PS_DOT, pDoc -> E_Thickness.GetAt (E_Number), pDoc -> E_Color.GetAt (E_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> E_FillPattern.GetAt (E_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
						pDC -> SelectObject ( oldBrush ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 4 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOT, pDoc -> E_Thickness.GetAt (E_Number), pDoc -> E_Color.GetAt (E_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> E_FillPattern.GetAt (E_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
						pDC -> SelectObject ( oldBrush ) ;
					}
					else if ( pDoc -> E_LinePattern.GetAt (E_Number) == 5 ) {
						CPen pen;
						pen.CreatePen( PS_DASHDOTDOT, pDoc -> E_Thickness.GetAt (E_Number), pDoc -> E_Color.GetAt (E_Number) ) ;
						CPen* oldPen = pDC->SelectObject( &pen ) ;
						CBrush brush;
						if ( pDoc -> E_FillPattern.GetAt (E_Number) == 1 )
							brush.CreateSolidBrush( pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 2 )
							brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 3 )
							brush.CreateHatchBrush ( HS_CROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 4 )
							brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 5 )
							brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 6 )
							brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;
						else if ( pDoc -> E_FillPattern.GetAt (E_Number) == 7 )
							brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> E_FillColor.GetAt (E_Number) ) ;

						CBrush* oldBrush = pDC->SelectObject( &brush ) ;
						pDC -> Ellipse ( pDoc -> E_Ellipse [E_Number].left, pDoc -> E_Ellipse [E_Number].top, pDoc -> E_Ellipse [E_Number].right, pDoc -> E_Ellipse [E_Number].bottom ) ;
						pDC -> SelectObject ( oldPen ) ;
						pDC -> SelectObject ( oldBrush ) ;
					}
				}
			}

			// 만약 이동시키고 있는 중이라면
			if ( M_Number == E_Number && M_IsDraw == 'o' && M_What == _T ("E") ) {
				if ( M_ChangeRectSize == 'x' ) {
					CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
					pDC -> SelectObject ( Draw_Pen ) ;

					CRect Rect, Rect2, Rect3, Rect4, Rect5, Rect6, Rect7, Rect8 ;
					Rect.top = M_Rect.top - 4 ;
					Rect.bottom = M_Rect.top + 4 ;
					Rect.left = M_Rect.left - 4 ;
					Rect.right = M_Rect.left + 4 ;

					Rect2.top = M_Rect.bottom - 4 ;
					Rect2.bottom = M_Rect.bottom + 4 ;
					Rect2.left = M_Rect.right - 4 ;
					Rect2.right = M_Rect.right + 4 ;

					Rect3.top = M_Rect.top - 4 ;
					Rect3.bottom = M_Rect.top + 4 ;
					Rect3.left = M_Rect.right - 4 ;
					Rect3.right = M_Rect.right + 4 ;

					Rect4.top = M_Rect.bottom - 4 ;
					Rect4.bottom = M_Rect.bottom + 4 ;
					Rect4.left = M_Rect.left - 4 ;
					Rect4.right = M_Rect.left + 4 ;

					Rect5.left = M_Rect.left + (M_Rect.right - M_Rect.left) / 2 - 4 ;
					Rect5.right = M_Rect.left + (M_Rect.right - M_Rect.left) / 2 + 4 ;
					Rect5.top = M_Rect.bottom - 4 ;
					Rect5.bottom = M_Rect.bottom + 4 ;

					Rect6.left = M_Rect.left + (M_Rect.right - M_Rect.left) / 2 - 4 ;
					Rect6.right = M_Rect.left + (M_Rect.right - M_Rect.left) / 2 + 4 ;
					Rect6.top = M_Rect.top - 4 ;
					Rect6.bottom = M_Rect.top + 4 ;

					Rect7.left = M_Rect.left - 4 ;
					Rect7.right = M_Rect.left + 4 ;
					Rect7.top = M_Rect.top + (M_Rect.bottom - M_Rect.top) / 2 - 4 ;
					Rect7.bottom = M_Rect.top + (M_Rect.bottom - M_Rect.top) / 2 + 4 ;

					Rect8.left = M_Rect.right - 4 ;
					Rect8.right = M_Rect.right + 4 ;
					Rect8.top = M_Rect.top + (M_Rect.bottom - M_Rect.top) / 2 - 4 ;
					Rect8.bottom = M_Rect.top + (M_Rect.bottom - M_Rect.top) / 2 + 4 ;

					pDC -> SelectStockObject ( NULL ) ;

					pDC -> Rectangle ( Rect.left, Rect.top, Rect.right, Rect.bottom ) ;
					pDC -> Rectangle ( Rect2.left, Rect2.top, Rect2.right, Rect2.bottom ) ;
					pDC -> Rectangle ( Rect3.left, Rect3.top, Rect3.right, Rect3.bottom ) ;
					pDC -> Rectangle ( Rect4.left, Rect4.top, Rect4.right, Rect4.bottom ) ;
					pDC -> Rectangle ( Rect5.left, Rect5.top, Rect5.right, Rect5.bottom ) ;
					pDC -> Rectangle ( Rect6.left, Rect6.top, Rect6.right, Rect6.bottom ) ;
					pDC -> Rectangle ( Rect7.left, Rect7.top, Rect7.right, Rect7.bottom ) ;
					pDC -> Rectangle ( Rect8.left, Rect8.top, Rect8.right, Rect8.bottom ) ;
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
				if ( pDoc -> T_IsNoFill.GetAt (T_Number) == 'o' ) {
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
					if ( pDoc -> T_FillPattern.GetAt (T_Number) == 1 )
						brush.CreateSolidBrush( pDoc -> T_FillColor.GetAt (T_Number) ) ;
					else if ( pDoc -> T_FillPattern.GetAt (T_Number) == 2 )
						brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> T_FillColor.GetAt (T_Number) ) ;
					else if ( pDoc -> T_FillPattern.GetAt (T_Number) == 3 )
						brush.CreateHatchBrush ( HS_CROSS, pDoc -> T_FillColor.GetAt (T_Number) ) ;
					else if ( pDoc -> T_FillPattern.GetAt (T_Number) == 4 )
						brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> T_FillColor.GetAt (T_Number) ) ;
					else if ( pDoc -> T_FillPattern.GetAt (T_Number) == 5 )
						brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> T_FillColor.GetAt (T_Number) ) ;
					else if ( pDoc -> T_FillPattern.GetAt (T_Number) == 6 )
						brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> T_FillColor.GetAt (T_Number) ) ;
					else if ( pDoc -> T_FillPattern.GetAt (T_Number) == 7 )
						brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> T_FillColor.GetAt (T_Number) ) ;

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
				if ( pDoc -> T_IsNoFill.GetAt (T_Number) == 'o' ) {
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
					if ( pDoc -> T_FillPattern.GetAt (T_Number) == 1 )
						brush.CreateSolidBrush( pDoc -> T_FillColor.GetAt (T_Number) ) ;
					else if ( pDoc -> T_FillPattern.GetAt (T_Number) == 2 )
						brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> T_FillColor.GetAt (T_Number) ) ;
					else if ( pDoc -> T_FillPattern.GetAt (T_Number) == 3 )
						brush.CreateHatchBrush ( HS_CROSS, pDoc -> T_FillColor.GetAt (T_Number) ) ;
					else if ( pDoc -> T_FillPattern.GetAt (T_Number) == 4 )
						brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> T_FillColor.GetAt (T_Number) ) ;
					else if ( pDoc -> T_FillPattern.GetAt (T_Number) == 5 )
						brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> T_FillColor.GetAt (T_Number) ) ;
					else if ( pDoc -> T_FillPattern.GetAt (T_Number) == 6 )
						brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> T_FillColor.GetAt (T_Number) ) ;
					else if ( pDoc -> T_FillPattern.GetAt (T_Number) == 7 )
						brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> T_FillColor.GetAt (T_Number) ) ;

					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Polygon ( T_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
					pDC -> SelectObject ( oldBrush ) ;		
				}
			}

			// 만약 이동시키고 있는 중이라면
			if ( M_Number == T_Number && M_IsDraw == 'o' && M_What == _T ("T") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;

				CRect Rect, Rect2, Rect3, Rect4 ;
				Rect.top = M_Rect.top - 4 ;
				Rect.bottom = M_Rect.top + 4 ;
				Rect.left = M_Rect.left - 4 ;
				Rect.right = M_Rect.left + 4 ;

				Rect2.top = M_Rect.bottom - 4 ;
				Rect2.bottom = M_Rect.bottom + 4 ;
				Rect2.left = M_Rect.right - 4 ;
				Rect2.right = M_Rect.right + 4 ;

				Rect3.top = M_Rect.top - 4 ;
				Rect3.bottom = M_Rect.top + 4 ;
				Rect3.left = M_Rect.right - 4 ;
				Rect3.right = M_Rect.right + 4 ;

				Rect4.top = M_Rect.bottom - 4 ;
				Rect4.bottom = M_Rect.bottom + 4 ;
				Rect4.left = M_Rect.left - 4 ;
				Rect4.right = M_Rect.left + 4 ;

				pDC -> SelectStockObject ( NULL ) ;
				
				pDC -> Rectangle ( Rect.left, Rect.top, Rect.right, Rect.bottom ) ;
				pDC -> Rectangle ( Rect2.left, Rect2.top, Rect2.right, Rect2.bottom ) ;
				pDC -> Rectangle ( Rect3.left, Rect3.top, Rect3.right, Rect3.bottom ) ;
				pDC -> Rectangle ( Rect4.left, Rect4.top, Rect4.right, Rect4.bottom ) ;
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
				if ( pDoc -> RT_IsNoFill.GetAt (RT_Number) == 'o' ) {
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
					if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 1 )
						brush.CreateSolidBrush( pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					else if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 2 )
						brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					else if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 3 )
						brush.CreateHatchBrush ( HS_CROSS, pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					else if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 4 )
						brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					else if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 5 )
						brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					else if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 6 )
						brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					else if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 7 )
						brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> RT_FillColor.GetAt (RT_Number) ) ;

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
				if ( pDoc -> RT_IsNoFill.GetAt (RT_Number) == 'o' ) {
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
					if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 1 )
						brush.CreateSolidBrush( pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					else if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 2 )
						brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					else if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 3 )
						brush.CreateHatchBrush ( HS_CROSS, pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					else if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 4 )
						brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					else if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 5 )
						brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					else if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 6 )
						brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> RT_FillColor.GetAt (RT_Number) ) ;
					else if ( pDoc -> RT_FillPattern.GetAt (RT_Number) == 7 )
						brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> RT_FillColor.GetAt (RT_Number) ) ;

					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Polygon ( RT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
					pDC -> SelectObject ( oldBrush ) ;		
				}
			}

			// 만약 이동시키고 있는 중이라면
			if ( M_Number == RT_Number && M_IsDraw == 'o' && M_What == _T ("RT") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;

				CRect Rect, Rect2, Rect3, Rect4 ;
				Rect.top = M_Rect.top - 4 ;
				Rect.bottom = M_Rect.top + 4 ;
				Rect.left = M_Rect.left - 4 ;
				Rect.right = M_Rect.left + 4 ;

				Rect2.top = M_Rect.bottom - 4 ;
				Rect2.bottom = M_Rect.bottom + 4 ;
				Rect2.left = M_Rect.right - 4 ;
				Rect2.right = M_Rect.right + 4 ;

				Rect3.top = M_Rect.top - 4 ;
				Rect3.bottom = M_Rect.top + 4 ;
				Rect3.left = M_Rect.right - 4 ;
				Rect3.right = M_Rect.right + 4 ;

				Rect4.top = M_Rect.bottom - 4 ;
				Rect4.bottom = M_Rect.bottom + 4 ;
				Rect4.left = M_Rect.left - 4 ;
				Rect4.right = M_Rect.left + 4 ;

				pDC -> SelectStockObject ( NULL ) ;
				
				pDC -> Rectangle ( Rect.left, Rect.top, Rect.right, Rect.bottom ) ;
				pDC -> Rectangle ( Rect2.left, Rect2.top, Rect2.right, Rect2.bottom ) ;
				pDC -> Rectangle ( Rect3.left, Rect3.top, Rect3.right, Rect3.bottom ) ;
				pDC -> Rectangle ( Rect4.left, Rect4.top, Rect4.right, Rect4.bottom ) ;
			}

			// 만약 역 삼각형을 그리고 있는 상태, 변경하는 상태라면 테두리 직사각형을 그려줍니다.
			if ( pDoc -> RT_Triangle.GetCount () - 1 == RT_Number && RT_CanMove == 'o') {
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
				if ( pDoc -> RightT_IsNoFill.GetAt (RightT_Number) == 'o' ) {
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
					if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 1 )
						brush.CreateSolidBrush( pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					else if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 2 )
						brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					else if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 3 )
						brush.CreateHatchBrush ( HS_CROSS, pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					else if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 4 )
						brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					else if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 5 )
						brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					else if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 6 )
						brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					else if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 7 )
						brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;

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
				if ( pDoc -> RightT_IsNoFill.GetAt (RightT_Number) == 'o' ) {
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
					if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 1 )
						brush.CreateSolidBrush( pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					else if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 2 )
						brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					else if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 3 )
						brush.CreateHatchBrush ( HS_CROSS, pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					else if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 4 )
						brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					else if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 5 )
						brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					else if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 6 )
						brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;
					else if ( pDoc -> RightT_FillPattern.GetAt (RightT_Number) == 7 )
						brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> RightT_FillColor.GetAt (RightT_Number) ) ;

					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Polygon ( RightT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
					pDC -> SelectObject ( oldBrush ) ;		
				}
			}

			// 만약 이동시키고 있는 중이라면
			if ( M_Number == RightT_Number && M_IsDraw == 'o' && M_What == _T ("RightT") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;

				CRect Rect, Rect2, Rect3, Rect4 ;
				Rect.top = M_Rect.top - 4 ;
				Rect.bottom = M_Rect.top + 4 ;
				Rect.left = M_Rect.left - 4 ;
				Rect.right = M_Rect.left + 4 ;

				Rect2.top = M_Rect.bottom - 4 ;
				Rect2.bottom = M_Rect.bottom + 4 ;
				Rect2.left = M_Rect.right - 4 ;
				Rect2.right = M_Rect.right + 4 ;

				Rect3.top = M_Rect.top - 4 ;
				Rect3.bottom = M_Rect.top + 4 ;
				Rect3.left = M_Rect.right - 4 ;
				Rect3.right = M_Rect.right + 4 ;

				Rect4.top = M_Rect.bottom - 4 ;
				Rect4.bottom = M_Rect.bottom + 4 ;
				Rect4.left = M_Rect.left - 4 ;
				Rect4.right = M_Rect.left + 4 ;

				pDC -> SelectStockObject ( NULL ) ;
				
				pDC -> Rectangle ( Rect.left, Rect.top, Rect.right, Rect.bottom ) ;
				pDC -> Rectangle ( Rect2.left, Rect2.top, Rect2.right, Rect2.bottom ) ;
				pDC -> Rectangle ( Rect3.left, Rect3.top, Rect3.right, Rect3.bottom ) ;
				pDC -> Rectangle ( Rect4.left, Rect4.top, Rect4.right, Rect4.bottom ) ;
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
				if ( pDoc -> RRightT_IsNoFill.GetAt (RRightT_Number) == 'o' ) {
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
					if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 1 )
						brush.CreateSolidBrush( pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					else if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 2 )
						brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					else if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 3 )
						brush.CreateHatchBrush ( HS_CROSS, pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					else if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 4 )
						brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					else if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 5 )
						brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					else if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 6 )
						brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					else if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 7 )
						brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;

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
				if ( pDoc -> RRightT_IsNoFill.GetAt (RRightT_Number) == 'o' ) {
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
					if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 1 )
						brush.CreateSolidBrush( pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					else if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 2 )
						brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					else if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 3 )
						brush.CreateHatchBrush ( HS_CROSS, pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					else if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 4 )
						brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					else if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 5 )
						brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					else if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 6 )
						brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;
					else if ( pDoc -> RRightT_FillPattern.GetAt (RRightT_Number) == 7 )
						brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> RRightT_FillColor.GetAt (RRightT_Number) ) ;

					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Polygon ( RRightT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
					pDC -> SelectObject ( oldBrush ) ;		
				}
			}

			// 만약 이동시키고 있는 중이라면
			if ( M_Number == RRightT_Number && M_IsDraw == 'o' && M_What == _T ("RRightT") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;

				CRect Rect, Rect2, Rect3, Rect4 ;
				Rect.top = M_Rect.top - 4 ;
				Rect.bottom = M_Rect.top + 4 ;
				Rect.left = M_Rect.left - 4 ;
				Rect.right = M_Rect.left + 4 ;

				Rect2.top = M_Rect.bottom - 4 ;
				Rect2.bottom = M_Rect.bottom + 4 ;
				Rect2.left = M_Rect.right - 4 ;
				Rect2.right = M_Rect.right + 4 ;

				Rect3.top = M_Rect.top - 4 ;
				Rect3.bottom = M_Rect.top + 4 ;
				Rect3.left = M_Rect.right - 4 ;
				Rect3.right = M_Rect.right + 4 ;

				Rect4.top = M_Rect.bottom - 4 ;
				Rect4.bottom = M_Rect.bottom + 4 ;
				Rect4.left = M_Rect.left - 4 ;
				Rect4.right = M_Rect.left + 4 ;

				pDC -> SelectStockObject ( NULL ) ;
				
				pDC -> Rectangle ( Rect.left, Rect.top, Rect.right, Rect.bottom ) ;
				pDC -> Rectangle ( Rect2.left, Rect2.top, Rect2.right, Rect2.bottom ) ;
				pDC -> Rectangle ( Rect3.left, Rect3.top, Rect3.right, Rect3.bottom ) ;
				pDC -> Rectangle ( Rect4.left, Rect4.top, Rect4.right, Rect4.bottom ) ;
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
				if ( pDoc -> LTRT_IsNoFill.GetAt (LTRT_Number) == 'o' ) {
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
					if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 1 )
						brush.CreateSolidBrush( pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					else if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 2 )
						brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					else if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 3 )
						brush.CreateHatchBrush ( HS_CROSS, pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					else if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 4 )
						brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					else if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 5 )
						brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					else if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 6 )
						brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					else if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 7 )
						brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;

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
				if ( pDoc -> LTRT_IsNoFill.GetAt (LTRT_Number) == 'o' ) {
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
					if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 1 )
						brush.CreateSolidBrush( pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					else if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 2 )
						brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					else if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 3 )
						brush.CreateHatchBrush ( HS_CROSS, pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					else if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 4 )
						brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					else if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 5 )
						brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					else if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 6 )
						brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;
					else if ( pDoc -> LTRT_FillPattern.GetAt (LTRT_Number) == 7 )
						brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> LTRT_FillColor.GetAt (LTRT_Number) ) ;

					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Polygon ( LTRT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
					pDC -> SelectObject ( oldBrush ) ;		
				}
			}

			// 만약 이동시키고 있는 중이라면
			if ( M_Number == LTRT_Number && M_IsDraw == 'o' && M_What == _T ("LTRT") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;

				CRect Rect, Rect2, Rect3, Rect4 ;
				Rect.top = M_Rect.top - 4 ;
				Rect.bottom = M_Rect.top + 4 ;
				Rect.left = M_Rect.left - 4 ;
				Rect.right = M_Rect.left + 4 ;

				Rect2.top = M_Rect.bottom - 4 ;
				Rect2.bottom = M_Rect.bottom + 4 ;
				Rect2.left = M_Rect.right - 4 ;
				Rect2.right = M_Rect.right + 4 ;

				Rect3.top = M_Rect.top - 4 ;
				Rect3.bottom = M_Rect.top + 4 ;
				Rect3.left = M_Rect.right - 4 ;
				Rect3.right = M_Rect.right + 4 ;

				Rect4.top = M_Rect.bottom - 4 ;
				Rect4.bottom = M_Rect.bottom + 4 ;
				Rect4.left = M_Rect.left - 4 ;
				Rect4.right = M_Rect.left + 4 ;

				pDC -> SelectStockObject ( NULL ) ;
				
				pDC -> Rectangle ( Rect.left, Rect.top, Rect.right, Rect.bottom ) ;
				pDC -> Rectangle ( Rect2.left, Rect2.top, Rect2.right, Rect2.bottom ) ;
				pDC -> Rectangle ( Rect3.left, Rect3.top, Rect3.right, Rect3.bottom ) ;
				pDC -> Rectangle ( Rect4.left, Rect4.top, Rect4.right, Rect4.bottom ) ;
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
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).left + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
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
					P_PointStart.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.x = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).right + pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
					P_PointLast.y = pDoc -> LTRT_Triangle.GetAt (LTRT_Number).top - pDoc -> LTRT_Thickness.GetAt (LTRT_Number) / 2 ;
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
				if ( pDoc -> RTLT_IsNoFill.GetAt (RTLT_Number) == 'o' ) {
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
					if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 1 )
						brush.CreateSolidBrush( pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					else if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 2 )
						brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					else if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 3 )
						brush.CreateHatchBrush ( HS_CROSS, pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					else if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 4 )
						brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					else if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 5 )
						brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					else if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 6 )
						brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					else if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 7 )
						brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;

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
				if ( pDoc -> RTLT_IsNoFill.GetAt (RTLT_Number) == 'o' ) {
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
					if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 1 )
						brush.CreateSolidBrush( pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					else if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 2 )
						brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					else if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 3 )
						brush.CreateHatchBrush ( HS_CROSS, pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					else if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 4 )
						brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					else if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 5 )
						brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					else if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 6 )
						brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;
					else if ( pDoc -> RTLT_FillPattern.GetAt (RTLT_Number) == 7 )
						brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> RTLT_FillColor.GetAt (RTLT_Number) ) ;

					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Polygon ( RTLT_Point, 3 ) ;

					pDC->SelectObject(Draw_Pen);
					pDC -> SelectObject ( oldBrush ) ;		
				}
			}

			// 만약 이동시키고 있는 중이라면
			if ( M_Number == RTLT_Number && M_IsDraw == 'o' && M_What == _T ("RTLT") ) {
				CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;

				CRect Rect, Rect2, Rect3, Rect4 ;
				Rect.top = M_Rect.top - 4 ;
				Rect.bottom = M_Rect.top + 4 ;
				Rect.left = M_Rect.left - 4 ;
				Rect.right = M_Rect.left + 4 ;

				Rect2.top = M_Rect.bottom - 4 ;
				Rect2.bottom = M_Rect.bottom + 4 ;
				Rect2.left = M_Rect.right - 4 ;
				Rect2.right = M_Rect.right + 4 ;

				Rect3.top = M_Rect.top - 4 ;
				Rect3.bottom = M_Rect.top + 4 ;
				Rect3.left = M_Rect.right - 4 ;
				Rect3.right = M_Rect.right + 4 ;

				Rect4.top = M_Rect.bottom - 4 ;
				Rect4.bottom = M_Rect.bottom + 4 ;
				Rect4.left = M_Rect.left - 4 ;
				Rect4.right = M_Rect.left + 4 ;

				pDC -> SelectStockObject ( NULL ) ;
				
				pDC -> Rectangle ( Rect.left, Rect.top, Rect.right, Rect.bottom ) ;
				pDC -> Rectangle ( Rect2.left, Rect2.top, Rect2.right, Rect2.bottom ) ;
				pDC -> Rectangle ( Rect3.left, Rect3.top, Rect3.right, Rect3.bottom ) ;
				pDC -> Rectangle ( Rect4.left, Rect4.top, Rect4.right, Rect4.bottom ) ;
			}

			// 만약 오른쪽 -> 왼쪽 삼각형을 그리고 있는 상태라면 테두리 직사각형을 그려줍니다.
			if ( pDoc -> RTLT_Triangle.GetCount () - 1 == RTLT_Number && RTLT_CanMove == 'o' ) {
				CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );

				if ( pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left > pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right ) {
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen);

					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen3);
				}
				else {
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen);

					CPen *Draw_Pen2 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).top - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen2);

					CPen *Draw_Pen3 = pDC -> SelectObject(&pen);
					P_PointStart.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).right + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointStart.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.x = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).left - pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					P_PointLast.y = pDoc -> RTLT_Triangle.GetAt (RTLT_Number).bottom + pDoc -> RTLT_Thickness.GetAt (RTLT_Number) / 2 ;
					pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
					pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
					pDC->SelectObject(Draw_Pen3);
				}
			}
			RTLT_Number++ ;
		}

		// 텍스트 객체일 경우
		else if ( pDoc -> What.GetAt (i) == _T ("Text") ) {

			// 폰트 지정한 경우
			if ( pDoc -> Text_Text.GetAt ( Text_Number ).IsFont == 'o' ) {

				CFont Font ;
				Font.CreateFontIndirect ( &(pDoc -> Text_Text.GetAt ( Text_Number ).Font) ) ;
				CFont* def_font = pDC -> SelectObject ( &Font ) ;
				pDC -> SetTextColor ( pDoc -> Text_Text.GetAt ( Text_Number ).Color ) ;

				CSize strSize ;

				if ( (Text_IsKeyDown == 'o' && Text_Number == pDoc -> Text_Text.GetCount () - 1) || (Text_IsChange == 'o' && Text_Number == M_Number) ) {
					strSize = pDC -> GetTextExtent ( pDoc -> Text_Text.GetAt ( Text_Number ).Text ) ;
					Text_CurPoint.x = pDoc -> Text_Text.GetAt ( Text_Number ).Location.x + strSize.cx ;
					Text_CurPoint.y = pDoc -> Text_Text.GetAt ( Text_Number ).Location.y ;
					SetCaretPos ( Text_CurPoint ) ;
					ShowCaret () ;
				}

				if ( (Text_IsKeyDown == 'o' && M_IsDraw != 'o' && Text_Number == pDoc -> Text_Text.GetCount () - 1) || (M_IsDraw == 'o' && Text_IsChange == 'o' && Text_Number == M_Number) ) {
					pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.top = pDoc -> Text_Text.GetAt ( Text_Number ).Location.y + pDoc -> Text_Text.GetAt ( Text_Number ).Font.lfHeight - 10 ;
					pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.left = pDoc -> Text_Text.GetAt ( Text_Number ).Location.x - 10 ;
					pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.bottom = pDoc -> Text_Text.GetAt ( Text_Number ).Location.y + 10 ;
					pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.right = Text_CurPoint.x + 10 ;
				}

				// 배경색 추가한 경우
				if ( pDoc -> Text_Text.GetAt ( Text_Number ).IsNoFill == 'x' ) {
					pDC->SetBkMode(TRANSPARENT);
					pDC -> SelectStockObject ( NULL_PEN ) ;
					CBrush brush ;
					brush.CreateSolidBrush ( pDoc -> Text_Text.GetAt ( Text_Number ).BGColor ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Rectangle ( pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.left, pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.top,
									   pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.right, pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.bottom ) ;
					pDC -> SelectObject ( oldBrush ) ;
				}
				
				// 텍스트 입력중이면 테두리 사각형 출력
				if ( Text_Number == pDoc -> Text_Text.GetCount () - 1 && Text_IsKeyDown == 'o' ||
					(M_IsDraw == 'o' && Text_Number == M_Number) ) {
					pDC -> SelectStockObject ( NULL ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> Rectangle ( pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.left, pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.top,
									   pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.right, pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.bottom ) ;
					pDC->SelectObject(Draw_Pen) ;
				}

				pDC -> TextOut ( pDoc -> Text_Text.GetAt ( Text_Number ).Location.x, pDoc -> Text_Text.GetAt ( Text_Number ).Location.y + pDoc -> Text_Text.GetAt ( Text_Number ).Font.lfHeight,
								 pDoc -> Text_Text.GetAt ( Text_Number ).Text ) ;
				pDC -> SelectObject ( def_font ) ;
			}
			// 폰트 지정을 하지 않은 경우
			else {

				CSize strSize ;

				if ( (Text_IsKeyDown == 'o' && Text_Number == pDoc -> Text_Text.GetCount () - 1) || (Text_IsChange == 'o' && Text_Number == M_Number) ) {
					strSize = pDC -> GetTextExtent ( pDoc -> Text_Text.GetAt ( Text_Number ).Text ) ;
					Text_CurPoint.x = pDoc -> Text_Text.GetAt ( Text_Number ).Location.x + strSize.cx ;
					Text_CurPoint.y = pDoc -> Text_Text.GetAt ( Text_Number ).Location.y ;
					SetCaretPos ( Text_CurPoint ) ;
					ShowCaret () ;
				}
				
				if ( (Text_IsKeyDown == 'o' && M_IsDraw != 'o' && Text_Number == pDoc -> Text_Text.GetCount () - 1) || (M_IsDraw == 'o' && Text_IsChange == 'o' && Text_Number == M_Number) ) {
					pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.top = pDoc -> Text_Text.GetAt ( Text_Number ).Location.y - 10 ;
					pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.left = pDoc -> Text_Text.GetAt ( Text_Number ).Location.x - 10 ;
					pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.bottom = pDoc -> Text_Text.GetAt ( Text_Number ).Location.y + 26 ;
					pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.right = Text_CurPoint.x + 10 ;
				}

				// 배경색 추가한 경우
				if ( pDoc -> Text_Text.GetAt ( Text_Number ).IsNoFill == 'x' ) {
					pDC->SetBkMode(TRANSPARENT);
					pDC -> SelectStockObject ( NULL_PEN ) ;
					CBrush brush ;
					brush.CreateSolidBrush ( pDoc -> Text_Text.GetAt ( Text_Number ).BGColor ) ;
					CBrush* oldBrush = pDC->SelectObject( &brush ) ;

					pDC -> Rectangle ( pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.left, pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.top,
									   pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.right, pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.bottom ) ;
					pDC -> SelectObject ( oldBrush ) ;
				}

				// 텍스트 입력중이면 테두리 사각형 출력
				if ( Text_Number == pDoc -> Text_Text.GetCount () - 1 && Text_IsKeyDown == 'o' ||
					(M_IsDraw == 'o' && Text_Number == M_Number) ) {
					pDC -> SelectStockObject ( NULL ) ;
					pDC -> SelectStockObject ( NULL_BRUSH ) ;
					CPen pen ( PS_DOT, 1.8, RGB (100, 100, 255) );
					CPen *Draw_Pen = pDC -> SelectObject(&pen);
					pDC -> Rectangle ( pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.left, pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.top,
									   pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.right, pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.bottom ) ;
					pDC->SelectObject(Draw_Pen) ;
				}

				pDC -> TextOut ( pDoc -> Text_Text.GetAt ( Text_Number ).Location.x, pDoc -> Text_Text.GetAt ( Text_Number ).Location.y,
								 pDoc -> Text_Text.GetAt ( Text_Number ).Text ) ;

			}
			Text_Number++ ;
		}

		// 그룹화 객체일 경우의 출력
		else if ( pDoc -> What.GetAt (i) == _T ("G") ) {

			if ( M_Number == G_Number && M_IsDraw == 'o' && M_What == _T ("G") ) {
				CPen pen ( PS_SOLID, 1.8, RGB (200, 0, 0) ) ;
				CPen *Draw_Pen = pDC -> SelectObject(&pen);
				pDC -> SelectStockObject ( NULL_BRUSH ) ;
				pDC -> Rectangle ( M_Rect.left, M_Rect.top, M_Rect.right, M_Rect.bottom ) ;
				pDC -> SelectObject ( Draw_Pen ) ;
			}

			int L_Number = 0 ;
			int P_Number = 0 ;
			int R_Number = 0 ;
			int E_Number = 0 ;
			int Text_Number = 0 ;
			int G_Numbers = 0 ;

			for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).What.GetCount () ; i++ ) {

				// 그룹화 중 '선'을 출력함
				if ( pDoc -> G_Group.GetAt (G_Number).What.GetAt (i) == _T ("L") ) {
					// 색상을 가지지 않을 경우의 출력
					if ( pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).L_Color == RGB (0,0,0) ) {
						if ( pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Pattern == 1 ) {
							CPen pen ( PS_SOLID, pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
							CPen *Draw_Pen = pDC -> SelectObject(&pen);
							L_Insert.Start = pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Start ;
							L_Insert.Last = pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Last ;
							pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
							pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
							pDC->SelectObject(Draw_Pen);
						}
						else if ( pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Pattern == 2 ) {
							CPen pen ( PS_DASH, pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
							CPen *Draw_Pen = pDC -> SelectObject(&pen);
							L_Insert.Start = pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Start ;
							L_Insert.Last = pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Last ;
							pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
							pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
							pDC->SelectObject(Draw_Pen);
						}
						else if ( pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Pattern == 3 ) {
							CPen pen ( PS_DOT, pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
							CPen *Draw_Pen = pDC -> SelectObject(&pen);
							L_Insert.Start = pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Start ;
							L_Insert.Last = pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Last ;
							pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
							pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
							pDC->SelectObject(Draw_Pen);
						}
						else if ( pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Pattern == 4 ) {
							CPen pen ( PS_DASHDOT, pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
							CPen *Draw_Pen = pDC -> SelectObject(&pen);
							L_Insert.Start = pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Start ;
							L_Insert.Last = pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Last ;
							pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
							pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
							pDC->SelectObject(Draw_Pen);
						}
						else if ( pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Pattern == 5 ) {
							CPen pen ( PS_DASHDOTDOT, pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
							CPen *Draw_Pen = pDC -> SelectObject(&pen);
							L_Insert.Start = pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Start ;
							L_Insert.Last = pDoc -> G_Group.GetAt (G_Number).Line.GetAt (L_Number).Last ;
							pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
							pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
							pDC->SelectObject(Draw_Pen);
						}
					}
					// 특정 색상을 가졌을 경우의 출력
					else {
						if ( pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Pattern == 1 ) {
							CPen pen ( PS_SOLID, pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Thickness, pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).L_Color ) ;
							CPen *Draw_Pen = pDC -> SelectObject(&pen);
							L_Insert.Start = pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Start ;
							L_Insert.Last = pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Last ;
							pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
							pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
							pDC->SelectObject(Draw_Pen);
						}
						else if (pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Pattern == 2 ) {
							CPen pen ( PS_DASH, pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Thickness, pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).L_Color ) ;
							CPen *Draw_Pen = pDC -> SelectObject(&pen);
							L_Insert.Start = pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Start ;
							L_Insert.Last = pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Last ;
							pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
							pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
							pDC->SelectObject(Draw_Pen);
						}
						else if (pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Pattern == 3 ) {
							CPen pen ( PS_DOT, pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Thickness, pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).L_Color ) ;
							CPen *Draw_Pen = pDC -> SelectObject(&pen);
							L_Insert.Start = pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Start ;
							L_Insert.Last = pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Last ;
							pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
							pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
							pDC->SelectObject(Draw_Pen);
						}
						else if (pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Pattern == 4 ) {
							CPen pen ( PS_DASHDOT, pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Thickness, pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).L_Color ) ;
							CPen *Draw_Pen = pDC -> SelectObject(&pen);
							L_Insert.Start = pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Start ;
							L_Insert.Last = pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Last ;
							pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
							pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
							pDC->SelectObject(Draw_Pen);
						}
						else if (pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Pattern == 5 ) {
							CPen pen ( PS_DASHDOTDOT, pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Thickness, pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).L_Color ) ;
							CPen *Draw_Pen = pDC -> SelectObject(&pen);
							L_Insert.Start = pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Start ;
							L_Insert.Last = pDoc ->  G_Group.GetAt (G_Number).Line.GetAt (L_Number).Last ;
							pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
							pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
							pDC->SelectObject(Draw_Pen);
						}
					}
					L_Number++ ;
				}

				// 그룹화 중 PolyLine을 출력함
				else if ( pDoc -> G_Group.GetAt (G_Number).What.GetAt (i) == _T ("P") ) {

					int j ;
					for ( j = 0 ; j < pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetCount () - 1 ; j++ ) {

						// PolyLine이 색상을 가지지 않을 경우의 출력
						if ( pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).P_Color == RGB (0,0,0) ) {
							if ( pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Pattern == 1 ) {
								CPen pen ( PS_SOLID, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
								CPen *Draw_Pen = pDC -> SelectObject(&pen);
								P_PointStart = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
								P_PointLast = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
								pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
								pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
								pDC->SelectObject(Draw_Pen);
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Pattern == 2 ) {
								CPen pen ( PS_DASH, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
								CPen *Draw_Pen = pDC -> SelectObject(&pen);
								P_PointStart = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
								P_PointLast = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
								pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
								pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
								pDC->SelectObject(Draw_Pen);
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Pattern == 3 ) {
								CPen pen ( PS_DOT, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
								CPen *Draw_Pen = pDC -> SelectObject(&pen);
								P_PointStart = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
								P_PointLast = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
								pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
								pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
								pDC->SelectObject(Draw_Pen);
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Pattern == 4 ) {
								CPen pen ( PS_DASHDOT, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
								CPen *Draw_Pen = pDC -> SelectObject(&pen);
								P_PointStart = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
								P_PointLast = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
								pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
								pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
								pDC->SelectObject(Draw_Pen);
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Pattern == 5 ) {
								CPen pen ( PS_DASHDOTDOT, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
								CPen *Draw_Pen = pDC -> SelectObject(&pen);
								P_PointStart = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
								P_PointLast = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
								pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
								pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
								pDC->SelectObject(Draw_Pen);
							}

						}
						// PolyLine이 지정된 색상을 가졌을 경우의 출력
						else {
							if ( pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Pattern == 1 ) {
								CPen pen ( PS_SOLID, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).thickness, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).P_Color ) ;
								CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
								P_PointStart = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
								P_PointLast = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
								pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
								pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
								pDC->SelectObject(Draw_Pen);
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Pattern == 2 ) {
								CPen pen ( PS_DASH, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).thickness, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).P_Color ) ;
								CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
								P_PointStart = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
								P_PointLast = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
								pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
								pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
								pDC->SelectObject(Draw_Pen);
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Pattern == 3 ) {
								CPen pen ( PS_DOT, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).thickness, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).P_Color ) ;
								CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
								P_PointStart = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
								P_PointLast = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
								pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
								pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
								pDC->SelectObject(Draw_Pen);
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Pattern == 4 ) {
								CPen pen ( PS_DASHDOT, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).thickness, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).P_Color ) ;
								CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
								P_PointStart = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
								P_PointLast = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
								pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
								pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
								pDC->SelectObject(Draw_Pen);
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Pattern == 5 ) {
								CPen pen ( PS_DASHDOTDOT, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).thickness, pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).P_Color ) ;
								CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
								P_PointStart = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
								P_PointLast = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
								pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
								pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
								pDC->SelectObject(Draw_Pen);
							}
						}

					}
					P_Number++ ;
				}

				// 그룹화 중 상자 객체를 출력함
				else if ( pDoc -> G_Group.GetAt (G_Number).What.GetAt (i) == _T ("R") ) {
					// 선 색을 가지지 않았을 경우의 출력
					if ( pDoc -> G_Group.GetAt (G_Number).R_Color.GetAt (R_Number) == RGB (0,0,0) ) {

						// 채우기 색상을 가지지 않았을 경우의 출력
						if ( pDoc -> G_Group.GetAt (G_Number).R_IsNoFill.GetAt (R_Number) == 'o' ) {
							if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 1 ) {
								CPen pen;
								pen.CreatePen( PS_SOLID, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 2 ) {
								CPen pen;
								pen.CreatePen( PS_DASH, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 3 ) {
								CPen pen;
								pen.CreatePen( PS_DOT, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 4 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOT, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 5 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
						}
						// 채우기 색상을 가졌을 경우의 출력
						else {
							if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 1 ) {
								CPen pen;
								pen.CreatePen( PS_SOLID, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldBrush ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 2 ) {
								CPen pen;
								pen.CreatePen( PS_DASH, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldBrush ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 3 ) {
								CPen pen;
								pen.CreatePen( PS_DOT, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldBrush ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 4 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOT, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldBrush ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 5 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldBrush ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
						}
					}
					// 특정 선 색상을 가졌을 경우의 출력
					else {

						// 채우기 색상을 가지지 않았을 경우의 출력
						if ( pDoc -> G_Group.GetAt (G_Number).R_IsNoFill.GetAt (R_Number) == 'o' ) {
							if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 1 ) {
								CPen pen;
								pen.CreatePen( PS_SOLID, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), pDoc -> G_Group.GetAt (G_Number).R_Color.GetAt (R_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC ->SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 2 ) {
								CPen pen;
								pen.CreatePen( PS_DASH, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), pDoc -> G_Group.GetAt (G_Number).R_Color.GetAt (R_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC ->SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 3 ) {
								CPen pen;
								pen.CreatePen( PS_DOT, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), pDoc -> G_Group.GetAt (G_Number).R_Color.GetAt (R_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC ->SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 4 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOT, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), pDoc -> G_Group.GetAt (G_Number).R_Color.GetAt (R_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC ->SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 5 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), pDoc -> G_Group.GetAt (G_Number).R_Color.GetAt (R_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC ->SelectObject ( oldPen ) ;
							}
						}
						// 채우기 색상을 가졌을 경우의 출력
						else {
							if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 1 ) {
								CPen pen;
								pen.CreatePen( PS_SOLID, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), pDoc -> G_Group.GetAt (G_Number).R_Color.GetAt (R_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
								pDC -> SelectObject ( oldBrush ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 2 ) {
								CPen pen;
								pen.CreatePen( PS_DASH, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), pDoc -> G_Group.GetAt (G_Number).R_Color.GetAt (R_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
								pDC -> SelectObject ( oldBrush ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 3 ) {
								CPen pen;
								pen.CreatePen( PS_DOT, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), pDoc -> G_Group.GetAt (G_Number).R_Color.GetAt (R_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
								pDC -> SelectObject ( oldBrush ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 4 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOT, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), pDoc -> G_Group.GetAt (G_Number).R_Color.GetAt (R_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
								pDC -> SelectObject ( oldBrush ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (R_Number) == 5 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (R_Number), pDoc -> G_Group.GetAt (G_Number).R_Color.GetAt (R_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (R_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (R_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].left, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].top, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].right, pDoc -> G_Group.GetAt (G_Number).Rect [R_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
								pDC -> SelectObject ( oldBrush ) ;
							}
						}
					}
					R_Number++ ;
				}

				// 그룹화 객체중 원을 출력
				else if ( pDoc -> G_Group.GetAt (G_Number).What.GetAt (i) == _T ("E") ) {
					// 선 색을 가지지 않았을 경우의 출력
					if ( pDoc -> G_Group.GetAt (G_Number).E_Color.GetAt (E_Number) == RGB (0,0,0) ) {
						// 채우기 색상을 가지지 않았을 경우의 출력
						if ( pDoc -> G_Group.GetAt (G_Number).E_IsNoFill.GetAt (E_Number) == 'o' ) {
							if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 1 ) {
								CPen pen;
								pen.CreatePen( PS_SOLID, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 2 ) {
								CPen pen;
								pen.CreatePen( PS_DASH, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 3 ) {
								CPen pen;
								pen.CreatePen( PS_DOT, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 4 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOT, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 5 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
						}
						// 채우기 색상을 가졌을 경우의 출력
						else {
							if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 1 ) {
								CPen pen;
								pen.CreatePen( PS_SOLID, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldBrush ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 2 ) {
								CPen pen;
								pen.CreatePen( PS_DASH, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldBrush ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 3 ) {
								CPen pen;
								pen.CreatePen( PS_DOT, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldBrush ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 4 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOT, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldBrush ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 5 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldBrush ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
						}
					}
					// 특정 선 색상을 가졌을 경우의 출력
					else {
						// 채우기 색상을 가지지 않았을 경우의 출력
						if ( pDoc -> G_Group.GetAt (G_Number).E_IsNoFill.GetAt (E_Number) == 'o' ) {
							if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 1 ) {
								CPen pen;
								pen.CreatePen( PS_SOLID, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), pDoc -> G_Group.GetAt (G_Number).E_Color.GetAt (E_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 2 ) {
								CPen pen;
								pen.CreatePen( PS_DASH, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), pDoc -> G_Group.GetAt (G_Number).E_Color.GetAt (E_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 3 ) {
								CPen pen;
								pen.CreatePen( PS_DOT, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), pDoc -> G_Group.GetAt (G_Number).E_Color.GetAt (E_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 4 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOT, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), pDoc -> G_Group.GetAt (G_Number).E_Color.GetAt (E_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 5 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), pDoc -> G_Group.GetAt (G_Number).E_Color.GetAt (E_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								pDC -> SelectStockObject ( NULL_BRUSH ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
							}
						}
						// 채우기 색상을 가졌을 경우의 출력
						else {
							if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 1 ) {
								CPen pen;
								pen.CreatePen( PS_SOLID, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), pDoc -> G_Group.GetAt (G_Number).E_Color.GetAt (E_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
								pDC -> SelectObject ( oldBrush ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 2 ) {
								CPen pen;
								pen.CreatePen( PS_DASH, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), pDoc -> G_Group.GetAt (G_Number).E_Color.GetAt (E_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
								pDC -> SelectObject ( oldBrush ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 3 ) {
								CPen pen;
								pen.CreatePen( PS_DOT, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), pDoc -> G_Group.GetAt (G_Number).E_Color.GetAt (E_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
								pDC -> SelectObject ( oldBrush ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 4 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOT, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), pDoc -> G_Group.GetAt (G_Number).E_Color.GetAt (E_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
								pDC -> SelectObject ( oldBrush ) ;
							}
							else if ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (E_Number) == 5 ) {
								CPen pen;
								pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (E_Number), pDoc -> G_Group.GetAt (G_Number).E_Color.GetAt (E_Number) ) ;
								CPen* oldPen = pDC->SelectObject( &pen ) ;
								CBrush brush;
								if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 1 )
									brush.CreateSolidBrush( pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 2 )
									brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 3 )
									brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 4 )
									brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 5 )
									brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 6 )
									brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;
								else if ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (E_Number) == 7 )
									brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (E_Number) ) ;

								CBrush* oldBrush = pDC->SelectObject( &brush ) ;
								pDC -> Ellipse ( pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].left, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].top, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].right, pDoc -> G_Group.GetAt (G_Number).Ellipse [E_Number].bottom ) ;
								pDC -> SelectObject ( oldPen ) ;
								pDC -> SelectObject ( oldBrush ) ;
							}
						}
					}
					E_Number++ ;
				}

				// 그룹화 객체중 텍스트를 출력
				else if ( pDoc -> G_Group.GetAt (G_Number).What.GetAt (i) == _T ("Text") ) {
					// 폰트 지정한 경우
					if ( pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).IsFont == 'o' ) {

						CFont Font ;
						Font.CreateFontIndirect ( &(pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).Font) ) ;
						CFont* def_font = pDC -> SelectObject ( &Font ) ;
						pDC -> SetTextColor ( pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).Color ) ;

						CSize strSize ;

						if ( Text_IsFont == 'o' ) {
							strSize = pDC -> GetTextExtent ( pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).Text ) ;
							Text_CurPoint.x = pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).Location.x + strSize.cx ;
							Text_CurPoint.y = pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).Location.y ;
							SetCaretPos ( Text_CurPoint ) ;
						}

						if ( Text_IsFont == 'o' ) {
							pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).Text_Rect.top = pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).Location.y + pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).Font.lfHeight - 10 ;
							pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).Text_Rect.left = pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).Location.x - 10 ;
							pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).Text_Rect.bottom = pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).Location.y + 10 ;
							pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).Text_Rect.right = Text_CurPoint.x + 10 ;
						}

						// 배경색 추가한 경우
						if ( pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).IsNoFill == 'x' ) {
							pDC->SetBkMode(TRANSPARENT);
							pDC -> SelectStockObject ( NULL_PEN ) ;
							CBrush brush ;
							brush.CreateSolidBrush ( pDoc -> G_Group.GetAt (G_Number).Text.GetAt ( Text_Number ).BGColor ) ;
							CBrush* oldBrush = pDC->SelectObject( &brush ) ;

							pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Text_Rect.left, pDoc -> G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Text_Rect.top,
								pDoc -> G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Text_Rect.right, pDoc -> G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Text_Rect.bottom ) ;
							pDC -> SelectObject ( oldBrush ) ;
						}

						pDC -> TextOut ( pDoc ->  G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Location.x, pDoc ->  G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Location.y + pDoc ->  G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Font.lfHeight,
							pDoc ->  G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Text ) ;
						pDC -> SelectObject ( def_font ) ;
					}
					// 폰트 지정을 하지 않은 경우
					else {

						// 배경색 추가한 경우
						if ( pDoc -> G_Group.GetAt (G_Number).Text.GetAt (Text_Number).IsNoFill == 'x' ) {
							pDC->SetBkMode(TRANSPARENT);
							pDC -> SelectStockObject ( NULL_PEN ) ;
							CBrush brush ;
							brush.CreateSolidBrush ( pDoc -> G_Group.GetAt (G_Number).Text.GetAt (Text_Number).BGColor ) ;
							CBrush* oldBrush = pDC->SelectObject( &brush ) ;

							pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Text_Rect.left, pDoc -> G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Text_Rect.top,
								pDoc -> G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Text_Rect.right, pDoc -> G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Text_Rect.bottom ) ;
							pDC -> SelectObject ( oldBrush ) ;
						}

						pDC -> TextOut ( pDoc ->  G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Location.x, pDoc ->  G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Location.y,
							pDoc ->  G_Group.GetAt (G_Number).Text.GetAt (Text_Number).Text ) ;

					}
					Text_Number++ ;
				}
				// 그룹화 객체중 그룹화를 출력
				else if ( pDoc -> G_Group.GetAt (G_Number).What.GetAt (i) == _T ("G") ) {
					for ( int k = 0 ; k < pDoc -> G_Group.GetAt (G_Number).Index.GetCount () ; k++ ) {

						int m = pDoc -> G_Group.GetAt (G_Number).Index.GetAt (k) ;
						int L_Number = 0 ;
						int R_Number = 0 ;
						int E_Number = 0 ;
						int Text_Number = 0 ;
						int P_Number = 0 ;

						for ( int l = 0 ; l < pDoc -> G_InGroup.GetAt ( m ).What.GetCount () ; l++ ) {
							// 그룹화 중 '선'을 출력함
							if ( pDoc -> G_InGroup.GetAt (m).What.GetAt (l) == _T ("L") ) {
								// 색상을 가지지 않을 경우의 출력
								if ( pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).L_Color == RGB (0,0,0) ) {
									if ( pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Pattern == 1 ) {
										CPen pen ( PS_SOLID, pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
										CPen *Draw_Pen = pDC -> SelectObject(&pen);
										L_Insert.Start = pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Start ;
										L_Insert.Last = pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Last ;
										pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
										pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
										pDC->SelectObject(Draw_Pen);
									}
									else if ( pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Pattern == 2 ) {
										CPen pen ( PS_DASH, pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
										CPen *Draw_Pen = pDC -> SelectObject(&pen);
										L_Insert.Start = pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Start ;
										L_Insert.Last = pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Last ;
										pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
										pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
										pDC->SelectObject(Draw_Pen);
									}
									else if ( pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Pattern == 3 ) {
										CPen pen ( PS_DOT, pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
										CPen *Draw_Pen = pDC -> SelectObject(&pen);
										L_Insert.Start = pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Start ;
										L_Insert.Last = pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Last ;
										pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
										pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
										pDC->SelectObject(Draw_Pen);
									}
									else if ( pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Pattern == 4 ) {
										CPen pen ( PS_DASHDOT, pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
										CPen *Draw_Pen = pDC -> SelectObject(&pen);
										L_Insert.Start = pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Start ;
										L_Insert.Last = pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Last ;
										pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
										pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
										pDC->SelectObject(Draw_Pen);
									}
									else if ( pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Pattern == 5 ) {
										CPen pen ( PS_DASHDOTDOT, pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Thickness, RGB (0, 0, 0) ) ;
										CPen *Draw_Pen = pDC -> SelectObject(&pen);
										L_Insert.Start = pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Start ;
										L_Insert.Last = pDoc -> G_InGroup.GetAt (m).Line.GetAt (L_Number).Last ;
										pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
										pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
										pDC->SelectObject(Draw_Pen);
									}
								}
								// 특정 색상을 가졌을 경우의 출력
								else {
									if ( pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Pattern == 1 ) {
										CPen pen ( PS_SOLID, pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Thickness, pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).L_Color ) ;
										CPen *Draw_Pen = pDC -> SelectObject(&pen);
										L_Insert.Start = pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Start ;
										L_Insert.Last = pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Last ;
										pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
										pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
										pDC->SelectObject(Draw_Pen);
									}
									else if (pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Pattern == 2 ) {
										CPen pen ( PS_DASH, pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Thickness, pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).L_Color ) ;
										CPen *Draw_Pen = pDC -> SelectObject(&pen);
										L_Insert.Start = pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Start ;
										L_Insert.Last = pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Last ;
										pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
										pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
										pDC->SelectObject(Draw_Pen);
									}
									else if (pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Pattern == 3 ) {
										CPen pen ( PS_DOT, pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Thickness, pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).L_Color ) ;
										CPen *Draw_Pen = pDC -> SelectObject(&pen);
										L_Insert.Start = pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Start ;
										L_Insert.Last = pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Last ;
										pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
										pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
										pDC->SelectObject(Draw_Pen);
									}
									else if (pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Pattern == 4 ) {
										CPen pen ( PS_DASHDOT, pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Thickness, pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).L_Color ) ;
										CPen *Draw_Pen = pDC -> SelectObject(&pen);
										L_Insert.Start = pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Start ;
										L_Insert.Last = pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Last ;
										pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
										pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
										pDC->SelectObject(Draw_Pen);
									}
									else if (pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Pattern == 5 ) {
										CPen pen ( PS_DASHDOTDOT, pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Thickness, pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).L_Color ) ;
										CPen *Draw_Pen = pDC -> SelectObject(&pen);
										L_Insert.Start = pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Start ;
										L_Insert.Last = pDoc ->  G_InGroup.GetAt (m).Line.GetAt (L_Number).Last ;
										pDC -> MoveTo ( L_Insert.Start ) ;	// 선의 시작위치
										pDC -> LineTo ( L_Insert.Last ) ;	// 선의 종착점
										pDC->SelectObject(Draw_Pen);
									}
								}
								L_Number++ ;
							}

							// 그룹화 중 PolyLine을 출력함
							else if ( pDoc -> G_InGroup.GetAt (m).What.GetAt (l) == _T ("P") ) {

								int j ;
								for ( j = 0 ; j < pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetCount () - 1 ; j++ ) {

									// PolyLine이 색상을 가지지 않을 경우의 출력
									if ( pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).P_Color == RGB (0,0,0) ) {
										if ( pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Pattern == 1 ) {
											CPen pen ( PS_SOLID, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
											CPen *Draw_Pen = pDC -> SelectObject(&pen);
											P_PointStart = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
											P_PointLast = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
											pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
											pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
											pDC->SelectObject(Draw_Pen);
										}
										else if ( pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Pattern == 2 ) {
											CPen pen ( PS_DASH, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
											CPen *Draw_Pen = pDC -> SelectObject(&pen);
											P_PointStart = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
											P_PointLast = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
											pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
											pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
											pDC->SelectObject(Draw_Pen);
										}
										else if ( pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Pattern == 3 ) {
											CPen pen ( PS_DOT, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
											CPen *Draw_Pen = pDC -> SelectObject(&pen);
											P_PointStart = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
											P_PointLast = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
											pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
											pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
											pDC->SelectObject(Draw_Pen);
										}
										else if ( pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Pattern == 4 ) {
											CPen pen ( PS_DASHDOT, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
											CPen *Draw_Pen = pDC -> SelectObject(&pen);
											P_PointStart = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
											P_PointLast = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
											pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
											pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
											pDC->SelectObject(Draw_Pen);
										}
										else if ( pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Pattern == 5 ) {
											CPen pen ( PS_DASHDOTDOT, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).thickness, RGB (0, 0, 0) );
											CPen *Draw_Pen = pDC -> SelectObject(&pen);
											P_PointStart = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
											P_PointLast = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
											pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
											pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
											pDC->SelectObject(Draw_Pen);
										}

									}
									// PolyLine이 지정된 색상을 가졌을 경우의 출력
									else {
										if ( pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Pattern == 1 ) {
											CPen pen ( PS_SOLID, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).thickness, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).P_Color ) ;
											CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
											P_PointStart = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
											P_PointLast = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
											pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
											pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
											pDC->SelectObject(Draw_Pen);
										}
										else if ( pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Pattern == 2 ) {
											CPen pen ( PS_DASH, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).thickness, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).P_Color ) ;
											CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
											P_PointStart = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
											P_PointLast = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
											pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
											pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
											pDC->SelectObject(Draw_Pen);
										}
										else if ( pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Pattern == 3 ) {
											CPen pen ( PS_DOT, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).thickness, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).P_Color ) ;
											CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
											P_PointStart = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
											P_PointLast = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
											pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
											pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
											pDC->SelectObject(Draw_Pen);
										}
										else if ( pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Pattern == 4 ) {
											CPen pen ( PS_DASHDOT, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).thickness, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).P_Color ) ;
											CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
											P_PointStart = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
											P_PointLast = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
											pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
											pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
											pDC->SelectObject(Draw_Pen);
										}
										else if ( pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Pattern == 5 ) {
											CPen pen ( PS_DASHDOTDOT, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).thickness, pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).P_Color ) ;
											CPen *Draw_Pen = pDC -> SelectObject(&pen) ;
											P_PointStart = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j) ;
											P_PointLast = pDoc -> G_InGroup.GetAt (m).Poly.GetAt (P_Number).Poly_point.GetAt (j+1) ;
											pDC -> MoveTo ( P_PointStart ) ;		// 선의 시작위치
											pDC -> LineTo ( P_PointLast ) ;		// 선의 종착점
											pDC->SelectObject(Draw_Pen);
										}
									}

								}
								P_Number++ ;
							}

							// 그룹화 중 상자 객체를 출력함
							else if ( pDoc -> G_InGroup.GetAt (m).What.GetAt (l) == _T ("R") ) {
								// 선 색을 가지지 않았을 경우의 출력
								if ( pDoc -> G_InGroup.GetAt (m).R_Color.GetAt (R_Number) == RGB (0,0,0) ) {

									// 채우기 색상을 가지지 않았을 경우의 출력
									if ( pDoc -> G_InGroup.GetAt (m).R_IsNoFill.GetAt (R_Number) == 'o' ) {
										if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 1 ) {
											CPen pen;
											pen.CreatePen( PS_SOLID, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 2 ) {
											CPen pen;
											pen.CreatePen( PS_DASH, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 3 ) {
											CPen pen;
											pen.CreatePen( PS_DOT, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 4 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOT, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 5 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
									}
									// 채우기 색상을 가졌을 경우의 출력
									else {
										if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 1 ) {
											CPen pen;
											pen.CreatePen( PS_SOLID, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldBrush ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 2 ) {
											CPen pen;
											pen.CreatePen( PS_DASH, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldBrush ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 3 ) {
											CPen pen;
											pen.CreatePen( PS_DOT, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldBrush ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 4 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOT, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldBrush ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 5 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldBrush ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
									}
								}
								// 특정 선 색상을 가졌을 경우의 출력
								else {

									// 채우기 색상을 가지지 않았을 경우의 출력
									if ( pDoc -> G_InGroup.GetAt (m).R_IsNoFill.GetAt (R_Number) == 'o' ) {
										if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 1 ) {
											CPen pen;
											pen.CreatePen( PS_SOLID, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), pDoc -> G_InGroup.GetAt (m).R_Color.GetAt (R_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC ->SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 2 ) {
											CPen pen;
											pen.CreatePen( PS_DASH, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), pDoc -> G_InGroup.GetAt (m).R_Color.GetAt (R_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC ->SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 3 ) {
											CPen pen;
											pen.CreatePen( PS_DOT, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), pDoc -> G_InGroup.GetAt (m).R_Color.GetAt (R_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC ->SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 4 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOT, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), pDoc -> G_InGroup.GetAt (m).R_Color.GetAt (R_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC ->SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 5 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), pDoc -> G_InGroup.GetAt (m).R_Color.GetAt (R_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC ->SelectObject ( oldPen ) ;
										}
									}
									// 채우기 색상을 가졌을 경우의 출력
									else {
										if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 1 ) {
											CPen pen;
											pen.CreatePen( PS_SOLID, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), pDoc -> G_InGroup.GetAt (m).R_Color.GetAt (R_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
											pDC -> SelectObject ( oldBrush ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 2 ) {
											CPen pen;
											pen.CreatePen( PS_DASH, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), pDoc -> G_InGroup.GetAt (m).R_Color.GetAt (R_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
											pDC -> SelectObject ( oldBrush ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 3 ) {
											CPen pen;
											pen.CreatePen( PS_DOT, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), pDoc -> G_InGroup.GetAt (m).R_Color.GetAt (R_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
											pDC -> SelectObject ( oldBrush ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 4 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOT, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), pDoc -> G_InGroup.GetAt (m).R_Color.GetAt (R_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
											pDC -> SelectObject ( oldBrush ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).R_LinePattern.GetAt (R_Number) == 5 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_InGroup.GetAt (m).R_Thickness.GetAt (R_Number), pDoc -> G_InGroup.GetAt (m).R_Color.GetAt (R_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).R_FillPattern.GetAt (R_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).R_FillColor.GetAt (R_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Rect [R_Number].left, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].top, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].right, pDoc -> G_InGroup.GetAt (m).Rect [R_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
											pDC -> SelectObject ( oldBrush ) ;
										}
									}
								}
								R_Number++ ;
							}

							// 그룹화 객체중 원을 출력
							else if ( pDoc -> G_InGroup.GetAt (m).What.GetAt (l) == _T ("E") ) {
								// 선 색을 가지지 않았을 경우의 출력
								if ( pDoc -> G_InGroup.GetAt (m).E_Color.GetAt (E_Number) == RGB (0,0,0) ) {
									// 채우기 색상을 가지지 않았을 경우의 출력
									if ( pDoc -> G_InGroup.GetAt (m).E_IsNoFill.GetAt (E_Number) == 'o' ) {
										if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 1 ) {
											CPen pen;
											pen.CreatePen( PS_SOLID, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 2 ) {
											CPen pen;
											pen.CreatePen( PS_DASH, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 3 ) {
											CPen pen;
											pen.CreatePen( PS_DOT, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 4 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOT, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 5 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
									}
									// 채우기 색상을 가졌을 경우의 출력
									else {
										if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 1 ) {
											CPen pen;
											pen.CreatePen( PS_SOLID, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldBrush ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 2 ) {
											CPen pen;
											pen.CreatePen( PS_DASH, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldBrush ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 3 ) {
											CPen pen;
											pen.CreatePen( PS_DOT, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldBrush ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 4 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOT, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldBrush ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 5 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), RGB (0,0,0) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldBrush ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
									}
								}
								// 특정 선 색상을 가졌을 경우의 출력
								else {
									// 채우기 색상을 가지지 않았을 경우의 출력
									if ( pDoc -> G_InGroup.GetAt (m).E_IsNoFill.GetAt (E_Number) == 'o' ) {
										if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 1 ) {
											CPen pen;
											pen.CreatePen( PS_SOLID, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), pDoc -> G_InGroup.GetAt (m).E_Color.GetAt (E_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 2 ) {
											CPen pen;
											pen.CreatePen( PS_DASH, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), pDoc -> G_InGroup.GetAt (m).E_Color.GetAt (E_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 3 ) {
											CPen pen;
											pen.CreatePen( PS_DOT, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), pDoc -> G_InGroup.GetAt (m).E_Color.GetAt (E_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 4 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOT, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), pDoc -> G_InGroup.GetAt (m).E_Color.GetAt (E_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 5 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), pDoc -> G_InGroup.GetAt (m).E_Color.GetAt (E_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											pDC -> SelectStockObject ( NULL_BRUSH ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
										}
									}
									// 채우기 색상을 가졌을 경우의 출력
									else {
										if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 1 ) {
											CPen pen;
											pen.CreatePen( PS_SOLID, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), pDoc -> G_InGroup.GetAt (m).E_Color.GetAt (E_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
											pDC -> SelectObject ( oldBrush ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 2 ) {
											CPen pen;
											pen.CreatePen( PS_DASH, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), pDoc -> G_InGroup.GetAt (m).E_Color.GetAt (E_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
											pDC -> SelectObject ( oldBrush ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 3 ) {
											CPen pen;
											pen.CreatePen( PS_DOT, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), pDoc -> G_InGroup.GetAt (m).E_Color.GetAt (E_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
											pDC -> SelectObject ( oldBrush ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 4 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOT, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), pDoc -> G_InGroup.GetAt (m).E_Color.GetAt (E_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
											pDC -> SelectObject ( oldBrush ) ;
										}
										else if ( pDoc -> G_InGroup.GetAt (m).E_LinePattern.GetAt (E_Number) == 5 ) {
											CPen pen;
											pen.CreatePen( PS_DASHDOTDOT, pDoc -> G_InGroup.GetAt (m).E_Thickness.GetAt (E_Number), pDoc -> G_InGroup.GetAt (m).E_Color.GetAt (E_Number) ) ;
											CPen* oldPen = pDC->SelectObject( &pen ) ;
											CBrush brush;
											if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 1 )
												brush.CreateSolidBrush( pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 2 )
												brush.CreateHatchBrush ( HS_BDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 3 )
												brush.CreateHatchBrush ( HS_CROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 4 )
												brush.CreateHatchBrush ( HS_DIAGCROSS, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 5 )
												brush.CreateHatchBrush ( HS_FDIAGONAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 6 )
												brush.CreateHatchBrush ( HS_HORIZONTAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;
											else if ( pDoc -> G_InGroup.GetAt (m).E_FillPattern.GetAt (E_Number) == 7 )
												brush.CreateHatchBrush ( HS_VERTICAL, pDoc -> G_InGroup.GetAt (m).E_FillColor.GetAt (E_Number) ) ;

											CBrush* oldBrush = pDC->SelectObject( &brush ) ;
											pDC -> Ellipse ( pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].left, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].top, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].right, pDoc -> G_InGroup.GetAt (m).Ellipse [E_Number].bottom ) ;
											pDC -> SelectObject ( oldPen ) ;
											pDC -> SelectObject ( oldBrush ) ;
										}
									}
								}
								E_Number++ ;
							}

							// 그룹화 객체중 텍스트를 출력
							else if ( pDoc -> G_InGroup.GetAt (m).What.GetAt (l) == _T ("Text") ) {
								// 폰트 지정한 경우
								if ( pDoc -> G_InGroup.GetAt (m).Text.GetAt ( Text_Number ).IsFont == 'o' ) {

									CFont Font ;
									Font.CreateFontIndirect ( &(pDoc -> G_InGroup.GetAt (m).Text.GetAt ( Text_Number ).Font) ) ;
									CFont* def_font = pDC -> SelectObject ( &Font ) ;
									pDC -> SetTextColor ( pDoc -> G_InGroup.GetAt (m).Text.GetAt ( Text_Number ).Color ) ;

									// 배경색 추가한 경우
									if ( pDoc -> G_InGroup.GetAt (m).Text.GetAt ( Text_Number ).IsNoFill == 'x' ) {
										pDC->SetBkMode(TRANSPARENT);
										pDC -> SelectStockObject ( NULL_PEN ) ;
										CBrush brush ;
										brush.CreateSolidBrush ( pDoc -> G_InGroup.GetAt (m).Text.GetAt ( Text_Number ).BGColor ) ;
										CBrush* oldBrush = pDC->SelectObject( &brush ) ;

										pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Text.GetAt (Text_Number).Text_Rect.left, pDoc -> G_InGroup.GetAt (m).Text.GetAt (Text_Number).Text_Rect.top,
											pDoc -> G_InGroup.GetAt (m).Text.GetAt (Text_Number).Text_Rect.right, pDoc -> G_InGroup.GetAt (m).Text.GetAt (Text_Number).Text_Rect.bottom ) ;
										pDC -> SelectObject ( oldBrush ) ;
									}

									pDC -> TextOut ( pDoc ->  G_InGroup.GetAt (m).Text.GetAt (Text_Number).Location.x, pDoc ->  G_InGroup.GetAt (m).Text.GetAt (Text_Number).Location.y + pDoc ->  G_InGroup.GetAt (m).Text.GetAt (Text_Number).Font.lfHeight,
										pDoc ->  G_InGroup.GetAt (m).Text.GetAt (Text_Number).Text ) ;
									pDC -> SelectObject ( def_font ) ;
								}
								// 폰트 지정을 하지 않은 경우
								else {

									// 배경색 추가한 경우
									if ( pDoc -> G_InGroup.GetAt (m).Text.GetAt (Text_Number).IsNoFill == 'x' ) {
										pDC->SetBkMode(TRANSPARENT);
										pDC -> SelectStockObject ( NULL_PEN ) ;
										CBrush brush ;
										brush.CreateSolidBrush ( pDoc -> G_InGroup.GetAt (m).Text.GetAt (Text_Number).BGColor ) ;
										CBrush* oldBrush = pDC->SelectObject( &brush ) ;

										pDC -> Rectangle ( pDoc -> G_InGroup.GetAt (m).Text.GetAt (Text_Number).Text_Rect.left, pDoc -> G_InGroup.GetAt (m).Text.GetAt (Text_Number).Text_Rect.top,
											pDoc -> G_InGroup.GetAt (m).Text.GetAt (Text_Number).Text_Rect.right, pDoc -> G_InGroup.GetAt (m).Text.GetAt (Text_Number).Text_Rect.bottom ) ;
										pDC -> SelectObject ( oldBrush ) ;
									}

									pDC -> TextOut ( pDoc ->  G_InGroup.GetAt (m).Text.GetAt (Text_Number).Location.x, pDoc ->  G_InGroup.GetAt (m).Text.GetAt (Text_Number).Location.y,
										pDoc ->  G_InGroup.GetAt (m).Text.GetAt (Text_Number).Text ) ;

								}
							}
						}
					}
					G_Numbers++ ;
				}
			}
			G_Number++ ;
		}
	}

	if ( m_IsSelectGroup == 'o' || G_IsMakeGroup == 'o' ) {
		CPen pen ( PS_DOT, 1.8, RGB (0, 0, 150) ) ;
		CPen *Draw_Pen = pDC -> SelectObject(&pen);
		pDC -> SelectStockObject ( NULL_BRUSH ) ;
		pDC -> Rectangle ( G_Include.left, G_Include.top, G_Include.right, G_Include.bottom ) ;
		pDC -> SelectObject ( Draw_Pen ) ;
	}
	else if ( G_ViewSelection == 'o' ) {
		CPen pen ( PS_SOLID, 1.8, RGB (200, 0, 0) ) ;
		CPen *Draw_Pen = pDC -> SelectObject(&pen);
		pDC -> SelectStockObject ( NULL_BRUSH ) ;
		pDC -> Rectangle ( pDoc -> G_Group.GetAt (G_Current).GroupBox.left - 5 , pDoc -> G_Group.GetAt (G_Current).GroupBox.top - 5, pDoc -> G_Group.GetAt (G_Current).GroupBox.right + 5 , pDoc -> G_Group.GetAt (G_Current).GroupBox.bottom + 5 ) ;
		pDC -> SelectObject ( Draw_Pen ) ;
		G_ViewSelection = 'x' ;
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
		pDoc->L_Location.Add ( pDoc->What.GetSize () - 1 ) ;
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
		pDoc->R_Location.Add ( pDoc->What.GetSize () - 1 ) ;
		pDoc->R_Count++ ;
		R_Current = pDoc -> R_Rec.GetCount () - 1 ;
		R_CanMove = 'o' ;

		if ( m_IsColor == 'o' )
			pDoc -> R_Color.Add ( m_Color ) ;
		else if ( m_IsColor == 'x' )
			pDoc -> R_Color.Add ( RGB(0,0,0) ) ;

		if ( m_IsFillColor == 'o' ) {
			pDoc -> R_FillColor.Add ( m_FillColor ) ;
			pDoc -> R_IsNoFill.Add ( 'x' ) ;
		}
		else if ( m_IsFillColor == 'x' ) {
			pDoc -> R_FillColor.Add ( RGB(0,0,0) ) ;
			pDoc -> R_IsNoFill.Add ( 'o' ) ;
		}

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> R_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> R_Thickness.Add (1) ;

		if ( m_IsFillPattern == 'o' )
			pDoc -> R_FillPattern.Add ( m_FillPattern ) ;
		else
			pDoc -> R_FillPattern.Add ( 1 ) ;

		if ( m_IsLinePattern == 'o' )
			pDoc -> R_LinePattern.Add ( m_LinePattern ) ;
		else
			pDoc -> R_LinePattern.Add ( 1 ) ;

	}
	// PolyLine을 계속해서 그리거나 변경하는 경우
	else if ( (P_IsContinue == 'o') || (M_IsDraw == 'o' && P_IsContinue == 'o') ) {
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
						  P_Insert.Poly_point.GetAt ( 0 ).y >= point.y - 15) ) {
						P_IsStart = 'o' ;
						PSkeleton = 0 ;
						m_PSkeleton = 'o' ;
					}
					else {
						P_CurrentPoint++ ;
						PSkeleton = 1 ;
						m_PSkeleton = 'o' ;
					}

					P_ChangeSkeleton = 0 ;
					P_CanMove = 'o' ;
					m_PSkeleton = 'o' ;
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
					PSkeleton = i ;
					m_PSkeleton = 'o' ;
					break ;
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
						PSkeleton = 0 ;
						P_ChangeSkeleton = 0 ;
						m_PSkeleton = 'o' ;
				}
				// 마지막 Skeleton을 건드리면 그 Skeleton을 변경한다.
				else if ( (P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x <= point.x + 15 &&
					P_Insert.Poly_point.GetAt ( P_CurrentPoint ).x >= point.x - 15 &&
					P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y <= point.y + 15 &&
					P_Insert.Poly_point.GetAt ( P_CurrentPoint ).y >= point.y - 15) ) {
						P_CanMove = 'o' ;
						PSkeleton = P_CurrentPoint ;
						P_CurrentPoint++ ;
						P_ChangeSkeleton = 0 ;
						m_PSkeleton = 'o' ;
				}
			}
		}
	}
	// PolyLine 그리기 시, 맨 처음 Skeleton을 클릭하여 만들 경우입니다.
	else if ( P_IsDraw == 'o' && P_IsContinue == 'x' ) {
		P_Insert.Poly_point.Add ( point ) ;
		pDoc->What.Add ( _T("P") ) ;
		pDoc->P_Location.Add ( pDoc->What.GetSize () - 1 ) ;
		pDoc -> P_Count = P_Current = pDoc -> P_Poly.GetCount () ;
		pDoc -> P_Count++ ;
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

		if ( m_IsLinePattern == 'o' )
			pDoc -> P_Poly.GetAt ( P_Current ).Pattern = m_LinePattern ;
		else
			pDoc -> P_Poly.GetAt ( P_Current ).Pattern = 1 ;
	}
	// 원을 그리는 경우
	else if ( E_IsDraw == 'o' ) {
		E_Insert.left = point.x ;
		E_Insert.right = point.x ;
		E_Insert.top = point.y ;
		E_Insert.bottom = point.y ;

		pDoc -> E_Ellipse.Add ( E_Insert ) ;
		pDoc->What.Add ( _T("E") ) ;
		pDoc->E_Location.Add ( pDoc->What.GetSize () - 1 ) ;
		pDoc->E_Count++ ;
		R_Current = pDoc -> E_Ellipse.GetCount () - 1 ;
		E_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> E_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> E_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' ) {
			pDoc -> E_FillColor.Add ( m_FillColor ) ;
			pDoc -> E_IsNoFill.Add ( 'x' ) ;
		}
		else if ( m_IsFillColor == 'x' ) {
			pDoc -> E_FillColor.Add ( RGB(0,0,0) ) ;
			pDoc -> E_IsNoFill.Add ( 'o' ) ;
		}

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> E_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> E_Thickness.Add (1) ;

		if ( m_IsFillPattern == 'o' )
			pDoc -> E_FillPattern.Add ( m_FillPattern ) ;
		else
			pDoc -> E_FillPattern.Add ( 1 ) ;

		if ( m_IsLinePattern == 'o' )
			pDoc -> E_LinePattern.Add ( m_LinePattern ) ;
		else
			pDoc -> E_LinePattern.Add ( 1 ) ;

	}
	// 세모를 그리는 경우
	else if ( T_IsDraw == 'o' ) {
		T_Insert.left = point.x ;
		T_Insert.right = point.x ;
		T_Insert.top = point.y ;
		T_Insert.bottom = point.y ;

		pDoc -> T_Triangle.Add ( T_Insert ) ;
		pDoc->What.Add ( _T("T") ) ;
		pDoc->T_Location.Add ( pDoc->What.GetSize () - 1 ) ;
		pDoc->T_Count++ ;
		T_Current = pDoc -> T_Triangle.GetCount () - 1 ;
		T_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> T_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> T_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' ) {
			pDoc -> T_FillColor.Add ( m_FillColor ) ;
			pDoc -> T_IsNoFill.Add ( 'x' ) ;
		}
		else if ( m_IsFillColor == 'x' ) {
			pDoc -> T_FillColor.Add ( RGB(0,0,0) ) ;
			pDoc -> T_IsNoFill.Add ( 'o' ) ;
		}

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> T_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> T_Thickness.Add (1) ;

		if ( m_IsFillPattern == 'o' )
			pDoc -> T_FillPattern.Add ( m_FillPattern ) ;
		else
			pDoc -> T_FillPattern.Add ( 1 ) ;

		if ( m_IsLinePattern == 'o' )
			pDoc -> T_LinePattern.Add ( m_LinePattern ) ;
		else
			pDoc -> T_LinePattern.Add ( 1 ) ;
	}
	// 역 삼각형을 그리는 경우
	else if ( RT_IsDraw == 'o' ) {
		RT_Insert.left = point.x ;
		RT_Insert.right = point.x ;
		RT_Insert.top = point.y ;
		RT_Insert.bottom = point.y ;

		pDoc -> RT_Triangle.Add ( RT_Insert ) ;
		pDoc->What.Add ( _T("RT") ) ;
		pDoc->RT_Location.Add ( pDoc->What.GetSize () - 1 ) ;
		pDoc->RT_Count++ ;
		RT_Current = pDoc -> RT_Triangle.GetCount () - 1 ;
		RT_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> RT_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> RT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' ) {
			pDoc -> RT_FillColor.Add ( m_FillColor ) ;
			pDoc -> RT_IsNoFill.Add ( 'x' ) ;
		}
		else if ( m_IsFillColor == 'x' ) {
			pDoc -> RT_FillColor.Add ( RGB(0,0,0) ) ;
			pDoc -> RT_IsNoFill.Add ( 'o' ) ;
		}

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> RT_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> RT_Thickness.Add (1) ;

		if ( m_IsFillPattern == 'o' )
			pDoc -> RT_FillPattern.Add ( m_FillPattern ) ;
		else
			pDoc -> RT_FillPattern.Add ( 1 ) ;

		if ( m_IsLinePattern == 'o' )
			pDoc -> RT_LinePattern.Add ( m_LinePattern ) ;
		else
			pDoc -> RT_LinePattern.Add ( 1 ) ;
	}
	// 직각 삼각형을 그리는 경우
	else if ( RightT_IsDraw == 'o' ) {
		RightT_Insert.left = point.x ;
		RightT_Insert.right = point.x ;
		RightT_Insert.top = point.y ;
		RightT_Insert.bottom = point.y ;

		pDoc -> RightT_Triangle.Add ( RightT_Insert ) ;
		pDoc->What.Add ( _T("RightT") ) ;
		pDoc->RightT_Location.Add ( pDoc->What.GetSize () - 1 ) ;
		pDoc->RightT_Count++ ;
		RightT_Current = pDoc -> RightT_Triangle.GetCount () - 1 ;
		RightT_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> RightT_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> RightT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' ) {
			pDoc -> RightT_FillColor.Add ( m_FillColor ) ;
			pDoc -> RightT_IsNoFill.Add ( 'x' ) ;
		}
		else if ( m_IsFillColor == 'x' ) {
			pDoc -> RightT_FillColor.Add ( RGB(0,0,0) ) ;
			pDoc -> RightT_IsNoFill.Add ( 'o' ) ;
		}

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> RightT_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> RightT_Thickness.Add (1) ;

		if ( m_IsFillPattern == 'o' )
			pDoc -> RightT_FillPattern.Add ( m_FillPattern ) ;
		else
			pDoc -> RightT_FillPattern.Add ( 1 ) ;

		if ( m_IsLinePattern == 'o' )
			pDoc -> RightT_LinePattern.Add ( m_LinePattern ) ;
		else
			pDoc -> RightT_LinePattern.Add ( 1 ) ;
	}
	// 역 직각 삼각형을 그리는 경우
	else if ( RRightT_IsDraw == 'o' ) {
		RRightT_Insert.left = point.x ;
		RRightT_Insert.right = point.x ;
		RRightT_Insert.top = point.y ;
		RRightT_Insert.bottom = point.y ;

		pDoc -> RRightT_Triangle.Add ( RRightT_Insert ) ;
		pDoc->What.Add ( _T("RRightT") ) ;
		pDoc->RRightT_Location.Add ( pDoc->What.GetSize () - 1 ) ;
		pDoc->RRightT_Count++ ;
		RRightT_Current = pDoc -> RRightT_Triangle.GetCount () - 1 ;
		RRightT_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> RRightT_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> RRightT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' ) {
			pDoc -> RRightT_FillColor.Add ( m_FillColor ) ;
			pDoc -> RRightT_IsNoFill.Add ( 'x' ) ;
		}
		else if ( m_IsFillColor == 'x' ) {
			pDoc -> RRightT_FillColor.Add ( RGB(0,0,0) ) ;
			pDoc -> RRightT_IsNoFill.Add ( 'o' ) ;
		}

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> RRightT_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> RRightT_Thickness.Add (1) ;

		if ( m_IsFillPattern == 'o' )
			pDoc -> RRightT_FillPattern.Add ( m_FillPattern ) ;
		else
			pDoc -> RRightT_FillPattern.Add ( 1 ) ;

		if ( m_IsLinePattern == 'o' )
			pDoc -> RRightT_LinePattern.Add ( m_LinePattern ) ;
		else
			pDoc -> RRightT_LinePattern.Add ( 1 ) ;
	}
	// 왼쪽 -> 오른쪽 삼각형을 그리는 경우
	else if ( LTRT_IsDraw == 'o' ) {
		LTRT_Insert.left = point.x ;
		LTRT_Insert.right = point.x ;
		LTRT_Insert.top = point.y ;
		LTRT_Insert.bottom = point.y ;

		pDoc -> LTRT_Triangle.Add ( LTRT_Insert ) ;
		pDoc->What.Add ( _T("LTRT") ) ;
		pDoc->LTRT_Location.Add ( pDoc->What.GetSize () - 1 ) ;
		pDoc->LTRT_Count++ ;
		LTRT_Current = pDoc -> LTRT_Triangle.GetCount () - 1 ;
		LTRT_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> LTRT_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> LTRT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' ) {
			pDoc -> LTRT_FillColor.Add ( m_FillColor ) ;
			pDoc -> LTRT_IsNoFill.Add ( 'x' ) ;
		}
		else if ( m_IsFillColor == 'x' ) {
			pDoc -> LTRT_FillColor.Add ( RGB(0,0,0) ) ;
			pDoc -> LTRT_IsNoFill.Add ( 'o' ) ;
		}

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> LTRT_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> LTRT_Thickness.Add (1) ;

		if ( m_IsFillPattern == 'o' )
			pDoc -> LTRT_FillPattern.Add ( m_FillPattern ) ;
		else
			pDoc -> LTRT_FillPattern.Add ( 1 ) ;

		if ( m_IsLinePattern == 'o' )
			pDoc -> LTRT_LinePattern.Add ( m_LinePattern ) ;
		else
			pDoc -> LTRT_LinePattern.Add ( 1 ) ;
	}
	// 오른쪽 -> 왼쪽 삼각형을 그리는 경우
	else if ( RTLT_IsDraw == 'o' ) {
		RTLT_Insert.left = point.x ;
		RTLT_Insert.right = point.x ;
		RTLT_Insert.top = point.y ;
		RTLT_Insert.bottom = point.y ;

		pDoc -> RTLT_Triangle.Add ( RTLT_Insert ) ;
		pDoc->What.Add ( _T("RTLT") ) ;
		pDoc->RTLT_Location.Add ( pDoc->What.GetSize () - 1 ) ;
		pDoc->RTLT_Count++ ;
		RTLT_Current = pDoc -> RTLT_Triangle.GetCount () - 1 ;
		RTLT_CanMove = 'o' ;

		// 만약 색상을 선택하고 그렸을 경우 선택 색상을 기억.
		if ( m_IsColor == 'o' )
			pDoc -> RTLT_Color.Add ( m_Color ) ;
		// 색상을 선택하지 않고 그렸을 경우 표준 색상 기억.
		else if ( m_IsColor == 'x' )
			pDoc -> RTLT_Color.Add (RGB(0,0,0)) ;

		if ( m_IsFillColor == 'o' ) {
			pDoc -> RTLT_FillColor.Add ( m_FillColor ) ;
			pDoc -> RTLT_IsNoFill.Add ( 'x' ) ;
		}
		else if ( m_IsFillColor == 'x' ) {
			pDoc -> RTLT_FillColor.Add ( RGB(0,0,0) ) ;
			pDoc -> RTLT_IsNoFill.Add ( 'o' ) ;
		}

		// 두께 설정을 한 경우
		if ( m_IsThickness == 'o' )
			pDoc -> RTLT_Thickness.Add ( m_Thickness ) ;
		// 두께 설정을 하지 않은 경우
		else if ( m_IsThickness == 'x' )
			pDoc -> RTLT_Thickness.Add (1) ;

		if ( m_IsFillPattern == 'o' )
			pDoc -> RTLT_FillPattern.Add ( m_FillPattern ) ;
		else
			pDoc -> RTLT_FillPattern.Add ( 1 ) ;

		if ( m_IsLinePattern == 'o' )
			pDoc -> RTLT_LinePattern.Add ( m_LinePattern ) ;
		else
			pDoc -> RTLT_LinePattern.Add ( 1 ) ;
	}

	if ( Text_IsText == 'o' && Text_IsKeyDown == 'o' ) {
		HideCaret () ;
		Text_IsKeyDown = 'x' ;
	}
	// 텍스트를 입력 하는 경우
	else if ( Text_IsText == 'o' && Text_IsKeyDown == 'x' ) {
		Text_Current = pDoc -> Text_Text.GetCount () ;
		pDoc -> Text_Text.SetSize ( pDoc -> Text_Text.GetCount () + 1 ) ;
		pDoc -> What.Add ( _T("Text") ) ;
		pDoc -> Text_Location.Add ( pDoc->What.GetCount () - 1 ) ;
		pDoc -> Text_Count++ ;
		pDoc -> Text_Text.GetAt ( Text_Current ).Location = point ;

		// 폰트 설정을 한 경우
		if ( Text_IsFont == 'o' ) {
			pDoc -> Text_Text.GetAt ( Text_Current ).Font = Text_lf ;
			pDoc -> Text_Text.GetAt ( Text_Current ).IsFont = 'o' ;
			CreateSolidCaret ( 1, Text_lf.lfHeight ) ;
			pDoc -> Text_Text.GetAt ( Text_Current ).Color = Text_Color ;
		}
		else {
			pDoc -> Text_Text.GetAt ( Text_Current ).IsFont = 'x' ;
			CreateSolidCaret ( 1, 16 ) ;
		}

		if ( Text_IsBGColor == 'o' ) {
			pDoc -> Text_Text.GetAt ( Text_Current ).BGColor = Text_BGColor ;
			pDoc -> Text_Text.GetAt ( Text_Current ).IsNoFill = 'x' ;
		}
		else {
			pDoc -> Text_Text.GetAt ( Text_Current ).IsNoFill = 'o' ;
		}

		SetCaretPos ( point ) ;
		
		ShowCaret () ;
		Invalidate () ;
		Text_IsKeyDown = 'o' ;
	}
	// 객체를 이동, 선택하는 경우
	else if ( M_IsMove == 'o' && P_CanMove == 'x' ) {

		char Find = 'x' ;
		// 선 객체를 변경시키는 경우
		if ( M_IsLineSelect == 'o' &&
			((pDoc -> L_Line.GetAt ( M_Number ).Start.x - 15 <= point.x && pDoc -> L_Line.GetAt ( M_Number ).Start.x + 15 >= point.x
			&& pDoc -> L_Line.GetAt ( M_Number ).Start.y - 15 <= point.y && pDoc -> L_Line.GetAt ( M_Number ).Start.y + 15 >= point.y) ||
			(pDoc -> L_Line.GetAt ( M_Number ).Last.x - 15 <= point.x && pDoc -> L_Line.GetAt ( M_Number ).Last.x + 15 >= point.x
			&& pDoc -> L_Line.GetAt ( M_Number ).Last.y - 15 <= point.y && pDoc -> L_Line.GetAt ( M_Number ).Last.y + 15 >= point.y)) ) {

				M_ChangeLineOnePoint = 'o' ;
				if ( pDoc -> L_Line.GetAt ( M_Number ).Start.x - 15 <= point.x && pDoc -> L_Line.GetAt ( M_Number ).Start.x + 15 >= point.x
					&& pDoc -> L_Line.GetAt ( M_Number ).Start.y - 15 <= point.y && pDoc -> L_Line.GetAt ( M_Number ).Start.y + 15 >= point.y ) {

						M_IsChangeLineStart = 'o' ;
				}
				else {
					M_IsChangeLineStart = 'x' ;
				}
		}

		// 상자 객체를 변경시키는 경우
		else if ( M_IsRectSelect == 'o' &&
				( ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) ||
				  ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) ||
				  ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) ||
				  ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) ||
				  ((M_Rect.right - M_Rect.left) / 2 + M_Rect.left + 15 >= point.x && (M_Rect.right - M_Rect.left) / 2 + M_Rect.left - 15 <= point.x &&
				    M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y ) ||
				  ((M_Rect.right - M_Rect.left) / 2 + M_Rect.left + 15 >= point.x && (M_Rect.right - M_Rect.left) / 2 + M_Rect.left - 15 <= point.x &&
				    M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y) ||
				  ((M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top - 15 <= point.y && (M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top + 15 >= point.y &&
				    M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x) ||
				  ((M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top - 15 <= point.y && (M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top + 15 >= point.y &&
				    M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x) ) ) {

			M_ChangeRectSize = 'o' ;
			if ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) {
				M_IsChangeRectSide = 'o' ;
				M_IsChangeRectNW = 'o' ;
				M_ChangeRect.top = point.y ;
				M_ChangeRect.left = point.x ;
				M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;
				M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).right ;

				M_Start.x = point.x ;
				M_Start.y = point.y ;
			}
			else if ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) {
				M_IsChangeRectSide = 'o' ;
				M_IsChangeRectNE = 'o' ;
				M_ChangeRect.top = point.y ;
				M_ChangeRect.right = point.x ;
				M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).left ;
				M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;

				M_Start.x = point.x ;
				M_Start.y = point.y ;
			}
			else if ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) {
				M_IsChangeRectSide = 'o' ;
				M_IsChangeRectSW = 'o' ;
				M_ChangeRect.bottom = point.y ;
				M_ChangeRect.left = point.x ;
				M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).right ;

				M_Start.x = point.x ;
				M_Start.y = point.y ;
			}
			else if ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) {
				M_IsChangeRectSide = 'o' ;
				M_IsChangeRectNW ;
				M_IsChangeRectSE = 'o' ;
				M_ChangeRect.bottom = point.y ;
				M_ChangeRect.right = point.x ;
				M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).left ;

				M_Start.x = point.x ;
				M_Start.y = point.y ;
			}
			else if ( (M_Rect.right - M_Rect.left) / 2 + M_Rect.left + 15 >= point.x && (M_Rect.right - M_Rect.left) / 2 + M_Rect.left - 15 <= point.x &&
				    M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y ) {
				M_IsChangeRectVerticalTop = 'o' ;
				M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).left ;
				M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).right ;
				M_ChangeRect.top = point.y ;
				M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;

				M_Start.y = point.y ;
			}
			else if ( (M_Rect.right - M_Rect.left) / 2 + M_Rect.left + 15 >= point.x && (M_Rect.right - M_Rect.left) / 2 + M_Rect.left - 15 <= point.x &&
				    M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y ) {
				M_IsChangeRectVerticalBottom = 'o' ;
				M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).left ;
				M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).right ;
				M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				M_ChangeRect.bottom = point.y ;

				M_Start.y = point.y ;
			}
			else if ( (M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top - 15 <= point.y && (M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top + 15 >= point.y &&
				    M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) {
				M_IsChangeRectWidthLeft = 'o' ;
				M_ChangeRect.left = point.x ;
				M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).right ;
				M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;

				M_Start.x = point.x ;
			}
			else {
				M_IsChangeRectWidthRight = 'o' ;
				M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).left ;
				M_ChangeRect.right = point.x ;
				M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;

				M_Start.x = point.x ;
			}
		}
		// 원 객체를 변경시키는 경우
		else if ( M_IsEllipseSelect == 'o' &&
				( ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) ||
				  ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) ||
				  ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) ||
				  ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) ||
				  ((M_Rect.right - M_Rect.left) / 2 + M_Rect.left + 15 >= point.x && (M_Rect.right - M_Rect.left) / 2 + M_Rect.left - 15 <= point.x &&
				    M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y ) ||
				  ((M_Rect.right - M_Rect.left) / 2 + M_Rect.left + 15 >= point.x && (M_Rect.right - M_Rect.left) / 2 + M_Rect.left - 15 <= point.x &&
				    M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y) ||
				  ((M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top - 15 <= point.y && (M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top + 15 >= point.y &&
				    M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x) ||
				  ((M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top - 15 <= point.y && (M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top + 15 >= point.y &&
				    M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x) ) ) {

			M_ChangeEllipseSize = 'o' ;
			if ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) {
				M_IsChangeEllipseSide = 'o' ;
				M_IsChangeEllipseNW = 'o' ;
				M_ChangeRect.top = point.y ;
				M_ChangeRect.left = point.x ;
				M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;
				M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;

				M_Start.x = point.x ;
				M_Start.y = point.y ;
			}
			else if ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) {
				M_IsChangeEllipseSide = 'o' ;
				M_IsChangeEllipseNE = 'o' ;
				M_ChangeRect.top = point.y ;
				M_ChangeRect.right = point.x ;
				M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
				M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;

				M_Start.x = point.x ;
				M_Start.y = point.y ;
			}
			else if ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) {
				M_IsChangeEllipseSide = 'o' ;
				M_IsChangeEllipseSW = 'o' ;
				M_ChangeRect.bottom = point.y ;
				M_ChangeRect.left = point.x ;
				M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;

				M_Start.x = point.x ;
				M_Start.y = point.y ;
			}
			else if ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) {
				M_IsChangeEllipseSide = 'o' ;
				M_IsChangeRectSE = 'o' ;
				M_ChangeRect.bottom = point.y ;
				M_ChangeRect.right = point.x ;
				M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;

				M_Start.x = point.x ;
				M_Start.y = point.y ;
			}
			else if ( (M_Rect.right - M_Rect.left) / 2 + M_Rect.left + 15 >= point.x && (M_Rect.right - M_Rect.left) / 2 + M_Rect.left - 15 <= point.x &&
				    M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y ) {
				M_IsChangeEllipseVerticalTop = 'o' ;
				M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
				M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;
				M_ChangeRect.top = point.y ;
				M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;

				M_Start.y = point.y ;
			}
			else if ( (M_Rect.right - M_Rect.left) / 2 + M_Rect.left + 15 >= point.x && (M_Rect.right - M_Rect.left) / 2 + M_Rect.left - 15 <= point.x &&
				    M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y ) {
				M_IsChangeEllipseVerticalBottom = 'o' ;
				M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
				M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;
				M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				M_ChangeRect.bottom = point.y ;

				M_Start.y = point.y ;
			}
			else if ( (M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top - 15 <= point.y && (M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top + 15 >= point.y &&
				    M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) {
				M_IsChangeEllipseWidthLeft = 'o' ;
				M_ChangeRect.left = point.x ;
				M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;
				M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;

				M_Start.x = point.x ;
			}
			else {
				M_IsChangeEllipseWidthRight = 'o' ;
				M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
				M_ChangeRect.right = point.x ;
				M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;

				M_Start.x = point.x ;
			}
		}
		else if ( G_IsMakeGroup != 'o' ) {
			M_IsLineSelect = 'x' ;
			M_IsRectSelect = 'x' ;
			M_IsEllipseSelect = 'x' ;
			M_ChangeLineOnePoint = 'x' ;
			M_IsChangeLineStart = 'x' ;
			M_ChangeRectSize = 'x' ;
			M_IsChangeRectVerticalTop = 'x' ;
			M_IsChangeRectVerticalBottom = 'x' ;
			M_IsChangeRectSide = 'x' ;
			M_IsChangeRectNW = 'x' ;
			M_IsChangeRectNE = 'x' ;
			M_IsChangeRectSW = 'x' ;
			M_IsChangeRectSE = 'x' ;
			M_IsChangeRectWidthLeft = 'x' ;
			M_IsChangeRectWidthRight = 'x' ;
			M_ChangeEllipseSize = 'x' ;
			M_IsChangeEllipseVerticalTop = 'x' ;
			M_IsChangeEllipseVerticalBottom = 'x' ;
			M_IsChangeEllipseSide = 'x' ;
			M_IsChangeEllipseNW = 'x' ;
			M_IsChangeEllipseNE = 'x' ;
			M_IsChangeEllipseSW = 'x' ;
			M_IsChangeEllipseSE = 'x' ;
			M_IsChangeEllipseWidthLeft = 'x' ;
			M_IsChangeEllipseWidthRight = 'x' ;

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
			int Text_Number = pDoc -> Text_Count - 1;
			int G_Number = pDoc -> G_Count - 1 ;

			// 선택한 좌표에 객체가 있는지 전부 확인합니다.
			// 늦게 그린 객체부터 확인합니다.
			int i ;
			for ( i = pDoc->What.GetCount () ; i > 0  ; i-- ) {

				// 선 객체인 경우
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
									M_IsDraw = 'o' ; P_IsContinue = 'x' ;
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
									Invalidate () ; M_IsLineSelect = 'o' ; Text_IsChange = 'x' ; Find = 'o' ; break ;
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
									M_IsDraw = 'o' ; P_IsContinue = 'x' ;
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
									Invalidate () ; M_IsLineSelect = 'o' ; Text_IsChange = 'x' ; Find = 'o' ; break ;
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
									M_IsDraw = 'o' ; P_IsContinue = 'x' ;
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
									Invalidate () ; M_IsLineSelect = 'o' ; Text_IsChange = 'x' ; Find = 'o' ; break ;
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
									M_IsDraw = 'o' ; P_IsContinue = 'x' ;
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
									Invalidate () ; M_IsLineSelect = 'o' ; Text_IsChange = 'x' ; Find = 'o' ; break ;
							}
						}
					}
					L_Number-- ;
				}

				// 상자 객체인 경우
				else if ( pDoc -> What.GetAt (i-1) == _T ("R") ) {
					if ( pDoc -> R_Rec.GetAt ( R_Number ).left - 2 <= point.x && pDoc -> R_Rec.GetAt ( R_Number ).right + 2 >= point.x &&
						pDoc -> R_Rec.GetAt ( R_Number ).top - 2 <= point.y && pDoc -> R_Rec.GetAt ( R_Number ).bottom + 2 >= point.y ) {

							M_Rect.top = pDoc -> R_Rec.GetAt ( R_Number ).top - pDoc -> R_Thickness.GetAt ( R_Number ) / 2 - 2 ;
							M_Rect.bottom = pDoc -> R_Rec.GetAt ( R_Number ).bottom + pDoc -> R_Thickness.GetAt ( R_Number ) / 2 + 2 ;
							M_Rect.left = pDoc -> R_Rec.GetAt ( R_Number ).left - pDoc -> R_Thickness.GetAt ( R_Number ) / 2 - 2 ;
							M_Rect.right = pDoc -> R_Rec.GetAt ( R_Number ).right + pDoc -> R_Thickness.GetAt ( R_Number ) / 2 + 2 ;

							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("R") ) ; M_Number = R_Number ;
							M_IsDraw = 'o' ; P_IsContinue = 'x' ; Text_IsChange = 'x' ;
							Invalidate () ; M_IsRectSelect = 'o' ; Find = 'o' ; break ;
					}
					R_Number-- ;
				}

				// PolyLine 객체인 경우
				else if ( pDoc -> What.GetAt (i-1) == _T ("P") ) {
					M_PMax_x = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (0).x ;
					M_PMax_y = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (0).y ;
					M_PMin_x = M_PMax_x ;
					M_PMin_y = M_PMax_y ;

					for ( int i = 1 ; i < pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetCount () ; i++ ) {
						if ( M_PMax_x < pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x )
							M_PMax_x = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x ;
						else if ( M_PMin_x > pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x )
							M_PMin_x = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).x ;

						if ( M_PMax_y < pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y )
							M_PMax_y = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y ;
						else if ( M_PMin_y > pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y )
							M_PMin_y = pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt (i).y ;
					}

					if ( M_PMax_x >= point.x && M_PMin_x <= point.x && M_PMax_y >= point.y && M_PMin_y <= point.y ) {
						M_Rect.top = M_PMin_y  - pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 ;
						M_Rect.bottom = M_PMax_y + pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 ;
						M_Rect.left = M_PMin_x - pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 ;
						M_Rect.right = M_PMax_x + pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 ;

						M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
						M_What.Format ( _T ("P") ) ; M_Number = P_Number ;
						M_IsDraw = 'o' ;
						P_Current = M_Number ;
						for ( int i = 0 ; i < pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetCount () ; i++ ) {
							P_Insert.Poly_point.Add ( pDoc -> P_Poly.GetAt ( M_Number ).Poly_point.GetAt (i) ) ;
						}
						P_Insert.P_Color = pDoc -> P_Poly.GetAt ( M_Number ).P_Color ;
						P_Insert.thickness = pDoc -> P_Poly.GetAt ( M_Number ).thickness ;
						P_CurrentPoint = pDoc -> P_Poly.GetAt ( M_Number ).Poly_point.GetCount () - 1 ;
						Invalidate () ; P_IsContinue = 'o' ; m_PSkeleton = 'x' ; Text_IsChange = 'x' ; Find = 'o' ; break ;
					}
					P_Number-- ;
				}

				// 원 객체인 경우
				else if ( pDoc -> What.GetAt (i-1) == _T ("E") ) {
					if ( pDoc -> E_Ellipse.GetAt ( E_Number ).left - 2 <= point.x && pDoc -> E_Ellipse.GetAt ( E_Number ).right + 2 >= point.x &&
						pDoc -> E_Ellipse.GetAt ( E_Number ).top - 2 <= point.y && pDoc -> E_Ellipse.GetAt ( E_Number ).bottom + 2 >= point.y ) {

							M_Rect.top = pDoc -> E_Ellipse.GetAt ( E_Number ).top - pDoc -> E_Thickness.GetAt ( E_Number ) / 2 - 2 ;
							M_Rect.bottom = pDoc -> E_Ellipse.GetAt ( E_Number ).bottom + pDoc -> E_Thickness.GetAt ( E_Number ) / 2 + 2 ;
							M_Rect.left = pDoc -> E_Ellipse.GetAt ( E_Number ).left - pDoc -> E_Thickness.GetAt ( E_Number ) / 2 - 2 ;
							M_Rect.right = pDoc -> E_Ellipse.GetAt ( E_Number ).right + pDoc -> E_Thickness.GetAt ( E_Number ) / 2 + 2 ;

							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("E") ) ; M_Number = E_Number ;
							M_IsDraw = 'o' ; P_IsContinue = 'x' ; Text_IsChange = 'x' ;
							Invalidate () ; M_IsEllipseSelect = 'o' ; Find = 'o' ; break ;
					}
					E_Number-- ;

				}

				// 세모 객체인 경우
				else if ( pDoc -> What.GetAt (i-1) == _T ("T") ) {
					if ( pDoc -> T_Triangle.GetAt ( T_Number ).left - 2 <= point.x && pDoc -> T_Triangle.GetAt ( T_Number ).right + 2 >= point.x &&
						pDoc -> T_Triangle.GetAt ( T_Number ).top - 2 <= point.y && pDoc -> T_Triangle.GetAt ( T_Number ).bottom + 2 >= point.y ) {

							M_Rect.top = pDoc -> T_Triangle.GetAt ( T_Number ).top - pDoc -> T_Thickness.GetAt ( T_Number ) / 2 - 2 ;
							M_Rect.bottom = pDoc -> T_Triangle.GetAt ( T_Number ).bottom + pDoc -> T_Thickness.GetAt ( T_Number ) / 2 + 2 ;
							M_Rect.left = pDoc -> T_Triangle.GetAt ( T_Number ).left - pDoc -> T_Thickness.GetAt ( T_Number ) / 2 - 2 ;
							M_Rect.right = pDoc -> T_Triangle.GetAt ( T_Number ).right + pDoc -> T_Thickness.GetAt ( T_Number ) / 2 + 2 ;

							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("T") ) ; M_Number = T_Number ;
							M_IsDraw = 'o' ; P_IsContinue = 'x' ; Text_IsChange = 'x' ;
							Invalidate () ; Find = 'o' ; break ;
					}
					T_Number-- ;
				}

				// 역 삼각형 객체인 경우
				else if ( pDoc -> What.GetAt (i-1) == _T ("RT") ) {
					if ( pDoc -> RT_Triangle.GetAt ( RT_Number ).left - 2 <= point.x && pDoc -> RT_Triangle.GetAt ( RT_Number ).right + 2 >= point.x &&
						pDoc -> RT_Triangle.GetAt ( RT_Number ).top - 2 <= point.y && pDoc -> RT_Triangle.GetAt ( RT_Number ).bottom + 2 >= point.y ) {

							M_Rect.top = pDoc -> RT_Triangle.GetAt ( RT_Number ).top - pDoc -> RT_Thickness.GetAt ( RT_Number ) / 2 - 2 ;
							M_Rect.bottom = pDoc -> RT_Triangle.GetAt ( RT_Number ).bottom + pDoc -> RT_Thickness.GetAt ( RT_Number ) / 2 + 2 ;
							M_Rect.left = pDoc -> RT_Triangle.GetAt ( RT_Number ).left - pDoc -> RT_Thickness.GetAt ( RT_Number ) / 2 - 2 ;
							M_Rect.right = pDoc -> RT_Triangle.GetAt ( RT_Number ).right + pDoc -> RT_Thickness.GetAt ( RT_Number ) / 2 + 2 ;

							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("RT") ) ; M_Number = RT_Number ;
							M_IsDraw = 'o' ; P_IsContinue = 'x' ; Text_IsChange = 'x' ;
							Invalidate () ; Find = 'o' ; break ;
					}
					RT_Number-- ;
				}

				// 직각 삼각형 객체인 경우
				else if ( pDoc -> What.GetAt (i-1) == _T ("RightT") ) {
					if ( pDoc -> RightT_Triangle.GetAt ( RightT_Number ).left - 2 <= point.x && pDoc -> RightT_Triangle.GetAt ( RightT_Number ).right + 2 >= point.x &&
						pDoc -> RightT_Triangle.GetAt ( RightT_Number ).top - 2 <= point.y && pDoc -> RightT_Triangle.GetAt ( RightT_Number ).bottom + 2 >= point.y ) {

							M_Rect.top = pDoc -> RightT_Triangle.GetAt ( RightT_Number ).top - pDoc -> RightT_Thickness.GetAt ( RightT_Number ) / 2 - 2 ;
							M_Rect.bottom = pDoc -> RightT_Triangle.GetAt ( RightT_Number ).bottom + pDoc -> RightT_Thickness.GetAt ( RightT_Number ) / 2 + 2 ;
							M_Rect.left = pDoc -> RightT_Triangle.GetAt ( RightT_Number ).left - pDoc -> RightT_Thickness.GetAt ( RightT_Number ) / 2 - 2 ;
							M_Rect.right = pDoc -> RightT_Triangle.GetAt ( RightT_Number ).right + pDoc -> RightT_Thickness.GetAt ( RightT_Number ) / 2 + 2 ;

							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("RightT") ) ; M_Number = RightT_Number ;
							M_IsDraw = 'o' ; P_IsContinue = 'x' ; Text_IsChange = 'x' ;
							Invalidate () ; Find = 'o' ; break ;
					}
					RightT_Number-- ;
				}

				// 역 직각 삼각형 객체인 경우
				else if ( pDoc -> What.GetAt (i-1) == _T ("RRightT") ) {
					if ( pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).left - 2 <= point.x && pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).right + 2 >= point.x &&
						pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).top - 2 <= point.y && pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).bottom + 2 >= point.y ) {

							M_Rect.top = pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).top - pDoc -> RRightT_Thickness.GetAt ( RRightT_Number ) / 2 - 2 ;
							M_Rect.bottom = pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).bottom + pDoc -> RRightT_Thickness.GetAt ( RRightT_Number ) / 2 + 2 ;
							M_Rect.left = pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).left - pDoc -> RRightT_Thickness.GetAt ( RRightT_Number ) / 2 - 2 ;
							M_Rect.right = pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).right + pDoc -> RRightT_Thickness.GetAt ( RRightT_Number ) / 2 + 2 ;

							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("RRightT") ) ; M_Number = RRightT_Number ;
							M_IsDraw = 'o' ; P_IsContinue = 'x' ; Text_IsChange = 'x' ;
							Invalidate () ; Find = 'o' ; break ;
					}
					RRightT_Number-- ;
				}

				// 왼쪽 -> 오른쪽 삼각형 객체인 경우
				else if ( pDoc -> What.GetAt (i-1) == _T ("LTRT") ) {
					if ( pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).left - 2 <= point.x && pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).right + 2 >= point.x &&
						pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).top - 2 <= point.y && pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).bottom + 2 >= point.y ) {

							M_Rect.top = pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).top - pDoc -> LTRT_Thickness.GetAt ( LTRT_Number ) / 2 - 2 ;
							M_Rect.bottom = pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).bottom + pDoc -> LTRT_Thickness.GetAt ( LTRT_Number ) / 2 + 2 ;
							M_Rect.left = pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).left - pDoc -> LTRT_Thickness.GetAt ( LTRT_Number ) / 2 - 2 ;
							M_Rect.right = pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).right + pDoc -> LTRT_Thickness.GetAt ( LTRT_Number ) / 2 + 2 ;

							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("LTRT") ) ; M_Number = LTRT_Number ;
							M_IsDraw = 'o' ; P_IsContinue = 'x' ; Text_IsChange = 'x' ;
							Invalidate () ; Find = 'o' ; break ;
					}
					LTRT_Number-- ;
				}

				// 오른쪽 -> 왼쪽 삼각형 객체인 경우
				else if ( pDoc -> What.GetAt (i-1) == _T ("RTLT") ) {
					if ( pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).left - 2 <= point.x && pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).right + 2 >= point.x &&
						pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).top - 2 <= point.y && pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).bottom + 2 >= point.y ) {

							M_Rect.top = pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).top - pDoc -> RTLT_Thickness.GetAt ( RTLT_Number ) / 2 - 2 ;
							M_Rect.bottom = pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).bottom + pDoc -> RTLT_Thickness.GetAt ( RTLT_Number ) / 2 + 2 ;
							M_Rect.left = pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).left - pDoc -> RTLT_Thickness.GetAt ( RTLT_Number ) / 2 - 2 ;
							M_Rect.right = pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).right + pDoc -> RTLT_Thickness.GetAt ( RTLT_Number ) / 2 + 2 ;

							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("RTLT") ) ; M_Number = RTLT_Number ;
							M_IsDraw = 'o' ; P_IsContinue = 'x' ; Text_IsChange = 'x' ;
							Invalidate () ; Find = 'o' ; break ;
					}
					RTLT_Number-- ;
				}
				else if ( pDoc -> What.GetAt (i-1) == _T ("Text") ) {
					if ( pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.left - 2 <= point.x && pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.right + 2 >= point.x &&
						pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.top - 2 <= point.y && pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.bottom + 2 >= point.y ) {

							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("Text") ) ; M_Number = Text_Number ;
							M_IsDraw = 'o' ; P_IsContinue = 'x' ;
							Invalidate () ; Text_IsChange = 'o' ; Find = 'o' ; break ;
					}
					Text_Number-- ;
				}
				else if ( pDoc -> What.GetAt (i-1) == _T ("G") ) {
					if ( pDoc -> G_Group.GetAt ( G_Number ).GroupBox.left - 2 <= point.x && pDoc -> G_Group.GetAt ( G_Number ).GroupBox.right + 2 >= point.x &&
						pDoc -> G_Group.GetAt ( G_Number ).GroupBox.top - 2 <= point.y && pDoc -> G_Group.GetAt ( G_Number ).GroupBox.bottom + 2 >= point.y ) {

							M_Rect.top = pDoc -> G_Group.GetAt ( G_Number ).GroupBox.top - 2 ;
							M_Rect.bottom = pDoc -> G_Group.GetAt ( G_Number ).GroupBox.bottom + 2 ;
							M_Rect.left = pDoc -> G_Group.GetAt ( G_Number ).GroupBox.left - 2 ;
							M_Rect.right = pDoc -> G_Group.GetAt ( G_Number ).GroupBox.right + 2 ;

							M_IsSelect = 'o' ;	M_Start.x = point.x ; M_Start.y = point.y ;
							M_What.Format ( _T ("G") ) ; M_Number = G_Number ;
							M_IsDraw = 'o' ; P_IsContinue = 'x' ; Text_IsChange = 'x' ;
							Invalidate () ; Find = 'o' ; break ;
					}
					G_Number-- ;
				}

			}
			if ( Find == 'x') {
				P_IsContinue = 'x' ;
				P_Insert.Poly_point.RemoveAll () ;
				M_IsDraw = 'x' ;
				Invalidate () ;

				m_IsSelectGroup = 'o' ;
				G_Include.top = point.y ; G_Include.bottom = point.y ;
				G_Include.left = point.x ; G_Include.right = point.x ;
				G_Start = point ;
			}
		}
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

		if ( m_IsThickness == 'o' )
			L_Insert.Thickness = m_Thickness ;
		else
			L_Insert.Thickness = 1 ;

		if ( m_IsLinePattern == 'o' )
			L_Insert.Pattern = m_LinePattern ;
		else
			L_Insert.Pattern = 1 ;

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
		
		m_PSkeleton = 'x' ;
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
	// PolyLine의 Skeleton 하나를 변경하는 경우
	else if ( M_ChangeLineOnePoint == 'o' ) {
		if ( M_IsChangeLineStart == 'o' ) {
			pDoc -> L_Line.GetAt ( M_Number ).Start.x = point.x ;
			pDoc -> L_Line.GetAt ( M_Number ).Start.y = point.y ;
		}
		else {
			pDoc -> L_Line.GetAt ( M_Number ).Last.x = point.x ;
			pDoc -> L_Line.GetAt ( M_Number ).Last.y = point.y ;
		}

		Invalidate () ;
	}
	// 상자 객체를 변경시키는 경우
	else if ( M_ChangeRectSize == 'o' ) {
		// 상자의 각 4 꼭지점을 클릭하여 변경하는 경우
		if ( M_IsChangeRectSide == 'o' ) {
			// 북서쪽 Skeleton으로 변경하는 경우
			if ( M_IsChangeRectNW == 'o' ) {
				if ( M_Rect.bottom >= point.y && M_Rect.right >= point.x ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> R_Rec.GetAt ( M_Number ).right )
						M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).right ;
					if ( M_ChangeRect.bottom != pDoc -> R_Rec.GetAt ( M_Number ).bottom )
						M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;
				}
				else if ( M_Rect.bottom <= point.y && M_Rect.right >= point.x ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.top != pDoc -> R_Rec.GetAt ( M_Number ).bottom )
						M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;
					if ( M_ChangeRect.right != pDoc -> R_Rec.GetAt ( M_Number ).right )
						M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).right ;
				}
				else if ( M_Rect.bottom >= point.y && M_Rect.right <= point.x ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> R_Rec.GetAt ( M_Number ).right )
						M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).right ;
					if ( M_ChangeRect.bottom != pDoc -> R_Rec.GetAt ( M_Number ).bottom )
						M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;
				}
				else {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.top != pDoc -> R_Rec.GetAt ( M_Number ).bottom )
						M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;
					if ( M_ChangeRect.left != pDoc -> R_Rec.GetAt ( M_Number ).right )
						M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).right ;
				}
			}
			// 북동쪽 Skeleton으로 변경하는 경우
			else if ( M_IsChangeRectNE == 'o' ) {
				if ( M_Rect.bottom >= point.y && M_Rect.left <= point.x ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> R_Rec.GetAt ( M_Number ).left )
						M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.bottom != pDoc -> R_Rec.GetAt ( M_Number ).bottom )
						M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;
				}
				else if ( M_Rect.bottom <= point.y && M_Rect.left <= point.x ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.top != pDoc -> R_Rec.GetAt ( M_Number ).bottom )
						M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;
					if ( M_ChangeRect.left != pDoc -> R_Rec.GetAt ( M_Number ).left )
						M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).left ;
				}
				else if ( M_Rect.bottom >= point.y && M_Rect.left >= point.x ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> R_Rec.GetAt ( M_Number ).left )
						M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.bottom != pDoc -> R_Rec.GetAt ( M_Number ).bottom )
						M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;
				}
				else {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> R_Rec.GetAt ( M_Number ).left )
						M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.top != pDoc -> R_Rec.GetAt ( M_Number ).bottom )
						M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;
				}
			}
			// 남서쪽 Skeleton으로 변경하는 경우
			else if ( M_IsChangeRectSW == 'o' ) {
				if ( M_Rect.top <= point.y && M_Rect.right >= point.x ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> R_Rec.GetAt ( M_Number ).right )
						M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).right ;
					if ( M_ChangeRect.top != pDoc -> R_Rec.GetAt ( M_Number ).top )
						M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				}
				else if ( M_Rect.top <= point.y && M_Rect.right <= point.x ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> R_Rec.GetAt ( M_Number ).right )
						M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).right ;
					if ( M_ChangeRect.top != pDoc -> R_Rec.GetAt ( M_Number ).top )
						M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				}
				else if ( M_Rect.top >= point.y && M_Rect.right >= point.x ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> R_Rec.GetAt ( M_Number ).right )
						M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).right ;
					if ( M_ChangeRect.bottom != pDoc -> R_Rec.GetAt ( M_Number ).top )
						M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				}
				else {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> R_Rec.GetAt ( M_Number ).right )
						M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).right ;
					if ( M_ChangeRect.bottom != pDoc -> R_Rec.GetAt ( M_Number ).top )
						M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				}
			}
			// 남동쪽 Skeleton으로 변경하는 경우
			else {
				if ( M_Rect.top <= point.y && M_Rect.left <= point.x ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> R_Rec.GetAt ( M_Number ).left )
						M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.top != pDoc -> R_Rec.GetAt ( M_Number ).top )
						M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				}
				else if ( M_Rect.top <= point.y && M_Rect.left >= point.x ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> R_Rec.GetAt ( M_Number ).left )
						M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.top != pDoc -> R_Rec.GetAt ( M_Number ).top )
						M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				}
				else if ( M_Rect.top >= point.y && M_Rect.left <= point.x ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> R_Rec.GetAt ( M_Number ).left )
						M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.bottom != pDoc -> R_Rec.GetAt ( M_Number ).top )
						M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				}
				else {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> R_Rec.GetAt ( M_Number ).left )
						M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.bottom != pDoc -> R_Rec.GetAt ( M_Number ).top )
						M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				}
			}
		}
		// 상자의 4 꼭지점이 아닌 경우
		else {
			// 위쪽 방향으로만 변경하는 경우
			if ( M_IsChangeRectVerticalTop == 'o' ) {
				
				if ( point.y <= M_Rect.bottom ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					if ( M_ChangeRect.bottom != pDoc -> R_Rec.GetAt ( M_Number ).bottom )
						M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;
				}
				else {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					if ( M_ChangeRect.top != pDoc -> R_Rec.GetAt ( M_Number ).bottom )
						M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).bottom ;
				}
			}
			// 아래쪽 방향으로만 변경하는 경우
			else if ( M_IsChangeRectVerticalBottom == 'o' ) {
				
				if ( point.y >= M_Rect.top ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					if ( M_ChangeRect.top != pDoc -> R_Rec.GetAt ( M_Number ).top )
						M_ChangeRect.top = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				}
				else {
					M_ChangeRect.top += point.y - M_Start.y ;
					if ( M_ChangeRect.bottom != pDoc -> R_Rec.GetAt ( M_Number ).top )
						M_ChangeRect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).top ;
				}
			}
			// 왼쪽 방향으로만 변경하는 경우
			else if ( M_IsChangeRectWidthLeft == 'o' ) {
				
				if ( point.x <= M_Rect.right ) {
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> R_Rec.GetAt ( M_Number ).right )
						M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).right ;
				}
				else {
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> R_Rec.GetAt ( M_Number ).right )
						M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).right ;
				}
			}
			// 오른쪽 방향으로만 변경하는 경우
			else {

				if ( point.x >= M_Rect.left ) {
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> R_Rec.GetAt ( M_Number ).left )
						M_ChangeRect.left = pDoc -> R_Rec.GetAt ( M_Number ).left ;
				}
				else {
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> R_Rec.GetAt ( M_Number ).left )
						M_ChangeRect.right = pDoc -> R_Rec.GetAt ( M_Number ).left ;
				}
			}
		}

		M_Start.x = point.x ;
		M_Start.y = point.y ;

		Invalidate () ;

	}
	// 원의 크기를 변경시키는 경우
	else if ( M_ChangeEllipseSize == 'o' ) {
		// 원을 둘러싼 상자의 각 4 꼭지점을 클릭하여 변경하는 경우
		if ( M_IsChangeEllipseSide == 'o' ) {
			// 북서쪽 Skeleton으로 변경하는 경우
			if ( M_IsChangeEllipseNW == 'o' ) {
				if ( M_Rect.bottom >= point.y && M_Rect.right >= point.x ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> E_Ellipse.GetAt ( M_Number ).right )
						M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;
					if ( M_ChangeRect.bottom != pDoc -> E_Ellipse.GetAt ( M_Number ).bottom )
						M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;
				}
				else if ( M_Rect.bottom <= point.y && M_Rect.right >= point.x ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.top != pDoc -> E_Ellipse.GetAt ( M_Number ).bottom )
						M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;
					if ( M_ChangeRect.right != pDoc -> E_Ellipse.GetAt ( M_Number ).right )
						M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;
				}
				else if ( M_Rect.bottom >= point.y && M_Rect.right <= point.x ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> E_Ellipse.GetAt ( M_Number ).right )
						M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;
					if ( M_ChangeRect.bottom != pDoc -> E_Ellipse.GetAt ( M_Number ).bottom )
						M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;
				}
				else {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.top != pDoc -> E_Ellipse.GetAt ( M_Number ).bottom )
						M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;
					if ( M_ChangeRect.left != pDoc -> E_Ellipse.GetAt ( M_Number ).right )
						M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;
				}
			}
			// 북동쪽 Skeleton으로 변경하는 경우
			else if ( M_IsChangeEllipseNE == 'o' ) {
				if ( M_Rect.bottom >= point.y && M_Rect.left <= point.x ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> E_Ellipse.GetAt ( M_Number ).left )
						M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.bottom != pDoc -> E_Ellipse.GetAt ( M_Number ).bottom )
						M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;
				}
				else if ( M_Rect.bottom <= point.y && M_Rect.left <= point.x ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.top != pDoc -> E_Ellipse.GetAt ( M_Number ).bottom )
						M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;
					if ( M_ChangeRect.left != pDoc -> E_Ellipse.GetAt ( M_Number ).left )
						M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
				}
				else if ( M_Rect.bottom >= point.y && M_Rect.left >= point.x ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> E_Ellipse.GetAt ( M_Number ).left )
						M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.bottom != pDoc -> E_Ellipse.GetAt ( M_Number ).bottom )
						M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;
				}
				else {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> E_Ellipse.GetAt ( M_Number ).left )
						M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.top != pDoc -> E_Ellipse.GetAt ( M_Number ).bottom )
						M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;
				}
			}
			// 남서쪽 Skeleton으로 변경하는 경우
			else if ( M_IsChangeEllipseSW == 'o' ) {
				if ( M_Rect.top <= point.y && M_Rect.right >= point.x ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> E_Ellipse.GetAt ( M_Number ).right )
						M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;
					if ( M_ChangeRect.top != pDoc -> E_Ellipse.GetAt ( M_Number ).top )
						M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				}
				else if ( M_Rect.top <= point.y && M_Rect.right <= point.x ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> E_Ellipse.GetAt ( M_Number ).right )
						M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;
					if ( M_ChangeRect.top != pDoc -> E_Ellipse.GetAt ( M_Number ).top )
						M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				}
				else if ( M_Rect.top >= point.y && M_Rect.right >= point.x ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> E_Ellipse.GetAt ( M_Number ).right )
						M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;
					if ( M_ChangeRect.bottom != pDoc -> E_Ellipse.GetAt ( M_Number ).top )
						M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				}
				else {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> E_Ellipse.GetAt ( M_Number ).right )
						M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;
					if ( M_ChangeRect.bottom != pDoc -> E_Ellipse.GetAt ( M_Number ).top )
						M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				}
			}
			// 남동쪽 Skeleton으로 변경하는 경우
			else {
				if ( M_Rect.top <= point.y && M_Rect.left <= point.x ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> E_Ellipse.GetAt ( M_Number ).left )
						M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.top != pDoc -> E_Ellipse.GetAt ( M_Number ).top )
						M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				}
				else if ( M_Rect.top <= point.y && M_Rect.left >= point.x ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> E_Ellipse.GetAt ( M_Number ).left )
						M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.top != pDoc -> E_Ellipse.GetAt ( M_Number ).top )
						M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				}
				else if ( M_Rect.top >= point.y && M_Rect.left <= point.x ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> E_Ellipse.GetAt ( M_Number ).left )
						M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.bottom != pDoc -> E_Ellipse.GetAt ( M_Number ).top )
						M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				}
				else {
					M_ChangeRect.top += point.y - M_Start.y ;
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> E_Ellipse.GetAt ( M_Number ).left )
						M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
					if ( M_ChangeRect.bottom != pDoc -> E_Ellipse.GetAt ( M_Number ).top )
						M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				}
			}
		}
		// 원을 둘러싼 상자의 4 꼭지점이 아닌 경우
		else {
			// 위쪽 방향으로만 변경하는 경우
			if ( M_IsChangeEllipseVerticalTop == 'o' ) {
				
				if ( point.y <= M_Rect.bottom ) {
					M_ChangeRect.top += point.y - M_Start.y ;
					if ( M_ChangeRect.bottom != pDoc -> E_Ellipse.GetAt ( M_Number ).bottom )
						M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;
				}
				else {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					if ( M_ChangeRect.top != pDoc -> E_Ellipse.GetAt ( M_Number ).bottom )
						M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom ;
				}
			}
			// 아래쪽 방향으로만 변경하는 경우
			else if ( M_IsChangeEllipseVerticalBottom == 'o' ) {
				
				if ( point.y >= M_Rect.top ) {
					M_ChangeRect.bottom += point.y - M_Start.y ;
					if ( M_ChangeRect.top != pDoc -> E_Ellipse.GetAt ( M_Number ).top )
						M_ChangeRect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				}
				else {
					M_ChangeRect.top += point.y - M_Start.y ;
					if ( M_ChangeRect.bottom != pDoc -> E_Ellipse.GetAt ( M_Number ).top )
						M_ChangeRect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).top ;
				}
			}
			// 왼쪽 방향으로만 변경하는 경우
			else if ( M_IsChangeEllipseWidthLeft == 'o' ) {
				
				if ( point.x <= M_Rect.right ) {
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> E_Ellipse.GetAt ( M_Number ).right )
						M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;
				}
				else {
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> E_Ellipse.GetAt ( M_Number ).right )
						M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).right ;
				}
			}
			// 오른쪽 방향으로만 변경하는 경우
			else {

				if ( point.x >= M_Rect.left ) {
					M_ChangeRect.right += point.x - M_Start.x ;
					if ( M_ChangeRect.left != pDoc -> E_Ellipse.GetAt ( M_Number ).left )
						M_ChangeRect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
				}
				else {
					M_ChangeRect.left += point.x - M_Start.x ;
					if ( M_ChangeRect.right != pDoc -> E_Ellipse.GetAt ( M_Number ).left )
						M_ChangeRect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).left ;
				}
			}
		}

		M_Start.x = point.x ;
		M_Start.y = point.y ;

		Invalidate () ;

	}
	// 객체를 이동시키는 경우
	else if ( M_IsSelect == 'o' ) {
		M_Rect.top += point.y - M_Start.y ;
		M_Rect.bottom += point.y - M_Start.y ;
		M_Rect.left += point.x - M_Start.x ;
		M_Rect.right += point.x - M_Start.x ;

		// 선을 이동하는 경우
		if ( M_What == _T ("L") ) {
			pDoc -> L_Line.GetAt ( M_Number ).Start.x += point.x - M_Start.x ;
			pDoc -> L_Line.GetAt ( M_Number ).Last.x += point.x - M_Start.x ;
			pDoc -> L_Line.GetAt ( M_Number ).Start.y += point.y - M_Start.y ;
			pDoc -> L_Line.GetAt ( M_Number ).Last.y += point.y - M_Start.y ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// 상자를 이동하는 경우
		else if ( M_What == _T ("R") ) {
			pDoc -> R_Rec.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> R_Rec.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> R_Rec.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> R_Rec.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// PolyLine을 이동하는 경우
		else if ( M_What == _T ("P") ) {
			for ( int i = 0 ; i < pDoc -> P_Poly.GetAt ( M_Number ).Poly_point.GetCount () ; i++ ) {
				pDoc -> P_Poly.GetAt ( M_Number).Poly_point.GetAt (i).x += point.x - M_Start.x ;
				pDoc -> P_Poly.GetAt ( M_Number).Poly_point.GetAt (i).y += point.y - M_Start.y ;
			}

			if ( M_Start.x <= point.x ) {
				M_PMax_x += point.x - M_Start.x ;
				M_PMin_x -= M_Start.x - point.x ;
			}
			else {
				M_PMax_x -= M_Start.x - point.x ;
				M_PMin_x += point.x - M_Start.x ;
			}

			if ( M_Start.y <= point.y ) {
				M_PMax_y += point.y - M_Start.y ;
				M_PMin_y -= M_Start.y - point.y ;
			}
			else {
				M_PMax_y -= M_Start.y - point.y ;
				M_PMin_y += point.y - M_Start.y ;
			}

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// 원을 이동하는 경우
		else if ( M_What == _T ("E") ) {
			pDoc -> E_Ellipse.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> E_Ellipse.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> E_Ellipse.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> E_Ellipse.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// 세모를 이동하는 경우
		else if ( M_What == _T ("T") ) {
			pDoc -> T_Triangle.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> T_Triangle.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> T_Triangle.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> T_Triangle.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// 역 삼각형을 이동하는 경우
		else if ( M_What == _T ("RT") ) {
			pDoc -> RT_Triangle.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> RT_Triangle.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> RT_Triangle.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> RT_Triangle.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// 직각 삼각형을 이동하는 경우
		else if ( M_What == _T ("RightT") ) {
			pDoc -> RightT_Triangle.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> RightT_Triangle.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> RightT_Triangle.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> RightT_Triangle.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// 역 직각 삼각형을 이동하는 경우
		else if ( M_What == _T ("RRightT") ) {
			pDoc -> RRightT_Triangle.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> RRightT_Triangle.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> RRightT_Triangle.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> RRightT_Triangle.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// 왼쪽 -> 오른쪽 삼각형을 이동하는 경우
		else if ( M_What == _T ("LTRT") ) {
			pDoc -> LTRT_Triangle.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> LTRT_Triangle.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> LTRT_Triangle.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> LTRT_Triangle.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// 오른쪽 -> 왼쪽 삼각형을 이동하는 경우
		else if ( M_What == _T ("RTLT") ) {
			pDoc -> RTLT_Triangle.GetAt ( M_Number ).top += point.y - M_Start.y ;
			pDoc -> RTLT_Triangle.GetAt ( M_Number ).bottom += point.y - M_Start.y ;
			pDoc -> RTLT_Triangle.GetAt ( M_Number ).left += point.x - M_Start.x ;
			pDoc -> RTLT_Triangle.GetAt ( M_Number ).right += point.x - M_Start.x ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// 텍스트를 이동하는 경우
		else if ( M_What == _T ("Text") ) {
			pDoc -> Text_Text.GetAt ( M_Number ).Text_Rect.top += point.y - M_Start.y ;
			pDoc -> Text_Text.GetAt ( M_Number ).Text_Rect.bottom += point.y - M_Start.y ;
			pDoc -> Text_Text.GetAt ( M_Number ).Text_Rect.left += point.x - M_Start.x ;
			pDoc -> Text_Text.GetAt ( M_Number ).Text_Rect.right += point.x - M_Start.x ;

			pDoc -> Text_Text.GetAt ( M_Number ).Location.x += point.x - M_Start.x ;
			pDoc -> Text_Text.GetAt ( M_Number ).Location.y += point.y - M_Start.y ;

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}
		// 그룹화를 이동하는 경우
		else if ( M_What == _T ("G") ) {

			for ( int i = 0 ; i < pDoc -> G_Group.GetAt (M_Number).Line.GetCount () ; i++ ) {
				pDoc -> G_Group.GetAt (M_Number).Line.GetAt (i).Start.x += point.x - M_Start.x ;
				pDoc -> G_Group.GetAt (M_Number).Line.GetAt (i).Start.y += point.y - M_Start.y ;
				pDoc -> G_Group.GetAt (M_Number).Line.GetAt (i).Last.x += point.x - M_Start.x ;
				pDoc -> G_Group.GetAt (M_Number).Line.GetAt (i).Last.y += point.y - M_Start.y ;
			}
			for ( int i = 0 ; i < pDoc -> G_Group.GetAt (M_Number).Poly.GetCount () ; i++ ) {
				for ( int j = 0 ; j < pDoc -> G_Group.GetAt (M_Number).Poly.GetAt (i).Poly_point.GetCount () ; j++ ) {
					pDoc -> G_Group.GetAt (M_Number).Poly.GetAt (i).Poly_point.GetAt (j).x += point.x - M_Start.x ;
					pDoc -> G_Group.GetAt (M_Number).Poly.GetAt (i).Poly_point.GetAt (j).y += point.y - M_Start.y ;
				}
			}
			for ( int i = 0 ; i < pDoc -> G_Group.GetAt (M_Number).Rect.GetCount () ; i++ ) {
				pDoc -> G_Group.GetAt (M_Number).Rect.GetAt (i).left += point.x - M_Start.x ;
				pDoc -> G_Group.GetAt (M_Number).Rect.GetAt (i).top += point.y - M_Start.y ;
				pDoc -> G_Group.GetAt (M_Number).Rect.GetAt (i).right += point.x - M_Start.x ;
				pDoc -> G_Group.GetAt (M_Number).Rect.GetAt (i).bottom += point.y - M_Start.y ;
			}
			for ( int i = 0 ; i < pDoc -> G_Group.GetAt (M_Number).Ellipse.GetCount () ; i++ ) {
				pDoc -> G_Group.GetAt (M_Number).Ellipse.GetAt (i).left += point.x - M_Start.x ;
				pDoc -> G_Group.GetAt (M_Number).Ellipse.GetAt (i).top += point.y - M_Start.y ;
				pDoc -> G_Group.GetAt (M_Number).Ellipse.GetAt (i).right += point.x - M_Start.x ;
				pDoc -> G_Group.GetAt (M_Number).Ellipse.GetAt (i).bottom += point.y - M_Start.y ;
			}
			for ( int i = 0 ; i < pDoc -> G_Group.GetAt (M_Number).Text.GetCount () ; i++ ) {
				pDoc -> G_Group.GetAt (M_Number).Text.GetAt (i).Text_Rect.left += point.x - M_Start.x ;
				pDoc -> G_Group.GetAt (M_Number).Text.GetAt (i).Text_Rect.top += point.y - M_Start.y ;
				pDoc -> G_Group.GetAt (M_Number).Text.GetAt (i).Text_Rect.right += point.x - M_Start.x ;
				pDoc -> G_Group.GetAt (M_Number).Text.GetAt (i).Text_Rect.bottom += point.y - M_Start.y ;

				pDoc -> G_Group.GetAt (M_Number).Text.GetAt (i).Location.x += point.x - M_Start.x ;
				pDoc -> G_Group.GetAt (M_Number).Text.GetAt (i).Location.y += point.y - M_Start.y ;
			}
			for ( int i = 0 ; i < pDoc -> G_Group.GetAt (M_Number).Index.GetCount () ; i++ ) {
				for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Line.GetCount () ; j++ ) {
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Line.GetAt (j).Start.x += point.x - M_Start.x ;
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Line.GetAt (j).Start.y += point.y - M_Start.y ;
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Line.GetAt (j).Last.x += point.x - M_Start.x ;
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Line.GetAt (j).Last.y += point.y - M_Start.y ;
				}
				for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Ellipse.GetCount () ; j++ ) {
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Ellipse.GetAt (j).left += point.x - M_Start.x ;
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Ellipse.GetAt (j).top += point.y - M_Start.y ;
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Ellipse.GetAt (j).right += point.x - M_Start.x ;
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Ellipse.GetAt (j).bottom += point.y - M_Start.y ;
				}
				for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Rect.GetCount () ; j++ ) {
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Rect.GetAt (j).left += point.x - M_Start.x ;
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Rect.GetAt (j).top += point.y - M_Start.y ;
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Rect.GetAt (j).right += point.x - M_Start.x ;
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Rect.GetAt (j).bottom += point.y - M_Start.y ;
				}
				for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Text.GetCount () ; j++ ) {
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Text.GetAt (j).Text_Rect.left += point.x - M_Start.x ;
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Text.GetAt (j).Text_Rect.top += point.y - M_Start.y ;
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Text.GetAt (j).Text_Rect.right += point.x - M_Start.x ;
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Text.GetAt (j).Text_Rect.bottom += point.y - M_Start.y ;
				}
				for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Poly.GetCount () ; j++ ) {
					for ( int k = 0 ; k < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Poly.GetAt (j).Poly_point.GetCount () ; k++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Poly.GetAt (j).Poly_point.GetAt (k).x += point.x - M_Start.x ;
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt (M_Number).Index.GetAt (i) ).Poly.GetAt (j).Poly_point.GetAt (k).y += point.y - M_Start.y ;
					}
				}
			}

			M_Start.x = point.x ;
			M_Start.y = point.y ;
		}

		Invalidate () ;
	}
	else if ( m_IsSelectGroup == 'o' && G_IsMakeGroup == 'x' ) {
		G_Include.right += point.x - G_Start.x ;
		G_Include.bottom += point.y - G_Start.y ;

		G_Start = point ;
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

	// 선의 Skeleton 하나를 변경하다 클릭을 땐 경우
	if ( M_ChangeLineOnePoint == 'o' ) {
		if ( M_IsChangeLineStart == 'o' ) {
			pDoc -> L_Line.GetAt ( M_Number ).Start.x = point.x ;
			pDoc -> L_Line.GetAt ( M_Number ).Start.y = point.y ;
			
			if ( pDoc -> L_Line.GetAt ( M_Number ).Start.x >= pDoc -> L_Line.GetAt ( M_Number ).Last.x ) {
				M_Rect.left = pDoc -> L_Line.GetAt ( M_Number ).Last.x - pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
				M_Rect.right = pDoc -> L_Line.GetAt ( M_Number ).Start.x + pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
			}
			else {
				M_Rect.left = pDoc -> L_Line.GetAt ( M_Number ).Start.x - pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
				M_Rect.right = pDoc -> L_Line.GetAt ( M_Number ).Last.x + pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
			}

			if ( pDoc -> L_Line.GetAt ( M_Number ).Start.y >= pDoc -> L_Line.GetAt ( M_Number ).Last.y ) {
				M_Rect.top = pDoc -> L_Line.GetAt ( M_Number ).Last.y - pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
				M_Rect.bottom = pDoc -> L_Line.GetAt ( M_Number ).Start.y + pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
			}
			else {
				M_Rect.top = pDoc -> L_Line.GetAt ( M_Number ).Start.y - pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
				M_Rect.bottom = pDoc -> L_Line.GetAt ( M_Number ).Last.y + pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
			}
		}
		else {
			pDoc -> L_Line.GetAt ( M_Number ).Last.x = point.x ;
			pDoc -> L_Line.GetAt ( M_Number ).Last.y = point.y ;

			if ( pDoc -> L_Line.GetAt ( M_Number ).Start.x >= pDoc -> L_Line.GetAt ( M_Number ).Last.x ) {
				M_Rect.left = pDoc -> L_Line.GetAt ( M_Number ).Last.x - pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
				M_Rect.right = pDoc -> L_Line.GetAt ( M_Number ).Start.x + pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
			}
			else {
				M_Rect.left = pDoc -> L_Line.GetAt ( M_Number ).Start.x - pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
				M_Rect.right = pDoc -> L_Line.GetAt ( M_Number ).Last.x + pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
			}

			if ( pDoc -> L_Line.GetAt ( M_Number ).Start.y >= pDoc -> L_Line.GetAt ( M_Number ).Last.y ) {
				M_Rect.top = pDoc -> L_Line.GetAt ( M_Number ).Last.y - pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
				M_Rect.bottom = pDoc -> L_Line.GetAt ( M_Number ).Start.y + pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
			}
			else {
				M_Rect.top = pDoc -> L_Line.GetAt ( M_Number ).Start.y - pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
				M_Rect.bottom = pDoc -> L_Line.GetAt ( M_Number ).Last.y + pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
			}
		}
		M_ChangeLineOnePoint = 'x' ;

		Invalidate () ;
	}
	// PolyLine을 변경하다 클릭을 뗀 경우
	else if ( M_IsDraw == 'o' && P_IsContinue == 'o' && P_CanMove == 'o' ) {
		// 만약 같은 좌표에 클릭, 땠을 경우 그리기 취소
		if ( P_IsMove == 'x' ) {
			if ( m_PSkeleton == 'o' ) {
				P_CanMove = 'x' ; P_IsStart = 'x' ;
				if ( PSkeleton + 1 == P_CurrentPoint && P_IsStart == 'x' && P_ChangeSkeleton == 0 )
					P_CurrentPoint-- ;
			}
			else {
				P_CanMove = 'x' ; P_IsStart = 'x' ;
				P_Insert.Poly_point.RemoveAll () ;
				P_IsContinue = 'x' ;
			}
			Invalidate () ;
		}
		// 같은 좌표에 클릭, 땐 경우가 아니라면 그리기 모드
		else {
			m_PSkeleton = 'o' ;
			// 만약 마지막 Skeleton을 변경한 경우
			if ( P_IsStart == 'x' && P_ChangeSkeleton == 0 ) {
				P_Insert.Poly_point.SetAt ( P_CurrentPoint, point ) ;
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( P_CurrentPoint, point ) ;

				if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( P_CurrentPoint ).x + pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 >= M_Rect.right )
					M_Rect.right = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( P_CurrentPoint).x + pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;
				
				else if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( P_CurrentPoint ).x - pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 <= M_Rect.left )
					M_Rect.left = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( P_CurrentPoint ).x - pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;

				if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( P_CurrentPoint ).y + pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 >= M_Rect.bottom )
					M_Rect.bottom = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( P_CurrentPoint ).y + pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;
				else if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( P_CurrentPoint ).y - pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 <= M_Rect.top )
					M_Rect.top = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( P_CurrentPoint ).y - pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;

				Invalidate () ;
			}
			// 만약 첫번째 Skeleton을 변경한 경우
			else if ( P_IsStart == 'o' ) {
				P_Insert.Poly_point.SetAt ( 0, point ) ;
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( 0, point ) ;
				P_IsStart = 'x' ;
				P_IsSkeletonStart = 'x' ;

				if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( 0 ).x + pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 >= M_Rect.right )
					M_Rect.right = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( 0 ).x + pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;
				else if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( 0 ).x - pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 <= M_Rect.left )
					M_Rect.left = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( 0 ).x - pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;

				if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( 0 ).y + pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 >= M_Rect.bottom )
					M_Rect.bottom = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( 0 ).y + pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;
				else if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( 0 ).y - pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 <= M_Rect.top )
					M_Rect.top = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt ( 0 ).y - pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;

				Invalidate () ;

			}
			// 만약 첫번째, 마지막 Skeleton외 다른 Skeleton을 변경한 경우
			else if ( P_ChangeSkeleton > 0 ) {
				P_Insert.Poly_point.SetAt ( P_ChangeSkeleton, point ) ;
				pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.SetAt ( P_ChangeSkeleton, point ) ;

				int Max_x = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (0).x ;
				int Min_x = Max_x ;
				int Max_y = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (0).y ;
				int Min_y = Max_y ;

				for ( int i = 1 ; i < pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetCount () ; i++ ) {
					if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).x > Max_x )
						Max_x = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).x ;
					else if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).x < Min_x )
						Min_x = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).x ;

					if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).y > Max_y )
						Max_y = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).y ;
					else if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).y < Min_y )
						Min_y = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).y ;
				}

				M_Rect.top = Min_y - pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;
				M_Rect.left = Min_x - pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;
				M_Rect.bottom = Max_y + pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;
				M_Rect.right = Max_x + pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;
				
				Invalidate () ;
				P_ChangeSkeleton = 0 ;
			}
			P_CanMove = 'x' ;
			P_IsMove = 'x' ;
			M_IsSelect = 'x' ;
		}
	}
	// 상자를 변경하다 클릭을 땐 경우
	else if ( M_IsDraw == 'o' && M_IsRectSelect == 'o' && M_ChangeRectSize == 'o' ) {
		M_Rect.top = pDoc -> R_Rec.GetAt ( M_Number ).top = M_ChangeRect.top ;
		M_Rect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).bottom = M_ChangeRect.bottom ;
		M_Rect.left = pDoc -> R_Rec.GetAt ( M_Number ).left = M_ChangeRect.left ;
		M_Rect.right = pDoc -> R_Rec.GetAt ( M_Number ).right = M_ChangeRect.right ;

		M_Rect.top -= pDoc -> R_Thickness.GetAt ( M_Number ) / 2 + 2 ;
		M_Rect.bottom += pDoc -> R_Thickness.GetAt ( M_Number ) / 2 + 2 ;
		M_Rect.left -= pDoc -> R_Thickness.GetAt ( M_Number ) / 2 + 2 ;
		M_Rect.right += pDoc -> R_Thickness.GetAt ( M_Number ) / 2 + 2 ;

		M_ChangeRectSize = 'x' ;
		M_IsChangeRectSide = 'x' ;
		M_IsChangeRectVerticalTop = 'x' ;
		M_IsChangeRectVerticalBottom = 'x' ;
		M_IsChangeRectNW = 'x' ;
		M_IsChangeRectNE = 'x' ;
		M_IsChangeRectSW = 'x' ;
		M_IsChangeRectSE = 'x' ;
		M_IsChangeRectWidthLeft = 'x' ;
		M_IsChangeRectWidthRight = 'x' ;

		Invalidate () ;
	}
	// 원을 변경하다 클릭을 땐 경우
	else if ( M_IsDraw == 'o' && M_IsEllipseSelect == 'o' && M_ChangeEllipseSize == 'o' ) {
		M_Rect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).top = M_ChangeRect.top ;
		M_Rect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom = M_ChangeRect.bottom ;
		M_Rect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).left = M_ChangeRect.left ;
		M_Rect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).right = M_ChangeRect.right ;

		M_Rect.top -= pDoc -> E_Thickness.GetAt ( M_Number ) / 2 + 2 ;
		M_Rect.bottom += pDoc -> E_Thickness.GetAt ( M_Number ) / 2 + 2 ;
		M_Rect.left -= pDoc -> E_Thickness.GetAt ( M_Number ) / 2 + 2 ;
		M_Rect.right += pDoc -> E_Thickness.GetAt ( M_Number ) / 2 + 2 ;

		M_ChangeEllipseSize = 'x' ;
		M_IsChangeEllipseSide = 'x' ;
		M_IsChangeEllipseVerticalTop = 'x' ;
		M_IsChangeEllipseVerticalBottom = 'x' ;
		M_IsChangeEllipseNW = 'x' ;
		M_IsChangeEllipseNE = 'x' ;
		M_IsChangeEllipseSW = 'x' ;
		M_IsChangeEllipseSE = 'x' ;
		M_IsChangeEllipseWidthLeft = 'x' ;
		M_IsChangeEllipseWidthRight = 'x' ;

		Invalidate () ;
	}
	// 객체를 이동시키다 클릭을 땐 경우
	else if ( M_IsMove == 'o' ) {
		if ( M_What == 'P' ) {
			if ( P_Insert.Poly_point.GetSize () > 0 ) {
				for ( int i = 0 ; i < pDoc -> P_Poly.GetAt ( M_Number ).Poly_point.GetCount () ; i++ )
					P_Insert.Poly_point.SetAt ( i, pDoc -> P_Poly.GetAt ( M_Number ).Poly_point.GetAt (i) ) ;
			}
		}
		else if ( M_What == "G" ) {
			pDoc -> G_Group.GetAt (M_Number).GroupBox.top = M_Rect.top + 2 ;
			pDoc -> G_Group.GetAt (M_Number).GroupBox.bottom = M_Rect.bottom - 2 ;
			pDoc -> G_Group.GetAt (M_Number).GroupBox.left = M_Rect.left + 2 ;
			pDoc -> G_Group.GetAt (M_Number).GroupBox.right = M_Rect.right - 2 ;
		}
		Invalidate () ;
		M_IsSelect = 'x' ;
	}
	
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
		L_CanMove = 'x' ;
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
		R_CanMove = 'x' ;
	}
	// PolyLine을 그리다 클릭을 땐 경우
	else if ( P_IsDraw == 'o' ) {
		// 만약 같은 좌표에 클릭, 땠을 경우 그리기 취소
		if ( P_IsMove == 'x' ) {
			P_CanMove = 'x' ; P_IsStart = 'x' ;
			P_Insert.Poly_point.RemoveAll () ;
			P_CanMove = 'x' ;
			P_IsContinue = 'x' ;
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
			M_IsSelect = 'x' ;
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
		E_CanMove = 'x' ;
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
		T_CanMove = 'x' ;
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
		RT_CanMove = 'x' ;
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
		RightT_CanMove = 'x' ;
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
		RRightT_CanMove = 'x' ;
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
		LTRT_CanMove = 'x' ;
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
		RTLT_CanMove = 'x' ;
	}
	// 그룹화 다중 선택을 하다가 클릭을 땐 경우
	else if ( m_IsSelectGroup == 'o' ) {
		G_Include.right = point.x ;
		G_Include.bottom = point.y ;

		if ( G_Include.left > G_Include.right ) {
			int temp = G_Include.right ;
			G_Include.right = G_Include.left ;
			G_Include.left = temp ;
		}
		if ( G_Include.top > G_Include.bottom ) {
			int temp = G_Include.bottom ;
			G_Include.bottom = G_Include.top ;
			G_Include.top = temp ;
		}
		int a = pDoc -> What.GetCount () ;
		G_IsMakeGroup = 'o' ;
		m_IsSelectGroup = 'x' ;
		Invalidate () ;
	}
	
	CScrollView::OnLButtonUp(nFlags, point);
}

// 선 그리기 툴바를 선택한 경우 불리어 집니다.
void CGraphicEditorView::OnDrawline()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	HideCaret () ;
	G_IsMakeGroup = 'x' ;
	Text_IsChange = 'x' ;
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
	Text_IsKeyDown = 'x' ;
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
	m_PSkeleton = 'x' ;
	P_IsDraw = 'x' ;
	L_IsDraw = 'o' ;
	IsNormal = 'x' ;

	Invalidate () ;
}


BOOL CGraphicEditorView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return CScrollView::OnSetCursor(pWnd, nHitTest, message);
	
	char Flag = 'x' ;

	if (nHitTest == HTCLIENT) {
		CPoint point ;
		::GetCursorPos ( &point ) ;	// 스크린 좌표
		ScreenToClient ( &point ) ;	// 클라이언트 좌표로 변환

		// 평상시엔 기본 커서로 변환 합니다.
		if ( IsNormal == 'o' )
			::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_ARROW)) ;
		// 선택한 PolyLine의 특정 Skeleton에 근접할 경우 커서를 변환합니다.
		else if ( M_IsDraw == 'o' && P_IsContinue == 'o' ) {
			for ( int i = 0 ; i < P_Insert.Poly_point.GetCount () ; i++ ) {
				if ( P_Insert.Poly_point.GetAt (i).x - 15 <= point.x && P_Insert.Poly_point.GetAt (i).x + 15 >= point.x &&
					 P_Insert.Poly_point.GetAt (i).y - 15 <= point.y && P_Insert.Poly_point.GetAt (i).y + 15 >= point.y ) {
					::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
					Flag = 'o' ; break ;
				}
			}
		}

		if ( M_IsDraw == 'o' && M_IsLineSelect == 'o' &&
			  ((pDoc -> L_Line.GetAt ( M_Number ).Start.x - 15 <= point.x && pDoc -> L_Line.GetAt ( M_Number ).Start.x + 15 >= point.x
			  && pDoc -> L_Line.GetAt ( M_Number ).Start.y - 15 <= point.y && pDoc -> L_Line.GetAt ( M_Number ).Start.y + 15 >= point.y) ||
			  (pDoc -> L_Line.GetAt ( M_Number ).Last.x - 15 <= point.x && pDoc -> L_Line.GetAt ( M_Number ).Last.x + 15 >= point.x
			  && pDoc -> L_Line.GetAt ( M_Number ).Last.y - 15 <= point.y && pDoc -> L_Line.GetAt ( M_Number ).Last.y + 15 >= point.y)) ) {

			::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ;
		}
		else if ( M_IsDraw == 'o' && M_IsEllipseSelect == 'o' && M_IsChangeEllipseSide == 'o' ) {
			if ( M_IsChangeEllipseNW == 'o' || M_IsChangeEllipseSE == 'o' )
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZENWSE)) ;
			else if ( M_IsChangeEllipseNE == 'o' || M_IsChangeEllipseSW == 'o' )
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZENESW)) ;
		}
		else if ( M_IsDraw == 'o' && M_IsEllipseSelect == 'o' && (M_IsChangeEllipseVerticalTop == 'o' || M_IsChangeEllipseVerticalBottom == 'o' ||
				  M_IsChangeEllipseWidthLeft == 'o' || M_IsChangeEllipseWidthRight == 'o') ) {
			if ( M_IsChangeEllipseVerticalTop == 'o' || M_IsChangeEllipseVerticalBottom == 'o' )
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZENS)) ;
			else {
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEWE)) ;
			}
		}
		else if ( M_IsDraw == 'o' && M_IsEllipseSelect == 'o' &&
				(( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) ||
				  ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) ||
				  ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) ||
				  ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) ||
				  ((M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top - 15 <= point.y && (M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top + 15 >= point.y &&
				    M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x) ||
				  ((M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top - 15 <= point.y && (M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top + 15 >= point.y &&
				    M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x)) ) {

			if ( ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) ||
				 ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) )
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZENWSE)) ;
			else if ( ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) ||
					  ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) )
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZENESW)) ;
			else
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEWE)) ;
		}
		else if ( M_IsDraw == 'o' && M_IsEllipseSelect == 'o' &&
				(((M_Rect.right - M_Rect.left) / 2 + M_Rect.left + 15 >= point.x && (M_Rect.right - M_Rect.left) / 2 + M_Rect.left - 15 <= point.x &&
				  M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y ) ||
				((M_Rect.right - M_Rect.left) / 2 + M_Rect.left + 15 >= point.x && (M_Rect.right - M_Rect.left) / 2 + M_Rect.left - 15 <= point.x &&
				  M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y)) ) {
			::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZENS)) ;
		}
		else if ( M_IsDraw == 'o' && M_IsRectSelect == 'o' && M_IsChangeRectSide == 'o' ) {
			if ( M_IsChangeRectNW == 'o' || M_IsChangeRectSE == 'o' )
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZENWSE)) ;
			else if ( M_IsChangeRectNE == 'o' || M_IsChangeRectSW == 'o' )
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZENESW)) ;
		}
		else if ( M_IsDraw == 'o' && M_IsRectSelect == 'o' && (M_IsChangeRectVerticalTop == 'o' || M_IsChangeRectVerticalBottom == 'o' ||
				  M_IsChangeRectWidthLeft == 'o' || M_IsChangeRectWidthRight == 'o') ) {
			if ( M_IsChangeRectVerticalTop == 'o' || M_IsChangeRectVerticalBottom == 'o' )
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZENS)) ;
			else {
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEWE)) ;
			}
		}
		else if ( M_IsDraw == 'o' && M_IsRectSelect == 'o' &&
				(( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) ||
				  ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) ||
				  ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) ||
				  ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) ||
				  ((M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top - 15 <= point.y && (M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top + 15 >= point.y &&
				    M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x) ||
				  ((M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top - 15 <= point.y && (M_Rect.bottom - M_Rect.top) / 2 + M_Rect.top + 15 >= point.y &&
				    M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x)) ) {

			if ( ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) ||
				 ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) )
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZENWSE)) ;
			else if ( ( M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y && M_Rect.right - 15 <= point.x && M_Rect.right + 15 >= point.x ) ||
					  ( M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y && M_Rect.left - 15 <= point.x && M_Rect.left + 15 >= point.x ) )
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZENESW)) ;
			else
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEWE)) ;
		}
		else if ( M_IsDraw == 'o' && M_IsRectSelect == 'o' &&
				(((M_Rect.right - M_Rect.left) / 2 + M_Rect.left + 15 >= point.x && (M_Rect.right - M_Rect.left) / 2 + M_Rect.left - 15 <= point.x &&
				  M_Rect.top - 15 <= point.y && M_Rect.top + 15 >= point.y ) ||
				((M_Rect.right - M_Rect.left) / 2 + M_Rect.left + 15 >= point.x && (M_Rect.right - M_Rect.left) / 2 + M_Rect.left - 15 <= point.x &&
				  M_Rect.bottom - 15 <= point.y && M_Rect.bottom + 15 >= point.y)) ) {
			::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZENS)) ;
		}
		else if ( M_IsMove == 'o' && Flag == 'x' ) {
			if ( M_IsDraw == 'x' )  {
				M_IsLineSelect = 'x' ;
				M_IsRectSelect = 'x' ;
				M_IsEllipseSelect = 'x' ;
			}

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

					// 선택한 좌표에 객체가 있는지 전부 확인합니다.
					// 늦게 그린 객체부터 확인합니다.
					for ( int i = pDoc->What.GetCount () ; i > 0  ; i-- ) {

						// 선 객체인 경우
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

						// 상자 객체인 경우
						else if ( pDoc -> What.GetAt (i-1) == _T ("R") ) {
							if ( pDoc -> R_Rec.GetAt ( R_Number ).left - 2 <= point.x && pDoc -> R_Rec.GetAt ( R_Number ).right + 2 >= point.x &&
								pDoc -> R_Rec.GetAt ( R_Number ).top - 2 <= point.y && pDoc -> R_Rec.GetAt ( R_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							R_Number-- ;
						}

						// PolyLine 객체인 경우
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

						// 원 객체인 경우
						else if ( pDoc -> What.GetAt (i-1) == _T ("E") ) {
							if ( pDoc -> E_Ellipse.GetAt ( E_Number ).left <= point.x && pDoc -> E_Ellipse.GetAt ( E_Number ).right >= point.x &&
								pDoc -> E_Ellipse.GetAt ( E_Number ).top <= point.y && pDoc -> E_Ellipse.GetAt ( E_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							E_Number-- ;
						}

						// 세모 객체인 경우
						else if ( pDoc -> What.GetAt (i-1) == _T ("T") ) {
							if ( pDoc -> T_Triangle.GetAt ( T_Number ).left - 2 <= point.x && pDoc -> T_Triangle.GetAt ( T_Number ).right + 2 >= point.x &&
								pDoc -> T_Triangle.GetAt ( T_Number ).top - 2 <= point.y && pDoc -> T_Triangle.GetAt ( T_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							T_Number-- ;
						}

						// 역 삼각형 객체인 경우
						else if ( pDoc -> What.GetAt (i-1) == _T ("RT") ) {
							if ( pDoc -> RT_Triangle.GetAt ( RT_Number ).left - 2 <= point.x && pDoc -> RT_Triangle.GetAt ( RT_Number ).right + 2 >= point.x &&
								pDoc -> RT_Triangle.GetAt ( RT_Number ).top - 2 <= point.y && pDoc -> RT_Triangle.GetAt ( RT_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							RT_Number-- ;
						}

						// 직각 삼각형 객체인 경우
						else if ( pDoc -> What.GetAt (i-1) == _T ("RightT") ) {
							if ( pDoc -> RightT_Triangle.GetAt ( RightT_Number ).left - 2 <= point.x && pDoc -> RightT_Triangle.GetAt ( RightT_Number ).right + 2 >= point.x &&
								pDoc -> RightT_Triangle.GetAt ( RightT_Number ).top - 2 <= point.y && pDoc -> RightT_Triangle.GetAt ( RightT_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							RightT_Number-- ;
						}

						// 역 직각 삼각형 객체인 경우
						else if ( pDoc -> What.GetAt (i-1) == _T ("RRightT") ) {
							if ( pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).left - 2 <= point.x && pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).right + 2 >= point.x &&
								pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).top - 2 <= point.y && pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							RRightT_Number-- ;
						}

						// 왼쪽 -> 오른쪽 삼각형 객체인 경우
						else if ( pDoc -> What.GetAt (i-1) == _T ("LTRT") ) {
							if ( pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).left - 2 <= point.x && pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).right + 2 >= point.x &&
								pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).top - 2 <= point.y && pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							LTRT_Number-- ;
						}

						// 오른쪽 -> 왼쪽 삼각형 객체인 경우
						else if ( pDoc -> What.GetAt (i-1) == _T ("RTLT") ) {
							if ( pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).left - 2 <= point.x && pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).right + 2 >= point.x &&
								pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).top - 2 <= point.y && pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
							}
							RTLT_Number-- ;
						}

					}
				}
			}
			else if ( M_IsDraw == 'x' ) {
				::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_ARROW)) ;

				// 선택한 좌표에 객체가 있는지 전부 확인합니다.
				// 늦게 그린 객체부터 확인합니다.
				for ( int i = pDoc->What.GetCount () ; i > 0  ; i-- ) {

					// 선 객체인 경우
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

					// 상자 객체인 경우
					else if ( pDoc -> What.GetAt (i-1) == _T ("R") ) {
						if ( pDoc -> R_Rec.GetAt ( R_Number ).left - 2 <= point.x && pDoc -> R_Rec.GetAt ( R_Number ).right + 2 >= point.x &&
							pDoc -> R_Rec.GetAt ( R_Number ).top - 2 <= point.y && pDoc -> R_Rec.GetAt ( R_Number ).bottom + 2 >= point.y ) {

							::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						R_Number-- ;
					}

					// PolyLine 객체인 경우
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

					// 원 객체인 경우
					else if ( pDoc -> What.GetAt (i-1) == _T ("E") ) {
						if ( pDoc -> E_Ellipse.GetAt ( E_Number ).left <= point.x && pDoc -> E_Ellipse.GetAt ( E_Number ).right >= point.x &&
							pDoc -> E_Ellipse.GetAt ( E_Number ).top <= point.y && pDoc -> E_Ellipse.GetAt ( E_Number ).bottom >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						E_Number-- ;
					}

					// 세모 객체인 경우
					else if ( pDoc -> What.GetAt (i-1) == _T ("T") ) {
						if ( pDoc -> T_Triangle.GetAt ( T_Number ).left - 2 <= point.x && pDoc -> T_Triangle.GetAt ( T_Number ).right + 2 >= point.x &&
							pDoc -> T_Triangle.GetAt ( T_Number ).top - 2 <= point.y && pDoc -> T_Triangle.GetAt ( T_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						T_Number-- ;
					}

					// 역 삼각형 객체인 경우
					else if ( pDoc -> What.GetAt (i-1) == _T ("RT") ) {
						if ( pDoc -> RT_Triangle.GetAt ( RT_Number ).left - 2 <= point.x && pDoc -> RT_Triangle.GetAt ( RT_Number ).right + 2 >= point.x &&
							pDoc -> RT_Triangle.GetAt ( RT_Number ).top - 2 <= point.y && pDoc -> RT_Triangle.GetAt ( RT_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						RT_Number-- ;
					}

					// 직각 삼각형 객체인 경우
					else if ( pDoc -> What.GetAt (i-1) == _T ("RightT") ) {
						if ( pDoc -> RightT_Triangle.GetAt ( RightT_Number ).left - 2 <= point.x && pDoc -> RightT_Triangle.GetAt ( RightT_Number ).right + 2 >= point.x &&
							pDoc -> RightT_Triangle.GetAt ( RightT_Number ).top - 2 <= point.y && pDoc -> RightT_Triangle.GetAt ( RightT_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						RightT_Number-- ;
					}

					// 역 직각 삼각형 객체인 경우
					else if ( pDoc -> What.GetAt (i-1) == _T ("RRightT") ) {
						if ( pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).left - 2 <= point.x && pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).right + 2 >= point.x &&
							pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).top - 2 <= point.y && pDoc -> RRightT_Triangle.GetAt ( RRightT_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						RRightT_Number-- ;
					}

					// 왼쪽 -> 오른쪽 삼각형 객체인 경우
					else if ( pDoc -> What.GetAt (i-1) == _T ("LTRT") ) {
						if ( pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).left - 2 <= point.x && pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).right + 2 >= point.x &&
							pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).top - 2 <= point.y && pDoc -> LTRT_Triangle.GetAt ( LTRT_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						LTRT_Number-- ;
					}

					// 오른쪽 -> 왼쪽 삼각형 객체인 경우
					else if ( pDoc -> What.GetAt (i-1) == _T ("RTLT") ) {
						if ( pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).left - 2 <= point.x && pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).right + 2 >= point.x &&
							pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).top - 2 <= point.y && pDoc -> RTLT_Triangle.GetAt ( RTLT_Number ).bottom + 2 >= point.y ) {

								::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_SIZEALL)) ; break ;
						}
						RTLT_Number-- ;
					}

				}
			}
		}
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
		// Text 모드 + 입력 중이라면 기본 커서로 변합니다.
		else if ( Text_IsText == 'o' && Text_IsKeyDown == 'o' ) {
			::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_ARROW)) ;
		}
		// Text 모드에선 커서가 글자 입력 모양으로 변합니다.
		else if ( Text_IsText == 'o' ) {
			::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_IBEAM)) ;
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

	HideCaret () ;
	G_IsMakeGroup = 'x' ;
	Text_IsChange = 'x' ;
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
	Text_IsKeyDown = 'x' ;
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
	m_PSkeleton = 'x' ;
	P_IsDraw = 'x' ;
	R_IsDraw = 'o' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

// PolyLine 그리기 툴바를 선택한 경우 불리어 집니다.
void CGraphicEditorView::OnDrawpoly()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	HideCaret () ;
	G_IsMakeGroup = 'x' ;
	Text_IsChange = 'x' ;
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
	Text_IsKeyDown = 'x' ;
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
	m_PSkeleton = 'x' ;
	P_IsDraw = 'x' ;
	Invalidate () ;

	P_IsDraw = 'o' ;
	IsNormal = 'x' ;
}

// 원 그리기 툴바를 선택한 경우 불리어 집니다.
void CGraphicEditorView::OnDrawellipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	HideCaret () ;
	G_IsMakeGroup = 'x' ;
	Text_IsChange = 'x' ;
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
	Text_IsKeyDown = 'x' ;
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
	m_PSkeleton = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'o' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

void CGraphicEditorView::OnSelectobject()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	HideCaret () ;
	G_IsMakeGroup = 'x' ;
	Text_IsChange = 'x' ;
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	Text_IsText = 'x' ;
	Text_IsKeyDown = 'x' ;
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
	m_PSkeleton = 'x' ;
	P_IsDraw = 'x' ;
	IsNormal = 'x' ;
	M_IsMove = 'o' ;

	Invalidate () ;
}

void CGraphicEditorView::OnChangecolor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CColorDialog dlgColor(0, CC_FULLOPEN, NULL);

	if ( M_IsDraw != 'o' ) {
		if ( dlgColor.DoModal() == IDOK )
		{
			m_Color = dlgColor.GetColor();
			m_IsColor = 'o' ;
		}
	}
	else {
		if ( dlgColor.DoModal () == IDOK )
		{
			m_Color = dlgColor.GetColor () ;
			
			if ( M_What == _T ("L") )
				pDoc -> L_Line.GetAt ( M_Number ).L_Color = m_Color ;
			else if ( M_What == _T ("R") )
				pDoc -> R_Color.GetAt ( M_Number ) = m_Color ;
			else if ( M_What == _T ("P") )
				pDoc -> P_Poly.GetAt ( M_Number ).P_Color = m_Color ;
			else if ( M_What == _T ("E") )
				pDoc -> E_Color.GetAt ( M_Number ) = m_Color ;
			else if ( M_What == _T ("T") )
				pDoc -> T_Color.GetAt ( M_Number ) = m_Color ;
			else if ( M_What == _T ("RT") )
				pDoc -> RT_Color.GetAt ( M_Number ) = m_Color ;
			else if ( M_What == _T ("RightT") )
				pDoc -> RightT_Color.GetAt ( M_Number ) = m_Color ;
			else if ( M_What == _T ("RRightT") )
				pDoc -> RRightT_Color.GetAt ( M_Number ) = m_Color ;
			else if ( M_What == _T ("LTRT") )
				pDoc -> LTRT_Color.GetAt ( M_Number ) = m_Color ;
			else if ( M_What == _T ("RTLT") )
				pDoc -> RTLT_Color.GetAt ( M_Number ) = m_Color ;
			else if ( M_What == _T ("G") ) {
				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).E_Color.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).E_Color.GetAt (i) = m_Color ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Line.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).Line.GetAt (i).L_Color = m_Color ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Poly.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).Poly.GetAt (i).P_Color = m_Color ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).R_Color.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).R_Color.GetAt (i) = m_Color ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Index.GetCount () ; i++ ) {
					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_Color.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_Color.GetAt (j) = m_Color ;
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_Color.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_Color.GetAt (j) = m_Color ;
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Line.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Line.GetAt (j).L_Color = m_Color ;
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Poly.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Poly.GetAt (j).P_Color = m_Color ;
					}
				}
			}

			m_IsColor = 'o' ;

			Invalidate () ;
		}
	}
}


void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	HideCaret () ;
	G_IsMakeGroup = 'x' ;
	Text_IsChange = 'x' ;
	P_CanMove = 'x' ;
	IsNormal = 'o' ;
	P_Insert.Poly_point.RemoveAll () ;
	P_ChangeSkeleton = 0 ;
	P_IsContinue = 'x' ;
	m_PSkeleton = 'x' ;
	P_DrawContinue = 'x' ;
	P_IsStart = 'x' ;
	P_IsMove = 'x' ;
	M_IsChangeLineStart = 'x' ;
	M_ChangeLineOnePoint = 'x' ;
	M_IsRectSelect = 'x' ;
	M_ChangeRectSize = 'x' ;
	M_IsChangeRectVerticalTop = 'x' ;
	M_IsChangeRectVerticalBottom = 'x' ;
	M_IsChangeRectSide = 'x' ;
	M_IsChangeRectNW = 'x' ;
	M_IsChangeRectNE = 'x' ;
	M_IsChangeRectSW = 'x' ;
	M_IsChangeRectSE = 'x' ;
	M_IsChangeRectWidthLeft = 'x' ;
	M_IsChangeRectWidthRight = 'x' ;
	M_IsEllipseSelect = 'x' ;
	M_ChangeEllipseSize = 'x' ;
	M_IsChangeEllipseSide = 'x' ;
	M_IsChangeEllipseNW = 'x' ;
	M_IsChangeEllipseNE = 'x' ;
	M_IsChangeEllipseSW = 'x' ;
	M_IsChangeEllipseSE = 'x' ;
	M_IsChangeEllipseVerticalTop = 'x' ;
	M_IsChangeEllipseVerticalBottom = 'x' ;
	M_IsChangeEllipseWidthLeft = 'x' ;
	M_IsChangeEllipseWidthRight = 'x' ;
	M_IsLineSelect = 'x' ;
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
	Text_IsKeyDown = 'x' ;
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

// 채우기 색 변경하는 버튼
void CGraphicEditorView::OnChangefillcolor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CColorDialog dlgColor(0, CC_FULLOPEN, NULL) ;
	
	if ( M_IsDraw != 'o' ) {
		if( dlgColor.DoModal() == IDOK )
		{
			m_FillColor = dlgColor.GetColor();
			m_IsFillColor = 'o' ;
		}
	}
	else {
		m_IsFillColor = 'o' ;

		if ( dlgColor.DoModal () == IDOK ) {
			m_FillColor = dlgColor.GetColor () ;

			if ( M_What == _T ("R") ) {
				pDoc -> R_FillColor.GetAt ( M_Number ) = m_FillColor ;
				pDoc -> R_IsNoFill.GetAt ( M_Number ) = 'x' ;
			}
			else if ( M_What == _T("E") ) {
				pDoc -> E_FillColor.GetAt ( M_Number ) = m_FillColor ;
				pDoc -> E_IsNoFill.GetAt ( M_Number ) = 'x' ;
			}
			else if ( M_What == _T("T") ) {
				pDoc -> T_FillColor.GetAt ( M_Number ) = m_FillColor ;
				pDoc -> T_IsNoFill.GetAt ( M_Number ) = 'x' ;
			}
			else if ( M_What == _T("RT") ) {
				pDoc -> RT_FillColor.GetAt ( M_Number ) = m_FillColor ;
				pDoc -> RT_IsNoFill.GetAt ( M_Number ) = 'x' ;
			}
			else if ( M_What == _T("RightT") ) {
				pDoc -> RightT_FillColor.GetAt ( M_Number ) = m_FillColor ;
				pDoc -> RightT_IsNoFill.GetAt ( M_Number ) = 'x' ;
			}
			else if ( M_What == _T("RRightT") ) {
				pDoc -> RRightT_FillColor.GetAt ( M_Number ) = m_FillColor ;
				pDoc -> RRightT_IsNoFill.GetAt ( M_Number ) = 'x' ;
			}
			else if ( M_What == _T("LTRT") ) {
				pDoc -> LTRT_FillColor.GetAt ( M_Number ) = m_FillColor ;
				pDoc -> LTRT_IsNoFill.GetAt ( M_Number ) = 'x' ;
			}
			else if ( M_What == _T("RTLT") ) {
				pDoc -> RTLT_FillColor.GetAt ( M_Number ) = m_FillColor ;
				pDoc -> RTLT_IsNoFill.GetAt ( M_Number ) = 'x' ;
			}
			else if ( M_What == _T ("G") ) {
				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).E_FillColor.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).E_FillColor.GetAt (i) = m_FillColor ;
					pDoc -> G_Group.GetAt ( M_Number ).E_IsNoFill.GetAt (i) = 'x' ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).R_FillColor.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).R_FillColor.GetAt (i) = m_FillColor ;
					pDoc -> G_Group.GetAt ( M_Number ).R_IsNoFill.GetAt (i) = 'x' ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Index.GetCount () ; i++ ) {
					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_FillColor.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_FillColor.GetAt (j) = m_FillColor ;
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_IsNoFill.GetAt (j) = 'x' ;
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_FillColor.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_FillColor.GetAt (j) = m_FillColor ;
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_IsNoFill.GetAt (j) = 'x' ;
					}
				}
			}
		}

		Invalidate () ;
	}
}

// 채우기 색을 투명으로 하는 버튼
void CGraphicEditorView::OnNofillcolor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if ( M_IsDraw != 'o' ) {
		m_IsFillColor = 'x' ;
		if ( M_What == _T ("R") )
			pDoc -> R_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("E") )
			pDoc -> E_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("T") )
			pDoc -> T_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("RT") )
			pDoc -> RT_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("RightT") )
			pDoc -> RightT_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("RRightT") )
			pDoc -> RRightT_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("LTRT") )
			pDoc -> LTRT_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("RTLT") )
			pDoc -> RTLT_IsNoFill.GetAt ( M_Number ) = 'o' ;
	}
	else {
		m_IsFillColor = 'x' ;
		if ( M_What == _T ("R") )
			pDoc -> R_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("E") )
			pDoc -> E_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("T") )
			pDoc -> T_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("RT") )
			pDoc -> RT_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("RightT") )
			pDoc -> RightT_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("RRightT") )
			pDoc -> RRightT_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("LTRT") )
			pDoc -> LTRT_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T("RTLT") )
			pDoc -> RTLT_IsNoFill.GetAt ( M_Number ) = 'o' ;
		else if ( M_What == _T ("G") ) {
			for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).E_FillColor.GetCount () ; i++ ) {
				pDoc -> G_Group.GetAt ( M_Number ).E_IsNoFill.GetAt (i) = 'o' ;
			}

			for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).R_FillColor.GetCount () ; i++ ) {
				pDoc -> G_Group.GetAt ( M_Number ).R_IsNoFill.GetAt (i) = 'o' ;
			}

			for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Index.GetCount () ; i++ ) {
				for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_FillColor.GetCount () ; j++ ) {
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_IsNoFill.GetAt (j) = 'o' ;
				}

				for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_FillColor.GetCount () ; j++ ) {
					pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_IsNoFill.GetAt (j) = 'o' ;
				}
			}
		}
		Invalidate () ;
	}
}

// 세모 그리기 모드
void CGraphicEditorView::OnDrawtriangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	HideCaret () ;
	G_IsMakeGroup = 'x' ;
	Text_IsChange = 'x' ;
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
	Text_IsKeyDown = 'x' ;
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
	m_PSkeleton = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

// 역 삼각형 그리기 모드
void CGraphicEditorView::OnDrawreversetri()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	HideCaret () ;
	G_IsMakeGroup = 'x' ;
	Text_IsChange = 'x' ;
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
	Text_IsKeyDown = 'x' ;
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
	m_PSkeleton = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

// 두께 지정 버튼 처리기
void CGraphicEditorView::OnThickness()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CThickness dlg (this) ;

	if ( M_IsDraw != 'o' ) {
		if( dlg.DoModal() == IDOK )
		{
			m_Thickness = dlg.GetThickness () ;
			m_IsThickness = 'o' ;
			P_Insert.Poly_point.RemoveAll () ;
			P_CanMove = 'x' ;
			P_IsContinue = 'x' ;
			m_PSkeleton = 'x' ;
		}
	}
	else {
		if ( dlg.DoModal () == IDOK )
		{
			m_Thickness = dlg.GetThickness () ;
			m_IsThickness = 'o' ;

			if ( M_What == _T ("L") ) {
				pDoc -> L_Line.GetAt ( M_Number ).Thickness = m_Thickness ;
				
				if ( pDoc -> L_Line.GetAt ( M_Number ).Start.x >= pDoc -> L_Line.GetAt ( M_Number ).Last.x ) {
					M_Rect.left = pDoc -> L_Line.GetAt ( M_Number ).Last.x - pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
					M_Rect.right = pDoc -> L_Line.GetAt ( M_Number ).Start.x + pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
				}
				else {
					M_Rect.left = pDoc -> L_Line.GetAt ( M_Number ).Start.x - pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
					M_Rect.right = pDoc -> L_Line.GetAt ( M_Number ).Last.x + pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
				}

				if ( pDoc -> L_Line.GetAt ( M_Number ).Start.y >= pDoc -> L_Line.GetAt ( M_Number ).Last.y ) {
					M_Rect.top = pDoc -> L_Line.GetAt ( M_Number ).Last.y - pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
					M_Rect.bottom = pDoc -> L_Line.GetAt ( M_Number ).Start.y + pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
				}
				else {
					M_Rect.top = pDoc -> L_Line.GetAt ( M_Number ).Start.y - pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
					M_Rect.bottom = pDoc -> L_Line.GetAt ( M_Number ).Last.y + pDoc -> L_Line.GetAt ( M_Number ).Thickness / 2 ;
				}
			}
			else if ( M_What == _T ("R") ) {
				pDoc -> R_Thickness.GetAt ( M_Number ) = m_Thickness ;

				M_Rect.top = pDoc -> R_Rec.GetAt ( M_Number ).top - pDoc -> R_Thickness.GetAt ( M_Number ) / 2 - 2 ;
				M_Rect.bottom = pDoc -> R_Rec.GetAt ( M_Number ).bottom + pDoc -> R_Thickness.GetAt ( M_Number ) / 2 + 2 ;
				M_Rect.left = pDoc -> R_Rec.GetAt ( M_Number ).left - pDoc -> R_Thickness.GetAt ( M_Number ) / 2 - 2 ;
				M_Rect.right = pDoc -> R_Rec.GetAt ( M_Number ).right + pDoc -> R_Thickness.GetAt ( M_Number ) / 2 + 2 ;
			}
			else if ( M_What == _T ("P") ) {
				pDoc -> P_Poly.GetAt ( M_Number ).thickness = m_Thickness ;
				
				M_Rect.top = M_PMin_y - pDoc -> P_Poly.GetAt ( M_Number ).thickness / 2 ;
				M_Rect.bottom = M_PMax_y + pDoc -> P_Poly.GetAt ( M_Number ).thickness / 2 ;
				M_Rect.left = M_PMin_x - pDoc -> P_Poly.GetAt ( M_Number ).thickness / 2 ;
				M_Rect.right = M_PMax_x + pDoc -> P_Poly.GetAt ( M_Number ).thickness / 2 ;
			}
			else if ( M_What == _T ("E") ) {
				pDoc -> E_Thickness.GetAt ( M_Number ) = m_Thickness ;

				M_Rect.top = pDoc -> E_Ellipse.GetAt ( M_Number ).top - pDoc -> E_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.bottom = pDoc -> E_Ellipse.GetAt ( M_Number ).bottom + pDoc -> E_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.left = pDoc -> E_Ellipse.GetAt ( M_Number ).left - pDoc -> E_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.right = pDoc -> E_Ellipse.GetAt ( M_Number ).right + pDoc -> E_Thickness.GetAt ( M_Number ) / 2 ;
			}
			else if ( M_What == _T ("T") ) {
				pDoc -> T_Thickness.GetAt ( M_Number ) = m_Thickness ;

				M_Rect.top = pDoc -> T_Triangle.GetAt ( M_Number ).top - pDoc -> T_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.bottom = pDoc -> T_Triangle.GetAt ( M_Number ).bottom + pDoc -> T_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.left = pDoc -> T_Triangle.GetAt ( M_Number ).left - pDoc -> T_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.right = pDoc -> T_Triangle.GetAt ( M_Number ).right + pDoc -> T_Thickness.GetAt ( M_Number ) / 2 ;
			}
			else if ( M_What == _T ("RT") ) {
				pDoc -> RT_Thickness.GetAt ( M_Number ) = m_Thickness ;

				M_Rect.top = pDoc -> RT_Triangle.GetAt ( M_Number ).top - pDoc -> RT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.bottom = pDoc -> RT_Triangle.GetAt ( M_Number ).bottom + pDoc -> RT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.left = pDoc -> RT_Triangle.GetAt ( M_Number ).left - pDoc -> RT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.right = pDoc -> RT_Triangle.GetAt ( M_Number ).right + pDoc -> RT_Thickness.GetAt ( M_Number ) / 2 ;
			}
			else if ( M_What == _T ("RightT") ) {
				pDoc -> RightT_Thickness.GetAt ( M_Number ) = m_Thickness ;

				M_Rect.top = pDoc -> RightT_Triangle.GetAt ( M_Number ).top - pDoc -> RightT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.bottom = pDoc -> RightT_Triangle.GetAt ( M_Number ).bottom + pDoc -> RightT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.left = pDoc -> RightT_Triangle.GetAt ( M_Number ).left - pDoc -> RightT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.right = pDoc -> RightT_Triangle.GetAt ( M_Number ).right + pDoc -> RightT_Thickness.GetAt ( M_Number ) / 2 ;
			}
			else if ( M_What == _T ("RRightT") ) {
				pDoc -> RRightT_Thickness.GetAt ( M_Number ) = m_Thickness ;

				M_Rect.top = pDoc -> RRightT_Triangle.GetAt ( M_Number ).top - pDoc -> RRightT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.bottom = pDoc -> RRightT_Triangle.GetAt ( M_Number ).bottom + pDoc -> RRightT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.left = pDoc -> RRightT_Triangle.GetAt ( M_Number ).left - pDoc -> RRightT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.right = pDoc -> RRightT_Triangle.GetAt ( M_Number ).right + pDoc -> RRightT_Thickness.GetAt ( M_Number ) / 2 ;
			}
			else if ( M_What == _T ("LTRT") ) {
				pDoc -> LTRT_Thickness.GetAt ( M_Number ) = m_Thickness ;

				M_Rect.top = pDoc -> LTRT_Triangle.GetAt ( M_Number ).top - pDoc -> LTRT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.bottom = pDoc -> LTRT_Triangle.GetAt ( M_Number ).bottom + pDoc -> LTRT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.left = pDoc -> LTRT_Triangle.GetAt ( M_Number ).left - pDoc -> LTRT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.right = pDoc -> LTRT_Triangle.GetAt ( M_Number ).right + pDoc -> LTRT_Thickness.GetAt ( M_Number ) / 2 ;
			}
			else if ( M_What == _T ("RTLT") ) {
				pDoc -> RTLT_Thickness.GetAt ( M_Number ) = m_Thickness ;

				M_Rect.top = pDoc -> RTLT_Triangle.GetAt ( M_Number ).top - pDoc -> RTLT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.bottom = pDoc -> RTLT_Triangle.GetAt ( M_Number ).bottom + pDoc -> RTLT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.left = pDoc -> RTLT_Triangle.GetAt ( M_Number ).left - pDoc -> RTLT_Thickness.GetAt ( M_Number ) / 2 ;
				M_Rect.right = pDoc -> RTLT_Triangle.GetAt ( M_Number ).right + pDoc -> RTLT_Thickness.GetAt ( M_Number ) / 2 ;
			}
			else if ( M_What == _T ("G") ) {
				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).R_Thickness.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).R_Thickness.GetAt (i) = m_Thickness ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).E_Thickness.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).E_Thickness.GetAt (i) = m_Thickness ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Line.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).Line.GetAt (i).Thickness = m_Thickness ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Poly.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).Poly.GetAt (i).thickness = m_Thickness ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Index.GetCount () ; i++ ) {

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_Thickness.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_Thickness.GetAt (j) = m_Thickness ;
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_Thickness.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_Thickness.GetAt (j) = m_Thickness ;
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Line.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Line.GetAt (j).Thickness = m_Thickness ;
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Poly.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Poly.GetAt (j).thickness = m_Thickness ;
					}
				}
			}

			if ( M_What == _T ("G") ) {
				int Min_x = 0 ;
				int Min_y = 0 ;
				int Max_x = Min_x ;
				int Max_y = Min_y ;

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).R_Thickness.GetCount () ; i++ ) {
					if ( pDoc -> G_Group.GetAt ( M_Number ).Rect.GetAt (i).top - pDoc -> G_Group.GetAt ( M_Number ).R_Thickness.GetAt (i) / 2 < pDoc -> G_Group.GetAt ( M_Number ).GroupBox.top )
						pDoc -> G_Group.GetAt ( M_Number ).GroupBox.top = pDoc -> G_Group.GetAt ( M_Number ).Rect.GetAt (i).top - pDoc -> G_Group.GetAt ( M_Number ).R_Thickness.GetAt (i) / 2 ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).E_Thickness.GetCount () ; i++ ) {
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Line.GetCount () ; i++ ) {
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Poly.GetCount () ; i++ ) {
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Index.GetCount () ; i++ ) {

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_Thickness.GetCount () ; j++ ) {
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_Thickness.GetCount () ; j++ ) {
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Line.GetCount () ; j++ ) {
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Poly.GetCount () ; j++ ) {
					}
				}

			}

			Invalidate () ;
		}
	}
}

// 직각 삼각형 그리기 모드
void CGraphicEditorView::OnRightangledtri()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	HideCaret () ;
	G_IsMakeGroup = 'x' ;
	Text_IsChange = 'x' ;
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
	Text_IsKeyDown = 'x' ;
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
	m_PSkeleton = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

// 역 직각 삼각형 그리기 모드
void CGraphicEditorView::OnRRrightangledtri()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	HideCaret () ;
	G_IsMakeGroup = 'x' ;
	Text_IsChange = 'x' ;
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
	Text_IsKeyDown = 'x' ;
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
	m_PSkeleton = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

// 오른쪽 -> 왼쪽 삼각형 그리기 모드
void CGraphicEditorView::OnRighttolefttri()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	HideCaret () ;
	G_IsMakeGroup = 'x' ;
	Text_IsChange = 'x' ;
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
	Text_IsKeyDown = 'x' ;
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
	m_PSkeleton = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

// 왼쪽 -> 오른쪽 삼각형 그리기 모드
void CGraphicEditorView::OnLefttorighttri()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	HideCaret () ;
	G_IsMakeGroup = 'x' ;
	Text_IsChange = 'x' ;
	M_IsSelect = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'x' ;
	Text_IsKeyDown = 'x' ;
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
	m_PSkeleton = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}

// 폰트 바꾸기 버튼
void CGraphicEditorView::OnFont()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFontDialog dlg ;
	if ( M_IsDraw != 'o' ) {
		if( dlg.DoModal() == IDOK )
		{
			dlg.GetCurrentFont (&Text_lf) ;
			Text_IsFont = 'o' ;
			Text_Color = dlg.GetColor () ;
		}
	}
	else {
		if( dlg.DoModal() == IDOK )
		{
			Text_IsFont = 'o' ;
			Text_Color = dlg.GetColor () ;
			dlg.GetCurrentFont (&Text_lf) ;
			if ( M_What == _T ("Text") ) {
				pDoc -> Text_Text.GetAt ( M_Number ).Font = Text_lf ;
				pDoc -> Text_Text.GetAt ( M_Number ).Color = Text_Color ;
				pDoc -> Text_Text.GetAt ( M_Number ).IsFont = 'o' ;
			}
			else if ( M_What == _T ("G") ) {
				
				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Text.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).Text.GetAt (i).Font = Text_lf ;
					pDoc -> G_Group.GetAt ( M_Number ).Text.GetAt (i).Color = Text_Color ;
					pDoc -> G_Group.GetAt ( M_Number ).Text.GetAt (i).IsFont = 'o' ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Index.GetCount () ; i++ ) {

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetAt (j).Font = Text_lf ;
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetAt (j).Color = Text_Color ;
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetAt (j).IsFont = 'o' ;
					}
				}
			}

			Invalidate () ;
		} 
	}
}

// 텍스트 삽입 모드
void CGraphicEditorView::OnText()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	M_IsSelect = 'x' ;
	G_IsMakeGroup = 'x' ;
	Text_IsChange = 'x' ;
	M_IsDraw = 'x' ;
	M_IsMove = 'x' ;
	Text_IsText = 'o' ;
	Text_IsKeyDown = 'x' ;
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
	m_PSkeleton = 'x' ;
	P_IsDraw = 'x' ;
	E_IsDraw = 'x' ;
	IsNormal = 'x' ;

	Invalidate () ;
}


void CGraphicEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// 특정 객체를 클릭한 상태입니다.
	if ( M_IsDraw == 'o' && Text_IsChange == 'x' ) {
		// Delete 키나 백 스페이스 키를 누르면 해당 객체를 삭제합니다.
		if ( nChar == VK_DELETE || nChar == VK_BACK ) {
			if ( M_What == _T ("L") ) {

				M_ChangeLineOnePoint = 'x' ;
				M_IsChangeLineStart = 'x' ;
				M_IsSelect = 'x' ;
				M_IsDraw = 'x' ;
				pDoc -> L_Line.RemoveAt ( M_Number ) ;
				int location = pDoc -> L_Location.GetAt ( M_Number ) ;
				pDoc -> L_Count-- ;
				pDoc -> What.RemoveAt ( pDoc -> L_Location.GetAt ( M_Number ) ) ;
				pDoc -> L_Location.RemoveAt ( M_Number ) ;

				for ( int i = M_Number ; i < pDoc -> L_Line.GetCount () ; i++ ) {
					pDoc -> L_Location.GetAt (i)-- ;
				}
				int R_For = 0 ;
				int P_For = 0 ;
				int E_For = 0 ;
				int T_For = 0 ;
				int RT_For = 0 ;
				int RightT_For = 0 ;
				int RRightT_For = 0 ;
				int LTRT_For = 0 ;
				int RTLT_For = 0 ;
				int Text_For = 0 ;
				int G_For = 0 ;

				for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
					if ( pDoc -> What.GetAt (i) == _T ("R") ) {
						for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
							if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
								pDoc -> R_Location.SetAt (j, i) ;
								R_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("P") ) {
						for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
							if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
								pDoc -> P_Location.SetAt (j, i) ;
								P_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("E") ) {
						for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
							if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
								pDoc -> E_Location.SetAt (j, i) ;
								E_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("T") ) {
						for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
							if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
								pDoc -> T_Location.SetAt (j, i) ;
								T_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
						for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
								pDoc -> RT_Location.SetAt (j, i) ;
								RT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
						for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RightT_Location.SetAt (j, i) ;
								RightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
						for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RRightT_Location.SetAt (j, i) ;
								RRightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
						for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
							if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
								pDoc -> LTRT_Location.SetAt (j, i) ;
								LTRT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
						for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
								pDoc -> RTLT_Location.SetAt (j, i) ;
								RTLT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
						for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
							if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
								pDoc -> Text_Location.SetAt (j, i) ;
								Text_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("G") ) {
						for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
							if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
								pDoc -> G_Location.SetAt (j, i) ;
								G_For = j ;
								break ;
							}
						}
					}
				}
				M_Number = 0 ;
			}
			else if ( M_What == _T ("R") ) {
				M_ChangeLineOnePoint = 'x' ;
				M_IsChangeLineStart = 'x' ;
				M_IsSelect = 'x' ;
				M_IsDraw = 'x' ;
				pDoc -> R_Count-- ;
				int location = pDoc -> R_Location.GetAt ( M_Number ) ;
				pDoc -> What.RemoveAt ( pDoc -> R_Location.GetAt ( M_Number ) ) ;
				pDoc -> R_Rec.RemoveAt ( M_Number ) ;
				pDoc -> R_Location.RemoveAt ( M_Number ) ;
				pDoc -> R_Color.RemoveAt ( M_Number ) ;
				pDoc -> R_FillColor.RemoveAt ( M_Number ) ;
				pDoc -> R_FillPattern.RemoveAt ( M_Number ) ;
				pDoc -> R_IsNoFill.RemoveAt ( M_Number ) ;
				pDoc -> R_LinePattern.RemoveAt ( M_Number ) ;
				pDoc -> R_Thickness.RemoveAt ( M_Number ) ;

				for ( int i = M_Number ; i < pDoc -> R_Rec.GetCount () ; i++ ) {
					pDoc -> R_Location.GetAt (i)-- ;
				}

				int L_For = 0 ;
				int P_For = 0 ;
				int E_For = 0 ;
				int T_For = 0 ;
				int RT_For = 0 ;
				int RightT_For = 0 ;
				int RRightT_For = 0 ;
				int LTRT_For = 0 ;
				int RTLT_For = 0 ;
				int Text_For = 0 ;
				int G_For = 0 ;

				for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
					if ( pDoc -> What.GetAt (i) == _T ("L") ) {
						for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
							if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
								pDoc -> L_Location.SetAt (j, i) ;
								L_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("P") ) {
						for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
							if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
								pDoc -> P_Location.SetAt (j, i) ;
								P_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("E") ) {
						for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
							if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
								pDoc -> E_Location.SetAt (j, i) ;
								E_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("T") ) {
						for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
							if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
								pDoc -> T_Location.SetAt (j, i) ;
								T_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
						for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
								pDoc -> RT_Location.SetAt (j, i) ;
								RT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
						for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RightT_Location.SetAt (j, i) ;
								RightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
						for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RRightT_Location.SetAt (j, i) ;
								RRightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
						for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
							if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
								pDoc -> LTRT_Location.SetAt (j, i) ;
								LTRT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
						for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
								pDoc -> RTLT_Location.SetAt (j, i) ;
								RTLT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
						for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
							if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
								pDoc -> Text_Location.SetAt (j, i) ;
								Text_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("G") ) {
						for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
							if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
								pDoc -> G_Location.SetAt (j, i) ;
								G_For = j ;
								break ;
							}
						}
					}
				}
				M_Number = 0 ;
			}
			else if ( M_What == _T ("P") ) {

				if ( m_PSkeleton != 'o' || pDoc -> P_Poly.GetAt (M_Number).Poly_point.GetCount () == 2 ) {
					M_IsSelect = 'x' ;
					M_IsDraw = 'x' ;
					int location = pDoc -> P_Location.GetAt ( M_Number ) ;
					pDoc -> P_Poly.RemoveAt ( M_Number ) ;
					pDoc -> P_Count-- ;
					pDoc -> What.RemoveAt ( pDoc -> P_Location.GetAt ( M_Number ) ) ;
					pDoc -> P_Location.RemoveAt ( M_Number ) ;
					for ( int i = M_Number ; i < pDoc -> P_Poly.GetCount () ; i++ ) {
						pDoc -> P_Location.GetAt (i)-- ;
					}

					int R_For = 0 ;
					int L_For = 0 ;
					int E_For = 0 ;
					int T_For = 0 ;
					int RT_For = 0 ;
					int RightT_For = 0 ;
					int RRightT_For = 0 ;
					int LTRT_For = 0 ;
					int RTLT_For = 0 ;
					int Text_For = 0 ;
					int G_For = 0 ;

					for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
						if ( pDoc -> What.GetAt (i) == _T ("R") ) {
							for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
								if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
									pDoc -> R_Location.SetAt (j, i) ;
									R_For = j ;
									break ;
								}
							}
						}
						else if ( pDoc -> What.GetAt (i) == _T("L") ) {
							for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
								if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
									pDoc -> L_Location.SetAt (j, i) ;
									L_For = j ;
									break ;
								}
							}
						}
						else if ( pDoc -> What.GetAt (i) == _T("E") ) {
							for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
								if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
									pDoc -> E_Location.SetAt (j, i) ;
									E_For = j ;
									break ;
								}
							}
						}
						else if ( pDoc -> What.GetAt (i) == _T("T") ) {
							for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
								if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
									pDoc -> T_Location.SetAt (j, i) ;
									T_For = j ;
									break ;
								}
							}
						}
						else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
							for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
								if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
									pDoc -> RT_Location.SetAt (j, i) ;
									RT_For = j ;
									break ;
								}
							}
						}
						else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
							for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
								if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
									pDoc -> RightT_Location.SetAt (j, i) ;
									RightT_For = j ;
									break ;
								}
							}
						}
						else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
							for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
								if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
									pDoc -> RRightT_Location.SetAt (j, i) ;
									RRightT_For = j ;
									break ;
								}
							}
						}
						else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
							for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
								if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
									pDoc -> LTRT_Location.SetAt (j, i) ;
									LTRT_For = j ;
									break ;
								}
							}
						}
						else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
							for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
								if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
									pDoc -> RTLT_Location.SetAt (j, i) ;
									RTLT_For = j ;
									break ;
								}
							}
						}
						else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
							for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
								if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
									pDoc -> Text_Location.SetAt (j, i) ;
									Text_For = j ;
									break ;
								}
							}
						}
						else if ( pDoc -> What.GetAt (i) == _T("G") ) {
						for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
							if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
								pDoc -> G_Location.SetAt (j, i) ;
								G_For = j ;
								break ;
							}
						}
					}
					}
				}
				else {
					pDoc -> P_Poly.GetAt ( M_Number ).Poly_point.RemoveAt ( PSkeleton ) ;
					P_Insert.Poly_point.RemoveAt ( PSkeleton ) ;

					P_CurrentPoint-- ;

					int Max_x = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (0).x ;
					int Min_x = Max_x ;
					int Max_y = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (0).y ;
					int Min_y = Max_y ;

					for ( int i = 1 ; i < pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetCount () ; i++ ) {
						if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).x > Max_x )
							Max_x = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).x ;
						else if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).x < Min_x )
							Min_x = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).x ;

						if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).y > Max_y )
							Max_y = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).y ;
						else if ( pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).y < Min_y )
							Min_y = pDoc -> P_Poly.GetAt ( P_Current ).Poly_point.GetAt (i).y ;
					}

					M_Rect.top = Min_y - pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;
					M_Rect.left = Min_x - pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;
					M_Rect.bottom = Max_y + pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;
					M_Rect.right = Max_x + pDoc -> P_Poly.GetAt ( P_Current ).thickness / 2 ;

					Invalidate () ;
					P_ChangeSkeleton = 0 ;
				}
			}
			else if ( M_What == _T ("E") ) {
				M_IsSelect = 'x' ;
				M_IsDraw = 'x' ;
				int location = pDoc -> E_Location.GetAt ( M_Number ) ;
				pDoc -> E_Ellipse.RemoveAt ( M_Number ) ;
				pDoc -> E_Count-- ;
				pDoc -> What.RemoveAt ( pDoc -> E_Location.GetAt ( M_Number ) ) ;
				pDoc -> E_Location.RemoveAt ( M_Number ) ;
				pDoc -> E_Color.RemoveAt ( M_Number ) ;
				pDoc -> E_FillColor.RemoveAt ( M_Number ) ;
				pDoc -> E_FillPattern.RemoveAt ( M_Number ) ;
				pDoc -> E_IsNoFill.RemoveAt ( M_Number ) ;
				pDoc -> E_LinePattern.RemoveAt ( M_Number ) ;
				pDoc -> E_Thickness.RemoveAt ( M_Number ) ;

				for ( int i = M_Number ; i < pDoc -> E_Ellipse.GetCount () ; i++ ) {
					pDoc -> E_Location.GetAt (i)-- ;
				}

				int R_For = 0 ;
				int P_For = 0 ;
				int L_For = 0 ;
				int T_For = 0 ;
				int RT_For = 0 ;
				int RightT_For = 0 ;
				int RRightT_For = 0 ;
				int LTRT_For = 0 ;
				int RTLT_For = 0 ;
				int Text_For = 0 ;
				int G_For = 0 ;

				for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
					if ( pDoc -> What.GetAt (i) == _T ("R") ) {
						for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
							if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
								pDoc -> R_Location.SetAt (j, i) ;
								R_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("P") ) {
						for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
							if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
								pDoc -> P_Location.SetAt (j, i) ;
								P_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("L") ) {
						for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
							if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
								pDoc -> L_Location.SetAt (j, i) ;
								L_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("T") ) {
						for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
							if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
								pDoc -> T_Location.SetAt (j, i) ;
								T_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
						for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
								pDoc -> RT_Location.SetAt (j, i) ;
								RT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
						for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RightT_Location.SetAt (j, i) ;
								RightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
						for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RRightT_Location.SetAt (j, i) ;
								RRightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
						for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
							if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
								pDoc -> LTRT_Location.SetAt (j, i) ;
								LTRT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
						for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
								pDoc -> RTLT_Location.SetAt (j, i) ;
								RTLT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
						for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
							if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
								pDoc -> Text_Location.SetAt (j, i) ;
								Text_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("G") ) {
						for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
							if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
								pDoc -> G_Location.SetAt (j, i) ;
								G_For = j ;
								break ;
							}
						}
					}
				}
				M_Number = 0 ;
			}
			else if ( M_What == _T ("T") ) {
				M_IsSelect = 'x' ;
				M_IsDraw = 'x' ;
				int location = pDoc -> T_Location.GetAt ( M_Number ) ;
				pDoc -> T_Triangle.RemoveAt ( M_Number ) ;
				pDoc -> T_Count-- ;
				pDoc -> What.RemoveAt ( pDoc -> T_Location.GetAt ( M_Number ) ) ;
				pDoc -> T_Location.RemoveAt ( M_Number ) ;
				pDoc -> T_Color.RemoveAt ( M_Number ) ;
				pDoc -> T_FillColor.RemoveAt ( M_Number ) ;
				pDoc -> T_FillPattern.RemoveAt ( M_Number ) ;
				pDoc -> T_IsNoFill.RemoveAt ( M_Number ) ;
				pDoc -> T_LinePattern.RemoveAt ( M_Number ) ;
				pDoc -> T_Thickness.RemoveAt ( M_Number ) ;

				for ( int i = M_Number ; i < pDoc -> T_Triangle.GetCount () ; i++ ) {
					pDoc -> T_Location.GetAt (i)-- ;
				}

				int R_For = 0 ;
				int P_For = 0 ;
				int E_For = 0 ;
				int L_For = 0 ;
				int RT_For = 0 ;
				int RightT_For = 0 ;
				int RRightT_For = 0 ;
				int LTRT_For = 0 ;
				int RTLT_For = 0 ;
				int Text_For = 0 ;
				int G_For = 0 ;

				for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
					if ( pDoc -> What.GetAt (i) == _T ("R") ) {
						for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
							if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
								pDoc -> R_Location.SetAt (j, i) ;
								R_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("P") ) {
						for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
							if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
								pDoc -> P_Location.SetAt (j, i) ;
								P_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("E") ) {
						for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
							if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
								pDoc -> E_Location.SetAt (j, i) ;
								E_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("L") ) {
						for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
							if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
								pDoc -> L_Location.SetAt (j, i) ;
								L_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
						for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
								pDoc -> RT_Location.SetAt (j, i) ;
								RT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
						for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RightT_Location.SetAt (j, i) ;
								RightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
						for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RRightT_Location.SetAt (j, i) ;
								RRightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
						for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
							if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
								pDoc -> LTRT_Location.SetAt (j, i) ;
								LTRT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
						for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
								pDoc -> RTLT_Location.SetAt (j, i) ;
								RTLT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
						for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
							if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
								pDoc -> Text_Location.SetAt (j, i) ;
								Text_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("G") ) {
						for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
							if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
								pDoc -> G_Location.SetAt (j, i) ;
								G_For = j ;
								break ;
							}
						}
					}
				}
				M_Number = 0 ;
			}
			else if ( M_What == _T ("RT") ) {
				M_IsSelect = 'x' ;
				M_IsDraw = 'x' ;
				int location = pDoc -> RT_Location.GetAt ( M_Number ) ;
				pDoc -> RT_Triangle.RemoveAt ( M_Number ) ;
				pDoc -> RT_Count-- ;
				pDoc -> What.RemoveAt ( pDoc -> RT_Location.GetAt ( M_Number ) ) ;
				pDoc -> RT_Location.RemoveAt ( M_Number ) ;
				pDoc -> RT_Color.RemoveAt ( M_Number ) ;
				pDoc -> RT_FillColor.RemoveAt ( M_Number ) ;
				pDoc -> RT_FillPattern.RemoveAt ( M_Number ) ;
				pDoc -> RT_IsNoFill.RemoveAt ( M_Number ) ;
				pDoc -> RT_LinePattern.RemoveAt ( M_Number ) ;
				pDoc -> RT_Thickness.RemoveAt ( M_Number ) ;

				for ( int i = M_Number ; i < pDoc -> RT_Triangle.GetCount () ; i++ ) {
					pDoc -> RT_Location.GetAt (i)-- ;
				}

				int R_For = 0 ;
				int P_For = 0 ;
				int E_For = 0 ;
				int T_For = 0 ;
				int L_For = 0 ;
				int RightT_For = 0 ;
				int RRightT_For = 0 ;
				int LTRT_For = 0 ;
				int RTLT_For = 0 ;
				int Text_For = 0 ;
				int G_For = 0 ;

				for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
					if ( pDoc -> What.GetAt (i) == _T ("R") ) {
						for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
							if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
								pDoc -> R_Location.SetAt (j, i) ;
								R_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("P") ) {
						for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
							if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
								pDoc -> P_Location.SetAt (j, i) ;
								P_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("E") ) {
						for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
							if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
								pDoc -> E_Location.SetAt (j, i) ;
								E_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("T") ) {
						for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
							if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
								pDoc -> T_Location.SetAt (j, i) ;
								T_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("L") ) {
						for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
							if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
								pDoc -> L_Location.SetAt (j, i) ;
								L_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
						for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RightT_Location.SetAt (j, i) ;
								RightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
						for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RRightT_Location.SetAt (j, i) ;
								RRightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
						for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
							if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
								pDoc -> LTRT_Location.SetAt (j, i) ;
								LTRT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
						for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
								pDoc -> RTLT_Location.SetAt (j, i) ;
								RTLT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
						for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
							if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
								pDoc -> Text_Location.SetAt (j, i) ;
								Text_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("G") ) {
						for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
							if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
								pDoc -> G_Location.SetAt (j, i) ;
								G_For = j ;
								break ;
							}
						}
					}
				}
				M_Number = 0 ;
			}
			else if ( M_What == _T ("RightT") ) {
				M_IsSelect = 'x' ;
				M_IsDraw = 'x' ;
				int location = pDoc -> RightT_Location.GetAt ( M_Number ) ;
				pDoc -> RightT_Triangle.RemoveAt ( M_Number ) ;
				pDoc -> RightT_Count-- ;
				pDoc -> What.RemoveAt ( pDoc -> RightT_Location.GetAt ( M_Number ) ) ;
				pDoc -> RightT_Location.RemoveAt ( M_Number ) ;
				pDoc -> RightT_Color.RemoveAt ( M_Number ) ;
				pDoc -> RightT_FillColor.RemoveAt ( M_Number ) ;
				pDoc -> RightT_FillPattern.RemoveAt ( M_Number ) ;
				pDoc -> RightT_IsNoFill.RemoveAt ( M_Number ) ;
				pDoc -> RightT_LinePattern.RemoveAt ( M_Number ) ;
				pDoc -> RightT_Thickness.RemoveAt ( M_Number ) ;

				for ( int i = M_Number ; i < pDoc -> RightT_Triangle.GetCount () ; i++ ) {
					pDoc -> RightT_Location.GetAt (i)-- ;
				}

				int R_For = 0 ;
				int P_For = 0 ;
				int E_For = 0 ;
				int T_For = 0 ;
				int RT_For = 0 ;
				int L_For = 0 ;
				int RRightT_For = 0 ;
				int LTRT_For = 0 ;
				int RTLT_For = 0 ;
				int Text_For = 0 ;
				int G_For = 0 ;

				for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
					if ( pDoc -> What.GetAt (i) == _T ("R") ) {
						for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
							if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
								pDoc -> R_Location.SetAt (j, i) ;
								R_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("P") ) {
						for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
							if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
								pDoc -> P_Location.SetAt (j, i) ;
								P_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("E") ) {
						for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
							if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
								pDoc -> E_Location.SetAt (j, i) ;
								E_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("T") ) {
						for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
							if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
								pDoc -> T_Location.SetAt (j, i) ;
								T_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
						for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
								pDoc -> RT_Location.SetAt (j, i) ;
								RT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("L") ) {
						for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
							if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
								pDoc -> L_Location.SetAt (j, i) ;
								L_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
						for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RRightT_Location.SetAt (j, i) ;
								RRightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
						for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
							if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
								pDoc -> LTRT_Location.SetAt (j, i) ;
								LTRT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
						for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
								pDoc -> RTLT_Location.SetAt (j, i) ;
								RTLT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
						for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
							if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
								pDoc -> Text_Location.SetAt (j, i) ;
								Text_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("G") ) {
						for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
							if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
								pDoc -> G_Location.SetAt (j, i) ;
								G_For = j ;
								break ;
							}
						}
					}
				}
				M_Number = 0 ;
			}
			else if ( M_What == _T ("RRightT") ) {
				M_IsSelect = 'x' ;
				M_IsDraw = 'x' ;
				int location = pDoc -> RRightT_Location.GetAt ( M_Number ) ;
				pDoc -> RRightT_Triangle.RemoveAt ( M_Number ) ;
				pDoc -> RRightT_Count-- ;
				pDoc -> What.RemoveAt ( pDoc -> RRightT_Location.GetAt ( M_Number ) ) ;
				pDoc -> RRightT_Location.RemoveAt ( M_Number ) ;
				pDoc -> RRightT_Color.RemoveAt ( M_Number ) ;
				pDoc -> RRightT_FillColor.RemoveAt ( M_Number ) ;
				pDoc -> RRightT_FillPattern.RemoveAt ( M_Number ) ;
				pDoc -> RRightT_IsNoFill.RemoveAt ( M_Number ) ;
				pDoc -> RRightT_LinePattern.RemoveAt ( M_Number ) ;
				pDoc -> RRightT_Thickness.RemoveAt ( M_Number ) ;

				for ( int i = M_Number ; i < pDoc -> RRightT_Triangle.GetCount () ; i++ ) {
					pDoc -> RRightT_Location.GetAt (i)-- ;
				}

				int R_For = 0 ;
				int P_For = 0 ;
				int E_For = 0 ;
				int T_For = 0 ;
				int RT_For = 0 ;
				int RightT_For = 0 ;
				int L_For = 0 ;
				int LTRT_For = 0 ;
				int RTLT_For = 0 ;
				int Text_For = 0 ;
				int G_For = 0 ;

				for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
					if ( pDoc -> What.GetAt (i) == _T ("R") ) {
						for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
							if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
								pDoc -> R_Location.SetAt (j, i) ;
								R_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("P") ) {
						for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
							if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
								pDoc -> P_Location.SetAt (j, i) ;
								P_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("E") ) {
						for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
							if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
								pDoc -> E_Location.SetAt (j, i) ;
								E_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("T") ) {
						for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
							if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
								pDoc -> T_Location.SetAt (j, i) ;
								T_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
						for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
								pDoc -> RT_Location.SetAt (j, i) ;
								RT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
						for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RightT_Location.SetAt (j, i) ;
								RightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("L") ) {
						for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
							if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
								pDoc -> L_Location.SetAt (j, i) ;
								L_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
						for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
							if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
								pDoc -> LTRT_Location.SetAt (j, i) ;
								LTRT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
						for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
								pDoc -> RTLT_Location.SetAt (j, i) ;
								RTLT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
						for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
							if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
								pDoc -> Text_Location.SetAt (j, i) ;
								Text_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("G") ) {
						for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
							if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
								pDoc -> G_Location.SetAt (j, i) ;
								G_For = j ;
								break ;
							}
						}
					}
				}
				M_Number = 0 ;
			}
			else if ( M_What == _T ("LTRT") ) {
				M_IsSelect = 'x' ;
				M_IsDraw = 'x' ;
				int location = pDoc -> LTRT_Location.GetAt ( M_Number ) ;
				pDoc -> LTRT_Triangle.RemoveAt ( M_Number ) ;
				pDoc -> LTRT_Count-- ;
				pDoc -> What.RemoveAt ( pDoc -> LTRT_Location.GetAt ( M_Number ) ) ;
				pDoc -> LTRT_Location.RemoveAt ( M_Number ) ;
				pDoc -> LTRT_Color.RemoveAt ( M_Number ) ;
				pDoc -> LTRT_FillColor.RemoveAt ( M_Number ) ;
				pDoc -> LTRT_FillPattern.RemoveAt ( M_Number ) ;
				pDoc -> LTRT_IsNoFill.RemoveAt ( M_Number ) ;
				pDoc -> LTRT_LinePattern.RemoveAt ( M_Number ) ;
				pDoc -> LTRT_Thickness.RemoveAt ( M_Number ) ;

				for ( int i = M_Number ; i < pDoc -> LTRT_Triangle.GetCount () ; i++ ) {
					pDoc -> LTRT_Location.GetAt (i)-- ;
				}

				int R_For = 0 ;
				int P_For = 0 ;
				int E_For = 0 ;
				int T_For = 0 ;
				int RT_For = 0 ;
				int RightT_For = 0 ;
				int RRightT_For = 0 ;
				int L_For = 0 ;
				int RTLT_For = 0 ;
				int Text_For = 0 ;
				int G_For = 0 ;

				for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
					if ( pDoc -> What.GetAt (i) == _T ("R") ) {
						for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
							if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
								pDoc -> R_Location.SetAt (j, i) ;
								R_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("P") ) {
						for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
							if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
								pDoc -> P_Location.SetAt (j, i) ;
								P_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("E") ) {
						for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
							if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
								pDoc -> E_Location.SetAt (j, i) ;
								E_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("T") ) {
						for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
							if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
								pDoc -> T_Location.SetAt (j, i) ;
								T_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
						for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
								pDoc -> RT_Location.SetAt (j, i) ;
								RT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
						for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RightT_Location.SetAt (j, i) ;
								RightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
						for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RRightT_Location.SetAt (j, i) ;
								RRightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("L") ) {
						for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
							if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
								pDoc -> L_Location.SetAt (j, i) ;
								L_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
						for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
								pDoc -> RTLT_Location.SetAt (j, i) ;
								RTLT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
						for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
							if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
								pDoc -> Text_Location.SetAt (j, i) ;
								Text_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("G") ) {
						for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
							if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
								pDoc -> G_Location.SetAt (j, i) ;
								G_For = j ;
								break ;
							}
						}
					}
				}
				M_Number = 0 ;
			}
			else if ( M_What == _T ("RTLT") ) {
				M_IsSelect = 'x' ;
				M_IsDraw = 'x' ;
				int location = pDoc -> RTLT_Location.GetAt ( M_Number ) ;
				pDoc -> RTLT_Triangle.RemoveAt ( M_Number ) ;
				pDoc -> RTLT_Count-- ;
				pDoc -> What.RemoveAt ( pDoc -> RTLT_Location.GetAt ( M_Number ) ) ;
				pDoc -> RTLT_Location.RemoveAt ( M_Number ) ;
				pDoc -> RTLT_Color.RemoveAt ( M_Number ) ;
				pDoc -> RTLT_FillColor.RemoveAt ( M_Number ) ;
				pDoc -> RTLT_FillPattern.RemoveAt ( M_Number ) ;
				pDoc -> RTLT_IsNoFill.RemoveAt ( M_Number ) ;
				pDoc -> RTLT_LinePattern.RemoveAt ( M_Number ) ;
				pDoc -> RTLT_Thickness.RemoveAt ( M_Number ) ;

				for ( int i = M_Number ; i < pDoc -> RTLT_Triangle.GetCount () ; i++ ) {
					pDoc -> RTLT_Location.GetAt (i)-- ;
				}

				int R_For = 0 ;
				int P_For = 0 ;
				int E_For = 0 ;
				int T_For = 0 ;
				int RT_For = 0 ;
				int RightT_For = 0 ;
				int RRightT_For = 0 ;
				int LTRT_For = 0 ;
				int L_For = 0 ;
				int Text_For = 0 ;
				int G_For = 0 ;

				for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
					if ( pDoc -> What.GetAt (i) == _T ("R") ) {
						for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
							if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
								pDoc -> R_Location.SetAt (j, i) ;
								R_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("P") ) {
						for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
							if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
								pDoc -> P_Location.SetAt (j, i) ;
								P_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("E") ) {
						for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
							if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
								pDoc -> E_Location.SetAt (j, i) ;
								E_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("T") ) {
						for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
							if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
								pDoc -> T_Location.SetAt (j, i) ;
								T_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
						for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
								pDoc -> RT_Location.SetAt (j, i) ;
								RT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
						for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RightT_Location.SetAt (j, i) ;
								RightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
						for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RRightT_Location.SetAt (j, i) ;
								RRightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
						for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
							if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
								pDoc -> LTRT_Location.SetAt (j, i) ;
								LTRT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("L") ) {
						for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
							if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
								pDoc -> L_Location.SetAt (j, i) ;
								L_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
						for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
							if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
								pDoc -> Text_Location.SetAt (j, i) ;
								Text_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("G") ) {
						for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
							if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
								pDoc -> G_Location.SetAt (j, i) ;
								G_For = j ;
								break ;
							}
						}
					}
				}
				M_Number = 0 ;
			}
			else if ( M_What == _T ("Text") ) {
				M_IsSelect = 'x' ;
				M_IsDraw = 'x' ;
				int location = pDoc -> Text_Location.GetAt ( M_Number ) ;
				pDoc -> Text_Text.RemoveAt ( M_Number ) ;
				pDoc -> Text_Count-- ;
				pDoc -> Text_Text.SetSize ( pDoc -> Text_Count ) ;
				pDoc -> What.RemoveAt ( pDoc -> Text_Location.GetAt ( M_Number ) ) ;
				pDoc -> Text_Location.RemoveAt ( M_Number ) ;

				for ( int i = M_Number ; i < pDoc -> Text_Text.GetCount () ; i++ ) {
					pDoc -> Text_Location.GetAt (i)-- ;
				}

				int R_For = 0 ;
				int P_For = 0 ;
				int E_For = 0 ;
				int T_For = 0 ;
				int RT_For = 0 ;
				int RightT_For = 0 ;
				int RRightT_For = 0 ;
				int LTRT_For = 0 ;
				int L_For = 0 ;
				int RTLT_For = 0 ;
				int G_For = 0 ;

				for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
					if ( pDoc -> What.GetAt (i) == _T ("R") ) {
						for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
							if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
								pDoc -> R_Location.SetAt (j, i) ;
								R_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("P") ) {
						for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
							if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
								pDoc -> P_Location.SetAt (j, i) ;
								P_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("E") ) {
						for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
							if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
								pDoc -> E_Location.SetAt (j, i) ;
								E_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("T") ) {
						for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
							if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
								pDoc -> T_Location.SetAt (j, i) ;
								T_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
						for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
								pDoc -> RT_Location.SetAt (j, i) ;
								RT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
						for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RightT_Location.SetAt (j, i) ;
								RightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
						for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RRightT_Location.SetAt (j, i) ;
								RRightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
						for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
							if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
								pDoc -> LTRT_Location.SetAt (j, i) ;
								LTRT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("L") ) {
						for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
							if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
								pDoc -> L_Location.SetAt (j, i) ;
								L_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
						for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
								pDoc -> RTLT_Location.SetAt (j, i) ;
								RTLT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("G") ) {
						for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
							if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
								pDoc -> G_Location.SetAt (j, i) ;
								G_For = j ;
								break ;
							}
						}
					}
				}
			}
			// 그룹화 객체를 삭제하는 경우
			else if ( M_What == _T ("G") ) {
				M_IsSelect = 'x' ;
				M_IsDraw = 'x' ;
				int location = pDoc -> G_Location.GetAt ( M_Number ) ;
				pDoc -> G_Group.RemoveAt ( M_Number ) ;
				pDoc -> G_Count-- ;
				pDoc -> G_Group.SetSize ( pDoc -> G_Count ) ;
				pDoc -> What.RemoveAt ( pDoc -> G_Location.GetAt ( M_Number ) ) ;
				pDoc -> G_Location.RemoveAt ( M_Number ) ;

				for ( int i = M_Number ; i < pDoc -> G_Group.GetCount () ; i++ ) {
					pDoc -> G_Location.GetAt (i)-- ;
				}

				int R_For = 0 ;
				int P_For = 0 ;
				int E_For = 0 ;
				int T_For = 0 ;
				int RT_For = 0 ;
				int RightT_For = 0 ;
				int RRightT_For = 0 ;
				int LTRT_For = 0 ;
				int L_For = 0 ;
				int RTLT_For = 0 ;
				int Text_For = 0 ;

				for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
					if ( pDoc -> What.GetAt (i) == _T ("R") ) {
						for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
							if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
								pDoc -> R_Location.SetAt (j, i) ;
								R_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("P") ) {
						for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
							if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
								pDoc -> P_Location.SetAt (j, i) ;
								P_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("E") ) {
						for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
							if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
								pDoc -> E_Location.SetAt (j, i) ;
								E_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("T") ) {
						for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
							if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
								pDoc -> T_Location.SetAt (j, i) ;
								T_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
						for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
								pDoc -> RT_Location.SetAt (j, i) ;
								RT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
						for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RightT_Location.SetAt (j, i) ;
								RightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
						for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
								pDoc -> RRightT_Location.SetAt (j, i) ;
								RRightT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
						for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
							if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
								pDoc -> LTRT_Location.SetAt (j, i) ;
								LTRT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("L") ) {
						for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
							if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
								pDoc -> L_Location.SetAt (j, i) ;
								L_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
						for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
							if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
								pDoc -> RTLT_Location.SetAt (j, i) ;
								RTLT_For = j ;
								break ;
							}
						}
					}
					else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
						for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
							if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
								pDoc -> Text_Location.SetAt (j, i) ;
								Text_For = j ;
								break ;
							}
						}
					}
				}
			}

			Invalidate () ;
		}
	}

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Text를 입력 중인 경우
	if ( (Text_IsText == 'o' && Text_IsKeyDown == 'o') || Text_IsChange == 'o' ) {

		if ( Text_IsChange == 'o' ) {
			// 백 스페이스를 누르는 경우
			if ( nChar == VK_BACK )
				pDoc -> Text_Text.GetAt ( M_Number ).Text.Delete ( pDoc -> Text_Text.GetAt ( M_Number ).Text.GetLength () - 1 ) ;
			// esc나 엔터를 누르는 경우
			else if ( nChar == VK_ESCAPE || nChar == VK_RETURN ) {
				Text_IsKeyDown = 'x' ;
				Text_IsChange = 'x' ;
				HideCaret () ;
			}
			// TAB을 누르면 8번 띄어쓰기 효과를 가집니다.
			else if ( nChar == VK_TAB ) {
				pDoc -> Text_Text.GetAt ( M_Number ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( M_Number ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( M_Number ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( M_Number ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( M_Number ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( M_Number ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( M_Number ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( M_Number ).Text.AppendChar ( VK_SPACE ) ;
			}
			// 일반적인 경우는 해당 키를 그대로 출력합니다.
			else
				pDoc -> Text_Text.GetAt ( M_Number ).Text.AppendChar ( nChar ) ;
		}
		else {
			// 백 스페이스를 누르는 경우
			if ( nChar == VK_BACK )
				pDoc -> Text_Text.GetAt ( Text_Current ).Text.Delete ( pDoc -> Text_Text.GetAt ( Text_Current ).Text.GetLength () - 1 ) ;
			// esc나 엔터를 누르는 경우
			else if ( nChar == VK_ESCAPE || nChar == VK_RETURN ) {
				Text_IsKeyDown = 'x' ;
				HideCaret () ;
			}
			// TAB을 누르면 8번 띄어쓰기 효과를 가집니다.
			else if ( nChar == VK_TAB ) {
				pDoc -> Text_Text.GetAt ( Text_Current ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( Text_Current ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( Text_Current ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( Text_Current ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( Text_Current ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( Text_Current ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( Text_Current ).Text.AppendChar ( VK_SPACE ) ;
				pDoc -> Text_Text.GetAt ( Text_Current ).Text.AppendChar ( VK_SPACE ) ;
			}
			// 일반적인 경우는 해당 키를 그대로 출력합니다.
			else
				pDoc -> Text_Text.GetAt ( Text_Current ).Text.AppendChar ( nChar ) ;
		}

		Invalidate () ;
	}
	else if ( Text_IsText == 'o' && Text_IsKeyDown == 'x' && nChar == VK_ESCAPE ) {
		HideCaret () ;
		Text_IsKeyDown = 'x' ;
		Text_IsText = 'x' ;
		IsNormal = 'o' ;
	}
	
	CScrollView::OnChar(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnFillpattern()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFillPattern dlg ;

	if ( M_IsDraw != 'o' ) {
		if( dlg.DoModal() == IDOK )
		{
			m_IsFillPattern = 'o' ;
			m_FillPattern = dlg.GetPattern () ;
		}
	}
	else {
		if( dlg.DoModal() == IDOK )
		{
			m_IsFillPattern = 'o' ;
			m_FillPattern = dlg.GetPattern () ;
			if ( M_What == _T("R") )
				pDoc -> R_FillPattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("E") )
				pDoc -> E_FillPattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("T") )
				pDoc -> T_FillPattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("RT") )
				pDoc -> RT_FillPattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("RightT") )
				pDoc -> RightT_FillPattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("RRightT") )
				pDoc -> RRightT_FillPattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("LTRT") )
				pDoc -> LTRT_FillPattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("RTLT") )
				pDoc -> RTLT_FillPattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("G") ) {

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).E_FillPattern.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).E_FillPattern.GetAt (i) = dlg.GetPattern () ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).R_FillPattern.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).R_FillPattern.GetAt (i) = dlg.GetPattern () ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Index.GetCount () ; i++ ) {

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_FillPattern.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_FillPattern.GetAt (j) = dlg.GetPattern () ;
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_FillColor.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_FillColor.GetAt (j) = dlg.GetPattern () ;
					}
				}
			}

			Invalidate () ;
		}
	}
}

void CGraphicEditorView::OnLinepattern()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	LinePattern dlg ;

	if ( M_IsDraw != 'o' ) {
		if( dlg.DoModal() == IDOK )
		{
			m_IsLinePattern = 'o' ;
			m_LinePattern = dlg.GetPattern () ;

		}
	}
	else {
		if( dlg.DoModal() == IDOK )
		{
			m_IsLinePattern = 'o' ;
			m_LinePattern = dlg.GetPattern () ;
			if ( M_What == _T("R") )
				pDoc -> R_LinePattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("L") )
				pDoc -> L_Line.GetAt ( M_Number ).Pattern = dlg.GetPattern () ;
			else if ( M_What == _T("P") )
				pDoc -> P_Poly.GetAt ( M_Number ).Pattern = dlg.GetPattern () ;
			else if ( M_What == _T("E") )
				pDoc -> E_LinePattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("T") )
				pDoc -> T_LinePattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("RT") )
				pDoc -> RT_LinePattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("RightT") )
				pDoc -> RightT_LinePattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("RRightT") )
				pDoc -> RRightT_LinePattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("LTRT") )
				pDoc -> LTRT_LinePattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("RTLT") )
				pDoc -> RTLT_LinePattern.GetAt ( M_Number ) = dlg.GetPattern () ;
			else if ( M_What == _T("G") ) {

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Line.GetCount () ; i ++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).Line.GetAt (i).Pattern = dlg.GetPattern () ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Poly.GetCount () ; i ++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).Poly.GetAt (i).Pattern = dlg.GetPattern () ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).E_LinePattern.GetCount () ; i ++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).E_LinePattern.GetAt (i) = dlg.GetPattern () ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).R_LinePattern.GetCount () ; i ++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).R_LinePattern.GetAt (i) = dlg.GetPattern () ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Index.GetCount () ; i++ ) {

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Line.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Line.GetAt (j).Pattern = dlg.GetPattern () ;
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Poly.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Poly.GetAt (j).Pattern = dlg.GetPattern () ;
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_LinePattern.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).E_LinePattern.GetAt (j) = dlg.GetPattern () ;
					}

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_LinePattern.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).R_LinePattern.GetAt (j) = dlg.GetPattern () ;
					}
				}
			}

			Invalidate () ;
		}
	}
}

void CGraphicEditorView::OnTextbgcolor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CColorDialog dlgColor(0, CC_FULLOPEN, NULL) ;
	
	if ( M_IsDraw != 'o' ) {
		if( dlgColor.DoModal() == IDOK ) {
			Text_IsBGColor = 'o' ;
			Text_BGColor = dlgColor.GetColor () ;
		}
	}
	else {
		if( dlgColor.DoModal() == IDOK ) {
			Text_IsBGColor = 'o' ;
			Text_BGColor = dlgColor.GetColor () ;

			if ( M_What == _T("Text") ) {
				pDoc -> Text_Text.GetAt ( M_Number ).IsNoFill = 'x' ;
				pDoc -> Text_Text.GetAt ( M_Number ).BGColor = Text_BGColor ;	
			}
			else if ( M_What == _T("G") ) {

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Text.GetCount () ; i++ ) {
					pDoc -> G_Group.GetAt ( M_Number ).Text.GetAt (i).BGColor = Text_BGColor ;
					pDoc -> G_Group.GetAt ( M_Number ).Text.GetAt (i).IsNoFill = 'x' ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Index.GetCount () ; i++ ) {

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetCount () ; j++ ) {
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetAt (j).BGColor = Text_BGColor ;
						pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetAt (j).IsNoFill = 'x' ;
					}
				}
			}

			Invalidate () ;

			if ( M_What == _T("G") ) {
				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Text.GetCount () ; i++ ) {
					if ( pDoc -> G_Group.GetAt ( M_Number ).Text.GetAt (i).Text_Rect.top < pDoc -> G_Group.GetAt ( M_Number ).GroupBox.top )
						pDoc -> G_Group.GetAt ( M_Number ).GroupBox.top = pDoc -> G_Group.GetAt ( M_Number ).Text.GetAt (i).Text_Rect.top - 5 ;
					if ( pDoc -> G_Group.GetAt ( M_Number ).Text.GetAt (i).Text_Rect.bottom > pDoc -> G_Group.GetAt ( M_Number ).GroupBox.bottom )
						pDoc -> G_Group.GetAt ( M_Number ).GroupBox.bottom = pDoc -> G_Group.GetAt ( M_Number ).Text.GetAt (i).Text_Rect.bottom + 5 ;
					if ( pDoc -> G_Group.GetAt ( M_Number ).Text.GetAt (i).Text_Rect.left < pDoc -> G_Group.GetAt ( M_Number ).GroupBox.left )
						pDoc -> G_Group.GetAt ( M_Number ).GroupBox.left = pDoc -> G_Group.GetAt ( M_Number ).Text.GetAt (i).Text_Rect.left - 5 ;
					if ( pDoc -> G_Group.GetAt ( M_Number ).Text.GetAt (i).Text_Rect.right > pDoc -> G_Group.GetAt ( M_Number ).GroupBox.right )
						pDoc -> G_Group.GetAt ( M_Number ).GroupBox.right = pDoc -> G_Group.GetAt ( M_Number ).Text.GetAt (i).Text_Rect.right + 5 ;
				}

				for ( int i = 0 ; i < pDoc -> G_Group.GetAt ( M_Number ).Index.GetCount () ; i++ ) {

					for ( int j = 0 ; j < pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetCount () ; j++ ) {
						if ( pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetAt (j).Text_Rect.top < pDoc -> G_Group.GetAt ( M_Number ).GroupBox.top )
							pDoc -> G_Group.GetAt ( M_Number ).GroupBox.top = pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetAt (j).Text_Rect.top - 5 ;
						if ( pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetAt (j).Text_Rect.bottom > pDoc -> G_Group.GetAt ( M_Number ).GroupBox.bottom )
							pDoc -> G_Group.GetAt ( M_Number ).GroupBox.bottom = pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetAt (j).Text_Rect.bottom + 5 ;
						if ( pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetAt (j).Text_Rect.left < pDoc -> G_Group.GetAt ( M_Number ).GroupBox.left )
							pDoc -> G_Group.GetAt ( M_Number ).GroupBox.left = pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetAt (j).Text_Rect.left - 5 ;
						if ( pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetAt (j).Text_Rect.right > pDoc -> G_Group.GetAt ( M_Number ).GroupBox.right )
							pDoc -> G_Group.GetAt ( M_Number ).GroupBox.right = pDoc -> G_InGroup.GetAt ( pDoc -> G_Group.GetAt ( M_Number ).Index.GetAt (i) ).Text.GetAt (j).Text_Rect.right + 5 ;
					}
				}

				Invalidate () ;
			}
		}
	}
}

void CGraphicEditorView::OnGroup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if ( G_IsMakeGroup == 'o' ) {
		G_Current = pDoc -> G_Count ;
		pDoc -> G_Group.SetSize ( pDoc -> G_Count + 1 ) ;

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
		int G_Number = 0 ;
		int P_Find = 0 ;
		int flag = 0 ;

		G_FindCount = 0 ;

		for ( int i = 0 ; i < pDoc -> What.GetCount () ; i++ ) {
			if ( pDoc -> What.GetAt (i) == _T ("L") ) {
				if ( pDoc -> L_Line.GetAt ( L_Number ).Start.x >= G_Include.left && pDoc -> L_Line.GetAt ( L_Number ).Start.x <= G_Include.right &&
					pDoc -> L_Line.GetAt ( L_Number ).Last.x >= G_Include.left && pDoc -> L_Line.GetAt ( L_Number ).Last.x <= G_Include.right &&
					pDoc -> L_Line.GetAt ( L_Number ).Start.y >= G_Include.top && pDoc -> L_Line.GetAt ( L_Number ).Start.y <= G_Include.bottom &&
					pDoc -> L_Line.GetAt ( L_Number ).Last.y >= G_Include.top && pDoc -> L_Line.GetAt ( L_Number ).Last.y <= G_Include.bottom ) {

						flag++ ;
				}
				L_Number++ ;
			}
			else if ( pDoc -> What.GetAt (i) == _T ("P") ) {
				int j ;
				for ( j = 0 ; j < pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetCount () ; j++ ) {
					if ( pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (j).x < G_Include.left || pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (j).x > G_Include.right ||
						pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (j).y < G_Include.top || pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (j).y > G_Include.bottom )
						break ;
				}

				if ( j == pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetCount () ) {
					flag++ ;
				}
				P_Number++ ;
			}
			else if ( pDoc -> What.GetAt (i) == _T ("R") ) {
				if ( pDoc -> R_Rec.GetAt ( R_Number ).top >= G_Include.top && pDoc -> R_Rec.GetAt ( R_Number ).bottom <= G_Include.bottom &&
					pDoc -> R_Rec.GetAt ( R_Number ).left >= G_Include.left && pDoc -> R_Rec.GetAt ( R_Number ).right <= G_Include.right ) {
						flag++ ;
				}
				R_Number++ ;
			}
			else if ( pDoc -> What.GetAt (i) == _T ("E") ) {
				if ( pDoc -> E_Ellipse.GetAt ( E_Number ).top >= G_Include.top && pDoc -> E_Ellipse.GetAt ( E_Number ).bottom <= G_Include.bottom &&
					pDoc -> E_Ellipse.GetAt ( E_Number ).left >= G_Include.left && pDoc -> E_Ellipse.GetAt ( E_Number ).right <= G_Include.right ) {
						flag++ ;
				}
				E_Number++;
			}
			else if ( pDoc -> What.GetAt (i) == _T ("Text") ) {
				if ( pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.top >= G_Include.top && pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.bottom <= G_Include.bottom &&
					pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.left >= G_Include.left && pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.right <= G_Include.right ) {
						flag++ ;
				}
				Text_Number++ ;
			}
			else if ( pDoc -> What.GetAt (i) == _T("G") ) {
				if ( pDoc -> G_Group.GetAt ( G_Number ).GroupBox.top >= G_Include.top && pDoc -> G_Group.GetAt ( G_Number ).GroupBox.bottom <= G_Include.bottom &&
					pDoc -> G_Group.GetAt ( G_Number ).GroupBox.left >= G_Include.left && pDoc -> G_Group.GetAt ( G_Number ).GroupBox.right <= G_Include.right ) {
						flag++ ;
				}
				G_Number++ ;
			}

			if ( flag == 2 )
				break ;

		}

		L_Number = 0 ;
		R_Number = 0 ;
		P_Number = 0 ;
		E_Number = 0 ;
		T_Number = 0 ;
		RT_Number = 0 ;
		RightT_Number = 0 ;
		RRightT_Number = 0 ;
		LTRT_Number = 0 ;
		RTLT_Number = 0 ;
		Text_Number = 0 ;
		G_Number = 0 ;

		if ( flag == 2 ) {
			for ( int i = 0 ; i < pDoc -> What.GetCount () ; i++ ) {
				if ( pDoc -> What.GetAt (i) == _T ("L") ) {
					if ( pDoc -> L_Line.GetAt ( L_Number ).Start.x >= G_Include.left && pDoc -> L_Line.GetAt ( L_Number ).Start.x <= G_Include.right &&
						pDoc -> L_Line.GetAt ( L_Number ).Last.x >= G_Include.left && pDoc -> L_Line.GetAt ( L_Number ).Last.x <= G_Include.right &&
						pDoc -> L_Line.GetAt ( L_Number ).Start.y >= G_Include.top && pDoc -> L_Line.GetAt ( L_Number ).Start.y <= G_Include.bottom &&
						pDoc -> L_Line.GetAt ( L_Number ).Last.y >= G_Include.top && pDoc -> L_Line.GetAt ( L_Number ).Last.y <= G_Include.bottom ) {

							pDoc -> G_Group.GetAt ( G_Current ).Line.Add ( pDoc -> L_Line.GetAt ( L_Number ) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).What.Add ( _T ("L") ) ;
							pDoc -> G_Group.GetAt ( G_Current ).L_Count++ ;

							if ( G_FindCount == 0 ) {
								if ( pDoc -> L_Line.GetAt ( L_Number ).Start.x >= pDoc -> L_Line.GetAt ( L_Number ).Last.x ) {
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = pDoc -> L_Line.GetAt ( L_Number ).Last.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = pDoc -> L_Line.GetAt ( L_Number ).Start.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}
								else {
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = pDoc -> L_Line.GetAt ( L_Number ).Start.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = pDoc -> L_Line.GetAt ( L_Number ).Last.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}

								if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y >= pDoc -> L_Line.GetAt ( L_Number ).Last.y ) {
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = pDoc -> L_Line.GetAt ( L_Number ).Last.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = pDoc -> L_Line.GetAt ( L_Number ).Start.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}
								else {
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = pDoc -> L_Line.GetAt ( L_Number ).Start.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = pDoc -> L_Line.GetAt ( L_Number ).Last.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								}
							}
							else {
								if ( pDoc -> L_Line.GetAt ( L_Number ).Start.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 > pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = pDoc -> L_Line.GetAt ( L_Number ).Start.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								else if ( pDoc -> L_Line.GetAt ( L_Number ).Start.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 < pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = pDoc -> L_Line.GetAt ( L_Number ).Start.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;

								if ( pDoc -> L_Line.GetAt ( L_Number ).Last.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 > pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = pDoc -> L_Line.GetAt ( L_Number ).Last.x + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								else if ( pDoc -> L_Line.GetAt ( L_Number ).Last.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 < pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = pDoc -> L_Line.GetAt ( L_Number ).Last.x - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;

								if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 > pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = pDoc -> L_Line.GetAt ( L_Number ).Start.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								else if ( pDoc -> L_Line.GetAt ( L_Number ).Start.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 < pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = pDoc -> L_Line.GetAt ( L_Number ).Start.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;

								if ( pDoc -> L_Line.GetAt ( L_Number ).Last.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 > pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = pDoc -> L_Line.GetAt ( L_Number ).Last.y + pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
								else if ( pDoc -> L_Line.GetAt ( L_Number ).Last.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 < pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = pDoc -> L_Line.GetAt ( L_Number ).Last.y - pDoc -> L_Line.GetAt ( L_Number ).Thickness / 2 ;
							}
							G_FindCount++ ;

							pDoc -> L_Line.RemoveAt ( L_Number ) ;
							int location = pDoc -> L_Location.GetAt ( L_Number ) ;
							pDoc -> L_Count-- ;
							pDoc -> What.RemoveAt ( pDoc -> L_Location.GetAt ( L_Number ) ) ;
							pDoc -> L_Location.RemoveAt ( L_Number ) ;

							for ( int i = L_Number ; i < pDoc -> L_Line.GetCount () ; i++ ) {
								pDoc -> L_Location.GetAt (i)-- ;
							}
							int R_For = 0 ;
							int P_For = 0 ;
							int E_For = 0 ;
							int T_For = 0 ;
							int RT_For = 0 ;
							int RightT_For = 0 ;
							int RRightT_For = 0 ;
							int LTRT_For = 0 ;
							int RTLT_For = 0 ;
							int Text_For = 0 ;
							int G_For = 0 ;

							for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
								if ( pDoc -> What.GetAt (i) == _T ("R") ) {
									for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
										if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
											pDoc -> R_Location.SetAt (j, i) ;
											R_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("P") ) {
									for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
										if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
											pDoc -> P_Location.SetAt (j, i) ;
											P_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("E") ) {
									for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
										if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
											pDoc -> E_Location.SetAt (j, i) ;
											E_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("T") ) {
									for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
										if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
											pDoc -> T_Location.SetAt (j, i) ;
											T_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
									for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
											pDoc -> RT_Location.SetAt (j, i) ;
											RT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
									for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
											pDoc -> RightT_Location.SetAt (j, i) ;
											RightT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
									for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
											pDoc -> RRightT_Location.SetAt (j, i) ;
											RRightT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
									for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
										if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
											pDoc -> LTRT_Location.SetAt (j, i) ;
											LTRT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
									for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
											pDoc -> RTLT_Location.SetAt (j, i) ;
											RTLT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
									for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
										if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
											pDoc -> Text_Location.SetAt (j, i) ;
											Text_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("G") ) {
									for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
										if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
											pDoc -> G_Location.SetAt (j, i) ;
											G_For = j ;
											break ;
										}
									}
								}
							}
							i-- ;
							L_Number-- ;
					}
					L_Number++ ;
				}
				else if ( pDoc -> What.GetAt (i) == _T ("P") ) {

					int j ;
					for ( j = 0 ; j < pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetCount () ; j++ ) {
						if ( pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (j).x < G_Include.left || pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (j).x > G_Include.right ||
							pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (j).y < G_Include.top || pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (j).y > G_Include.bottom )
							break ;
					}

					if ( j == pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetCount () ) {
						pDoc -> G_Group.GetAt ( G_Current ).What.Add ( _T ("P") ) ;
						pDoc -> G_Group.GetAt ( G_Current ).Poly.SetSize (P_Find+1) ;
						pDoc -> G_Group.GetAt ( G_Current ).Poly.GetAt (P_Find).Poly_point.SetSize (j) ;

						int Max_x = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (0).x ;
						int Max_y = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (0).y ;
						int Min_x = Max_x ;
						int Min_y = Max_y ;

						for ( int k = 0 ; k < j ; k++ ) {
							pDoc -> G_Group.GetAt ( G_Current ).Poly.GetAt (P_Find).Poly_point.SetAt (k, pDoc -> P_Poly.GetAt (P_Number).Poly_point.GetAt(k)) ;

							if ( Max_x < pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (k).x )
								Max_x = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (k).x ;
							else if ( Min_x > pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (k).x )
								Min_x = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (k).x ;

							if ( Max_y < pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (k).y )
								Max_y = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (k).y ;
							else if ( Min_y > pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (k).y )
								Min_y = pDoc -> P_Poly.GetAt ( P_Number ).Poly_point.GetAt (k).y ;
						}
						pDoc -> G_Group.GetAt ( G_Current ).Poly.GetAt (P_Find).Pattern = pDoc -> P_Poly.GetAt (P_Number).Pattern ;
						pDoc -> G_Group.GetAt ( G_Current ).Poly.GetAt (P_Find).P_Color = pDoc -> P_Poly.GetAt (P_Number).P_Color ;
						pDoc -> G_Group.GetAt ( G_Current ).Poly.GetAt (P_Find).thickness = pDoc -> P_Poly.GetAt (P_Number).thickness ;
						pDoc -> G_Group.GetAt ( G_Current ).P_Count++ ;

						if ( G_FindCount == 0 ) {
							pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = Min_y - pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 ;
							pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = Max_y + pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 ;
							pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = Min_x - pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 ;
							pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = Max_x + pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 ;
						}
						else {
							if ( Min_x - pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 < pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left )
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = Min_x - pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 ;
							if ( Max_x + pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 > pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right )
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = Max_x + pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 ;
							if ( Max_y + pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 > pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom )
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = Max_y + pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 ;
							if ( Min_y - pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 < pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top )
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = Min_y - pDoc -> P_Poly.GetAt ( P_Number ).thickness / 2 ;
						}
						G_FindCount++ ;

						int location = pDoc -> P_Location.GetAt ( P_Number ) ;
						pDoc -> P_Poly.RemoveAt ( P_Number ) ;
						pDoc -> P_Count-- ;
						pDoc -> What.RemoveAt ( pDoc -> P_Location.GetAt ( P_Number ) ) ;
						pDoc -> P_Location.RemoveAt ( P_Number ) ;
						for ( int i = P_Number ; i < pDoc -> P_Poly.GetCount () ; i++ ) {
							pDoc -> P_Location.GetAt (i)-- ;
						}

						int R_For = 0 ;
						int L_For = 0 ;
						int E_For = 0 ;
						int T_For = 0 ;
						int RT_For = 0 ;
						int RightT_For = 0 ;
						int RRightT_For = 0 ;
						int LTRT_For = 0 ;
						int RTLT_For = 0 ;
						int Text_For = 0 ;
						int G_For = 0 ;

						for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
							if ( pDoc -> What.GetAt (i) == _T ("R") ) {
								for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
									if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
										pDoc -> R_Location.SetAt (j, i) ;
										R_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("L") ) {
								for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
									if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
										pDoc -> L_Location.SetAt (j, i) ;
										L_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("E") ) {
								for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
									if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
										pDoc -> E_Location.SetAt (j, i) ;
										E_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("T") ) {
								for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
									if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
										pDoc -> T_Location.SetAt (j, i) ;
										T_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
								for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
									if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
										pDoc -> RT_Location.SetAt (j, i) ;
										RT_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
								for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
									if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
										pDoc -> RightT_Location.SetAt (j, i) ;
										RightT_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
								for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
									if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
										pDoc -> RRightT_Location.SetAt (j, i) ;
										RRightT_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
								for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
									if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
										pDoc -> LTRT_Location.SetAt (j, i) ;
										LTRT_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
								for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
									if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
										pDoc -> RTLT_Location.SetAt (j, i) ;
										RTLT_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
								for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
									if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
										pDoc -> Text_Location.SetAt (j, i) ;
										Text_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("G") ) {
								for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
									if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
										pDoc -> G_Location.SetAt (j, i) ;
										G_For = j ;
										break ;
									}
								}
							}
						}
						P_Find++ ;
						i-- ;
						P_Number-- ;
					}
					P_Number++ ;
				}
				else if ( pDoc -> What.GetAt (i) == _T ("R") ) {
					if ( pDoc -> R_Rec.GetAt ( R_Number ).top >= G_Include.top && pDoc -> R_Rec.GetAt ( R_Number ).bottom <= G_Include.bottom &&
						pDoc -> R_Rec.GetAt ( R_Number ).left >= G_Include.left && pDoc -> R_Rec.GetAt ( R_Number ).right <= G_Include.right ) {

							pDoc -> G_Group.GetAt ( G_Current ).Rect.Add ( pDoc -> R_Rec.GetAt ( R_Number ) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).R_Color.Add ( pDoc -> R_Color.GetAt (R_Number) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).R_FillColor.Add ( pDoc -> R_FillColor.GetAt (R_Number) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).R_Count++ ;
							pDoc -> G_Group.GetAt ( G_Current ).R_IsNoFill.Add ( pDoc -> R_IsNoFill.GetAt (R_Number) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).R_FillPattern.Add ( pDoc -> R_FillPattern.GetAt (R_Number) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).R_LinePattern.Add ( pDoc -> R_LinePattern.GetAt (R_Number) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).R_Thickness.Add ( pDoc -> R_Thickness.GetAt (R_Number) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).What.Add ( _T ("R") ) ;

							if ( G_FindCount == 0 ) {
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = pDoc -> R_Rec.GetAt ( R_Number ).top - pDoc -> R_Thickness.GetAt (R_Number) / 2 ;
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = pDoc -> R_Rec.GetAt ( R_Number ).bottom + pDoc -> R_Thickness.GetAt (R_Number) / 2 ;
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = pDoc -> R_Rec.GetAt ( R_Number ).left - pDoc -> R_Thickness.GetAt (R_Number) / 2 ;
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = pDoc -> R_Rec.GetAt ( R_Number ).right + pDoc -> R_Thickness.GetAt (R_Number) / 2 ;
							}
							else {
								if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top > pDoc -> R_Rec.GetAt ( R_Number ).top - pDoc -> R_Thickness.GetAt (R_Number) / 2 )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = pDoc -> R_Rec.GetAt ( R_Number ).top - pDoc -> R_Thickness.GetAt (R_Number) / 2 ;
								if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom < pDoc -> R_Rec.GetAt ( R_Number ).bottom + pDoc -> R_Thickness.GetAt (R_Number) / 2 )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = pDoc -> R_Rec.GetAt ( R_Number ).bottom + pDoc -> R_Thickness.GetAt (R_Number) / 2 ;
								if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left > pDoc -> R_Rec.GetAt ( R_Number ).left - pDoc -> R_Thickness.GetAt (R_Number) / 2 )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = pDoc -> R_Rec.GetAt ( R_Number ).left - pDoc -> R_Thickness.GetAt (R_Number) / 2 ;
								if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right < pDoc -> R_Rec.GetAt ( R_Number ).right + pDoc -> R_Thickness.GetAt (R_Number) / 2 )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = pDoc -> R_Rec.GetAt ( R_Number ).right + pDoc -> R_Thickness.GetAt (R_Number) / 2 ;
							}
							G_FindCount++ ;

							pDoc -> R_Count-- ;
							int location = pDoc -> R_Location.GetAt ( R_Number ) ;
							pDoc -> What.RemoveAt ( pDoc -> R_Location.GetAt ( R_Number ) ) ;
							pDoc -> R_Rec.RemoveAt ( R_Number ) ;
							pDoc -> R_Location.RemoveAt ( R_Number ) ;
							pDoc -> R_Color.RemoveAt ( R_Number ) ;
							pDoc -> R_FillColor.RemoveAt ( R_Number ) ;
							pDoc -> R_FillPattern.RemoveAt ( R_Number ) ;
							pDoc -> R_IsNoFill.RemoveAt ( R_Number ) ;
							pDoc -> R_LinePattern.RemoveAt ( R_Number ) ;
							pDoc -> R_Thickness.RemoveAt ( R_Number ) ;

							for ( int i = R_Number ; i < pDoc -> R_Rec.GetCount () ; i++ ) {
								pDoc -> R_Location.GetAt (i)-- ;
							}

							int L_For = 0 ;
							int P_For = 0 ;
							int E_For = 0 ;
							int T_For = 0 ;
							int RT_For = 0 ;
							int RightT_For = 0 ;
							int RRightT_For = 0 ;
							int LTRT_For = 0 ;
							int RTLT_For = 0 ;
							int Text_For = 0 ;
							int G_For = 0 ;

							for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
								if ( pDoc -> What.GetAt (i) == _T ("L") ) {
									for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
										if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
											pDoc -> L_Location.SetAt (j, i) ;
											L_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("P") ) {
									for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
										if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
											pDoc -> P_Location.SetAt (j, i) ;
											P_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("E") ) {
									for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
										if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
											pDoc -> E_Location.SetAt (j, i) ;
											E_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("T") ) {
									for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
										if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
											pDoc -> T_Location.SetAt (j, i) ;
											T_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
									for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
											pDoc -> RT_Location.SetAt (j, i) ;
											RT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
									for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
											pDoc -> RightT_Location.SetAt (j, i) ;
											RightT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
									for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
											pDoc -> RRightT_Location.SetAt (j, i) ;
											RRightT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
									for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
										if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
											pDoc -> LTRT_Location.SetAt (j, i) ;
											LTRT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
									for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
											pDoc -> RTLT_Location.SetAt (j, i) ;
											RTLT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
									for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
										if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
											pDoc -> Text_Location.SetAt (j, i) ;
											Text_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("G") ) {
									for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
										if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
											pDoc -> G_Location.SetAt (j, i) ;
											G_For = j ;
											break ;
										}
									}
								}
							}
							i-- ;
							R_Number-- ;
					}
					R_Number++ ;
				}
				else if ( pDoc -> What.GetAt (i) == _T ("E") ) {
					if ( pDoc -> E_Ellipse.GetAt ( E_Number ).top >= G_Include.top && pDoc -> E_Ellipse.GetAt ( E_Number ).bottom <= G_Include.bottom &&
						pDoc -> E_Ellipse.GetAt ( E_Number ).left >= G_Include.left && pDoc -> E_Ellipse.GetAt ( E_Number ).right <= G_Include.right ) {

							pDoc -> G_Group.GetAt ( G_Current ).Ellipse.Add ( pDoc -> E_Ellipse.GetAt ( E_Number ) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).E_Color.Add ( pDoc -> E_Color.GetAt (E_Number) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).E_FillColor.Add ( pDoc -> E_FillColor.GetAt (E_Number) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).E_Count++ ;
							pDoc -> G_Group.GetAt ( G_Current ).E_IsNoFill.Add ( pDoc -> E_IsNoFill.GetAt (E_Number) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).E_FillPattern.Add ( pDoc -> E_FillPattern.GetAt (E_Number) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).E_LinePattern.Add ( pDoc -> E_LinePattern.GetAt (E_Number) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).E_Thickness.Add ( pDoc -> E_Thickness.GetAt (E_Number) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).What.Add ( _T ("E") ) ;

							if ( G_FindCount == 0 ) {
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = pDoc -> E_Ellipse.GetAt ( E_Number ).top - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = pDoc -> E_Ellipse.GetAt ( E_Number ).bottom + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = pDoc -> E_Ellipse.GetAt ( E_Number ).left - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = pDoc -> E_Ellipse.GetAt ( E_Number ).right + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
							}
							else {
								if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top > pDoc -> E_Ellipse.GetAt ( E_Number ).top - pDoc -> E_Thickness.GetAt (E_Number) / 2 )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = pDoc -> E_Ellipse.GetAt ( E_Number ).top - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
								if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom < pDoc -> E_Ellipse.GetAt ( E_Number ).bottom + pDoc -> E_Thickness.GetAt (E_Number) / 2 )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = pDoc -> E_Ellipse.GetAt ( E_Number ).bottom + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
								if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left > pDoc -> E_Ellipse.GetAt ( E_Number ).left - pDoc -> E_Thickness.GetAt (E_Number) / 2 )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = pDoc -> E_Ellipse.GetAt ( E_Number ).left - pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
								if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right < pDoc -> E_Ellipse.GetAt ( E_Number ).right + pDoc -> E_Thickness.GetAt (E_Number) / 2 )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = pDoc -> E_Ellipse.GetAt ( E_Number ).right + pDoc -> E_Thickness.GetAt (E_Number) / 2 ;
							}
							G_FindCount++ ;

							int location = pDoc -> E_Location.GetAt ( E_Number ) ;
							pDoc -> E_Ellipse.RemoveAt ( E_Number ) ;
							pDoc -> E_Count-- ;
							pDoc -> What.RemoveAt ( pDoc -> E_Location.GetAt ( E_Number ) ) ;
							pDoc -> E_Location.RemoveAt ( E_Number ) ;
							pDoc -> E_Color.RemoveAt ( E_Number ) ;
							pDoc -> E_FillColor.RemoveAt ( E_Number ) ;
							pDoc -> E_FillPattern.RemoveAt ( E_Number ) ;
							pDoc -> E_IsNoFill.RemoveAt ( E_Number ) ;
							pDoc -> E_LinePattern.RemoveAt ( E_Number ) ;
							pDoc -> E_Thickness.RemoveAt ( E_Number ) ;

							for ( int i = E_Number ; i < pDoc -> E_Ellipse.GetCount () ; i++ ) {
								pDoc -> E_Location.GetAt (i)-- ;
							}

							int R_For = 0 ;
							int P_For = 0 ;
							int L_For = 0 ;
							int T_For = 0 ;
							int RT_For = 0 ;
							int RightT_For = 0 ;
							int RRightT_For = 0 ;
							int LTRT_For = 0 ;
							int RTLT_For = 0 ;
							int Text_For = 0 ;
							int G_For = 0 ;

							for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
								if ( pDoc -> What.GetAt (i) == _T ("R") ) {
									for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
										if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
											pDoc -> R_Location.SetAt (j, i) ;
											R_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("P") ) {
									for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
										if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
											pDoc -> P_Location.SetAt (j, i) ;
											P_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("L") ) {
									for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
										if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
											pDoc -> L_Location.SetAt (j, i) ;
											L_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("T") ) {
									for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
										if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
											pDoc -> T_Location.SetAt (j, i) ;
											T_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
									for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
											pDoc -> RT_Location.SetAt (j, i) ;
											RT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
									for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
											pDoc -> RightT_Location.SetAt (j, i) ;
											RightT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
									for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
											pDoc -> RRightT_Location.SetAt (j, i) ;
											RRightT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
									for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
										if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
											pDoc -> LTRT_Location.SetAt (j, i) ;
											LTRT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
									for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
											pDoc -> RTLT_Location.SetAt (j, i) ;
											RTLT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
									for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
										if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
											pDoc -> Text_Location.SetAt (j, i) ;
											Text_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("G") ) {
									for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
										if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
											pDoc -> G_Location.SetAt (j, i) ;
											G_For = j ;
											break ;
										}
									}
								}
							}
							i-- ;
							E_Number-- ;
					}
					E_Number++ ;
				}
				else if ( pDoc -> What.GetAt (i) == _T ("Text") ) {
					if ( pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.top >= G_Include.top && pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.bottom <= G_Include.bottom &&
						pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.left >= G_Include.left && pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.right <= G_Include.right ) {

							pDoc -> G_Group.GetAt ( G_Current ).Text_Count++ ;
							pDoc -> G_Group.GetAt ( G_Current ).Text.Add ( pDoc -> Text_Text.GetAt (Text_Number) ) ;
							pDoc -> G_Group.GetAt ( G_Current ).What.Add ( _T ("Text") ) ;
							
							if ( G_FindCount == 0 ) {
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.top ;
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.bottom ;
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.left ;
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.right ;
							}
							else {
								if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top > pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.top )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.top ;
								if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom < pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.bottom )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.bottom ;
								if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left > pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.left )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.left ;
								if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right < pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.right )
									pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = pDoc -> Text_Text.GetAt ( Text_Number ).Text_Rect.right ;
							}
							G_FindCount++ ;

							int location = pDoc -> Text_Location.GetAt ( Text_Number ) ;
							pDoc -> Text_Text.RemoveAt ( Text_Number ) ;
							pDoc -> Text_Count-- ;
							pDoc -> Text_Text.SetSize ( pDoc -> Text_Count ) ;
							pDoc -> What.RemoveAt ( pDoc -> Text_Location.GetAt ( Text_Number ) ) ;
							pDoc -> Text_Location.RemoveAt ( Text_Number ) ;
							for ( int i = Text_Number ; i < pDoc -> Text_Text.GetCount () ; i++ ) {
								pDoc -> Text_Location.GetAt (i)-- ;
							}

							int R_For = 0 ;
							int P_For = 0 ;
							int E_For = 0 ;
							int T_For = 0 ;
							int RT_For = 0 ;
							int RightT_For = 0 ;
							int RRightT_For = 0 ;
							int LTRT_For = 0 ;
							int L_For = 0 ;
							int RTLT_For = 0 ;
							int G_For = 0 ;

							for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
								if ( pDoc -> What.GetAt (i) == _T ("R") ) {
									for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
										if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
											pDoc -> R_Location.SetAt (j, i) ;
											R_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("P") ) {
									for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
										if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
											pDoc -> P_Location.SetAt (j, i) ;
											P_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("E") ) {
									for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
										if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
											pDoc -> E_Location.SetAt (j, i) ;
											E_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("T") ) {
									for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
										if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
											pDoc -> T_Location.SetAt (j, i) ;
											T_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
									for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
											pDoc -> RT_Location.SetAt (j, i) ;
											RT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
									for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
											pDoc -> RightT_Location.SetAt (j, i) ;
											RightT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
									for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
											pDoc -> RRightT_Location.SetAt (j, i) ;
											RRightT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
									for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
										if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
											pDoc -> LTRT_Location.SetAt (j, i) ;
											LTRT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("L") ) {
									for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
										if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
											pDoc -> L_Location.SetAt (j, i) ;
											L_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
									for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
										if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
											pDoc -> RTLT_Location.SetAt (j, i) ;
											RTLT_For = j ;
											break ;
										}
									}
								}
								else if ( pDoc -> What.GetAt (i) == _T("G") ) {
									for ( int j = G_For ; j < pDoc -> G_Location.GetCount () ; j++ ) {
										if ( pDoc -> G_Location.GetAt (j) == i+1 ) {
											pDoc -> G_Location.SetAt (j, i) ;
											G_For = j ;
											break ;
										}
									}
								}
							}
							i-- ;
							Text_Number--;
					}
					Text_Number++ ;
				}
				// 종속된 그룹을 그룹화 합니다.
				else if ( pDoc -> What.GetAt (i) == _T ("G") ) {
					if ( pDoc -> G_Group.GetAt ( G_Number ).GroupBox.top >= G_Include.top && pDoc -> G_Group.GetAt ( G_Number ).GroupBox.bottom <= G_Include.bottom &&
						pDoc -> G_Group.GetAt ( G_Number ).GroupBox.left >= G_Include.left && pDoc -> G_Group.GetAt ( G_Number ).GroupBox.right <= G_Include.right ) {

						pDoc -> G_Group.GetAt (G_Current).G_Count++ ;
						pDoc -> G_Group.GetAt (G_Current).What.Add ( _T ("G") ) ;
						pDoc -> G_Group.GetAt (G_Current).G_Count += pDoc -> G_Group.GetAt (G_Number).G_Count ;
						int InCurrent = pDoc -> G_InCount ;
						pDoc -> G_InCount++ ;
						pDoc -> G_InGroup.SetSize ( pDoc -> G_InCount ) ;
						
						if ( G_FindCount == 0 ) {
							pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = pDoc -> G_Group.GetAt ( G_Number ).GroupBox.top ;
							pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = pDoc -> G_Group.GetAt ( G_Number ).GroupBox.bottom ;
							pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = pDoc -> G_Group.GetAt ( G_Number ).GroupBox.left ;
							pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = pDoc -> G_Group.GetAt ( G_Number ).GroupBox.right ;
						}
						else {
							if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top > pDoc -> G_Group.GetAt ( G_Number ).GroupBox.top )
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.top = pDoc -> G_Group.GetAt ( G_Number ).GroupBox.top ;
							if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom < pDoc -> G_Group.GetAt ( G_Number ).GroupBox.bottom )
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.bottom = pDoc -> G_Group.GetAt ( G_Number ).GroupBox.bottom ;
							if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left > pDoc -> G_Group.GetAt ( G_Number ).GroupBox.left )
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.left = pDoc -> G_Group.GetAt ( G_Number ).GroupBox.left ;
							if ( pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right < pDoc -> G_Group.GetAt ( G_Number ).GroupBox.right )
								pDoc -> G_Group.GetAt ( G_Current ).GroupBox.right = pDoc -> G_Group.GetAt ( G_Number ).GroupBox.right ;
						}

						if ( pDoc -> G_Group.GetAt (G_Number).Index.GetCount () > 0 ) {
							for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).Index.GetCount () ; i++ )
								pDoc -> G_Group.GetAt (G_Current).Index.Add ( pDoc -> G_Group.GetAt (G_Number).Index.GetAt (i) ) ;
						}

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).Ellipse.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).Ellipse.Add ( pDoc -> G_Group.GetAt (G_Number).Ellipse.GetAt (i) ) ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).E_Color.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).E_Color.Add ( pDoc -> G_Group.GetAt (G_Number).E_Color.GetAt (i) ) ;

						pDoc -> G_InGroup.GetAt (InCurrent).E_Count = pDoc -> G_Group.GetAt (G_Number).E_Count ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).E_FillColor.Add ( pDoc -> G_Group.GetAt (G_Number).E_FillColor.GetAt (i) ) ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).E_FillPattern.Add ( pDoc -> G_Group.GetAt (G_Number).E_FillPattern.GetAt (i) ) ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).E_IsNoFill.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).E_IsNoFill.Add ( pDoc -> G_Group.GetAt (G_Number).E_IsNoFill.GetAt (i) ) ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).E_LinePattern.Add ( pDoc -> G_Group.GetAt (G_Number).E_LinePattern.GetAt (i) ) ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).E_Thickness.Add ( pDoc -> G_Group.GetAt (G_Number).E_Thickness.GetAt (i) ) ;

						pDoc -> G_InGroup.GetAt (InCurrent).GroupBox = pDoc -> G_Group.GetAt (G_Number).GroupBox ;
						pDoc -> G_InGroup.GetAt (InCurrent).G_Count = pDoc -> G_Group.GetAt (G_Number).G_Count ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).Line.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).Line.Add ( pDoc -> G_Group.GetAt (G_Number).Line.GetAt (i) ) ;

						pDoc -> G_InGroup.GetAt (InCurrent).L_Count = pDoc -> G_Group.GetAt (G_Number).L_Count ;

						pDoc -> G_InGroup.GetAt (InCurrent).Poly.SetSize ( pDoc -> G_Group.GetAt (G_Number).Poly.GetCount () ) ;
						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).Poly.GetCount () ; i++ ) {

							pDoc -> G_InGroup.GetAt (InCurrent).Poly.GetAt (i).Poly_point.SetSize ( pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (i).Poly_point.GetSize () ) ;
							for ( int j = 0 ; j < pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (i).Poly_point.GetCount () ; j++ ) {
								pDoc -> G_InGroup.GetAt (InCurrent).Poly.GetAt (i).Poly_point.GetAt (j).x = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (i).Poly_point.GetAt (j).x ;
								pDoc -> G_InGroup.GetAt (InCurrent).Poly.GetAt (i).Poly_point.GetAt (j).y = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (i).Poly_point.GetAt (j).y ;
							}
							pDoc -> G_InGroup.GetAt (InCurrent).Poly.GetAt (i).Pattern = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (i).Pattern ;
							pDoc -> G_InGroup.GetAt (InCurrent).Poly.GetAt (i).P_Color = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (i).P_Color ;
							pDoc -> G_InGroup.GetAt (InCurrent).Poly.GetAt (i).thickness = pDoc -> G_Group.GetAt (G_Number).Poly.GetAt (i).thickness ;
						}

						pDoc -> G_InGroup.GetAt (InCurrent).P_Count = pDoc -> G_Group.GetAt (G_Number).P_Count ;
						
						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).Rect.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).Rect.Add ( pDoc -> G_Group.GetAt (G_Number).Rect.GetAt (i) ) ;

						pDoc -> G_InGroup.GetAt (InCurrent).R_Count = pDoc -> G_Group.GetAt (G_Number).R_Count ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).R_Color.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).R_Color.Add ( pDoc -> G_Group.GetAt (G_Number).R_Color.GetAt (i) ) ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).R_FillColor.Add ( pDoc -> G_Group.GetAt (G_Number).R_FillColor.GetAt (i) ) ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).R_FillPattern.Add ( pDoc -> G_Group.GetAt (G_Number).R_FillPattern.GetAt (i) ) ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).R_IsNoFill.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).R_IsNoFill.Add ( pDoc -> G_Group.GetAt (G_Number).R_IsNoFill.GetAt (i) ) ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).R_LinePattern.Add ( pDoc -> G_Group.GetAt (G_Number).R_LinePattern.GetAt (i) ) ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).R_Thickness.Add ( pDoc -> G_Group.GetAt (G_Number).R_Thickness.GetAt (i) ) ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).Text.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).Text.Add ( pDoc -> G_Group.GetAt (G_Number).Text.GetAt (i) ) ;

						pDoc -> G_InGroup.GetAt (InCurrent).Text_Count = pDoc -> G_Group.GetAt (G_Number).Text_Count ;

						for ( int i = 0 ; i < pDoc -> G_Group.GetAt (G_Number).What.GetCount () ; i++ )
							pDoc -> G_InGroup.GetAt (InCurrent).What.Add ( pDoc -> G_Group.GetAt (G_Number).What.GetAt (i) ) ;
							
						G_FindCount++ ;

						pDoc -> G_Group.GetAt (G_Current).Index.Add ( InCurrent ) ;

						int location = pDoc -> G_Location.GetAt ( G_Number ) ;
						pDoc -> G_Group.RemoveAt ( G_Number ) ;
						pDoc -> G_Count-- ;
						pDoc -> What.RemoveAt ( pDoc -> G_Location.GetAt ( G_Number ) ) ;
						pDoc -> G_Location.RemoveAt ( G_Number ) ;
						
						for ( int i = G_Number ; i < pDoc -> G_Group.GetCount () - 1 ; i++ ) {
								pDoc -> G_Location.GetAt (i)-- ;
						}

						int R_For = 0 ;
						int P_For = 0 ;
						int E_For = 0 ;
						int T_For = 0 ;
						int RT_For = 0 ;
						int RightT_For = 0 ;
						int RRightT_For = 0 ;
						int LTRT_For = 0 ;
						int L_For = 0 ;
						int RTLT_For = 0 ;
						int Text_For = 0 ;

						for ( int i = location ; i < pDoc -> What.GetCount () ; i++ ) {
							if ( pDoc -> What.GetAt (i) == _T ("R") ) {
								for ( int j = R_For ; j < pDoc -> R_Location.GetCount () ; j++ ) {
									if ( pDoc -> R_Location.GetAt (j) == i+1 ) {
										pDoc -> R_Location.SetAt (j, i) ;
										R_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("P") ) {
								for ( int j = P_For ; j < pDoc -> P_Location.GetCount () ; j++ ) {
									if ( pDoc -> P_Location.GetAt (j) == i+1 ) {
										pDoc -> P_Location.SetAt (j, i) ;
										P_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("E") ) {
								for ( int j = E_For ; j < pDoc -> E_Location.GetCount () ; j++ ) {
									if ( pDoc -> E_Location.GetAt (j) == i+1 ) {
										pDoc -> E_Location.SetAt (j, i) ;
										E_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("T") ) {
								for ( int j = T_For ; j < pDoc -> T_Location.GetCount () ; j++ ) {
									if ( pDoc -> T_Location.GetAt (j) == i+1 ) {
										pDoc -> T_Location.SetAt (j, i) ;
										T_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("RT") ) {
								for ( int j = RT_For ; j < pDoc -> RT_Location.GetCount () ; j++ ) {
									if ( pDoc -> RT_Location.GetAt (j) == i+1 ) {
										pDoc -> RT_Location.SetAt (j, i) ;
										RT_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("RightT") ) {
								for ( int j = RightT_For ; j < pDoc -> RightT_Location.GetCount () ; j++ ) {
									if ( pDoc -> RightT_Location.GetAt (j) == i+1 ) {
										pDoc -> RightT_Location.SetAt (j, i) ;
										RightT_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("RRightT") ) {
								for ( int j = RRightT_For ; j < pDoc -> RRightT_Location.GetCount () ; j++ ) {
									if ( pDoc -> RRightT_Location.GetAt (j) == i+1 ) {
										pDoc -> RRightT_Location.SetAt (j, i) ;
										RRightT_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("LTRT") ) {
								for ( int j = LTRT_For ; j < pDoc -> LTRT_Location.GetCount () ; j++ ) {
									if ( pDoc -> LTRT_Location.GetAt (j) == i+1 ) {
										pDoc -> LTRT_Location.SetAt (j, i) ;
										LTRT_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("L") ) {
								for ( int j = L_For ; j < pDoc -> L_Location.GetCount () ; j++ ) {
									if ( pDoc -> L_Location.GetAt (j) == i+1 ) {
										pDoc -> L_Location.SetAt (j, i) ;
										L_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("RTLT") ) {
								for ( int j = RTLT_For ; j < pDoc -> RTLT_Location.GetCount () ; j++ ) {
									if ( pDoc -> RTLT_Location.GetAt (j) == i+1 ) {
										pDoc -> RTLT_Location.SetAt (j, i) ;
										RTLT_For = j ;
										break ;
									}
								}
							}
							else if ( pDoc -> What.GetAt (i) == _T("Text") ) {
								for ( int j = Text_For ; j < pDoc -> Text_Location.GetCount () ; j++ ) {
									if ( pDoc -> Text_Location.GetAt (j) == i+1 ) {
										pDoc -> Text_Location.SetAt (j, i) ;
										Text_For = j ;
										break ;
									}
								}
							}
						}
						i-- ;
						G_Number-- ;
						G_Current-- ;
					}
					G_Number++ ;
				}
			}

			if ( G_FindCount > 1 ) {
				pDoc -> What.Add ( _T ("G") ) ;
				pDoc -> G_Count++ ;
				pDoc -> G_Location.Add ( pDoc -> What.GetCount () - 1 ) ;
				G_ViewSelection = 'o' ;
			}
			else {
				pDoc -> G_Group.RemoveAt ( pDoc -> G_Count ) ;
			}

		}
		Invalidate () ;
		m_IsSelectGroup = 'x' ;
		G_IsMakeGroup = 'x' ;
	}
}

void CGraphicEditorView::OnGroupx()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
