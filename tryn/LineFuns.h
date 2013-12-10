#pragma once
#include "stdafx.h"
#include <afx.h>
#include "FileStruct.h"
#include"trynView.h"
#include <math.h>
#include <vector>


//�������ܣ���㵽�߶���̾���  
//������������㣬�߶ε�1���߶ε�2��
double PointToSegDist(long x, long y, long x1, long y1, long x2, long y2)
{
	double cross = (x2 - x1) * (x - x1) + (y2 - y1) * (y - y1);
	if (cross <= 0) return sqrt((double)(x - x1) * (x - x1) + (y - y1) * (y - y1));

	double d2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	if (cross >= d2) return sqrt((double)(x - x2) * (x - x2) + (y - y2) * (y - y2));

	double r = cross / d2;
	double px = x1 + (x2 - x1) * r;
	double py = y1 + (y2 - y1) * r;

	return sqrt((x - px) * (x - px) + (py - y1) * (py - y1));

}



//�������ܣ����ļ��в����������  
//������ �����꣬���
long FindNearLine(CPoint point,int &num)  
{
	int toDel=0;		//���ص�������
	//CFile linedata;
	//CFile linendx;

	double temp;
	long resultX;
	long resultY;
	long tempX;
	long tempY;
	double tempdist=0;
	double resultdist=0;

	int resultL=0;				//���շ��ص������
	int resultLine=0;			//���շ��ص������

	int ii=0;
	int j=0;
	int k=0;
	int datalen=0;
	int ndxlen=0;
	int dotnum=0;
	int datff=0;
	CPoint ptemp;
	int ptemp2=0;
	bool isStrat=0;
	int linlen=sizeof(LIN_NDX_STRU);
	int plen=sizeof(PNT_STRU);
	tempX=point.x;
	tempY=point.y;
	if(1==GLinFCreated)
	{
		datalen=GLinTmpFile2.GetLength();
		ndxlen=GLinTmpFile1.GetLength();

		GLinTmpFile2.Seek(0,CFile::begin);
		GLinTmpFile1.Seek(0,CFile::begin);

		for(ii=0;ii< ndxlen / linlen;ii++)   //�������е�������
		{
			
			GLinTmpFile1.Read(&LIN_NDX_STRU, linlen);
		    resultL++;

			if(LIN_NDX_STRU.isDel==0)            //��û��ɾ������
			{
				dotnum=LIN_NDX_STRU.dotNum;
				datff=LIN_NDX_STRU.datOff;
				POINT *pp=new POINT[dotnum];
				GLinTmpFile2.Seek(datff,CFile::begin);
				for(j=0; j < dotnum ; j++)       // ĳ�������е����
				{
					GLinTmpFile2.Read(&PNT_STRU, plen );
					ptemp.x=PNT_STRU.x;
					ptemp.y=PNT_STRU.y;
					pp[j]=ptemp;
				}
				if(dotnum>0)
				{
					ptemp2++;;

					for(j=0; j < dotnum-1 ; j++)       // �����߷�Ϊ�߶�,��㵽�߶���̾���
					{
						k=j + 1;                    
						temp=PointToSegDist(point.x, point.y, pp[j].x, pp[j].y, pp[k].x, pp[k].y);
						if(j == 0) tempdist = temp;   //��һ���߶�
						if(temp <= tempdist)
						{
							tempdist =temp;
						}
					}
				}
				

				if( ptemp2==1) resultdist=tempdist;
				if(tempdist <= resultdist)
				{
					resultdist =tempdist;
					resultLine=resultL;		//���������ߺ�
				}
				isStrat=0;
				
				//resultdi//=tempdist//
			}

		}

		num=resultLine;
		resultLine=0;
		resultL=0;
		//linedata.Close();  //�ر��ļ�
		//linendx.Close();  //�ر��ļ�
	}

	return ( 1 );

}


//�������ܣ��洢ѡ������
//������Ҫ�洢���ߺ�,��Ҫ�������
	long SelectLinCon(int num, std::vector<CPoint> &v)     //�洢ѡ�����ߵ�
	{	
		
	//	CFile linedata;
	//	CFile linendx;

		int ii=0;
		int j=0;
		int datalen=0;
		int ndxlen=0;
		int dotnum=0;
		int datff=0;
		CPoint ptemp;
		CPoint todel;
		int linlen=sizeof(LIN_NDX_STRU);
		int plen=sizeof(PNT_STRU);

		if(1==GLinFCreated)
		{
			datalen=GLinTmpFile2.GetLength();
			ndxlen=GLinTmpFile1.GetLength();

			GLinTmpFile1.Seek( (num -1) * linlen,CFile::begin);  //�ҵ�������ΪtoErase����
			GLinTmpFile1.Read(&LIN_NDX_STRU,  linlen);
			dotnum=LIN_NDX_STRU.dotNum;
			datff=LIN_NDX_STRU.datOff;
			GLinTmpFile2.Seek(datff,CFile::begin);           //�������ҵ�������ΪtoErase��������

			for(j=0 ; j < dotnum ; j++)                //�ӵ�2���㿪ʼ
			{
				GLinTmpFile2.Read(&PNT_STRU, plen );
				todel.x=PNT_STRU.x;
				todel.y=PNT_STRU.y;
				v.push_back(todel);
			}

		}

		return 1;


	}

