#include "stdafx.h"
#include "CLine.h"

CLine::CLine () {}

CLine::CLine ( CPoint Start, CPoint Last ) {
	this->Start = Start ;
	this->Last = Last ;
	this->L_Color = RGB (0,0,0) ;
}