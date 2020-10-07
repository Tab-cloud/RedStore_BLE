//******************************************************************************                              
//name:             GUA_RF_Communication.h                
//introduce:        ͨ��Э���ͷ�ļ�                 
//******************************************************************************   
#ifndef _GUA_RF_COMMUNICATION_H_  
#define _GUA_RF_COMMUNICATION_H_  
  
/*********************�궨��************************/   
#include "hal_lcd.h"
//#ifndef uint8      
//typedef unsigned char uint8;      
//#endif      
//
//#ifndef uint16      
//typedef unsigned short uint16;      
//#endif      
//
//#ifndef uint32      
//typedef unsigned long uint32;      
//#endif      
  
#define GUA_RF_COMMUNICATION_JUDGMENT_FALSE     0  
#define GUA_RF_COMMUNICATION_JUDGMENT_TRUE      1  

  
/*********************�ⲿ��������************************/    
 
extern void GZ_RF_Communication_DataPackage_Send(uint16 nGUA_ConnHandle,   
                                                  uint8 *npGUA_ValidData, uint8 nGUA_ValidData_Len);  
#endif  