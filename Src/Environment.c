#include "GraphDisp.h"
#include "EnvironmentDisp.h"

//==============================================================================
//
// Title:		Environment.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/26 at 15:46:52 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <userint.h>
#include "Environment.h"
#include "LoadPanel.h"
#include "Cgs_mt.h" 
#include "Graph.h"
#include "Plot.h"
#include "utility.h"


//#include "Environment.h"

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
int temp_flag,humidity_flag,pressure_flag;
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?

int CVICALLBACK MesaureCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{ 
	int CheckValue;
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			GetCtrlVal(panel,control,&CheckValue);//Measure ��ѡ 
			if(CheckValue)
			{
				SetCtrlVal(panel,ENVIRONMEN_TEMPTER,CheckValue);
				SetCtrlVal(panel,ENVIRONMEN_HUMIDITY,CheckValue);
				SetCtrlVal(panel,ENVIRONMEN_PRESSURE,CheckValue);
			} 
			else
			{
				SetCtrlVal(panel,ENVIRONMEN_TEMPTER,0);
				SetCtrlVal(panel,ENVIRONMEN_HUMIDITY,0);
				SetCtrlVal(panel,ENVIRONMEN_PRESSURE,0);
			}
		break;
	}
	return 0;
}

int CVICALLBACK Humidity_displayCB (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{   
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			temp_hum_pre_display();

			break;
	}
	return 0;
}

int CVICALLBACK Temp_displayCB (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			temp_hum_pre_display();

			break;
	}
	return 0;
}

int CVICALLBACK Pressure_displayCB (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			temp_hum_pre_display();
			
			break;
	}
	return 0;
}
//===========================canvas==================================
int CVICALLBACK CANVAS_CB (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int LeftButtonDown;
	int x;
	int y;
	int CtrlTop;
	int CtrlLeft;
	static int OldX = 0;	  //�ֲ���̬��������X������ֵ 
	static int OldY = 0;	
	switch (event)
	{
		case EVENT_MOUSE_POINTER_MOVE:
			GetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_LEFT, &CtrlLeft);
			GetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_TOP, &CtrlTop);
			GetGlobalMouseState (&panel, &x, &y, &LeftButtonDown, NULL, NULL);	     // ���������λ�á�����������
			if (LeftButtonDown == 1)	  											 // ������������ʱ
			{
				SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_LEFT, CtrlLeft + (x-OldX) );
				SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_TOP, CtrlTop + (y-OldY) );
				OldX = x;
				OldY = y;				  				 // ����X��Y ����ֵ�Ե�ǰ��ֵ���� 
				if( ( CtrlTop + (y-OldY) )<420)			 //ͼ�����ܳ���graph2�ķ�Χ
				{
					SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_LEFT, CtrlLeft + (x-OldX) );
					SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_TOP, 420 );
				}
				if( ( CtrlTop + (y-OldY) )>670)
				{
					SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_LEFT, CtrlLeft + (x-OldX) );
					SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_TOP, 670 );
				}
				if( (CtrlLeft + (x-OldX) )<15)
				{
					SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_LEFT, 15 );
					SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_TOP, CtrlTop + (y-OldY) );
				}
				if( (CtrlLeft + (x-OldX) )>1010)
				{
					SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_LEFT, 1010 );
					SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_TOP, CtrlTop + (y-OldY) );
				}
			}
			OldX = x;
			OldY = y;					  // ����X������ֵ�Ե�ǰ��ֵ����
		break;
	}
	return 0;
}
//int CVICALLBACK Legend_display_CB (int panel, int control, int event,void *callbackData, int eventData1, int eventData2)
//{   
//	int legendval;
//	if( event == EVENT_VAL_CHANGED) 
//	{   
//		GetCtrlVal(hEnvResultPanel, ENVIRPANEL_LEGENDCHECK, &legendval);
//		SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_VISIBLE, legendval);
//		SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_LEFT, 1010); 
//		SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_TOP, 420);
//	}
//	return 0;
//}
