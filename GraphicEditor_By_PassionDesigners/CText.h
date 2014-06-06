#include "stdafx.h"

#pragma once

class CText {
public:
	CText () ;
	char IsFont ;
	char IsNoFill ;
	CRect Text_Rect ;
	CPoint Location ;
	CString Text ;
	CFont Font ;
};