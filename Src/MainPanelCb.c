//==============================================================================
//
// Title:		MainPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 15:58:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "Tools.h"     
#include <utility.h>
#include "asynctmr.h"
#include "MainPanelCb.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "LoadPanel.h"
#include "Protocol.h"
#include "Timer.h"
#include "I_T_Panel.h"
#include "SampleCfgPanel.h"
#include "ResultMenuPanel.h"
#include "table.h"
#include "SetPanelCB.h"
#include "File.h"
#include <rs232.h>
#include "MainPanel.h"
//==============================================================================
// Constants
#define TWO_TERMINAL 0
#define EXP_I_V 1
#define EXP_V_I 2
#define EXP_I_T 3
#define EXP_V_T 4
#define EXP_R_T 5
#define FOUR_TERMINAL 16
#define EXP_ID_VDS 17
#define EXP_ID_VGS 18
#define VAL_TEXTBG                        0xF0F0F0L    //未被选中背景色
#define VAL_TEXTBG_PRESSED                0x065279L    //被选中背景
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
int TimerID;
char configSavePath[512]={0};
FileLableTypeDef *pFileLable[64];									//存所有FileLable的指针，最多只能加载一个文件夹下的64个文件
PrjHandleTypeDef SingleProject[64];									
Graph_TypeDef Graph;
Graph_TypeDef Graph_Temp;
char ABC[11][20] ={"A","B","C","D","E","F","G","H","I","J","K"};
char Table_title_IV[11][20] ={"Current(A)","Voltage(mV)","Current(A)","Voltage(mV)"};
char Table_title_VI[11][20] ={"Voltage(mV)","Current(A)","Voltage(mV)","Current(A)"}; 
char Table_title_IT[11][20] ={"Time(S)","Current(A)","Time(S)","Current(A)"};
char Table_title_RT[11][20] ={"Time(S)","Resistance(Ω)","Time(S)","Resistance(Ω)"};
//==============================================================================
// Global functions
static void DispRuntime(int display)
{ 
	SetCtrlAttribute (hBasicSamplePanel, SAMPLE_CFG_TXT_RUNTIME, ATTR_VISIBLE, display);
	SetCtrlAttribute (hBasicSamplePanel, SAMPLE_CFG_RUNTIME, ATTR_VISIBLE, display); 
	SetCtrlAttribute (hBasicSamplePanel, SAMPLE_CFG_TXT_S, ATTR_VISIBLE, display);
}
//===================================================
//   MAIN_PANEL_Callback

int CVICALLBACK MAIN_PANEL_Callback (int panel, int event, void *callbackData,
									 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			if(CGS_comSelect>0)
			CloseCom(CGS_comSelect);
			if(comSelect>0)
			CloseCom(comSelect);
			QuitUserInterface(0); 
		break;
	}
	return 0;
}
static void InitSingleProject(PrjHandleTypeDef *pSingleProject)
{
	int i;
	for(i=0;i<64;i++)
	{
		(pSingleProject+i)->index=-1;	
	}
}

void Dispgraph()
{
	int index;
	GetCtrlIndex(expListPanel, EXP_LIST_EXPLIST, &index);
	if(index==EXP_I_V)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "V(mV)");		  //graph1坐标轴
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "V");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "mV");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "I");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "A");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "V");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "mV");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "I");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "A");
	}
	else if(index==EXP_V_I)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "I(mA)");
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");		//graph1坐标轴
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "I");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "A");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "V");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "mV");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "I");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "A");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "V");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "mV");
	}
	else if(index==EXP_I_T)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "T(ms)");		   //graph1坐标轴 
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");		   
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "T");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "ms");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "I");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "A");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "T");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "ms");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "I");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "A");
	}
	else if(index==EXP_V_T)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "T(ms)");
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(mV)");		  //graph1坐标轴
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "T");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "ms");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "V");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "mV");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "T");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "ms");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "V");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "mV");
	}
	else if(index==EXP_R_T)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "T(ms)");
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "R(Ω)");		   //graph1坐标轴
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "T");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "ms");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "R1");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "Ω");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "T");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "ms");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "R");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "Ω");
	}
	else
	{
	}
}

