//6264

#include <reg51.h>
#include <absacc.h> 



#define OFFRAMBASE 0x100

unsigned char xdata offRamVal0 _at_ 0x300; //��ַoverFlow ����Ч��ֱַ��0x01ff���������󣬽�λ������λ����Ϊ0���ʴ˵�ַʵ��ֵΪ0
unsigned char xdata offRamVal1 _at_ 0x01;
unsigned char xdata offRamVal2 _at_ 0xFF;
int main()
{

	unsigned char idata index = 1;
	//----һ�㸳ֵ����
	offRamVal0 = 0xAA;
	offRamVal1 = 0xCC;
	offRamVal2 = 3;
	//-----��ַ��ַ��ֵ����
	for(index=0;index<0x10;index++)
	{
		XBYTE[index+OFFRAMBASE] = 0x55;	
	}		
	return 0;
} 
 // void main(){
  
//	unsigned char temp _at_ 0x1020;
   
 // }







