/**************************************************************************************************
  Filename:       hal_lcd.h
  Revised:        $Date: 2007-07-06 10:42:24 -0700 (Fri, 06 Jul 2007) $
  Revision:       $Revision: 13579 $

  Description:    This file contains the interface to the LCD Service.


  Copyright 2005-2007 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

#ifndef HAL_LCD_H
#define HAL_LCD_H

#ifdef __cplusplus
extern "C"
{
#endif

/**************************************************************************************************
 *                                          INCLUDES
 **************************************************************************************************/
#include "hal_board.h"
#if (defined HAL_LCD) && (HAL_LCD == TRUE) 
#endif
  
/**************************************************************************************************
 *                                         CONSTANTS
 **************************************************************************************************/

/* These are used to specify which line the text will be printed */
#define HAL_LCD_LINE_1      0x01
#define HAL_LCD_LINE_2      0x02
/*
   This to support LCD with extended number of lines (more than 2).
   Don't use these if LCD doesn't support more than 2 lines
*/
#define HAL_LCD_LINE_3      0x03
#define HAL_LCD_LINE_4      0x04
#define HAL_LCD_LINE_5      0x05
#define HAL_LCD_LINE_6      0x06
#define HAL_LCD_LINE_7      0x07
#define HAL_LCD_LINE_8      0x08
 
  
//������ɫ
#define WHITE         	               0xFFFF
#define BLACK                          0x0000	  
#define BLUE           	               0x001F  
#define BRED                           0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	               0xF800
#define MAGENTA       	               0xF81F
#define GREEN         	               0x07E0
#define CYAN          	               0x7FFF
#define YELLOW        	               0xFFE0
#define BROWN 			       0XBC40 //��ɫ
#define BRRED 			       0XFC07 //�غ�ɫ
#define GRAY  			       0X8430 //��ɫ
#define SHELL_PINK                     0xFD97 //����
#define VIOLET                         0xF014 //������ɫ
#define MALLOW                         0xDA5F //������
#define PLUM                           0xDD1B //÷��ɫ
#define OLET                           0xBD19 //����
#define COFFE                          0x49c0
#define PALE_OCRE                      0Xcd91 //����ɫ
#define BRIGHT_GREEN                   0X67C0 //����
//GUI��ɫ
  
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
  
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 		 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)  
/**************************************************************************************************
 *                                          MACROS
 **************************************************************************************************/

/*
����ʾ����������(����):
1-----------GND  =  �ӵ�
2-----------VCC  =  ��Դһ��2V~5V
3-----------SCL  =  IIC_SCLK     P00
4-----------SDA  =  IIC_SDA      P02
5-----------RST  =  IIC_RESET    P01
6-----------DC   =  DC           P06
7-----------CS   =  CS           P10
8-----------BLK  =  BLK          P12
����ʾ��ʹ��spi�ӿڣ�ֻ�����û�����룬����cs��û����������Ĭ��ѡͨ��
dc�߱�������spi�ӿڷ��룬���Ǹ���ʾ����������������������ѡ���ߣ�
dcΪ1ʱ��ͨ��spi�ӿ�д�������ʾ����
dcΪ0ʱ��ͨ��spi�ӿ�д���������.
*/

// oled��ʾ���ϵ� SCL ��
#define LCD_SCLK_SBIT             P0_0       //SCLK  ʱ�� D0��SCLK��
#define LCD_SCLK_DDR              P0DIR      //�˿�
#define LCD_SCLK_BV               BV(0)      //λ(��Χ0~7)

// oled��ʾ���ϵ� SDA ��
#define LCD_SDA_SBIT              P0_2       //SDA   D1��SDA�� ����
#define LCD_SDA_DDR               P0DIR      //�˿�
#define LCD_SDA_BV                BV(2)      //λ(��Χ0~7)

// oled��ʾ���ϵ� RST ��
#define LCD_RST_SBIT              P0_1       //_RES  hardware reset ��λ 
#define LCD_RST_DDR               P0DIR      //�˿�
#define LCD_RST_BV                BV(1)      //λ(��Χ0~7)

// oled��ʾ���ϵ� DC ��
#define LCD_DC_SBIT               P0_6       //A0  H/L ��������ѡͨ�ˣ�H�����ݣ�L:����
#define LCD_DC_DDR                P0DIR      //�˿�
#define LCD_DC_BV                 BV(6)      //λ(��Χ0~7)

// oled��ʾ���ϵ� CS ��
#define LCD_CS_SBIT               P1_0       //CS  Ƭѡ
#define LCD_CS_DDR                P1DIR      //�˿�
#define LCD_CS_BV                 BV(0)      //λ(��Χ0~7)

