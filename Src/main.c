#include "main.h"
#include "Table.h"
#include <utility.h>
#include "Environment.h"
#include "asynctmr.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>
#include "Protocol.h"   
#include "LoadPanel.h"
#include "MainPanelCb.h"
#include "Graph.h"
#include "Cgs_mt.h"
#include  "Plot.h"
unsigned char comSelect;					//Serial Com Number
unsigned char CGS_comSelect;				//Serial Com Number
unsigned char measUartTxBuf1[32]={0};
unsigned char measUartRxBuf1[500]={0};

unsigned char measUartTxBuf2[32]={0};
unsigned char measUartRxBuf2[500]={0};
float X1 = 0;
float X2 = 0; 
void CVICALLBACK ComCallback(int portNumber ,int eventMask, void * callbackData);
void CVICALLBACK ComCallbackCGS(int portNumber, int eventMask, void * callbackData); 
int CVICALLBACK TimerCallback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);
int CheckPortStatus(unsigned char portNumber, unsigned char uartRxLen, void (*pFunc)(int, int, void*));

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	comSelect = 5;
	CGS_comSelect = 1;
	LoadInitPanel(); 
	CheckPortStatus(comSelect, 20, ComCallback);
	CheckPortStatus(CGS_comSelect, 14, ComCallbackCGS);
	RunUserInterface ();
	DiscardPanel (mainPanel);
	return 0;
}
static int CheckPortStatus(unsigned char portNumber, unsigned char uartRxLen, void (*pFunc)(int, int, void*))
{
	int status;
	status = OpenComConfig(portNumber, "", 115200, 0, 8, 1, 512, 512);	   //Config and Connect serial port
	if(status != 0) 
	{
		MessagePopup("Error","Device unconnected.");
		return -1;
	}
	else
	{
		InstallComCallback (portNumber, LWRS_RECEIVE, uartRxLen, 0, pFunc, 0);   //binding Callback function to serial input data		18 bytes received will calling for an interrupt
		SetCTSMode(portNumber, LWRS_HWHANDSHAKE_OFF);
		FlushInQ(portNumber);	   														//Clear input and output buffer
		FlushOutQ(portNumber);
		return 0;
	}
}
void Getxy(unsigned char *measUartRxBuf, RxDataTypeDef* RxData1, RxDataTypeDef* RxData2) //�жϽ���Դ��1 Դ��2������
{
	int row;
	if( *measUartRxBuf  == 0x01) //�ж��Ƿ��� 01 ��ַ���� ������
	{
        InsertTableRows (tablePanel,TABLE_TABLE1 ,-1, 1, VAL_CELL_NUMERIC);				          //����1�� 
		GetNumTableRows (tablePanel, TABLE_TABLE1, &row); 										  //�õ���ǰ����
		
		if(TestPara1.testMode == NO_SWEEP_IV ) //���ݲ�ͬģʽ ѡ��ͬ��X ������
		{
			*(Graph.pCurveArray->pDotX++) = RxData1->rx_Theory_voltaget;
			*(Graph.pCurveArray->pDotY++) = RxData1->rx_current.num_float;				//get y, set pointer to the next data 
			SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (1,row), *(Graph.pCurveArray->pDotX-1));
			SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (2,row ),*(Graph.pCurveArray->pDotY-1)); 
		}
		if(TestPara1.testMode == NO_SWEEP_VI )
		{
			*(Graph.pCurveArray->pDotX++) = RxData1->rx_Theory_current;
			*(Graph.pCurveArray->pDotY++) = RxData1->rx_current.num_float;				//get y, set pointer to the next data  
		}
		if(TestPara1.testMode == NO_SWEEP_IT )
		{
			*(Graph.pCurveArray->pDotX++) = X1++;
			*(Graph.pCurveArray->pDotY++) = RxData1->rx_current.num_float;				//get y, set pointer to the next data 
			SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (1,row), *(Graph.pCurveArray->pDotX-1));
			SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (2,row ),*(Graph.pCurveArray->pDotY-1)); 
		}
		//if(TestPara1.testMode == NO_SWEEP_VT )
		//		*(Graph.pCurveArray->pDotX++) = RxData1.rx_Theory_voltaget;
		if(TestPara1.testMode == NO_SWEEP_RT )
		{
			*(Graph.pCurveArray->pDotX++) = X1++;		
			*(Graph.pCurveArray->pDotY++) = (TestPara1.Voltage_Start*0.001)/RxData1->rx_current.num_float;				//get y, set pointer to the next data
			SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (1,row), *(Graph.pCurveArray->pDotX-1));
			SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (2,row ),*(Graph.pCurveArray->pDotY-1)); 
		}
		Graph.pCurveArray->numOfDotsToPlot++;				 						//number of dots to plot increase 
	}
	if(*measUartRxBuf  == 0x02) //�ж��Ƿ��� 02 ��ַ���� ������
	{
		if(TestPara2.testMode == NO_SWEEP_IV )
			*((Graph.pCurveArray + 1)->pDotX++) = RxData2->rx_Theory_voltaget;
		
		if(TestPara2.testMode == NO_SWEEP_VI )
			*((Graph.pCurveArray + 1)->pDotX++) = RxData2->rx_Theory_current;
		
		if(TestPara2.testMode == NO_SWEEP_IT )
				*((Graph.pCurveArray + 1)->pDotX++) = X2++;
		
		//if(TestPara2.testMode == NO_SWEEP_VT )
		//	*(Graph.pCurveArray->pDotX++) = RxData2.rx_Theory_voltaget;
		
		if(TestPara2.testMode == NO_SWEEP_RT )
			*((Graph.pCurveArray + 1)->pDotX++) = X2++;
		
		*((Graph.pCurveArray+1)->pDotY++) = RxData2->rx_current.num_float;
		(Graph.pCurveArray+1)->numOfDotsToPlot++;				 					//number of dots to plot increase
	}
}
void CVICALLBACK ComCallback(int portNumber, int eventMask, void * callbackData)
{
	int status;
	int rxNum;																							  
	int i=0;
	RxDataTypeDef RxData1,RxData2;
	RxData1.rxStopSign=0x00; 
	rxNum = GetInQLen(comSelect);  												//��ȡ�����з���������������
	if(rxNum>500) rxNum=500;													//��ֹ�����ڴ淶Χ
	//status = ComRd(comSelect, (char *)measUartRxBuf1, rxNum); 	
	          
	while(rxNum>=UART_RX_LEN)
	{	 
		
		 if((RxData1.rxStopSign == 0x01) || (Graph.pCurveArray->numOfPlotDots == Graph.pCurveArray->numOfTotalDots))//if complete the test, stop the timer
		 {
		 	DiscardAsyncTimer(TimerID);
			rxNum =0;
		 }
		 else
		 {
			status = ComRd(comSelect, (char *)measUartRxBuf1, 20); 				
			ProtocolGetData(measUartRxBuf1+i*UART_RX_LEN, &RxData1,&RxData2);					//get data from uart buffer ,�����ж��Ƿ���Դ��1��2 ���ݣ��ֱ������Ӧ�Ļ�����
			Getxy(&measUartRxBuf1[i*UART_RX_LEN], &RxData1, &RxData2);							//�Ӵ��ڴ�����������ȡ��  X��Y�� ������
			rxNum -=UART_RX_LEN;
		 }
		
	     //status = ComRd(comSelect, (char *)measUartRxBuf1, 20); 				
	     //ProtocolGetData(measUartRxBuf1+i*UART_RX_LEN, &RxData1,&RxData2);					//get data from uart buffer ,�����ж��Ƿ���Դ��1��2 ���ݣ��ֱ������Ӧ�Ļ�����
		 //Getxy(&measUartRxBuf1[i*UART_RX_LEN], &RxData1, &RxData2);							//�Ӵ��ڴ�����������ȡ��  X��Y�� ������
		 //rxNum -=UART_RX_LEN;
		 //i++; 
	}
	rxNum = GetInQLen(comSelect); 
	PlotCurve(&Graph, graphDispPanel, GRAPHDISP_GRAPH1);//������ͼ  
	if((RxData1.rxStopSign == 0x01) || (Graph.pCurveArray->numOfPlotDots == Graph.pCurveArray->numOfTotalDots))
	{
		DiscardAsyncTimer(TimerID);
		ProtocolStop(comSelect, select_Addr1, select_Addr2, measUartTxBuf1, measUartTxBuf2);  //����ָֹͣ��  
		//GraphDeinit(&Graph);												//�ڴ��ͷ��ڻ�ͼ֮��
		//GraphDeinit(&Graph_Temp);
		SetCtrlAttribute (mainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //���� ֹͣ��ť      
	    SetCtrlAttribute (mainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
		SetCtrlAttribute (mainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //�ָ� ���水ť
	}
}

void CVICALLBACK ComCallbackCGS(int portNumber, int eventMask, void * callbackData)
{
	int status;
	int rxNum;																							  
	int i=0;
	static a = 0;
	Rx_CGS_DataTypeDef Rx_CGS_Data;
	rxNum = GetInQLen(CGS_comSelect);  													//��ȡ�����з���������������
	if(rxNum>500) rxNum=500;															//��ֹ�����ڴ淶Χ
	status = ComRd(CGS_comSelect, (char *)meas_CGS_UartRxBuf, rxNum);					//Read UART Buffer to local buffer at one time 
	while(rxNum>=14)
	{
		a++;
		ProtocolGet_CGS_Data(meas_CGS_UartRxBuf, &Rx_CGS_Data);							// �� ������ȡ�� ������������
		*(Graph_Temp.pCurveArray->pDotX++) = a;
		*((Graph_Temp.pCurveArray + 1)->pDotX++) = a; 
		*((Graph_Temp.pCurveArray + 2)->pDotX++) = a; 
	    *(Graph_Temp.pCurveArray->pDotY++) = Rx_CGS_Data.environmental_humidity; 		 //����ʪ��
		*((Graph_Temp.pCurveArray + 1)->pDotY++) = Rx_CGS_Data.environmental_temp;		 //�����¶�
		*((Graph_Temp.pCurveArray + 2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		 //����ѹǿ
		(Graph_Temp.pCurveArray +1)->numOfDotsToPlot++;
		(Graph_Temp.pCurveArray +2)->numOfDotsToPlot++; 
		Graph_Temp.pCurveArray->numOfDotsToPlot++; 
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_STR_TEMP, Rx_CGS_Data.environmental_temp);			//�����¶�
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_STR_HUM,  Rx_CGS_Data.environmental_humidity);		//����ʪ��
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_STR_PRES, Rx_CGS_Data.pressure);				 	//ѹǿ
		rxNum -=14; 
		i++; 
	}
	PlotCurve_Temp(&Graph_Temp, graphDispPanel, GRAPHDISP_GRAPH2);//������ͼ*/
}


