
// trynView.h : CtrynView ��Ľӿ�
//

#pragma once
#include<vector>

class CtrynView : public CView
{
protected: // �������л�����
	CtrynView();
	DECLARE_DYNCREATE(CtrynView)

// ����
public:
	CtrynDoc* GetDocument() const;

// ����
public:
	short	m_step;
	POINT	m_startPnt;
	POINT	m_lastPnt;
	int zoomstyle;
	long ZoomInLBU(POINT myPoint);
	long ZoomInMM(POINT myPoint);
	long ZoomInLBD(POINT myPoint);
	long ZoomOutLBU(POINT myPoint);


// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CtrynView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	

public:       

	//���������Ӧ����
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


	 //////ʵ�����л�ͼ�����ķ�װ

	 long DrawPoint(CPoint tempxy);  //���㺯��
	 long MovePoint(CPoint tempxy);  //�ƶ��㺯��
	 long ErasePoint(CPoint tempxy); // ɾ����

	  long DrawLine(CPoint tempxy);  //���ߺ���

	 afx_msg void OnZoomin();
	 afx_msg void OnZoomout();
	 afx_msg void OnCreateLin();
	 afx_msg void OnMoveLin();
	 afx_msg void OnDelLin();


public:  
	//��������
	 CPoint nowPoint; // ��־��һ�����
	 CPoint toMove; // ��Ҫ�ƶ��������
	 int isLeftBDown; //����Ƿ���

	 
	
	
	
	//��������
	        int MakingLine;
	        CPoint firstPoint; //
		    CPoint lastPoint; //����ʱ��һ�����

		    CPoint templastPoint; //����ʱ��һ�����
	      int linePnt;      // ��ʱ�ߵĵ����

		
		  long AppendLin();
		  long EraseLine(long toErase);
		  long DelLine(long toErase);
		  long MoveLin(CPoint point);
		  long SelectLin(int num);			//�洢��ǰҪ�ƶ�����
		  long MoveLinLBU(CPoint point);	//��Ӧ�ƶ���굯��
		  POINT linPnt[500];				//���Ҫ�ƶ��ߵĵ�
		
		  CPoint startPnt;					 //����ƶ��߿�ʼ��

		  int step;							//�ƶ��ߵ�ǰ״̬
		  int linNum;                       //�ƶ����м�����
		  int linToMove;
		  
		  //���ں���
		  long WindowMoveLBD(POINT xy);	
		  long WindowMoveLBU(POINT xy);	
		  afx_msg void OnWinmove();
		  afx_msg void OnWinreset();
		  afx_msg void OnConnectLin();

		  //������
		  int firstlinnum;          
		  int seclinnum;
		  int isfirst;
		  int issecond;
		  long ConnectLins(int lin1,int lin2);	
		  long DrawConLine();						 //�����Ӻ����
		  long WriteConLine();						 //д���Ӻ����
		  long DrawConLine(int num);				//����ĳ����
		  

		  afx_msg void OnShwodelpnt();
};

#ifndef _DEBUG  // trynView.cpp �еĵ��԰汾
inline CtrynDoc* CtrynView::GetDocument() const
   { return reinterpret_cast<CtrynDoc*>(m_pDocument); }
#endif

