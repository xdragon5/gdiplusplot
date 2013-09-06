/*
 * Copyright (C) 2009 by CCTEC ENGINEERING CO., LTD
 * Copyright (C) 2013 Deepin, Inc.                                                 
 *               2013 Leslie Zhai                                                  
 *                                                                              
 * Author:     Leslie Zhai <zhaixiang@linuxdeepin.com>                           
 * Maintainer: Leslie Zhai <zhaixiang@linuxdeepin.com>                           
 *                                                                              
 * This program is free software: you can redistribute it and/or modify         
 * it under the terms of the GNU General Public License as published by         
 * the Free Software Foundation, either version 3 of the License, or            
 * any later version.                                                           
 *                                                                              
 * This program is distributed in the hope that it will be useful,              
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                
 * GNU General Public License for more details.                                 
 *                                                                              
 * You should have received a copy of the GNU General Public License            
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.        
 */

// GDIPlusPlotCtl.cpp : Implementation of the CGDIPlusPlotCtrl ActiveX Control class.

#include "stdafx.h"
#include "GDIPlusPlot.h"
#include "GDIPlusPlotCtl.h"
#include "GDIPlusPlotPpg.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define XTIME_TIMER 1	
#define XTIME_TIMER_INTERVAL 100
#define RED_RGB Gdiplus::Color(255, 255, 0, 0)
#define BLACK_RGB Gdiplus::Color(255, 0, 0, 0)
#define GREEN_RGB Gdiplus::Color(255, 0, 255, 0)
#define WHITE_RGB Gdiplus::Color(255, 255, 255, 255)
#define YELLOW_RGB Gdiplus::Color(255, 255, 255, 0)
#define BLUE_RGB Gdiplus::Color(255, 0, 0, 255)
#define WHITE_ARGB(X) Gdiplus::Color(X, 255, 255, 255)
#define LIGHT_WHITE_RGB WHITE_ARGB(86)
#define CAPTION_SIZE 16
#define MARGIN 0
#define LABEL_SIZE 12
#define SCALE_SIZE 10
#define X_UNIT_ONE 10
#define Y_UNIT_ONE 5
#define BUFFER_SIZE 1024
#define CURVE_POINTS_SIZE 1024
#define X_CURSOR_STEP 20
#define MAX_RANGE_Y 40
#define MIN_RANGE_Y 10
#define DEBUG_MSGBOX(X) MessageBox(X, "DEBUG", MB_OK | MB_ICONINFORMATION)

IMPLEMENT_DYNCREATE(CGDIPlusPlotCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGDIPlusPlotCtrl, COleControl)
	//{{AFX_MSG_MAP(CGDIPlusPlotCtrl)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(OCM_COMMAND, OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CGDIPlusPlotCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CGDIPlusPlotCtrl)
	DISP_PROPERTY_EX(CGDIPlusPlotCtrl, "caption", GetCaption, SetCaption, VT_BSTR)
	DISP_PROPERTY_EX(CGDIPlusPlotCtrl, "xTime", GetXTime, SetXTime, VT_BOOL)
	DISP_PROPERTY_EX(CGDIPlusPlotCtrl, "xLabel", GetXLabel, SetXLabel, VT_BSTR)
	DISP_PROPERTY_EX(CGDIPlusPlotCtrl, "yLabel", GetYLabel, SetYLabel, VT_BSTR)
	DISP_PROPERTY_EX(CGDIPlusPlotCtrl, "interval", GetInterval, SetInterval, VT_I2)
	DISP_PROPERTY_EX(CGDIPlusPlotCtrl, "annolabel", GetAnnolabel, SetAnnolabel, VT_BSTR)
	DISP_PROPERTY_EX(CGDIPlusPlotCtrl, "xTrack", GetXTrack, SetXTrack, VT_BOOL)
	DISP_FUNCTION(CGDIPlusPlotCtrl, "PlotXY", PlotXY, VT_EMPTY, VTS_R8 VTS_R8 VTS_I2)
	DISP_FUNCTION(CGDIPlusPlotCtrl, "SetRange", SetRange, VT_EMPTY, VTS_R8 VTS_R8 VTS_R8 VTS_R8)
	DISP_FUNCTION(CGDIPlusPlotCtrl, "PlotY", PlotY, VT_EMPTY, VTS_R8 VTS_I2)
	DISP_FUNCTION(CGDIPlusPlotCtrl, "ClearGraph", ClearGraph, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGDIPlusPlotCtrl, "AddElement", AddElement, VT_EMPTY, VTS_I2)
	DISP_FUNCTION(CGDIPlusPlotCtrl, "IsElementVisible", IsElementVisible, VT_EMPTY, VTS_I2 VTS_BOOL)
	DISP_FUNCTION(CGDIPlusPlotCtrl, "SetXCursorPos", SetXCursorPos, VT_EMPTY, VTS_R8)
	DISP_FUNCTION(CGDIPlusPlotCtrl, "GetQuadrantWidth", GetQuadrantWidth, VT_R8, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CGDIPlusPlotCtrl, COleControl)
	//{{AFX_EVENT_MAP(CGDIPlusPlotCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGDIPlusPlotCtrl, 1)
	PROPPAGEID(CGDIPlusPlotPropPage::guid)
