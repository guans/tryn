#include "stdafx.h"
//#include "FileStruct.h"
#include<vector>



//ȫ�ֲ���״̬��ʼ��
 int GCurOperState=0;							 //ȫ�ֲ���״̬
 int GCurPNTState=0;							 //ȫ�ֵ����
 int GCurLINState=0;							 //ȫ���߲���
//1.���ļ�{
CFile GPntTmpFile,GPntFile;						//����ʱ�ļ����������ļ�
int GPntNum,GPntLNum;							//����������߼�����
int GPntFCreated=0;								//���ļ��Ƿ񴴽�
int GPntChanged=0;								//���ļ��Ƿ�ı�
char GPntFName[256];							//���ļ���	
int GPntTmpFOpened=0;							//����ʱ�ļ��Ƿ񱻴�
//}
//2.���ļ�{
CFile GLinTmpFile1,GLinTmpFile2,GLinFile;		//����ʱ�ļ����������ļ�
int GLinNum,GLinLNum;							//�����������߼�����
int GLinFCreated=0;								//���ļ��Ƿ񴴽�
int GLinChanged=0;								//���ļ��Ƿ�ı�
char GLinFName[256];							//���ļ���	
int GLinTmpFOpened=0;							//����ʱ�ļ��Ƿ񱻴�
//}
//3.���ļ�{
CFile GRegTmpFile1,GRegTmpFile2,GRegFile;		//����ʱ�ļ����������ļ�
int GRegNum,GRegLNum;							//�����������߼�����
int GRegFCreated=0;								//���ļ��Ƿ񴴽�
int GRegChanged=0;								//���ļ��Ƿ�ı�
char GRegFName[256];							//���ļ���	
int GRegTmpFOpened=0;							//����ʱ�ļ��Ƿ񱻴�
//}
//4.{
double GZoom=1;									//����ϵ��
double GxOffset=0;								//�����������������ϵ��xƫ����yƫ��
double GyOffset=0;								
//}
