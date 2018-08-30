//==============================================================================
//
// Title:		Protocol.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/9 at 9:58:35 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files


#include <utility.h>
#include <userint.h>
#include "Protocol.h"
#include "LoadPanel.h"
#include "ResultMenuPanel.h"
#include "IdVdsPanel.h"
#include "IdVgsPanel.h"
#include "I_T_Panel.h"
//#include "pTestPara1Panel.h"
#include <rs232.h>
#include "table.h"
#include "Plot.h"
//==============================================================================
// Constants

//==============================================================================
// Types
enum MsgType
{
	MSG_TYPE_NULL=0,
	MSG_TYPE_SETTING=0x11,		//��������				
	MSG_TYPE_RUN=0x12,			//��ʼ����
	MSG_TYPE_STOP=0x13,			//ֹͣ����
	MSG_TYPE_QUERY=0x14,		//��ѯ����
	MSG_TYPE_CALIBRATION=0x15,	//У׼����
	MSG_TYPE_REPORT_ID=0xFF   	//ID��ѯ����
};
//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
TestParaTypeDef TestPara1;  
TestParaTypeDef TestPara2;

unsigned char select_Addr1 = 0X01;   //���û�ѡ���Ƿ�ʹ�ô� Դ�� 1 	  Ĭ��	0x01 Ϊ ѡ�У�0x00Ϊ��ѡ�У���ʹ��Դ�� 1 ���в���
unsigned char select_Addr2 = 0X00;   //���û�ѡ���Ƿ�ʹ�ô� Դ�� 2	  Ĭ��	0x02 Ϊ ѡ�У�0x00Ϊ��ѡ�У���ʹ��Դ�� 2 ���в���




//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return