END_PROPPAGEIDS(CGDIPlusPlotCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIPlusPlotCtrl, "GDIPLUSPLOT.GDIPlusPlotCtrl.1",
	0xdcd24674, 0xd4a1, 0x4ece, 0xb6, 0xa0, 0xd8, 0x54, 0xdb, 0x5a, 0xd6, 0x92)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CGDIPlusPlotCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DGDIPlusPlot =
		{ 0x6bb19a9a, 0x4f5, 0x42de, { 0x94, 0x95, 0xec, 0xc3, 0x19, 0xd4, 0x9e, 0x81 } };
const IID BASED_CODE IID_DGDIPlusPlotEvents =
		{ 0xd60098a8, 0x5b4e, 0x4b86, { 0x91, 0x1a, 0xf2, 0xc6, 0xb5, 0x41, 0x1c, 0xb3 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwGDIPlusPlotOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGDIPlusPlotCtrl, IDS_GDIPLUSPLOT, _dwGDIPlusPlotOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotCtrl::CGDIPlusPlotCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIPlusPlotCtrl

BOOL CGDIPlusPlotCtrl::CGDIPlusPlotCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_GDIPLUSPLOT,
			IDB_GDIPLUSPLOT,
			afxRegApartmentThreading,
			_dwGDIPlusPlotOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotCtrl::CGDIPlusPlotCtrl - Constructor

CGDIPlusPlotCtrl::CGDIPlusPlotCtrl()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;

	InitializeIIDs(&IID_DGDIPlusPlot, &IID_DGDIPlusPlotEvents);

	// Initial GDI+ related handler
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
	m_MemoryGraphics = NULL;

	m_caption	    = L"GDIPlusPlot";	    // Default caption
	m_xLabel	    = L"X AXIS";		    // Default X axis label
	m_yLabel	    = L"Y AXIS";		    // Default Y axis label
	m_annolabel		= L"";					// Default anno label
	m_xTime		    = FALSE;			    // Disable auto-timer for X axis
	m_xTrack		= FALSE;				// Disable track on X axis
    m_xMin		    = 0;                    // Default x min range
	m_xMax		    = 100;                  // Default x max range
	m_yMin		    = -10;                  // Default y min range
	m_yMax		    = 10;                   // Default y max range
	m_CursorX		= 0;
	m_ElementCount	= 0;
}


/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotCtrl::~CGDIPlusPlotCtrl - Destructor

CGDIPlusPlotCtrl::~CGDIPlusPlotCtrl()
{
	// Release GDI+ related handler
	if (m_MemoryGraphics) 
    {
        delete m_MemoryGraphics; 
        m_MemoryGraphics = NULL;
    }
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
}

// Draw caption
void CGDIPlusPlotCtrl::m_DrawCaption(CRect rcBounds) 
{
    // See the example of DrawString section of GDI+ in MSDN
	Gdiplus::FontFamily		fontFamily(L"Courier New");
	Gdiplus::Font			font(&fontFamily, CAPTION_SIZE, Gdiplus::FontStyleBold, 
            Gdiplus::UnitPixel);
	Gdiplus::RectF			layoutRect(0.0f, MARGIN, rcBounds.Width(), CAPTION_SIZE);
	Gdiplus::StringFormat	format;
	Gdiplus::SolidBrush		solidBrush(BLACK_RGB);

	format.SetAlignment(Gdiplus::StringAlignmentCenter);
	m_MemoryGraphics->DrawString(m_caption, -1, &font, layoutRect, &format, &solidBrush);
}

// Draw X axis label
void CGDIPlusPlotCtrl::m_DrawXLabel(CRect rcBounds) 
{
	Gdiplus::FontFamily		fontFamily(L"Courier New");
	Gdiplus::Font			font(&fontFamily, LABEL_SIZE, Gdiplus::FontStyleRegular, 
            Gdiplus::UnitPixel);
	Gdiplus::RectF			layoutRect(0.0f, rcBounds.Height() - LABEL_SIZE - MARGIN, 
            rcBounds.Width(), LABEL_SIZE);
	Gdiplus::StringFormat	format;
	Gdiplus::SolidBrush		solidBrush(BLACK_RGB);

	format.SetAlignment(Gdiplus::StringAlignmentCenter);
	m_MemoryGraphics->DrawString(m_xLabel, -1, &font, layoutRect, &format, &solidBrush);
}

// Draw Y axis label
void CGDIPlusPlotCtrl::m_DrawYLabel(CRect rcBounds) 
{
	Gdiplus::FontFamily		fontFamily(L"Courier New");
	Gdiplus::Font			font(&fontFamily, LABEL_SIZE, Gdiplus::FontStyleRegular, 
            Gdiplus::UnitPixel);
	Gdiplus::RectF			layoutRect(0.0f, 0.0f, LABEL_SIZE, rcBounds.Height());
	Gdiplus::StringFormat	format;
	Gdiplus::SolidBrush		solidBrush(BLACK_RGB);

	// FIXME: *BUG* fail to vertical
	format.SetFormatFlags(Gdiplus::StringFormatFlagsDirectionVertical | 
		Gdiplus::StringFormatFlagsDirectionRightToLeft);
	format.SetAlignment(Gdiplus::StringAlignmentCenter);
	m_MemoryGraphics->DrawString(m_yLabel, -1, &font, layoutRect, &format, &solidBrush);
}

int CGDIPlusPlotCtrl::m_GetPointY(int PointX, std::vector<point_t> pointList) 
{
    std::vector<point_t>::iterator point;

    for (point = pointList.begin(); point != pointList.end(); point++) 
    {
        // FIXME: Big number eat small one
        if ((*point).x == PointX) 
            return ((*point).y - m_QuadrantHeight) / (m_yMax - m_yMin);
    }
    return 0;
}

void CGDIPlusPlotCtrl::m_DrawCurve(short index) 
{
    Gdiplus::Point                  curvePoints[CURVE_POINTS_SIZE];
	std::vector<element_t>::iterator	elementIter;
	std::vector<point_t>::iterator    pointIter;
    Gdiplus::FontFamily		        fontFamily(L"Courier New");
	Gdiplus::Font			        font(&fontFamily, SCALE_SIZE, Gdiplus::FontStyleRegular, 
                                        Gdiplus::UnitPixel);
    Gdiplus::StringFormat	        format;
	Gdiplus::SolidBrush		        solidBrush(WHITE_RGB);
    wchar_t                         xTrack[BUFFER_SIZE];
	unsigned int					i, j;
	
    format.SetAlignment(Gdiplus::StringAlignmentNear);

	for (elementIter = m_ElementList.begin(), j = 0; 
            elementIter != m_ElementList.end(); elementIter++, j++) 
	{
		// Find the element with the index if it is visible
		if (index == (*elementIter).index && (*elementIter).visible) 
		{
			Gdiplus::Pen pen((*elementIter).color);

			// Cleanup curve points array
			memset(curvePoints, 0, CURVE_POINTS_SIZE);
			for (pointIter = (*elementIter).pointList.begin(), i = 0; 
				pointIter != (*elementIter).pointList.end(); pointIter++, i++) 
			{
                // Make the original point
				if (i == 0) 
                {
                    Gdiplus::Point point(m_QuadrantX, m_QuadrantHeight / 2);
                    curvePoints[i] = point; 
                    continue;
                }
                Gdiplus::Point point((*pointIter).x, (*pointIter).y);
				curvePoints[i] = point;
			}
			m_MemoryGraphics->DrawCurve(&pen, curvePoints, i);
            
            // Draw track cursor value
            if (m_xTrack) 
            {
                Gdiplus::RectF layoutRect(m_TrackX, m_QuadrantY + SCALE_SIZE * j, 
                    Y_UNIT_ONE * 16, SCALE_SIZE);

                memset(xTrack, 0, BUFFER_SIZE);
                swprintf( xTrack, L"%d", m_GetPointY(m_TrackX, (*elementIter).pointList) );
                m_MemoryGraphics->DrawString(xTrack, -1, &font, layoutRect, 
                    &format, &solidBrush);
            }
			break;
		}
	}
}

void CGDIPlusPlotCtrl::m_DrawPlotXY() 
{
    unsigned int e;

    if (m_xTrack && m_QuadrantX < m_TrackX) m_DrawCursor(m_TrackX);

	// Draw multi curve
	for (e = 0; e < m_ElementCount; e++) 
	{
		m_DrawCurve(e);
	}
}

void CGDIPlusPlotCtrl::m_DrawCursor(int x) 
{
    Gdiplus::Pen pen(RED_RGB);

    m_MemoryGraphics->DrawLine(&pen, x, m_QuadrantY, x, m_QuadrantY + m_QuadrantHeight);
}

// Draw the cursor flying with the timer for X axis
void CGDIPlusPlotCtrl::m_DrawXTimeCursor() 
{
	// Cleanup when out of range
    if (m_QuadrantWidth < m_CursorX) 
        ClearGraph();
    
    m_DrawCursor(m_QuadrantX + m_CursorX);
    // Draw Y axis depending on the value via PlotY
    m_DrawPlotXY();

    // Move the X axis cursor
    m_CursorX += X_CURSOR_STEP;
}

// Draw the scale for X axis
void CGDIPlusPlotCtrl::m_DrawXScale() 
{
    Gdiplus::FontFamily		fontFamily(L"Courier New");
	Gdiplus::Font			font(&fontFamily, SCALE_SIZE, Gdiplus::FontStyleRegular, 
            Gdiplus::UnitPixel);
    Gdiplus::StringFormat	format;
	Gdiplus::SolidBrush		solidBrush(LIGHT_WHITE_RGB);
    wchar_t                 pScale[BUFFER_SIZE];
    Gdiplus::Pen            pen(LIGHT_WHITE_RGB);
    int                     x1, x2;
    int                     y1 = m_QuadrantY, y2 = m_QuadrantY + m_QuadrantHeight;
    unsigned int            i, pCount = (m_xMax - m_xMin) / X_UNIT_ONE;
    SYSTEMTIME              st;

    GetLocalTime(&st);
    format.SetAlignment(Gdiplus::StringAlignmentNear);

    // At least there are 3 scales
    if (pCount == 0) pCount = 2;
    for (i = 0; i < pCount + 1; i++) 
    {
        x1 = x2 = m_QuadrantX + (m_QuadrantWidth / pCount) * i;
        if (X_UNIT_ONE < m_QuadrantWidth - x1) m_MemoryGraphics->DrawLine(&pen, x1, y1, x2, y2);
        // FIXME: Is the width suitable
        Gdiplus::RectF layoutRect(x1, y2 - SCALE_SIZE, X_UNIT_ONE * 16, SCALE_SIZE);
	    memset(pScale, 0, BUFFER_SIZE);
        if (m_xTime) 
        {
            swprintf(pScale, L"%d:%d:%d:%d", st.wHour, st.wMinute, st.wSecond, 
                    st.wMilliseconds / 100 + i);
        } 
        else 
        {
            swprintf(pScale, L"%d", m_xMin + X_UNIT_ONE * i);
        }
        if (i != 0 && i != pCount) m_MemoryGraphics->DrawString(pScale, -1, &font, layoutRect, &format, &solidBrush);
    }
}

// Draw Y axis scale
void CGDIPlusPlotCtrl::m_DrawYScale() 
{
    Gdiplus::FontFamily		fontFamily(L"Courier New");
	Gdiplus::Font			font(&fontFamily, SCALE_SIZE, Gdiplus::FontStyleRegular, 
            Gdiplus::UnitPixel);
    Gdiplus::StringFormat	format;
	Gdiplus::SolidBrush		solidBrush(WHITE_RGB), lightBrush(LIGHT_WHITE_RGB);
    wchar_t                 pScale[BUFFER_SIZE];
    Gdiplus::Pen            pen(LIGHT_WHITE_RGB);
    int                     x1 = m_QuadrantX, x2 = m_QuadrantX + m_QuadrantWidth;
    int                     y1, y2;
    unsigned int            i, pCount = (m_yMax - m_yMin) / Y_UNIT_ONE;

    format.SetAlignment(Gdiplus::StringAlignmentNear);

    // At least there are 3 scales
    if (pCount == 0) 
        pCount = 2;
    for (i = 0; i < pCount + 1; i++) 
    {
        y1 = y2 = m_QuadrantY + (m_QuadrantHeight / pCount) * i;
        if (Y_UNIT_ONE < m_QuadrantHeight - y1) 
        {
            m_MemoryGraphics->DrawLine(&pen, x1, y1, x2, y2);
        }
	    memset(pScale, 0, BUFFER_SIZE);
        // Draw Y min and max only
        if (i == 0) 
        {
            Gdiplus::RectF layoutRect(x1, y2, Y_UNIT_ONE * 6, SCALE_SIZE);
            swprintf(pScale, L"%d", m_yMin);
			m_MemoryGraphics->DrawString(pScale, -1, &font, layoutRect, &format, &lightBrush);
        }
        // Draw Y max here
        if (i == pCount) 
        {
            Gdiplus::RectF layoutRect(x1, y2 - SCALE_SIZE, Y_UNIT_ONE * 6, SCALE_SIZE);
            swprintf(pScale, L"%d", m_yMax);
			m_MemoryGraphics->DrawString(pScale, -1, &font, layoutRect, &format, &lightBrush);
        }
    }
	if (m_xTime) 
	{
		Gdiplus::RectF layoutRect(x1, m_QuadrantY + m_QuadrantHeight / 2 - SCALE_SIZE, 
			Y_UNIT_ONE * 6, SCALE_SIZE);
		m_MemoryGraphics->DrawString(m_annolabel, -1, &font, layoutRect, &format, &solidBrush);
	}
}

// Draw quadrant
void CGDIPlusPlotCtrl::m_DrawQuadrant(CRect rcBounds) 
{
	Gdiplus::SolidBrush	solidBrush(BLACK_RGB);

	//m_QuadrantX = LABEL_SIZE; 
    m_QuadrantX = 0;
    //m_QuadrantY = CAPTION_SIZE + MARGIN;
    m_QuadrantY = 0; 
    //m_QuadrantWidth = rcBounds.Width() - LABEL_SIZE - MARGIN; 
    m_QuadrantWidth = rcBounds.Width();
    //m_QuadrantHeight = rcBounds.Height() - CAPTION_SIZE - LABEL_SIZE - MARGIN * 2;
    m_QuadrantHeight = rcBounds.Height();

    // Draw each layer
    m_MemoryGraphics->FillRectangle(&solidBrush, m_QuadrantX, m_QuadrantY, m_QuadrantWidth, 
            m_QuadrantHeight);

    // Draw X axis related thing
    m_DrawXScale();

    // Draw Y axis related thing
    m_DrawYScale();

    // Draw XTime cursor
    if (m_xTime) 
        m_DrawXTimeCursor();
    else 
        m_DrawPlotXY();
}

/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotCtrl::OnDraw - Drawing function

void CGDIPlusPlotCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	Gdiplus::Graphics pGraphics(pdc->m_hDC);
	Gdiplus::Bitmap pBitmap(rcBounds.Width(), rcBounds.Height());

	// Cache the GDI+ Graphics object handler
	m_MemoryGraphics = Gdiplus::Graphics::FromImage(&pBitmap);

	// Anti alias
	m_MemoryGraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

	// Fill the background color with the parent hWnd`s
	OLE_COLOR pWndBkColor = AmbientBackColor();
	Gdiplus::Rect pWndRect(0, 0, rcBounds.Width(), rcBounds.Height());
	COLORREF pWndRGB = TranslateColor(pWndBkColor);
	Gdiplus::SolidBrush pWndBg(Gdiplus::Color(255, GetRValue(pWndRGB), 
		GetGValue(pWndRGB), GetBValue(pWndRGB)));
	m_MemoryGraphics->FillRectangle(&pWndBg, pWndRect);

	// Draw caption
	m_DrawCaption(rcBounds);
	
	// Draw X axis label
	//m_DrawXLabel(rcBounds);

	// TODO: Draw Y axis label
	//m_DrawYLabel(rcBounds);

	// TODO: Draw quadrant
	m_DrawQuadrant(rcBounds);

    // TODO: Multi framebuffer
	pGraphics.DrawImage(&pBitmap, rcBounds.left, rcBounds.top);

	// Cleanup Gdiplus::Graphics object
	if (m_MemoryGraphics) 
    {
        delete m_MemoryGraphics; 
        m_MemoryGraphics = NULL;
    }
}