void Runkeyaction()//运行按钮按下后产生的一系列动作
{
	SetCtrlAttribute (mainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);         //禁用 开始按钮      
    SetCtrlAttribute (mainPanel, MAIN_PANEL_STOP, ATTR_DIMMED, 0);       //恢复 停止按钮
    SetCtrlAttribute (mainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED,1);        //禁用 保存按钮
	SetCtrlAttribute (mainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED,1);        //禁用 保存按钮  
	
	/*SetPanelPos(resultPanel, 105, 305);     
	DisplayPanel(resultPanel);*/  

	SetPanelPos(graphDispPanel, 105, 305);
	DisplayPanel(graphDispPanel);
		
			
	SetPanelPos(hResultDispPanel, 105, 3);
	DisplayPanel(hResultDispPanel);
			
	SetPanelPos(hStrainDispPanel, 457, 3);
	DisplayPanel(hStrainDispPanel);
			
	SetPanelPos(hEnvResultPanel, 659, 3);
	DisplayPanel(hEnvResultPanel);

	SetPanelPos(hImageDispPanel, 807, 3);
	DisplayPanel(hImageDispPanel);
	
	HidePanel(hBasicSamplePanel);
	HidePanel(hAdvanceSamplePanel);
	
	//DispResultTableGraph();  
	DisplayImageFile (mainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
	DisplayImageFile (mainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
	DisplayImageFile (mainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");
	
	SetCtrlAttribute(graphDispPanel, GRAPHDISP_GRAPH1, ATTR_ENABLE_ZOOM_AND_PAN, 1 );	//设置曲线图可以通过鼠标键盘放大与缩小
	SetCtrlAttribute(graphDispPanel, GRAPHDISP_GRAPH2, ATTR_ENABLE_ZOOM_AND_PAN, 1 );	//设置曲线图可以通过鼠标键盘放大与缩小
	
	DeleteGraphPlot (graphDispPanel, GRAPHDISP_GRAPH1,-1 , VAL_IMMEDIATE_DRAW); 		//清空曲线图上的所有曲线
	DeleteGraphPlot (graphDispPanel, GRAPHDISP_GRAPH2,-1 , VAL_IMMEDIATE_DRAW); 		//清空曲线图上的所有曲线 
	DeleteTableRows (tablePanel, TABLE_TABLE1, 1, -1);									//清除表格 
	DeleteTableColumns (tablePanel, TABLE_TABLE1, 1, -1);
}
void ProtocolCfg(unsigned char comSelect, unsigned char devAddr1, unsigned char devAddr2,unsigned char expType, unsigned char* pmeasUartTxBuf1,unsigned char* pmeasUartTxBuf2)
{
	int graphIndex=1;
	int numOfCurve=2;
	int numOfDots=100;
	Table_TypeDef Table_ATTR;
	switch((enum ExpType)expType)
	{
		case NO_SWEEP_IV:
			Table_ATTR.column = 2 ;   				//列数
			Table_ATTR.column_width = 300;  		//列宽
			Table_init(Table_title_IV, Table_ATTR.column, Table_ATTR.column_width );
			
			GetTestPara(&I_V_Panel1, &TestPara1);  //得到源表 1 用户设置参数
			GetTestPara(&I_V_Panel2, &TestPara2); //得到源表 2 用户设置参数
			
			numOfDots = abs(TestPara1.Current_Start - TestPara1.Current_Stop)/TestPara1.Current_Step +1;
			
			graphInit(graphIndex, numOfCurve, numOfDots, &Graph);
			Graph.pCurveArray->numOfTotalDots = numOfDots; 
			Graph.pGraphAttr->xAxisHead = TestPara1.Current_Start;
			Graph.pGraphAttr->xAxisTail = TestPara1.Current_Stop;
			SetAxisScalingMode(graphDispPanel,GRAPHDISP_GRAPH1,VAL_BOTTOM_XAXIS,VAL_MANUAL,Graph.pGraphAttr->xAxisHead,Graph.pGraphAttr->xAxisTail);
			
			break;
		case NO_SWEEP_VI:
			Table_ATTR.column = 2 ;   				//列数
			Table_ATTR.column_width = 300;  		//列宽
			Table_init(Table_title_VI, Table_ATTR.column, Table_ATTR.column_width );
			
			GetTestPara(&V_I_Panel1, &TestPara1);  //得到源表 1 用户设置参数
			GetTestPara(&V_I_Panel2, &TestPara2); //得到源表 2 用户设置参数
			
			numOfDots = abs(TestPara1.Voltage_Start - TestPara1.Voltage_Stop)/TestPara2.Voltage_Stop;
			graphInit(graphIndex, numOfCurve, numOfDots, &Graph);
			Graph.pGraphAttr->xAxisHead = TestPara1.Voltage_Start;   
			Graph.pGraphAttr->xAxisTail = TestPara1.Voltage_Stop;
			SetAxisScalingMode(graphDispPanel,GRAPHDISP_GRAPH1,VAL_BOTTOM_XAXIS,VAL_MANUAL,Graph.pGraphAttr->xAxisHead,Graph.pGraphAttr->xAxisTail);
			
			break;
		case NO_SWEEP_IT:
			Graph.X_Axis_Max = 100;
			Graph_Temp.X_Axis_Max=100;
			Table_ATTR.column = 2 ;   				//列数
			Table_ATTR.column_width = 300;			//列宽
			Table_init(Table_title_IT, Table_ATTR.column, Table_ATTR.column_width );
			
			GetTestPara(&I_T_Panel1, &TestPara1);  //得到源表 1 用户设置参数
			GetTestPara(&I_T_Panel2, &TestPara2);  //得到源表 2 用户设置参数
			
			numOfDots = (TestPara1.runTime*1000)/TestPara1.timeStep + 1; 
			graphInit(graphIndex, numOfCurve, numOfDots, &Graph);
			Graph.pCurveArray->numOfTotalDots = numOfDots;
			
			SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph.X_Axis_Max);//设置 X 轴的范围
			SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph_Temp.X_Axis_Max);//设置 X 轴的范围
			
			break;
		case NO_SWEEP_RT:
			Graph.X_Axis_Max = 100;
			Graph_Temp.X_Axis_Max=100;
			Table_ATTR.column = 2 ;   				//列数
			Table_ATTR.column_width = 300;  		//列宽
			Table_init(Table_title_RT, Table_ATTR.column, Table_ATTR.column_width );
			GetTestPara(&R_T_Panel1, &TestPara1);  //得到源表 1 用户设置参数
			GetTestPara(&R_T_Panel2, &TestPara2); //得到源表 2 用户设置参数
			
			numOfDots =(TestPara1.runTime*1000)/TestPara1.timeStep;
			graphInit(graphIndex, numOfCurve, numOfDots+5, &Graph);
			Graph.pCurveArray->numOfTotalDots = numOfDots;
			
			SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph.X_Axis_Max);//设置 X 轴的范围
			SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph_Temp.X_Axis_Max);//设置 X 轴的范围
			break;
	}
	graphInit(graphIndex, 3, numOfDots + 5, &Graph_Temp);
	PrepareCfgTxData(&TestPara1, &TestPara2, devAddr1, devAddr2, expType, pmeasUartTxBuf1,pmeasUartTxBuf2); //分别向  源表1  源表2 存储区中 放入用户输入的 设置命令 
	if(devAddr1 == 0x01)	//判断是否为源表 1 地址，为真则发送 源表 1 设置命令
	ComWrt(comSelect, (const char*)pmeasUartTxBuf1, SA31_UART_TX_LEN); 
	Delay(0.2);
	if(devAddr2 == 0x02)	//判断是否为源表 2 地址，为真则发送 源表 2 设置命令  
	ComWrt(comSelect, (const char*)pmeasUartTxBuf2, SA31_UART_TX_LEN);
}

