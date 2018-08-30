//==============================================================================
//
// Title:		SetPanelCB.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/27 at 11:32:39 by �� ��.
// Copyright:	���ɹ������ѧ. All Rights Reserved.
//
//==============================================================================

#ifndef __SetPanelCB_H__
#define __SetPanelCB_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
#define GRAPH1 0
#define GRAPH2 1
#define CURVE1 0
#define CURVE2 1  
#define CURVE3 2  
//==============================================================================
// Types

//==============================================================================
// External variables
extern int smu1ClrOld;
extern int smu2ClrOld;
extern int graph2Color1Old;
extern int graph2Color2Old;
extern int graph2Color3Old;

extern int graph2tempclr;
extern int graph2humclr; 
extern int graph2preclr;
extern int smu1Clr;
extern int smu2Clr;
extern char ProjectSavePath[512];	   //���ع���Ŀ¼Dir  
//==============================================================================
// Global functions

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __SetPanelCB_H__ */
