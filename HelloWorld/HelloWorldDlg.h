// HelloWorldDlg.h : header file
//
//{{AFX_INCLUDES()
#include "gdiplusplot.h"
//}}AFX_INCLUDES

#if !defined(AFX_HELLOWORLDDLG_H__797E3E4A_F730_4EF1_B730_482E80747225__INCLUDED_)
#define AFX_HELLOWORLDDLG_H__797E3E4A_F730_4EF1_B730_482E80747225__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHelloWorldDlg dialog

class CHelloWorldDlg : public CDialog
{
// Construction
public:
	CHelloWorldDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHelloWorldDlg)
	enum { IDD = IDD_HELLOWORLD_DIALOG };
	CGDIPlusPlot	m_GDIPlusPlot1;
	CGDIPlusPlot	m_GDIPlusPlot2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelloWorldDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHelloWorldDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButton1();
	afx_msg void OnButt();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_CursorX;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELLOWORLDDLG_H__797E3E4A_F730_4EF1_B730_482E80747225__INCLUDED_)
