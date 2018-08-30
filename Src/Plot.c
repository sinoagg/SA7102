//==============================================================================
//
// Title:		Plot.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 17:35:20 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

//#include "Plot.h"
#include <userint.h>
#include "Graph.h"
#include "GraphDisp.h"
#include "LoadPanel.h"
#include "Environment.h"
#include "SetPanelCB.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
int graph2tempclr;
int graph2humclr; 
int graph2preclr; 
int smu1Clr;
int smu2Clr;
//==============================================================================
// Global functions
int PlotCurve(Graph_TypeDef* pGraph, int graphDispPanel, int control)
{
	int numOfDotsToPlot=pGraph->pCurveArray->numOfDotsToPlot;							//��ֹ�ж϶�ȥд��������� 
	int numOfDotsToPlot2=(pGraph->pCurveArray + 1)->numOfDotsToPlot;							//��ֹ�ж϶�ȥд���������  
	if(Graph.pCurveArray->numOfPlotDots >=1 )//�� �ڶ��� ��
	{
			if(numOfDotsToPlot>0)																
			{
				SetCtrlVal (hResultDispPanel, SAMPLE_VD, *(Graph.pCurveArray->pDotX-1) );
				SetCtrlVal (hResultDispPanel, SAMPLE_VG, *(Graph.pCurveArray->pDotY-1));
				pGraph->plotHandle=PlotXY(graphDispPanel, control, pGraph->pCurveArray->pDotXPlot-1, pGraph->pCurveArray->pDotYPlot-1, numOfDotsToPlot+1, 
										  VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, smu1Clr);
				pGraph->pCurveArray->numOfPlotDots+=numOfDotsToPlot;		//��ͼ�ܵ�������
				pGraph->pCurveArray->pDotXPlot+=numOfDotsToPlot;			//��ͼ��X����ָ�����
				pGraph->pCurveArray->pDotYPlot+=numOfDotsToPlot;			//��ͼ��Y����ָ�����
				pGraph->pCurveArray->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
			}
    }
	else //����һ����
	{
			if(numOfDotsToPlot>0)																//�������Ҫ��ͼ�ĵ�
			{																			//pDotXPlot						//pDotYPlot	   numOfDotsToPlot

				pGraph->plotHandle=PlotXY(graphDispPanel, control, pGraph->pCurveArray->pDotXPlot, pGraph->pCurveArray->pDotYPlot, numOfDotsToPlot, 
										  VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, smu1Clr);
			//	SetCtrlVal(graphDispPanel, GRAPHDISP_NUMERIC ,pGraph->pCurveArray->pDotXHead[pGraph->pCurveArray->numOfPlotDots ); 
			//	SetCtrlVal(graphDispPanel, SETGRAPHDISP_NUMERIC ,pGraph->pCurveArray->pDotXHead[pGraph->pCurveArray->numOfPlotDots ); 

				pGraph->pCurveArray->numOfPlotDots+=numOfDotsToPlot;		//��ͼ�ܵ�������
				pGraph->pCurveArray->pDotXPlot+=numOfDotsToPlot;			//��ͼ��X����ָ�����
				pGraph->pCurveArray->pDotYPlot+=numOfDotsToPlot;			//��ͼ��Y����ָ�����
				pGraph->pCurveArray->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.

			}
	}
	
	if((Graph.pCurveArray+1)->numOfPlotDots >=1 ) 
	{
		if(numOfDotsToPlot2>0)
		{
				pGraph->plotHandle=PlotXY(graphDispPanel, control, (pGraph->pCurveArray + 1)->pDotXPlot-1, (pGraph->pCurveArray + 1)->pDotYPlot-1, numOfDotsToPlot2+1, 
										  VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, smu2Clr);
			//	SetCtrlVal(graphDispPanel, GRAPHDISP_NUMERIC ,pGraph->pCurveArray->pDotXHead[pGraph->pCurveArray->numOfPlotDots ); 
				(pGraph->pCurveArray + 1)->numOfPlotDots+=numOfDotsToPlot2;		//��ͼ�ܵ�������
				(pGraph->pCurveArray + 1)->pDotXPlot+=numOfDotsToPlot2;			//��ͼ��X����ָ�����
				(pGraph->pCurveArray + 1)->pDotYPlot+=numOfDotsToPlot2;			//��ͼ��Y����ָ�����
				(pGraph->pCurveArray + 1)->numOfDotsToPlot-=numOfDotsToPlot2;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
		}
	}
	else
	{
		if(numOfDotsToPlot2>0)
		{
				pGraph->plotHandle=PlotXY(graphDispPanel, control, (pGraph->pCurveArray + 1)->pDotXPlot, (pGraph->pCurveArray + 1)->pDotYPlot, numOfDotsToPlot2, 
										  VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, smu2Clr);
				//SetCtrlVal(graphDispPanel, GRAPHDISP_NUMERIC ,pGraph->pCurveArray->pDotXHead[pGraph->pCurveArray->numOfPlotDots ); 
				(pGraph->pCurveArray + 1)->numOfPlotDots+=numOfDotsToPlot2;		//��ͼ�ܵ�������
				(pGraph->pCurveArray + 1)->pDotXPlot+=numOfDotsToPlot2;			//��ͼ��X����ָ�����
				(pGraph->pCurveArray + 1)->pDotYPlot+=numOfDotsToPlot2;			//��ͼ��Y����ָ�����																																				     
				(pGraph->pCurveArray + 1)->numOfDotsToPlot-=numOfDotsToPlot2;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
		}
	}
	


	
	if(pGraph->plotHandle<0)
		return -1;
	else
		return 0;
}
//temp,humidity,pressure; 
int PlotCurve_Temp(Graph_TypeDef* pGraph_Temp, int graphDispPanel, int control)
{
	int numOfDotsToPlot=pGraph_Temp->pCurveArray->numOfDotsToPlot;							//��ֹ�ж϶�ȥд���������
	if(pGraph_Temp->pCurveArray->numOfPlotDots >=1 )	//�� �ڶ��� ��
	{
			if(numOfDotsToPlot>0)																
			{
				if(temp_flag == 1)  
				{
					pGraph_Temp->plotHandle=PlotXY(graphDispPanel, control, (pGraph_Temp->pCurveArray +1)->pDotXPlot-1, (pGraph_Temp->pCurveArray +1)->pDotYPlot-1, 
												   numOfDotsToPlot+1, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, graph2tempclr);
				}
				if(humidity_flag == 1)
				{
					pGraph_Temp->plotHandle=PlotXY(graphDispPanel, control, pGraph_Temp->pCurveArray->pDotXPlot-1, pGraph_Temp->pCurveArray->pDotYPlot-1, 
												   numOfDotsToPlot+1, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, graph2humclr);
				}
				if(pressure_flag == 1)
				{
					pGraph_Temp->plotHandle=PlotXY(graphDispPanel, control, (pGraph_Temp->pCurveArray +2)->pDotXPlot-1, (pGraph_Temp->pCurveArray +2)->pDotYPlot-1, 
												   numOfDotsToPlot+1, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, graph2preclr);
				}
				pGraph_Temp->pCurveArray->numOfPlotDots+=numOfDotsToPlot;				//��ͼ�ܵ�������
				pGraph_Temp->pCurveArray->pDotXPlot+=numOfDotsToPlot;					//��ͼ��X����ָ�����
				pGraph_Temp->pCurveArray->pDotYPlot+=numOfDotsToPlot;					//��ͼ��Y����ָ�����
				pGraph_Temp->pCurveArray->numOfDotsToPlot-=numOfDotsToPlot;				//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
				
				(pGraph_Temp->pCurveArray + 1)->numOfPlotDots+=numOfDotsToPlot;			//��ͼ�ܵ�������
				(pGraph_Temp->pCurveArray + 1)->pDotXPlot+=numOfDotsToPlot;				//��ͼ��X����ָ�����
				(pGraph_Temp->pCurveArray + 1)->pDotYPlot+=numOfDotsToPlot;				//��ͼ��Y����ָ�����
				(pGraph_Temp->pCurveArray + 1)->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
				
				(pGraph_Temp->pCurveArray + 2)->numOfPlotDots+=numOfDotsToPlot;			//��ͼ�ܵ�������
				(pGraph_Temp->pCurveArray + 2)->pDotXPlot+=numOfDotsToPlot;				//��ͼ��X����ָ�����
				(pGraph_Temp->pCurveArray + 2)->pDotYPlot+=numOfDotsToPlot;				//��ͼ��Y����ָ�����
				(pGraph_Temp->pCurveArray + 2)->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
			}
    }
	else //����һ����
	{
			if(numOfDotsToPlot>0)																//�������Ҫ��ͼ�ĵ�
			{	
				if(temp_flag == 1)
				{
					pGraph_Temp->plotHandle=PlotXY(graphDispPanel, control, (pGraph_Temp->pCurveArray +1)->pDotXPlot, (pGraph_Temp->pCurveArray +1)->pDotYPlot, 
												   numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, graph2tempclr);
				}
				
				if(humidity_flag == 1) 
				{
					pGraph_Temp->plotHandle=PlotXY(graphDispPanel, control, pGraph_Temp->pCurveArray->pDotXPlot, pGraph_Temp->pCurveArray->pDotYPlot, 
												   numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, graph2humclr);
				}
				if(pressure_flag == 1)
				{
					pGraph_Temp->plotHandle=PlotXY(graphDispPanel, control, (pGraph_Temp->pCurveArray +2)->pDotXPlot, (pGraph_Temp->pCurveArray +2)->pDotYPlot, 
												   numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, graph2preclr);
				}
				pGraph_Temp->pCurveArray->numOfPlotDots+=numOfDotsToPlot;		//��ͼ�ܵ�������
				pGraph_Temp->pCurveArray->pDotXPlot+=numOfDotsToPlot;			//��ͼ��X����ָ�����
				pGraph_Temp->pCurveArray->pDotYPlot+=numOfDotsToPlot;			//��ͼ��Y����ָ�����
				pGraph_Temp->pCurveArray->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
				
				(pGraph_Temp->pCurveArray + 1)->numOfPlotDots+=numOfDotsToPlot;		//��ͼ�ܵ�������
				(pGraph_Temp->pCurveArray + 1)->pDotXPlot+=numOfDotsToPlot;			//��ͼ��X����ָ�����
				(pGraph_Temp->pCurveArray + 1)->pDotYPlot+=numOfDotsToPlot;			//��ͼ��Y����ָ�����
				(pGraph_Temp->pCurveArray + 1)->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
				
				(pGraph_Temp->pCurveArray + 2)->numOfPlotDots+=numOfDotsToPlot;		//��ͼ�ܵ�������
				(pGraph_Temp->pCurveArray + 2)->pDotXPlot+=numOfDotsToPlot;			//��ͼ��X����ָ�����
				(pGraph_Temp->pCurveArray + 2)->pDotYPlot+=numOfDotsToPlot;			//��ͼ��Y����ָ�����
				(pGraph_Temp->pCurveArray + 2)->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
			}
	}
	if(pGraph_Temp->plotHandle<0)
		return -1;
	else
		return 0;
}
void temp_hum_pre_display()
{

	DeleteGraphPlot (graphDispPanel, GRAPHDISP_GRAPH2, -1, VAL_IMMEDIATE_DRAW);	//�����������������ͼ�е���������
	GetCtrlVal(hEnvResultPanel,ENVIRPANEL_CHECKBOX,&temp_flag);		//Ȼ���ȡ�û�Ҫѡ�е�����
	GetCtrlVal(hEnvResultPanel,ENVIRPANEL_CHECKBOX_2,&humidity_flag); 
	GetCtrlVal(hEnvResultPanel,ENVIRPANEL_CHECKBOX_3,&pressure_flag);
	/*GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR1, &graph2tempclr);
	GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR2, &graph2humclr);
	GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR3, &graph2preclr);*/
	if((temp_flag == 1)&&((Graph_Temp.pCurveArray  + 1)->numOfPlotDots>0))
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);    //text����ɫ(��canvas��ɫ��ͬ)
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);		 //"Temperature"��ɫ
		CanvasDrawText (graphDispPanel, GRAPHDISP_CANVAS, "T",VAL_APP_META_FONT, MakeRect(40,15,15,70), VAL_CENTER);	                            //д"Temperature"
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, graph2tempclr);			    //Temperatureͼ��
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_PEN_WIDTH, 2);			        //�ߵĿ��
		CanvasDrawLine (graphDispPanel, GRAPHDISP_CANVAS, MakePoint (110,47), MakePoint (150, 47));		//canvas����
		PlotXY(graphDispPanel, GRAPHDISP_GRAPH2, (Graph_Temp.pCurveArray  + 1)->pDotXHead, (Graph_Temp.pCurveArray  + 1)->pDotYHead, 
			   (Graph_Temp.pCurveArray  + 1)->numOfPlotDots, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, graph2tempclr);
	}
	else
	{
	  CanvasClear (graphDispPanel, GRAPHDISP_CANVAS, MakeRect(40,15,15,140));
	}
	if((humidity_flag == 1)&&(Graph_Temp.pCurveArray->numOfPlotDots>0))
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);    //text����ɫ(��canvas��ɫ��ͬ)
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);		 //"humidity"��ɫ
		CanvasDrawText (graphDispPanel, GRAPHDISP_CANVAS, "H",VAL_APP_META_FONT, MakeRect(60,15,15,70), VAL_CENTER);	                            //д"humidity"
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, graph2humclr);			    //humidityͼ��
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_PEN_WIDTH, 2);			        //�ߵĿ��
		CanvasDrawLine (graphDispPanel, GRAPHDISP_CANVAS, MakePoint (110, 67), MakePoint (150, 67));		//canvas����
		PlotXY(graphDispPanel, GRAPHDISP_GRAPH2, Graph_Temp.pCurveArray->pDotXHead, Graph_Temp.pCurveArray->pDotYHead, 
			   Graph_Temp.pCurveArray->numOfPlotDots, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, graph2humclr);
	}
	else
	{
	  CanvasClear (graphDispPanel, GRAPHDISP_CANVAS, MakeRect(60,15,15,140));
	}
	
	if((pressure_flag == 1)&&((Graph_Temp.pCurveArray  + 2)->numOfPlotDots>0))
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);    //text����ɫ(��canvas��ɫ��ͬ)
	    SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);		 //"pressure"��ɫ
	    CanvasDrawText (graphDispPanel, GRAPHDISP_CANVAS, "P",VAL_APP_META_FONT, MakeRect(80,15,15,70), VAL_CENTER);	                            //д"pressure"
	    SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, graph2preclr);			    //pressureͼ��
	    SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_PEN_WIDTH, 2);			        //�ߵĿ��
	    CanvasDrawLine (graphDispPanel, GRAPHDISP_CANVAS, MakePoint (110, 87), MakePoint (150, 87));		//canvas����
		PlotXY(graphDispPanel, GRAPHDISP_GRAPH2, (Graph_Temp.pCurveArray  + 2)->pDotXHead, (Graph_Temp.pCurveArray  + 2)->pDotYHead, 
			   (Graph_Temp.pCurveArray  + 2)->numOfPlotDots, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, graph2preclr);
	}
	else
	{
	 CanvasClear (graphDispPanel, GRAPHDISP_CANVAS, MakeRect(80,15,15,140)); 
	}
	
}


