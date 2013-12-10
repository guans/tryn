#pragma once
#include "stdafx.h"
#include <afx.h>
#include "FileStruct.h"
#include"trynView.h"


//�������ܣ����ļ��мӵ�
//������ ������
long AppendPnt(CPoint xy)  
	{
	
		GPntNum++,GPntLNum++;	  //����������߼������Լ�
	
		if(1==GPntTmpFOpened)
		{

		int len=GPntTmpFile.GetLength();
		GPntTmpFile.Seek(len,CFile::current);     //���ļ�ĩβд

		//�ṹ���е�����
		PNT_STRU.isDel=0;
		PNT_STRU.color=0;
		PNT_STRU.pattern=0;
		PNT_STRU.x=xy.x;
		PNT_STRU.y=xy.y;
		GPntTmpFile.Write(&PNT_STRU,sizeof(PNT_STRU));  //���ṹ��д���ļ�
		//GPntTmpFile.Close();  //�ر��ļ�

		}

		return 1;
	}


//�������ܣ�Ѱ������㺯��1
//������ ������
long FindNearestPnt(CPoint &xy)				
	{
		// TODO: �ڴ����ʵ��Ѱ������㺯��

		//CFile file;
		int i=0;
		int temp=0;
		int len=0;
		char xx[4];
		char yy[4];
		long tempX=0;
		long tempY=0;
		long tempJuli=0;
		long resultX=0;                // �ҵ���̾���ĵ�
		long resultY=0;


	//	file.Open (_T("E:\\���\\���ڱ���\\MapEditor\\tempfile\\GPntTmpFile.pnt"),CFile::modeReadWrite/*|CFile::shareDenyWrite*/);

		len=GPntTmpFile.GetLength();
		GPntTmpFile.Seek(0,CFile::begin);

		for(i=0;i<len/sizeof(PNT_STRU);i++)   //�������еĵ�,������ĵ�
		{
			GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
			tempX=PNT_STRU.x;
			tempY=PNT_STRU.y;	
			temp=(tempX-xy.x) * (tempX-xy.x) + (tempY -xy.y) * (tempY -xy.y);
			if(i == 0) tempJuli = temp;
			if(temp <= tempJuli)
			{
				resultX = tempX;
				resultY = tempY;     //���������
				tempJuli=temp;
			}

		}
		xy.x=resultX;
		xy.y=resultY;      //�������������
	//	file.Close();  //�ر��ļ�
		return 1;
	}

//�������ܣ�Ѱ������㺯��2
//������ ������
long FindNearestPnt(CPoint xy,long x,long y,pnt_stru *ptpnt=NULL)		 //Ѱ������㺯��2
	{
		// TODO: �ڴ����ʵ��Ѱ������㺯��
		CFile file;
		int n=0;                       //���ز��ҵ������
		int i=0;
		int temp=0;
		int len=0;
		char xx[4];
		char yy[4];
		long tempX=0;
		long tempY=0;
		long tempJuli=0;
		long resultX=0;                // �ҵ���̾���ĵ�
		long resultY=0;

		//file.Open (_T("E:\\���\\���ڱ���\\MapEditor\\tempfile\\GPntTmpFile.pnt"),CFile::modeReadWrite/*|CFile::shareDenyWrite*/);

		len=file.GetLength();
		file.Seek(0,CFile::begin);

		for(i=0;i<len/sizeof(PNT_STRU);i++)		//�������еĵ�,������ĵ�
		{   n++;								//����ŵ���
			file.Read(&PNT_STRU, sizeof( PNT_STRU ));
			tempX=PNT_STRU.x;
			tempY=PNT_STRU.y;	
			temp=(tempX-xy.x) * (tempX-xy.x) + (tempY -xy.y) * (tempY -xy.y);
			if(i == 0) tempJuli = temp;
			if(temp <= tempJuli)
			{
				resultX = tempX;
				resultY = tempY;     //���������
				tempJuli=temp;
			}

		}
		x=resultX;
		y=resultY;      //�������������
		ptpnt->x=resultX;
		ptpnt->y=resultY;
		file.Close();  //�ر��ļ�
		return n;
	}

//�������ܣ����ļ���ɾ��
//������ ������
	long DeletePnt(CPoint xy)  
	{
		int perPntLen=sizeof(TEM_PNT);   //��ṹ�峤��
		int n=0;                          //Ҫɾ�������
		long tempX=0;
		long tempY=0;
		int len=0;
		int i=0;
		int filenow=0;
		FindNearestPnt(xy);
		tempX=xy.x;
		tempY=xy.y;
		//CFile file;
		//CFile filetemp;
		//file.Open (_T("E:\\���\\���ڱ���\\MapEditor\\tempfile\\GPntTmpFile.pnt"),CFile::modeReadWrite|CFile::typeBinary/*|CFile::shareDenyWrite*/);
		try{
			len=GPntTmpFile.GetLength(); //����ļ�����
		}catch(CFileException){          }

		GPntTmpFile.Seek(0,CFile::begin);

		for(i=0;i<len / perPntLen;i++)   //�������еĵ�,�������һ����
		{
			GPntTmpFile.Read(&PNT_STRU, perPntLen );
			if(PNT_STRU.x==tempX && PNT_STRU.y == tempY)
			{
				GPntTmpFile.Seek(-perPntLen,CFile::current); 
				//filenow=file.GetPosition();
				TEM_PNT=PNT_STRU;
				TEM_PNT.isDel=1;
				GPntTmpFile.Write(&TEM_PNT,perPntLen);   //�����޸ĺ������
				
			}

		}

	//	file.Close();
		return 1;
		
	}

//�������ܣ����ļ����ƶ���
//������ �����꣬Ҫ�ƶ�������

	long MovePnt(CPoint xy,CPoint toMove)  //// 
	{	
		int perPntLen=sizeof(TEM_PNT);			//��ṹ�峤��
		long tempX=0;
		long tempY=0;
		int len=0;
		int i=0;
		int filenow=0;
		
	    
		FindNearestPnt(toMove);
		tempX=toMove.x;
		tempY=toMove.y;							 //Ҫ�ƶ��ĵ�
	//	CFile file;
		
	//	file.Open (_T("E:\\���\\���ڱ���\\MapEditor\\tempfile\\GPntTmpFile.pnt"),CFile::modeReadWrite/*|CFile::shareDenyWrite*/);
		len=GPntTmpFile.GetLength();
		GPntTmpFile.Seek(0,CFile::begin);

		for(i=0;i<len / perPntLen;i++)					//�������еĵ�,�������һ����
		{
			GPntTmpFile.Read(&PNT_STRU, perPntLen);
			if(PNT_STRU.isDel==0 && PNT_STRU.x==tempX && PNT_STRU.y == tempY)
			{
				GPntTmpFile.Seek(-perPntLen,CFile::current); 
				TEM_PNT=PNT_STRU;
				TEM_PNT.x=xy.x;
				TEM_PNT.y=xy.y;							//�޸ĺ������
				GPntTmpFile.Write(&TEM_PNT,perPntLen);			//�����޸ĺ������
			}
		}
	//	file.Close();
		return (1);
	}


	