//===================================================
//   RunCallback

int CVICALLBACK RunCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int expType;
	int index;
	GetCtrlIndex(expListPanel, EXP_LIST_EXPLIST, &index);
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			if(index==TWO_TERMINAL||index==FOUR_TERMINAL)
			{
				MessagePopup ("", "Please select a experiment!");
			}
			else
			{
				GetCtrlVal (hSettingsGraphPanel, SETGRAPH_SMU1CLR, &smu1Clr);
				GetCtrlVal (hSettingsGraphPanel, SETGRAPH_SMU2CLR, &smu2Clr); 
				GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR1, &graph2tempclr);				//得到温度湿度压力三条曲线的颜色
				GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR2, &graph2humclr);
				GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR3, &graph2preclr);
			
				X1 = 0;  
				X2 = 0;
				/*FlushInQ(6);	   														//Clear input and output buffer
				FlushOutQ(6);*/
				
				GraphDeinit(&Graph);													//内存释放在画图之后
				GraphDeinit(&Graph_Temp);
	
				Dispgraph();
				Runkeyaction();																//运行按钮按下后产生的一系列动作
		
				if(GetCtrlVal(expListPanel, EXP_LIST_EXPLIST, &expType)<0)  //每次开始之前判断一下用户选择的 测试模式
					return -1;
				TestPara1.testMode = expType; //源表 1 测试类型
				TestPara2.testMode = expType; //源表 1 测试类型
				ProtocolCfg(comSelect, select_Addr1, select_Addr2,(unsigned char)expType, measUartTxBuf1,measUartTxBuf2);//得到用户的设置参数  并发送
				//SetCtrlAttribute (mainPanel, MAIN_PANEL_TIMER, ATTR_INTERVAL, TestPara1.timeStep * 0.001);  //设置同步回调函数定时值 定时发送查询命令
				Delay(2);//延时
				//TimerID = NewAsyncTimer(TestPara1.timeStep * 0.001,-1, 1, TimerCallback, 0);		//Create Asynchronous (Timer time interval 1s, continue generating evernt, enabled, callback function name, passing no pointer) 
			
				double temp=(double)TestPara1.timeStep * 0.001;
				if(temp<0.03) temp=0.03;													//如果查询时间过快，会造成数据混乱，下位机响应中断过多
				TimerID = NewAsyncTimer(temp,-1, 1, TimerCallback, 0);
				ProtocolRun(comSelect, select_Addr1, select_Addr2, measUartTxBuf1, measUartTxBuf2);		//send RUN command to instrument via UART
				//SetCtrlAttribute (mainPanel, MAIN_PANEL_TIMER, ATTR_ENABLED, 1);       //开启同步定时器
				//Delay(2);
			}
			break;
	}
	return 0;
}

