
// trynView.h : CtrynView 类的接口
//

#pragma once
#include<vector>

class CtrynView : public CView
{
protected: // 仅从序列化创建
	CtrynView();
	DECLARE_DYNCREATE(CtrynView)

// 特性
public:
	CtrynDoc* GetDocument() const;

// 操作
public:
	short	m_step;
	POINT	m_startPnt;
	POINT	m_lastPnt;
	int zoomstyle;
	long ZoomInLBU(POINT myPoint);
	long ZoomInMM(POINT myPoint);
	long ZoomInLBD(POINT myPoint);
	long ZoomOutLBU(POINT myPoint);


// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CtrynView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	

public:       

	//所有鼠标响应函数
	 afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	 afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	 afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	 afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	
	 afx_msg void OnCreatePnt();
	 afx_msg void OnDelPnt();
	 afx_msg void OnMovePnt();
	
	 afx_msg void OnFileNew();
	 afx_msg void OnFileOpen();
	 afx_msg void OnFileSave();
	 afx_msg void OnFileSaveAs();
	 afx_msg void OnAppExit();


	 //////实现所有画图函数的封装

	 long DrawPoint(CPoint tempxy);  //画点函数
	 long MovePoint(CPoint tempxy);  //移动点函数
	 long ErasePoint(CPoint tempxy); // 删除点

	  long DrawLine(CPoint tempxy);  //画线函数

	 afx_msg void OnZoomin();
	 afx_msg void OnZoomout();
	 afx_msg void OnCreateLin();
	 afx_msg void OnMoveLin();
	 afx_msg void OnDelLin();


public:  
	//画点数据
	 CPoint nowPoint; // 标志上一坐标点
	 CPoint toMove; // 需要移动点的坐标
	 int isLeftBDown; //左键是否按下

	 
	
	
	
	//画线数据
	        int MakingLine;
	        CPoint firstPoint; //
		    CPoint lastPoint; //画线时上一坐标点

		    CPoint templastPoint; //画线时上一坐标点
	      int linePnt;      // 临时线的点个数

		
		  long AppendLin();
		  long EraseLine(long toErase);
		  long DelLine(long toErase);
		  long MoveLin(CPoint point);
		  long SelectLin(int num);			//存储当前要移动的线
		  long MoveLinLBU(CPoint point);	//响应移动鼠标弹起
		  POINT linPnt[500];				//存放要移动线的点
		
		  CPoint startPnt;					 //存放移动线开始点

		  int step;							//移动线当前状态
		  int linNum;                       //移动线有几个点
		  int linToMove;
		  
		  //窗口函数
		  long WindowMoveLBD(POINT xy);	
		  long WindowMoveLBU(POINT xy);	
		  afx_msg void OnWinmove();
		  afx_msg void OnWinreset();
		  afx_msg void OnConnectLin();

		  //连接线
		  int firstlinnum;          
		  int seclinnum;
		  int isfirst;
		  int issecond;
		  long ConnectLins(int lin1,int lin2);	
		  long DrawConLine();						 //画连接后的线
		  long WriteConLine();						 //写连接后的线
		  long DrawConLine(int num);				//标亮某条线
		  

		  afx_msg void OnShwodelpnt();
};

#ifndef _DEBUG  // trynView.cpp 中的调试版本
inline CtrynDoc* CtrynView::GetDocument() const
   { return reinterpret_cast<CtrynDoc*>(m_pDocument); }
#endif

