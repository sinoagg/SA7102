#include "TableData.h"

//#include "Table.h"
#include <userint.h>

#include "LoadPanel.h"
#include "table.h"

//==============================================================================
//
// Title:		Table.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/19 at 22:18:03 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
//Table_TypeDef Table_ATTR;

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return

//char ABC[11][20] ={"A","B","C","D","E","F","G","H","I","J","K"};

//char Table_title_IV[11][20] ={"Current(A)","Voltage(V)","Current(A)","Voltage(V)"};
//char Table_title_VI[11][20] ={"Current(A)","Voltage(V)","Current(A)","Voltage(V)"}; 
//char Table_title_IT[11][20] ={"Current(A)","Time(S)","Current(A)","Time(S)"};

/*


	���ܣ�ɾ����������


*/

void DeleteTabble_Row_Columns()
{
	 DeleteTableRows (tablePanel, TABLE_TABLE1, 1, -1);
	 DeleteTableColumns (tablePanel, TABLE_TABLE1, 1, -1);		//ɾ����������
}

void Table_init(char table_title_IV[][20], int column, column_width)
{						    
			
			InsertTableColumns(tablePanel,TABLE_TABLE1,1,column,VAL_CELL_STRING);              //����в�������� 
			InsertTableRows (tablePanel,TABLE_TABLE1 ,-1 , 1, VAL_CELL_STRING);				      		  //����1�� 
			for(int i=1;i<column+1;i++)
			{
			SetTableColumnAttribute(tablePanel,TABLE_TABLE1,i,ATTR_USE_LABEL_TEXT,1);                     //��������
			SetTableColumnAttribute(tablePanel,TABLE_TABLE1,i,ATTR_COLUMN_WIDTH,column_width); 			  //�����п�
			SetTableColumnAttribute(tablePanel, TABLE_TABLE1, i, ATTR_LABEL_TEXT, ABC[i-1]);             //�б��
		    SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (i, 1), table_title_IV[i-1]);	          //�ֱ����ñ��� 
		   	//SetTableColumnAttribute(tablePanel, TABLE_TABLE1, i, ATTR_LABEL_TEXT, table_title_IV[i-1]); 

			
			}
			

}
int CVICALLBACK COMMANDBUTTON_Back (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
  
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			
			//Table_ATTR.column = 4 ;   		//����
			//Table_ATTR.column_width = 300;  //�п�
			//Table_init(Table_title_IT, Table_ATTR.column, Table_ATTR.column_width );
			//
			//SetCtrlAttribute (tablePanel, TABLE_COMMANDBUTTON_2, ATTR_DIMMED,0);       
			//SetCtrlAttribute (tablePanel, TABLE_COMMANDBUTTON,  ATTR_DIMMED,1);          

			break;
	}
	return 0;
}


//int CVICALLBACK COMMANDBUTTON_2_Callback (int panel, int control, int event,
//		void *callbackData, int eventData1, int eventData2)
//{
//	switch (event)
//	{
//		case EVENT_LEFT_CLICK_UP:
//			
//			
//						    int row;
//   	                  		InsertTableRows (tablePanel,TABLE_TABLE1 ,-1, 1, VAL_CELL_NUMERIC);				          //����1�� 
//							GetNumTableRows (tablePanel, TABLE_TABLE1, &row); 										  //�õ���ǰ����
//						    SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (1,row ), 100.0);
//							SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (2,row ), 200.0); 
//							SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (3,row ), 300.0); 
//							SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (4,row ), 400.0); 
//			

//			break;
//	}
//	return 0;
//}			
/*


	���ܣ��ı䵥Ԫ���ɫ


*/
int CVICALLBACK CHECKBOX_Callback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{   int temp; 
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			GetCtrlVal(tablePanel,TABLE_CHECKBOX, &temp);
			
			if(temp == 1)
			{
			
			   GetNumTableRows (tablePanel, TABLE_TABLE1, &temp);
			   
			    for (int rowIndex = 1; rowIndex <= temp; rowIndex++)
				{
					   if ((rowIndex % 2) == 1)
		            SetTableCellRangeAttribute (tablePanel, TABLE_TABLE1,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, VAL_WHITE);
		        	else
		            SetTableCellRangeAttribute (tablePanel, TABLE_TABLE1,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, 0xD0D0D0L);
				
				}
			}
			else
			{
				GetNumTableRows (tablePanel, TABLE_TABLE1, &temp);
			    for (int rowIndex = 1; rowIndex <= temp; rowIndex++)
				{
					   
		            SetTableCellRangeAttribute (tablePanel, TABLE_TABLE1,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, VAL_WHITE);
				
				}
			}

			break;
	}
	return 0;
}

//int CVICALLBACK COMMANDBUTTON_3_Callback (int panel, int control, int event,
//		void *callbackData, int eventData1, int eventData2)
//{
//	switch (event)
//	{
//		case EVENT_LEFT_CLICK_UP:
//			
//			DeleteTabble_Row_Columns();
//			SetCtrlAttribute (tablePanel, TABLE_COMMANDBUTTON_2, ATTR_DIMMED,1);       
//			SetCtrlAttribute (tablePanel, TABLE_COMMANDBUTTON,  ATTR_DIMMED,0);          
//			

//			break;
//	}
//	return 0;
//}
