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
#include "excelreport.h"
#include "excel2000.h"
#include "GraphDisp.h"
#include <userint.h>
#include "toolbox.h"   
#include "ResultMenuPanel.h"
#include "Graph.h"
#include "LoadPanel.h"
//==============================================================================
// Constants

//==============================================================================
// Types
enum ResultDispSelect
{
	DISP_TABLE=0,
	DISP_GRAPH=1
};
enum GraphDispSelect
{
	DISP_SINGLE_GRAPH=0,
	DISP_DOUBLE_GRAPH=1	
};
//==============================================================================
// Static global variables
char sheetSavePath[512];
char graph1SavePath[512];
char graph2SavePath[512];
//==============================================================================
// Static functions
//==============================================================================
// Global variables
enum ResultDispSelect resultDispSelect=DISP_GRAPH;
enum GraphDispSelect graphDispSelect=DISP_SINGLE_GRAPH;
//==============================================================================
// Global functions	

static void DispTable(void)
{
	SetPanelPos(tablePanel, 172, 305);  
 	SetPanelSize(tablePanel, 833, 1293);      
	DisplayPanel(tablePanel);
}

static void DispSingleGraph(void)
{
	SetPanelPos(graphDispPanel, 172, 305);  
	SetPanelSize(graphDispPanel, 833, 1293);
	SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 700);
	SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
	DisplayPanel(graphDispPanel);
//	SetCtrlAttribute (hEnvResultPanel, ENVIRPANEL_LEGENDCHECK, ATTR_VISIBLE, 0);
//	SetCtrlAttribute (hEnvResultPanel, ENVIRPANEL_TXT_LEGEND, ATTR_VISIBLE, 0);
	SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_VISIBLE, 0);  
}

static void DispDoubleGraph(void)
{
	SetPanelPos(graphDispPanel, 172, 305);  
	SetPanelSize(graphDispPanel, 833, 1293);
	SetCtrlAttribute (graphDispPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 380); //���CheckBox��ѡ��״̬����ʾ����graph     
	SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
	DisplayPanel(graphDispPanel);
//	SetCtrlAttribute (hEnvResultPanel, ENVIRPANEL_LEGENDCHECK, ATTR_VISIBLE, 1);
//	SetCtrlAttribute (hEnvResultPanel, ENVIRPANEL_TXT_LEGEND, ATTR_VISIBLE, 1);
	
	int legendval;
//	GetCtrlVal(hEnvResultPanel, ENVIRPANEL_LEGENDCHECK, &legendval);
	SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_VISIBLE, legendval);
	SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_LEFT, 1010); 
	SetCtrlAttribute (graphDispPanel, GRAPHDISP_CANVAS, ATTR_TOP, 420);

	
}

static void DispGraphSelectCheckBox(void)
{
	if(graphDispSelect==DISP_SINGLE_GRAPH)
	{
		SetCtrlVal(chPanel, CHPANEL_CHECKBOX, 0);
	}
	else{
		SetCtrlVal(chPanel, CHPANEL_CHECKBOX, 1);
	 
	}
	SetPanelPos(chPanel, 172, 1457);  
	SetPanelSize(chPanel, 26, 140);      
 	DisplayPanel(chPanel);
}

void DispResultTableGraph(void)
{
	if(resultDispSelect==DISP_TABLE)
		DispTable();
	else
	{
	  	if(graphDispSelect==DISP_SINGLE_GRAPH) 
		DispSingleGraph();
		else if(graphDispSelect==DISP_DOUBLE_GRAPH)
		DispDoubleGraph();
	}
}
//======================Table=================================  
int CVICALLBACK TableCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	
	//���tableͼ���л���table���
	switch(event)
	{
		case EVENT_LEFT_CLICK_UP:
			DisplayImageFile (resultPanel, RESULTMENU_TABLE, "Resource\\Table_pressed.ico"); 
			DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph.ico"); 
			DisplayImageFile (resultPanel, RESULTMENU_SAVE, "Resource\\SaveData.ico");
			resultDispSelect=DISP_TABLE;
			DispResultTableGraph();
			break;
	}
	return 0;
}
//======================Graph=================================  
int CVICALLBACK GraphCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch(event)			   //���graphͼ���л���graph���
	{
		case EVENT_LEFT_CLICK_UP:
			
			DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
			DisplayImageFile (resultPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
			DisplayImageFile (resultPanel, RESULTMENU_SAVE, "Resource\\SaveData.ico"); 
				
			if(resultDispSelect==DISP_GRAPH)//�����ʱ����ʾͼ��ʱ��ȥ���ͼ��ͼ�꣬����Ϊ�����л���ʾ
			{	
		  		DispGraphSelectCheckBox();
			}
			else
			{
				resultDispSelect=DISP_GRAPH;
				DispResultTableGraph();
			}
			
			int val;
	  	    GetCtrlVal(chPanel, CHPANEL_CHECKBOX, &val);
			if(val)
				DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
			else
				DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
				
			break;
		
	}	
	return 0;
}
//======================SaveData=================================  
int CVICALLBACK SaveDataCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)

