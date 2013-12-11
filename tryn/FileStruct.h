#pragma once
#include "stdafx.h"
#include <afx.h>
#include "CreatDlg.h"
//#include<vector>
/////////���к궨��
//�����
#define NEW_PNT 0x0001;
#define NEW_LIN 0x0002;
#define NEW_REG 0x0004;
//�����
#define OPERSTATE_INPUT_PNT		1      //���
#define OPERSTATE_DEL_PNT		2	   //ɾ����
#define OPERSTATE_MOV_PNT	    3      //�ƶ���
#define OPERSTATE_SHOW_DEL_PNT	4	   //��ʾɾ����
#define OPERSTATE_RECOVER_PNT   5      //�ָ�ɾ����
#define OPERSTATE_EDIT_PNT      6      //�༭�����
#define OPERSTATE_SET_PNT       7      //���õ�ȱʡ����
//��ͼ����ϵ����
#define OPERSTATE_ZOOM_IN		8      //�Ŵ�
#define OPERSTATE_ZOOM_OUT		9      //��С
//�߲���
#define OPERSTATE_INPUT_IIN			10       //����
#define OPERSTATE_MOVE_IIN			11      //�ƶ���
#define OPERSTATE_DEL_IIN			12      //ɾ����
#define OPERSTATE_SHOW_IIN			13      //��ʾɾ����
#define OPERSTATE_RECOVER_IIN		14      //�ָ���
#define OPERSTATE_ADD_PNT			15      //���ϼӵ�
#define OPERSTATE_DEL_PNT			16      //����ɾ��
#define OPERSTATE_CONNECT_IIN		17      //������
#define OPERSTATE_EDIT_IIN			18      //�޸�������
#define OPERSTATE_SET_IIN			19      //������ȱʡ����

//���ڲ���
#define OPERSTATE_ZOOM_IN		20      //�Ŵ�
#define OPERSTATE_ZOOM_OUT		21      //��С
#define OPERSTATE_CREAT_REG		22      //����
#define OPERSTATE_DELETE_REG    23	   //ɾ����
#define OPERSTATE_MOVE_REG      24	   //�ƶ���
#define OPERSTATE_WINDOW_MOVE   25	   //�����ƶ�
#define OPERSTATE_WINDOW_RESET  26	   //��������


extern int GCurOperState;
extern int GCurPNTState;							 //ȫ�ֵ����
extern int GCurLINState;							 //ȫ���߲���
//1.���ļ�{
extern CFile GPntTmpFile,GPntFile;						//����ʱ�ļ����������ļ�
extern int GPntNum,GPntLNum;							//����������߼�����
extern int GPntFCreated;								//���ļ��Ƿ񴴽�
extern int GPntChanged;									//���ļ��Ƿ�ı�
extern char GPntFName[256];								//���ļ���	
extern int GPntTmpFOpened;								//����ʱ�ļ��Ƿ񱻴�
//}
//2.���ļ�{
extern CFile GLinTmpFile1,GLinTmpFile2,GLinFile;		//����ʱ�ļ����������ļ�
extern int GLinNum,GLinLNum;							//�����������߼�����
extern int GLinFCreated;								//���ļ��Ƿ񴴽�
extern int GLinChanged;									//���ļ��Ƿ�ı�
extern char GLinFName[256];								//���ļ���	
extern int GLinTmpFOpened;								//����ʱ�ļ��Ƿ񱻴�
//}
//3.���ļ�{
extern CFile GRegTmpFile1,GRegTmpFile2,GRegFile;		//����ʱ�ļ����������ļ�
extern int GRegNum,GRegLNum;							//�����������߼�����
extern int GRegFCreated;								//���ļ��Ƿ񴴽�
extern int GRegChanged;									//���ļ��Ƿ�ı�
extern char GRegFName[256];								//���ļ���	
extern int GRegTmpFOpened;								//����ʱ�ļ��Ƿ񱻴�
//}

//4.{
extern double GZoom;									//����ϵ��
extern double GxOffset;									//����xƫ����yƫ��
extern double GyOffset;								
//}

struct pnt_stru
{
	char			isDel;		//�Ƿ�ɾ����
	COLORREF		color;		//����ɫ
	int				pattern;	//��ͼ�����ţ�
	double			x;			//��λ����
	double			y;  
}PNT_STRU,TEM_PNT;

struct pnt_version
{
	char 	flag[3];	//��־����PNT��
	int		version;	//10
}PNT_VERSION;

struct lin_ndx_stru
{
	char				isDel;		//�Ƿ�ɾ����
	COLORREF			color;		//����ɫ
	int				pattern;		//���ͣ��ţ�
	long 				dotNum;		//���������
	long				datOff;		//���������ݴ洢λ��  
}LIN_NDX_STRU,TEM_LIN;

