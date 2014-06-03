#pragma once
#include "stdafx.h"
#include "DrawObject.h"

class CLine
{
public:
	CLine () ;
	CLine ( CPoint Start, CPoint Last ) ;
	// 선의 시작점과 종착점의 좌표
	CPoint Start ;
	CPoint Last ;

	COLORREF Color ;	// 선의 색상 정보
	int Bold ;			// 선의 굵기 정보
	int Count ;			// 그려진 선의 갯수
	unsigned char Pattern ;		// 선의 패턴 정보
	CLine *Next ;		// 다음을 가리키는 선의 주소
	CLine *Pre ;		// 이전을 가리키는 선의 주소
	void Insert (CPoint Start, CPoint Last) ;	// 선 객체를 추가 한다.
	void Delete () ;							// 선 객체를 삭제 한다.
};