/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotCtrl::DoPropExchange - Persistence support

void CGDIPlusPlotCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotCtrl::OnResetState - Reset control to default state

void CGDIPlusPlotCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotCtrl::IsSubclassedControl - This is a subclassed control

BOOL CGDIPlusPlotCtrl::IsSubclassedControl()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotCtrl::OnOcmCommand - Handle command messages

LRESULT CGDIPlusPlotCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif

	// TODO: Switch on wNotifyCode here.

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotCtrl message handlers

void CGDIPlusPlotCtrl::OnTimer(UINT nIDEvent) 
{
	InvalidateControl();

	COleControl::OnTimer(nIDEvent);
}

void CGDIPlusPlotCtrl::PlotXY(double xValue, double yValue, short index) 
{
    point_t                         p;
	std::vector<element_t>::iterator  pIter;

	// index is bigger than element count
	if (m_ElementCount < index) 
        return ;

    p.x = m_QuadrantX + m_QuadrantWidth / (m_xMax - m_xMin) * (xValue - m_xMin);
    p.y = m_QuadrantY + m_QuadrantHeight / (m_yMax - m_yMin) * (yValue - m_yMin);

	for (pIter = m_ElementList.begin(); pIter != m_ElementList.end(); pIter++) 
	{
		if (index == (*pIter).index) 
		{
            (*pIter).pointList.push_back(p);
			break;
		}
	}
}

