// HelloWorldDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HelloWorld.h"
#include "HelloWorldDlg.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEBUG_MSGBOX(X) MessageBox(X, "Debug", MB_OK);

/////////////////////////////////////////////////////////////////////////////
// CHelloWorldDlg dialog

CHelloWorldDlg::CHelloWorldDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelloWorldDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelloWorldDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_CursorX = 0;
}

void CHelloWorldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelloWorldDlg)
	DDX_Control(pDX, IDC_GDIPLUSPLOTCTRL1, m_GDIPlusPlot1);
	DDX_Control(pDX, IDC_GDIPLUSPLOTCTRL2, m_GDIPlusPlot2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHelloWorldDlg, CDialog)
	//{{AFX_MSG_MAP(CHelloWorldDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTT, OnButt)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelloWorldDlg message handlers

BOOL CHelloWorldDlg::OnInitDialog()
{
	int RANGE_MIN = -10;
    int RANGE_MAX = 10;
	unsigned int i;

	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_GDIPlusPlot1.SetXTime(TRUE);
	m_GDIPlusPlot1.SetCaption("RealTime");
	m_GDIPlusPlot1.AddElement(0);
	m_GDIPlusPlot1.AddElement(2);

	m_GDIPlusPlot2.SetXTrack(TRUE);
	m_GDIPlusPlot2.AddElement(3);
	m_GDIPlusPlot2.AddElement(4);
	m_GDIPlusPlot2.AddElement(0);
	for (i = 0; i < 168; i++) 
	{
		int randv = (((double) rand() / 
                         (double) RAND_MAX) * RANGE_MAX + RANGE_MIN);
		m_GDIPlusPlot2.PlotXY(i, randv, 0);
		m_GDIPlusPlot2.PlotXY(i, randv / 1.6, 1);
		m_GDIPlusPlot2.PlotXY(i, sin(randv), 2);
	}

	SetTimer(1, 100, NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHelloWorldDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHelloWorldDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHelloWorldDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	int RANGE_MIN = -6;
    int RANGE_MAX = 6;
	int randv = (((double) rand() / 
                         (double) RAND_MAX) * RANGE_MAX + RANGE_MIN);

	m_GDIPlusPlot1.PlotY(randv, 0);
	m_GDIPlusPlot1.PlotY(randv * 3, 1);
	
	CDialog::OnTimer(nIDEvent);
}

void CHelloWorldDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
}

void CHelloWorldDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
}

void CHelloWorldDlg::OnButt() 
{
	// TODO: Add your control notification handler code here
	m_GDIPlusPlot1.IsElementVisible(0, TRUE);
	m_GDIPlusPlot1.IsElementVisible(1, FALSE);
}

void CHelloWorldDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	m_GDIPlusPlot1.IsElementVisible(1, TRUE);
	m_GDIPlusPlot1.IsElementVisible(0, FALSE);
}
