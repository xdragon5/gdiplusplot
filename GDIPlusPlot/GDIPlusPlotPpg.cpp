// GDIPlusPlotPpg.cpp : Implementation of the CGDIPlusPlotPropPage property page class.

#include "stdafx.h"
#include "GDIPlusPlot.h"
#include "GDIPlusPlotPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGDIPlusPlotPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGDIPlusPlotPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CGDIPlusPlotPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIPlusPlotPropPage, "GDIPLUSPLOT.GDIPlusPlotPropPage.1",
	0x9bc6c497, 0x1072, 0x4f56, 0x9b, 0x67, 0x70, 0x59, 0xb6, 0x30, 0x1b, 0xbf)


/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotPropPage::CGDIPlusPlotPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIPlusPlotPropPage

BOOL CGDIPlusPlotPropPage::CGDIPlusPlotPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GDIPLUSPLOT_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotPropPage::CGDIPlusPlotPropPage - Constructor

CGDIPlusPlotPropPage::CGDIPlusPlotPropPage() :
	COlePropertyPage(IDD, IDS_GDIPLUSPLOT_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CGDIPlusPlotPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotPropPage::DoDataExchange - Moves data between page and properties

void CGDIPlusPlotPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CGDIPlusPlotPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotPropPage message handlers
