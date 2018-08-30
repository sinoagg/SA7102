//==============================================================================
//
// Title:		V_I_Panel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/14 at 10:17:00 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "V-I Configuration.h"
#include <userint.h>
#include "I_T_Panel.h"
#include "ExpListPanel.h"
#include "LoadPanel.h"
//==============================================================================
// Constants
#define VAL_BG                        0xA9A9A9L    //δ��ѡ��ʱ�ı���ɫ
#define VAL_BG_Pressed                0xA5B8D2L    //��ѡ��ʱ�ı���ɫ
#define FOCUS	0
#define UNFOCUS 1
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
//ITCfg_TypeDef ITCfg1;

//ITCfg_TypeDef ITCfg2;
ExpPanelTypeDef V_I_Panel1={0, PANEL_V_I_START1, PANEL_V_I_STOP1, PANEL_V_I_GAP1, PANEL_V_I_START1, PANEL_V_I_STOP1, PANEL_V_I_GAP1};
ExpPanelTypeDef V_I_Panel2={0, PANEL_V_I_START2, PANEL_V_I_STOP2, PANEL_V_I_GAP2, PANEL_V_I_START2, PANEL_V_I_STOP2, PANEL_V_I_GAP2};

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
static void VISetSMU1Disp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		SetCtrlAttribute (panel, PANEL_V_I_BG_SMU1, ATTR_PICT_BGCOLOR, VAL_BG_Pressed);
		SetCtrlAttribute (panel, PANEL_V_I_TXT_SMU1, ATTR_TEXT_BGCOLOR, VAL_BG_Pressed);// change text bgcolor together with picture
	}
	else
	{
		SetCtrlAttribute (panel, PANEL_V_I_BG_SMU1, ATTR_PICT_BGCOLOR, VAL_BG); 
		SetCtrlAttribute (panel, PANEL_V_I_TXT_SMU1, ATTR_TEXT_BGCOLOR, VAL_BG);// change text bgcolor together with picture
	}
}

static void VISetSMU2Disp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		SetCtrlAttribute (panel, PANEL_V_I_BG_SMU2, ATTR_PICT_BGCOLOR, VAL_BG_Pressed);
		SetCtrlAttribute (panel, PANEL_V_I_TXT_SMU2, ATTR_TEXT_BGCOLOR, VAL_BG_Pressed);// change text bgcolor together with picture
	}
	else
	{
		SetCtrlAttribute (panel, PANEL_V_I_BG_SMU2, ATTR_PICT_BGCOLOR, VAL_BG);
		SetCtrlAttribute (panel, PANEL_V_I_TXT_SMU2, ATTR_TEXT_BGCOLOR, VAL_BG);// change text bgcolor together with picture
	}
}
int CVICALLBACK VISMU1DecoCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 VISetSMU1Disp(panel, FOCUS);
			 VISetSMU2Disp(panel, UNFOCUS);
			break;
	}
	return 0;
}

int CVICALLBACK VISMU2DecoCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 VISetSMU1Disp(panel, UNFOCUS);
			 VISetSMU2Disp(panel, FOCUS);
			break;
	}
	return 0;
}

int CVICALLBACK Start1UnitCB (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	int val;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (VIPanel, PANEL_V_I_START1UNIT, &val);
			if(val==0)
			{
				SetCtrlVal (VIPanel, PANEL_V_I_STOP1UNIT, "A");
				SetCtrlVal (VIPanel, PANEL_V_I_GAP1UNIT, "A");
			}
			else if(val==1)
			{
				SetCtrlVal (VIPanel, PANEL_V_I_STOP1UNIT, "mA");
				SetCtrlVal (VIPanel, PANEL_V_I_GAP1UNIT, "mA");
			}
			else if(val==2)
			{
				SetCtrlVal (VIPanel, PANEL_V_I_STOP1UNIT, "uA");
				SetCtrlVal (VIPanel, PANEL_V_I_GAP1UNIT, "uA");
			}
			else if(val==3)
			{
				SetCtrlVal (VIPanel, PANEL_V_I_STOP1UNIT, "nA");
				SetCtrlVal (VIPanel, PANEL_V_I_GAP1UNIT, "nA");
			}
			else if(val==4)
			{
				SetCtrlVal (VIPanel, PANEL_V_I_STOP1UNIT, "pA");
				SetCtrlVal (VIPanel, PANEL_V_I_GAP1UNIT, "pA");
			}
			break;
		case EVENT_LEFT_CLICK_UP:
			 VISetSMU1Disp(panel, FOCUS);
			 VISetSMU2Disp(panel, UNFOCUS);
			break;
	}
	return 0;
}