static unsigned char GetXorCheckVal(unsigned char* pUartBuf, unsigned char lenth)//����У��ֵ
{
	unsigned char i, xorCheck=0;
	for(i=0;i<lenth;i++)
		xorCheck^=*(pUartBuf+i);	
	return xorCheck;	
}
/*


	���ܣ��ֱ���  ��ַ1 ��ַ2 ���� ��������


*/
void PrepareCfgTxData(TestParaTypeDef* pTestPara1,TestParaTypeDef* pTestPara2,unsigned char devAddr1, unsigned char devAddr2, unsigned char expType, unsigned char* measUartTxBuf1,unsigned char* measUartTxBuf2)	//Make config info to UART Tx Buffer
{
	if(devAddr1 == 0x01 )
	{
	*measUartTxBuf1=devAddr1; 		//�豸��ַ
	*(measUartTxBuf1+1)=0x11;		//��������  0X11����  0X12��ʼ		0X13ֹͣ	0X14��ѯ	0X15У׼	0XFF��ѯ
	*(measUartTxBuf1+2)=expType;	//��������
	*(measUartTxBuf1+3)=0x00;		//���� 
	
	//��Դ�� 1 �� ��ѹ ��ʼ ���� ������� ����������׼������
	*(measUartTxBuf1+4)=(unsigned char)(pTestPara1->Voltage_Start >> 8) ;	   
	*(measUartTxBuf1+5)=(unsigned char)(pTestPara1->Voltage_Start & 0xFF);
	*(measUartTxBuf1+6)=(unsigned char)(pTestPara1->Voltage_Stop >> 8) ;
	*(measUartTxBuf1+7)=(unsigned char)(pTestPara1->Voltage_Stop & 0xFF );
	*(measUartTxBuf1+8)=(unsigned char)(pTestPara1->Voltage_Step >> 8 ) ;
	*(measUartTxBuf1+9)=(unsigned char)(pTestPara1->Voltage_Step & 0xFF);
	
	//��Դ�� 1 �� ���� ��ʼ ���� ������� ����������׼������ 
	*(measUartTxBuf1+10)=(unsigned char)(pTestPara1->Current_Start >> 8 );	    
	*(measUartTxBuf1+11)=(unsigned char)(pTestPara1->Current_Start & 0xFF);
	*(measUartTxBuf1+12)=(unsigned char)(pTestPara1->Current_Stop >> 8) ;
	*(measUartTxBuf1+13)=(unsigned char)(pTestPara1->Current_Stop & 0xFF );
	*(measUartTxBuf1+14)=(unsigned char)(pTestPara1->Current_Step >> 8) ;
	*(measUartTxBuf1+15)=(unsigned char)(pTestPara1->Current_Step & 0xFF);
	
	//��Դ�� 1 �� �������� ����������׼������
	*(measUartTxBuf1+16)=(unsigned char)(pTestPara1->quietTime >>8);
	*(measUartTxBuf1+17)=(unsigned char)(pTestPara1->quietTime &0xFF);
	*(measUartTxBuf1+18)=(unsigned char)(pTestPara1->timeStep >>8);
	*(measUartTxBuf1+19)=(unsigned char)(pTestPara1->timeStep&0xFF);
	*(measUartTxBuf1+20)=(unsigned char)(pTestPara1->runTime >>8);
	*(measUartTxBuf1+21)=(unsigned char)(pTestPara1->runTime&0xFF);
	*(measUartTxBuf1+22)=(unsigned char)(pTestPara1->sampleRate >>8);
	*(measUartTxBuf1+23)=(unsigned char)(pTestPara1->sampleRate&0xFF);
	*(measUartTxBuf1+24)=(unsigned char)(pTestPara1->sampleNumber >>8);
	*(measUartTxBuf1+25)=(unsigned char)(pTestPara1->sampleNumber&0xFF);
	*(measUartTxBuf1+26)=(unsigned char)(pTestPara1->rangeMode&0xFF);
	
	
	*(measUartTxBuf1+27)=9;  //����ʹ�����λ    	pTestPara1->maxRange 
	*(measUartTxBuf1+28)=1;  //����ʹ����С��λ 	pTestPara1->minRange 
	
	*(measUartTxBuf1+SA31_UART_TX_LEN-1) = GetXorCheckVal(measUartTxBuf1, SA31_UART_TX_LEN-1); 
	}
	if(devAddr2 == 0x02)
	{ 
	*measUartTxBuf2=devAddr2; 		//�豸��ַ
	*(measUartTxBuf2+1)=0x11;		//��������  0X11����  0X12��ʼ		0X13ֹͣ	0X14��ѯ	0X15У׼	0XFF��ѯ
	*(measUartTxBuf2+2)=expType;	//��������
	*(measUartTxBuf2+3)=0x00;		//���� 
	
	//��Դ�� 2 �� ��ѹ ��ʼ ���� ������� ����������׼������ 													  
	*(measUartTxBuf2+4)=(unsigned char)(pTestPara2->Voltage_Start >> 8);	   
	*(measUartTxBuf2+5)=(unsigned char)(pTestPara2->Voltage_Start & 0xFF);
	*(measUartTxBuf2+6)=(unsigned char)(pTestPara2->Voltage_Stop >> 8) ;
	*(measUartTxBuf2+7)=(unsigned char)(pTestPara2->Voltage_Stop & 0xFF );
	*(measUartTxBuf2+8)=(unsigned char)(pTestPara2->Voltage_Step >> 8 ) ;
	*(measUartTxBuf2+9)=(unsigned char)(pTestPara2->Voltage_Step & 0xFF);

	
	//��Դ�� 2 �� ���� ��ʼ ���� ������� ����������׼������
	*(measUartTxBuf2+10)=(unsigned char)(pTestPara2->Current_Start >> 8 );	    //03e8
	*(measUartTxBuf2+11)=(unsigned char)(pTestPara2->Current_Start & 0xFF);
	*(measUartTxBuf2+12)=(unsigned char)(pTestPara2->Current_Stop >> 8) ;
	*(measUartTxBuf2+13)=(unsigned char)(pTestPara2->Current_Stop & 0xFF );
	*(measUartTxBuf2+14)=(unsigned char)(pTestPara2->Current_Step >> 8) ;
	*(measUartTxBuf2+15)=(unsigned char)(pTestPara2->Current_Step & 0xFF);
	
	//��Դ�� 2  �� �������� ����������׼������
	*(measUartTxBuf2+16)=(unsigned char)(pTestPara2->quietTime >>8);
	*(measUartTxBuf2+17)=(unsigned char)(pTestPara2->quietTime&0xFF);
	*(measUartTxBuf2+18)=(unsigned char)(pTestPara2->timeStep >>8);
	*(measUartTxBuf2+19)=(unsigned char)(pTestPara2->timeStep&0xFF);
	*(measUartTxBuf2+20)=(unsigned char)(pTestPara2->runTime >>8);
	*(measUartTxBuf2+21)=(unsigned char)(pTestPara2->runTime&0xFF);
	*(measUartTxBuf2+22)=(unsigned char)(pTestPara2->sampleRate >>8);
	*(measUartTxBuf2+23)=(unsigned char)(pTestPara2->sampleRate&0xFF);
	*(measUartTxBuf2+24)=(unsigned char)(pTestPara2->sampleNumber >>8);
	*(measUartTxBuf2+25)=(unsigned char)(pTestPara2->sampleNumber&0xFF);
	*(measUartTxBuf2+26)=(unsigned char)(pTestPara2->rangeMode&0xFF); 
	
	*(measUartTxBuf2 + 27)=9;  //����ʹ�����λ
	*(measUartTxBuf2 + 28)=1;  //����ʹ����С��λ
	
	*(measUartTxBuf2+SA31_UART_TX_LEN-1) = GetXorCheckVal(measUartTxBuf2, SA31_UART_TX_LEN-1); //У��λ
	}
	

}

