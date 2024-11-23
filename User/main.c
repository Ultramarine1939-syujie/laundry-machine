#include "stm32f10x.h"
#include "timer.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "rtc.h" 
#include "adc.h"
#include "key.h"
#include "beep.h"
#include "hwjs.h"
#include "stepper.h"
#include "touch_key.h"
#include "pwm.h"
#include "ws2812.h"

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int step_cir = 0;	
u8 alt_set = 0;
u8 step_run = 0;
u8 step_reverse = 0;
u32 step_reverse_time = 0;
u32 step_speed = 1;
u32 temp_time=0;

u8 status = 0;

u8 mode = 0;
u8 texture = 0;

u8 set_min = 0;
u8 set_hour = 0;

u8 rtc_alt = 0;
u8 keypad = 255;

u16  timer_set =0;
u16 timer_set_set = 0;
	
int main()
{
	static u8 key = 1;
	static u8 touch_key = 0;

	u16 main_time = 0;
	u16 adc_value = 0;
	float adc_voltage = 0;
	u8 str_tmp[24],float_tmp[6];
	u32 color[]={RGB_COLOR_RED,RGB_COLOR_GREEN,
								RGB_COLOR_BLUE,RGB_COLOR_WHITE,RGB_COLOR_YELLOW};
	
	int pwm_value=0;					
	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	
	LED_Init();
	RTC_Init();
	RTC_Set(2024,10,8,8,50,00);
	
	ADCx_Init();
	KEY_Init();
	Touch_Key_Init(6);
	Hwjs_Init();
	BEEP_Init();
	RGB_LED_Init();
//	My_EXTI_Init();
	
	Stepper_Config();
	TIM4_Init();
	
	TIM2_CH3_PWM_Init(100,72-1); //频率是2Kh
	TIM_SetCompare3(TIM2,0);
	
	RTC_ClearITPendingBit(RTC_IT_ALR);
	
	LCD_Init();
	POINT_COLOR=RED;
	
	LCD_ShowString(70,10,200,16,16,"HFUT GXJ 2021218017");
	LCD_ShowString(70,30,200,16,16,"HFUT LLH 2021218032");
//	LCD_ShowString(70,90,200,16,16,"ST-LINK TEST");
	LCD_ShowString(30,130,320,16,16,"HWJS:          ");
//	LCD_ShowString(30,170,320,16,16,"RTC Alrt:    -  -     :  :  ");
	LCD_ShowString(30,220,320,16,16,"Machine Status:     ");
	LCD_ShowString(30,240,320,16,16,"RTC Time:    -  -     :  :  ");
	LCD_ShowString(30,260,320,16,16,"AD was detected:      ");
	LCD_ShowString(30,280,320,16,16,"Detective voltage:     V");
	LCD_ShowString(30,320,320,16,16,"Key pressed: ");	
	LCD_ShowString(30,340,320,16,16,"The motor speed is:    %");	
	LCD_ShowString(30,380,320,16,16,"The mode is:     ");	
	
	
	Chinese_Show_one(100,50,0,24,0,0);		
	Chinese_Show_one(124,50,1,24,0,0);	 	
	Chinese_Show_one(148,50,2,24,0,0);		
	Chinese_Show_one(172,50,3,24,0,0);
	Chinese_Show_one(196,50,4,24,0,0);
	
	while(1)
	{
		if(main_time % 1000){
//			LED1=!LED1;
			LCD_ShowxNum(100,90,temp_time+RTC_GetCounter()%86400,4,16,0);
			LCD_ShowxNum(150,90,step_reverse_time,4,16,0);
		}
		
		/*********  RTC时间显示  *********/
		if(main_time % 1000){
			RTC_Get();
			LCD_ShowxNum(102,240,calendar.w_year,4,16,0);
			LCD_ShowxNum(142,240,calendar.w_month,2,16,0);
			LCD_ShowxNum(166,240,calendar.w_date,2,16,0);
			LCD_ShowxNum(190,240,calendar.hour,2,16,0);
			LCD_ShowxNum(214,240,calendar.min,2,16,0);
			LCD_ShowxNum(236,240,calendar.sec,2,16,0);
		}
		
		/*********  ADC状态检测  *********/
		if(main_time % 1000){
			adc_value = Get_ADC_Value(ADC_Channel_1,20);
			LCD_ShowxNum(174,260,adc_value,4,16,0);
			adc_voltage = (float)adc_value*(3.3/4096);
			sprintf((char*)float_tmp,"%.2f",adc_voltage);
			LCD_ShowString(175,280,32,16,16,float_tmp);	
			if(adc_voltage < 2.0){
				LCD_ShowString(30,400,320,16,16,"Adc is too low.");	
			}else{
				LCD_ShowString(30,400,320,16,16,"Adc works fine.  ");
			}
		}
		
		/*********  按键检测  *********/
//		if(main_time % 25){
//			if(keypad==0)
//				LCD_ShowString(30,320,320,16,16,"Key pressed: Change Mode Set           ");	
//			else if (keypad==1)
//				LCD_ShowString(30,320,320,16,16,"Key pressed: Start Work             ");
//			else if (keypad==2)
//				LCD_ShowString(30,320,320,16,16,"Key pressed: Appointment Time Set        ");
//			else if (keypad==3)
//				LCD_ShowString(30,320,320,16,16,"Key pressed: Clothes Texture Set          ");
//		}
		
		if(timer_set == 1){
			RTC_SetAlarm(5+RTC_GetCounter());
			timer_set = 0;
			timer_set_set = 0;
		}
		
		if(main_time % 25){
			key = KEY_Scan(0);
			switch(key){
				case KEY_UP_PRESS:	//调模式
					mode = mode+1;
					LED2 = 0; 
					LCD_ShowString(30,320,320,16,16,"Key pressed: Change Mode Set           ");		
					break;
				
				case KEY1_PRESS: 		//定时预约
					if(status == 0 && step_run == 0)
					{
						timer_set_set = 1;
						RTC_SetAlarm(5+RTC_GetCounter());		//预约5秒
						
					}
					else if(status == 1 && step_run ==1)
					{
						RTC_SetAlarm(5+RTC_GetCounter());		//预约5秒
					}
					
					LED2 = 1;
					LCD_ShowString(30,320,320,16,16,"Key pressed: Appointment Time Set        ");
					break;
				
				case KEY2_PRESS:	//启动停止					
					BEEP=1;
					delay_ms(100);
					BEEP=0;
					if (status == 0 && step_run == 0)
					{
					timer_set_set = 0;
					status = !status;
					step_run =!step_run;
					RTC_SetAlarm(5+RTC_GetCounter());
					}
					else if (status == 1 && step_run ==1)
					{
						timer_set_set = 0;
						status = !status;
						step_run =!step_run;
					}
					LCD_ShowString(30,320,320,16,16,"Key pressed: Start Work             ");
					break;
				
				case KEY0_PRESS:	//衣物材质设定
					BEEP=1;
					delay_ms(100);
					BEEP=0;
					texture++;
					LCD_ShowString(30,320,320,16,16,"Key pressed: Clothes Texture Set          ");
					break;
			}
		}
		
			
		
		/*********  定时显示  *********/
		
//		if(main_time % 1000){
//			RTC_Get();
//			LCD_ShowxNum(102,170,calendar.w_year,4,16,0);
//			LCD_ShowxNum(142,170,calendar.w_month,2,16,0);
//			LCD_ShowxNum(166,170,calendar.w_date,2,16,0);
//			LCD_ShowxNum(190,170,set_hour,2,16,0);
//			LCD_ShowxNum(214,170,set_min,2,16,0);
//			LCD_ShowxNum(236,170,0,2,16,0);
//		}
		
		/*********  触摸按键  *********/
		if(main_time % 35){
			touch_key = Touch_Key_Scan(0);
			if(touch_key == 1){
				LCD_ShowString(30,320,320,16,16,"Key pressed: touch");
				LED1=!LED1;
			}
		}
		
		/*********  红外遥控  *********/
		if(main_time % 100){
			if(hw_jsbz==1)	//如果红外接收到
			{
				hw_jsbz=0;	   //清零
				printf("红外接收码 %0.8X\r\n",hw_jsm);	//打印
				sprintf((char*)str_tmp,"Hwjs %0.8X",hw_jsm);
				LCD_ShowString(30,130,320,16,16,str_tmp);	
				
				if(hw_jsm == 0x00FF629D){
					BEEP=1;
					delay_ms(10);
					BEEP=0;
					mode = mode+1;
				}
				else if(hw_jsm == 0x00FFA857){
					alt_set = 0;
					BEEP=1;
					delay_ms(100);
					BEEP=0;
					if(status == 0 && step_run == 0)
					{
						timer_set_set = 1;
						RTC_SetAlarm(5+RTC_GetCounter());		//预约5秒
						
					}
					else if(status == 1 && step_run ==1)
					{
						RTC_SetAlarm(5+RTC_GetCounter());		//预约5秒
					}
				}
				else if(hw_jsm == 0x00FF22DD){
					BEEP=1;
					delay_ms(10);
					BEEP=0;
					timer_set_set = 0;
					if (status == 0 && step_run == 0)
					{
					status = !status;
					step_run =!step_run;
					RTC_SetAlarm(10+RTC_GetCounter());
					}
					else if (status == 1 && step_run ==1)
					{
						status = !status;
						step_run =!step_run;
					}
				}
				else if(hw_jsm == 0x00FFC23D){
					
					BEEP=1;
					delay_ms(10);
					BEEP=0;
					texture++;
				}
				else if(hw_jsm == 0x00FF02FD){
					BEEP=1;
					delay_ms(10);
					BEEP=0;
					step_reverse = !step_reverse;
					LCD_ShowString(30,70,320,16,16,"Step motor: REVERSED ");
				}
				else{
					LCD_ShowString(200,130,320,16,16,"not!");	
				}
				hw_jsm=0;					//接收码清零
			}				
		}
		
		if(alt_set == 1){
				BEEP=1;
				delay_ms(200);
				BEEP=0;
				LED2 = 0;
				alt_set = 0;
		}
		
		/*********  状态更新  *********/
		if(main_time % 100){
			if(mode % 4 == 0){
				mode = 0;
			}else if(mode == 255){
				mode = 3;
			}
			LCD_ShowxNum(174,380,mode,4,16,0);
			LCD_ShowxNum(200,420,timer_set,4,16,0);
			
			
			if(texture % 3 == 0){
				texture = 0;
			}
			
			if(rtc_alt ==0){
				LCD_ShowString(30,150,320,16,16,"RTC_ALR SET START   ");
			}else if (rtc_alt ==1)
				LCD_ShowString(30,150,320,16,16,"RTC_ALR SET STOP   ");
			
			switch(mode){
				case 0:
					pwm_value=0;
					step_speed = 10000-5000*texture;
					temp_time = 10;
				if(step_reverse_time < RTC_GetCounter()%86400)
					step_reverse_time = temp_time+RTC_GetCounter()%86400;
					
					break;
				case 1:
					pwm_value=0;
					step_speed = 50000-5000*texture;
					temp_time = 10;
				if(step_reverse_time < RTC_GetCounter()%86400)
					step_reverse_time = temp_time+RTC_GetCounter()%86400;
					break;
				case 2:
					pwm_value=0;
					step_speed = 50000-5000*texture;
					temp_time = 20;
				if(step_reverse_time < RTC_GetCounter()%86400)
					step_reverse_time = temp_time+RTC_GetCounter()%86400;
					break;
				case 3:
					pwm_value=75;
					step_speed = 10000-5000*texture;
					temp_time = 30;
				if(step_reverse_time < RTC_GetCounter()%86400)
					step_reverse_time = temp_time+RTC_GetCounter()%86400;
					break;
			}
			
			switch(texture){
				case 0:
					LCD_ShowString(30,200,320,16,16,"Clothes texture: 000");
					break;
				case 1:
					LCD_ShowString(30,200,320,16,16,"Clothes texture: 001");
					break;
				case 2:
					LCD_ShowString(30,200,320,16,16,"Clothes texture: 002");
					break;
			}
		}
		
		if(main_time % 100){
//			RGB_ShowCharNum(mode,color[mode]);
			switch(mode){
				case 0:
					RGB_LED_Red();
					break;
				case 1:
					RGB_LED_Green();
					break;
				case 2:
					RGB_LED_Blue();
					break;
				case 3:
					RGB_LED_Fuck();
					break;
			}
		}
		
		/*********  直流电机  *********/
		
		if(main_time % 100){
			if (status==0 && adc_voltage > 2.0){
				LCD_ShowString(30,220,320,16,16,"Machine Status: Stop    ");
				TIM_SetCompare3(TIM2,0);
				LCD_ShowxNum(180,340,pwm_value,3,16,0);
				
			}else if(status==1 && adc_voltage > 2.0){
				LCD_ShowString(30,220,320,16,16,"Machine Status: Start  ");
				TIM_SetCompare3(TIM2,pwm_value);
				LCD_ShowxNum(180,340,pwm_value,3,16,0);
			}
			
			if(adc_voltage < 2.0){
				TIM_SetCompare3(TIM2,0);
				LCD_ShowString(30,220,320,16,16,"Machine Status: ADC low  ");
				LCD_ShowxNum(180,340,pwm_value,3,16,0);
				step_run = 0;
			}
		}		

		
		/*********  步进电机  *********/
		if(step_run != 0){
			step_cir += 2000;
			step_run = 1;
			LCD_ShowString(30,110,320,16,16,"Step motor:Start ");
			TIM4_EnableInterrupt();
		}
		else if(step_run ==0){
			LCD_ShowString(30,110,320,16,16,"Step motor: Stop ");
			TIM4_DisableInterrupt();
		}
		else{
			LCD_ShowxNum(30,380,step_cir,4,16,0);
		}
		
		delay_ms(1);
		main_time++;
		if(main_time >= 1E5) main_time = 0;
	}
}
