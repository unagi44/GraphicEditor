#include "stdafx.h"
#include "CLine.h"

CLine::CLine () {}

CLine::CLine ( CPoint Start, CPoint Last ) {
	this->Start = Start ;
	this->Last = Last ;
}