struct lin_version
{
	char	flag[3];	//��ʶ����LIN��
	int		version;	//10
}LIN_VERSION;

struct reg_ndx_stru
{
	char				isDel;		//�Ƿ�ɾ����
	COLORREF			color;		//����ɫ
	long 				dotNum;		//���������
	long				datOff;		//���������ݴ洢λ��  
}REG_NDX_STRU;

struct reg_version
{
	char	flag[3];	//��ʶ����REG��
	int		version;	//10
}REG_VERSION;

long GetNewType(int& mtype)
{
	CreatDlg mdlg;
	mdlg.DoModal();
	int type=0x0000;;
	if(mdlg.m_new_pnt==TRUE)
	{
		type=type|NEW_PNT;
	}
	if(mdlg.m_new_lin==TRUE)
	{
		type=type|NEW_LIN;
	}
	if(mdlg.m_new_reg==TRUE)
	{
		type=type|NEW_REG;
	}
	mtype=type;
	return (1);
}
long NewPnt()
{
	if(GPntFCreated==1)
	{
		AfxMessageBox(_T("���ļ��Ѵ�����"));
		return (0);
	}
	else

		GPntFCreated = 1;
	GPntTmpFile.Open (_T("E:\\���\\���ڱ���\\MapEditor\\tempfile\\GPntTmpFile.pnt"),CFile:: modeCreate|CFile:: modeReadWrite);
	GPntTmpFOpened = 1;
	return (1);
}
long NewLin()
{
	if(GLinFCreated==1)
	{
		AfxMessageBox(_T("���ļ��Ѵ�����"));
		return (0);
	}
	else

		GLinFCreated = 1;
	GLinTmpFile1.Open (_T("E:\\���\\���ڱ���\\MapEditor\\tempfile\\GLinTmpFFile1.lin"),CFile:: modeCreate|CFile:: modeReadWrite);
	GLinTmpFile2.Open (_T("E:\\���\\���ڱ���\\MapEditor\\tempfile\\GLinTmpFFile2.lin"),CFile:: modeCreate|CFile:: modeReadWrite);
	GLinTmpFOpened = 1;
	return (1);
}
long NewReg()
{
	if(GRegFCreated==1)
	{
		AfxMessageBox(_T("���ļ��Ѵ�����"));
		return (0);
	}
	else

		GRegFCreated = 1;
	GRegTmpFile1.Open (_T("E:\\���\\���ڱ���\\MapEditor\\tempfile\\GRegTmpFile1.regn"),CFile:: modeCreate|CFile::modeReadWrite);
	GRegTmpFile2.Open (_T("E:\\���\\���ڱ���\\MapEditor\\tempfile\\GRegTmpFile2.regn"),CFile:: modeCreate|CFile::modeReadWrite);
	GRegTmpFOpened = 1;
	return (1);
}
//���������ļ�ת���ɵ���ʱ�ļ��ĺ���
long Pnt_FCT(CFile &PntFile,CString FilePathName)
{
	//PntFile.Open(FilePathName,CFile::modeRead);
	int Off=sizeof(PNT_VERSION)+sizeof(GPntNum)+sizeof(GPntLNum)-1;
	pnt_stru pnt;
	if(!GPntTmpFOpened)						//�������ʱ�ļ�û�д����½�
		NewPnt();
	GPntTmpFile.Seek(0,CFile::begin);		//������ʱ�ļ�ָ�붨�嵽��ʼ
	PntFile.Seek(Off,CFile::begin);			//�������ļ�ָ�������汾���������߼���
	int GPntNum=( PntFile.GetLength()-Off)/sizeof(PNT_STRU);
	for(int i=0;i<GPntNum;i++)
	{
		PntFile.Read(&pnt,sizeof(PNT_STRU));
		GPntTmpFile.Write(&pnt,sizeof(PNT_STRU));
	}

	return (1);
}
//������ʱ�ļ�ת���������ļ��ĺ���
long Pnt_TCF(CString FilePathName,int version)
{
	char flag[3];
	pnt_stru pnt;
	int len=0;
	if(!GPntTmpFOpened)
		return (0);
	len=GPntTmpFile.GetLength();
	GPntTmpFile.Seek(0,CFile::begin);
	GPntFile.Open(FilePathName,CFile:: modeCreate|CFile:: modeWrite|CFile::modeRead);
	GPntFile.Seek(0,CFile::begin);

	flag[0] = 'P';
	flag[1] = 'N';
	flag[2] = 'T';
	GPntFile.Write(flag,3);
	GPntFile.Write (&version,sizeof(int));
	GPntFile.Write (&GPntNum,sizeof(int));
	GPntFile.Write (&GPntLNum,sizeof(int));
	for(int i=0;i<len/sizeof(PNT_STRU);i++)
	{
		GPntTmpFile.Read(&TEM_PNT,sizeof(TEM_PNT));
		PNT_STRU=TEM_PNT;
		GPntFile.Write(&PNT_STRU,sizeof(PNT_STRU));

	}
	GPntFile.Close();
	GPntChanged=0;
	return (1);

}
//���������ļ�ת������ʱ�ļ��ĺ���
long Lin_FCT(CFile &LinFile,CString FilePathName)
{
	int i;
	int ndxOff=sizeof(LIN_VERSION)+sizeof(GLinNum)+sizeof(GLinLNum);
	//sizeof(LIN_VERSION)+sizeof(GLinNum)+sizeof(GLinLNum)+3;
	int tmpDatOff;
	lin_ndx_stru linNdx;
	int linDatSize;
	char *linDatBuf;
	int linversion=0;
	int linnum=0;
	int linlnum=0;


	if(!GLinTmpFOpened)
		NewLin();

	LinFile.Read(&linversion,sizeof(int));			
	LinFile.Read(&linnum,sizeof(int));			
	LinFile.Read(&linlnum,sizeof(int));			
	GPntNum+=linnum;
	GPntLNum+=linnum;
	GLinTmpFile1.Seek(0,CFile::begin);				//������ʱ�ļ�1ָ�붨�嵽��ʼ
	tmpDatOff=0;
	GLinTmpFile2.Seek(tmpDatOff,CFile::begin);		//������ʱ�ļ�2ָ�붨�嵽tmpdatoff
	LinFile.Seek(ndxOff,CFile::begin);				//���������ļ�ָ�������汾���߼���������


	for(i=0;i< linnum ;i++)					
	{
		int lindatasize;
		LinFile.Read(&linNdx,sizeof(LIN_NDX_STRU));			//����i���ߵ�����
		ndxOff+=sizeof(LIN_NDX_STRU);
		linDatSize=linNdx.dotNum*sizeof(PNT_STRU);				//���㵱ǰ�ߵ�����������ڴ��ֽ���
		linDatBuf=new char [linDatSize];					//�����ŵ�ǰ���������������ڴ�
		lindatasize=linDatSize;
		LinFile.Seek(linNdx.datOff,CFile::begin);			//��λ����ǰ������������ʼλ��
		LinFile.Read(linDatBuf,lindatasize);					//����ǰ�ߵ���������
		GLinTmpFile2.Write(linDatBuf,lindatasize);			//�����������ݴ�����ʱ�ļ�2
		linNdx.datOff=tmpDatOff;
		tmpDatOff+=linDatSize;
		GLinTmpFile1.Write(&linNdx,sizeof(LIN_NDX_STRU)); //���������ṹ������ʱ�ļ�1
		LinFile.Seek(ndxOff,CFile::begin);					//���¶�λ�������ṹ��
		delete []linDatBuf;
	}

	return (1);
}

