#include "triode_judge.h"
#define width	480
#define high	800	
#define IO(n)		PFout(n)
/*
		IO0		---->		PF0		PFout(0)
		IO1		---->		PF1		PFout(1)
		IO2		---->		PF2		PFout(2)
		IO3		---->		PF3		PFout(3)
		IO4		---->		PF4		PFout(4)
		IO5		---->		PF5		PFout(5)
*/
/* test value */
static double adcbuf[3][3] = {0};
static double adcbuf1[3][3] = {0};
static uint8_t buf[3][3] = {0} ;
static uint8_t baseindex[3] = {0,1,2};//B , C , E
static double Ube = 0;
uint8_t TroBase_judge(void)
{
///
	IO(0) = 0;
	IO(1) = 1;
	IO(2) = 1;
	HAL_Delay(500);
	for(int i=0; i<3; i++)
	{
		HAL_ADC_Start(&hadc1); 
		HAL_ADC_PollForConversion(&hadc1,10);
		int getvalue =HAL_ADC_GetValue(&hadc1);      
		adcbuf[0][i] = (double)getvalue*3.3/4096;
		if(adcbuf[0][i] > 0.05)
			buf[0][i] = 1;
		else 
			buf[0][i] = 0;
		
		char temp1[20];
		sprintf (temp1 ,"%.3fV",adcbuf[0][i]); 
		lcd_show_string (10+i*width*1/5,0,280,32,32,temp1,RED);
	}
	HAL_ADC_Stop(&hadc1);
///
	IO(0) = 1;
	IO(1) = 0;
	IO(2) = 1;
	HAL_Delay(500);
	for(int i=0; i<3; i++)
	{
		HAL_ADC_Start(&hadc1); 
		HAL_ADC_PollForConversion(&hadc1,10);
		int getvalue =HAL_ADC_GetValue(&hadc1);      		
		adcbuf[1][i] = (double)getvalue*3.3/4096;
		if(adcbuf[1][i] > 0.05)
			buf[1][i] = 1;
		else
			buf[1][i] = 0;
		
		char temp2[20];
		sprintf (temp2,"%.3fV",adcbuf[1][i]); 
		lcd_show_string (10+i*width*1/5,high*1/10,280,32,32,temp2,RED);
	}
	HAL_ADC_Stop(&hadc1);
///
	IO(0) = 1;
	IO(1) = 1;
	IO(2) = 0;
	HAL_Delay(500);
	for(int i=0; i<3; i++)
	{
		HAL_ADC_Start(&hadc1); 
		HAL_ADC_PollForConversion(&hadc1,10);
		int getvalue =HAL_ADC_GetValue(&hadc1);
		adcbuf[2][i] = (double)getvalue*3.3/4096;
		if(adcbuf[2][i] > 0.05)
			buf[2][i] = 1;
		else 
			buf[2][i] = 0;
		
		char temp3[20];
		sprintf (temp3 ,"%.3fV",adcbuf[2][i]); 
		lcd_show_string (10+i*width*1/5,high*2/10,280,32,32,temp3,RED);
	}
	HAL_ADC_Stop(&hadc1);

	int counter = 0;
	int cnt ;
	int i,j;
	for(i=0; i<3; i++)
	{
		cnt = 0;
		for(j=0; j<3; j++)
		{
//			printf("%d\t",buf[i][j]);
			if(buf[i][j]==1)
			{
				++cnt;
			}
		}
		if(cnt==3)
		{
			++counter;
		}
//		printf("\r\n");
	}
	
	if(counter==1)//judge NPN
	{
		double max = 0;//0:max value		1:max index
		for(i=0; i<3; i++)
		{
			cnt = 0;
			for(j=0; j<3; j++)
			{
				if(buf[i][j]==1)
				{
					++cnt;
				}
			}
			/* NPN base correspond the max index */
			if(cnt==3)
			{
//				printf("%f	%f	%f\r\n",adcbuf[i][0],adcbuf[i][1],adcbuf[i][2]);
				for(j=0; j<3; j++)
				{
					if(adcbuf[i][j] > max)  
					{
						max = adcbuf[i][j];
						int rem = baseindex[0];
						baseindex[0] = j ;
						baseindex[j] = rem;
					}
				}
				break;
			}
		}
		
	}
	else if(counter==2)//judge PNP
	{
		for(i=0; i<3; i++)
		{
			cnt = 0;
			for(j=0; j<3; j++)
			{
				if(buf[i][j]==1)
				{
					++cnt;
				}
			}
			/* NPN base correspond the one index */
			if(cnt==1)
			{
				for(j=0; j<3; j++)
				{
					if(buf[i][j] == 1)  
					{
						/* let the B const corrspond the index[0] */
						int rem = baseindex[0];
						baseindex[0] = j ;
						baseindex[j] = rem;
						break;
					}
				}
				break;
			}
		}
	}
	return counter;

}

