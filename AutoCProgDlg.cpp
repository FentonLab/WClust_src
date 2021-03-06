// AutoCProgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WClust.h"
#include "AutoCProgDlg.h"
#include ".\autocprogdlg.h"


// AutoCProgDlg dialog

IMPLEMENT_DYNAMIC(AutoCProgDlg, CDialog)
AutoCProgDlg::AutoCProgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AutoCProgDlg::IDD, pParent)
{
}

AutoCProgDlg::~AutoCProgDlg()
{
}

void AutoCProgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_AUTO_C, m_progBar);
}


BEGIN_MESSAGE_MAP(AutoCProgDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_GETDLGCODE()
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// AutoCProgDlg message handlers

void AutoCProgDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	m_bRunning = false;
//	OnCancel();
	DestroyWindow();
}

void AutoCProgDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
}

UINT AutoCProgDlg::OnGetDlgCode()
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnGetDlgCode();
}

int AutoCProgDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_bRunning = true;

	return 0;
}

void AutoCProgDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
}
