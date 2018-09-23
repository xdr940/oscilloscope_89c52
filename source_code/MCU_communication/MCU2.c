//MCU2
#include <reg51.h>

#define InPut P0;//P1������λ��������
#define N 16
#define   uchar		 unsigned char
#define Input  P0
sbit ST = P3^2;	   //�ȴ���ʼ
 
sbit EndRead=P3^6;//����ȷ�� WR���ӣ�RD���
 sbit InEn =P3^7;  //�ȴ���� sendEn RD���ӣ�WR���

	 
data unsigned  char F[16]={22,22,22}; //��д
	 void delay( uchar a){
	uchar i =0;
	 	for( i=0;i<a;i++);
	 
}
  
void initT0(){
	
		TMOD = 0x06;	  //0000 0010 ѡ��T0��ʱ��������ѡ�����1��ѡ��ʽ2��λ��װ��
		TH0=254;				//0x14  �����ѡ���adc��ʱ��Ƶ��				
		TL0=254;
		IE=0X82;			  //1000 0010 ����T0
		TR0=1;				 //TCON����T0
	}
  void initINT0(){
 	 EA=1;	  // �ж��ܿ���
	EX0=1	; //  �ⲿ�ж��ܿ���

	//��INT0��Ϊ�ж�
	IT1=1;	   //ʹ��!INT0,���ش��� 
	}

   void func_INT0()interrupt 0{
   	
   	   uchar i =0;
	 	EndRead=0;
		
	  for(;i<N;i++){
		
	   while(!InEn) ; //�������� ,3.7
   		 F[i]=Input;	  //��P1�ڵ�����洢����
	  	 	  //��֤
			
		  EndRead=1;		//����ȷ��
			  delay(2);
		 
		 EndRead=0;
			// delay(2);
	  }
	 
	   EndRead=0;


   	 
   }
void main(){
   	 initINT0();
	  P1=0xFF;	
	  P3=0xFF;
	  ST=1;//������ڣ���������ж��źţ����͵�ƽ��Ч��֮ǰ�÷������������
	  InEn=1;//ͬ�� ���������
	  EndRead=0;   //д���ˣ�Ҫ��Ȼ��һ��������
	while(1);

}



