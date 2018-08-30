//==============================================================================
//
// Title:		Timer.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 17:33:45 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

//#include "Timer.h"
#include "Graph.h"
#include "GraphDisp.h"
#include "LoadPanel.h"
#include "Plot.h"
#include "protocol.h"
#include "Cgs_mt.h"
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

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int CVICALLBACK TimerCallback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2)
{
	//PlotCurve(&Graph, graphDispPanel, GRAPHDISP_GRAPH1);//������ͼ
	PlotCurve_Temp(&Graph_Temp, graphDispPanel, GRAPHDISP_GRAPH2);//������ͼ

	ProtocolQuery( comSelect, select_Addr1, select_Addr2, measUartTxBuf1,  measUartTxBuf2);
	//Read_CGS_Value(CGS_comSelect);
	
	//�ж���ʾ�� X �᷶Χ�� X �᷶ΧҪ���� ʵʱ��ʾ�����ݵ�
	//if(Graph.X_Axis_Max < Graph.pCurveArray->numOfPlotDots)
	//{
	//	Graph.X_Axis_Max = Graph.X_Axis_Max + 100; 			//��ͼ�е� X ���������ֵ��Χ����100
	//	SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph.X_Axis_Max);//���� X ��ķ�Χ

	//	//SetAxisScalingMode (panelHandle, PANEL_GRAPH2, VAL_LEFT_YAXIS , VAL_MANUAL, 0, 20);   //���� Y ��ķ�Χ
	//}
	//
	////�ж���ʾ�� X �᷶Χ�� X �᷶ΧҪ���� ʵʱ��ʾ�����ݵ�
	//if(Graph_Temp.X_Axis_Max < Graph_Temp.pCurveArray->numOfPlotDots)
	//{
	//	Graph_Temp.X_Axis_Max = Graph_Temp.X_Axis_Max + 100; 			//��ͼ�е� X ���������ֵ��Χ����100
	//	SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph_Temp.X_Axis_Max);//���� X ��ķ�Χ

	//	//SetAxisScalingMode (panelHandle, PANEL_GRAPH2, VAL_LEFT_YAXIS , VAL_MANUAL, 0, 20);   //���� Y ��ķ�Χ
	//}
	
	
	return 0;
}
