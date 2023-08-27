#include "mylcd.h"
#include "math.h"
#define width	480
#define high	800	//4.3��
const  uint8_t* key_menu[16]={"1","2","3","4","5","6","7","8","9","0","CE","Go",};  
uint8_t counter[20] = {0};	//���ڴ����������
void Load_keyboard()
{
	uint16_t i;
	lcd_fill(0,0,width,width,WHITE);
	//����
	lcd_draw_rectangle(0,high*1/2,width,high,RED);			
	lcd_draw_rectangle(width*1/3,high*1/2,width*2/3,high,RED);		
	
	lcd_draw_rectangle(0,0,width,high*1/2,RED);	
	//���
	lcd_draw_rectangle(0,high*1/8,width,high*2/8,RED);	
	lcd_draw_rectangle(0,high*2/8,width,high*3/8,RED);	
	
	lcd_draw_rectangle(0,high*5/8,width,high*6/8,RED);	
	lcd_draw_rectangle(0,high*6/8,width,high*7/8,RED);	
	
	for(i=0;i<16;i++)
	{
		lcd_show_string((i%3)*width/3+70 , high/2+(i/3)*(high/2)/4+35,32,32,32 , (uint8_t*)key_menu[i],BLUE);	
	} 
}
//the text show
void Load_textshow()
{ 
	char* temp1[20] = {"Start fre:(0~1M):"};
	lcd_show_string (10,40,280,32,32,*temp1,RED);
	char* temp2[20] = {"End fre(0~100M):"};
	lcd_show_string (10,high*1/8+40,250,32,32,*temp2,RED);
	char* temp3[20] = {"Fre Step(0~1M):"};
	lcd_show_string (10,high*2/8+40,250,32,32,*temp3,RED);
	char* temp4[20] = {"ChangeTime(0~1m):"};
	lcd_show_string (10,high*3/8+40,280,32,32,*temp4,RED);
}
//���ð�������״̬����
void Key_staset(uint8_t keyx,uint8_t sta)
{		  
	u16 i=(keyx-1)/3,j=(keyx-1)%3;
	if(keyx>16)return;
	if(sta == 1)  //�����������£����򲻲���
		lcd_fill(j*width*1/3+1,high/2+i*high*1/8+1,j*width*1/3+width*1/3-1,high/2+i*high*1/8+high*1/8-1,RED);  //�������򱻰��� ���򱻺�ɫ���
	else if( sta == 0)//�����ɿ�
	{
		lcd_fill(j*width*1/3+1,high/2+i*high*1/8+1,j*width*1/3+width*1/3-1,high/2+i*high*1/8+high*1/8-1,WHITE);
		lcd_show_string(j*width*1/3+70,high/2+high*1/8*i+35,32,32,32,(uint8_t*)key_menu[keyx-1],BLUE);	//������ɫ��������ʾ
	}
}
//�õ����������뺯��   ����ֵ��1-15
uint8_t Get_keynum()
{
	uint16_t i,j;
	static uint8_t key_x=-1 ;//�����ϴμ�ֵ
	uint8_t key=0;
	uint8_t state = 0;
	tp_dev.scan(0); 		 
	if(tp_dev.sta&TP_PRES_DOWN)  //������������
	{	
//	HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
//		printf("%d",tp_dev.x[0]);
		for(i=0;i<4;i++)
		{
			for(j=0;j<3;j++)
			{
			 	if(tp_dev.x[0]<(j*width*1/3+width*1/3)&&tp_dev.x[0]>(j*width*1/3)&&tp_dev.y[0]<(high/2+i*high*1/8+high*1/8)&&tp_dev.y[0]>(high/2+i*high*1/8))  //����ÿһ�������������ֵ
				{	
						
					key=i*3+j+1;	//i������ ÿһ�еı仯��Ҫ�仯����ֵ j������ ÿһ�б仯����Ҫ�仯һ��ֵ
//					printf("%d\r",key);//A == 2 B == 3
					break;	 		   
				}
			}
			if(key) //key!=0
			{	   
				if(key_x==key)key=0; 
				else 
				{
					state = 1; //���µİ���������
					key_x=key; //�����µļ�ֵ
					Key_staset(key_x,state);  
				}
				break;
			}
	  }
		return key; //return start for 1 ,2 ,3 ~
	}
	else if(key_x>=0)  //�����ɿ� �õ���ֵ
	{
		state = 0;
		Key_staset(key_x,state);
		key_x=-1;
	} 
	return 0; 
}
/**
* @brief   caculate the input keynum to 10 base value
* @param[in]     the keynum have get 
* @return the Dex num
*/

uint32_t show_number(uint8_t key_in)//��������ֵ����ʾ
{
	uint32_t getnum = 0;//return value
	static uint8_t cnt = 0;
	static uint16_t high_cnt = 0;
	static uint32_t getnum_lock = 0;
	char temp1[20];
	if(key_in == 10)
	{
		key_in = 0;
	}
	
	if(key_in == 11 && cnt >0)
	{
		cnt--;
	}else	if(key_in == 12)
	{
		cnt = 0;
		high_cnt+=100;
		if(high_cnt>=340)
		{
				high_cnt = 0;		
		}
		return getnum_lock;
	}else
	{
		counter[cnt] = key_in;
		cnt++;
	}
	for(int i=0; i<cnt; i++)
	{
		 getnum = getnum + counter[i] * pow(10,cnt-i-1);
	}
	getnum_lock = getnum;
	
	sprintf (temp1 ,"%dHz",getnum); 
	lcd_show_string (280,high_cnt+40,200,32,32,temp1,RED);

	return 0;
}

	
	
	

	
	

