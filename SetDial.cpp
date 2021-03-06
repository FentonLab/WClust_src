// SetDial.cpp : implementation file
//

#include "stdafx.h"
#include "wclust.h"
#include "SetDial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDial dialog


CSetDial::CSetDial(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDial::IDD, pParent)
{
	m_Type = 0;
	//{{AFX_DATA_INIT(CSetDial)
	m_EdFirstEv = 0;
	m_EdLastEv = 0;
	m_EdPrecent = 0;
	//}}AFX_DATA_INIT
}


void CSetDial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDial)
	DDX_Text(pDX, IDC_EDIT_FIRST_EV, m_EdFirstEv);
	DDX_Text(pDX, IDC_EDIT_LAST_EV, m_EdLastEv);
	DDX_Text(pDX, IDC_EDIT_PERCENT, m_EdPrecent);
	DDV_MinMaxInt(pDX, m_EdPrecent, 1, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetDial, CDialog)
	//{{AFX_MSG_MAP(CSetDial)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDial message handlers

void CSetDial::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (m_Type == 1)
		SetWindowText(TEXT("Set amount spikes to view"));
	if (m_Type == 2)
		SetWindowText(TEXT("Set amount vectors to view"));
	if (m_ClMode == 0)
		((CButton*) CWnd::GetDlgItem(IDC_RD_RANDOM))->SetCheck(1);
	if (m_ClMode == 1)
		((CButton*) CWnd::GetDlgItem(IDC_RD_EXCLUDE))->SetCheck(1);
	if (m_ClMode == 2)
		((CButton*) CWnd::GetDlgItem(IDC_RD_WEIGHTED))->SetCheck(1);
	
}

void CSetDial::OnOK() 
{
	if (((CButton*) CWnd::GetDlgItem(IDC_RD_RANDOM))->GetCheck())
		m_ClMode = 0;
	if (((CButton*) CWnd::GetDlgItem(IDC_RD_EXCLUDE))->GetCheck())
		m_ClMode = 1;
	if (((CButton*) CWnd::GetDlgItem(IDC_RD_WEIGHTED))->GetCheck())
		m_ClMode = 2;

	CDialog::OnOK();
}