// oled��ʾ���ϵ� BLK ��
#define LCD_BLK_SBIT              P1_2       //BLK �������
#define LCD_BLK_DDR               P1DIR      //�˿�
#define LCD_BLK_BV                BV(2)      //λ(��Χ0~7)
  
 // ��ʼ����6��io��Ϊ���
#define LCD_SPI_PORT_INIT()             \
    do{                                 \
        LCD_SCLK_DDR |= LCD_SCLK_BV;    \
        LCD_SDA_DDR  |= LCD_SDA_BV;     \
        LCD_RST_DDR  |= LCD_RST_BV;     \
        LCD_DC_DDR   |= LCD_DC_BV;      \
        LCD_CS_DDR   |= LCD_CS_BV;      \
        LCD_BLK_DDR  |= LCD_BLK_BV;     \
   }while(0)
     
#define USE_HORIZONTAL 1  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 80
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 80
#endif
     
//-----------------����LED�˿ڶ���---------------- 

//#define LED_ON  LCD_BLK_SBIT = 0
//#define LED_OFF LCD_BLK_SBIT = 1
     
//-----------------OLED�˿ڶ���---------------- 

#define OLED_SCLK_Clr() LCD_SCLK_SBIT = 0
#define OLED_SCLK_Set() LCD_SCLK_SBIT = 1

#define OLED_SDIN_Clr() LCD_SDA_SBIT = 0
#define OLED_SDIN_Set() LCD_SDA_SBIT = 1

#define OLED_RST_Clr() LCD_RST_SBIT = 0
#define OLED_RST_Set() LCD_RST_SBIT = 1

#define OLED_DC_Clr() LCD_DC_SBIT = 0
#define OLED_DC_Set() LCD_DC_SBIT = 1
 		     
#define OLED_CS_Clr()  LCD_CS_SBIT = 0
#define OLED_CS_Set()  LCD_CS_SBIT = 1

#define OLED_BLK_Clr()  LCD_BLK_SBIT = 0
#define OLED_BLK_Set()  LCD_BLK_SBIT = 1

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
/**************************************************************************************************
 *                                         TYPEDEFS
 **************************************************************************************************/
typedef	uint8 u8 ;
#define	u16 unsigned int
typedef	uint32 u32 ;

/**************************************************************************************************
 *                                     GLOBAL VARIABLES
 **************************************************************************************************/
extern  u16 BACK_COLOR;   //����ɫ

/**************************************************************************************************
 *                                     FUNCTIONS - API
 **************************************************************************************************/
void LCD_Writ_Bus(u8 dat);
void LCD_WR_DATA8(u8 dat);
void LCD_WR_DATA(u16 dat);
void LCD_WR_REG(u8 dat);
extern void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);
extern void LCD_Clear(u16 Color);
extern void LCD_ShowChinese(u16 x,u16 y,u8 index,u8 size,u16 color);
extern void LCD_DrawPoint(u16 x,u16 y,u16 color);
extern void LCD_DrawPoint_big(u16 x,u16 y,u16 color);
extern void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
extern void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);
extern void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
extern void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);
extern void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode,u16 color);
extern void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 color);
u32 mypow(u8 m,u8 n);
extern void LCD_ShowNum(u16 x,u16 y,u16 num,u8 len,u16 color);
extern void LCD_ShowNum1(u16 x,u16 y,float num,u8 len,u16 color);
extern void LCD_ShowPicture(u16 x1,u16 y1,u16 x2,u16 y2);
void LCD_Start_log(void);
void LCD_Display_Qr(void);
void LCD_Display_Power(u16 Vaule,u16 bk_color);
void LCD_Clear_Powr(u16 color);
void LCD_Display_CutLine(u16 color);
/*
 * Initialize LCD Service
 */
extern void HalLcdInit(void);

/*
 * Write a string to the LCD
 */
extern void HalLcdWriteString ( char *str, uint8 option);

/*
 * Write a value to the LCD
 */
extern void HalLcdWriteValue ( uint32 value, const uint8 radix, uint8 option);

/*
 * Write a value to the LCD
 */
extern void HalLcdWriteScreen( char *line1, char *line2 );

/*
 * Write a string followed by a value to the LCD
 */
extern void HalLcdWriteStringValue( char *title, uint16 value, uint8 format, uint8 line );

/*
 * Write a string followed by 2 values to the LCD
 */
extern void HalLcdWriteStringValueValue( char *title, uint16 value1, uint8 format1, uint16 value2, uint8 format2, uint8 line );

/*
 * Write a percentage bar to the LCD
 */
extern void HalLcdDisplayPercentBar( char *title, uint8 value );

extern void Hal_HW_WaitUs(uint16 microSecs);
void LCD_DLY_ms(unsigned int ms);
/**************************************************************************************************
**************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