/*


	1,�ֱ���1��2�Ű��ӷ���    ��ʼ����
	2,���ӵ�ַ����ѡ��ʹ�õ�Դ����˫Դ��


*/
void ProtocolRun(unsigned char comSelect, unsigned char devAddr1, unsigned char devAddr2, unsigned char* measUartTxBuf1, unsigned char* measUartTxBuf2)
{
	if(devAddr1 == 0x01)
	{
			*measUartTxBuf1 = devAddr1;
			*(measUartTxBuf1+1) = MSG_TYPE_RUN;
			*(measUartTxBuf1+SA31_UART_TX_LEN-1) = GetXorCheckVal(measUartTxBuf1, SA31_UART_TX_LEN-1);
			ComWrt(comSelect, (const char*)measUartTxBuf1, 30);
	}
	Delay(0.2);
	if(devAddr2 == 0x02)
	{
			*measUartTxBuf2=devAddr2;
			*(measUartTxBuf2+1)=MSG_TYPE_RUN;
			*(measUartTxBuf2+29)=GetXorCheckVal(measUartTxBuf2, SA31_UART_TX_LEN-1);
			ComWrt(comSelect, (const char*)measUartTxBuf2, 30);
	}
}
/*

	1,�ֱ���1��2�Ű��ӷ���    ֹͣ����
	2,���ӵ�ַ����ѡ��ʹ�õ�Դ����˫Դ��

*/