{
	switch(event)
	{
		case EVENT_LEFT_CLICK_UP:
 
			DisplayImageFile (resultPanel, RESULTMENU_SAVE, "Resource\\SaveData_pressed.ico"); 
			InstallPopup(saveDataPanel);		//����savedata��� 
			break;
	}	
	return 0;
}
//======================Exit=================================  
int CVICALLBACK ExitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
		if (event == EVENT_COMMIT)
		{
			RemovePopup (saveDataPanel);	 //�Ƴ����ر�savedata���  
			DisplayImageFile (resultPanel, RESULTMENU_SAVE, "Resource\\SaveData.ico");
			
		}
			return 0;
}

//======================BrowseSheet=================================
int CVICALLBACK BrowseSheetCallback (int panel, int control, int event,
								   	 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{			
		case EVENT_LEFT_CLICK_UP:
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\", ".xls", "*.xls", "Select Path", VAL_OK_BUTTON, 0, 1, 1, 1, sheetSavePath)>0)
				SetCtrlVal(panel, SAVEDATA_SHEETPATH, sheetSavePath);
			else 
				return -1;
			break;
	}
	return 0;
}
//======================BrowseGraph1=================================		 
int CVICALLBACK BrowseGraph1Callback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		     
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\UserData", ".jpg", "*.jpg;*.png;*.bmp;*.tif", "Select Path", VAL_OK_BUTTON, 0, 0, 1, 1, graph1SavePath)>0)
				SetCtrlVal(panel, SAVEDATA_GRAPH1PATH, graph1SavePath);
			break;
	}
	return 0;
}
//======================BrowseGraph2=================================
int CVICALLBACK BrowseGraph2Callback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\UserData", ".jpg", "*.jpg;*.png;*.bmp;*.tif", "Select Path", VAL_OK_BUTTON, 0, 0, 1, 1, graph2SavePath)>0)
				SetCtrlVal(panel, SAVEDATA_GRAPH2PATH, graph2SavePath);
			break;
	}
	return 0;
}

//=======================saveGraph1=====================
int CVICALLBACK SaveGraph1Callback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	Rect rc;
	int nBitmapID;
	switch (event)
	{
		case EVENT_COMMIT:
		if(graph1SavePath[0]=='\0')
		{
			
		}
		else
		{
			GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_TOP, &rc.top);		//�õ���Ҫ��ȡ�Ĳ���ͼ������  
			GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_LEFT, &rc.left);
			GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_HEIGHT, &rc.height);
			GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_WIDTH, &rc.width);
			GetPanelDisplayBitmap (graphDispPanel, VAL_FULL_PANEL, rc, &nBitmapID);
			SaveBitmapToJPEGFile (nBitmapID, graph1SavePath, JPEG_INTERLACE, 100);
			DiscardBitmap (nBitmapID);
		}
		
			break;
	}
	return 0;
}
//=======================saveGraph2=====================
int CVICALLBACK SaveGraph2Callback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	Rect rc;
	int nBitmapID;
	
	switch (event)
	{
		case EVENT_COMMIT:
		if(graph2SavePath[0]=='\0') 
		{

		}
		else
		{
			GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH2, ATTR_TOP, &rc.top);		//�õ���Ҫ��ȡ�Ĳ���ͼ������  
			GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH2, ATTR_LEFT, &rc.left);
			GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH2, ATTR_HEIGHT, &rc.height);
			GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH2, ATTR_WIDTH, &rc.width);
			GetPanelDisplayBitmap (graphDispPanel, VAL_FULL_PANEL, rc, &nBitmapID);
			SaveBitmapToJPEGFile (nBitmapID, graph2SavePath, JPEG_INTERLACE, 100);
			DiscardBitmap (nBitmapID);
		}
			
		break;
	}
	return 0;
}

//======================saveSheet==========================
int CVICALLBACK SaveSheetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	
	static ExcelObj_App               ExcelAppHandle = 0;       
	static ExcelObj_Workbooks         ExcelWorkbooksHandle = 0; 
	static ExcelObj_Workbook          ExcelWorkbookHandle = 0;  
	static ExcelObj_Sheets            ExcelSheetsHandle = 0;    
	static ExcelObj_Worksheet         ExcelWorksheetHandle = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			if(sheetSavePath[0]=='\0')
			{

			
			}
			else
			{
				Excel_NewApp (NULL, 1, LOCALE_NEUTRAL, 0, &ExcelAppHandle);	  //create a new Application object, and obtain a handle to the object.
				// Excel_SetProperty (ExcelAppHandle, NULL, Excel_AppVisible, CAVT_BOOL, VTRUE);	  //set application visible
				Excel_GetProperty (ExcelAppHandle, NULL, Excel_AppWorkbooks, CAVT_OBJHANDLE, &ExcelWorkbooksHandle);
				Excel_WorkbooksAdd (ExcelWorkbooksHandle, NULL, CA_DEFAULT_VAL,&ExcelWorkbookHandle);
				Excel_GetProperty (ExcelAppHandle, NULL, Excel_AppSheets,CAVT_OBJHANDLE, &ExcelSheetsHandle);
				Excel_SheetsItem (ExcelSheetsHandle, NULL, CA_VariantInt(1),&ExcelWorksheetHandle);
				Excel_WorksheetActivate (ExcelWorksheetHandle, NULL);
				ExcelRpt_WriteDataFromTableControl (ExcelWorksheetHandle, "A1:D100", tablePanel, TABLE_TABLE1);	//write data from table control
				ExcelRpt_WorkbookSave (ExcelWorkbookHandle, sheetSavePath, ExRConst_DefaultFileFormat);
				Excel_AppQuit (ExcelAppHandle, NULL);
			}
			
			break;
	}
	return 0;
}

