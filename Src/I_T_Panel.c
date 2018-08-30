//==============================================================================
//
// Title:		I_T_Panel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/14 at 10:17:00 by.
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "I-T Configuration.h"
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
////ITCfg_TypeDef ITCfg1; 
//ITCfg_TypeDef ITCfg2;
ExpPanelTypeDef I_T_Panel1={0, PANEL_I_T_START1, PANEL_I_T_START1, PANEL_I_T_START1, PANEL_I_T_START1, PANEL_I_T_START1, PANEL_I_T_START1};
ExpPanelTypeDef I_T_Panel2={0, PANEL_I_T_START2, PANEL_I_T_START2, PANEL_I_T_START2, PANEL_I_T_START2, PANEL_I_T_START2, PANEL_I_T_START2};
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
static void ITSetSMU1Disp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		SetCtrlAttribute (panel, PANEL_I_T_BG_SMU1, ATTR_PICT_BGCOLOR, VAL_BG_Pressed);
		SetCtrlAttribute (panel, PANEL_I_T_TXT_SMU1, ATTR_TEXT_BGCOLOR, VAL_BG_Pressed);// change text bgcolor together with picture
	}
	else
	{
		SetCtrlAttribute (panel, PANEL_I_T_BG_SMU1, ATTR_PICT_BGCOLOR, VAL_BG); 
		SetCtrlAttribute (panel, PANEL_I_T_TXT_SMU1, ATTR_TEXT_BGCOLOR, VAL_BG);// change text bgcolor together with picture
	}
}

static void ITSetSMU2Disp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		SetCtrlAttribute (panel, PANEL_I_T_BG_SMU2, ATTR_PICT_BGCOLOR, VAL_BG_Pressed);
		SetCtrlAttribute (panel, PANEL_I_T_TXT_SMU2, ATTR_TEXT_BGCOLOR, VAL_BG_Pressed);// change text bgcolor together with picture
	}
	else
	{
		SetCtrlAttribute (panel, PANEL_I_T_BG_SMU2, ATTR_PICT_BGCOLOR, VAL_BG);
		SetCtrlAttribute (panel, PANEL_I_T_TXT_SMU2, ATTR_TEXT_BGCOLOR, VAL_BG);// change text bgcolor together with picture
	}
}
int CVICALLBACK ITSMU1DecoCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 ITSetSMU1Disp(panel, FOCUS);
			 ITSetSMU2Disp(panel, UNFOCUS);
			break;
	}
	return 0;
}

int CVICALLBACK ITSMU2DecoCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 ITSetSMU1Disp(panel, UNFOCUS);
			 ITSetSMU2Disp(panel, FOCUS);
			break;
	}
	return 0;
}

static void GetTestPara(ExpPanelTypeDef* pExpPanel, TestParaTypeDef* pTestPara) //�õ�������û����õĲ���
{
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VdStartID,&(pTestPara->Voltage_Start));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VdStopID, &(pTestPara->Voltage_Stop));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VdStepID, &(pTestPara->Voltage_Step));
	
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VgStartID, &(pTestPara->Current_Start));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VgStopID, &(pTestPara->Current_Stop));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VgStepID, &(pTestPara->Current_Step));

	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_QUIETTIME, &(pTestPara->quietTime));   //���в������ö��Ǽ��ݵ�
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, &(pTestPara->timeStep));
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, &(pTestPara->runTime));
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, &(pTestPara->sampleRate));
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_SAMPLENUMBER, &(pTestPara->sampleNumber));
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_RANGESETTING, &(pTestPara->rangeMode));
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

