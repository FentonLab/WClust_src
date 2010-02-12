// DlgClustNum.cpp : implementation file
//

#include "stdafx.h"
#include "WClust.h"
#include "DlgClustNum.h"
#include ".\dlgclustnum.h"

// CDlgClustNum dialog

IMPLEMENT_DYNAMIC(CDlgClustNum, CDialog)
CDlgClustNum::CDlgClustNum(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgClustNum::IDD, pParent)
{
}

CDlgClustNum::~CDlgClustNum()
{
}

void CDlgClustNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgClustNum, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgClustNum message handlers

void CDlgClustNum::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_CLUST_NUMS);
	edit->SetFocus();
	CString strEdit;
	edit->GetWindowText(strEdit);

	int tmp=0;
	sscanf(strEdit.GetString(),"%d",&tmp);
	extern int gNumClusts;
	gNumClusts = tmp;

	OnOK();
}