//������ʱ�ļ�ת���������ļ��ĺ���
long Lin_TCF(CString FilePathName,int version)
{
	
	int i;
	int linDatSize;
	char *linDatBuf;
	int dataOff=sizeof(LIN_VERSION)+sizeof(GLinNum)+sizeof(GLinLNum)+GLinNum*sizeof(LIN_NDX_STRU);
	int ndxOff=sizeof(LIN_VERSION)+sizeof(GLinNum)+sizeof(GLinLNum);
	if(!GLinTmpFOpened)
		return (0);
	GLinFile.Open(FilePathName,CFile:: modeCreate|CFile:: modeWrite|CFile::modeRead);
	GLinFile.Seek(0,CFile::begin);
	GLinTmpFile1.Seek(0,CFile::begin);
	GLinTmpFile2.Seek(0,CFile::begin);
	char flag[3];
	flag[0] = 'L';
	flag[1] = 'I';
	flag[2] = 'N';
	GLinFile.Write(flag,3);
	GLinFile.Write(&version,sizeof(int));
	GLinFile.Write(&GLinNum,sizeof(int));
	GLinFile.Write(&GLinLNum,sizeof(int));

	for(i=0 ;i < GLinNum; i++)
	{
		int lindata=0;
		lin_ndx_stru linNdx;
		lin_ndx_stru tempNdx;

		GLinTmpFile1.Read(&linNdx,sizeof(LIN_NDX_STRU));	
		tempNdx=linNdx;

		linDatSize=linNdx.dotNum*sizeof(PNT_STRU);				//���㵱ǰ�ߵ�����������ڴ��ֽ���
		linDatBuf=new char [linDatSize];					//�����ŵ�ǰ���������������ڴ�
		GLinTmpFile2.Seek(linNdx.datOff,CFile::begin);		//��λ����������������
		lindata=linDatSize;
		GLinTmpFile2.Read(&linDatBuf,lindata);
		GLinFile.Seek(dataOff,CFile::begin);
		//lindata=linDatSize;
		GLinFile.Write(&linDatBuf,lindata);
		tempNdx.datOff=dataOff;
		GLinFile.Seek(ndxOff,CFile::begin);
		GLinFile.Write(&tempNdx,sizeof(LIN_NDX_STRU));
		ndxOff+=sizeof(LIN_NDX_STRU);

		dataOff+=lindata;
		delete []linDatBuf;


	}
	
	GLinFile.Close();
	GLinChanged=0;	
	return (1);

}
//���������ļ�ת��Ϊ��ʱ�ļ��ĺ���
long Reg_FCT(CFile &RegFile,CString FilePathName)
{
	int i;
	int ndxOff=sizeof(REG_VERSION)+sizeof(GRegNum)+sizeof(GRegLNum);
	int tmpDatOff;
	reg_ndx_stru regNdx;
	int regDatSize;
	char *regDatBuf;
	if(!GRegTmpFOpened)
		NewReg();
	GRegTmpFile1.Seek(0,CFile::begin);		//������ʱ�ļ�1ָ�붨�嵽��ʼ
	tmpDatOff=0;
	GRegTmpFile2.Seek(tmpDatOff,CFile::begin);		//������ʱ�ļ�2ָ�붨�嵽tepdatoff
	RegFile.Seek(ndxOff,CFile::begin);		//���������ļ�ָ�������汾���߼���������
	for(i=0;i<GRegNum;i++)					
	{
		RegFile.Read(&regNdx,sizeof(LIN_NDX_STRU));			//����i����������
		ndxOff+=sizeof(LIN_NDX_STRU);
		regDatSize=regNdx.dotNum*sizeof(POINT);				//���㵱ǰ��������������ڴ��ֽ���
		regDatBuf=new char [regDatSize];					//�����ŵ�ǰ���������������ڴ�
		RegFile.Seek(regNdx.datOff,CFile::begin);			//��λ����ǰ������������ʼλ��
		RegFile.Read(regDatBuf,regDatSize);					//����ǰ������������
		GLinTmpFile2.Write(regDatBuf,regDatSize);			//�����������ݴ�����ʱ�ļ�2
		regNdx.datOff=tmpDatOff;
		tmpDatOff += regDatSize;	
		GLinTmpFile1.Write(&regNdx,sizeof(LIN_NDX_STRU)); //���������ṹ������ʱ�ļ�1
		RegFile.Seek(ndxOff,CFile::begin);					//���¶�λ�������ṹ��

	}

	return (1);
}
//������ʱ�ļ�ת�����������ļ��ĺ���
long Reg_TCF(CString FilePathName,int version)
{
	int i;
	reg_ndx_stru regNdx;
	int regDatSize;
	char *regDatBuf;
	int dataOff=sizeof(REG_VERSION)+sizeof(GRegNum)+sizeof(GRegLNum)+GRegNum*sizeof(REG_NDX_STRU);
	int ndxOff=sizeof(REG_VERSION)+sizeof(GRegNum)+sizeof(GRegLNum);
	if(!GRegTmpFOpened)
		return (0);
	GRegFile.Open(FilePathName,CFile:: modeCreate|CFile:: modeWrite|CFile::modeRead);
	GRegFile.Seek(0,CFile::begin);
	GRegTmpFile1.Seek(0,CFile::begin);
	GRegTmpFile2.Seek(0,CFile::begin);
	char flag[3];
	flag[0] = 'R';
	flag[1] = 'E';
	flag[2] = 'G';
	GRegFile.Write(flag,3);
	GRegFile.Write(&version,sizeof(int));
	GRegFile.Write(&GRegNum,sizeof(int));
	GRegFile.Write(&GRegLNum,sizeof(int));
	for(i=0;i<GRegNum;i++)
	{
		GRegTmpFile1.Read(&regNdx,sizeof(REG_NDX_STRU));	
		regDatSize=regNdx.dotNum*sizeof(POINT);				//���㵱ǰ�ߵ�����������ڴ��ֽ���
		regDatBuf=new char [regDatSize];					//�����ŵ�ǰ���������������ڴ�
		GRegTmpFile2.Seek(regNdx.datOff,CFile::begin);		//��λ����������������
		GRegTmpFile2.Read(&regDatBuf,regDatSize);
		GRegFile.Seek(dataOff,CFile::begin);
		GRegFile.Write(&regDatBuf,regDatSize);
		dataOff+=regDatSize;
		regNdx.datOff=dataOff;
		GRegFile.Seek(ndxOff,CFile::begin);
		GRegFile.Write(&regNdx,sizeof(REG_NDX_STRU));
		ndxOff+=sizeof(REG_NDX_STRU);
	}

	GRegFile.Close();
	GRegChanged=0;	
	return (1);

}




