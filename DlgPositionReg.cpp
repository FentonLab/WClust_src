// $Id: DlgPositionReg.cpp,v 1.2 2008/01/23 23:37:57 samn Exp $ 
// DlgPositionReg.cpp : implementation file
//

#include "stdafx.h"
#include "wclust.h"
#include "DlgPositionReg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPositionReg dialog


CDlgPositionReg::CDlgPositionReg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPositionReg::IDD, pParent),
	  m_type(0),
	  m_param(16.0f)
{
	//{{AFX_DATA_INIT(CDlgPositionReg)
	m_Edit = 20.0f;
	//}}AFX_DATA_INIT
}


void CDlgPositionReg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPositionReg)
	DDX_Text(pDX, IDC_EDIT, m_Edit);
	DDV_MinMaxFloat(pDX, m_Edit, 1.f, 1000.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPositionReg, CDialog)
	//{{AFX_MSG_MAP(CDlgPositionReg)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_SYNC, OnRadioSync)
	ON_BN_CLICKED(IDC_RADIO_CONST, OnRadioConst)
	ON_BN_CLICKED(IDC_RADIO_OTHER, OnRadioOther)
	ON_BN_CLICKED(IDC_RADIO_WITHOUT, OnRadioWithout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPositionReg message handlers

void CDlgPositionReg::DisableConst()
{
	CWnd::GetDlgItem(IDC_16_7)->EnableWindow(false);
	CWnd::GetDlgItem(IDC_20)->EnableWindow(false);
	CWnd::GetDlgItem(IDC_33_3)->EnableWindow(false);
	CWnd::GetDlgItem(IDC_40)->EnableWindow(false);
	CWnd::GetDlgItem(IDC_100)->EnableWindow(false);
	CWnd::GetDlgItem(IDC_EDIT)->EnableWindow(false);
}

void CDlgPositionReg::InitUI()
{
	switch(m_type)
	{
	case 0:
	case 4:
		OnRadioWithout();
		((CButton*) CWnd::GetDlgItem(IDC_RADIO_WITHOUT))->SetCheck(true);
		break;
	case 1:
		OnRadioSync();
		((CButton*) CWnd::GetDlgItem(IDC_RADIO_SYNC))->SetCheck(true);
		break;
	case 2:
		OnRadioConst();
		((CButton*) CWnd::GetDlgItem(IDC_RADIO_CONST))->SetCheck(true);
		break;
	case 3:
		OnRadioOther();
		((CButton*) CWnd::GetDlgItem(IDC_RADIO_OTHER))->SetCheck(true);
		break;
	}
}

BOOL CDlgPositionReg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	InitUI();
		
	CWnd::UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgPositionReg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	static bool bFirst = true;
	if(bFirst)
	{
		if ( !(m_MainDataStack->InBpfExist & 3) )
		{
			CWnd::GetDlgItem(IDC_RADIO_WITHOUT)->EnableWindow(false);
			((CButton*) CWnd::GetDlgItem(IDC_RADIO_SYNC))->SetCheck(true);
		}
		else
		{
			CWnd::GetDlgItem(IDC_RADIO_WITHOUT)->EnableWindow(true);
			((CButton*) CWnd::GetDlgItem(IDC_RADIO_WITHOUT))->SetCheck(true);
		}
		bFirst=false;
	}
	else
	{
		InitUI();
	}
}

void CDlgPositionReg::OnRadioSync() 
{
	DisableConst();
}

void CDlgPositionReg::OnRadioConst() 
{
	CWnd::GetDlgItem(IDC_16_7)->EnableWindow(true);
	CWnd::GetDlgItem(IDC_20)->EnableWindow(true);
	CWnd::GetDlgItem(IDC_33_3)->EnableWindow(true);
	CWnd::GetDlgItem(IDC_40)->EnableWindow(true);
	CWnd::GetDlgItem(IDC_100)->EnableWindow(true);
	CWnd::GetDlgItem(IDC_EDIT)->EnableWindow(false);

	if(m_param==16.0f)
		((CButton*) CWnd::GetDlgItem(IDC_16_7))->SetCheck(1);
	else if(m_param==20.0f)
		((CButton*) CWnd::GetDlgItem(IDC_20))->SetCheck(1);
	else if(m_param==33.0f)
		((CButton*) CWnd::GetDlgItem(IDC_33_3))->SetCheck(1);
	else if(m_param==40.0f)
		((CButton*) CWnd::GetDlgItem(IDC_40))->SetCheck(1);
	else if(m_param==100.0f)
		((CButton*) CWnd::GetDlgItem(IDC_100))->SetCheck(1);
}

void CDlgPositionReg::OnRadioOther() 
{
	DisableConst();
	CWnd::GetDlgItem(IDC_EDIT)->EnableWindow(true);
}

void CDlgPositionReg::OnRadioWithout() 
{
	DisableConst();
}

void CDlgPositionReg::OnOK() 
{
	if (((CButton*) CWnd::GetDlgItem(IDC_RADIO_SYNC))->GetCheck())
	{
		m_type = 1;
	}
	if (((CButton*) CWnd::GetDlgItem(IDC_RADIO_CONST))->GetCheck())
	{
		m_type = 2;
		if (((CButton*) CWnd::GetDlgItem(IDC_16_7))->GetCheck())
			m_param = 16.0f;
		if (((CButton*) CWnd::GetDlgItem(IDC_20))->GetCheck())
			m_param = 20.0f;
		if (((CButton*) CWnd::GetDlgItem(IDC_33_3))->GetCheck())
			m_param = 33.0f;
		if (((CButton*) CWnd::GetDlgItem(IDC_40))->GetCheck())
			m_param = 40.0f;
		if (((CButton*) CWnd::GetDlgItem(IDC_100))->GetCheck())
			m_param = 100.0f;
	}
	if (((CButton*) CWnd::GetDlgItem(IDC_RADIO_OTHER))->GetCheck())
	{
		m_type = 3;
		UpdateData(true);
		m_param = m_Edit;
	}
	if (((CButton*) CWnd::GetDlgItem(IDC_RADIO_WITHOUT))->GetCheck())
	{
		m_type = 4;
	}
	
	m_MainDataStack->m_MainSyncStack.OrganizeSync(m_type, m_param);

	CDialog::OnOK();
}

