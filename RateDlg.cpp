// $Id: RateDlg.cpp,v 1.4 2008/03/30 02:12:22 samn Exp $ 
// RateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WClust.h"
#include "RateDlg.h"
#include ".\ratedlg.h"


// RateDlg dialog

IMPLEMENT_DYNAMIC(RateDlg, CDialog)
RateDlg::RateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RateDlg::IDD, pParent)
	, m_radio(0)
{
	m_MainDataStack = 0;
	m_MainClusters = 0;
	m_MainPalette = 0;
	m_bCancelled = false;
	m_bSkipPaint = true;
}

RateDlg::RateDlg(CWnd* pParent,CVerxStack* pVerx,
		    CPaletteStack* pPal,CCluster* pClust)
	: CDialog(RateDlg::IDD, pParent)
{
	m_MainDataStack = pVerx;
	m_MainClusters = pClust;
	m_MainPalette = pPal;
	m_vRatings = vector<double>(m_MainClusters->GetCount());

	m_Combo.SetPalette(m_MainPalette);

	CheckRatings();

	m_bSkipPaint = true;
}

RateDlg::~RateDlg()
{
}

void RateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_RATE, m_Combo);
	DDX_Control(pDX, IDC_CHECK_POOR, m_CheckPoor);
	DDX_Control(pDX, IDC_CHECK_FAIR, m_CheckFair);
	DDX_Control(pDX, IDC_CHECK_GOOD, m_CheckGood);
}

void RateDlg::CheckRatings()
{
	int iNumClusts = m_MainClusters->GetCount();
	
	if(!m_vRatings.size())
	{
		m_vRatings = vector<double>(iNumClusts);
		return;
	}
	
	if(iNumClusts > m_vRatings.size())
	{
		std::vector<double> vTmp(m_vRatings);
		m_vRatings.resize(iNumClusts);
		int i;
		for(i=0;i<vTmp.size();i++) m_vRatings[i] = vTmp[i];
	}
	else m_vRatings.resize(iNumClusts);
}

void RateDlg::InitCombo()
{
	int iSz = m_MainClusters->GetCount() , i = 0;

	char str[1024];

	m_Combo.AddString("noise");
	m_Combo.AddString("non clustered");

	for(i = 1; i < iSz; i++)
	{
		sprintf(str,"cluster %d",i);
		m_Combo.AddString(str);
	}

	if(iSz>1)
		m_Combo.SetCurSel(2);
	else
		m_Combo.SetCurSel(1);
}

BOOL RateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_HCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);

	InitCombo();

	CheckRatings();

	GetClientRect(m_wndRect);

	m_bSkipPaint = true;

	OnCbnSelchangeComboRate();

	return TRUE;
}

void RateDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow,nStatus);
}


BEGIN_MESSAGE_MAP(RateDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_GOOD, OnBnClickedCheckGood)
	ON_BN_CLICKED(IDC_CHECK_FAIR, OnBnClickedCheckFair)
	ON_BN_CLICKED(IDC_CHECK_POOR, OnBnClickedCheckPoor)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_RATE, OnCbnSelchangeComboRate)
END_MESSAGE_MAP()


// RateDlg message handlers

void RateDlg::OnBnClickedCheckGood()
{
	// TODO: Add your control notification handler code here
	int iSel = m_Combo.GetCurSel() - 1;
	if(iSel > 0 && iSel < m_vRatings.size())
	{
		int iVal = m_CheckGood.GetCheck();
		if(iVal == BST_CHECKED)
		{
			m_CheckFair.SetCheck(BST_UNCHECKED);
			m_CheckPoor.SetCheck(BST_UNCHECKED);
			m_vRatings[iSel] = RATE_GOOD;
		}
		else
		{
			m_vRatings[iSel] = RATE_UNKNOWN;
			if(iVal == BST_INDETERMINATE)
				m_CheckGood.SetCheck(BST_UNCHECKED);
		}
	}
	else m_CheckGood.SetCheck(BST_INDETERMINATE);
}

void RateDlg::OnBnClickedCheckFair()
{
	// TODO: Add your control notification handler code here
	int iSel = m_Combo.GetCurSel() - 1;
	
	if(iSel > 0 && iSel < m_vRatings.size())
	{
		int iVal = m_CheckFair.GetCheck();
		if(iVal == BST_CHECKED)
		{
			m_CheckGood.SetCheck(BST_UNCHECKED);
			m_CheckPoor.SetCheck(BST_UNCHECKED);
			m_vRatings[iSel] = RATE_FAIR;
		}
		else
		{
			m_vRatings[iSel] = RATE_UNKNOWN;
			if(iVal == BST_INDETERMINATE)
				m_CheckFair.SetCheck(BST_UNCHECKED);
		}
	}
	else m_CheckFair.SetCheck(BST_INDETERMINATE);
}

