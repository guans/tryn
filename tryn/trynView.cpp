
// trynView.cpp : CtrynView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

static vector<CPoint> tempLins;    //��ŵ�ǰ��ʱ��������
static vector<CPoint> ConResult;   //������Ӻ�


// CMapEditor10View
IMPLEMENT_DYNCREATE(CtrynView, CView)

	BEGIN_MESSAGE_MAP(CtrynView, CView)
		// ��׼��ӡ����
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

	// CtrynView ����/����

	CtrynView::CtrynView()
	{
		// TODO: �ڴ˴���ӹ������
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
		// TODO: �ڴ˴�ͨ���޸�
		//  CREATESTRUCT cs ���޸Ĵ��������ʽ

		return CView::PreCreateWindow(cs);
	}

	// CtrynView ����

	//�ػ�����
	void CtrynView::OnDraw(CDC* pDC)                
	{
		MakingLine=0;
		CtrynDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;


		if(GCurPNTState==0)
		{
			//����
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

				for(i=0;i<len/sizeof(PNT_STRU);i++)   //�������еĵ�
				{
					GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
					if(PNT_STRU.isDel==0)            //����û��ɾ���ĵ�
					{
						temp.x=PNT_STRU.x;
						temp.y=PNT_STRU.y;	
						DrawPoint(temp);
					}

				}

				//GPntTmpFile.Close();  //�ر��ļ�
			}

		}

		else if(GCurPNTState==1)
		{
			//����
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

				for(i=0;i<len/sizeof(PNT_STRU);i++)   //�������еĵ�
				{
					GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
					if(PNT_STRU.isDel==1)            //����ɾ���ĵ�
					{
						temp.x=PNT_STRU.x;
						temp.y=PNT_STRU.y;	
						DrawPoint(temp);
					}

				}

			//	GPntTmpFile.Close();  //�ر��ļ�
			}


		}
		//����
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

			for(ii=0;ii< ndxlen / linlen;ii++)   //�������е�������
			{
				GLinTmpFile1.Read(&LIN_NDX_STRU,  linlen);
				if(LIN_NDX_STRU.isDel==0)            //����û��ɾ������
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
			//GLinTmpFile2.Close();  //�ر��ļ�
			//GLinTmpFile1.Close();  //�ر��ļ�
		}

		//����ƶ�������
		firstlinnum=0;
		seclinnum=0;
		isfirst=0;
		issecond=0;

		ConResult.clear();
	}


	// CtrynView ��ӡ


	void CtrynView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CtrynView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// Ĭ��׼��
		return DoPreparePrinting(pInfo);
	}

	void CtrynView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
	}

	void CtrynView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӵ�ӡ����е��������
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


	// CtrynView ���

#ifdef _DEBUG
	void CtrynView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CtrynView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CtrynDoc* CtrynView::GetDocument() const // �ǵ��԰汾��������
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtrynDoc)));
		return (CtrynDoc*)m_pDocument;
	}
