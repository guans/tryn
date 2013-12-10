// DialoAddPoint.cpp : 实现文件
//

#include "stdafx.h"
#include "tryn.h"
#include "DialoAddPoint.h"
#include "afxdialogex.h"


// CDialoAddPoint 对话框

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


// CDialoAddPoint 消息处理程序


void CDialoAddPoint::OnBnClickedAddPnt()
{
	// TODO: 在此添加控件通知处理程序代码
}
