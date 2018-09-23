

#include <reg51.h>
 #define AIn P0
 #define sysOut P1
sbit OE = P3^4;
sbit EOC = P3^5;
sbit ST=P3^3;
sbit CLK=P3^2;

//sbit ADDA = P2^0;		 //这里只选择一条模拟道
//sbit ADDB= P2^1;
//sbit ADDC = P2^2;





 
void delay(char a){
	char i=0;
	  for(i=0;i<a;i++);
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
   	 int count =0;
   	unsigned char  ADout=0;
	 //选择0号模拟道
	 initADC0908();
	 initT0();


	 

	  while(1){
  		  
	 
		 ADout= ADC0809ConvertC0();		//不停的传值 采样周期最快现在是12us	大约83KHz
		  P1=ADout;
		
		// delay(0);					//采样频率控制
	

	  }//while
   	 
	 
	 
	
	 
	 
	 }
   
 