long GetOpenPath(CString &pathname)
{
	CFileDialog mFileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,_T("�������ļ� |*.pnt;*.lin;*.regn||"),AfxGetMainWnd());
	if(mFileDlg.DoModal()!=IDOK)
	{
		goto GET_OPEN_PATH_END;
	}
	pathname =mFileDlg.GetPathName();
	return 1;

GET_OPEN_PATH_END: 
	return	0;

}

long GetPntSavePath(CString &pathname)
{
	CFileDialog mFileDlg(FALSE,_T("pnt"),_T("δ����"),NULL,_T("�������ļ� |*.pnt;*.lin;*.regn||"),AfxGetMainWnd());
	mFileDlg.m_ofn.lpstrTitle = _T("����");	//���öԻ������
	if(mFileDlg.DoModal()!=IDOK)
	{
		goto GET_SAVE_PATH_END;	
	}
	//	mFileDlg.UpdateData(TRUE);
	pathname=mFileDlg.GetPathName();	
	return 1; 

GET_SAVE_PATH_END:
	return 0;
}
long GetLinSavePath(CString &pathname)
{
	CFileDialog mFileDlg(FALSE,_T("lin"),_T("δ����"),NULL,_T("�������ļ� |*.pnt;*.lin;*.regn||"),AfxGetMainWnd());
	mFileDlg.m_ofn.lpstrTitle = _T("����");	//���öԻ������
	if(mFileDlg.DoModal()!=IDOK)
	{
		goto GET_SAVE_PATH_END;	
	}
	//	mFileDlg.UpdateData(TRUE);
	pathname=mFileDlg.GetPathName();
	return 1; 	

GET_SAVE_PATH_END:
	return	0;
}
long GetRegSavePath(CString &pathname)
{
	CFileDialog mFileDlg(FALSE,_T("regn"),_T("δ����"),NULL,_T("�������ļ� |*.pnt;*.lin;*.regn||"),AfxGetMainWnd());
	mFileDlg.m_ofn.lpstrTitle = _T("����");	//���öԻ������
	if(mFileDlg.DoModal()!=IDOK)
	{
		goto GET_SAVE_PATH_END;	
	}
	//	mFileDlg.UpdateData(TRUE);
	pathname=mFileDlg.GetPathName();
	return 1;	

GET_SAVE_PATH_END:
	return	0;
}
long GetPntSaveAsPath(CString &pathname)
{
	CFileDialog mFileDlg(FALSE,_T("pnt"),(LPCTSTR)GPntFName,NULL,_T("�������ļ� |*.pnt;*.lin;*.regn||"),AfxGetMainWnd());
	mFileDlg.m_ofn.lpstrTitle = _T("���Ϊ");	//���öԻ������
	if(mFileDlg.DoModal()!=IDOK)
	{
		goto GET_SAVEAS_PATH_END;	
	}
	//mFileDlg.UpdateData(TRUE);
	pathname=mFileDlg.GetPathName();
	return 1;	

GET_SAVEAS_PATH_END:
	return 0;
}
long GetLinSaveAsPath(CString &pathname)
{
	CFileDialog mFileDlg(FALSE,_T("lin"),(LPCTSTR)GRegFName,NULL,_T("�������ļ� |*.pnt;*.lin;*.regn||"),AfxGetMainWnd());
	mFileDlg.m_ofn.lpstrTitle = _T("����");	//���öԻ������
	if(mFileDlg.DoModal()!=IDOK)
	{
		goto GET_SAVEAS_PATH_END;	
	}
	mFileDlg.UpdateData(TRUE);
	pathname=mFileDlg.GetPathName();
	return 1;	

GET_SAVEAS_PATH_END:
	return 0;
}
long GetRegSaveAsPath(CString &pathname)
{
	CFileDialog mFileDlg(FALSE,_T("regn"),(LPCTSTR)GRegFName,NULL,_T("�������ļ� |*.pnt;*.lin;*.regn||"),AfxGetMainWnd());
	mFileDlg.m_ofn.lpstrTitle = _T("����");	//���öԻ������
	if(mFileDlg.DoModal()!=IDOK)
	{
		goto GET_SAVEAS_PATH_END;	
	}
	mFileDlg.UpdateData(TRUE);
	pathname=mFileDlg.GetPathName();
	return 1; 	

GET_SAVEAS_PATH_END:
	return 0;
}
long GetPntExitPath(CString &pathname)
{
	int a=AfxMessageBox(_T("���Ѿ��½����޸����ĵ�,���ȱ���!"),MB_YESNOCANCEL|MB_ICONQUESTION);
	if(a==IDCANCEL)
		return 0;
	else if(a==IDNO)
	{
		return 2;
	}
	else
	{
		CFileDialog mFileDlg(FALSE,_T("pnt"),_T("δ����"),NULL,_T("�������ļ� |*.pnt;*.lin;*.regn||"),AfxGetMainWnd());
		mFileDlg.m_ofn.lpstrTitle = _T("����");	//���öԻ������
		if(mFileDlg.DoModal()!=IDOK)
		{
			goto GET_SAVE_PATH_END;	
		}
		mFileDlg.UpdateData(TRUE);
		pathname=mFileDlg.GetPathName();	
		return 1; 
	}
GET_SAVE_PATH_END:
	return 0;
}
long GetLinExitPath(CString &pathname)
{
	int a=AfxMessageBox(_T("���Ѿ��½����޸����ĵ�,���ȱ���!"),MB_YESNOCANCEL|MB_ICONQUESTION);
	if(a==IDCANCEL)
		return 0;
	else if(a==IDNO)
	{
		return 2;
	}
	else
	{
		CFileDialog mFileDlg(FALSE,_T("lin"),_T("δ����"),NULL,_T("�������ļ� |*.pnt;*.lin;*.regn||"),AfxGetMainWnd());
		mFileDlg.m_ofn.lpstrTitle = _T("����");	//���öԻ������
		if(mFileDlg.DoModal()!=IDOK)
		{
			goto GET_SAVE_PATH_END;	
		}
		mFileDlg.UpdateData(TRUE);
		pathname=mFileDlg.GetPathName();	
		return 1; 
	}
GET_SAVE_PATH_END:
	return 0;
}
long GetRegExitPath(CString &pathname)
{
	int a=AfxMessageBox(_T("���Ѿ��½����޸����ĵ�,���ȱ���!"),MB_YESNOCANCEL|MB_ICONQUESTION);
	if(a==IDCANCEL)
		return 0;
	else if(a==IDNO)
	{
		return 2;
	}
	else
	{
		CFileDialog mFileDlg(FALSE,_T("regn"),_T("δ����"),NULL,_T("�������ļ� |*.pnt;*.lin;*.regn||"),AfxGetMainWnd());
		mFileDlg.m_ofn.lpstrTitle = _T("����");	//���öԻ������
		if(mFileDlg.DoModal()!=IDOK)
		{
			goto GET_SAVE_PATH_END;	
		}
		mFileDlg.UpdateData(TRUE);
		pathname=mFileDlg.GetPathName();	
		return 1; 
	}
GET_SAVE_PATH_END:
	return 0;
}



