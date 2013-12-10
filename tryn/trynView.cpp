
// trynView.cpp : CtrynView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "tryn.h"
#endif

#include "trynDoc.h"
#include "trynView.h"

#include"FileStruct.h"
#include"PointFuns.h"
#include"LineFuns.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include<cmath>
#include<vector>
using namespace std;

static vector<CPoint> tempLins;    //存放当前临时线中数据
static vector<CPoint> ConResult;   //存放连接后


// CMapEditor10View
IMPLEMENT_DYNCREATE(CtrynView, CView)

	BEGIN_MESSAGE_MAP(CtrynView, CView)
		// 标准打印命令
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CtrynView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		//		ON_WM_RBUTTONUP()
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_COMMAND(ID_CREATE_PNT, &CtrynView::OnCreatePnt)
		ON_COMMAND(ID_32781, &CtrynView::OnDelPnt)
		ON_COMMAND(ID_32780, &CtrynView::OnMovePnt)
		ON_WM_MOUSEMOVE()
		ON_COMMAND(ID_FILE_NEW, &CtrynView::OnFileNew)
		ON_COMMAND(ID_FILE_OPEN, &CtrynView::OnFileOpen)
		ON_COMMAND(ID_FILE_SAVE, &CtrynView::OnFileSave)
		ON_COMMAND(ID_FILE_SAVE_AS, &CtrynView::OnFileSaveAs)
		ON_COMMAND(ID_ZOOMIN, &CtrynView::OnZoomin)
		ON_COMMAND(ID_ZOOMOUT, &CtrynView::OnZoomout)
		ON_COMMAND(ID_CREATE_LIN, &CtrynView::OnCreateLin)
		ON_COMMAND(ID_MOVE_LIN, &CtrynView::OnMoveLin)
		ON_COMMAND(ID_DEL_LIN, &CtrynView::OnDelLin)
		ON_WM_RBUTTONUP()
		ON_COMMAND(ID_WINMOVE, &CtrynView::OnWinmove)
		ON_COMMAND(ID_WINRESET, &CtrynView::OnWinreset)
		ON_COMMAND(ID_CONNECT_LIN, &CtrynView::OnConnectLin)
		ON_COMMAND(ID_SHWODELPNT, &CtrynView::OnShwodelpnt)
	END_MESSAGE_MAP()

	// CtrynView 构造/析构

	CtrynView::CtrynView()
	{
		// TODO: 在此处添加构造代码
		isLeftBDown=0;
		linePnt=0;
		GLinNum=0;
		GLinLNum=0;

		MakingLine=0;

		linNum=0;
		step=0;

		isfirst=0;
		issecond=0;

	}



	CtrynView::~CtrynView()
	{
	}

	BOOL CtrynView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return CView::PreCreateWindow(cs);
	}

	// CtrynView 绘制

	//重画函数
	void CtrynView::OnDraw(CDC* pDC)                
	{
		MakingLine=0;
		CtrynDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;


		if(GCurPNTState==0)
		{
			//画点
			//CFile file;
			int i=0;
			int len=0;
			long tempX=0;
			long tempY=0;
			CPoint temp;

			if(1==GPntTmpFOpened)
			{
				len=GPntTmpFile.GetLength();
				GPntTmpFile.Seek(0,CFile::begin);

				for(i=0;i<len/sizeof(PNT_STRU);i++)   //遍历所有的点
				{
					GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
					if(PNT_STRU.isDel==0)            //画出没被删掉的点
					{
						temp.x=PNT_STRU.x;
						temp.y=PNT_STRU.y;	
						DrawPoint(temp);
					}

				}

				//GPntTmpFile.Close();  //关闭文件
			}

		}

		else if(GCurPNTState==1)
		{
			//画点
			//CFile file;
			int i=0;
			int len=0;
			long tempX=0;
			long tempY=0;
			CPoint temp;

			if(1==GPntTmpFOpened)
			{
				len=GPntTmpFile.GetLength();
				GPntTmpFile.Seek(0,CFile::begin);

				for(i=0;i<len/sizeof(PNT_STRU);i++)   //遍历所有的点
				{
					GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
					if(PNT_STRU.isDel==1)            //画被删掉的点
					{
						temp.x=PNT_STRU.x;
						temp.y=PNT_STRU.y;	
						DrawPoint(temp);
					}

				}

			//	GPntTmpFile.Close();  //关闭文件
			}


		}
		//画线
	//	CFile linedata;
	//	CFile linendx;

		int ii=0;
		int j=0;
		int datalen=0;
		int ndxlen=0;
		int dotnum=0;
		int datff=0;
		CPoint ptemp;
		int linlen=sizeof(LIN_NDX_STRU);
		int plen=sizeof(PNT_STRU);

		if(1==GLinFCreated)
		{
			datalen=GLinTmpFile2.GetLength();
			ndxlen=GLinTmpFile1.GetLength();
			GLinTmpFile2.Seek(0,CFile::begin);
			GLinTmpFile1.Seek(0,CFile::begin);

			for(ii=0;ii< ndxlen / linlen;ii++)   //遍历所有的线索引
			{
				GLinTmpFile1.Read(&LIN_NDX_STRU,  linlen);
				if(LIN_NDX_STRU.isDel==0)            //画出没被删掉的线
				{
					dotnum=LIN_NDX_STRU.dotNum;
					datff=LIN_NDX_STRU.datOff;

					GLinTmpFile2.Seek(datff,CFile::begin);
					POINT *p=new POINT[dotnum];
					for(j=0; j < dotnum ; j++)
					{
						GLinTmpFile2.Read(&PNT_STRU, plen );
						ptemp.x=PNT_STRU.x;
						ptemp.y=PNT_STRU.y;
						p[j]=ptemp;
					}
					for(j=0; j < dotnum ; j++)
					{
						if(j==0)
							pDC->MoveTo(p[j]);
						else
							pDC->LineTo(p[j]);
					}
				}
			}
			ReleaseDC(pDC);
			//GLinTmpFile2.Close();  //关闭文件
			//GLinTmpFile1.Close();  //关闭文件
		}

		//清空移动线数据
		firstlinnum=0;
		seclinnum=0;
		isfirst=0;
		issecond=0;

		ConResult.clear();
	}


	// CtrynView 打印


	void CtrynView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CtrynView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 默认准备
		return DoPreparePrinting(pInfo);
	}

	void CtrynView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加额外的打印前进行的初始化过程
	}

	void CtrynView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加打印后进行的清理过程
	}

	//	void CtrynView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	//	{
	//		ClientToScreen(&point);
	//		OnContextMenu(this, point);
	//	}

	void CtrynView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CtrynView 诊断

