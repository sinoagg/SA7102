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
int val; 
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

int CVICALLBACK ModeCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			GetCtrlAttribute (hstretchPanel, STRETCH_STRAINTABLE, ATTR_VISIBLE, &val);
			if(val)
			{
				SetCtrlAttribute (hstretchPanel, STRETCH_STRAINTABLE, ATTR_VISIBLE, 0);
				SetCtrlAttribute (hstretchPanel, STRETCH_LOADTABLE, ATTR_VISIBLE, 1);
				SetCtrlVal (hstretchPanel, STRETCH_MODE, "  Strain");
			}
			else
			{
				SetCtrlAttribute (hstretchPanel, STRETCH_STRAINTABLE, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hstretchPanel, STRETCH_LOADTABLE, ATTR_VISIBLE, 0);
				SetCtrlVal (hstretchPanel, STRETCH_MODE, "  Load");
			}
			break;

	}
	return 0;
}

int CVICALLBACK DeleteCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
		    Rect range;
			int row;
			GetCtrlAttribute (hstretchPanel, STRETCH_STRAINTABLE, ATTR_VISIBLE, &val);
			if(val)
			{
				GetTableSelection (hstretchPanel, STRETCH_STRAINTABLE, &range);
				if(range.left==1&range.width==6)
				DeleteTableRows (hstretchPanel, STRETCH_STRAINTABLE, range.top, range.height); 
				GetNumTableRows (hstretchPanel, STRETCH_STRAINTABLE, &row);   //��ȡ����
				for(int i=1;i<row+1;i++)	  //���±��
				{
					SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, i, ATTR_USE_LABEL_TEXT, 1);
					SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, i, ATTR_LABEL_TEXT, a[i-1]);
				}
			}
			else
			{
				GetTableSelection (hstretchPanel, STRETCH_LOADTABLE, &range);
				if(range.left==1&range.width==6)
				DeleteTableRows (hstretchPanel, STRETCH_LOADTABLE, range.top, range.height); 
				GetNumTableRows (hstretchPanel, STRETCH_LOADTABLE, &row);   //��ȡ����
				for(int i=1;i<row+1;i++)	  //���±��
				{
					SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, i, ATTR_USE_LABEL_TEXT, 1);
					SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, i, ATTR_LABEL_TEXT, a[i-1]);
				}
				
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
			GetCtrlAttribute (hstretchPanel, STRETCH_STRAINTABLE, ATTR_VISIBLE, &val);
			if(val)
			{
				GetTableSelection (hstretchPanel, STRETCH_STRAINTABLE, &range);	 //��ȡ��ǰѡ�з�Χ
				if(range.left==1&range.width==6) 
				{
					InsertTableRows (hstretchPanel, STRETCH_STRAINTABLE, range.top, 1, VAL_CELL_STRING);   //����һ��
					SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, range.top, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);  //�и���Ϊ�ɵ�
					SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, range.top, ATTR_ROW_HEIGHT, 30);	 //�и���Ϊ30
					SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, range.top, ATTR_LABEL_FONT, VAL_MENU_FONT);   //�б�ǩ����
					SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, range.top, ATTR_LABEL_POINT_SIZE, 12);		  //�б�ǩ�ֺ�
					GetNumTableRows (hstretchPanel, STRETCH_STRAINTABLE, &row);   //��ȡ����
					for(int i=1;i<row+1;i++)	  //���±��
					{
						SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, i, ATTR_USE_LABEL_TEXT, 1);
						SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, i, ATTR_LABEL_TEXT, a[i-1]);
					}
				}
			}
			else
			{
				GetTableSelection (hstretchPanel, STRETCH_LOADTABLE, &range);	 //��ȡ��ǰѡ�з�Χ
				if(range.left==1&range.width==6) 
				{
					InsertTableRows (hstretchPanel, STRETCH_LOADTABLE, range.top, 1, VAL_CELL_STRING);   //����һ��
					SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, range.top, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);  //�и���Ϊ�ɵ�
					SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, range.top, ATTR_ROW_HEIGHT, 30);	 //�и���Ϊ30
					SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, range.top, ATTR_LABEL_FONT, VAL_MENU_FONT);   //�б�ǩ����
					SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, range.top, ATTR_LABEL_POINT_SIZE, 12);		  //�б�ǩ�ֺ�
					GetNumTableRows (hstretchPanel, STRETCH_LOADTABLE, &row);   //��ȡ����
					for(int i=1;i<row+1;i++)	  //���±��
					{
						SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, i, ATTR_USE_LABEL_TEXT, 1);
						SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, i, ATTR_LABEL_TEXT, a[i-1]);
					}
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
			GetCtrlAttribute (hstretchPanel, STRETCH_STRAINTABLE, ATTR_VISIBLE, &val);
			if(val)
			{
				GetTableSelection (hstretchPanel, STRETCH_STRAINTABLE, &range);
				if(range.left==1&range.width==6)
				{
					InsertTableRows (hstretchPanel, STRETCH_STRAINTABLE, range.top+1, 1, VAL_CELL_STRING);
					SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, range.top+1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE); 
					SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, range.top+1, ATTR_ROW_HEIGHT, 30);
					SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, range.top+1, ATTR_LABEL_FONT, VAL_MENU_FONT);
					SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, range.top+1, ATTR_LABEL_POINT_SIZE, 12);
					GetNumTableRows (hstretchPanel, STRETCH_STRAINTABLE, &row);
					for(int i=1;i<row+1;i++)
					{
						SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, i, ATTR_USE_LABEL_TEXT, 1);
						SetTableRowAttribute (hstretchPanel, STRETCH_STRAINTABLE, i, ATTR_LABEL_TEXT, a[i-1]);
					}
				}
			}
			else
			{
				GetTableSelection (hstretchPanel, STRETCH_LOADTABLE, &range);
				if(range.left==1&range.width==6)
				{
					InsertTableRows (hstretchPanel, STRETCH_LOADTABLE, range.top+1, 1, VAL_CELL_STRING);
					SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, range.top+1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE); 
					SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, range.top+1, ATTR_ROW_HEIGHT, 30);
					SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, range.top+1, ATTR_LABEL_FONT, VAL_MENU_FONT);
					SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, range.top+1, ATTR_LABEL_POINT_SIZE, 12);
					GetNumTableRows (hstretchPanel, STRETCH_LOADTABLE, &row);
					for(int i=1;i<row+1;i++)
					{
						SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, i, ATTR_USE_LABEL_TEXT, 1);
						SetTableRowAttribute (hstretchPanel, STRETCH_LOADTABLE, i, ATTR_LABEL_TEXT, a[i-1]);
					}
				}
			}
			break;

	}
	return 0;
}


