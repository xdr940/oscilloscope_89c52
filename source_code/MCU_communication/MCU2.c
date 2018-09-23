//MCU2
#include <reg51.h>

#define InPut P0;//P1口做八位并行输入
#define N 16
#define   uchar		 unsigned char
#define Input  P0
sbit ST = P3^2;	   //等待开始
 
sbit EndRead=P3^6;//读完确认 WR口子，RD标号
 sbit InEn =P3^7;  //等待输出 sendEn RD口子，WR标号

	 
data unsigned  char F[16]={22,22,22}; //乱写
	 void delay( uchar a){
	uchar i =0;
	 	for( i=0;i<a;i++);
	 
}
  
void initT0(){
	
		TMOD = 0x06;	  //0000 0010 选择T0定时计数器，选择计数1，选择方式2八位自装填
		TH0=254;				//0x14  这个是选择给adc的时钟频率				
		TL0=254;
		IE=0X82;			  //1000 0010 开启T0
		TR0=1;				 //TCON开启T0
	}
  void initINT0(){
 	 EA=1;	  // 中断总开关
	EX0=1	; //  外部中断总开关

	//用INT0作为中断
	IT1=1;	   //使得!INT0,边沿触发 
	}

   void func_INT0()interrupt 0{
   	
   	   uchar i =0;
	 	EndRead=0;
		
	  for(;i<N;i++){
		
	   while(!InEn) ; //读入数据 ,3.7
   		 F[i]=Input;	  //把P1口的输入存储起来
	  	 	  //验证
			
		  EndRead=1;		//读完确认
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
	  ST=1;//做输入口，这个输入中断信号，来低电平有效，之前用反相器处理过了
	  InEn=1;//同上 ，做输入口
	  EndRead=0;   //写死了，要不然第一个读不到
	while(1);

}



