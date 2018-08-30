//==============================================================================
//
// Title:		Protocol.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/9 at 9:58:35 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Protocol_H__
#define __Protocol_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
#define DEFAULT_ADDR1 0x01 
#define DEFAULT_ADDR2 0x02 
		
#define SA31_UART_TX_LEN 30
#define SA31_UART_RX_LEN 20


//==============================================================================
// Types
typedef union										//float union
{
	
	unsigned char num_uchar[4]; 
	float num_float;
	
}Float_Union_Data;
enum TestCmd
{
	CMD_START=0x11,
	CMD_PAUSE=0x12,
	CMD_STOP=0x13,
	CMD_CONTINUE=0x14
};
enum TestMode
{
	CALIBRATION=0,
	NO_SWEEP_IV=1,
	NO_SWEEP_VI=2,
	NO_SWEEP_IT=3,
	NO_SWEEP_RT=4
};
typedef struct
{
	unsigned char devAddr;
	enum TestCmd testCmd;
	enum TestMode testMode;
	unsigned char outputConnection;
	int Voltage_Start;									//start1
	int Voltage_Stop;									//stop1
	int Voltage_Step;									//step1
	int Current_Start;									//start2
	int Current_Stop;									//stop2
	int Current_Step;									//step2
	unsigned int quietTime;
	unsigned int timeStep;
	unsigned int runTime;								//effective only under R-t and I-t mode
	unsigned int sampleRate;
	unsigned int sampleNumber;
	int rangeMode;
	unsigned char maxRange;
	unsigned char minRange;
}TestParaTypeDef;
		
typedef struct
{
	unsigned char rxDevAddr;						//received Device Address
	unsigned char rxStopSign;						//received Stop Sign 0x00 nonstop 0x01 curve stop 0x02 test stop
	
	int rx_Theory_voltaget;							//���۵�ѹ
	int rx_Theory_current;							//���۵���
	
	Float_Union_Data rx_voltage;					//��ǰ�ɼ���ѹ
	Float_Union_Data rx_current;					//��ǰ�ɼ����� 
	Float_Union_Data rx_Default;					//Ĭ������
	unsigned char rangeSelect;
	
	
}RxDataTypeDef;

typedef struct
{
	int panelHandle;
	int VdStartID;									//voltage drain start
	int VdStopID;									//voltage drain stop
	int VdStepID;									//voltage drain step
	int VgStartID;									//voltage gate start
	int VgStopID;									//voltage gate stop
	int VgStepID;									//voltage gate step
	
}ExpPanelTypeDef;


extern unsigned char measUartTxBuf1[32];
extern unsigned char measUartRxBuf1[500];

extern unsigned char measUartTxBuf2[32];
extern unsigned char measUartRxBuf2[500];


//==============================================================================
// External variables
extern TestParaTypeDef TestPara1;  
extern TestParaTypeDef TestPara2;

extern unsigned char select_Addr1;   //���û�ѡ���Ƿ�ʹ�ô� Դ�� 1 	  Ĭ��	0x01 Ϊ ѡ�У�0x00Ϊ��ѡ�У���ʹ��Դ�� 1 ���в���
extern unsigned char select_Addr2;   //���û�ѡ���Ƿ�ʹ�ô� Դ�� 2	  Ĭ��	0x02 Ϊ ѡ�У�0x00Ϊ��ѡ�У���ʹ��Դ�� 2 ���в���


extern unsigned char comSelect;				//Serial Com Number
extern unsigned char CGS_comSelect;				//Serial Com Number


//==============================================================================
// Global functions

void PrepareCfgTxData(TestParaTypeDef* pTestPara1,TestParaTypeDef* pTestPara2,unsigned char devAddr1, unsigned char devAddr2,unsigned char expType, unsigned char* measUartTxBuf1, unsigned char* measUartTxBuf2);
void ProtocolCfg(unsigned char comSelect, unsigned char devAddr1, unsigned char devAddr2,unsigned char expType, unsigned char* pmeasUartTxBuf1,unsigned char* pmeasUartTxBuf2);
void ProtocolRun(unsigned char comSelect, unsigned char devAddr1, unsigned char devAddr2, unsigned char*  measUartTxBuf1, unsigned char* measUartTxBuf2);
void ProtocolStop(unsigned char comSelect, unsigned char devAddr1, unsigned char devAddr2, unsigned char* measUartTxBuf1, unsigned char* measUartTxBuf2); 
void ProtocolQuery(unsigned char comSelect, unsigned char devAddr1,unsigned char devAddr2, unsigned char* measUartTxBuf1, unsigned char* measUartTxBuf2);
void ProtocolCalibrate(unsigned char comSelect, unsigned char devAddr1, unsigned char* measUartTxBuf1, unsigned char devAddr2, unsigned char* measUartTxBuf2);
void ProtocolGetData(unsigned char* pUartRxBuf, RxDataTypeDef* pRxData1, RxDataTypeDef* pRxData2);
      

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Protocol_H__ */
