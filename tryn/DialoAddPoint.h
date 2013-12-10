#pragma once
#include "afxwin.h"


// CDialoAddPoint 对话框

class CDialoAddPoint : public CDialogEx
{
	DECLARE_DYNAMIC(CDialoAddPoint)

public:
	CDialoAddPoint(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialoAddPoint();

// 对话框数据
	enum { IDD = IDD_CCRETE_PNT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_pnt_x;
	afx_msg void OnBnClickedAddPnt();
};
