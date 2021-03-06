//==============================================================================
//
// Title:		table.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/20 at 10:36:04 by 斌 何.
// Copyright:	内蒙古民族大学. All Rights Reserved.
//
//==============================================================================

#ifndef __table_H__
#define __table_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	int column;									    //列
	int column_width;								//列宽  
	int row;										//行
	
}Table_TypeDef;


extern Table_TypeDef Table_Date;
//extern Table_TypeDef Table_ATTR; 
extern char ABC[11][20];
		
//==============================================================================
// External variables

//==============================================================================
// Global functions

void Table_init(char table_title_IV[][20], int column, column_width);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __table_H__ */