//===================================================
//   StopCallback

int CVICALLBACK StopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			DiscardAsyncTimer(TimerID);//关闭异步定时器  停止曲线显示
			SetCtrlAttribute (mainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //禁用 停止按钮      
			SetCtrlAttribute (mainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //恢复 开始按钮
			SetCtrlAttribute (mainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //恢复 保存按钮
			SetCtrlAttribute (mainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED,0); 
			//SetCtrlAttribute (mainPanel, MAIN_PANEL_TIMER, ATTR_ENABLED, 0);   //关闭同步定时器 停止发送查询命令
			ProtocolStop(comSelect, select_Addr1, select_Addr2, measUartTxBuf1, measUartTxBuf2);  //发送停止指令
		
			/*FlushInQ(6);	   														//Clear input and output buffer
			FlushOutQ(6);*/
			
			break;
	}
	return 0;
}

//===================================================
//   SaveCallback

int CVICALLBACK SaveCallback (int panel, int control, int event,void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:			    //当Save被鼠标左键点击时 
			DisplayImageFile (mainPanel, MAIN_PANEL_SAVE, "Resource\\Save_pressed.ico");
			break;
		case EVENT_LEFT_CLICK_UP:		    //当鼠标释放时  
			DisplayImageFile (mainPanel, MAIN_PANEL_SAVE, "Resource\\Save.ico");
			if(FileSelectPopupEx("C:\\SINOAGG\\SA3102\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 1,  configSavePath)>0)
			SaveConfigToFile(configSavePath);
			break;
	}
	return 0;
}
static int SaveAllPanelState(char* pConfigSavePath)
{
	SavePanelState(IVPanel, pConfigSavePath, 1);
	SavePanelState(VIPanel, pConfigSavePath, 2);
	SavePanelState(I_T_Panel1.panelHandle, pConfigSavePath, 3); //IT面板的值  
	SavePanelState(VTPanel, pConfigSavePath, 4);
	SavePanelState(RTPanel, pConfigSavePath, 5);
	SavePanelState(hBasicSamplePanel, pConfigSavePath, 10);	   //用户设置 配置值
	SavePanelState(hAdvanceSamplePanel, pConfigSavePath, 11);  //高级设置面板值
	SavePanelState(hEnvCfgPanel, pConfigSavePath, 14);
	SavePanelState(ENVTPanel, pConfigSavePath, 15);
	SavePanelState(hSettingsGraphPanel, pConfigSavePath, 16);
	return 0;
}
static int SaveConfigToFile(char* pConfigSavePath)
{
	FILE * fp = NULL;							//表示打开的文件
	fp = fopen(pConfigSavePath, "w");
	if(fp == NULL)
	{
		MessagePopup ("Error", "Invalid Path, please select path to save configurations.");
		if(FileSelectPopup ("C:\\SINOAGG\\SA3102\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 1, 1, 1, pConfigSavePath)<0)
			return -1;
	}
	else
	{
		int maxCommentSize=255;
		char description[maxCommentSize];
		PromptPopup("Message", "Please enter description for this configuration:", description, maxCommentSize-1);
		SaveAllPanelState(pConfigSavePath);		//保存所有面板的数据
		fp = fopen(pConfigSavePath, "a+");
		fprintf(fp, "\r\n%-61s\r\n", description);		//左对齐打满64字符
		fclose(fp);//关闭文件
	}
	return 0;
}
//===================================================
//   SelectCallback

int CVICALLBACK SelectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:			    //当Select被鼠标左键点击时,Select图标改变，其它两个正常状态 
			DisplayImageFile (mainPanel, MAIN_PANEL_SELECT, "Resource\\Select_pressed.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");
			HidePanel(hBasicSamplePanel);		
			HidePanel(hResultDispPanel);
			HidePanel(hEnvCfgPanel);
			HidePanel(hEnvResultPanel);
			HidePanel(hAdvanceSamplePanel);
			break;
	}
	return 0;
}



//===================================================
//   Analyze_Callback

int CVICALLBACK AnalyzeCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(graphDispPanel, 105, 305);
			DisplayPanel(graphDispPanel);
		
			//DispResultTableGraph();
			
			/*SetPanelPos(resultPanel, 105, 305);  
		    SetPanelSize(resultPanel, 65, 1293);      
	 		DisplayPanel(resultPanel); */ 
			
			SetPanelPos(hResultDispPanel, 105, 3);
			DisplayPanel(hResultDispPanel);
			
			SetPanelPos(hStrainDispPanel, 457, 3);
			DisplayPanel(hStrainDispPanel);
			
			SetPanelPos(hEnvResultPanel, 659, 3);
			DisplayPanel(hEnvResultPanel);

			SetPanelPos(hImageDispPanel, 807, 3);
			DisplayPanel(hImageDispPanel);
			
			DisplayImageFile (mainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");
			
			break;
	}
	return 0;
}

int CVICALLBACK SettingsCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			InstallPopup (setPanel);  //弹出settingsPanel
			HidePanel (hSettingsGraphPanel);
			HidePanel (aboutPanel);
			SetPanelPos(ENVTPanel, 5, 160);
			DisplayPanel(ENVTPanel);
			
			SetCtrlAttribute (setPanel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //project背景色
	     	SetCtrlAttribute (setPanel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //project文本颜色
			
			SetCtrlAttribute (setPanel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //graph背景色
	     	SetCtrlAttribute (setPanel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //graph文本颜色
			
			SetCtrlAttribute (setPanel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //about背景色
	     	SetCtrlAttribute (setPanel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //about文本颜色
			
			GetCtrlVal (hSettingsGraphPanel, SETGRAPH_SMU1CLR, &smu1ClrOld);
			GetCtrlVal (hSettingsGraphPanel, SETGRAPH_SMU2CLR, &smu2ClrOld); 
			GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR1, &graph2Color1Old);
			GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR2, &graph2Color2Old);
			GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR3, &graph2Color3Old);
			
		break;
	}
	return 0;
}
static int LoadAndDispPrj(FileLableTypeDef *pFileLable, char index)						//index为prj所在位置排序
{
	int hSinglePrjPanel;
	if ((hSinglePrjPanel = LoadPanel (projectPanel, "ProjectPanel.uir", DEFPANEL)) < 0)		//load projects panel
		return -1;
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_NAME, pFileLable->FileName);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_DATE, pFileLable->FileDate);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_TIME, pFileLable->FileTime);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_DESC, pFileLable->FileDesc);
	SetPanelPos(hSinglePrjPanel, index*117, -10);
	SetPanelSize(hSinglePrjPanel, 115, 1250);
	DisplayPanel(hSinglePrjPanel);
	return hSinglePrjPanel;
}

