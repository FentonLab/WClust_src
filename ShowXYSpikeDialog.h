#pragma once
#include "afxwin.h"


// ShowXYSpikeDialog dialog

class ShowXYSpikeDialog : public CDialog
{
	DECLARE_DYNAMIC(ShowXYSpikeDialog)

public:
	ShowXYSpikeDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~ShowXYSpikeDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_SHOW_SPIKE_XY };

	bool GetShowXYSpikes(){ return m_bShowXYSpikes; }

	int CollapseFactor(){ return m_iCollapseFactor; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//whether to show xy location of spikes for user cluster validation
	bool m_bShowXYSpikes;

	int m_iCollapseFactor;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CButton m_BtnShow;
	int m_iRadioCollapse;
	afx_msg void OnBnClickedCheckSpikeXy();
	afx_msg void OnBnClickedRadioXy32();
	afx_msg void OnBnClickedRadioXy16();
	afx_msg void OnBnClickedRadioXy8();
	afx_msg void OnBnClickedRadioXy4();
	afx_msg void OnBnClickedRadioXy2();
};
