#include "stdafx.h"
#include "CLine.h"
#include "CPolyLine.h"
#include "CText.h"

#pragma once

class CGroup {
public:
	CGroup () ;
	CRect GroupBox ;

	CArray < CLine, CLine& > Line ;
	CArray < CPolyLine, CPolyLine& > Poly ;
	CArray < CText, CText& > Text ;
	CArray < CRect, CRect& > Rect ;
	CArray < CRect, CRect& > Ellipse ;

	CArray < int, int > R_Color ;		// ���� �� ��
	CArray < int, int > R_FillColor ;	// ���� ä��� ��
	CArray < int, int > E_Color ;		// �� �� ��
	CArray < int, int > E_FillColor ;	// �� ä��� ��

	CArray < int, int > R_Thickness ;			// ������ �� �β�
	CArray < int, int > E_Thickness ;			// ���� �� �β�

	CArray < char, char > R_IsNoFill ;
	CArray < char, char > E_IsNoFill ;			// ä��� ������ ������ Ȯ���ϴ� ����

	CArray < int, int > R_FillPattern ;
	CArray < int, int > E_FillPattern ;			// ä��� ������ �������� Ȯ���ϴ� ����

	CArray < int, int > R_LinePattern ;
	CArray < int, int > E_LinePattern ;			// �� ������ �������� Ȯ���ϴ� ����

	int L_Count ;			// �� ��ü�� ����
	int P_Count ;			// PolyLine ��ü�� ����
	int R_Count ;			// ���� ��ü�� ����
	int E_Count ;			// �� ��ü�� ����
	int Text_Count ;		// �ؽ�Ʈ ��ü�� ����

};