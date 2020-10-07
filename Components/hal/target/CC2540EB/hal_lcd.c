#include "hal_types.h"
#include "hal_lcd.h"
#include "OSAL.h"
#include "OnBoard.h"
#include "stdio.h"

#include "oledfont.h"
#include "bmp.h"

#ifndef HAL_LCD_REVERSE
#define HAL_LCD_REVERSE     0x80//取反显示
#endif

#if (HAL_LCD == TRUE)

#if (HAL_UART == TRUE)
#ifdef LCD_TO_UART      // 串口输出显示的内容
  #include "npi.h"
#endif
#endif

u16 BACK_COLOR;   //背景色
u8 i;
/******************************************************************************
      函数说明：定时ms
      入口数据：目标时间
      返回值：  无
******************************************************************************/
void LCD_DLY_ms(unsigned int ms)
{  
  u16 n;
  for(n=0 ; n<ms; n++)
    Hal_HW_WaitUs(1000);
}

/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(u8 dat) 
{	
  u8 i;
  OLED_CS_Clr();
  for(i=0;i<8;i++)
  {			  
    OLED_SCLK_Clr();
    if(dat&0x80)
      OLED_SDIN_Set();
    else
      OLED_SDIN_Clr();
    OLED_SCLK_Set();
    dat<<=1;
  }	
  OLED_CS_Set();	
}

/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
  OLED_DC_Clr();//写命令
  LCD_Writ_Bus(dat);
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
  OLED_DC_Set();//写数据
  LCD_Writ_Bus(dat);
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
  OLED_DC_Set();//写数据
  LCD_Writ_Bus(dat>>8);
  LCD_Writ_Bus(dat);
}

/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
  if(USE_HORIZONTAL==0)
  {
    LCD_WR_REG(0x2a);//列地址设置
    LCD_WR_DATA(x1+26);
    LCD_WR_DATA(x2+26);
    LCD_WR_REG(0x2b);//行地址设置
    LCD_WR_DATA(y1+1);
    LCD_WR_DATA(y2+1);
    LCD_WR_REG(0x2c);//储存器写
  }
  else if(USE_HORIZONTAL==1)
  {
    LCD_WR_REG(0x2a);//列地址设置
    LCD_WR_DATA(x1+26);
    LCD_WR_DATA(x2+26);
    LCD_WR_REG(0x2b);//行地址设置
    LCD_WR_DATA(y1+1);
    LCD_WR_DATA(y2+1);
    LCD_WR_REG(0x2c);//储存器写
  }
  else if(USE_HORIZONTAL==2)
  {
    LCD_WR_REG(0x2a);//列地址设置
    LCD_WR_DATA(x1+1);
    LCD_WR_DATA(x2+1);
    LCD_WR_REG(0x2b);//行地址设置
    LCD_WR_DATA(y1+26);
    LCD_WR_DATA(y2+26);
    LCD_WR_REG(0x2c);//储存器写
  }
  else
  {
    LCD_WR_REG(0x2a);//列地址设置
    LCD_WR_DATA(x1+1);
    LCD_WR_DATA(x2+1);
    LCD_WR_REG(0x2b);//行地址设置
    LCD_WR_DATA(y1+26);
    LCD_WR_DATA(y2+26);
    LCD_WR_REG(0x2c);//储存器写
  }
}

