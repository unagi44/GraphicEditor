#pragma once
#include "stdafx.h"
#include "DrawObject.h"

class CLine
{
public:
	CLine () ;
	CLine ( CPoint Start, CPoint Last ) ;
	// ���� �������� �������� ��ǥ
	CPoint Start ;
	CPoint Last ;

	COLORREF Color ;	// ���� ���� ����
	int Bold ;			// ���� ���� ����
	int Count ;			// �׷��� ���� ����
	unsigned char Pattern ;		// ���� ���� ����
	CLine *Next ;		// ������ ����Ű�� ���� �ּ�
	CLine *Pre ;		// ������ ����Ű�� ���� �ּ�
	void Insert (CPoint Start, CPoint Last) ;	// �� ��ü�� �߰� �Ѵ�.
	void Delete () ;							// �� ��ü�� ���� �Ѵ�.
};