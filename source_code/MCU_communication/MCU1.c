//MCU1

#include <reg51.h>
#define   uchar		 unsigned char
#define OutPut P1
#define N 16
sbit ST= P3^0;	  //传数组开始的时候 置为高电平
sbit sendEn= P3^6;	  //传一个元素高电平一下,可以发送==可写
sbit EndRead = P3^7;

 idata  unsigned  char F[]={1,1,2,3,4,0xFF,6,7,8,9,10,11,12,13,14,15 };	//可变数组一定要加data关键字，要不然全是零！
  
	

int i=0;
   
 void delay( uchar a){
	uchar i =0;
	 	for( i=0;i<a;i++);
	 
}
   void send()	{
 		 uchar i =0;
	  	
		ST=1;//开始传送数组，此时MCU2进入中断处理函数
	//	ST=0;
		 for(i=0;i<16;i++){
		  
		     while(!EndRead);	//d对方收到信息，更新下一帧信息
			
		
		   P1=F[i];		//2us 左右 数据是0-9 四根线	
		   
		    sendEn=1;
					delay(2);
		   sendEn=0;
		   	//	delay(2);
	   	}//for	

	   	ST=0;//传送结束
   	
  }

  void change(int F[])	{
  int i=0;

  for(i=0;i<16;i++){
  	F[i]=40;
  
  }
  
  }
  void inits (){
  	   ST=0;
	  sendEn=0;
  }
void main(){
	
 	  // inits();
	
	   
 // 	change();
		  
	 


	 send();
	
	
		  



		
		

	


}