/******************************************************************************
      函数说明：LCD初始化函数
      入口数据：无
      返回值：  无
******************************************************************************/
void HalLcdInit(void)
{
  LCD_SPI_PORT_INIT();
  
  OLED_RST_Clr();
  LCD_DLY_ms(200);
  OLED_RST_Set();
  LCD_DLY_ms(200);
  OLED_BLK_Set();
  
  LCD_DLY_ms(200);
  LCD_WR_REG(0x11);     //Sleep out
  LCD_DLY_ms(200);
  LCD_WR_REG(0xB1);     //Normal mode
  LCD_WR_DATA8(0x05);   
  LCD_WR_DATA8(0x3C);   
  LCD_WR_DATA8(0x3C);   
  LCD_WR_REG(0xB2);     //Idle mode
  LCD_WR_DATA8(0x05);   
  LCD_WR_DATA8(0x3C);   
  LCD_WR_DATA8(0x3C);   
  LCD_WR_REG(0xB3);     //Partial mode
  LCD_WR_DATA8(0x05);   
  LCD_WR_DATA8(0x3C);   
  LCD_WR_DATA8(0x3C);   
  LCD_WR_DATA8(0x05);   
  LCD_WR_DATA8(0x3C);   
  LCD_WR_DATA8(0x3C);   
  LCD_WR_REG(0xB4);     //Dot inversion
  LCD_WR_DATA8(0x03);   
  LCD_WR_REG(0xC0);     //AVDD GVDD
  LCD_WR_DATA8(0xAB);   
  LCD_WR_DATA8(0x0B);   
  LCD_WR_DATA8(0x04);   
  LCD_WR_REG(0xC1);     //VGH VGL
  LCD_WR_DATA8(0xC5);   //C0
  LCD_WR_REG(0xC2);     //Normal Mode
  LCD_WR_DATA8(0x0D);   
  LCD_WR_DATA8(0x00);   
  LCD_WR_REG(0xC3);     //Idle
  LCD_WR_DATA8(0x8D);   
  LCD_WR_DATA8(0x6A);   
  LCD_WR_REG(0xC4);     //Partial+Full
  LCD_WR_DATA8(0x8D);   
  LCD_WR_DATA8(0xEE);   
  LCD_WR_REG(0xC5);     //VCOM
  LCD_WR_DATA8(0x0F);   
  LCD_WR_REG(0xE0);     //positive gamma
  LCD_WR_DATA8(0x07);   
  LCD_WR_DATA8(0x0E);   
  LCD_WR_DATA8(0x08);   
  LCD_WR_DATA8(0x07);   
  LCD_WR_DATA8(0x10);   
  LCD_WR_DATA8(0x07);   
  LCD_WR_DATA8(0x02);   
  LCD_WR_DATA8(0x07);   
  LCD_WR_DATA8(0x09);   
  LCD_WR_DATA8(0x0F);   
  LCD_WR_DATA8(0x25);   
  LCD_WR_DATA8(0x36);   
  LCD_WR_DATA8(0x00);   
  LCD_WR_DATA8(0x08);   
  LCD_WR_DATA8(0x04);   
  LCD_WR_DATA8(0x10);   
  LCD_WR_REG(0xE1);     //negative gamma
  LCD_WR_DATA8(0x0A);   
  LCD_WR_DATA8(0x0D);   
  LCD_WR_DATA8(0x08);   
  LCD_WR_DATA8(0x07);   
  LCD_WR_DATA8(0x0F);   
  LCD_WR_DATA8(0x07);   
  LCD_WR_DATA8(0x02);   
  LCD_WR_DATA8(0x07);   
  LCD_WR_DATA8(0x09);   
  LCD_WR_DATA8(0x0F);   
  LCD_WR_DATA8(0x25);   
  LCD_WR_DATA8(0x35);   
  LCD_WR_DATA8(0x00);   
  LCD_WR_DATA8(0x09);   
  LCD_WR_DATA8(0x04);   
  LCD_WR_DATA8(0x10);
          
  LCD_WR_REG(0xFC);    
  LCD_WR_DATA8(0x80);  
          
  LCD_WR_REG(0x3A);     
  LCD_WR_DATA8(0x05);   
  LCD_WR_REG(0x36);
  if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x08);
  else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC8);
  else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x78);
  else LCD_WR_DATA8(0xA8);   
  LCD_WR_REG(0x21);     //Display inversion
  LCD_WR_REG(0x29);     //Display on
  LCD_WR_REG(0x2A);     //Set Column Address
  LCD_WR_DATA8(0x00);   
  LCD_WR_DATA8(0x1A);  //26  
  LCD_WR_DATA8(0x00);   
  LCD_WR_DATA8(0x69);   //105 
  LCD_WR_REG(0x2B);     //Set Page Address
  LCD_WR_DATA8(0x00);   
  LCD_WR_DATA8(0x01);    //1
  LCD_WR_DATA8(0x00);   
  LCD_WR_DATA8(0xA0);    //160
  LCD_WR_REG(0x2C); 
  
  LCD_Clear(BROWN);
  BACK_COLOR=BROWN;
  LCD_Start_log();
  LCD_DLY_ms(2500);
  LCD_Clear(MALLOW);
  BACK_COLOR=MALLOW;
}

