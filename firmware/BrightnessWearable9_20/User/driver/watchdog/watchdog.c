#include "watchdog.h"


/*
 * 独立看门狗初始化 sec秒钟需要喂一次狗
 * prer:分频数:0~7(只有低3位有效!)
 * rlr:自动重装载值,0~0XFFF.
 * 分频因子=4*2^prer.但最大值只能是256!
 * rlr:重装载寄存器值:低11位有效
 * 时间计算(大概):Tout=((4*2^prer)*rlr) / 32 (ms).
 */
void watchdog_init_sec(uint8_t sec)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //使能对IWDG->PR IWDG->RLR的写
	IWDG_SetPrescaler(4); 			//设置IWDG分频系数 prer=4
	IWDG_SetReload(500*sec);   		//设置IWDG装载值 rlr=500
	IWDG_ReloadCounter(); 			//reload
	IWDG_Enable();       			//使能看门狗
}

/*
 * 喂狗
 */
void watchdog_feed(void)
{
	IWDG_ReloadCounter();		//reload
}
