// $Id: DlgEEGGain.cpp,v 1.2 2008/03/27 22:19:54 samn Exp $ 
// DlgEEGGain.cpp : implementation file
//

#include "stdafx.h"
#include "WClust.h"
#include "DlgEEGGain.h"
#include ".\dlgeeggain.h"


// DlgEEGGain dialog

IMPLEMENT_DYNAMIC(DlgEEGGain, CDialog)
DlgEEGGain::DlgEEGGain(CWnd* pParent,
					   vector<double>& vEEGGains,
					   vector<string>& vEEGNames,
					   CPaletteStack* pPal)
	: CDialog(DlgEEGGain::IDD, pParent)
	, m_dCurGain(1.0)
	, m_vEEGGains(vEEGGains)
	, m_vEEGNames(vEEGNames)
	, m_strCurGain(_T("1.0"))
{
	m_comboEEG.SetPalette(pPal);
}

DlgEEGGain::~DlgEEGGain()
{
}

void DlgEEGGain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_EEG_GAIN_CHAN, m_comboEEG);
	DDX_Control(pDX, IDC_SPINEEGGAIN, m_spinEEGGain);
	DDX_Control(pDX, IDC_EDITEEGGAIN, m_editEEGGain);
}


BEGIN_MESSAGE_MAP(DlgEEGGain, CDialog)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINEEGGAIN, OnDeltaposSpineeggain)
	ON_CBN_SELCHANGE(IDC_COMBO_EEG_GAIN_CHAN, OnCbnSelchangeComboEegGainChan)
	ON_EN_KILLFOCUS(IDC_EDITEEGGAIN, OnEnKillfocusEditeeggain)
END_MESSAGE_MAP()

BOOL DlgEEGGain::OnInitDialog()
{
	CDialog::OnInitDialog();
	if(!m_vEEGNames.size() || !m_vEEGGains.size())
		return TRUE;
	int i;
	for(i=0;i<m_vEEGNames.size();i++)
		m_comboEEG.AddString(m_vEEGNames[i].c_str());
	m_comboEEG.SetCurSel(0);
	m_dCurGain = m_vEEGGains[0];
	m_strCurGain.Format("%.2f",m_dCurGain);
	m_editEEGGain.SetWindowText(m_strCurGain);
	Invalidate();
	return TRUE;
}

void DlgEEGGain::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow,nStatus);
}

// DlgEEGGain message handlers

void DlgEEGGain::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void DlgEEGGain::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void DlgEEGGain::OnDeltaposSpineeggain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if(pNMUpDown->iDelta > 0)
		if(m_spinEEGGain.GetPos()-pNMUpDown->iDelta / 2.0>0.0)
		{
			pNMUpDown->iDelta *= -1; 
			m_dCurGain += pNMUpDown->iDelta / 2.0;
		}
		else 
			pNMUpDown->iDelta=0;
	else if(pNMUpDown->iDelta < 0)
		if(m_spinEEGGain.GetPos()+pNMUpDown->iDelta / 2.0>0.0)
		{
			pNMUpDown->iDelta *= -1;
			m_dCurGain += pNMUpDown->iDelta / 2.0;
		}
		else
			pNMUpDown->iDelta = 0;
	
	if(m_dCurGain <= 0.0) m_dCurGain = 0.5;
	int iCurSel = m_comboEEG.GetCurSel();
	if(iCurSel >= 0 && iCurSel < m_vEEGGains.size())
	{
		m_vEEGGains[iCurSel] = m_dCurGain;
		m_strCurGain.Format("%.2f",m_dCurGain);
		m_editEEGGain.SetWindowText(m_strCurGain);
	}
}

void DlgEEGGain::OnCbnSelchangeComboEegGainChan()
{
	// TODO: Add your control notification handler code here
	int iCurSel = m_comboEEG.GetCurSel();
	if(m_dCurGain <= 0.0) m_dCurGain = 0.5;
	if(iCurSel >= 0 && iCurSel < m_vEEGGains.size())
	{
		m_dCurGain = m_vEEGGains[iCurSel];
		m_strCurGain.Format("%.2f",m_dCurGain);
		m_editEEGGain.SetWindowText(m_strCurGain);
	}
}

void DlgEEGGain::OnEnKillfocusEditeeggain()
{
	// TODO: Add your control notification handler code here
	int iCurSel = m_comboEEG.GetCurSel();
	if(m_dCurGain <= 0.0) m_dCurGain = 0.5;
	if(iCurSel >= 0 && iCurSel < m_vEEGGains.size())
	{
		m_editEEGGain.GetWindowText(m_strCurGain);
		m_dCurGain = atof(m_strCurGain);
		if(m_dCurGain<=0.0) m_dCurGain = 0.5;
		m_vEEGGains[iCurSel] = m_dCurGain;
	}
	m_strCurGain.Format("%.2f",m_dCurGain);
	m_editEEGGain.SetWindowText(m_strCurGain);
}
