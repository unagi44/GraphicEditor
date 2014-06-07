#include "stdafx.h"
#include "CGroup.h"

CGroup::CGroup () {
	L_Count = 0 ;
	P_Count = 0 ;			// PolyLine 객체의 개수
	R_Count = 0 ;			// 상자 객체의 개수
	E_Count = 0 ;			// 원 객체의 개수
	Text_Count = 0 ;		// 텍스트 객체의 개수
}