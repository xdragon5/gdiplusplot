#if !defined(AFX_GDIPLUSPLOTPPG_H__4045DED1_F410_4624_A83D_F4CA43DEDE0B__INCLUDED_)
#define AFX_GDIPLUSPLOTPPG_H__4045DED1_F410_4624_A83D_F4CA43DEDE0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GDIPlusPlotPpg.h : Declaration of the CGDIPlusPlotPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotPropPage : See GDIPlusPlotPpg.cpp.cpp for implementation.

class CGDIPlusPlotPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGDIPlusPlotPropPage)
	DECLARE_OLECREATE_EX(CGDIPlusPlotPropPage)

// Constructor
public:
	CGDIPlusPlotPropPage();

// Dialog Data
	//{{AFX_DATA(CGDIPlusPlotPropPage)
	enum { IDD = IDD_PROPPAGE_GDIPLUSPLOT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CGDIPlusPlotPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GDIPLUSPLOTPPG_H__4045DED1_F410_4624_A83D_F4CA43DEDE0B__INCLUDED)
