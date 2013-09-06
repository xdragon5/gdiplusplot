#if !defined(AFX_GDIPLUSPLOT_H__3B027A5F_C060_4530_A485_0A4ECA813ED4__INCLUDED_)
#define AFX_GDIPLUSPLOT_H__3B027A5F_C060_4530_A485_0A4ECA813ED4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GDIPlusPlot.h : main header file for GDIPLUSPLOT.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotApp : See GDIPlusPlot.cpp for implementation.

class CGDIPlusPlotApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GDIPLUSPLOT_H__3B027A5F_C060_4530_A485_0A4ECA813ED4__INCLUDED)
