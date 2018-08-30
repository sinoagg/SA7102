//==============================================================================
//
// Title:		table.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/20 at 10:36:04 by �� ��.
// Copyright:	���ɹ������ѧ. All Rights Reserved.
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
	int column;									    //��
	int column_width;								//�п�  
	int row;										//��
	
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
