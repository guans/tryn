#include "stdafx.h"
//#include "FileStruct.h"
#include<vector>



//全局操作状态初始化
 int GCurOperState=0;							 //全局操作状态
 int GCurPNTState=0;							 //全局点操作
 int GCurLINState=0;							 //全局线操作
//1.点文件{
CFile GPntTmpFile,GPntFile;						//点临时文件、点永久文件
int GPntNum,GPntLNum;							//物理点数、逻辑点数
int GPntFCreated=0;								//点文件是否创建
int GPntChanged=0;								//点文件是否改变
char GPntFName[256];							//点文件名	
int GPntTmpFOpened=0;							//点临时文件是否被打开
//}
//2.线文件{
CFile GLinTmpFile1,GLinTmpFile2,GLinFile;		//线临时文件、线永久文件
int GLinNum,GLinLNum;							//物理线数、逻辑线数
int GLinFCreated=0;								//线文件是否创建
int GLinChanged=0;								//线文件是否改变
char GLinFName[256];							//线文件名	
int GLinTmpFOpened=0;							//点临时文件是否被打开
//}
//3.区文件{
CFile GRegTmpFile1,GRegTmpFile2,GRegFile;		//区临时文件、区永久文件
int GRegNum,GRegLNum;							//物理区数、逻辑区数
int GRegFCreated=0;								//区文件是否创建
int GRegChanged=0;								//区文件是否改变
char GRegFName[256];							//区文件名	
int GRegTmpFOpened=0;							//点临时文件是否被打开
//}
//4.{
double GZoom=1;									//比例系数
double GxOffset=0;								//保存相对于数据坐标系的x偏移与y偏移
double GyOffset=0;								
//}
