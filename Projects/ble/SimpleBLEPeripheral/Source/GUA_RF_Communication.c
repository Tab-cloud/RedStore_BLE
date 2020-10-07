//******************************************************************************                              
//name:             GUA_RF_Communication.c                 
//introduce:        通信协议                  
//******************************************************************************   
#include "GUA_RF_Communication.h"  
#include <string.h>  
  
/*********************宏定义************************/   
//通信协议的功能码  
#define FUNC_GUA_LED_ON_OFF                             0x00    //led开关的功能码  
  
//应用层事件（从应用层复制过来）  
#define SBP_START_DEVICE_EVT                            0x0001  
#define SBP_PERIODIC_EVT                                0x0002  
#define SBP_GUA_RF_COMMUNICAION_PROCESS_EVT             0x0004  //通信处理事件  
#define UART_EVENT                                      0x0008  //通信数据出错事件   
  
//通信协议的数据包长度  
#define GUA_DATA_PACKAGE_LEN                            20      //20字节一包  
/*
typedef unsigned short uint16;
******************************************************************************                  
//name:             GUA_RF_Communication_Judgment                 
//introduce:        RF的通信数据判断              
//parameter:        npGUA_Receive: 接收缓冲区首地址         
//return:           true: 数据包正确  
//                  false: 数据包错误                                      
******************************************************************************   
GUA_U8 GUA_RF_Communication_Judgment(GUA_U8 *npGUA_Receive)  
{ 
  uint16 BCC;
  uint16 j,i;
  
  i = 0;
  GUA_U8 nGUA_Sof = npGUA_Receive[i];
  
  GUA_U8 nGUA_Len = npGUA_Receive[i+1];
  
  GUA_U8 nGUA_Func = npGUA_Receive[i+2];
  
  GUA_U8 npGUA_Data = npGUA_Receive[i+3];
  i += 4;
   
  //判断起始位正确性  
  if(nGUA_Sof != 0xfe)  
  {  
    return GUA_RF_COMMUNICATION_JUDGMENT_FALSE;    
  }       
  
  //接收数据长度  
  if(nGUA_Len > 16)  
  {  
    return GUA_RF_COMMUNICATION_JUDGMENT_FALSE;    
  }   

  //BCC校验和
  BCC = 0;
  for(j=4;j<i;j++)
  {
    BCC+=npGUA_Receive[j];
  }
  npGUA_Receive[i] = (GUA_U8)(BCC);
  i += 1;
  
  //数据包正确  
  return GUA_RF_COMMUNICATION_JUDGMENT_TRUE;  
}  
*/  
extern void GZ_SimpleGATTprofile_Char6_Notify(uint16 nGUA_ConnHandle, uint8 *npGUA_Value, uint8 nGUA_Len);  
//******************************************************************************                  
//name:             GZ_RF_Communication_DataPackage_Send                 
//introduce:        RF的通信数据打包并发送(包头+有效数据长度+功能码+有效数据+补齐字节)              
//parameter:        nGUA_Func: 功能码       
//                  npGUA_ValidData: 有效数据首地址  
//                  nGUA_ValidData_Len: 要发送的数据长度  
//return:           none                                     
//******************************************************************************   
void GZ_RF_Communication_DataPackage_Send(uint16 nGUA_ConnHandle, uint8 *npGUA_ValidData, uint8 nGUA_ValidData_Len)  
{ 
  uint16 BCC;
  uint16 j;
  j = 0;
  
  uint8 nbGUA_DataPackage_Data[GUA_DATA_PACKAGE_LEN];   
    
  //初始化发送缓冲区  
  memset(nbGUA_DataPackage_Data, 0x00, 20);    
    
  //填充数据  
  nbGUA_DataPackage_Data[0] = 0xd8;                                                       //包头  
  nbGUA_DataPackage_Data[1] = nGUA_ValidData_Len;                                       //有效数据长度 
  
  memcpy(nbGUA_DataPackage_Data + 2, npGUA_ValidData, nGUA_ValidData_Len);                //有效数据  
  //BCC校验和
  BCC = 0;
  for(j=0;j<nGUA_ValidData_Len+2;j++)
  {
    BCC ^= nbGUA_DataPackage_Data[j];
  }
  nbGUA_DataPackage_Data[nGUA_ValidData_Len + 2] = (uint8)(BCC);
  
  //发送数据      
  GZ_SimpleGATTprofile_Char6_Notify(nGUA_ConnHandle, nbGUA_DataPackage_Data, GUA_DATA_PACKAGE_LEN);  

    
}  
  