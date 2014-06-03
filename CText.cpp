#include "stdafx.h"
#include "CText.h"

CText::CText () {
	VERIFY(Font.CreateFont(18, 10, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,        
							CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"))) ;
}