#include <userint.h>
//==============================================================================
//
// Title:		LoadPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 15:21:14 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "LoadPanel.h"
#include "I_T_Panel.h"



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
int mainPanel;
int expListPanel;
int TwoTerminalPanel;
int ITPanel;
int IVPanel;
int VIPanel;
int VTPanel;
int RTPanel;

int FourTerminalPanel;
int IdVdPanel;
int IdVgPanel;

int hstretchPanel;

int hBasicSamplePanel;
int graphDispPanel;
int hEnvCfgPanel;
int resultPanel;
int graphDispPanel;
int tablePanel;
int saveDataPanel;

int settingsPanel;
int setPanel; 
int ENVTPanel;
int GRAPHPanel;
int hSettingsGraphPanel;
int aboutPanel;


int chPanel;
int proPanel;
int defPanel;
int hEnvResultPanel;
int hResultDispPanel;
int hAdvanceSamplePanel;  
int projectPanel;
int hToolsPanel;
int hCalibrationPanel;
int hStrainDispPanel;
int hImageDispPanel;
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int LoadInitPanel (void)
{
	if ((mainPanel = LoadPanel (0, "MainPanel.uir", MAIN_PANEL)) < 0)	  //load main panel
		return -1;

	if ((expListPanel = LoadPanel (mainPanel, "Experiment List.uir", EXP_LIST)) < 0)		//load left panel
		return -1;

	if ((IdVdPanel = LoadPanel (mainPanel, "Id-Vds Configuration.uir", IDVDS_CFG)) < 0)		//load middle panel
		return -1;


	if ((IdVgPanel = LoadPanel (mainPanel, "Id-Vgs Configuration.uir", IDVGS_CFG)) < 0)		//load middle panel
		return -1;

	if ((hBasicSamplePanel = LoadPanel (mainPanel, "Sample Configuration.uir", SAMPLE_CFG)) < 0)		//load right panel
		return -1;
	
	if ((hResultDispPanel = LoadPanel (mainPanel, "Sample Analyze.uir", SAMPLE)) < 0)		//load right panel
		return -1;
	
	if ((hStrainDispPanel = LoadPanel (mainPanel, "Sample Analyze.uir", STRAINDISP)) < 0)		//load right panel
		return -1;
	
	if ((hImageDispPanel = LoadPanel (mainPanel, "Sample Analyze.uir", IMAGEDISP)) < 0)		//load right panel
		return -1;
	
	if ((hAdvanceSamplePanel = LoadPanel (mainPanel, "Sample Configuration.uir", SAMPLE_ADV)) < 0)		//load right panel
		return -1;

	if ((hEnvCfgPanel = LoadPanel (mainPanel, "EnvironmentDisp.uir", ENVIRONMEN)) < 0)		//load Enviroment panel
		return -1;
	
	if ((hEnvResultPanel = LoadPanel (mainPanel, "EnvironmentDisp.uir", ENVIRPANEL)) < 0)		//load Enviroment panel
		return -1;
	if ((resultPanel = LoadPanel (mainPanel, "Result Menu.uir", RESULTMENU)) < 0)		//load resultPanel panel
		return -1;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	 //���ڵ���savedata���
	if ((saveDataPanel = LoadPanel (mainPanel, "Result Menu.uir", SAVEDATA)) < 0)		//load savedata panel
		return -1;
	
	if ((setPanel = LoadPanel (mainPanel, "SetPanel.uir", SETTINGS)) < 0)		//load settings panel
		return -1;	
	
	 //���ڵ���Environment Settings���
	if ((ENVTPanel = LoadPanel (setPanel, "SetPanel.uir", ENVT)) < 0)		//load ENV panel
		return -1;
	
	//���ڵ���Graph Defaults���								
	if ((hSettingsGraphPanel = LoadPanel (setPanel, "SetPanel.uir", SETGRAPH)) < 0)		//load graph panel
		return -1;
	
	//���ڵ���About���
	if ((aboutPanel = LoadPanel (setPanel, "SetPanel.uir", ABOUT)) < 0)		//load graph panel
		return -1;
	
	if ((graphDispPanel = LoadPanel (mainPanel, "GraphDisp.uir", GRAPHDISP)) < 0)		//load SETGRAPHDISP panel
		return -1;

	if ((tablePanel = LoadPanel (mainPanel, "TableData.uir", TABLE)) < 0)		//load TABLE panel
		return -1;

	if ((ITPanel = LoadPanel (mainPanel, "I-T Configuration.uir", PANEL_I_T)) < 0)
		return -1;
	I_T_Panel1.panelHandle = ITPanel;
	I_T_Panel2.panelHandle = ITPanel;
		
	if ((TwoTerminalPanel = LoadPanel (mainPanel, "TerminalPanel.uir", TWO_TRML)) < 0)		//load middle panel
		return -1;
	
	if ((IVPanel = LoadPanel (mainPanel, "I-V Configuration.uir", PANEL_I_V)) < 0)		//load middle panel
		return -1;
	I_V_Panel1.panelHandle = IVPanel;
	I_V_Panel2.panelHandle = IVPanel;
	
	if ((VIPanel = LoadPanel (mainPanel, "V-I Configuration.uir", PANEL_V_I)) < 0)		//load middle panel
		return -1;
	V_I_Panel1.panelHandle = VIPanel;
	V_I_Panel2.panelHandle = VIPanel;
	
	if ((VTPanel = LoadPanel (mainPanel, "V-T Configuration.uir", PANEL_V_T)) < 0)		//load middle panel
		return -1;
	V_T_Panel1.panelHandle = VTPanel;
	V_T_Panel2.panelHandle = VTPanel;
	
	if ((RTPanel = LoadPanel (mainPanel, "R-T Configuration.uir", PANEL_R_T)) < 0)		//load middle panel
		return -1;
	R_T_Panel1.panelHandle = RTPanel;
	R_T_Panel2.panelHandle = RTPanel;
	
	if ((FourTerminalPanel = LoadPanel (mainPanel, "TerminalPanel.uir", FOUR_TRML)) < 0)		//load middle panel
		return -1;
	
	if ((hstretchPanel = LoadPanel (mainPanel, "StretchPanel.uir", STRETCH)) < 0)		//load middle panel
		return -1;
	
	if ((chPanel = LoadPanel (mainPanel, "Result Menu.uir", CHPANEL)) < 0)		//load chPanel panel
		return -1;
		//����projects		
	if ((proPanel = LoadPanel (mainPanel, "ProjectPanel.uir", PROPANEL)) < 0)		//load projects panel
		return -1;
	
	if ((projectPanel = LoadPanel (proPanel, "ProjectPanel.uir", PROJECT)) < 0)		//load projects panel
		return -1;
	/*if ((defPanel = LoadPanel (proPanel, "ProjectPanel.uir", DEFPANEL)) < 0)		//load projects panel
		return -1;*/
	if ((hToolsPanel = LoadPanel(mainPanel,"Tools.uir",TOOLSPANEL))<0)
		return -1;
	if((hCalibrationPanel = LoadPanel(hToolsPanel,"Tools.uir",CALPANEL))<0)  			 
		return -1;
	
	DisplayPanel (mainPanel);
	SetPanelPos(expListPanel, 105, 3);  //�������λ�� (,top,left)
	DisplayPanel(expListPanel);

	SetPanelPos(TwoTerminalPanel, 105, 305);		
	//SetPanelSize(TwoTerminalPanel, 900, 1293);
	DisplayPanel(TwoTerminalPanel);
	
	SetCtrlAttribute (mainPanel, MAIN_PANEL_ANALYZE, ATTR_DIMMED,1); 

	return 0;
}
