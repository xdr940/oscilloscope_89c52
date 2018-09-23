

#include <reg51.h>
 #define AIn P0
 #define sysOut P1
 #define N 16
 #define uchar  unsigned char
sbit OE = P3^4;
sbit EOC = P3^5;
sbit ST=P3^3;
sbit CLK=P3^2;
 int num2Disnum[9]={0xff,0xfe,0xFC,0xf8,0xf0,0xe0,0xc0,0x80,0x00}	;//转换表，从数字转换成输出的字

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
  	 //就把F打印一次
	 int i;
	 
	for(i =0;i<16;i++){
		P1=0xff;	//全灭	 	
 	   transform(i);//位选
	   		
    	P1=F[i]; 	 //赋值	 //这里有问题，如果这两步能同时进行更好
		delay(6);	 //这个延时正好
		
	}				
  
}

void initT0(){
	
		TMOD = 0x02;	  //0000 0010 选择T0定时计数器，选择定时0，选择方式2八位自装填
		TH0=0x37;				//0x14  这个是选择给adc的时钟频率				
		TL0=0;
		IE=0X82;			  //1000 0010 开启T0
		TR0=1;				 //TCON开启T0



	}

   
  void initADC0908(){
	   
	   	OE =1 ;				  //使能端
		EOC=1;			 //EndOfConvert  转换结束输出信号，结束后为1，正在转换为0
		ST=1;		//STart AD转换启动信号输入端
		CLK=1;
			   
	   
	   }

 void Timer_INT()interrupt 1{
		  
		  CLK=!CLK;
		  
		  }

unsigned char ADC0809ConvertC0(){

		 unsigned char ADtemp;			 //只执行一次

		

		
			ST=1;
		
			ST=0; //给出脉冲，启动信号

			while(EOC==0);		  //当EOC为1的时候，转换结束，往下走，耗时2us
		 
			OE=1;				   //采集完成之后，允许输出OE=1	//第一次很慢 7ms，后来就都是2us很快了
			
			ADtemp=AIn;		   //157us的时间//后来改成同一个类型只用了2 us，类型转换太费
			//OE=0;
			return ADtemp;			 //耗时 1us
		 
		 
		 }


void main(){

	   	 idata char F[16]={0x18};
	 int i=0;
   	unsigned char  ADout=0;
	 char num_dis=0;
	char adcout=0;
	int num0_8;
	 //选择0号模拟道
	 initADC0908();
	 initT0();


	 

	  while(1){
  		  
		for(i=0;i<16;i++){
		ADout=ADC0809ConvertC0()/15; //0-256之间 变成了0-8
		 //此时ADout是0-8之间
		 delay(2);
	 num_dis= num2Disnum[ADout];
		 F[i]=num_dis;
	
		}
			display(F);
			  display(F);
			 display(F);
			 display(F);

			//不停的传值 采样周期最快现在是12us	大约83KHz
		
		


		
		// delay(4);					//采样频率控制
	

	  }//while
   	 
	 
	 
	
	 
	 
	 }
   
 
