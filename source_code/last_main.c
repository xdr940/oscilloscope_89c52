

#include <reg51.h>
 #define AIn P0
 #define sysOut P1
 #define N 16
 #define uchar  unsigned char
sbit OE = P3^4;
sbit EOC = P3^5;
sbit ST=P3^3;
sbit CLK=P3^2;
 int num2Disnum[9]={0xff,0xfe,0xFC,0xf8,0xf0,0xe0,0xc0,0x80,0x00}	;//ת����������ת�����������

sbit   C3=P2^3;
sbit   C2=P2^2;
sbit   C1=P2^1;
sbit   C0=P2^0;



 
void delay(char a){
	char i=0;
	  for(i=0;i<a*a;i++);
}
  
void transform(char num){
		switch(num){
			case 0:
				P2=0xF0;
				break;
			
			case 1:
				P2=0xF1;
				break;
			
			case 2:
			P2=0xF2;
				break;
			
			case 3:
				P2=0xF3;
				break;
			
			case 4:
				P2=0xF4;
				break;
			
			case 5:
				P2=0xF5;
				break;
			
			case 6:
				P2=0xF6;
				break;
			
			case 7:
				P2=0xF7;
				break;
			
			case 8:
				P2=0xF8;
				break;
			
			case 9:
				P2=0xF9;
				break;
			
			case 10:
			P2=0xFA;
				break;
			
			case 11:
				P2=0xFB;
				break;
			
			case 12:
				P2=0xFC;
				break;
			
			case 13:
				P2=0xFD;
				break;
			
			case 14:
				P2=0xFE;
				break;
			
			case 15:
				P2=0xFF;
				break;
			
		}
	}
	 
void display(unsigned char F[]){
  	 //�Ͱ�F��ӡһ��
	 int i;
	 
	for(i =0;i<16;i++){
		P1=0xff;	//ȫ��	 	
 	   transform(i);//λѡ
	   		
    	P1=F[i]; 	 //��ֵ	 //���������⣬�����������ͬʱ���и���
		delay(6);	 //�����ʱ����
		
	}				
  
}

void initT0(){
	
		TMOD = 0x02;	  //0000 0010 ѡ��T0��ʱ��������ѡ��ʱ0��ѡ��ʽ2��λ��װ��
		TH0=0x37;				//0x14  �����ѡ���adc��ʱ��Ƶ��				
		TL0=0;
		IE=0X82;			  //1000 0010 ����T0
		TR0=1;				 //TCON����T0



	}

   
  void initADC0908(){
	   
	   	OE =1 ;				  //ʹ�ܶ�
		EOC=1;			 //EndOfConvert  ת����������źţ�������Ϊ1������ת��Ϊ0
		ST=1;		//STart ADת�������ź������
		CLK=1;
			   
	   
	   }

 void Timer_INT()interrupt 1{
		  
		  CLK=!CLK;
		  
		  }

unsigned char ADC0809ConvertC0(){

		 unsigned char ADtemp;			 //ִֻ��һ��

		

		
			ST=1;
		
			ST=0; //�������壬�����ź�

			while(EOC==0);		  //��EOCΪ1��ʱ��ת�������������ߣ���ʱ2us
		 
			OE=1;				   //�ɼ����֮���������OE=1	//��һ�κ��� 7ms�������Ͷ���2us�ܿ���
			
			ADtemp=AIn;		   //157us��ʱ��//�����ĳ�ͬһ������ֻ����2 us������ת��̫��
			//OE=0;
			return ADtemp;			 //��ʱ 1us
		 
		 
		 }


void main(){

	   	 idata char F[16]={0x18};
	 int i=0;
   	unsigned char  ADout=0;
	 char num_dis=0;
	char adcout=0;
	int num0_8;
	 //ѡ��0��ģ���
	 initADC0908();
	 initT0();


	 

	  while(1){
  		  
		for(i=0;i<16;i++){
		ADout=ADC0809ConvertC0()/15; //0-256֮�� �����0-8
		 //��ʱADout��0-8֮��
		 delay(2);
	 num_dis= num2Disnum[ADout];
		 F[i]=num_dis;
	
		}
			display(F);
			  display(F);
			 display(F);
			 display(F);

			//��ͣ�Ĵ�ֵ �����������������12us	��Լ83KHz
		
		


		
		// delay(4);					//����Ƶ�ʿ���
	

	  }//while
   	 
	 
	 
	
	 
	 
	 }
   
 