BSTR CGDIPlusPlotCtrl::GetCaption() 
{
	return m_caption;
}

void CGDIPlusPlotCtrl::SetCaption(LPCTSTR lpszNewValue) 
{
	CString strTmp;

	strTmp = lpszNewValue;
	m_caption = strTmp.AllocSysString();

	SetModifiedFlag();
}

BOOL CGDIPlusPlotCtrl::GetXTime() 
{
	return m_xTime;
}

void CGDIPlusPlotCtrl::SetXTime(BOOL bNewValue) 
{
	m_xTime = bNewValue;
    if (m_xTime) SetTimer(XTIME_TIMER, XTIME_TIMER_INTERVAL, NULL);
	
    SetModifiedFlag();
}

void CGDIPlusPlotCtrl::SetRange(double xMin, double xMax, double yMin, double yMax) 
{
	m_xMin = xMin; 
	m_xMax = xMax; 
	m_yMin = yMin; 
	m_yMax = yMax;
}

BSTR CGDIPlusPlotCtrl::GetXLabel() 
{
	return m_xLabel;
}

void CGDIPlusPlotCtrl::SetXLabel(LPCTSTR lpszNewValue) 
{
	CString strTmp;

	strTmp = lpszNewValue;
	m_xLabel = strTmp.AllocSysString();

	SetModifiedFlag();
}