long AppendAReg(COLORREF regColor,int RegPntNum,int RegDatOff,POINT *ptRegPnt)
{
	//1.������������ʱ�ļ�2��д������
	GRegTmpFile2.Seek(0,CFile::end);
	GRegTmpFile2.Write(ptRegPnt,RegPntNum*sizeof(POINT));
	//2.��������ʱ�ļ�1��д������
	REG_NDX_STRU.color=regColor;
	REG_NDX_STRU.datOff=RegDatOff;
	REG_NDX_STRU.dotNum=RegPntNum;
	GRegTmpFile1.Seek(0,CFile::end);
	GRegTmpFile1.Write(&REG_NDX_STRU,sizeof(REG_NDX_STRU));
	return (1);
}
//�������ܣ��õ���ri��������������������
//��������ri���������������������ã�����������������������߽������ָ�룬������������ݣ�ָ�볤�ȣ���������Ӧ
long GetAReg(int ri,reg_ndx_stru &regNdx,POINT *ptRegDatBuf, long bufLen)
{
	if(ri<=0)
		return (0);
	if(GRegTmpFOpened==0)
		return (0);
	if(GRegTmpFile1.GetLength()==0)
		return (0);
	int off=(ri-1)*sizeof(REG_NDX_STRU);
	int pntSize;
	GRegTmpFile1.Seek(off,CFile::begin);
	GRegTmpFile1.Read(&regNdx,sizeof(REG_NDX_STRU));
	if(regNdx.dotNum>bufLen)
		return (0);
	pntSize=regNdx.dotNum*sizeof(POINT);
	GRegTmpFile2.Seek(regNdx.datOff,CFile::begin);
	GRegTmpFile2.Read(ptRegDatBuf,pntSize);
	return (1);



}
//�������ܣ�����ʱ�ļ���ɾ����ri����
//��������ʱ�ļ��е�ri����
long DeleteAReg(int ri)
{
	if(ri<=0)
		return (0);
	reg_ndx_stru regNdx;
	int size=(ri-1)*sizeof(REG_NDX_STRU);
	GRegTmpFile1.Seek(size,CFile::begin);
	GRegTmpFile1.Read(&regNdx,sizeof(REG_NDX_STRU));
	regNdx.isDel=1;
	GRegTmpFile1.Seek(size,CFile::begin);
	GRegTmpFile1.Write(&regNdx,sizeof(REG_NDX_STRU));
	return (1);

}

