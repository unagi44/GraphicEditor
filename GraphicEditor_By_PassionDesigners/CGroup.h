#include "stdafx.h"
#include "CLine.h"
#include "CPolyLine.h"
#include "CText.h"

#pragma once

class CGroup {
public:
	CGroup () ;
	CRect GroupBox ;
	CArray < CString, CString > What ;
	CArray < int, int > Index ;

	CArray < CLine, CLine& > Line ;
	CArray < CPolyLine, CPolyLine& > Poly ;
	CArray < CText, CText& > Text ;
	CArray < CRect, CRect& > Rect ;
	CArray < CRect, CRect& > Ellipse ;

	CArray < int, int > R_Color ;		// 상자 선 색
	CArray < int, int > R_FillColor ;	// 상자 채우기 색
	CArray < int, int > E_Color ;		// 원 선 색
	CArray < int, int > E_FillColor ;	// 원 채우기 색

	CArray < int, int > R_Thickness ;			// 상자의 선 두께
	CArray < int, int > E_Thickness ;			// 원의 선 두께

	CArray < char, char > R_IsNoFill ;
	CArray < char, char > E_IsNoFill ;			// 채우기 색상이 없는지 확인하는 변수

	CArray < int, int > R_FillPattern ;
	CArray < int, int > E_FillPattern ;			// 채우기 패턴이 무엇인지 확인하는 변수

	CArray < int, int > R_LinePattern ;
	CArray < int, int > E_LinePattern ;			// 선 패턴이 무엇인지 확인하는 변수

	int L_Count ;			// 선 객체의 개수
	int P_Count ;			// PolyLine 객체의 개수
	int R_Count ;			// 상자 객체의 개수
	int E_Count ;			// 원 객체의 개수
	int Text_Count ;		// 텍스트 객체의 개수
	int G_Count ;			// 그룹화 객체의 개수

};