BSTR CGDIPlusPlotCtrl::GetYLabel() 
{
	return m_yLabel;
}

void CGDIPlusPlotCtrl::SetYLabel(LPCTSTR lpszNewValue) 
{
	CString strTmp;

	strTmp = lpszNewValue;
	m_yLabel = strTmp.AllocSysString();

	SetModifiedFlag();
}

short CGDIPlusPlotCtrl::GetInterval() 
{
	return 0;
}

void CGDIPlusPlotCtrl::SetInterval(short nNewValue) 
{
	SetModifiedFlag();
}

void CGDIPlusPlotCtrl::PlotY(double newValue, short index) 
{
	point_t                         p;
	std::vector<element_t>::iterator  pIter;

	// index is bigger than element count
	if (m_ElementCount < index) 
        return ;

    p.x = m_QuadrantX + m_CursorX;
    p.y = m_QuadrantY + m_QuadrantHeight / (m_yMax - m_yMin) * (newValue - m_yMin);

	for (pIter = m_ElementList.begin(); pIter != m_ElementList.end(); pIter++) 
	{
		if (index == (*pIter).index) 
		{
			(*pIter).pointList.push_back(p);
			break;
		}
	}

	SetModifiedFlag();
}

BSTR CGDIPlusPlotCtrl::GetAnnolabel() 
{
	return m_annolabel;
}

