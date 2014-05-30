#include "stdafx.h"
#include "Line.h"

// CLine 생성자
CLine::CLine () {
	Count = 1 ;
	this -> Color = RGB ( 0, 0, 0 ) ;
	this -> Bold = 1 ;
	this -> Next = NULL ;
}

CLine::CLine ( CPoint Start, CPoint Last ) {
	this -> Start = Start ;
	this -> Last = Last ;
	this -> Color = RGB ( 0, 0, 0 ) ;
	this -> Bold = 1 ;
	this -> Next = NULL ;
}

void CLine::Insert ( CPoint Start, CPoint Last ) {
	CLine line ( Start, Last ) ;
	CLine *temp, *pre ;

	temp = this -> Next ;
	pre = this ;

	while ( temp != NULL ) {
		temp = temp -> Next ;
		pre = pre -> Next ;
	}

	temp = &line ;
	temp -> Count = pre -> Count + 1 ;
	temp -> Pre = pre ;
}

// 선을 삭제하는 함수
void CLine::Delete () {
	this -> Pre -> Next = this -> Next ;
	this -> Next -> Pre = this -> Pre ;

	if ( Count > 0 )
		Count-- ;

	delete this ;
}