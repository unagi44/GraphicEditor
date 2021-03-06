//**************************************************************************************************************
// public of Passion Designers
// GraphicEditor program
// 2010253009 이계연
// 2010253026 박현태
//**************************************************************************************************************
// GraphicEditorDoc.cpp : CGraphicEditorDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GraphicEditor.h"
#endif

#include "GraphicEditorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGraphicEditorDoc

IMPLEMENT_DYNCREATE(CGraphicEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicEditorDoc, CDocument)
END_MESSAGE_MAP()


// CGraphicEditorDoc 생성/소멸

CGraphicEditorDoc::CGraphicEditorDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	L_Count = 0 ;
	R_Count = 0 ;
	P_Count = 0 ;
	E_Count = 0 ;
	T_Count = 0 ;
	RT_Count = 0 ;
	RightT_Count = 0 ;
	RRightT_Count = 0 ;
	LTRT_Count = 0 ;
	RTLT_Count = 0 ;
	Text_Count = 0 ;
	G_Count = 0 ;
	G_InCount = 0 ;
}

CGraphicEditorDoc::~CGraphicEditorDoc()
{
}

BOOL CGraphicEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CGraphicEditorDoc serialization

void CGraphicEditorDoc::Serialize(CArchive& ar)
{
	// 그린 모든 객체들을 저장, 불러오기를 가능하게 합니다.
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		L_Line.Serialize (ar) ;	// 선 그리기 배열 저장
		R_Rec.Serialize (ar) ;	// 상자 그리기 배열 저장

		// PolyLine 그리기 배열 저장
		CPolyCount = P_Poly.GetCount () ;
		ar << CPolyCount ;
		for ( int i = 0 ; i < P_Poly.GetCount () ; i++ ) {
			P_Poly.GetAt (i).Poly_point.Serialize (ar) ;
			ar << P_Poly.GetAt (i).P_Color ;
			ar << P_Poly.GetAt (i).thickness ;
			ar << P_Poly.GetAt (i).Pattern ;
		}
		
		E_Ellipse.Serialize (ar) ;	// 원 그리기 배열 저장
		T_Triangle.Serialize (ar) ;	// 세모 그리기 배열 저장
		RT_Triangle.Serialize (ar) ;// 역 삼각형 그리기 배열 저장
		R_Color.Serialize (ar) ;	// 사각형의 각 선 색상 정보 저장
		E_Color.Serialize (ar) ;	// 원의 각 선 색상 정보 저장
		R_FillColor.Serialize (ar) ;	// 사각형의 각 채우기 색상 정보 저장
		E_FillColor.Serialize (ar) ;	// 원의 각 채우기 색상 정보 저장
		T_Color.Serialize (ar) ;		// 세모 선 색상 정보 저장
		T_FillColor.Serialize (ar) ;	// 세모 채우기 색상 정보 저장
		RT_Color.Serialize (ar) ;		// 역 삼각형 선 색상 정보 저장
		RT_FillColor.Serialize (ar) ;	// 역 삼각형 채우기 색상 정보 저장
		RightT_Triangle.Serialize (ar) ;	// 직각 삼각형 그리기 배열 저장
		RRightT_Triangle.Serialize (ar) ;	// 역 직각 삼각형 그리기 배열 저장
		RightT_Color.Serialize (ar) ;		// 직각 삼각형 선 색상 정보 저장
		RightT_FillColor.Serialize (ar) ;	// 직각 삼각형 채우기 색상 정보 저장
		RRightT_Color.Serialize (ar) ;		// 역 직각 삼각형 선 색상 정보 저장
		RRightT_FillColor.Serialize (ar) ;	// 역 직각 삼각형 채우기 색상 정보 저장

		R_Thickness.Serialize (ar) ;		// 상자의 선 두께를 저장
		E_Thickness.Serialize (ar) ;		// 원의 선 두께를 저장
		T_Thickness.Serialize (ar) ;		// 세모의 선 두께를 저장
		RT_Thickness.Serialize (ar) ;		// 역 삼각형의 선 두께를 저장
		RightT_Thickness.Serialize (ar) ;	// 직각 삼각형의 선 두께를 저장
		RRightT_Thickness.Serialize (ar) ;	// 역 직각 삼각형의 선 두께를 저장
		RTLT_Triangle.Serialize (ar) ;		// 오른쪽 -> 왼쪽 삼각형 그리기 배열 저장
		LTRT_Triangle.Serialize (ar) ;		// 왼쪽 -> 오른쪽 삼각형 그리기 배열 저장
		RTLT_Color.Serialize (ar) ;			// 오른쪽 -> 왼쪽 삼각형 선 색 저장
		RTLT_FillColor.Serialize (ar) ;		// 오른쪽 -> 왼쪽 삼각형 채우기 색 저장
		RTLT_Thickness.Serialize (ar) ;		// 오른쪽 -> 왼쪽 삼각형 두께 저장
		LTRT_Color.Serialize (ar) ;			// 왼쪽 -> 오른쪽 삼각형 선 색 저장
		LTRT_FillColor.Serialize (ar) ;		// 왼쪽 -> 오른쪽 삼각형 채우기 색 저장
		LTRT_Thickness.Serialize (ar) ;		// 왼쪽 -> 오른쪽 삼각형 두께 저장
		What.Serialize (ar) ;
		Text_Text.Serialize (ar) ;			// 텍스트 객체 저장

		ar << L_Count ;
		ar << R_Count ;
		ar << P_Count ;
		ar << E_Count ;
		ar << T_Count ;
		ar << RT_Count ;
		ar << RightT_Count ;
		ar << RRightT_Count ;
		ar << LTRT_Count ;
		ar << RTLT_Count ;
		ar << Text_Count ;
		ar << G_Count ;

		L_Location.Serialize (ar) ;				// 그린 모든 객체 중 선 객체의 각 Index 저장
		R_Location.Serialize (ar) ;				// 그린 모든 객체 중 상자 객체의 각 Index 저장
		P_Location.Serialize (ar) ;				// 그린 모든 객체 중 PolyLine 객체의 각 Index 저장
		E_Location.Serialize (ar) ;				// 그린 모든 객체 중 원 객체의 각 Index 저장
		T_Location.Serialize (ar) ;				// 그린 모든 객체 중 세모 객체의 각 Index 저장
		RT_Location.Serialize (ar) ;			// 그린 모든 객체 중 역 삼각형 객체의 각 Index 저장
		RightT_Location.Serialize (ar) ;		// 그린 모든 객체 중 직각 삼각형 객체의 각 Index 저장
		RRightT_Location.Serialize (ar) ;		// 그린 모든 객체 중 역 직각 삼각형 객체의 각 Index 저장
		LTRT_Location.Serialize (ar) ;			// 그린 모든 객체 중 왼쪽 -> 오른쪽 삼각형 객체의 각 Index 저장
		RTLT_Location.Serialize (ar) ;			// 그린 모든 객체 중 오른쪽 -> 왼쪽 객체의 각 Index 저장
		Text_Location.Serialize (ar) ;			// 그린 모든 객체 중 Text 객체의 각 Index 저장
		G_Location.Serialize (ar) ;

		R_IsNoFill.Serialize (ar) ;
		E_IsNoFill.Serialize (ar) ;
		T_IsNoFill.Serialize (ar) ;
		RT_IsNoFill.Serialize (ar) ;
		RightT_IsNoFill.Serialize (ar) ;		// 채우기 색상이 없는지 확인해주는 변수
		RRightT_IsNoFill.Serialize (ar) ;
		LTRT_IsNoFill.Serialize (ar) ;
		RTLT_IsNoFill.Serialize (ar) ;

		R_FillPattern.Serialize (ar) ;
		E_FillPattern.Serialize (ar) ;
		T_FillPattern.Serialize (ar) ;
		RT_FillPattern.Serialize (ar) ;
		RightT_FillPattern.Serialize (ar) ;		// 채우기 패턴이 무엇인지 확인해주는 변수
		RRightT_FillPattern.Serialize (ar) ;
		LTRT_FillPattern.Serialize (ar) ;
		RTLT_FillPattern.Serialize (ar) ;

		R_LinePattern.Serialize (ar) ;
		E_LinePattern.Serialize (ar) ;
		T_LinePattern.Serialize (ar) ;
		RT_LinePattern.Serialize (ar) ;
		RightT_LinePattern.Serialize (ar) ;		// 선 패턴이 무엇인지 확인해주는 변수
		RRightT_LinePattern.Serialize (ar) ;
		LTRT_LinePattern.Serialize (ar) ;
		RTLT_LinePattern.Serialize (ar) ;

		// 그룹화 저장 가능
		ar << G_Count ;
		for ( int i = 0 ; i < G_Group.GetCount () ; i++ ) {
			G_Group.GetAt (i).Index.Serialize (ar) ;
			G_Group.GetAt (i).Ellipse.Serialize (ar) ;
			G_Group.GetAt (i).E_Color.Serialize (ar) ;
			ar << G_Group.GetAt (i).E_Count ;
			G_Group.GetAt (i).E_FillColor.Serialize (ar) ;
			G_Group.GetAt (i).E_FillPattern.Serialize (ar) ;
			G_Group.GetAt (i).E_IsNoFill.Serialize (ar) ;
			G_Group.GetAt (i).E_LinePattern.Serialize (ar) ;
			G_Group.GetAt (i).E_Thickness.Serialize (ar) ;
			ar << G_Group.GetAt (i).GroupBox ;
			ar << G_Group.GetAt (i).G_Count ;
			G_Group.GetAt (i).Line.Serialize (ar) ;
			ar << G_Group.GetAt (i).L_Count ;

			CPolyCount = G_Group.GetAt (i).Poly.GetCount () ;
			ar << CPolyCount ;
			for ( int j = 0 ; j < G_Group.GetAt (i).Poly.GetCount () ; j++ ) {
				G_Group.GetAt (i).Poly.GetAt (j).Poly_point.Serialize (ar) ;
				ar << G_Group.GetAt (i).Poly.GetAt (j).Pattern  ;
				ar << G_Group.GetAt (i).Poly.GetAt (j).P_Color ;
				ar << G_Group.GetAt (i).Poly.GetAt (j).thickness ;
			}

			ar << G_Group.GetAt (i).P_Count ;
			G_Group.GetAt (i).Rect.Serialize (ar) ;
			G_Group.GetAt (i).R_Color.Serialize (ar) ;
			ar << G_Group.GetAt (i).R_Count ;
			G_Group.GetAt (i).R_FillColor.Serialize (ar) ;
			G_Group.GetAt (i).R_FillPattern.Serialize (ar) ;
			G_Group.GetAt (i).R_IsNoFill.Serialize (ar) ;
			G_Group.GetAt (i).R_LinePattern.Serialize (ar) ;
			G_Group.GetAt (i).R_Thickness.Serialize (ar) ;
			G_Group.GetAt (i).Text.Serialize (ar) ;
			ar << G_Group.GetAt (i).Text_Count ;
			G_Group.GetAt (i).What.Serialize (ar) ;
		}
		
		// 종속된 그룹화 저장
		ar << G_InCount ;
		for ( int i = 0 ; i < G_InGroup.GetCount () ; i++ ) {
			G_InGroup.GetAt (i).Index.Serialize (ar) ;
			G_InGroup.GetAt (i).Ellipse.Serialize (ar) ;
			G_InGroup.GetAt (i).E_Color.Serialize (ar) ;
			ar << G_InGroup.GetAt (i).E_Count ;
			G_InGroup.GetAt (i).E_FillColor.Serialize (ar) ;
			G_InGroup.GetAt (i).E_FillPattern.Serialize (ar) ;
			G_InGroup.GetAt (i).E_IsNoFill.Serialize (ar) ;
			G_InGroup.GetAt (i).E_LinePattern.Serialize (ar) ;
			G_InGroup.GetAt (i).E_Thickness.Serialize (ar) ;
			ar << G_InGroup.GetAt (i).GroupBox ;
			ar << G_InGroup.GetAt (i).G_Count ;
			G_InGroup.GetAt (i).Line.Serialize (ar) ;
			ar << G_InGroup.GetAt (i).L_Count ;

			CPolyCount = G_InGroup.GetAt (i).Poly.GetCount () ;
			ar << CPolyCount ;
			for ( int j = 0 ; j < G_InGroup.GetAt (i).Poly.GetCount () ; j++ ) {
				G_InGroup.GetAt (i).Poly.GetAt (j).Poly_point.Serialize (ar) ;
				ar << G_InGroup.GetAt (i).Poly.GetAt (j).Pattern  ;
				ar << G_InGroup.GetAt (i).Poly.GetAt (j).P_Color ;
				ar << G_InGroup.GetAt (i).Poly.GetAt (j).thickness ;
			}

			ar << G_InGroup.GetAt (i).P_Count ;
			G_InGroup.GetAt (i).Rect.Serialize (ar) ;
			G_InGroup.GetAt (i).R_Color.Serialize (ar) ;
			ar << G_InGroup.GetAt (i).R_Count ;
			G_InGroup.GetAt (i).R_FillColor.Serialize (ar) ;
			G_InGroup.GetAt (i).R_FillPattern.Serialize (ar) ;
			G_InGroup.GetAt (i).R_IsNoFill.Serialize (ar) ;
			G_InGroup.GetAt (i).R_LinePattern.Serialize (ar) ;
			G_InGroup.GetAt (i).R_Thickness.Serialize (ar) ;
			G_InGroup.GetAt (i).Text.Serialize (ar) ;
			ar << G_InGroup.GetAt (i).Text_Count ;
			G_InGroup.GetAt (i).What.Serialize (ar) ;
		}
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		L_Line.Serialize (ar) ;	// 선 그리기 배열 불러오기
		R_Rec.Serialize (ar) ;	// 상자 그리기 배열 불러오기

		// PolyLine  그리기 배열 불러오기
		ar >> CPolyCount ;
		P_Poly.SetSize ( CPolyCount ) ;
		for ( int i = 0 ; i < CPolyCount ; i++ ) {
			P_Poly.GetAt (i).Poly_point.Serialize (ar) ;
			ar >> P_Poly.GetAt (i).P_Color ;
			ar >> P_Poly.GetAt (i).thickness ;
			ar >> P_Poly.GetAt (i).Pattern ;
		}
		
		E_Ellipse.Serialize (ar) ;	// 원 그리기 배열 불러오기
		T_Triangle.Serialize (ar) ;	// 세모 그리기 배열 불러오기
		RT_Triangle.Serialize (ar) ;// 역 삼각형 그리기 배열 불러오기
		R_Color.Serialize (ar) ;	// 사각형의 각 선 색상 정보 불러오기
		E_Color.Serialize (ar) ;	// 사각형의 각 선 색상 정보 불러오기
		R_FillColor.Serialize (ar) ;	// 사각형의 각 채우기 색상 정보 불러오기
		E_FillColor.Serialize (ar) ;	// 원의 각 채우기 색상 정보 불러오기
		T_Color.Serialize (ar) ;		// 세모 각 선 색상 정보 불러오기
		T_FillColor.Serialize (ar) ;	// 세모 각 채우기 색상 정보 불러오기
		RT_Color.Serialize (ar) ;		// 역 삼각형 선 색상 정보 불러오기
		RT_FillColor.Serialize (ar) ;	// 역 삼각형 채우기 색상 정보 불러오기
		RightT_Triangle.Serialize (ar) ;	// 직각 삼각형 그리기 배열 불러오기
		RRightT_Triangle.Serialize (ar) ;	// 역 직각 삼각형 그리기 배열 불러오기
		RightT_Color.Serialize (ar) ;		// 직각 삼각형 선 색상 정보 불러오기
		RightT_FillColor.Serialize (ar) ;	// 직각 삼각형 채우기 색상 정보 불러오기
		RRightT_Color.Serialize (ar) ;		// 역 직각 삼각형 선 색상 정보 불러오기
		RRightT_FillColor.Serialize (ar) ;	// 역 직각 삼각형 채우기 색상 정보 불러오기

		R_Thickness.Serialize (ar) ;		// 상자의 선 두께 불러오기
		E_Thickness.Serialize (ar) ;		// 원의 선 두께 불러오기
		T_Thickness.Serialize (ar) ;		// 세모의 선 두께 불러오기
		RT_Thickness.Serialize (ar) ;		// 역 삼각형의 선 두께 불러오기
		RightT_Thickness.Serialize (ar) ;	// 직각 삼각형의 선 두께 불러오기
		RRightT_Thickness.Serialize (ar) ;	// 역 직각 삼각형의 선 두께 불러오기
		RTLT_Triangle.Serialize (ar) ;		// 오른쪽 -> 왼쪽 삼각형 그리기 배열 불러오기
		LTRT_Triangle.Serialize (ar) ;		// 왼쪽 -> 오른쪽 삼각형 그리기 배열 불러오기
		RTLT_Color.Serialize (ar) ;			// 오른쪽 -> 왼쪽 삼각형 선 색 불러오기
		RTLT_FillColor.Serialize (ar) ;		// 오른쪽 -> 왼쪽 삼각형 채우기 색 불러오기
		RTLT_Thickness.Serialize (ar) ;		// 오른쪽 -> 왼쪽 삼각형 두께 불러오기
		LTRT_Color.Serialize (ar) ;			// 왼쪽 -> 오른쪽 삼각형 선 색 불러오기
		LTRT_FillColor.Serialize (ar) ;		// 왼쪽 -> 오른쪽 삼각형 채우기 색 불러오기
		LTRT_Thickness.Serialize (ar) ;		// 왼쪽 -> 오른쪽 삼각형 두께 불러오기
		What.Serialize (ar) ;
		Text_Text.Serialize (ar) ;			// 텍스트 객체 불러오기

		ar >> L_Count ;
		ar >> R_Count ;
		ar >> P_Count ;
		ar >> E_Count ;
		ar >> T_Count ;
		ar >> RT_Count ;
		ar >> RightT_Count ;
		ar >> RRightT_Count ;
		ar >> LTRT_Count ;
		ar >> RTLT_Count ;
		ar >> Text_Count ;
		ar >> G_Count ;

		L_Location.Serialize (ar) ;				// 그린 모든 객체 중 선 객체의 각 Index 불러오기
		R_Location.Serialize (ar) ;				// 그린 모든 객체 중 상자 객체의 각 Index 불러오기
		P_Location.Serialize (ar) ;				// 그린 모든 객체 중 PolyLine 객체의 각 Index 불러오기
		E_Location.Serialize (ar) ;				// 그린 모든 객체 중 원 객체의 각 Index 불러오기
		T_Location.Serialize (ar) ;				// 그린 모든 객체 중 세모 객체의 각 Index 불러오기
		RT_Location.Serialize (ar) ;			// 그린 모든 객체 중 역 삼각형 객체의 각 Index 불러오기
		RightT_Location.Serialize (ar) ;		// 그린 모든 객체 중 직각 삼각형 객체의 각 Index 불러오기
		RRightT_Location.Serialize (ar) ;		// 그린 모든 객체 중 역 직각 삼각형 객체의 각 Index 불러오기
		LTRT_Location.Serialize (ar) ;			// 그린 모든 객체 중 왼쪽 -> 오른쪽 삼각형 객체의 각 Index 불러오기
		RTLT_Location.Serialize (ar) ;			// 그린 모든 객체 중 오른쪽 -> 왼쪽 객체의 각 Index 불러오기
		Text_Location.Serialize (ar) ;			// 그린 모든 객체 중 Text 객체의 각 Index 불러오기
		G_Location.Serialize (ar) ;

		R_IsNoFill.Serialize (ar) ;
		E_IsNoFill.Serialize (ar) ;
		T_IsNoFill.Serialize (ar) ;
		RT_IsNoFill.Serialize (ar) ;
		RightT_IsNoFill.Serialize (ar) ;		// 채우기 색상이 없는지 확인해주는 변수
		RRightT_IsNoFill.Serialize (ar) ;
		LTRT_IsNoFill.Serialize (ar) ;
		RTLT_IsNoFill.Serialize (ar) ;

		R_FillPattern.Serialize (ar) ;
		E_FillPattern.Serialize (ar) ;
		T_FillPattern.Serialize (ar) ;
		RT_FillPattern.Serialize (ar) ;
		RightT_FillPattern.Serialize (ar) ;		// 채우기 패턴이 무엇인지 확인해주는 변수
		RRightT_FillPattern.Serialize (ar) ;
		LTRT_FillPattern.Serialize (ar) ;
		RTLT_FillPattern.Serialize (ar) ;

		R_LinePattern.Serialize (ar) ;
		E_LinePattern.Serialize (ar) ;
		T_LinePattern.Serialize (ar) ;
		RT_LinePattern.Serialize (ar) ;
		RightT_LinePattern.Serialize (ar) ;		// 선 패턴이 무엇인지 확인해주는 변수
		RRightT_LinePattern.Serialize (ar) ;
		LTRT_LinePattern.Serialize (ar) ;
		RTLT_LinePattern.Serialize (ar) ;

		// 그룹화 불러오기
		ar >> G_Count ;
		G_Group.SetSize ( G_Count ) ;
		for ( int i = 0 ; i < G_Count ; i++ ) {
			G_Group.GetAt (i).Index.Serialize (ar) ;
			G_Group.GetAt (i).Ellipse.Serialize (ar) ;
			G_Group.GetAt (i).E_Color.Serialize (ar) ;
			ar >> G_Group.GetAt (i).E_Count ;
			G_Group.GetAt (i).E_FillColor.Serialize (ar) ;
			G_Group.GetAt (i).E_FillPattern.Serialize (ar) ;
			G_Group.GetAt (i).E_IsNoFill.Serialize (ar) ;
			G_Group.GetAt (i).E_LinePattern.Serialize (ar) ;
			G_Group.GetAt (i).E_Thickness.Serialize (ar) ;
			ar >> G_Group.GetAt (i).GroupBox ;
			ar >> G_Group.GetAt (i).G_Count ;
			G_Group.GetAt (i).Line.Serialize (ar) ;
			ar >> G_Group.GetAt (i).L_Count ;

			ar >> CPolyCount ;
			G_Group.GetAt (i).Poly.SetSize ( CPolyCount ) ;
			for ( int j = 0 ; j < CPolyCount ; j++ ) {
				G_Group.GetAt (i).Poly.GetAt (j).Poly_point.Serialize (ar) ;
				ar >> G_Group.GetAt (i).Poly.GetAt (j).Pattern  ;
				ar >> G_Group.GetAt (i).Poly.GetAt (j).P_Color ;
				ar >> G_Group.GetAt (i).Poly.GetAt (j).thickness ;
			}

			ar >> G_Group.GetAt (i).P_Count ;
			G_Group.GetAt (i).Rect.Serialize (ar) ;
			G_Group.GetAt (i).R_Color.Serialize (ar) ;
			ar >> G_Group.GetAt (i).R_Count ;
			G_Group.GetAt (i).R_FillColor.Serialize (ar) ;
			G_Group.GetAt (i).R_FillPattern.Serialize (ar) ;
			G_Group.GetAt (i).R_IsNoFill.Serialize (ar) ;
			G_Group.GetAt (i).R_LinePattern.Serialize (ar) ;
			G_Group.GetAt (i).R_Thickness.Serialize (ar) ;
			G_Group.GetAt (i).Text.Serialize (ar) ;
			ar >> G_Group.GetAt (i).Text_Count ;
			G_Group.GetAt (i).What.Serialize (ar) ;
		}
		
		// 종속된 그룹화 불러오기
		ar >> G_InCount ;
		G_InGroup.SetSize ( G_InCount ) ;
		for ( int i = 0 ; i < G_InCount ; i++ ) {
			G_InGroup.GetAt (i).Index.Serialize (ar) ;
			G_InGroup.GetAt (i).Ellipse.Serialize (ar) ;
			G_InGroup.GetAt (i).E_Color.Serialize (ar) ;
			ar >> G_InGroup.GetAt (i).E_Count ;
			G_InGroup.GetAt (i).E_FillColor.Serialize (ar) ;
			G_InGroup.GetAt (i).E_FillPattern.Serialize (ar) ;
			G_InGroup.GetAt (i).E_IsNoFill.Serialize (ar) ;
			G_InGroup.GetAt (i).E_LinePattern.Serialize (ar) ;
			G_InGroup.GetAt (i).E_Thickness.Serialize (ar) ;
			ar >> G_InGroup.GetAt (i).GroupBox ;
			ar >> G_InGroup.GetAt (i).G_Count ;
			G_InGroup.GetAt (i).Line.Serialize (ar) ;
			ar >> G_InGroup.GetAt (i).L_Count ;

			ar >> CPolyCount ;
			G_InGroup.GetAt (i).Poly.SetSize ( CPolyCount ) ;
			for ( int j = 0 ; j < CPolyCount ; j++ ) {
				G_InGroup.GetAt (i).Poly.GetAt (j).Poly_point.Serialize (ar) ;
				ar >> G_InGroup.GetAt (i).Poly.GetAt (j).Pattern  ;
				ar >> G_InGroup.GetAt (i).Poly.GetAt (j).P_Color ;
				ar >> G_InGroup.GetAt (i).Poly.GetAt (j).thickness ;
			}

			ar >> G_InGroup.GetAt (i).P_Count ;
			G_InGroup.GetAt (i).Rect.Serialize (ar) ;
			G_InGroup.GetAt (i).R_Color.Serialize (ar) ;
			ar >> G_InGroup.GetAt (i).R_Count ;
			G_InGroup.GetAt (i).R_FillColor.Serialize (ar) ;
			G_InGroup.GetAt (i).R_FillPattern.Serialize (ar) ;
			G_InGroup.GetAt (i).R_IsNoFill.Serialize (ar) ;
			G_InGroup.GetAt (i).R_LinePattern.Serialize (ar) ;
			G_InGroup.GetAt (i).R_Thickness.Serialize (ar) ;
			G_InGroup.GetAt (i).Text.Serialize (ar) ;
			ar >> G_InGroup.GetAt (i).Text_Count ;
			G_InGroup.GetAt (i).What.Serialize (ar) ;
		}
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGraphicEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGraphicEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGraphicEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGraphicEditorDoc 진단

#ifdef _DEBUG
void CGraphicEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGraphicEditorDoc 명령
