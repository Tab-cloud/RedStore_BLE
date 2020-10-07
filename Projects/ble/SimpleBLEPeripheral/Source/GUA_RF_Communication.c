//******************************************************************************                              
//name:             GUA_RF_Communication.c                 
//introduce:        ͨ��Э��                  
//******************************************************************************   
#include "GUA_RF_Communication.h"  
#include <string.h>  
  
/*********************�궨��************************/   
//ͨ��Э��Ĺ�����  
#define FUNC_GUA_LED_ON_OFF                             0x00    //led���صĹ�����  
  
//Ӧ�ò��¼�����Ӧ�ò㸴�ƹ�����  
#define SBP_START_DEVICE_EVT                            0x0001  
#define SBP_PERIODIC_EVT                                0x0002  
#define SBP_GUA_RF_COMMUNICAION_PROCESS_EVT             0x0004  //ͨ�Ŵ����¼�  
#define UART_EVENT                                      0x0008  //ͨ�����ݳ����¼�   
  
//ͨ��Э������ݰ�����  
#define GUA_DATA_PACKAGE_LEN                            20      //20�ֽ�һ��  
/*
typedef unsigned short uint16;
******************************************************************************                  
//name:             GUA_RF_Communication_Judgment                 
//introduce:        RF��ͨ�������ж�              
//parameter:        npGUA_Receive: ���ջ������׵�ַ         
//return:           true: ���ݰ���ȷ  
//                  false: ���ݰ�����                                      
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
   
  //�ж���ʼλ��ȷ��  
  if(nGUA_Sof != 0xfe)  
  {  
    return GUA_RF_COMMUNICATION_JUDGMENT_FALSE;    
  }       
  
  //�������ݳ���  
  if(nGUA_Len > 16)  
  {  
    return GUA_RF_COMMUNICATION_JUDGMENT_FALSE;    
  }   

  //BCCУ���
  BCC = 0;
  for(j=4;j<i;j++)
  {
    BCC+=npGUA_Receive[j];
  }
  npGUA_Receive[i] = (GUA_U8)(BCC);
  i += 1;
  
  //���ݰ���ȷ  
  return GUA_RF_COMMUNICATION_JUDGMENT_TRUE;  
}  
*/  
extern void GZ_SimpleGATTprofile_Char6_Notify(uint16 nGUA_ConnHandle, uint8 *npGUA_Value, uint8 nGUA_Len);  
//******************************************************************************                  
//name:             GZ_RF_Communication_DataPackage_Send                 
//introduce:        RF��ͨ�����ݴ��������(��ͷ+��Ч���ݳ���+������+��Ч����+�����ֽ�)              
//parameter:        nGUA_Func: ������       
//                  npGUA_ValidData: ��Ч�����׵�ַ  
//                  nGUA_ValidData_Len: Ҫ���͵����ݳ���  
//return:           none                                     
//******************************************************************************   
void GZ_RF_Communication_DataPackage_Send(uint16 nGUA_ConnHandle, uint8 *npGUA_ValidData, uint8 nGUA_ValidData_Len)  
{ 
  uint16 BCC;
  uint16 j;
  j = 0;
  
  uint8 nbGUA_DataPackage_Data[GUA_DATA_PACKAGE_LEN];   
    
  //��ʼ�����ͻ�����  
  memset(nbGUA_DataPackage_Data, 0x00, 20);    
    
  //�������  
  nbGUA_DataPackage_Data[0] = 0xd8;                                                       //��ͷ  
  nbGUA_DataPackage_Data[1] = nGUA_ValidData_Len;                                       //��Ч���ݳ��� 
  
  memcpy(nbGUA_DataPackage_Data + 2, npGUA_ValidData, nGUA_ValidData_Len);                //��Ч����  
  //BCCУ���
  BCC = 0;
  for(j=0;j<nGUA_ValidData_Len+2;j++)
  {
    BCC ^= nbGUA_DataPackage_Data[j];
  }
  nbGUA_DataPackage_Data[nGUA_ValidData_Len + 2] = (uint8)(BCC);
  
  //��������      
  GZ_SimpleGATTprofile_Char6_Notify(nGUA_ConnHandle, nbGUA_DataPackage_Data, GUA_DATA_PACKAGE_LEN);  

    
}  
  