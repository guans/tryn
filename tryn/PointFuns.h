#pragma once
#include "stdafx.h"
#include <afx.h>
#include "FileStruct.h"
#include"trynView.h"


//函数功能：在文件中加点
//参数： 点坐标
long AppendPnt(CPoint xy)  
	{
	
		GPntNum++,GPntLNum++;	  //物理点数，逻辑点数自加
	
		if(1==GPntTmpFOpened)
		{

		int len=GPntTmpFile.GetLength();
		GPntTmpFile.Seek(len,CFile::current);     //从文件末尾写

		//结构体中点数据
		PNT_STRU.isDel=0;
		PNT_STRU.color=0;
		PNT_STRU.pattern=0;
		PNT_STRU.x=xy.x;
		PNT_STRU.y=xy.y;
		GPntTmpFile.Write(&PNT_STRU,sizeof(PNT_STRU));  //讲结构体写入文件
		//GPntTmpFile.Close();  //关闭文件

		}

		return 1;
	}


//函数功能：寻找最近点函数1
//参数： 点坐标
long FindNearestPnt(CPoint &xy)				
	{
		// TODO: 在此添加实现寻找最近点函数

		//CFile file;
		int i=0;
		int temp=0;
		int len=0;
		char xx[4];
		char yy[4];
		long tempX=0;
		long tempY=0;
		long tempJuli=0;
		long resultX=0;                // 找到最短距离的点
		long resultY=0;


	//	file.Open (_T("E:\\编程\\关于编书\\MapEditor\\tempfile\\GPntTmpFile.pnt"),CFile::modeReadWrite/*|CFile::shareDenyWrite*/);

		len=GPntTmpFile.GetLength();
		GPntTmpFile.Seek(0,CFile::begin);

		for(i=0;i<len/sizeof(PNT_STRU);i++)   //遍历所有的点,找最近的点
		{
			GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
			tempX=PNT_STRU.x;
			tempY=PNT_STRU.y;	
			temp=(tempX-xy.x) * (tempX-xy.x) + (tempY -xy.y) * (tempY -xy.y);
			if(i == 0) tempJuli = temp;
			if(temp <= tempJuli)
			{
				resultX = tempX;
				resultY = tempY;     //保存最近点
				tempJuli=temp;
			}

		}
		xy.x=resultX;
		xy.y=resultY;      //返回最近点坐标
	//	file.Close();  //关闭文件
		return 1;
	}

//函数功能：寻找最近点函数2
//参数： 点坐标
long FindNearestPnt(CPoint xy,long x,long y,pnt_stru *ptpnt=NULL)		 //寻找最近点函数2
	{
		// TODO: 在此添加实现寻找最近点函数
		CFile file;
		int n=0;                       //返回查找到的序号
		int i=0;
		int temp=0;
		int len=0;
		char xx[4];
		char yy[4];
		long tempX=0;
		long tempY=0;
		long tempJuli=0;
		long resultX=0;                // 找到最短距离的点
		long resultY=0;

		//file.Open (_T("E:\\编程\\关于编书\\MapEditor\\tempfile\\GPntTmpFile.pnt"),CFile::modeReadWrite/*|CFile::shareDenyWrite*/);

		len=file.GetLength();
		file.Seek(0,CFile::begin);

		for(i=0;i<len/sizeof(PNT_STRU);i++)		//遍历所有的点,找最近的点
		{   n++;								//点序号递增
			file.Read(&PNT_STRU, sizeof( PNT_STRU ));
			tempX=PNT_STRU.x;
			tempY=PNT_STRU.y;	
			temp=(tempX-xy.x) * (tempX-xy.x) + (tempY -xy.y) * (tempY -xy.y);
			if(i == 0) tempJuli = temp;
			if(temp <= tempJuli)
			{
				resultX = tempX;
				resultY = tempY;     //保存最近点
				tempJuli=temp;
			}

		}
		x=resultX;
		y=resultY;      //返回最近点坐标
		ptpnt->x=resultX;
		ptpnt->y=resultY;
		file.Close();  //关闭文件
		return n;
	}

//函数功能：在文件中删点
//参数： 点坐标
	long DeletePnt(CPoint xy)  
	{
		int perPntLen=sizeof(TEM_PNT);   //点结构体长度
		int n=0;                          //要删除的序号
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
		//file.Open (_T("E:\\编程\\关于编书\\MapEditor\\tempfile\\GPntTmpFile.pnt"),CFile::modeReadWrite|CFile::typeBinary/*|CFile::shareDenyWrite*/);
		try{
			len=GPntTmpFile.GetLength(); //获得文件长度
		}catch(CFileException){          }

		GPntTmpFile.Seek(0,CFile::begin);

		for(i=0;i<len / perPntLen;i++)   //遍历所有的点,找最近的一个点
		{
			GPntTmpFile.Read(&PNT_STRU, perPntLen );
			if(PNT_STRU.x==tempX && PNT_STRU.y == tempY)
			{
				GPntTmpFile.Seek(-perPntLen,CFile::current); 
				//filenow=file.GetPosition();
				TEM_PNT=PNT_STRU;
				TEM_PNT.isDel=1;
				GPntTmpFile.Write(&TEM_PNT,perPntLen);   //填入修改后的数据
				
			}

		}

	//	file.Close();
		return 1;
		
	}

//函数功能：在文件中移动点
//参数： 点坐标，要移动点坐标

	long MovePnt(CPoint xy,CPoint toMove)  //// 
	{	
		int perPntLen=sizeof(TEM_PNT);			//点结构体长度
		long tempX=0;
		long tempY=0;
		int len=0;
		int i=0;
		int filenow=0;
		
	    
		FindNearestPnt(toMove);
		tempX=toMove.x;
		tempY=toMove.y;							 //要移动的点
	//	CFile file;
		
	//	file.Open (_T("E:\\编程\\关于编书\\MapEditor\\tempfile\\GPntTmpFile.pnt"),CFile::modeReadWrite/*|CFile::shareDenyWrite*/);
		len=GPntTmpFile.GetLength();
		GPntTmpFile.Seek(0,CFile::begin);

		for(i=0;i<len / perPntLen;i++)					//遍历所有的点,找最近的一个点
		{
			GPntTmpFile.Read(&PNT_STRU, perPntLen);
			if(PNT_STRU.isDel==0 && PNT_STRU.x==tempX && PNT_STRU.y == tempY)
			{
				GPntTmpFile.Seek(-perPntLen,CFile::current); 
				TEM_PNT=PNT_STRU;
				TEM_PNT.x=xy.x;
				TEM_PNT.y=xy.y;							//修改后的坐标
				GPntTmpFile.Write(&TEM_PNT,perPntLen);			//填入修改后的数据
			}
		}
	//	file.Close();
		return (1);
	}


	