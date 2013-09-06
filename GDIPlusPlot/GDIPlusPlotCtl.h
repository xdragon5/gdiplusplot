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

#if !defined(AFX_GDIPLUSPLOTCTL_H__80277A03_B015_441F_8E85_B50C79EE828B__INCLUDED_)
#define AFX_GDIPLUSPLOTCTL_H__80277A03_B015_441F_8E85_B50C79EE828B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GDIPlusPlotCtl.h : Declaration of the CGDIPlusPlotCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CGDIPlusPlotCtrl : See GDIPlusPlotCtl.cpp for implementation.

#include <vector>

// point abstruct data type
typedef struct
{
    double	x;
    double	y;
} point_t;

// element abstruct data type
typedef struct 
{
	short				    index;
	Gdiplus::Color		    color;
	BOOL				    visible;
	std::vector<point_t>    pointList;
} element_t;

class CGDIPlusPlotCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGDIPlusPlotCtrl)

// Constructor
public:
	CGDIPlusPlotCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGDIPlusPlotCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CGDIPlusPlotCtrl();

	DECLARE_OLECREATE_EX(CGDIPlusPlotCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGDIPlusPlotCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGDIPlusPlotCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGDIPlusPlotCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Message maps
	//{{AFX_MSG(CGDIPlusPlotCtrl)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CGDIPlusPlotCtrl)
	afx_msg BSTR GetCaption();
	afx_msg void SetCaption(LPCTSTR lpszNewValue);
	afx_msg BOOL GetXTime();
	afx_msg void SetXTime(BOOL bNewValue);
	afx_msg BSTR GetXLabel();
	afx_msg void SetXLabel(LPCTSTR lpszNewValue);
	afx_msg BSTR GetYLabel();
	afx_msg void SetYLabel(LPCTSTR lpszNewValue);
	afx_msg short GetInterval();
	afx_msg void SetInterval(short nNewValue);
	afx_msg BSTR GetAnnolabel();
	afx_msg void SetAnnolabel(LPCTSTR lpszNewValue);
	afx_msg BOOL GetXTrack();
	afx_msg void SetXTrack(BOOL bNewValue);
	afx_msg void PlotXY(double xValue, double yValue, short index);
	afx_msg void SetRange(double xMin, double xMax, double yMin, double yMax);
	afx_msg void PlotY(double newValue, short index);
	afx_msg void ClearGraph();
	afx_msg void AddElement(short color);
	afx_msg void IsElementVisible(short index, BOOL visible);
	afx_msg void SetXCursorPos(double xValue);
	afx_msg double GetQuadrantWidth();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CGDIPlusPlotCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CGDIPlusPlotCtrl)
	dispidCaption = 1L,
	dispidXTime = 2L,
	dispidXLabel = 3L,
	dispidYLabel = 4L,
	dispidInterval = 5L,
	dispidAnnolabel = 6L,
	dispidXTrack = 7L,
	dispidPlotXY = 8L,
	dispidSetRange = 9L,
	dispidPlotY = 10L,
	dispidClearGraph = 11L,
	dispidAddElement = 12L,
	dispidIsElementVisible = 13L,
	dispidSetXCursorPos = 14L,
	dispidGetQuadrantWidth = 15L,
	//}}AFX_DISP_ID
	};

// Attribute ÊôÐÔ
private:
	ULONG_PTR						m_gdiplusToken;
	Gdiplus::Graphics				*m_MemoryGraphics;
	BOOL							m_xTime, m_xTrack;
	BSTR							m_caption, m_xLabel, m_yLabel, m_annolabel;
	int								m_xMin, m_xMax, m_yMin, m_yMax, m_QuadrantX, m_QuadrantY, 
									m_QuadrantWidth, m_QuadrantHeight, m_CursorX, m_TrackX, 
                                    m_TrackY;
	short							m_ElementCount;
	std::vector<element_t>			m_ElementList;

// Operation ²Ù×÷
private:
	void m_DrawCaption(CRect rcBounds);
	void m_DrawXLabel(CRect rcBounds);
	void m_DrawYLabel(CRect rcBounds);
	void m_DrawQuadrant(CRect rcBounds);
    void m_DrawXScale();
    void m_DrawYScale();
    void m_DrawPlotXY();
    void m_DrawCursor(int x);
    void m_DrawXTimeCursor();
	void m_DrawCurve(short index);
    int m_GetPointY(int PointX, std::vector<point_t> pointList);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GDIPLUSPLOTCTL_H__80277A03_B015_441F_8E85_B50C79EE828B__INCLUDED)
