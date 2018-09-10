//==============================================================================
//
// Title:		Stretch.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/26 at 15:46:52 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "StretchPanel.h" 
#include <userint.h>    
#include "LoadPanel.h" 
//==============================================================================
// Constants
char a[15][20]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"};
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

int CVICALLBACK DeleteCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			Rect range;
			int row;
			GetTableSelection (hstretchPanel, STRETCH_TABLE, &range);
			if(range.left==1&range.width==8)
			DeleteTableRows (hstretchPanel, STRETCH_TABLE, range.top, range.height); 
			GetNumTableRows (hstretchPanel, STRETCH_TABLE, &row);   //获取行数
			for(int i=1;i<row+1;i++)	  //重新编号
			{
				SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, i, ATTR_USE_LABEL_TEXT, 1);
				SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, i, ATTR_LABEL_TEXT, a[i-1]);
			}
			break;
	}
	return 0;
}

int CVICALLBACK InsabvCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			Rect range;		  
			int row;
			GetTableSelection (hstretchPanel, STRETCH_TABLE, &range);	 //获取当前选中范围
			if(range.left==1&range.width==8) 
			{
				InsertTableRows (hstretchPanel, STRETCH_TABLE, range.top, 1, VAL_CELL_STRING);   //插入一行
				SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, range.top, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);  //行高设为可调
				SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, range.top, ATTR_ROW_HEIGHT, 30);	 //行高设为30
				SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, range.top, ATTR_LABEL_FONT, VAL_MENU_FONT);   //行标签字体
				SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, range.top, ATTR_LABEL_POINT_SIZE, 12);		  //行标签字号
				GetNumTableRows (hstretchPanel, STRETCH_TABLE, &row);   //获取行数
				for(int i=1;i<row+1;i++)	  //重新编号
				{
					SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, i, ATTR_USE_LABEL_TEXT, 1);
					SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, i, ATTR_LABEL_TEXT, a[i-1]);
				}
			}
			
			break;
	}
	return 0;
}

int CVICALLBACK InsblwCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			Rect range;
			int row;
			GetTableSelection (hstretchPanel, STRETCH_TABLE, &range);
			if(range.left==1&range.width==8)
			{
				InsertTableRows (hstretchPanel, STRETCH_TABLE, range.top+1, 1, VAL_CELL_STRING);
				SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, range.top+1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE); 
				SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, range.top+1, ATTR_ROW_HEIGHT, 30);
				SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, range.top+1, ATTR_LABEL_FONT, VAL_MENU_FONT);
				SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, range.top+1, ATTR_LABEL_POINT_SIZE, 12);
				GetNumTableRows (hstretchPanel, STRETCH_TABLE, &row);
				for(int i=1;i<row+1;i++)
				{
					SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, i, ATTR_USE_LABEL_TEXT, 1);
					SetTableRowAttribute (hstretchPanel, STRETCH_TABLE, i, ATTR_LABEL_TEXT, a[i-1]);
				}
			}
			
			break;

	}
	return 0;
}
