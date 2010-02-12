// $Id: DlgFLClust.cpp,v 1.2 2008/11/27 20:30:33 samn Exp $ 
// DlgFLClust.cpp : implementation file
//

#include "stdafx.h"
#include "WClust.h"
#include "DlgFLClust.h"
#include ".\dlgflclust.h"
#include "flame\flame.h"


// CDlgFLClust dialog

IMPLEMENT_DYNAMIC(CDlgFLClust, CDialog)
CDlgFLClust::CDlgFLClust(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFLClust::IDD, pParent),
	  m_iIter(2000),
	  m_iDistT(DST_SQ_EUCLID),
	  m_fEps(0.00000001f),
	  m_fKNNPrct(1.0f),
	  m_fOutTH(3.0f)
{	
}

CDlgFLClust::~CDlgFLClust()
{
}

BOOL CDlgFLClust::OnInitDialog()
{
	CDialog::OnInitDialog();
	int i;
	m_cmbDistT.AddString("SQ Euclidean");
	m_cmbDistT.AddString("Euclidean");
	m_cmbDistT.AddString("Cosine");
	m_cmbDistT.AddString("Pearson");
	m_cmbDistT.AddString("UC Pearson");
	m_cmbDistT.AddString("SQ Pearson");
	m_cmbDistT.AddString("Dot Product");
	m_cmbDistT.AddString("Covariance");
	m_cmbDistT.AddString("Manhattan");
	m_cmbDistT.SetCurSel(m_iDistT-1);
	CString strTmp;
	strTmp.Format("%d",m_iIter);
	m_wndIterFL.SetWindowText(strTmp);
	strTmp.Format("%.10f",m_fEps);
	m_wndEpsFL.SetWindowText(strTmp);
	strTmp.Format("%.2f",m_fKNNPrct);
	m_wndKNNPrctFL.SetWindowText(strTmp);
	strTmp.Format("%.2f",m_fOutTH);
	m_wndOutTH.SetWindowText(strTmp);
	Invalidate();
	return TRUE;
}

void CDlgFLClust::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ITER_FL, m_wndIterFL);
	DDX_Control(pDX, IDC_EDIT_EPS_FL, m_wndEpsFL);
	DDX_Control(pDX, IDC_EDIT_KNNFL, m_wndKNNPrctFL);
	DDX_Control(pDX, IDC_COMBO_FL_DTT, m_cmbDistT);
	DDX_Control(pDX, IDC_EDIT_OUT_FL, m_wndOutTH);
}


BEGIN_MESSAGE_MAP(CDlgFLClust, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_FL_DTT, OnCbnSelchangeComboFlDtt)
END_MESSAGE_MAP()


// CDlgFLClust message handlers

void CDlgFLClust::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_iDistT = m_cmbDistT.GetCurSel() + 1;
	CString strTmp;
	m_wndIterFL.GetWindowText(strTmp);
	m_iIter = atoi(strTmp);
	m_wndEpsFL.GetWindowText(strTmp);
	m_fEps = atof(strTmp);
	m_wndKNNPrctFL.GetWindowText(strTmp);	
	m_fKNNPrct = atof(strTmp);
	m_wndOutTH.GetWindowText(strTmp);
	m_fOutTH = atof(strTmp);
	OnOK();
}

void CDlgFLClust::OnCbnSelchangeComboFlDtt()
{
	// TODO: Add your control notification handler code here
	m_iDistT = m_cmbDistT.GetCurSel() + 1;
}