//=======================saveAll============================
int CVICALLBACK SaveAllCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	Rect rc;
	int nBitmapID;
	static ExcelObj_App               ExcelAppHandle = 0;       
	static ExcelObj_Workbooks         ExcelWorkbooksHandle = 0; 
	static ExcelObj_Workbook          ExcelWorkbookHandle = 0;  
	static ExcelObj_Sheets            ExcelSheetsHandle = 0;    
	static ExcelObj_Worksheet         ExcelWorksheetHandle = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			
			if((sheetSavePath[0]=='\0')||(graph2SavePath[0]=='\0')||(graph1SavePath[0]=='\0'))
			{
				
			}
			else
			{
				Excel_NewApp (NULL, 1, LOCALE_NEUTRAL, 0, &ExcelAppHandle);	  //create a new Application object, and obtain a handle to the object.
				// Excel_SetProperty (ExcelAppHandle, NULL, Excel_AppVisible, CAVT_BOOL, VTRUE);	  //set application visible
				Excel_GetProperty (ExcelAppHandle, NULL, Excel_AppWorkbooks, CAVT_OBJHANDLE, &ExcelWorkbooksHandle);
				Excel_WorkbooksAdd (ExcelWorkbooksHandle, NULL, CA_DEFAULT_VAL,&ExcelWorkbookHandle);
				Excel_GetProperty (ExcelAppHandle, NULL, Excel_AppSheets,CAVT_OBJHANDLE, &ExcelSheetsHandle);
				Excel_SheetsItem (ExcelSheetsHandle, NULL, CA_VariantInt(1),&ExcelWorksheetHandle);
				Excel_WorksheetActivate (ExcelWorksheetHandle, NULL);
				ExcelRpt_WriteDataFromTableControl (ExcelWorksheetHandle, "A1:D100", tablePanel, TABLE_TABLE1);	//write data from table control
				ExcelRpt_WorkbookSave (ExcelWorkbookHandle, sheetSavePath, ExRConst_DefaultFileFormat);
				Excel_AppQuit (ExcelAppHandle, NULL);
		
				GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH2, ATTR_TOP, &rc.top);		//�õ���Ҫ��ȡ�Ĳ���ͼ������  
				GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH2, ATTR_LEFT, &rc.left);
				GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH2, ATTR_HEIGHT, &rc.height);
				GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH2, ATTR_WIDTH, &rc.width);
				GetPanelDisplayBitmap (graphDispPanel, VAL_FULL_PANEL, rc, &nBitmapID);
				SaveBitmapToJPEGFile (nBitmapID, graph2SavePath, JPEG_INTERLACE, 100);
				DiscardBitmap (nBitmapID);
		
				GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_TOP, &rc.top);		//�õ���Ҫ��ȡ�Ĳ���ͼ������  
				GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_LEFT, &rc.left);
				GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_HEIGHT, &rc.height);
				GetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_WIDTH, &rc.width);
				GetPanelDisplayBitmap (graphDispPanel, VAL_FULL_PANEL, rc, &nBitmapID);
				SaveBitmapToJPEGFile (nBitmapID, graph1SavePath, JPEG_INTERLACE, 100);
				DiscardBitmap (nBitmapID);
			
			}
		break;
	}
	return 0;
}

//======================Chose=================================
int CVICALLBACK ChoseCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{

	if( event == EVENT_VAL_CHANGED)
		{
			HidePanel(chPanel); 
			int val;
		  	GetCtrlVal(chPanel, CHPANEL_CHECKBOX, &val);
		    if(val)
			{	
			    DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
				DispDoubleGraph();
				graphDispSelect=DISP_DOUBLE_GRAPH;
			}
			else
			{   
				DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
				DispSingleGraph();
				graphDispSelect=DISP_SINGLE_GRAPH;
			}
			

		}
	return 0;
}

static int SaveGraph(int panel, int control, int plotHandle, const char path[])
{
	int bitmapID;
	if(plotHandle<=0)		//no valid plot behavior
		MessagePopup ("Message", "No valod plot. Please run test first.");
	else
	{
		if(GetCtrlBitmap(panel, control, plotHandle,&bitmapID)<0)
			return -1;
		if(SaveBitmapToFile(path, bitmapID)<0)		 //need check the file format
			return -1;
		DiscardBitmap(bitmapID);
	}
	return 0;
}
