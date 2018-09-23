

#include <reg51.h>
 #define AIn P0
 #define sysOut P1
sbit OE = P3^4;
sbit EOC = P3^5;
sbit ST=P3^3;
sbit CLK=P3^2;

//sbit ADDA = P2^0;		 //����ֻѡ��һ��ģ���
//sbit ADDB= P2^1;
//sbit ADDC = P2^2;





 
void delay(char a){
	char i=0;
	  for(i=0;i<a;i++);
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
   	 int count =0;
   	unsigned char  ADout=0;
	 //ѡ��0��ģ���
	 initADC0908();
	 initT0();


	 

	  while(1){
  		  
	 
		 ADout= ADC0809ConvertC0();		//��ͣ�Ĵ�ֵ �����������������12us	��Լ83KHz
		  P1=ADout;
		
		// delay(0);					//����Ƶ�ʿ���
	

	  }//while
   	 
	 
	 
	
	 
	 
	 }
   
 
