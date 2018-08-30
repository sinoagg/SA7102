//==============================================================================
//
// Title:		Plot.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/16 at 17:35:20 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Plot_H__
#define __Plot_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Graph.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions
int PlotCurve(Graph_TypeDef* pGraph, int graphDispPanel, int control);
int PlotCurve_Temp(Graph_TypeDef* pGraph_Temp, int graphDispPanel, int control);
void temp_hum_pre_display();

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Plot_H__ */
