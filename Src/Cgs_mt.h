//==============================================================================
//
// Title:		Cgs_mt.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/31 at 15:52:21 by �� ��.
// Copyright:	���ɹ������ѧ. All Rights Reserved.
//
//==============================================================================

#ifndef __Cgs_mt_H__
#define __Cgs_mt_H__

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
	unsigned char rxDevAddr;						//received Device Address

	unsigned int pressure;					//ѹ��ֵ
	
	int heating_stage_temp; 				//��̨�¶�
	
	unsigned int Evaporation_temp;			//�����¶�
	
	unsigned int environmental_humidity;	//����ʪ��
	
	int environmental_temp;					//�����¶� 

}Rx_CGS_DataTypeDef;
//==============================================================================
// External variables
extern unsigned char meas_CGS_UartTxBuf[];
extern unsigned char meas_CGS_UartRxBuf[];
//==============================================================================
// Global functions
void Read_CGS_Value(unsigned char comSelect);
void ProtocolGet_CGS_Data(unsigned char* meas_CGS_UartRxBuf, Rx_CGS_DataTypeDef* Rx_CGS_Data);	//Get data from UART Rx Buffer
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Cgs_mt_H__ */
