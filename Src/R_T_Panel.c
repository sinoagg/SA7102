//==============================================================================
//
// Title:		I_V_Panel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/14 at 10:17:00 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "R-T Configuration.h"
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
ExpPanelTypeDef R_T_Panel1={0, PANEL_R_T_START1, PANEL_R_T_START1, PANEL_R_T_START1, PANEL_R_T_START1, PANEL_R_T_START1, PANEL_R_T_START1};
ExpPanelTypeDef R_T_Panel2={0, PANEL_R_T_START2, PANEL_R_T_START2, PANEL_R_T_START2, PANEL_R_T_START2, PANEL_R_T_START2, PANEL_R_T_START2};

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
static void RTSetSMU1Disp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		SetCtrlAttribute (panel, PANEL_R_T_BG_SMU1, ATTR_PICT_BGCOLOR, VAL_BG_Pressed);
		SetCtrlAttribute (panel, PANEL_R_T_TXT_SMU1, ATTR_TEXT_BGCOLOR, VAL_BG_Pressed);// change text bgcolor together with picture
	}
	else
	{
		SetCtrlAttribute (panel, PANEL_R_T_BG_SMU1, ATTR_PICT_BGCOLOR, VAL_BG); 
		SetCtrlAttribute (panel, PANEL_R_T_TXT_SMU1, ATTR_TEXT_BGCOLOR, VAL_BG);// change text bgcolor together with picture
	}
}

static void RTSetSMU2Disp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		SetCtrlAttribute (panel, PANEL_R_T_BG_SMU2, ATTR_PICT_BGCOLOR, VAL_BG_Pressed);
		SetCtrlAttribute (panel, PANEL_V_T_TXT_SMU2, ATTR_TEXT_BGCOLOR, VAL_BG_Pressed);// change text bgcolor together with picture
	}
	else
	{
		SetCtrlAttribute (panel, PANEL_R_T_BG_SMU2, ATTR_PICT_BGCOLOR, VAL_BG);
		SetCtrlAttribute (panel, PANEL_R_T_TXT_SMU2, ATTR_TEXT_BGCOLOR, VAL_BG);// change text bgcolor together with picture
	}
}
int CVICALLBACK RTSMU1DecoCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 RTSetSMU1Disp(panel, FOCUS);
			 RTSetSMU2Disp(panel, UNFOCUS);
			break;
	}
	return 0;
}

int CVICALLBACK RTSMU2DecoCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 RTSetSMU1Disp(panel, UNFOCUS);
			 RTSetSMU2Disp(panel, FOCUS);
			break;
	}
	return 0;
}



								  

