/**
 ****************************************************************************************************
 * @file        sys.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-14
 * @brief       ϵͳ��ʼ������(����ʱ������/�жϹ���/GPIO���õ�)
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * ��һ�η���
 * V1.0 20211014

 ****************************************************************************************************
 */

#ifndef _SYS_H
#define _SYS_H

#include "stm32f4xx.h"
#include "core_cm4.h"
#include "stm32f4xx_hal.h"

#define BITBAND(addr,bitn)		((addr & 0xF0000000)+0x2000000 + ((addr & 0xFFFFF)*8 + bitn)*4)
#define MEM_ADDR(addr)  *((volatile unsigned int *)(addr))
#define BIT_ADDR(addr, bitn)   MEM_ADDR(BITBAND(addr, bitn))

#define GPIOA_ODR_Addr    ((unsigned int)&GPIOA->ODR) //0x40020014
#define GPIOB_ODR_Addr    ((unsigned int)&GPIOB->ODR) //0x40020414 
#define GPIOC_ODR_Addr    ((unsigned int)&GPIOC->ODR) //0x40020814 
#define GPIOD_ODR_Addr    ((unsigned int)&GPIOD->ODR) //0x40020C14 
#define GPIOE_ODR_Addr    ((unsigned int)&GPIOE->ODR) //0x40021014 
#define GPIOF_ODR_Addr    ((unsigned int)&GPIOF->ODR) //0x40021414    
#define GPIOG_ODR_Addr    ((unsigned int)&GPIOG->ODR) //0x40021814   
#define GPIOH_ODR_Addr    ((unsigned int)&GPIOH->ODR) //0x40021C14    
#define GPIOI_ODR_Addr    ((unsigned int)&GPIOI->ODR) //0x40022014     
//??
#define GPIOA_IDR_Addr    ((unsigned int)&GPIOA->IDR) //0x40020010 
#define GPIOB_IDR_Addr    ((unsigned int)&GPIOB->IDR) //0x40020410 
#define GPIOC_IDR_Addr    ((unsigned int)&GPIOC->IDR) //0x40020810 
#define GPIOD_IDR_Addr    ((unsigned int)&GPIOD->IDR) //0x40020C10 
#define GPIOE_IDR_Addr    ((unsigned int)&GPIOE->IDR) //0x40021010 
#define GPIOF_IDR_Addr    ((unsigned int)&GPIOF->IDR) //0x40021410 
#define GPIOG_IDR_Addr    ((unsigned int)&GPIOG->IDR) //0x40021810 
#define GPIOH_IDR_Addr    ((unsigned int)&GPIOH->IDR) //0x40021C10 
#define GPIOI_IDR_Addr    ((unsigned int)&GPIOI->IDR) //0x40022010 
 
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //?? 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //?? 
 
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //?? 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //?? 
 
#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //?? 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //?? 
 
#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //?? 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //?? 
 
#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //?? 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //??
 
#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //?? 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //??
 
#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //?? 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //??
 
#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //?? 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //??
 
#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //?? 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //??


/**
 * SYS_SUPPORT_OS���ڶ���ϵͳ�ļ����Ƿ�֧��OS
 * 0,��֧��OS
 * 1,֧��OS
 */
#define SYS_SUPPORT_OS         0

//����һЩ���õ��������Ͷ̹ؼ��� 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;  

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  
typedef __I int16_t vsc16; 
typedef __I int8_t vsc8;   

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8; 

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8;  

/*��������*******************************************************************************************/

void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset);                         /* �����ж�ƫ���� */
void sys_standby(void);                                                                     /* �������ģʽ */
void sys_soft_reset(void);                                                                  /* ϵͳ��λ */
uint8_t sys_stm32_clock_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq);   /* ����ϵͳʱ�� */


/* ����Ϊ��ຯ�� */
void sys_wfi_set(void);             /* ִ��WFIָ�� */
void sys_intx_disable(void);        /* �ر������ж� */
void sys_intx_enable(void);         /* ���������ж� */
void sys_msr_msp(uint32_t addr);    /* ����ջ����ַ */

#endif