void ProtocolStop(unsigned char comSelect, unsigned char devAddr1, unsigned char devAddr2, unsigned char* measUartTxBuf1, unsigned char* measUartTxBuf2)
{
	if(devAddr1 == 0x01)
	{
			*measUartTxBuf1 = devAddr1;
			*(measUartTxBuf1+1) = MSG_TYPE_STOP;
			*(measUartTxBuf1+29) = GetXorCheckVal(measUartTxBuf1, SA31_UART_TX_LEN-1);
			ComWrt(comSelect, (const char*)measUartTxBuf1, 30);
	}
	Delay(0.01);
	if(devAddr2 == 0x02)
	{
		*measUartTxBuf2 = devAddr2;
		*(measUartTxBuf2+1) = MSG_TYPE_STOP;
		*(measUartTxBuf2+29) = GetXorCheckVal(measUartTxBuf2, SA31_UART_TX_LEN-1);
		ComWrt(comSelect, (const char*)measUartTxBuf2, 30);
	}
}
/*


	1,�ֱ���1��2�Ű��ӷ���    ��ѯ����
	2,���ӵ�ַ����ѡ��ʹ�õ�Դ����˫Դ��


*/
void ProtocolQuery(unsigned char comSelect, unsigned char devAddr1,unsigned char devAddr2, unsigned char* measUartTxBuf1, unsigned char* measUartTxBuf2)
{
	if(devAddr1 == 0x01) 
	{
		*measUartTxBuf1=devAddr1;
		*(measUartTxBuf1+1)=0x14;
		*(measUartTxBuf1+29)=GetXorCheckVal(measUartTxBuf1, SA31_UART_TX_LEN-1);
		ComWrt(comSelect, (const char*)measUartTxBuf1, 30);
	}
	Delay(0.2); 
	if(devAddr2 == 0x02) 
	{
		*measUartTxBuf2=devAddr2;
		*(measUartTxBuf2+1)=0x14;
		*(measUartTxBuf2 + 29) = GetXorCheckVal(measUartTxBuf2, SA31_UART_TX_LEN-1);
		ComWrt(comSelect, (const char*)measUartTxBuf2, 30);
	
	}
}
/*


	1,�ֱ���1��2�Ű��ӷ���    У׼����
	2,���ӵ�ַ����ѡ��ʹ�õ�Դ����˫Դ��


*/
void ProtocolCalibrate(unsigned char comSelect, unsigned char devAddr1, unsigned char* measUartTxBuf1, unsigned char devAddr2, unsigned char* measUartTxBuf2)
{
	if(devAddr1 == 0x01) 
	{
		*measUartTxBuf1=devAddr1;
		*(measUartTxBuf1+1)=0x15;
		*(measUartTxBuf1+27)=GetXorCheckVal(measUartTxBuf1, SA31_UART_TX_LEN-1);
		ComWrt(comSelect, (const char*)measUartTxBuf1, 28);
	}
	if(devAddr2 == 0x02) 
	{
		*measUartTxBuf2=devAddr2;
		*(measUartTxBuf2+1)=0x15;
		*(measUartTxBuf2 + 27)=GetXorCheckVal(measUartTxBuf2, SA31_UART_TX_LEN-1);
		ComWrt(comSelect, (const char*)measUartTxBuf2, 28);
	}
}
/*


	1,�ֱ�������������� 1��2�Ű��ӵ����ݡ�
	2,���жϺ�õ������ݷֱ���뵽��ӦԴ��������Ľṹ���С�


*/
void ProtocolGetData(unsigned char* pUartRxBuf, RxDataTypeDef* pRxData1, RxDataTypeDef* pRxData2)	//Get data from UART Rx Buffer
{
	unsigned char Addr;
	Addr = *pUartRxBuf;  //��ȡ �豸 ��ַ  0X01 1�Ű���   0X02  2�Ű���
	
	if(Addr == 0x01)
	{
		pRxData1->rxDevAddr=*pUartRxBuf; //1�Ű����豸��ַ 
		pRxData1->rxStopSign=*(pUartRxBuf+1);
		
		if(*(pUartRxBuf+2) & 0x80 )
		{
			pRxData1->rx_Theory_voltaget = (((int)(*(pUartRxBuf+2) << 8))|*(pUartRxBuf+3)) - 65536;
		}
		else
		{
			pRxData1->rx_Theory_voltaget = ((int)(*(pUartRxBuf+2) << 8))|*(pUartRxBuf+3); 
		}
	
		if(*(pUartRxBuf+4) & 0x80 ) 
		{
			pRxData1->rx_Theory_current =  (((int)(*(pUartRxBuf+4) << 8))|*(pUartRxBuf+5)) - 65536;   
		}
		else
		{
			pRxData1->rx_Theory_current =  ((int)(*(pUartRxBuf+4) << 8))|*(pUartRxBuf+5);
		}

	
		pRxData1->rx_voltage.num_uchar[3] = *(pUartRxBuf+6);
		pRxData1->rx_voltage.num_uchar[2] = *(pUartRxBuf+7); 
		pRxData1->rx_voltage.num_uchar[1] = *(pUartRxBuf+8); 
		pRxData1->rx_voltage.num_uchar[0] = *(pUartRxBuf+9);
	
		pRxData1->rx_current.num_uchar[3] = *(pUartRxBuf+10); 
		pRxData1->rx_current.num_uchar[2] = *(pUartRxBuf+11);
		pRxData1->rx_current.num_uchar[1] = *(pUartRxBuf+12);
		pRxData1->rx_current.num_uchar[0] = *(pUartRxBuf+13);
	
		pRxData1->rx_Default.num_uchar[3] = *(pUartRxBuf+14); 
		pRxData1->rx_Default.num_uchar[2] = *(pUartRxBuf+15);
		pRxData1->rx_Default.num_uchar[1] = *(pUartRxBuf+16);
		pRxData1->rx_Default.num_uchar[0] = *(pUartRxBuf+17);
		
		pRxData1->rangeSelect = *(pUartRxBuf+18);
	}
	if(Addr == 0x02)
	{
		pRxData2->rxDevAddr=*pUartRxBuf; //1�Ű����豸��ַ 
		pRxData2->rxStopSign=*(pUartRxBuf+1);
	
		pRxData2->rx_Theory_voltaget = ((int)(*(pUartRxBuf+2) << 8))|*(pUartRxBuf+3);
		pRxData2->rx_Theory_current =  ((int)(*(pUartRxBuf+4) << 8))|*(pUartRxBuf+5);
	
	
		pRxData2->rx_voltage.num_uchar[3] = *(pUartRxBuf+6);
		pRxData2->rx_voltage.num_uchar[2] = *(pUartRxBuf+7); 
		pRxData2->rx_voltage.num_uchar[1] = *(pUartRxBuf+8); 
		pRxData2->rx_voltage.num_uchar[0] = *(pUartRxBuf+9);
	
		pRxData2->rx_current.num_uchar[3] = *(pUartRxBuf+10); 
		pRxData2->rx_current.num_uchar[2] = *(pUartRxBuf+11);
		pRxData2->rx_current.num_uchar[1] = *(pUartRxBuf+12);
		pRxData2->rx_current.num_uchar[0] = *(pUartRxBuf+13);
	
		pRxData2->rx_Default.num_uchar[3] = *(pUartRxBuf+14); 
		pRxData2->rx_Default.num_uchar[2] = *(pUartRxBuf+15);
		pRxData2->rx_Default.num_uchar[1] = *(pUartRxBuf+16);
		pRxData2->rx_Default.num_uchar[0] = *(pUartRxBuf+17);
		pRxData2->rangeSelect = *(pUartRxBuf+18);
	}
}