#endif //_DEBUG


	//�������ܣ��㻭ͼ����ʵ��
	//������������
	long CtrynView::DrawPoint(CPoint tempxy)       //ͼ���ϻ���
	{
		//��ñ����ڻ�ǰ���ͼ
		CClientDC dc(this);
		//�������ģʽ����
		//dc.SetROP2(R2_NOT);
		CPen  newPen(PS_SOLID,2,RGB(192,192,192));
		dc.MoveTo(tempxy.x,tempxy.y-6);
		dc.LineTo(tempxy.x,tempxy.y+6);
		dc.MoveTo(tempxy.x-6,tempxy.y);
		dc.LineTo(tempxy.x+6,tempxy.y);
		::ReleaseDC(m_hWnd,dc);
		return (1);
	}

	//�������ܣ�ͼ�����ƶ���
	//��������ǰ������
	long CtrynView::MovePoint(CPoint tempxy)    
	{
		CPen newpen(PS_SOLID,2,RGB(255,255,255));//���컭�ʶ���
		//��ñ����ڻ�ǰ���ͼ
		CClientDC dc(this);
		CPen *pOldPen=dc.SelectObject(&newpen);//������ѡ��DC��SelectObject����������ǰ����
		//�������ģʽ����
		//dc.SetROP2(R2_NOT);	
		//����Ĩȥһ��Сʮ��
		dc.MoveTo(nowPoint.x,nowPoint.y-6);
		dc.LineTo(nowPoint.x,nowPoint.y+6);
		dc.MoveTo(nowPoint.x-6,nowPoint.y);
		dc.LineTo(nowPoint.x+6,nowPoint.y);
		CPen oldpen(PS_SOLID,2,RGB(192,192,192));	//���컭�ʶ���
		dc.SelectObject(&oldpen);					//������ѡ��DC��SelectObject����������ǰ����
		//���ﻭһ��Сʮ��
		dc.MoveTo(tempxy.x,tempxy.y-6);
		dc.LineTo(tempxy.x,tempxy.y+6);
		dc.MoveTo(tempxy.x-6,tempxy.y);
		dc.LineTo(tempxy.x+6,tempxy.y);
		nowPoint=tempxy;							//�ѵ�ǰ���Ϊ��һ��

		::ReleaseDC(m_hWnd,dc);
		return (1);

	}
	//�������ܣ�ͼ���ϲ�����
	//������������
	long CtrynView::ErasePoint(CPoint tempxy)		 
	{

		CPoint toErase;
		FindNearestPnt(tempxy) ;
		toErase=tempxy;									 //�����ɾ����
		CPen newpen(PS_SOLID,2,RGB(255,255,255));		//���컭�ʶ���
		//��ñ����ڻ�ǰ���ͼ
		CClientDC dc(this);
		CPen *pOldPen=dc.SelectObject(&newpen);			//������ѡ��DC��SelectObject����������ǰ����
		//�������ģʽ����
		//dc.SetROP2(R2_NOT);	
		//����Ĩȥһ��Сʮ��
		dc.MoveTo(toErase.x,toErase.y-6);
		dc.LineTo(toErase.x,toErase.y+6);
		dc.MoveTo(toErase.x-6,toErase.y);
		dc.LineTo(toErase.x+6,toErase.y);

		::ReleaseDC(m_hWnd,dc);
		return 1;

	}

	//�㻭ͼ����ʵ��

	//�������ܣ�ͼ���ϻ���
	//��������ǰ������
	long CtrynView::DrawLine(CPoint tempxy)       
	{
		if(linePnt!=0)
		{
			//��ñ����ڻ�ǰ���ͼ
			CClientDC dc(this);
			//�������ģʽ����
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

	//�������ܣ�ͼ���ϲ�����
	//������Ҫ�����ߵı��
	long CtrynView::EraseLine(long toErase)     //
	{
		int num=0;

		num=toErase;										//�����ɾ����������
		CPen newpen(PS_SOLID,2,RGB(255,255,255));			//���컭�ʶ���
		CClientDC dc(this);									//��ñ����ڻ�ǰ���ͼ
		CPen *pOldPen=dc.SelectObject(&newpen);				//������ѡ��DC��SelectObject����������ǰ����
		//�������ģʽ���� //dc.SetROP2(R2_NOT);	
		//����Ĩȥһ��һ����

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
			GLinTmpFile1.Seek( (toErase -1) * linlen,CFile::begin);  //�ҵ�������ΪtoErase����
			GLinTmpFile1.Read(&LIN_NDX_STRU,  linlen);
			dotnum=LIN_NDX_STRU.dotNum;
			datff=LIN_NDX_STRU.datOff;
			GLinTmpFile2.Seek(datff,CFile::begin);				  //�������ҵ�������ΪtoErase��������

			GLinTmpFile2.Read(&PNT_STRU, plen );				 //�ߵ�һ����
			ptemp.x=PNT_STRU.x;
			ptemp.y=PNT_STRU.y;
			dc.MoveTo(ptemp);
			for(j=1 ; j < dotnum ; j++)						//�ӵ�2���㿪ʼ
			{
				GLinTmpFile2.Read(&PNT_STRU, plen );
				todel.x=PNT_STRU.x;
				todel.y=PNT_STRU.y;
				dc.LineTo(todel);
			}

		}
		return 1;

	}

	//�������ܣ��ļ��в�����
	//������Ҫ�����ߵı��
	long CtrynView::DelLine(long toErase)     
	{
		int num=0;
		num=toErase;									//�����ɾ����������
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
		//�޸������ļ�
		if(1==GLinFCreated)
		{
			ndxlen=GLinTmpFile1.GetLength();
			GLinTmpFile1.Seek( (num -1) * linlen,CFile::begin);
			GLinTmpFile1.Read(&TEM_LIN,linlen);
			TEM_LIN.isDel= 1;
			LIN_NDX_STRU=TEM_LIN;
			GLinTmpFile1.Seek( -linlen,CFile::current);			 //�ҵ�������ΪtoErase����

			GLinTmpFile1.Write(&LIN_NDX_STRU,linlen);

	//		GLinTmpFile1.Close();							//�ر��ļ�

		}
		return 1;
	}

	//�������ܣ�ͼ�����ƶ���
	//�����������
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
			CClientDC dc(this);							//��ñ����ڻ�ǰ���ͼ
			CPen newpen(PS_SOLID,2,RGB(255,255,255));	//���컭�ʶ���
			CPen *pOldPen=dc.SelectObject(&newpen);		//������ѡ��DC��SelectObject����������ǰ����

			long disX=point.x - startPnt.x;				//��������ƫ��
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
			CPen oldpen(PS_SOLID,2,RGB(192,192,192));		//���컭�ʶ���
			dc.SelectObject(&oldpen);						//������ѡ��DC��SelectObject����������ǰ����

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
	//�������ܣ��洢ѡ������
	//������Ҫ�洢���ߺ�
	long CtrynView::SelectLin(int num)     //�洢ѡ�����ߵ�
	{	
		CPen newpen(PS_SOLID,2,RGB(255,255,255));	//���컭�ʶ���
		CClientDC dc(this);							//��ñ����ڻ�ǰ���ͼ
		CPen *pOldPen=dc.SelectObject(&newpen);		//������ѡ��DC��SelectObject����������ǰ����
		//�������ģʽ���� //dc.SetROP2(R2_NOT);	
		//����Ĩȥһ��һ����
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
				tempLins.push_back(todel);
			}

		}

		linNum=dotnum;
		return 1;


	}

	//�������ܣ�д�ƶ������
	//������������
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
		//�޸������ļ�
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

		//	GLinTmpFile1.Close();  //�ر��ļ�
		//	GLinTmpFile2.Close();
		}
		return 1;


	}


	//�������ܣ����ļ���д������������
	//������
	long CtrynView::AppendLin()  
	{
		int lendata;
	//	CFile linedata;
		//int lenofp = sizeof(PNT_STRU);
		
		lendata=GLinTmpFile2.GetLength();
		GLinTmpFile2.Seek(lendata,CFile::begin);     //���ݴ��ļ�ĩβд

		GLinNum++,GLinLNum++;
		int pnum= tempLins.size() ;
		int lenndx;
		//CFile linendx;
		int lenofl=sizeof(LIN_NDX_STRU);        //�����ṹ����
		int lenofp = sizeof(PNT_STRU);           //��ṹ����
		

		lenndx=GLinTmpFile1.GetLength();
		GLinTmpFile1.Seek(lenndx,CFile::begin);     //�������ļ�ĩβд

		//д��ǰ������
		LIN_NDX_STRU.color=0;
		LIN_NDX_STRU.datOff= GLinTmpFile2.GetLength();       //���ݴ洢��ʼλ�� һ����ṹ����*�����*�ߺ�
		LIN_NDX_STRU.dotNum=pnum;
		LIN_NDX_STRU.isDel=0;
		LIN_NDX_STRU.pattern=0;
		GLinTmpFile1.Write(&LIN_NDX_STRU,lenofl);  //���ṹ��д���ļ�

		int i=0;
		for(i=0;i < pnum ; i++)
		{
			TEM_PNT.color=0;
			TEM_PNT.isDel=0;
			TEM_PNT.pattern=0;
			TEM_PNT.x=tempLins[i].x;
			TEM_PNT.y=tempLins[i].y;
			GLinTmpFile2.Write(&TEM_PNT,lenofp);  //���ݽṹ��д���ļ�

		}
	//	linendx.Close();
	//	GLinTmpFile2.Close();
		return 1;
	}

	//�������ܣ�����������
	//�������ߺ�1 2
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
		else														//��ʼ����
		{
			if(Lin1[lin1num -1].x < Lin2[0].x)						//��һ���ߵ�β �ӵڶ���ͷ
			{
				for(i=0;i< lin1num;i++)
					ConResult.push_back(Lin1[i]);

				for(i=0;i< lin2num;i++)
				{
					ConResult.push_back(Lin2[i]);
				}
			}
			else if(Lin1[lin1num-1].x > Lin2[0].x)				//��һ��β �� �ڶ���β
			{
				for(i=0;i< lin1num;i++)
					ConResult.push_back(Lin1[i]);
				for(i= lin2num-1;i>=0;i--)
				{
					ConResult.push_back(Lin2[i]);
				}
			}
			else if(Lin1[0].x < Lin2[lin2num-1].x)				//��һ��ͷ �ӵڶ���ͷ
			{

			}
			else if(Lin1[0].x > Lin2[lin2num-1].x)			   //��һ�� ͷ �ӵڶ��� β
			{

			}
		}

		EraseLine(lin1);									//����������
		EraseLine(lin2);
		DelLine(lin1);								     //�ļ���ɾ��������
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
		CClientDC dc(this);							//��ñ����ڻ�ǰ���ͼ
		CPen newpen(PS_SOLID,2,RGB(192,192,192));	//���컭�ʶ���
		CPen *pOldPen=dc.SelectObject(&newpen);		//������ѡ��DC��SelectObject����������ǰ����
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
		//linedata.Open (_T("E:\\���\\���ڱ���\\MapEditor\\tempfile\\GLinTmpFFile2.lin"),CFile::modeReadWrite/*|CFile::shareDenyWrite*/);
		lendata=GLinTmpFile2.GetLength();
		GLinTmpFile2.Seek(lendata,CFile::begin);     //���ݴ��ļ�ĩβд

		int lenndx;
		//CFile linendx;
		int lenofl=sizeof(LIN_NDX_STRU);        //�����ṹ����
		int lenofp = sizeof(PNT_STRU);           //��ṹ����
	//	linendx.Open (_T("E:\\���\\���ڱ���\\MapEditor\\tempfile\\GLinTmpFFile1.lin"),CFile::modeReadWrite/*|CFile::shareDenyWrite*/);

		lenndx=GLinTmpFile1.GetLength();
		GLinTmpFile1.Seek(lenndx,CFile::begin);     //�������ļ�ĩβд

		//д��ǰ������
		LIN_NDX_STRU.color=0;
		LIN_NDX_STRU.datOff= GLinTmpFile2.GetLength();       //���ݴ洢��ʼλ�� һ����ṹ����*�����*�ߺ�
		LIN_NDX_STRU.dotNum=linnum;
		LIN_NDX_STRU.isDel=0;
		LIN_NDX_STRU.pattern=0;
		GLinTmpFile1.Write(&LIN_NDX_STRU,lenofl);				//���ṹ��д���ļ�

		int i=0;
		for(i=0;i < linnum ; i++)
		{
			TEM_PNT.color=0;
			TEM_PNT.isDel=0;
			TEM_PNT.pattern=0;
			TEM_PNT.x=ConResult[i].x;
			TEM_PNT.y=ConResult[i].y;
			GLinTmpFile2.Write(&TEM_PNT,lenofp);				//���ݽṹ��д���ļ�

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
		//�޸������ļ�
		if(1==GLinFCreated)
		{
			datalen=GLinTmpFile2.GetLength();
			ndxlen=GLinTmpFile1.GetLength();

			GLinTmpFile1.Seek( (num -1) * linlen,CFile::begin);  //�ҵ�������ΪtoErase����
			GLinTmpFile1.Read(&LIN_NDX_STRU,  linlen);
			dotnum=LIN_NDX_STRU.dotNum;
			datff=LIN_NDX_STRU.datOff;
			GLinTmpFile2.Seek(datff,CFile::begin);           //�������ҵ�������ΪtoErase��������

			CClientDC dc(this);							//��ñ����ڻ�ǰ���ͼ
			CPen newpen(PS_SOLID,2,RGB(192,0,0));	//���컭�ʶ���
			CPen *pOldPen=dc.SelectObject(&newpen);		//������ѡ��DC��SelectObject����������ǰ����


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

			//linendx.Close();  //�ر��ļ�
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
		xOffset=startPnt.x-xy.x;							//���x�����ϵ�ƫ��
		yOffset=startPnt.y-xy.y;							//���y�����ϵ�ƫ��
		GxOffset+=xOffset/GZoom;
		GyOffset+=yOffset/GZoom;
		GetClientRect(&rect);									//��ȡ�ͻ�������
		dc.FillRect(&rect,new CBrush(RGB(255,255,255)));			//�հ׸��ǿͻ���
		if(GPntTmpFOpened==1&&GPntNum!=0)
		{
			GPntTmpFile.Seek(0,CFile::begin);
			for(i=0;i<GPntNum;i++)							 //�������еĵ�
			{
				GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
				if(PNT_STRU.isDel==0)				  //����û��ɾ���ĵ�
				{
					temp.x=PNT_STRU.x;
					temp.y=PNT_STRU.y;	
					DotDPtoVP(temp);						//ת������
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


	//����ͼ����ʵ��

	// CtrynView ��Ϣ�������
	//����������
	void CtrynView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

		switch(GCurOperState)
		{
			//case OPERSTATE_INPUT_PNT:						//����
			//	break;
			//case OPERSTATE_DEL_PNT:                     //ɾ����
			//	break;
		case OPERSTATE_MOV_PNT:								//�ƶ���
			{
				nowPoint=point;								//�洢��ǰ��Ϊǰһ��
				CPoint ptMove;
				FindNearestPnt(point);
				ptMove=point;
				toMove=point;
				CPen newpen(PS_SOLID,2,RGB(255,0,0));			//���컭�ʶ���
				CClientDC dc(this);								//��ñ����ڻ�ǰ���ͼ
				CPen *pOldPen=dc.SelectObject(&newpen);			//������ѡ��DC��SelectObject����������ǰ����
				//�������Ҫ�ƶ��ĵ�
				dc.MoveTo(ptMove.x,ptMove.y-6);
				dc.LineTo(ptMove.x,ptMove.y+6);
				dc.MoveTo(ptMove.x-6,ptMove.y);
				dc.LineTo(ptMove.x+6,ptMove.y);
				::ReleaseDC(m_hWnd,dc);
			}
			break;
		case OPERSTATE_MOVE_IIN:						 //���ò���״̬Ϊ�ƶ���
			{
				int num;
				startPnt=point;							//�洢��ǰ��Ϊǰһ��
				FindNearLine(point,num);
				SelectLin(num);
				EraseLine(num);
				linToMove=num;                           //����Ҫ�ƶ����ߺ�
				step=1;
			}
			break;
		case OPERSTATE_ZOOM_IN:							 //���ò���״̬Ϊ�Ŵ�
			ZoomInLBD(point);
			break;
		case OPERSTATE_WINDOW_MOVE:						//���ò���״̬Ϊ�����ƶ�
			WindowMoveLBD(point);
			break;
		default:
			
			break;

		}
		CView::OnLButtonDown(nFlags, point);
	}

	//����������
	void CtrynView::OnLButtonUp(UINT nFlags, CPoint point)  //
	{
		switch(GCurOperState)
		{
		case OPERSTATE_INPUT_PNT:						//����
			AppendPnt(point);							//���¼ӵĵ�д����ʱ�ļ�
			DrawPoint(point);							//������ǰ�ĵ�
			break;	
		case OPERSTATE_DEL_PNT:							//ɾ����
			DeletePnt(point);							//�ļ���ɾ����
			ErasePoint(point);							//ͼ����ɾ����
			break;
		case OPERSTATE_MOV_PNT:							//�ƶ���
			MovePnt(point,toMove);						//�ļ����ƶ���   (�ƶ����ĵ㣬Ҫ�ƶ��ĵ�)
			Invalidate();								//ˢ��ͼ��
			break;
		case OPERSTATE_ZOOM_IN:							//���ò���״̬Ϊ�Ŵ�
			ZoomInLBU(point);
			break;
		case OPERSTATE_ZOOM_OUT:						//���ò���״̬Ϊ��С
			ZoomOutLBU(point);
			break;	
		case OPERSTATE_INPUT_IIN:						 //����
			{
				nowPoint=point;							 //�洢ǰһ���ڵ� 	
				tempLins.push_back(point);				//��ǰ�����������
				MakingLine=1;							// �����������״̬
				DrawLine(point);     					//������ǰ�ĵ�
				break;
			}
		case OPERSTATE_DEL_IIN:							//ɾ����
			{
				CString str;
				int LineNum;					
				FindNearLine(point,LineNum);
				EraseLine(LineNum);						//ͼ����ɾ�����LineNum����
				DelLine(LineNum);
				//str.Format("%d",LineNum);
				//MessageBox(_T(str));
				break;
			}
		case OPERSTATE_MOVE_IIN:								 //�ƶ���
			MoveLinLBU(point);
			tempLins.clear();
			Invalidate();										//ˢ��ͼ��
			break;		
		case OPERSTATE_WINDOW_MOVE:								//�����ƶ�
			WindowMoveLBU(point);
			break;
		case OPERSTATE_CONNECT_IIN:								//������
			{
				int firstnum;
				int secnum;
				if(isfirst==0)									//ѡ�е�һ����
				{
					FindNearLine(point,firstnum);
					firstlinnum=firstnum;						//�����һ���ߺ�
					isfirst=1;
					DrawConLine(firstnum);
					CString sMousePos;
					CString nowstr="�Ѿ�ѡ���һ���ߣ���ѡ��ڶ���";
					sMousePos.Format(_T(" %s "),nowstr);
					AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowText(sMousePos);
				}
				else if(issecond==0)
				{
					FindNearLine(point,secnum);
					if(firstlinnum!=secnum)
					{
						seclinnum=secnum;							//����ڶ����ߺ�
						issecond=1;
						DrawConLine(secnum);
					}
				}
				else if(firstlinnum!=0 &&seclinnum!=0 ) ConnectLins(firstlinnum,seclinnum);        //����������

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
		if(nFlags==MK_LBUTTON)								//��ǰ�������Ƿ���
		{
			switch(GCurOperState)
			{
			case OPERSTATE_MOV_PNT:							//�ƶ���
				MovePoint(point);
				break;
			case OPERSTATE_ZOOM_IN:							//���ò���״̬Ϊ�Ŵ�
				ZoomInMM(point);
				break;
			case OPERSTATE_MOVE_IIN:						  //�ƶ���
				MoveLin(point);
				break;
			default:
				break;
			}
		}
		else
			switch(GCurOperState)
		{

			case OPERSTATE_INPUT_IIN:									//���ò���״̬Ϊ����
				{
					if(MakingLine==1) {
						DrawPoint(point);
						CPen newpen(PS_SOLID,2,RGB(255,0,0));			//���컭�ʶ���
						CPen oldpen(PS_SOLID,2,RGB(255,255,255));		//���컭�ʶ���

						CClientDC dc(this);								//��ñ����ڻ�ǰ���ͼ
						//dc.SetROP2(R2_NOT);
						CPen *pOldPen=dc.SelectObject(&newpen);			//������ѡ��DC��SelectObject����������ǰ����
						//�������Ҫ�ƶ��ĵ�
						dc.MoveTo(lastPoint.x,lastPoint.y);
						dc.LineTo(point.x,point.y);

						dc.SelectObject(&oldpen);						//������ѡ��DC��SelectObject����������ǰ����
						//�������Ҫ�ƶ��ĵ�
						dc.MoveTo(lastPoint.x,lastPoint.y);
						dc.LineTo(templastPoint.x,templastPoint.y);
						//����ɾ����һ����
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

		// TODO:��ʾ������ 
		/*	CString sMousePos;
		sMousePos.Format(_T("x=%d,y=%d"),point.x,point.y);
		AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowText(sMousePos);
		CView::OnMouseMove(nFlags, point); 
		*/

	}

	// TODO: ����Ҽ�̸�𣬻��߽���
	void CtrynView::OnRButtonUp(UINT nFlags, CPoint point)   
	{
		switch(GCurOperState)
		{
		case OPERSTATE_INPUT_IIN:						//����
			{ 
				AppendLin();
				linePnt=0;
				lastPoint.x=0;
				lastPoint.y=0;
				MakingLine=0;
				tempLins.clear();
				//MessageBox(_T("���߳ɹ�"));
				Invalidate();	
			}

		default:
			break;
		}

		CView::OnRButtonUp(nFlags, point);
	}



	//���е����״̬
	void CtrynView::OnMovePnt()
	{
		// TODO: �ڴ���������������
		GCurOperState=OPERSTATE_MOV_PNT;  //���õ�ǰ״̬Ϊ�ƶ�
		GPntChanged=1;

	}


	void CtrynView::OnCreatePnt()
	{
		// TODO: �ڴ���������������
		GCurOperState=OPERSTATE_INPUT_PNT;  //���õ�ǰ״̬Ϊ���
		GPntChanged=1;

	}

	void CtrynView::OnDelPnt()
	{
		// TODO: �ڴ���������������
		GCurOperState=OPERSTATE_DEL_PNT;  //���õ�ǰ״̬Ϊɾ��
		GPntChanged=1;

	}
	void CtrynView::OnZoomin()
	{
		// TODO: �ڴ���������������
		GCurOperState=OPERSTATE_ZOOM_IN;  //���õ�ǰ״̬Ϊ�Ŵ�

	}


	void CtrynView::OnZoomout()
	{
		// TODO: �ڴ���������������
		GCurOperState=OPERSTATE_ZOOM_OUT;  //���õ�ǰ״̬Ϊ��С
	}

	//�����߲���״̬
	void CtrynView::OnCreateLin()                  
	{
		// TODO: �ڴ���������������
		GCurOperState=OPERSTATE_INPUT_IIN;								  //������
		GLinChanged=1;
	}

	void CtrynView::OnMoveLin()
	{
		// TODO: �ڴ���������������
		GCurOperState=OPERSTATE_MOVE_IIN	 ;                                //�ƶ���
		GLinChanged=1;
	}


	void CtrynView::OnDelLin()
	{
		// TODO: �ڴ���������������
		GCurOperState=OPERSTATE_DEL_IIN	 	 ;                           //ɾ����
		GLinChanged=1;
	}

	void CtrynView::OnConnectLin()
	{
		// TODO: �ڴ���������������
		GCurOperState=OPERSTATE_CONNECT_IIN	 	 ;                           //������
		GLinChanged=1;
	}



	void CtrynView::OnWinmove()
	{
		GCurOperState=OPERSTATE_WINDOW_MOVE;                           //�����ƶ�
	}


	void CtrynView::OnWinreset()
	{
		GCurOperState=OPERSTATE_WINDOW_RESET;                         //��������
	}


	void CtrynView::OnShwodelpnt()							     //��ʾɾ���ĵ�
	{
		// TODO: �ڴ���������������
		GCurPNTState=1;

	}




	void CtrynView::OnFileNew()
	{
		// TODO: �ڴ���������������
		int type;
		GetNewType(type);
		if(type==0)
		{

		}
		 if(type&0x0001)
			NewPnt();		//�½����ļ�
		 if(type&0x0002)
			NewLin();		//�½����ļ�
		 if(type&0x0004)
			NewReg();		//�½����ļ�

	}


	void CtrynView::OnFileOpen()
	{
		// TODO: �ڴ���������������
		CString FilePathName;
		char sRead[3];
		CFile mFile;
		if(GetOpenPath(FilePathName)==0)			//�ж��Ƿ����·��
		{
			goto ON_FILE_OPEN_END;
		}
		mFile.Open (FilePathName,CFile::modeRead);
		mFile.Read(sRead,3);
		if(sRead[0]=='P'&&sRead[1]=='N'&&sRead[2]=='T')	//ȷ�����ļ��ǵ��ļ�
		{

			strcpy(GPntFName,(LPSTR)(LPCTSTR)FilePathName);
			Pnt_FCT(mFile,FilePathName);
		}
		else if(sRead[0]=='L'&&sRead[1]=='I'&&sRead[2]=='N')	//ȷ�����ļ������ļ�
		{
			strcpy(GLinFName,(LPSTR)(LPCTSTR)FilePathName);
			Lin_FCT(mFile,FilePathName);

		}
		else if(sRead[0]=='R'&&sRead[1]=='E'&&sRead[2]=='G')	//ȷ�����ļ������ļ�
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
		// TODO: �ڴ���������������
		CString FilePathName;
		if(GPntChanged==0&&GLinChanged==0&&GRegChanged==0)
		{
			MessageBox(_T("���޸Ĳ�����"));
		}
		if(GPntFCreated==1)			//���ļ��ѱ��޸�
		{
			if(GPntFName[0]!=0)			//�Ƿ����Ѵ򿪵��ļ�
			{
				Pnt_TCF((LPCTSTR)GPntFName,10);
			}
			else
			{
				if(GetPntSavePath(FilePathName)==0)			//�ж��Ƿ����·��
				{
					goto ON_FILE_SAVE_END;
				}
				strcpy(GPntFName,(LPSTR)(LPCTSTR)FilePathName);
				Pnt_TCF(FilePathName,10);

			}
		}
		 if(GLinChanged==1)			//���ļ��ѱ��޸�
		{
			if(GLinFName[0]!=0)			//�Ƿ����Ѵ򿪵��ļ�
			{
				Lin_TCF((LPCTSTR)GLinFName,10);

			}
			else
			{
				if(GetLinSavePath(FilePathName)==0)			//�ж��Ƿ����·��
				{
					goto ON_FILE_SAVE_END;
				}
				strcpy(GLinFName,(LPSTR)(LPCTSTR)FilePathName);
				Lin_TCF(FilePathName,10);

			}
		}
		 if(GRegChanged==1)			//���ļ��ѱ��޸�
		{
			if(GRegFName[0]!=0)			//�Ƿ����Ѵ򿪵��ļ�
			{
				Reg_TCF((LPCTSTR)GRegFName,10);
			}
			else
			{
				if(GetRegSavePath(FilePathName)==0)			//�ж��Ƿ����·��
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
		// TODO: �ڴ���������������
		CString FilePathName;
		if(GPntChanged==0||GLinChanged==0||GRegChanged==0)		//�ļ�û�б��޸�
		{
			MessageBox(_T("���޸Ĳ�����"));
		}
		else if(GPntFCreated==1)		//���ļ����޸�
		{
			if(GetPntSaveAsPath(FilePathName)==0)			//�ж��Ƿ����·��
			{
				goto ON_FILE_SAVEAS_END;
			}
			strcpy(GPntFName,(LPSTR)(LPCTSTR)FilePathName);
			Pnt_TCF(FilePathName,10);


		}
		else if(GLinChanged==1)	//���ļ����޸�
		{
			if(GetLinSaveAsPath(FilePathName)==0)			//�ж��Ƿ����·��
			{
				goto ON_FILE_SAVEAS_END;
			}
			strcpy(GLinFName,(LPSTR)(LPCTSTR)FilePathName);
			Lin_TCF(FilePathName,10);


		}
		else if(GRegChanged==1)	//���ļ����޸�
		{
			if(GetRegSaveAsPath(FilePathName)==0)			//�ж��Ƿ����·��
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
		CRect rect;							//����һ������
		double xOffset,yOffset;				//����xƫ����yƫ��
		double yp;							//����y�������
		double xp;							//����x�������
		double zoom;						//ȡ������СΪ��������
		long len;
		int i;
		POINT temp;
		CClientDC dc(this);
		GetClientRect(&rect);								//��ȡ�ͻ�������
		dc.FillRect(&rect,new CBrush(RGB(255,255,255)));			//�հ׸��ǿͻ���
		if(zoomstyle==0)
		{
			xOffset=(rect.right-rect.left)/2-myPoint.x;		//��λ����ͻ������ĵ�λ�ü���ƫ��
			yOffset=(rect.bottom-rect.top)/2-myPoint.y;
			len=GPntTmpFile.GetLength();
			GPntTmpFile.Seek(0,CFile::begin);
			for(i=0;i<len/sizeof(PNT_STRU);i++)   //�������еĵ�,������ĵ�
			{
				GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
				if(PNT_STRU.isDel==0)            //����û��ɾ���ĵ�
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
			yp=double(rect.bottom-rect.top)/double(myPoint.y-m_startPnt.y);		//�������ϵ���ͻ������ϵ����ƫ��
			xp=double(rect.right-rect.left)/double(myPoint.x-m_startPnt.x);
			zoom=((xp>yp)?yp:xp);
			xOffset=0-m_startPnt.x;
			yOffset=0-m_startPnt.y;
			len=GPntTmpFile.GetLength();
			GPntTmpFile.Seek(0,CFile::begin);
			for(i=0;i<len/sizeof(PNT_STRU);i++)   //�������еĵ�,������ĵ�
			{
				GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
				if(PNT_STRU.isDel==0)            //����û��ɾ���ĵ�
				{
					temp.x=PNT_STRU.x;
					temp.y=PNT_STRU.y;	
					temp.x+=xOffset;				//��������ƫ��
					temp.y+=yOffset;
					temp.x*=zoom;					//��������Ŵ����С
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
		CRect rect;							//����һ������
		double xOffset,yOffset;				//����xƫ����yƫ��
		double yp;							//����y�������
		double xp;							//����x�������						//ȡ������СΪ��������
		long len;
		int i;
		POINT temp;
		CClientDC dc(this);
		GetClientRect(&rect);
		dc.FillRect(&rect,new CBrush(RGB(255,255,255)));
		xOffset=(rect.right-rect.left)/2-myPoint.x;		//��λ����ͻ������ĵ�λ�ü���ƫ��
		yOffset=(rect.bottom-rect.top)/2-myPoint.y;
		len=GPntTmpFile.GetLength();
		GPntTmpFile.Seek(0,CFile::begin);
		for(i=0;i<len/sizeof(PNT_STRU);i++)   //�������еĵ�,������ĵ�
		{
			GPntTmpFile.Read(&PNT_STRU, sizeof( PNT_STRU ));
			if(PNT_STRU.isDel==0)            //����û��ɾ���ĵ�
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
		// TODO: �ڴ���������������
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