static int LoadAllProject(char* pProjectSavePath)
{
	char tempFileName[512];
	char tempFilePath[512];
	char index=0;
	char tempPathToSearch[512];
	InitSingleProject(SingleProject);
	sprintf(tempPathToSearch, "%s%s", pProjectSavePath, "\\*.sac");
	if(0==GetFirstFile(tempPathToSearch, 1, 1, 1, 1, 1, 0, tempFileName))		//如果第一个文件获取成功
	{
		sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
		pFileLable[index] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
		InitFileLable(pFileLable[index], tempFilePath); 				//读文件时间和文件名称及description，并展示
		SingleProject[index].hSinglePrjPanel = LoadAndDispPrj(pFileLable[index], index);
		SingleProject[index].index=index;
		index++;
		while(GetNextFile(tempFileName)==0)								//如果读取正确，持续读取
		{
			sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
			pFileLable[index] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
			InitFileLable(pFileLable[index], tempFilePath); //读文件时间和文件名称及description
			SingleProject[index].hSinglePrjPanel = LoadAndDispPrj(pFileLable[index], index);
			SingleProject[index].index=index; 
			index++;
		}
	}
	return 0;
}

int CVICALLBACK ProjectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		case EVENT_LEFT_CLICK_UP:
			InstallPopup (proPanel);
			SetPanelPos(projectPanel, 85, 0);
			SetPanelSize(projectPanel, 380, 1250);
			DisplayPanel(projectPanel);
			LoadAllProject(ProjectSavePath);
		break;
	}	 
	return 0;
}

int CVICALLBACK ToolsCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			InstallPopup (hToolsPanel); 
			break;
	}
	return 0;
}


