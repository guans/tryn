// DialoAddPoint.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "tryn.h"
#include "DialoAddPoint.h"
#include "afxdialogex.h"


// CDialoAddPoint �Ի���

IMPLEMENT_DYNAMIC(CDialoAddPoint, CDialogEx)

CDialoAddPoint::CDialoAddPoint(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialoAddPoint::IDD, pParent)
{

}

CDialoAddPoint::~CDialoAddPoint()
{
}

void CDialoAddPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_pnt_x);
}


BEGIN_MESSAGE_MAP(CDialoAddPoint, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_PNT, &CDialoAddPoint::OnBnClickedAddPnt)
END_MESSAGE_MAP()


// CDialoAddPoint ��Ϣ�������


void CDialoAddPoint::OnBnClickedAddPnt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
