#include "stdafx.h"

#pragma once

class CPolyLine {
public:
	CPolyLine () ;
	CArray < CPoint, CPoint& > Poly_point ;
	COLORREF P_Color ;
};