/******************************************************************************
      函数说明：LCD清屏函数
      入口数据：无
      返回值：  无
******************************************************************************/
void LCD_Clear(u16 Color)
{
  u16 i,j;  	
  LCD_Address_Set(0,0,LCD_W-1,LCD_H-1);
  for(i=0;i<LCD_W;i++)
  {
    for (j=0;j<LCD_H;j++)
    {
      LCD_WR_DATA(Color);
    }
  }
}

/******************************************************************************
      函数说明：LCD显示汉字
      入口数据：x,y   起始坐标
                index 汉字的序号
                size  字号
      返回值：  无
******************************************************************************/
void LCD_ShowChinese(u16 x,u16 y,u8 index,u8 size,u16 color)	
{  
  u8 i,j;
  u8 *temp,size1;
  if(size==16){temp=Hzk16;}//选择字号
  if(size==24){temp=Hzk24;}
  if(size==32){temp=Hzk32;}
  LCD_Address_Set(x,y,x+size-1,y+size-1); //设置一个汉字的区域
  size1=size*size/8;//一个汉字所占的字节
  temp+=index*size1;//写入的起始位置
  for(j=0;j<size1;j++)
  {
    for(i=0;i<8;i++)
    {
      if((*temp&(1<<i))!=0)//从数据的低位开始读
      
        LCD_WR_DATA(color);//点亮
      
      else
      
        LCD_WR_DATA(BACK_COLOR);//不点亮
      
    }
      temp++;
  }
}

/******************************************************************************
      函数说明：LCD显示汉字
      入口数据：x,y   起始坐标
      返回值：  无
******************************************************************************/
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
  LCD_Address_Set(x,y,x,y);//设置光标位置 
  LCD_WR_DATA(color);
} 

/******************************************************************************
      函数说明：LCD画一个大的点
      入口数据：x,y   起始坐标
      返回值：  无
******************************************************************************/
void LCD_DrawPoint_big(u16 x,u16 y,u16 color)
{
  LCD_Fill(x-1,y-1,x+1,y+1,color);
} 

/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
      返回值：  无
******************************************************************************/
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
  u16 i,j; 
  LCD_Address_Set(xsta,ysta,xend,yend);      //设置光标位置 
  for(i=ysta;i<=yend;i++)
  {													   	 	
    for(j=xsta;j<=xend;j++)LCD_WR_DATA(color);//设置光标位置 	    
  } 					  	    
}

/******************************************************************************
      函数说明：画线
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
      返回值：  无
******************************************************************************/
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
  u16 t; 
  int xerr=0,yerr=0,delta_x,delta_y,distance;
  int incx,incy,uRow,uCol;
  delta_x=x2-x1; //计算坐标增量 
  delta_y=y2-y1;
  uRow=x1;//画线起点坐标
  uCol=y1;
  if(delta_x>0)incx=1; //设置单步方向 
  else if (delta_x==0)incx=0;//垂直线 
  else {incx=-1;delta_x=-delta_x;}
  if(delta_y>0)incy=1;
  else if (delta_y==0)incy=0;//水平线 
  else {incy=-1;delta_y=-delta_x;}
  if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
  else distance=delta_y;
  for(t=0;t<distance+1;t++)
  {
    LCD_DrawPoint(uRow,uCol,color);//画点
    xerr+=delta_x;
    yerr+=delta_y;
    if(xerr>distance)
    {
      xerr-=distance;
      uRow+=incx;
    }
    if(yerr>distance)
    {
      yerr-=distance;
      uCol+=incy;
    }
  }
}

