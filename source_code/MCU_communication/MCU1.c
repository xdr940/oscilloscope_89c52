//MCU1

#include <reg51.h>
#define   uchar		 unsigned char
#define OutPut P1
#define N 16
sbit ST= P3^0;	  //�����鿪ʼ��ʱ�� ��Ϊ�ߵ�ƽ
sbit sendEn= P3^6;	  //��һ��Ԫ�ظߵ�ƽһ��,���Է���==��д
sbit EndRead = P3^7;

 idata  unsigned  char F[]={1,1,2,3,4,0xFF,6,7,8,9,10,11,12,13,14,15 };	//�ɱ�����һ��Ҫ��data�ؼ��֣�Ҫ��Ȼȫ���㣡
  
	

int i=0;
   
 void delay( uchar a){
	uchar i =0;
	 	for( i=0;i<a;i++);
	 
}
   void send()	{
 		 uchar i =0;
	  	
		ST=1;//��ʼ�������飬��ʱMCU2�����жϴ�����
	//	ST=0;
		 for(i=0;i<16;i++){
		  
		     while(!EndRead);	//d�Է��յ���Ϣ��������һ֡��Ϣ
			
		
		   P1=F[i];		//2us ���� ������0-9 �ĸ���	
		   
		    sendEn=1;
					delay(2);
		   sendEn=0;
		   	//	delay(2);
	   	}//for	

	   	ST=0;//���ͽ���
   	
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