void CGDIPlusPlotCtrl::SetAnnolabel(LPCTSTR lpszNewValue) 
{
	CString strTmp;

	strTmp = lpszNewValue;
	m_annolabel = strTmp.AllocSysString();

	SetModifiedFlag();
}

void CGDIPlusPlotCtrl::AddElement(short color) 
{
	element_t element;

	switch (color) 
	{
	default:
	case 0:
		element.color = GREEN_RGB;
		break;
	case 1:
		element.color = RED_RGB;
		break;
	case 2:
		element.color = BLUE_RGB;
		break;
	case 3:
		element.color = WHITE_RGB;
		break;
	case 4:
		element.color = YELLOW_RGB;
		break;
	}

	element.index = m_ElementCount;
	element.visible = TRUE;
	m_ElementList.push_back(element);
	m_ElementCount++;
}

void CGDIPlusPlotCtrl::ClearGraph() 
{
	std::vector<element_t>::iterator pIter;

	m_CursorX = 0;

	for (pIter = m_ElementList.begin(); pIter != m_ElementList.end(); pIter++) 
	{
		(*pIter).pointList.clear();
	}
}

void CGDIPlusPlotCtrl::IsElementVisible(short index, BOOL visible) 
{
	std::vector<element_t>::iterator pIter;

	// index is bigger than element count
	if (m_ElementCount < index) 
        return ;

	for (pIter = m_ElementList.begin(); pIter != m_ElementList.end(); pIter++) 
	{
		if (index == (*pIter).index) 
		{
			(*pIter).visible = visible;
			break;
		}
	}
}

void CGDIPlusPlotCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);

	m_QuadrantX = LABEL_SIZE; 
    m_QuadrantY = CAPTION_SIZE + MARGIN; 
    m_QuadrantWidth = cx - LABEL_SIZE - MARGIN; 
    m_QuadrantHeight = cy - CAPTION_SIZE - LABEL_SIZE - MARGIN * 2;
}

BOOL CGDIPlusPlotCtrl::GetXTrack() 
{
	return m_xTrack;
}

void CGDIPlusPlotCtrl::SetXTrack(BOOL bNewValue) 
{
	m_xTrack = bNewValue;

	SetModifiedFlag();
}

void CGDIPlusPlotCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (!m_xTrack || point.x < m_QuadrantX) 
        return ;

    m_TrackX = point.x;
    m_TrackY = point.y;

    InvalidateControl();

	COleControl::OnMouseMove(nFlags, point);
}

void CGDIPlusPlotCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
    std::vector<element_t>::iterator	elementIter;
	std::vector<point_t>::iterator    pointIter;

    if (!m_xTime) 
        return ;

	if (point.x < m_QuadrantWidth && 0 < point.x && 
            point.y < m_QuadrantHeight && 0 < point.y) 
    {
        if (abs(m_yMin) < MAX_RANGE_Y && abs(m_yMax) < MAX_RANGE_Y) 
        {
            m_yMin *= 2;
            m_yMax *= 2;
            if (!m_xTime) 
            {
                for (elementIter = m_ElementList.begin(); elementIter != m_ElementList.end(); elementIter++) 
                {
                    for (pointIter = (*elementIter).pointList.begin(); 
                        pointIter != (*elementIter).pointList.end(); pointIter++) 
                    {
						// FIXME: Relative postion issue but might be suitable in realtime mode
                        (*pointIter).y /= 2;
                    }
                }
            }
            InvalidateControl();
        }
    } 
	
	COleControl::OnLButtonDown(nFlags, point);
}

void CGDIPlusPlotCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	std::vector<element_t>::iterator	elementIter;
	std::vector<point_t>::iterator    pointIter;

    if (!m_xTime) return ;

	if (point.x < m_QuadrantWidth && 0 < point.x && 
            point.y < m_QuadrantHeight && 0 < point.y) 
    {
        if (MIN_RANGE_Y < abs(m_yMin) && MIN_RANGE_Y < abs(m_yMax)) 
        {
            m_yMin /= 2;
            m_yMax /= 2;
            if (!m_xTime) 
            {
                for (elementIter = m_ElementList.begin(); 
                        elementIter != m_ElementList.end(); elementIter++) 
                {
                    for (pointIter = (*elementIter).pointList.begin(); 
                        pointIter != (*elementIter).pointList.end(); pointIter++) 
                    {
						(*pointIter).y *= 2;
                    }
                }
            }
            InvalidateControl();
        }
    } 
	
	COleControl::OnRButtonDown(nFlags, point);
}

void CGDIPlusPlotCtrl::SetXCursorPos(double xValue) 
{
	m_CursorX = xValue;
}

double CGDIPlusPlotCtrl::GetQuadrantWidth() 
{
	return m_QuadrantWidth;
}