/******************************************************************************
      函数说明：画矩形
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
      返回值：  无
******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
  LCD_DrawLine(x1,y1,x2,y1,color);
  LCD_DrawLine(x1,y1,x1,y2,color);
  LCD_DrawLine(x1,y2,x2,y2,color);
  LCD_DrawLine(x2,y1,x2,y2,color);
}

/******************************************************************************
      函数说明：画圆
      入口数据：x0,y0   圆心坐标
                r       半径
      返回值：  无
******************************************************************************/
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
  int a,b;
  a=0;b=r;	  
  while(a<=b)
  {
    LCD_DrawPoint(x0-b,y0-a,color);             //3           
    LCD_DrawPoint(x0+b,y0-a,color);             //0           
    LCD_DrawPoint(x0-a,y0+b,color);             //1                
    LCD_DrawPoint(x0-a,y0-b,color);             //2             
    LCD_DrawPoint(x0+b,y0+a,color);             //4               
    LCD_DrawPoint(x0+a,y0-b,color);             //5
    LCD_DrawPoint(x0+a,y0+b,color);             //6 
    LCD_DrawPoint(x0-b,y0+a,color);             //7
    a++;
    if((a*a+b*b)>(r*r))//判断要画的点是否过远
    {
      b--;
    }
  }
}

/******************************************************************************
      函数说明：显示字符
      入口数据：x,y    起点坐标
                num    要显示的字符
                mode   1叠加方式  0非叠加方式
      返回值：  无
******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode,u16 color)
{
  u8 temp;
  u8 pos,t;
  u16 x0=x;    
  if(x>LCD_W-16||y>LCD_H-16)return;	    //设置窗口		   
  num=num-' ';//得到偏移后的值
  LCD_Address_Set(x,y,x+8-1,y+16-1);      //设置光标位置 
  if(!mode) //非叠加方式
  {
    for(pos=0;pos<16;pos++)
    { 
      temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
      for(t=0;t<8;t++)
      {                 
        if(temp&0x01)LCD_WR_DATA(color);
	else LCD_WR_DATA(BACK_COLOR);
	temp>>=1;
	x++;
       }
	x=x0;
	y++;
    }	
  }else//叠加方式
  {
    for(pos=0;pos<16;pos++)
    {
      temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
      for(t=0;t<8;t++)
      {                 
        if(temp&0x01)LCD_DrawPoint(x+t,y+pos,color);//画一个点     
        temp>>=1; 
      }
    }
  }   	   	 	  
}

/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y    起点坐标
                *p     字符串起始地址
      返回值：  无
******************************************************************************/
void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 color)
{         
  while(*p!='\0')
  {       
    if(x>LCD_W-16){x=0;y+=16;}
    if(y>LCD_H-16){y=x=0;LCD_Clear(RED);}
    LCD_ShowChar(x,y,*p,0,color);
    x+=8;
    p++;
   }  
}

/******************************************************************************
      函数说明：显示数字
      入口数据：m底数，n指数
      返回值：  无
******************************************************************************/
u32 mypow(u8 m,u8 n)
{
  u32 result=1;	 
  while(n--)result*=m;    
  return result;
}

/******************************************************************************
      函数说明：显示数字
      入口数据：x,y    起点坐标
                num    要显示的数字
                len    要显示的数字个数
      返回值：  无
******************************************************************************/
void LCD_ShowNum(u16 x,u16 y,u16 num,u8 len,u16 color)
{         	
  u8 t,temp;
  u8 enshow=0;
  for(t=0;t<len;t++)
  {
    temp=(num/mypow(10,len-t-1))%10;
    if(enshow==0&&t<(len-1))
    {
      if(temp==0)
      {
	LCD_ShowChar(x+8*t,y,' ',0,color);
	continue;
      }else enshow=1; 
		 	 
    }
    LCD_ShowChar(x+8*t,y,temp+48,0,color); 
  }
} 

/******************************************************************************
      函数说明：显示小数
      入口数据：x,y    起点坐标
                num    要显示的小数
                len    要显示的数字个数
      返回值：  无
******************************************************************************/
void LCD_ShowNum1(u16 x,u16 y,float num,u8 len,u16 color)
{         	
  u8 t,temp;
  u16 num1;
  num1=(u16)num*100;
  for(t=0;t<len;t++)
  {
    temp=(num1/mypow(10,len-t-1))%10;
    if(t==(len-2))
    {
      LCD_ShowChar(x+8*(len-2),y,'.',0,color);
      t++;
      len+=1;
    }
    LCD_ShowChar(x+8*t,y,temp+48,0,color);
  }
}