void	TroCE_judge(uint8_t Tro_flag)
{
	printf("%d  %d  %d\r\n",baseindex[0],baseindex[1],baseindex[2]);
	if(Tro_flag==1)	//NPN
	{
///
		IO(baseindex[0]) = 0;
		IO(baseindex[1]) = 1;
		IO(baseindex[2]) = 1;
		HAL_Delay(500);
		for(int i=0; i<3; i++)
		{
			HAL_ADC_Start(&hadc1); 
			HAL_ADC_PollForConversion(&hadc1,10);
			int getvalue =HAL_ADC_GetValue(&hadc1);      
			adcbuf1[0][i] = (double)getvalue*3.3/4096;

			char temp1[20];
			sprintf (temp1 ,"%.3fV",adcbuf1[0][i]); 
			lcd_show_string (10+i*width*1/5,high*5/10,280,32,32,temp1,RED);
		}
		HAL_ADC_Stop(&hadc1);
///
		IO(baseindex[0]) = 0;
		IO(baseindex[1]) = 0;
		IO(baseindex[2]) = 1;
		HAL_Delay(500);
		for(int i=0; i<3; i++)
		{
			HAL_ADC_Start(&hadc1); 
			HAL_ADC_PollForConversion(&hadc1,10);
			int getvalue =HAL_ADC_GetValue(&hadc1);      
			adcbuf1[1][i] = (double)getvalue*3.3/4096;

			char temp1[20];
			sprintf (temp1 ,"%.3fV",adcbuf1[1][i]); 
			lcd_show_string (10+i*width*1/5,high*6/10,280,32,32,temp1,RED);
		}
		HAL_ADC_Stop(&hadc1);
///
		IO(baseindex[0]) = 0;
		IO(baseindex[1]) = 1;
		IO(baseindex[2]) = 0;
		HAL_Delay(500);
		for(int i=0; i<3; i++)
		{
			HAL_ADC_Start(&hadc1); 
			HAL_ADC_PollForConversion(&hadc1,10);
			int getvalue =HAL_ADC_GetValue(&hadc1);      
			adcbuf1[2][i] = (double)getvalue*3.3/4096;

			char temp1[20];
			sprintf (temp1 ,"%.3fV",adcbuf1[2][i]); 
			lcd_show_string (10+i*width*1/5,high*7/10,280,32,32,temp1,RED);
		}
		HAL_ADC_Stop(&hadc1);
				
		if(adcbuf1[1][baseindex[1]] > adcbuf1[2][baseindex[2]])
		{
			int rem = baseindex[2];
			baseindex[2] = baseindex[1] ;
			baseindex[1] = rem;
		}
		
	}
	else if(Tro_flag==2) //PNP
	{
///
		IO(baseindex[0]) = 0;
		IO(baseindex[1]) = 1;
		IO(baseindex[2]) = 1;
		HAL_Delay(500);
		for(int i=0; i<3; i++)
		{
			HAL_ADC_Start(&hadc1); 
			HAL_ADC_PollForConversion(&hadc1,10);
			int getvalue =HAL_ADC_GetValue(&hadc1);      
			adcbuf1[0][i] = (double)getvalue*3.3/4096;

			char temp1[20];
			sprintf (temp1 ,"%.3fV",adcbuf1[0][i]); 
			lcd_show_string (10+i*width*1/5,high*5/10,280,32,32,temp1,RED);
		}
		HAL_ADC_Stop(&hadc1);
		Ube = adcbuf1[0][baseindex[0]];
///
		IO(baseindex[0]) = 0;
		IO(baseindex[1]) = 0;
		IO(baseindex[2]) = 1;
		HAL_Delay(500);
		for(int i=0; i<3; i++)
		{
			HAL_ADC_Start(&hadc1); 
			HAL_ADC_PollForConversion(&hadc1,10);
			int getvalue =HAL_ADC_GetValue(&hadc1);      
			adcbuf1[1][i] = (double)getvalue*3.3/4096;

			char temp1[20];
			sprintf (temp1 ,"%.3fV",adcbuf1[1][i]); 
			lcd_show_string (10+i*width*1/5,high*6/10,280,32,32,temp1,RED);
		}
		HAL_ADC_Stop(&hadc1);
///
		IO(baseindex[0]) = 0;
		IO(baseindex[1]) = 1;
		IO(baseindex[2]) = 0;
		HAL_Delay(500);
		for(int i=0; i<3; i++)
		{
			HAL_ADC_Start(&hadc1); 
			HAL_ADC_PollForConversion(&hadc1,10);
			int getvalue =HAL_ADC_GetValue(&hadc1);      
			adcbuf1[2][i] = (double)getvalue*3.3/4096;

			char temp1[20];
			sprintf (temp1 ,"%.3fV",adcbuf1[2][i]); 
			lcd_show_string (10+i*width*1/5,high*7/10,280,32,32,temp1,RED);
		}
		HAL_ADC_Stop(&hadc1);
				
		if(adcbuf1[1][baseindex[1]] < adcbuf1[2][baseindex[2]])
		{
			int rem = baseindex[1];
			baseindex[1] = baseindex[2] ;
			baseindex[2] = rem;
		}

	}
	Ube = adcbuf1[0][baseindex[0]] - adcbuf1[0][baseindex[2]];
	printf("%f\r\n",Ube);
	printf("%d  %d	%d\r\n",baseindex[0],baseindex[1],baseindex[2]);
	
	char temp[10];
	sprintf (temp ,"Ube:%.4fV",Ube); 
	lcd_show_string (10,high*8/10,280,32,32,temp,RED);
	
	char* temp1[3] = {"B","C","E"};
	for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if(baseindex[j]==i)
				{
					lcd_show_string (10+i*width*1/5,high*9/10,280,32,32,temp1[j],RED);
				}
			}
		}
	
	while(1);
}






