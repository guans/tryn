#pragma once


// CreatDlg �Ի���

class CreatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CreatDlg)

public:
	CreatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CreatDlg();

// �Ի�������
	enum { IDD = IDD_CREATDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_new_pnt;
	BOOL m_new_lin;
	BOOL m_new_reg;
	afx_msg void OnBnClickedNewPnt();
};