#ifdef _DEBUG
	void CtrynView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CtrynView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CtrynDoc* CtrynView::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtrynDoc)));
		return (CtrynDoc*)m_pDocument;
	}
#endif //_DEBUG


	//函数功能：点画图函数实现
	//参数：点坐标
	long CtrynView::DrawPoint(CPoint tempxy)       //图像上画点
	{
		//获得本窗口或当前活动视图
		CClientDC dc(this);
		//设置异或模式画点
		//dc.SetROP2(R2_NOT);
		CPen  newPen(PS_SOLID,2,RGB(192,192,192));
		dc.MoveTo(tempxy.x,tempxy.y-6);
		dc.LineTo(tempxy.x,tempxy.y+6);
		dc.MoveTo(tempxy.x-6,tempxy.y);
		dc.LineTo(tempxy.x+6,tempxy.y);
		::ReleaseDC(m_hWnd,dc);
		return (1);
	}

	//函数功能：图像上移动点
	//参数：当前点坐标
	long CtrynView::MovePoint(CPoint tempxy)    
	{
		CPen newpen(PS_SOLID,2,RGB(255,255,255));//构造画笔对象
		//获得本窗口或当前活动视图
		CClientDC dc(this);
		CPen *pOldPen=dc.SelectObject(&newpen);//将画笔选入DC，SelectObject函数返回先前画笔
		//设置异或模式画点
		//dc.SetROP2(R2_NOT);	
		//这里抹去一个小十字
		dc.MoveTo(nowPoint.x,nowPoint.y-6);
		dc.LineTo(nowPoint.x,nowPoint.y+6);
		dc.MoveTo(nowPoint.x-6,nowPoint.y);
		dc.LineTo(nowPoint.x+6,nowPoint.y);
		CPen oldpen(PS_SOLID,2,RGB(192,192,192));	//构造画笔对象
		dc.SelectObject(&oldpen);					//将画笔选入DC，SelectObject函数返回先前画笔
		//这里画一个小十字
		dc.MoveTo(tempxy.x,tempxy.y-6);
		dc.LineTo(tempxy.x,tempxy.y+6);
		dc.MoveTo(tempxy.x-6,tempxy.y);
		dc.LineTo(tempxy.x+6,tempxy.y);
		nowPoint=tempxy;							//把当前点存为上一点

		::ReleaseDC(m_hWnd,dc);
		return (1);

	}
	//函数功能：图像上擦除点
	//参数：点坐标
	long CtrynView::ErasePoint(CPoint tempxy)		 
	{

		CPoint toErase;
		FindNearestPnt(tempxy) ;
		toErase=tempxy;									 //保存待删除点
		CPen newpen(PS_SOLID,2,RGB(255,255,255));		//构造画笔对象
		//获得本窗口或当前活动视图
		CClientDC dc(this);
		CPen *pOldPen=dc.SelectObject(&newpen);			//将画笔选入DC，SelectObject函数返回先前画笔
		//设置异或模式画点
		//dc.SetROP2(R2_NOT);	
		//这里抹去一个小十字
		dc.MoveTo(toErase.x,toErase.y-6);
		dc.LineTo(toErase.x,toErase.y+6);
		dc.MoveTo(toErase.x-6,toErase.y);
		dc.LineTo(toErase.x+6,toErase.y);

		::ReleaseDC(m_hWnd,dc);
		return 1;

	}

	//点画图函数实现

	//函数功能：图像上画线
	//参数：当前点坐标
	long CtrynView::DrawLine(CPoint tempxy)       
	{
		if(linePnt!=0)
		{
			//获得本窗口或当前活动视图
			CClientDC dc(this);
			//设置异或模式画点
			//dc.SetROP2(R2_NOT);
			DrawPoint(lastPoint);   
			DrawPoint(tempxy);       
			CPen  newPen(PS_SOLID,2,RGB(192,192,192));
			dc.MoveTo(lastPoint.x,lastPoint.y);
			dc.LineTo(tempxy.x,tempxy.y);

			::ReleaseDC(m_hWnd,dc);
		}
		else
		{
			DrawPoint(tempxy); 
		}
		lastPoint=tempxy;
		linePnt++;
		return (1);
	}

	//函数功能：图像上擦除线
	//参数：要擦除线的编号
	long CtrynView::EraseLine(long toErase)     //
	{
		int num=0;

		num=toErase;										//保存待删除线索引号
		CPen newpen(PS_SOLID,2,RGB(255,255,255));			//构造画笔对象
		CClientDC dc(this);									//获得本窗口或当前活动视图
		CPen *pOldPen=dc.SelectObject(&newpen);				//将画笔选入DC，SelectObject函数返回先前画笔
		//设置异或模式画点 //dc.SetROP2(R2_NOT);	
		//这里抹去一个一条线

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
			//linedata.Seek(0,CFile::begin);
			GLinTmpFile1.Seek( (toErase -1) * linlen,CFile::begin);  //找到索引号为toErase的线
			GLinTmpFile1.Read(&LIN_NDX_STRU,  linlen);
			dotnum=LIN_NDX_STRU.dotNum;
			datff=LIN_NDX_STRU.datOff;
			GLinTmpFile2.Seek(datff,CFile::begin);				  //数据中找到索引号为toErase的线数据

			GLinTmpFile2.Read(&PNT_STRU, plen );				 //线第一个点
			ptemp.x=PNT_STRU.x;
			ptemp.y=PNT_STRU.y;
			dc.MoveTo(ptemp);
			for(j=1 ; j < dotnum ; j++)						//从第2个点开始
			{
				GLinTmpFile2.Read(&PNT_STRU, plen );
				todel.x=PNT_STRU.x;
				todel.y=PNT_STRU.y;
				dc.LineTo(todel);
			}

		}
		return 1;

	}

	//函数功能：文件中擦除线
	//参数：要擦除线的编号
	long CtrynView::DelLine(long toErase)     
	{
		int num=0;
		num=toErase;									//保存待删除线索引号
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
		//修改索引文件
		if(1==GLinFCreated)
		{
			ndxlen=GLinTmpFile1.GetLength();
			GLinTmpFile1.Seek( (num -1) * linlen,CFile::begin);
			GLinTmpFile1.Read(&TEM_LIN,linlen);
			TEM_LIN.isDel= 1;
			LIN_NDX_STRU=TEM_LIN;
			GLinTmpFile1.Seek( -linlen,CFile::current);			 //找到索引号为toErase的线

			GLinTmpFile1.Write(&LIN_NDX_STRU,linlen);

	//		GLinTmpFile1.Close();							//关闭文件

		}
		return 1;
	}

	//函数功能：图像中移动线
	//参数：坐标点
	long CtrynView::MoveLin(CPoint point)			 //
	{	
		int i;
		CPoint pt;
		vector<CPoint> lins;
		if(step==0)
		{
			startPnt.x=0;
			startPnt.y=0;
			return (0);
		}
		else if(step==1)
		{
			CClientDC dc(this);							//获得本窗口或当前活动视图
			CPen newpen(PS_SOLID,2,RGB(255,255,255));	//构造画笔对象
			CPen *pOldPen=dc.SelectObject(&newpen);		//将画笔选入DC，SelectObject函数返回先前画笔

			long disX=point.x - startPnt.x;				//计算坐标偏移
			long disY=point.y - startPnt.y;

			for(i=0;i< tempLins.size();i++)
			{
				if(i==0)
					dc.MoveTo(tempLins[i]);
				else
					dc.LineTo(tempLins[i]);

				pt.x=tempLins[i].x + disX;
				pt.y=tempLins[i].y + disY;
				lins.push_back(pt);
			}
			CPen oldpen(PS_SOLID,2,RGB(192,192,192));		//构造画笔对象
			dc.SelectObject(&oldpen);						//将画笔选入DC，SelectObject函数返回先前画笔

			for(i=0;i<lins.size();i++)
			{
				if(i==0)
					dc.MoveTo(lins[i]);
				else
					dc.LineTo(lins[i]);
			}
			tempLins=lins;
			lins.clear();
			startPnt=point;
			::ReleaseDC(m_hWnd,dc);
		}
		return (1);
	}
	//函数功能：存储选定的线
	//参数：要存储的线号
	long CtrynView::SelectLin(int num)     //存储选定的线点
	{	
		CPen newpen(PS_SOLID,2,RGB(255,255,255));	//构造画笔对象
		CClientDC dc(this);							//获得本窗口或当前活动视图
		CPen *pOldPen=dc.SelectObject(&newpen);		//将画笔选入DC，SelectObject函数返回先前画笔
		//设置异或模式画点 //dc.SetROP2(R2_NOT);	
		//这里抹去一个一条线
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

			GLinTmpFile1.Seek( (num -1) * linlen,CFile::begin);  //找到索引号为toErase的线
			GLinTmpFile1.Read(&LIN_NDX_STRU,  linlen);
			dotnum=LIN_NDX_STRU.dotNum;
			datff=LIN_NDX_STRU.datOff;
			GLinTmpFile2.Seek(datff,CFile::begin);           //数据中找到索引号为toErase的线数据

			for(j=0 ; j < dotnum ; j++)                //从第2个点开始
			{
				GLinTmpFile2.Read(&PNT_STRU, plen );
				todel.x=PNT_STRU.x;
				todel.y=PNT_STRU.y;
				tempLins.push_back(todel);
			}

		}

		linNum=dotnum;
		return 1;


	}

	//函数功能：写移动后的线
	//参数：点坐标
	long CtrynView::MoveLinLBU(CPoint point)     
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
		//修改索引文件
		if(1==GLinFCreated)
		{
			ndxlen=GLinTmpFile1.GetLength();
			GLinTmpFile1.Seek( (linToMove -1) * linlen,CFile::begin);
			GLinTmpFile1.Read(&TEM_LIN,linlen);

			dotnum=LIN_NDX_STRU.dotNum;
			datff=LIN_NDX_STRU.datOff;

			GLinTmpFile2.Seek(datff,CFile::begin);

			for(j=0; j < dotnum ; j++)
			{

				PNT_STRU.x=tempLins[j].x;
				PNT_STRU.y=tempLins[j].y;

				GLinTmpFile2.Write(&PNT_STRU,plen);
			}

		//	GLinTmpFile1.Close();  //关闭文件
		//	GLinTmpFile2.Close();
		}
		return 1;


	}


	//函数功能：在文件中写索引和线数据
	//参数：
	long CtrynView::AppendLin()  
	{
		int lendata;
	//	CFile linedata;
		//int lenofp = sizeof(PNT_STRU);
		
		lendata=GLinTmpFile2.GetLength();
		GLinTmpFile2.Seek(lendata,CFile::begin);     //数据从文件末尾写

		GLinNum++,GLinLNum++;
		int pnum= tempLins.size() ;
		int lenndx;
		//CFile linendx;
		int lenofl=sizeof(LIN_NDX_STRU);        //索引结构长度
		int lenofp = sizeof(PNT_STRU);           //点结构长度
		

		lenndx=GLinTmpFile1.GetLength();
		GLinTmpFile1.Seek(lenndx,CFile::begin);     //索引从文件末尾写

		//写当前线索引
		LIN_NDX_STRU.color=0;
		LIN_NDX_STRU.datOff= GLinTmpFile2.GetLength();       //数据存储开始位置 一个点结构长度*点个数*线号
		LIN_NDX_STRU.dotNum=pnum;
		LIN_NDX_STRU.isDel=0;
		LIN_NDX_STRU.pattern=0;
		GLinTmpFile1.Write(&LIN_NDX_STRU,lenofl);  //讲结构体写入文件

		int i=0;
		for(i=0;i < pnum ; i++)
		{
			TEM_PNT.color=0;
			TEM_PNT.isDel=0;
			TEM_PNT.pattern=0;
			TEM_PNT.x=tempLins[i].x;
			TEM_PNT.y=tempLins[i].y;
			GLinTmpFile2.Write(&TEM_PNT,lenofp);  //数据结构体写入文件

		}
	//	linendx.Close();
	//	GLinTmpFile2.Close();
		return 1;
	}

	//函数功能：连接两条线
	//参数：线号1 2
	long CtrynView::ConnectLins(int lin1,int lin2)  
	{
		int i=0;
		int lin1num;
		int lin2num;
		double disX;
		double disY;
		CPoint temp;
		vector<CPoint> Lin1;
		vector<CPoint> Lin2;
		SelectLinCon(lin1,Lin1);
		SelectLinCon(lin2,Lin2);

		lin1num=Lin1.size();
		lin2num=Lin2.size();
		if(lin1num==0 || lin2num==0)
			return 0;
		else														//开始操作
		{
			if(Lin1[lin1num -1].x < Lin2[0].x)						//第一条线的尾 接第二个头
			{
				for(i=0;i< lin1num;i++)
					ConResult.push_back(Lin1[i]);

				for(i=0;i< lin2num;i++)
				{
					ConResult.push_back(Lin2[i]);
				}
			}
			else if(Lin1[lin1num-1].x > Lin2[0].x)				//第一个尾 接 第二个尾
			{
				for(i=0;i< lin1num;i++)
					ConResult.push_back(Lin1[i]);
				for(i= lin2num-1;i>=0;i--)
				{
					ConResult.push_back(Lin2[i]);
				}
			}
			else if(Lin1[0].x < Lin2[lin2num-1].x)				//第一条头 接第二个头
			{

			}
			else if(Lin1[0].x > Lin2[lin2num-1].x)			   //第一条 头 接第二个 尾
			{

			}
		}

		EraseLine(lin1);									//擦除两条线
		EraseLine(lin2);
		DelLine(lin1);								     //文件中删除两条线
		DelLine(lin2);
		WriteConLine();
		DrawConLine();
		firstlinnum=0;
		seclinnum=0;
		isfirst=0;
		issecond=0;
		return 1;
	}



	long CtrynView::DrawConLine( )
	{
		int i=0;
		CClientDC dc(this);							//获得本窗口或当前活动视图
		CPen newpen(PS_SOLID,2,RGB(192,192,192));	//构造画笔对象
		CPen *pOldPen=dc.SelectObject(&newpen);		//将画笔选入DC，SelectObject函数返回先前画笔
		for(i=0;i< ConResult.size();i++)
		{
			if(i==0)
				dc.MoveTo(ConResult[i]);
			else
				dc.LineTo(ConResult[i]);
		}
		ConResult.clear();

		return 1;
	}

	long CtrynView::WriteConLine( )
	{
		int linnum=ConResult.size();
		int lendata;
		//CFile linedata;
		//int lenofp = sizeof(PNT_STRU);
		//linedata.Open (_T("E:\\编程\\关于编书\\MapEditor\\tempfile\\GLinTmpFFile2.lin"),CFile::modeReadWrite/*|CFile::shareDenyWrite*/);
		lendata=GLinTmpFile2.GetLength();
		GLinTmpFile2.Seek(lendata,CFile::begin);     //数据从文件末尾写

		int lenndx;
		//CFile linendx;
		int lenofl=sizeof(LIN_NDX_STRU);        //索引结构长度
		int lenofp = sizeof(PNT_STRU);           //点结构长度
	//	linendx.Open (_T("E:\\编程\\关于编书\\MapEditor\\tempfile\\GLinTmpFFile1.lin"),CFile::modeReadWrite/*|CFile::shareDenyWrite*/);

		lenndx=GLinTmpFile1.GetLength();
		GLinTmpFile1.Seek(lenndx,CFile::begin);     //索引从文件末尾写

		//写当前线索引
		LIN_NDX_STRU.color=0;
		LIN_NDX_STRU.datOff= GLinTmpFile2.GetLength();       //数据存储开始位置 一个点结构长度*点个数*线号
		LIN_NDX_STRU.dotNum=linnum;
		LIN_NDX_STRU.isDel=0;
		LIN_NDX_STRU.pattern=0;
		GLinTmpFile1.Write(&LIN_NDX_STRU,lenofl);				//讲结构体写入文件

		int i=0;
		for(i=0;i < linnum ; i++)
		{
			TEM_PNT.color=0;
			TEM_PNT.isDel=0;
			TEM_PNT.pattern=0;
			TEM_PNT.x=ConResult[i].x;
			TEM_PNT.y=ConResult[i].y;
			GLinTmpFile2.Write(&TEM_PNT,lenofp);				//数据结构体写入文件

		}
	//	linendx.Close();
	//	linedata.Close();

		return 1;

	}


	long CtrynView::DrawConLine(int num)
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

		int linlen=sizeof(LIN_NDX_STRU);
		int plen=sizeof(PNT_STRU);
		//修改索引文件
		if(1==GLinFCreated)
		{
			datalen=GLinTmpFile2.GetLength();
			ndxlen=GLinTmpFile1.GetLength();

			GLinTmpFile1.Seek( (num -1) * linlen,CFile::begin);  //找到索引号为toErase的线
			GLinTmpFile1.Read(&LIN_NDX_STRU,  linlen);
			dotnum=LIN_NDX_STRU.dotNum;
			datff=LIN_NDX_STRU.datOff;
			GLinTmpFile2.Seek(datff,CFile::begin);           //数据中找到索引号为toErase的线数据

			CClientDC dc(this);							//获得本窗口或当前活动视图
			CPen newpen(PS_SOLID,2,RGB(192,0,0));	//构造画笔对象
			CPen *pOldPen=dc.SelectObject(&newpen);		//将画笔选入DC，SelectObject函数返回先前画笔


			for(j=0; j < dotnum ; j++)
			{
				GLinTmpFile2.Read(&PNT_STRU,plen);
				ptemp.x=PNT_STRU.x;
				ptemp.y=PNT_STRU.y;
				if(j==0)
					dc.MoveTo(ptemp);
				else
					dc.LineTo(ptemp);
			}

			//linendx.Close();  //关闭文件
			//linedata.Close();
		}
		return 1;	

	}


	long CtrynView::WindowMoveLBD(POINT xy)
	{
		startPnt=xy;
		return (1);
	}


	long CtrynView::WindowMoveLBU(POINT xy)
	{
		int i,j;
		POINT temp;
		CRect rect;
		CClientDC dc(this);
		double xOffset;
		double yOffset;
		xOffset=startPnt.x-xy.x;							//获得x方向上的偏移
		yOffset=startPnt.y-xy.y;							//获得y方向上的偏移
		GxOffset+=xOffset/GZoom;
		GyOffset+=yOffset/GZoom;
		GetClientRect(&rect);									//获取客户区矩形
		dc.FillRect(&rect,new CBrush(RGB(255,255,255)));			//空白覆盖客户区
		if(GPntTmpFOpened==1&&GPntNum!=0)
		{
			GPntTmpFile.Seek(0,CFile::begin);
			for(i=0;i<GPntNum;i++)							 //遍历所有的点
			{
				GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
				if(PNT_STRU.isDel==0)				  //画出没被删掉的点
				{
					temp.x=PNT_STRU.x;
					temp.y=PNT_STRU.y;	
					DotDPtoVP(temp);						//转换坐标
					CPen  newPen(PS_SOLID,2,RGB(192,192,192));
					dc.MoveTo(temp.x,temp.y-6);
					dc.LineTo(temp.x,temp.y+6);
					dc.MoveTo(temp.x-6,temp.y);
					dc.LineTo(temp.x+6,temp.y);

				}

			}
		}
		if(GLinTmpFOpened==1&&GLinNum!=0)
		{}

		startPnt.x = 0;
		startPnt.y = 0;
		return (1);
	}


	//区画图函数实现

	// CtrynView 消息处理程序
	//鼠标左键按下
	void CtrynView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值

		switch(GCurOperState)
		{
			//case OPERSTATE_INPUT_PNT:						//画点
			//	break;
			//case OPERSTATE_DEL_PNT:                     //删除点
			//	break;
		case OPERSTATE_MOV_PNT:								//移动点
			{
				nowPoint=point;								//存储当前点为前一点
				CPoint ptMove;
				FindNearestPnt(point);
				ptMove=point;
				toMove=point;
				CPen newpen(PS_SOLID,2,RGB(255,0,0));			//构造画笔对象
				CClientDC dc(this);								//获得本窗口或当前活动视图
				CPen *pOldPen=dc.SelectObject(&newpen);			//将画笔选入DC，SelectObject函数返回先前画笔
				//这里标亮要移动的点
				dc.MoveTo(ptMove.x,ptMove.y-6);
				dc.LineTo(ptMove.x,ptMove.y+6);
				dc.MoveTo(ptMove.x-6,ptMove.y);
				dc.LineTo(ptMove.x+6,ptMove.y);
				::ReleaseDC(m_hWnd,dc);
			}
			break;
		case OPERSTATE_MOVE_IIN:						 //设置操作状态为移动线
			{
				int num;
				startPnt=point;							//存储当前点为前一点
				FindNearLine(point,num);
				SelectLin(num);
				EraseLine(num);
				linToMove=num;                           //保存要移动的线号
				step=1;
			}
			break;
		case OPERSTATE_ZOOM_IN:							 //设置操作状态为放大
			ZoomInLBD(point);
			break;
		case OPERSTATE_WINDOW_MOVE:						//设置操作状态为窗口移动
			WindowMoveLBD(point);
			break;
		default:
			
			break;

		}
		CView::OnLButtonDown(nFlags, point);
	}

	//鼠标左键弹起
	void CtrynView::OnLButtonUp(UINT nFlags, CPoint point)  //
	{
		switch(GCurOperState)
		{
		case OPERSTATE_INPUT_PNT:						//画点
			AppendPnt(point);							//把新加的点写入临时文件
			DrawPoint(point);							//画出当前的点
			break;	
		case OPERSTATE_DEL_PNT:							//删除点
			DeletePnt(point);							//文件中删除点
			ErasePoint(point);							//图像中删除点
			break;
		case OPERSTATE_MOV_PNT:							//移动点
			MovePnt(point,toMove);						//文件中移动点   (移动到的点，要移动的点)
			Invalidate();								//刷新图像
			break;
		case OPERSTATE_ZOOM_IN:							//设置操作状态为放大
			ZoomInLBU(point);
			break;
		case OPERSTATE_ZOOM_OUT:						//设置操作状态为缩小
			ZoomOutLBU(point);
			break;	
		case OPERSTATE_INPUT_IIN:						 //造线
			{
				nowPoint=point;							 //存储前一个节点 	
				tempLins.push_back(point);				//当前点存入向量中
				MakingLine=1;							// 设置正在造点状态
				DrawLine(point);     					//画出当前的点
				break;
			}
		case OPERSTATE_DEL_IIN:							//删除线
			{
				CString str;
				int LineNum;					
				FindNearLine(point,LineNum);
				EraseLine(LineNum);						//图像中删除编号LineNum的线
				DelLine(LineNum);
				//str.Format("%d",LineNum);
				//MessageBox(_T(str));
				break;
			}
		case OPERSTATE_MOVE_IIN:								 //移动线
			MoveLinLBU(point);
			tempLins.clear();
			Invalidate();										//刷新图像
			break;		
		case OPERSTATE_WINDOW_MOVE:								//窗口移动
			WindowMoveLBU(point);
			break;
		case OPERSTATE_CONNECT_IIN:								//连接线
			{
				int firstnum;
				int secnum;
				if(isfirst==0)									//选中第一条线
				{
					FindNearLine(point,firstnum);
					firstlinnum=firstnum;						//保存第一条线号
					isfirst=1;
					DrawConLine(firstnum);
					CString sMousePos;
					CString nowstr="已经选择第一条线，请选择第二条";
					sMousePos.Format(_T(" %s "),nowstr);
					AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowText(sMousePos);
				}
				else if(issecond==0)
				{
					FindNearLine(point,secnum);
					if(firstlinnum!=secnum)
					{
						seclinnum=secnum;							//保存第二条线号
						issecond=1;
						DrawConLine(secnum);
					}
				}
				else if(firstlinnum!=0 &&seclinnum!=0 ) ConnectLins(firstlinnum,seclinnum);        //连接两条线

				ConResult.clear();

			}
			break;
		default:
			
			break;
		}
		CView::OnLButtonUp(nFlags, point);
	}



	void CtrynView::OnMouseMove(UINT nFlags, CPoint point)
	{
		if(nFlags==MK_LBUTTON)								//当前鼠标左键是否按下
		{
			switch(GCurOperState)
			{
			case OPERSTATE_MOV_PNT:							//移动点
				MovePoint(point);
				break;
			case OPERSTATE_ZOOM_IN:							//设置操作状态为放大
				ZoomInMM(point);
				break;
			case OPERSTATE_MOVE_IIN:						  //移动线
				MoveLin(point);
				break;
			default:
				break;
			}
		}
		else
			switch(GCurOperState)
		{

			case OPERSTATE_INPUT_IIN:									//设置操作状态为造线
				{
					if(MakingLine==1) {
						DrawPoint(point);
						CPen newpen(PS_SOLID,2,RGB(255,0,0));			//构造画笔对象
						CPen oldpen(PS_SOLID,2,RGB(255,255,255));		//构造画笔对象

						CClientDC dc(this);								//获得本窗口或当前活动视图
						//dc.SetROP2(R2_NOT);
						CPen *pOldPen=dc.SelectObject(&newpen);			//将画笔选入DC，SelectObject函数返回先前画笔
						//这里标亮要移动的点
						dc.MoveTo(lastPoint.x,lastPoint.y);
						dc.LineTo(point.x,point.y);

						dc.SelectObject(&oldpen);						//将画笔选入DC，SelectObject函数返回先前画笔
						//这里标亮要移动的点
						dc.MoveTo(lastPoint.x,lastPoint.y);
						dc.LineTo(templastPoint.x,templastPoint.y);
						//这里删除上一个点
						dc.MoveTo(templastPoint.x,templastPoint.y-6);
						dc.LineTo(templastPoint.x,templastPoint.y+6);
						dc.MoveTo(templastPoint.x-6,templastPoint.y);
						dc.LineTo(templastPoint.x+6,templastPoint.y);

						templastPoint=point;
						::ReleaseDC(m_hWnd,dc);
					}
				}  
				break;
			default:
				break;
		}

		// TODO:显示坐标用 
		/*	CString sMousePos;
		sMousePos.Format(_T("x=%d,y=%d"),point.x,point.y);
		AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowText(sMousePos);
		CView::OnMouseMove(nFlags, point); 
		*/

	}

	// TODO: 鼠标右键谈起，画线结束
	void CtrynView::OnRButtonUp(UINT nFlags, CPoint point)   
	{
		switch(GCurOperState)
		{
		case OPERSTATE_INPUT_IIN:						//造线
			{ 
				AppendLin();
				linePnt=0;
				lastPoint.x=0;
				lastPoint.y=0;
				MakingLine=0;
				tempLins.clear();
				//MessageBox(_T("画线成功"));
				Invalidate();	
			}

		default:
			break;
		}

		CView::OnRButtonUp(nFlags, point);
	}



	//所有点操作状态
	void CtrynView::OnMovePnt()
	{
		// TODO: 在此添加命令处理程序代码
		GCurOperState=OPERSTATE_MOV_PNT;  //设置当前状态为移动
		GPntChanged=1;

	}


	void CtrynView::OnCreatePnt()
	{
		// TODO: 在此添加命令处理程序代码
		GCurOperState=OPERSTATE_INPUT_PNT;  //设置当前状态为造点
		GPntChanged=1;

	}

	void CtrynView::OnDelPnt()
	{
		// TODO: 在此添加命令处理程序代码
		GCurOperState=OPERSTATE_DEL_PNT;  //设置当前状态为删除
		GPntChanged=1;

	}
	void CtrynView::OnZoomin()
	{
		// TODO: 在此添加命令处理程序代码
		GCurOperState=OPERSTATE_ZOOM_IN;  //设置当前状态为放大

	}


	void CtrynView::OnZoomout()
	{
		// TODO: 在此添加命令处理程序代码
		GCurOperState=OPERSTATE_ZOOM_OUT;  //设置当前状态为缩小
	}

	//所有线操作状态
	void CtrynView::OnCreateLin()                  
	{
		// TODO: 在此添加命令处理程序代码
		GCurOperState=OPERSTATE_INPUT_IIN;								  //创建线
		GLinChanged=1;
	}

	void CtrynView::OnMoveLin()
	{
		// TODO: 在此添加命令处理程序代码
		GCurOperState=OPERSTATE_MOVE_IIN	 ;                                //移动线
		GLinChanged=1;
	}


	void CtrynView::OnDelLin()
	{
		// TODO: 在此添加命令处理程序代码
		GCurOperState=OPERSTATE_DEL_IIN	 	 ;                           //删除线
		GLinChanged=1;
	}

	void CtrynView::OnConnectLin()
	{
		// TODO: 在此添加命令处理程序代码
		GCurOperState=OPERSTATE_CONNECT_IIN	 	 ;                           //连接线
		GLinChanged=1;
	}



	void CtrynView::OnWinmove()
	{
		GCurOperState=OPERSTATE_WINDOW_MOVE;                           //窗口移动
	}


	void CtrynView::OnWinreset()
	{
		GCurOperState=OPERSTATE_WINDOW_RESET;                         //窗口重置
	}


	void CtrynView::OnShwodelpnt()							     //显示删除的点
	{
		// TODO: 在此添加命令处理程序代码
		GCurPNTState=1;

	}




	void CtrynView::OnFileNew()
	{
		// TODO: 在此添加命令处理程序代码
		int type;
		GetNewType(type);
		if(type==0)
		{

		}
		 if(type&0x0001)
			NewPnt();		//新建点文件
		 if(type&0x0002)
			NewLin();		//新建线文件
		 if(type&0x0004)
			NewReg();		//新建区文件

	}


	void CtrynView::OnFileOpen()
	{
		// TODO: 在此添加命令处理程序代码
		CString FilePathName;
		char sRead[3];
		CFile mFile;
		if(GetOpenPath(FilePathName)==0)			//判断是否打开了路径
		{
			goto ON_FILE_OPEN_END;
		}
		mFile.Open (FilePathName,CFile::modeRead);
		mFile.Read(sRead,3);
		if(sRead[0]=='P'&&sRead[1]=='N'&&sRead[2]=='T')	//确定该文件是点文件
		{

			strcpy(GPntFName,(LPSTR)(LPCTSTR)FilePathName);
			Pnt_FCT(mFile,FilePathName);
		}
		else if(sRead[0]=='L'&&sRead[1]=='I'&&sRead[2]=='N')	//确定该文件是线文件
		{
			strcpy(GLinFName,(LPSTR)(LPCTSTR)FilePathName);
			Lin_FCT(mFile,FilePathName);

		}
		else if(sRead[0]=='R'&&sRead[1]=='E'&&sRead[2]=='G')	//确定该文件是区文件
		{
			strcpy(GRegFName,(LPSTR)(LPCTSTR)FilePathName);
			Reg_FCT(mFile,FilePathName);
		}
			
		mFile.Close();
		Invalidate();
ON_FILE_OPEN_END:;

	}


	void CtrynView::OnFileSave()
	{
		// TODO: 在此添加命令处理程序代码
		CString FilePathName;
		if(GPntChanged==0&&GLinChanged==0&&GRegChanged==0)
		{
			MessageBox(_T("无修改操作！"));
		}
		if(GPntFCreated==1)			//点文件已被修改
		{
			if(GPntFName[0]!=0)			//是否是已打开的文件
			{
				Pnt_TCF((LPCTSTR)GPntFName,10);
			}
			else
			{
				if(GetPntSavePath(FilePathName)==0)			//判断是否打开了路径
				{
					goto ON_FILE_SAVE_END;
				}
				strcpy(GPntFName,(LPSTR)(LPCTSTR)FilePathName);
				Pnt_TCF(FilePathName,10);

			}
		}
		 if(GLinChanged==1)			//线文件已被修改
		{
			if(GLinFName[0]!=0)			//是否是已打开的文件
			{
				Lin_TCF((LPCTSTR)GLinFName,10);

			}
			else
			{
				if(GetLinSavePath(FilePathName)==0)			//判断是否打开了路径
				{
					goto ON_FILE_SAVE_END;
				}
				strcpy(GLinFName,(LPSTR)(LPCTSTR)FilePathName);
				Lin_TCF(FilePathName,10);

			}
		}
		 if(GRegChanged==1)			//区文件已被修改
		{
			if(GRegFName[0]!=0)			//是否是已打开的文件
			{
				Reg_TCF((LPCTSTR)GRegFName,10);
			}
			else
			{
				if(GetRegSavePath(FilePathName)==0)			//判断是否打开了路径
				{
					goto ON_FILE_SAVE_END;
				}
				strcpy(GRegFName,(LPSTR)(LPCTSTR)FilePathName);
				Reg_TCF(FilePathName,10);

			}
		}
ON_FILE_SAVE_END:;

	}


	void CtrynView::OnFileSaveAs()
	{
		// TODO: 在此添加命令处理程序代码
		CString FilePathName;
		if(GPntChanged==0||GLinChanged==0||GRegChanged==0)		//文件没有被修改
		{
			MessageBox(_T("无修改操作！"));
		}
		else if(GPntFCreated==1)		//点文件被修改
		{
			if(GetPntSaveAsPath(FilePathName)==0)			//判断是否打开了路径
			{
				goto ON_FILE_SAVEAS_END;
			}
			strcpy(GPntFName,(LPSTR)(LPCTSTR)FilePathName);
			Pnt_TCF(FilePathName,10);


		}
		else if(GLinChanged==1)	//线文件被修改
		{
			if(GetLinSaveAsPath(FilePathName)==0)			//判断是否打开了路径
			{
				goto ON_FILE_SAVEAS_END;
			}
			strcpy(GLinFName,(LPSTR)(LPCTSTR)FilePathName);
			Lin_TCF(FilePathName,10);


		}
		else if(GRegChanged==1)	//区文件被修改
		{
			if(GetRegSaveAsPath(FilePathName)==0)			//判断是否打开了路径
			{
				goto ON_FILE_SAVEAS_END;
			}
			strcpy(GLinFName,(LPSTR)(LPCTSTR)FilePathName);
			Reg_TCF(FilePathName,10);
		}
ON_FILE_SAVEAS_END:;

	}



	long CtrynView::ZoomInLBU(POINT myPoint)
	{
		if(!GPntTmpFOpened)
			return (0);
		CRect rect;							//定义一个矩形
		double xOffset,yOffset;				//保存x偏移与y偏移
		double yp;							//计算y方向比例
		double xp;							//计算x方向比例
		double zoom;						//取比例较小为放缩比例
		long len;
		int i;
		POINT temp;
		CClientDC dc(this);
		GetClientRect(&rect);								//获取客户区矩形
		dc.FillRect(&rect,new CBrush(RGB(255,255,255)));			//空白覆盖客户区
		if(zoomstyle==0)
		{
			xOffset=(rect.right-rect.left)/2-myPoint.x;		//点位置与客户区中心点位置计算偏移
			yOffset=(rect.bottom-rect.top)/2-myPoint.y;
			len=GPntTmpFile.GetLength();
			GPntTmpFile.Seek(0,CFile::begin);
			for(i=0;i<len/sizeof(PNT_STRU);i++)   //遍历所有的点,找最近的点
			{
				GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
				if(PNT_STRU.isDel==0)            //画出没被删掉的点
				{
					temp.x=PNT_STRU.x;
					temp.y=PNT_STRU.y;	
					temp.x+=xOffset;
					temp.y+=yOffset;
					temp.x*=1.2;
					temp.y*=1.2;
					CPen  newPen(PS_SOLID,2,RGB(192,192,192));
					dc.MoveTo(temp.x,temp.y-6);
					dc.LineTo(temp.x,temp.y+6);
					dc.MoveTo(temp.x-6,temp.y);
					dc.LineTo(temp.x+6,temp.y);

				}

			}
		}
		else 
		{
			dc.SetROP2(R2_NOTXORPEN);
			dc.Rectangle (m_startPnt.x, m_startPnt.y, myPoint.x, myPoint.y);
			yp=double(rect.bottom-rect.top)/double(myPoint.y-m_startPnt.y);		//矩形左上点与客户区左上点计算偏移
			xp=double(rect.right-rect.left)/double(myPoint.x-m_startPnt.x);
			zoom=((xp>yp)?yp:xp);
			xOffset=0-m_startPnt.x;
			yOffset=0-m_startPnt.y;
			len=GPntTmpFile.GetLength();
			GPntTmpFile.Seek(0,CFile::begin);
			for(i=0;i<len/sizeof(PNT_STRU);i++)   //遍历所有的点,找最近的点
			{
				GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
				if(PNT_STRU.isDel==0)            //画出没被删掉的点
				{
					temp.x=PNT_STRU.x;
					temp.y=PNT_STRU.y;	
					temp.x+=xOffset;				//进行坐标偏移
					temp.y+=yOffset;
					temp.x*=zoom;					//进行坐标放大或缩小
					temp.y*=zoom;
					CPen  newPen(PS_SOLID,2,RGB(192,192,192));
					dc.MoveTo(temp.x,temp.y-6);
					dc.LineTo(temp.x,temp.y+6);
					dc.MoveTo(temp.x-6,temp.y);
					dc.LineTo(temp.x+6,temp.y);

				}

			}


		}
		m_step = 0;
		m_startPnt.x = 0;
		m_startPnt.y = 0;
		m_lastPnt.x = 0;
		m_lastPnt.y = 0;

		return (1);
	}
	long CtrynView::ZoomInMM(POINT myPoint)
	{
		if(!GPntTmpFOpened)
			return (0);
		CClientDC dc(this);
		if(m_step!=0)
		{
			dc.SetROP2(R2_NOTXORPEN);
			if (m_lastPnt.x!=0 && m_lastPnt.y!=0)
				dc.Rectangle(m_startPnt.x, m_startPnt.y, m_lastPnt.x, m_lastPnt.y);

			dc.Rectangle(m_startPnt.x, m_startPnt.y, myPoint.x, myPoint.y);
			m_lastPnt = myPoint;
			zoomstyle=1;
		}

		return (1);
	}
	long CtrynView::ZoomInLBD(POINT myPoint)
	{
		if(!GPntTmpFOpened)
			return (0);
		if(m_step!=0)
		{

		}
		else
		{
			m_step++;
			m_startPnt = myPoint;
		}

		return (1);
	}
	long CtrynView::ZoomOutLBU(POINT myPoint)
	{
		if(!GPntTmpFOpened)
			return (0);
		CRect rect;							//定义一个矩形
		double xOffset,yOffset;				//保存x偏移与y偏移
		double yp;							//计算y方向比例
		double xp;							//计算x方向比例						//取比例较小为放缩比例
		long len;
		int i;
		POINT temp;
		CClientDC dc(this);
		GetClientRect(&rect);
		dc.FillRect(&rect,new CBrush(RGB(255,255,255)));
		xOffset=(rect.right-rect.left)/2-myPoint.x;		//点位置与客户区中心点位置计算偏移
		yOffset=(rect.bottom-rect.top)/2-myPoint.y;
		len=GPntTmpFile.GetLength();
		GPntTmpFile.Seek(0,CFile::begin);
		for(i=0;i<len/sizeof(PNT_STRU);i++)   //遍历所有的点,找最近的点
		{
			GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
			if(PNT_STRU.isDel==0)            //画出没被删掉的点
			{
				temp.x=PNT_STRU.x;
				temp.y=PNT_STRU.y;	
				temp.x+=xOffset;
				temp.y+=yOffset;
				temp.x*=0.8;
				temp.y*=0.8;
				CPen  newPen(PS_SOLID,2,RGB(192,192,192));
				dc.MoveTo(temp.x,temp.y-6);
				dc.LineTo(temp.x,temp.y+6);
				dc.MoveTo(temp.x-6,temp.y);
				dc.LineTo(temp.x+6,temp.y);

			}

		}

		return (1);
	}



	void CtrynView::OnAppExit()
	{
		// TODO: 在此添加命令处理程序代码
		CString FilePathName;
		long value;
		if(GPntChanged==0&&GLinChanged==0&&GRegChanged==0)
		{
			if(GPntTmpFOpened)
				GPntTmpFile.Close();
			if(GLinTmpFOpened)
			{
				GLinTmpFile1.Close();
				GLinTmpFile2.Close();
			}
			if(GRegTmpFOpened)
			{
				GRegTmpFile1.Close();
				GRegTmpFile2.Close();
			}
			exit(0);
		}
		else
		{
			if(GPntChanged==1)
			{
				value=GetPntExitPath(FilePathName);
				if(value==0)
					goto ON_APPEXIT_END;
				if(value==2)
				{
					if(GPntTmpFOpened)
						GPntTmpFile.Close();

					exit(0);
				}
				strcpy(GPntFName,(LPSTR)(LPCTSTR)FilePathName);
				Pnt_TCF(FilePathName,10);
				if(GPntTmpFOpened)
					GPntTmpFile.Close();
				exit(0);
			}
			else if(GLinChanged==1)
			{
				value=GetLinExitPath(FilePathName);
				if(value==0)
					goto ON_APPEXIT_END;
				if(value==2)
				{
					if(GLinTmpFOpened)
					{
						GLinTmpFile1.Close();
						GLinTmpFile2.Close();
					}
					exit(0);
				}
				strcpy(GLinFName,(LPSTR)(LPCTSTR)FilePathName);
				Lin_TCF(FilePathName,10);
				if(GLinTmpFOpened)
				{
					GLinTmpFile1.Close();
					GLinTmpFile2.Close();
				}
				exit(0);
			}
			else if(GRegChanged==1)
			{
				value=GetRegExitPath(FilePathName);
				if(value==0)
					goto ON_APPEXIT_END;
				if(value==2)
				{
					if(GRegTmpFOpened)
					{	
						GRegTmpFile1.Close();
						GRegTmpFile2.Close();
					}
					exit(0);
				}
				strcpy(GLinFName,(LPSTR)(LPCTSTR)FilePathName);
				Reg_TCF(FilePathName,10);
				if(GRegTmpFOpened)
				{
					GRegTmpFile1.Close();
					GRegTmpFile2.Close();
				}
				exit(0);
			}
		}
ON_APPEXIT_END:;
	}