void RateDlg::OnBnClickedCheckPoor()
{
	// TODO: Add your control notification handler code here
	int iSel = m_Combo.GetCurSel() - 1;
	if(iSel > 0 && iSel < m_vRatings.size())
	{
		int iVal = m_CheckPoor.GetCheck();
		if(iVal == BST_CHECKED)
		{
			m_CheckGood.SetCheck(BST_UNCHECKED);
			m_CheckFair.SetCheck(BST_UNCHECKED);
			m_vRatings[iSel] = RATE_POOR;
		}
		else
		{
			m_vRatings[iSel] = RATE_UNKNOWN;
			if(iVal == BST_INDETERMINATE)
				m_CheckPoor.SetCheck(BST_UNCHECKED);
		}
	}
	else m_CheckPoor.SetCheck(BST_INDETERMINATE);
}

bool RateDlg::FinishedRating()
{
	CheckRatings();

	int iSz = m_vRatings.size();
	int i = 1;
	for(i=1;i<iSz;i++)
		if(m_vRatings[i] == RATE_UNKNOWN)
			return false;
	return true;
}

void RateDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_bCancelled = false;
	OnOK();
}

void RateDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	m_bCancelled = true;
	OnCancel();
}

void RateDlg::OnCbnSelchangeComboRate()
{
	// TODO: Add your control notification handler code here
	int iSel = m_Combo.GetCurSel() - 1;
	if(iSel < 1)
	{
		m_CheckGood.SetCheck(BST_INDETERMINATE);
		m_CheckFair.SetCheck(BST_INDETERMINATE);
		m_CheckPoor.SetCheck(BST_INDETERMINATE);
	}
	else if(iSel < m_vRatings.size())
	{	m_CheckPoor.SetCheck(BST_UNCHECKED);
		m_CheckFair.SetCheck(BST_UNCHECKED);
		m_CheckGood.SetCheck(BST_UNCHECKED);
		if(m_vRatings[iSel] == RATE_POOR)
			m_CheckPoor.SetCheck(BST_CHECKED);
		else if(m_vRatings[iSel] == RATE_FAIR)
			m_CheckFair.SetCheck(BST_CHECKED);
		else if(m_vRatings[iSel] == RATE_GOOD)
			m_CheckGood.SetCheck(BST_CHECKED);
	}
	
	if(!m_bSkipPaint)
	{
		InvalidateRect(m_DrawingSpikesRect,FALSE);
		OnPaint();
	}
	else
	{
		m_bSkipPaint = false;
	}
}

void RateDlg::OnPaint()
{
	return; // no more painting waveforms since it wastes time!!

	CPaintDC dc(this); // device context for painting

	GetClientRect(m_wndRect);
	m_DrawingRect=m_wndRect;
	m_DrawingRect.left+=10;
	m_DrawingRect.top+=10;
	//m_DrawingRect.right-=190;
	m_DrawingRect.bottom-=10;
	
	m_rect=m_DrawingRect;
	m_rect.top+=10;
	m_rect.left+=20;
	m_rect.right-=10;
	m_rect.bottom-=20;

	// Drawing frame
	dc.Rectangle(m_DrawingRect);
	
	int HeightSpike = 275;

	//Drawing spikes window
	m_DrawingSpikesRect.left = 11; 
	m_DrawingSpikesRect.right = m_wndRect.right - 11; 
	m_DrawingSpikesRect.top = m_wndRect.top + 10;
	m_DrawingSpikesRect.bottom = m_wndRect.bottom - 125; 
	dc.Rectangle(m_DrawingSpikesRect);

	int iClustNum = m_Combo.GetCurSel() - 1;

	if(iClustNum < 0) return;

	CRect MiniWin;

	MiniWin.top = m_DrawingSpikesRect.top;
	MiniWin.bottom = m_DrawingSpikesRect.top +	HeightSpike;

	for (int j=0; j<4; j++)
	{
		MiniWin.left = m_DrawingSpikesRect.left + j * (m_DrawingSpikesRect.Width())/4+1;
		MiniWin.right = m_DrawingSpikesRect.left + (j+1) * (m_DrawingSpikesRect.Width())/4-1;
		m_MainDataStack->DrawSpikes( &dc , MiniWin , j , iClustNum );
	}

}

CString GetRatingString(vector<double>& vRatings)
{
	CString str("");
	str += "%%BEGIN CLUSTER_RATING\n";
	str += "// %%ClustRating.0 ( ClusterId Rating)\n";

	CString strTmp;

	char sUser[1024]={0};
	DWORD dLen = 1024;
	if(GetUserName(sUser,&dLen))
	{
		strTmp.Format("// UserName = %s\n",sUser);
		str += strTmp;
	}

	int i = 1;
	for(i=1;i<vRatings.size();i++)
	{
		strTmp.Format("%%ClustRating.0 ( %d %.2f )\n",i,vRatings[i]);
		str += strTmp;
	}

	str += "%%END CLUSTER_RATING\n\n";	
	
	return str;
}

void RateDlg::GetRatingString(CString& str)
{
	str = ::GetRatingString(m_vRatings);	
}
