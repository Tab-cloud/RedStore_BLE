#include "adc.h"

/*******************************************************************************************************************/
/****************************************************Define ********************************************************/
/*******************************************************************************************************************/
u16 Vbat,Temp,R_Face;

/*******************************************************************************************************************/
/************************************************* Function Code ***************************************************/
/*******************************************************************************************************************/
u16 Get_Vbat_Vaule(void)
{
  u16 Vbat_Vaule;
  // Configure ADC and perform a read
  HalAdcSetReference( HAL_ADC_REF_AVDD );
  Vbat_Vaule = HalAdcRead( HAL_ADC_CHN_AIN7, HAL_ADC_RESOLUTION_12 );
  
  return Vbat_Vaule;
}

u16 Get_Temp_Vaule(void)
{
  u16 Temp_Vaule;
  // Configure ADC and perform a read
  HalAdcSetReference( HAL_ADC_REF_AVDD );
  Temp_Vaule = HalAdcRead( HAL_ADC_CHN_AIN5, HAL_ADC_RESOLUTION_12 );
  
  return Temp_Vaule;
}

u16 Get_RFace_Vaule(void)
{
  u16 RFace_Vaule;
  // Configure ADC and perform a read
  HalAdcSetReference( HAL_ADC_REF_AVDD );
  RFace_Vaule = HalAdcRead( HAL_ADC_CHN_AIN3, HAL_ADC_RESOLUTION_12 );
  
  return RFace_Vaule;
}

u16 Get_Key_Left(void)
{
  u16 Key_Left_Vaule;
  
  // Configure ADC and perform a read
  HalAdcSetReference( HAL_ADC_REF_AVDD );
  Key_Left_Vaule = HalAdcRead( HAL_ADC_CHN_AIN1, HAL_ADC_RESOLUTION_12 );
}