int CVICALLBACK Start2UnitCB (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	int val;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (VIPanel, PANEL_V_I_START2UNIT, &val);
			if(val==0)
			{
				SetCtrlVal (VIPanel, PANEL_V_I_STOP2UNIT, "A");
				SetCtrlVal (VIPanel, PANEL_V_I_GAP2UNIT, "A");
			}
			else if(val==1)
			{
				SetCtrlVal (VIPanel, PANEL_V_I_STOP2UNIT, "mA");
				SetCtrlVal (VIPanel, PANEL_V_I_GAP2UNIT, "mA");
			}
			else if(val==2)
			{
				SetCtrlVal (VIPanel, PANEL_V_I_STOP2UNIT, "uA");
				SetCtrlVal (VIPanel, PANEL_V_I_GAP2UNIT, "uA");
			}
			else if(val==3)
			{
				SetCtrlVal (VIPanel, PANEL_V_I_STOP2UNIT, "nA");
				SetCtrlVal (VIPanel, PANEL_V_I_GAP2UNIT, "nA");
			}
			else if(val==4)
			{
				SetCtrlVal (VIPanel, PANEL_V_I_STOP2UNIT, "pA");
				SetCtrlVal (VIPanel, PANEL_V_I_GAP2UNIT, "pA");
			}
	    	break;
		case EVENT_LEFT_CLICK_UP:
			 VISetSMU1Disp(panel, UNFOCUS);
			 VISetSMU2Disp(panel, FOCUS);
			break;
	}
	return 0;
}
								  

/////*


////	���ܣ��õ� V_T V_I  ģʽ���û�����������ֵ

////*/
////int Get_V_I_Cfg (int panelHandle)
////{
////	int temp;
////	
////	//�õ�Դ�� 1 �� ����   ��ʼ  ���� �������	  
////	if(GetCtrlVal(panelHandle, PANEL_I_T_START1, &temp)<0)
////		return -1;
////	ITCfg1.cfgIT_Current_start=temp;
////	if(GetCtrlVal(panelHandle, PANEL_I_T_STOP1, &temp)<0)
////		return -1;
////	ITCfg1.cfgIT_Current_stop=temp;
////	if(GetCtrlVal(panelHandle, PANEL_I_T_GAP1, &temp)<0)
////		return -1;
////	ITCfg1.cfgIT_Current_step = temp;
////	
////	
////	//�õ�Դ�� 2 �� ����   ��ʼ  ���� ������� 	
////	if(GetCtrlVal(panelHandle, PANEL_I_T_START2, &temp)<0)
////		return -1;
////	ITCfg2.cfgIT_Current_start = temp;
////	if(GetCtrlVal(panelHandle, PANEL_I_T_STOP2, &temp)<0)
////		return -1;
////	ITCfg2.cfgIT_Current_stop = temp;
////	if(GetCtrlVal(panelHandle, PANEL_I_T_GAP2, &temp)<0)
////		return -1;
////	ITCfg2.cfgIT_Current_step = temp;
////	
////	return 0;
////}
/////*


////	���ܣ��õ� I_T  I_V  ģʽ���û�����������ֵ

////*/
////int Get_IT_Cfg (int panelHandle)
////{
////	int temp;
////	
////	//�õ�Դ�� 1 �� ��ѹ   ��ʼ  ���� �������	  
////	if(GetCtrlVal(panelHandle, PANEL_I_T_START1, &temp)<0)		  
////		return -1;
////	ITCfg1.cfgIT_Voltage_start=temp;
////	if(GetCtrlVal(panelHandle, PANEL_I_T_STOP1, &temp)<0)
////		return -1;
////	ITCfg1.cfgIT_Voltage_stop=temp;
////	if(GetCtrlVal(panelHandle, PANEL_I_T_GAP1, &temp)<0)
////		return -1;
////	ITCfg1.cfgIT_Voltage_step = temp;
////	
////	//�õ�Դ�� 2 �� ��ѹ   ��ʼ  ���� ������� 	
////	if(GetCtrlVal(panelHandle, PANEL_I_T_START2, &temp)<0)
////		return -1;
////	ITCfg2.cfgIT_Voltage_start = temp;
////	if(GetCtrlVal(panelHandle, PANEL_I_T_STOP2, &temp)<0)
////		return -1;
////	ITCfg2.cfgIT_Voltage_stop = temp;
////	if(GetCtrlVal(panelHandle, PANEL_I_T_GAP2, &temp)<0)
////		return -1;
////	ITCfg2.cfgIT_Voltage_step = temp;
////	
////	return 0;
////}


