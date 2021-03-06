// $Id: SelectTT.h,v 1.2 2008/02/12 02:31:02 samn Exp $ 
#if !defined(AFX_SELECTTT_H__E4541C2A_396E_4617_9EA0_657AEDEE7776__INCLUDED_)
#define AFX_SELECTTT_H__E4541C2A_396E_4617_9EA0_657AEDEE7776__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectTT.h : header file
//
#include "MyObj.h"
#include "afxwin.h"
#include "ColorComboBox.h"
/////////////////////////////////////////////////////////////////////////////
// CSelectTT dialog

class CSelectTT : public CDialog
{
public:
	char		EldeCh;
	char		EldeType;
	int			EldeMaxAmount;	// amount of spikes in channel
	char		UnitOfAmount;	// 0 - spikes, 1 - % 
	char		FileType;
	char		dFileOK;		// for showing Warning Message
	char		dLastType;		// for showing Warning Message
	long		dLastPos;		// for showing Warning Message

	int			*ChannelNo;
	int			NoLines;
	char		max_elde;
	MY_INT_VECT	EldeNoStack;
	MY_INT_VECT	ChannelNoStack;
	MY_INT_VECT	AmountStack;
	bool		m_bUseEEG;

	int			GetAmount();

// Construction
public:
	CSelectTT(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectTT)
	enum { IDD = IDD_SELECT_TETRODE };
	CListBox	m_wndListMessage;
	CEdit	m_wndEdAmount;
	CButton	m_wndPB6;
	CButton	m_wndPB5;
	CButton	m_wndPB4;
	CButton	m_wndPB3;
	CButton	m_wndPB2;
	CButton	m_wndPB1;
	CListBox	m_wndList;
	int		m_edAmount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectTT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectTT)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeListOfElectrodes();
	afx_msg void OnDblclkListOfElectrodes();
	virtual void OnCancel();
	afx_msg void OnPerbut1();
	afx_msg void OnPerbut2();
	afx_msg void OnPerbut3();
	afx_msg void OnPerbut4();
	afx_msg void OnPerbut5();
	afx_msg void OnPerbut6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CButton m_BtnDoPCA;
	CButton m_BtnCatPCA;
	/*CComboBox*/CColorComboBox m_ComboNumPCs;
	afx_msg void OnBnClickedCheckPca();

	int NumPCs(){ return m_iNumPCs; }
	bool DoPCA(){ return m_bUsePCA; }
	bool CatPCA(){ return m_bCatPCA; }
	afx_msg void OnCbnSelchangeComboNumPcs();
	afx_msg void OnBnClickedCheckPcaConcat();

protected:
	bool m_bUsePCA;
	bool m_bCatPCA;
	int m_iNumPCs;
public:
	afx_msg void OnCbnDropdownComboNumPcs();
	afx_msg void OnCbnEditchangeComboNumPcs();
	afx_msg void OnCbnEditupdateComboNumPcs();
	CString m_strNumPCs;
	afx_msg void OnEnUpdateEditNumPcs();
	CButton m_btnLoadEEG;
	afx_msg void OnBnClickedCheckLdEeg();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTTT_H__E4541C2A_396E_4617_9EA0_657AEDEE7776__INCLUDED_)
