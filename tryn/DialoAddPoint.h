#pragma once
#include "afxwin.h"


// CDialoAddPoint �Ի���

class CDialoAddPoint : public CDialogEx
{
	DECLARE_DYNAMIC(CDialoAddPoint)

public:
	CDialoAddPoint(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialoAddPoint();

// �Ի�������
	enum { IDD = IDD_CCRETE_PNT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_pnt_x;
	afx_msg void OnBnClickedAddPnt();
};
