#include "stdafx.h"

#pragma once

class CLine {
public:
	CLine () ;
	CLine ( CPoint Start, CPoint Last ) ;
	CPoint Start, Last ;
	COLORREF L_Color ;
	COLORREF L_FillColor ;
};