//�������ܣ��ж�һ�����Ƿ���һ������,����ͨ���õ���y�����ϵ����������Ľ��������ж�
//��������ָ�룬ָ�����������ݣ����������������Ҫ�жϵĵ�
long IsInReg(POINT *regPnt,int regPntNum,POINT xy)
{
	int i;
	int sum=0;
	int ymax,xmin,xmax,ymin;
	double k,b,yy;
	for(i=0;i<regPntNum-1;i++)
	{
		if(regPnt[i].x==xy.x&&regPnt[i].y==xy.y)			//����õ��������ߵĽ���������Լ����������
			return (1);
		if(regPnt[i].y>regPnt[i+1].y)						//�����ÿһ��������x�����Сֵ��y�����Сֵ
		{
			ymax = regPnt[i].y;
			ymin = regPnt[i+1].y;
		}
		else
		{
			ymax = regPnt[i+1].y;
			ymin = regPnt[i].y;
		}
		if(regPnt[i].x>regPnt[i+1].x)
		{
			xmax = regPnt[i].x;
			xmin = regPnt[i+1].x;
		}
		else
		{
			xmax = regPnt[i+1].x;
			xmin = regPnt[i].x;
		}
		//�����������Сֵ
		if(regPnt[i+1].y==regPnt[i].y)				//�������ƽ����y����
		{
			if(xy.y==regPnt[i].y&&xy.x>=xmin&&xy.x<=xmax)		//����õ��ڸ������򽻵��1
				sum++;
		}
		else if(regPnt[i+1].x!=regPnt[i].x)
		{
			k=double((regPnt[i+1].x-regPnt[i].x))/double((regPnt[i+1].y-regPnt[i].y));	//�������ֱ��б��ʽ���̵�б��k
			b=double((regPnt[i+1].y*regPnt[i].x-regPnt[i+1].x*regPnt[i].y))/double((regPnt[i+1].y-regPnt[i].y));	//�������ֱ��б��ʽ���̵�б��b

			yy=(xy.x-b)/k;		//������õ�x�µ�yֵ
			if(yy>=xy.y&&yy<=ymax&&yy>=ymin)	//���y�������Сyֵ�У��򽻵��1
			{
				sum++;
			}

		}
	}
	//�������һ�������һ�����γɵ�ֱ��
	if(regPnt[regPntNum-1].y>regPnt[0].y)
	{
		ymax = regPnt[regPntNum-1].y;
		ymin = regPnt[0].y;
	}
	else
	{
		ymax = regPnt[0].y;
		ymin = regPnt[regPntNum-1].y;
	}
	if(regPnt[regPntNum-1].x>regPnt[0].x)
	{
		xmax = regPnt[regPntNum-1].x;
		xmin = regPnt[0].x;
	}
	else
	{
		xmax = regPnt[0].x;
		xmin = regPnt[regPntNum-1].x;
	}
	if(regPnt[regPntNum-1].y==regPnt[0].y)
	{
		if(xy.y==regPnt[0].y&&xy.x>=xmin&&xy.x<=xmax)
			sum++;
	}
	else if(regPnt[regPntNum-1].x!=regPnt[0].x)
	{
		k=double((regPnt[regPntNum-1].x-regPnt[0].x))/double((regPnt[regPntNum-1].y-regPnt[0].y));
		b=double((regPnt[regPntNum-1].y*regPnt[0].x-regPnt[regPntNum-1].x*regPnt[0].y))/double((regPnt[regPntNum-1].y-regPnt[0].y));

		yy=(xy.x-b)/k;
		if(yy>=xy.y&&yy<=ymax&&yy>=ymin)
		{		
			sum++;
		}
	}


	if(sum%2==1)
	{
		return (1);
	}
	else
		return (0);

}
//�������ܣ�ʵ��һ�������������ϵ�봰������ϵ��ת��
//��������xy
long DotDPtoVP(POINT &xy)
{
	xy.x-=GxOffset;
	xy.y-=GyOffset;
	xy.x*=GZoom;
	xy.y*=GZoom;
	return (1);
}
//�������ܣ�ʵ��һЩ�����������ϵ�봰������ϵ��ת��
//��������ָ�룬������
long SomeDotDPtoVP(POINT *ptPntDat,int datLen)
{
	int i;
	for(i=0;i<datLen;i++)
	{
		DotDPtoVP(ptPntDat[i]);
	}
	return (1);
}
//�������ܣ�ʵ��һ����Ĵ�������ϵ����������ϵ��ת��
//��������xy
long DotVPtoDP(POINT &xy)
{
	xy.x/=GZoom;
	xy.y/=GZoom;
	xy.x+=GxOffset;
	xy.y+=GyOffset;
	return (1);
}
//�������ܣ�ʵ��һЩ��Ĵ�������ϵ����������ϵ��ת��
//��������ָ�룬������
long SomeDotVPtoDP(POINT *ptPntDat,int datLen)
{
	int i;
	for(i=0;i<datLen;i++)
	{
		DotVPtoDP(ptPntDat[i]);
	}
	return (1);
}
//�������ܣ��õ�����������ͼ�ε���С�������
//����������rect������
long GetMBR(CRect &rect)
{
	int i,j;
	POINT temp;
	double minx,miny,maxx,maxy;
	if(GPntTmpFOpened==0&&GLinTmpFOpened==0&&GRegTmpFOpened==0)
		return (0);
	if(GPntTmpFOpened==1&&GPntNum!=0)				//��minx,miny,maxx,maxy���г�ʼ�����������ǲ�֪���ļ��Ƿ������ÿ������ʼ��
	{
		GPntTmpFile.Seek(0,CFile::begin);
		GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
		minx=PNT_STRU.x;
		maxx=PNT_STRU.x;
		miny=PNT_STRU.y;
		maxy=PNT_STRU.y;
	}
	if(GLinTmpFOpened==1&&GLinNum!=0)
	{
		GLinTmpFile1.Seek(0,CFile::begin);
		do{
			GLinTmpFile1.Read(&LIN_NDX_STRU,sizeof(LIN_NDX_STRU));
		}while(LIN_NDX_STRU.isDel==1);
		GLinTmpFile2.Seek(LIN_NDX_STRU.datOff,CFile::begin);
		GLinTmpFile2.Read(&temp,sizeof(POINT));					//ȡ��һ������г�ʼ��
		minx=temp.x;
		maxx=temp.x;
		miny=temp.y;
		maxy=temp.y;
	}
	if(GRegTmpFOpened==1&&GRegNum!=0)
	{
		GRegTmpFile1.Seek(0,CFile::begin);
		do{
			GRegTmpFile1.Read(&REG_NDX_STRU,sizeof(REG_NDX_STRU));
		}while(REG_NDX_STRU.isDel==1);
		GRegTmpFile2.Seek(REG_NDX_STRU.datOff,CFile::begin);
		GRegTmpFile2.Read(&temp,sizeof(POINT));
		minx=temp.x;
		maxx=temp.x;
		miny=temp.y;
		maxy=temp.y;
	}
	if(GPntTmpFOpened==1&&GPntNum!=0)
	{
		GPntTmpFile.Seek(0,CFile::begin);
		for(i=0;i<GPntNum;i++)   //�������еĵ�
		{
			GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
			if(PNT_STRU.isDel==0)            
			{
				if(PNT_STRU.x<minx)					
					minx=PNT_STRU.x;					
				if(PNT_STRU.x>maxx)				
					maxx=PNT_STRU.x;					
				if(PNT_STRU.y<miny)					
					miny=PNT_STRU.y;					
				if(PNT_STRU.y>maxy)					
					maxy=PNT_STRU.y;
			}
		}
	}
	if(GLinTmpFOpened==1&&GLinNum!=0)
	{
		GLinTmpFile1.Seek(0,CFile::begin);
		for(i=0;i<GLinNum;i++)
		{
			GLinTmpFile1.Read(&LIN_NDX_STRU,sizeof(LIN_NDX_STRU));
			if(LIN_NDX_STRU.isDel==0)
			{
				GLinTmpFile2.Seek(LIN_NDX_STRU.datOff,CFile::begin);
				for(j=0;j<LIN_NDX_STRU.dotNum;j++)
				{
					GLinTmpFile2.Read(&temp,sizeof(POINT));
					if(temp.x<minx)					
						minx=temp.x;					
					if(temp.x>maxx)				
						maxx=temp.x;					
					if(temp.y<miny)					
						miny=temp.y;					
					if(temp.y>maxy)					
						maxy=temp.y;
				}
			}
		}
	}
	if(GRegTmpFOpened==1&&GRegNum!=0)
	{
		GRegTmpFile1.Seek(0,CFile::begin);
		for(i=0;i<GRegNum;i++)
		{
			GRegTmpFile1.Read(&REG_NDX_STRU,sizeof(REG_NDX_STRU));
			if(REG_NDX_STRU.isDel==0)
			{
				GRegTmpFile1.Seek(REG_NDX_STRU.datOff,CFile::begin);
				for(j=0;j<REG_NDX_STRU.dotNum;j++)
				{
					GRegTmpFile2.Read(&temp,sizeof(POINT));
					if(temp.x<minx)					
						minx=temp.x;					
					if(temp.x>maxx)				
						maxx=temp.x;					
					if(temp.y<miny)					
						miny=temp.y;					
					if(temp.y>maxy)					
						maxy=temp.y;
				}
			}
		}
	}
	rect.bottom=maxy;
	rect.top=miny;
	rect.left=minx;
	rect.right=maxx;
	return (1);
}