/******************************************************************************
      函数说明：显示40x40图片
      入口数据：x,y    起点坐标
      返回值：  无
******************************************************************************/
void LCD_ShowPicture(u16 x1,u16 y1,u16 x2,u16 y2)
{
  int i;
  LCD_Address_Set(x1,y1,x2,y2);
  for(i=0;i<3600;i++)
  { 	
    LCD_WR_DATA8(start[i*2+1]);	 
    LCD_WR_DATA8(start[i*2]);			
  }			
}
/******************************************************************************
      函数说明：显示电量
      入口数据：Vaule:电量值
      返回值：  无c
******************************************************************************/
void LCD_Display_Power(u16 Vaule,u16 bk_color)
{ 
  u8 Rx,Ry;
  u8 Powr_Rate;
  
  Powr_Rate = (u8)(25*Vaule/2047);
  LCD_DrawRectangle(1,1,26,13,WHITE);          //76-52=25
  for(Rx = 2; Rx <Powr_Rate ; Rx ++)
  {
    for(Ry = 2 ; Ry < 13 ; Ry ++)
      LCD_DrawPoint( Rx, Ry, BRIGHT_GREEN);
  }
  
  for(Rx = 26-Powr_Rate;Rx>1;Rx-- )
  {
    for(Ry = 2 ; Ry < 13 ; Ry ++)
      LCD_DrawPoint( Rx, Ry, bk_color);
  }
}

/******************************************************************************
      函数说明：显示分割栏
      入口数据：coLor:颜色
      返回值：  无c
******************************************************************************/
void LCD_Display_CutLine(u16 color)
{
  u8 num;
  for(num = 16 ; num <80 ; num ++)
    LCD_DrawPoint(num,15,color);
}

/******************************************************************************
      函数说明：开机显示，静态标志语
      入口数据：void
      返回值：  无
******************************************************************************/
void LCD_Start_log(void)
{
  LCD_Clear(SHELL_PINK);
  BACK_COLOR=SHELL_PINK;
  LCD_ShowChinese(12,24,0,16, VIOLET);   //要
  LCD_ShowChinese(12,40,1,16, VIOLET);   //我
  LCD_ShowChinese(12,56,2,16, VIOLET);   //说
  LCD_ShowChinese(12,72,3,16, VIOLET);   //这
  LCD_ShowChinese(12,88,4,16, VIOLET);   //人
  LCD_ShowChinese(12,104,5,16,VIOLET);   //呐
  LCD_ShowChinese(16,120,6,16,VIOLET);   //！
  
  LCD_ShowChinese(48,0,7,16,   VIOLET);   //各
  LCD_ShowChinese(48,16,8,16,  VIOLET);   //有
  LCD_ShowChinese(48,32,7,16,  VIOLET);   //各
  LCD_ShowChinese(48,48,9,16,  VIOLET);   //的
  LCD_ShowChinese(40,64,0,32,  VIOLET);   //漂
  LCD_ShowChinese(40,96,1,32,  VIOLET);   //亮
  LCD_ShowChinese(40,128,2,32, VIOLET);   //法
}

/******************************************************************************
      函数说明：扫码获取app 二维码，静态标志语
      入口数据：void
      返回值：  无
******************************************************************************/
void LCD_Display_Qr(void)
{
  LCD_Clear(PLUM);
  BACK_COLOR=PLUM;
    
  LCD_ShowChinese(8,8,13,16,WHITE);
  LCD_ShowChinese(24,8,14,16,WHITE);
  LCD_ShowChinese(40,8,15,16,WHITE);
  LCD_ShowChinese(56,8,16,16,WHITE);
  LCD_ShowString(24,28,"APP!",WHITE);
  LCD_ShowPicture(10,50,69,109);
  
  LCD_ShowChinese(0,120,8,16,WHITE);
  LCD_ShowChinese(16,120,17,16,WHITE);
  LCD_ShowChinese(32,120,18,16,WHITE);
  LCD_ShowChinese(48,120,19,16,WHITE);
  LCD_ShowChinese(64,120,20,16,WHITE);
  LCD_ShowChinese(16,136,9,16,WHITE);
  LCD_ShowChinese(32,136,21,16,WHITE);
  LCD_ShowChinese(48,136,22,16,WHITE);
}

/*********************************************************************************************/

#else
/*
 * Initialize LCD Service
 */
void HalLcdInit(void){}
#endif

