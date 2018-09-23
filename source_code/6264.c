//6264

#include <reg51.h>
#include <absacc.h> 



#define OFFRAMBASE 0x100

unsigned char xdata offRamVal0 _at_ 0x300; //地址overFlow ，有效地址直到0x01ff，当超过后，进位，后面位数都为0，故此地址实际值为0
unsigned char xdata offRamVal1 _at_ 0x01;
unsigned char xdata offRamVal2 _at_ 0xFF;
int main()
{

	unsigned char idata index = 1;
	//----一般赋值测试
	offRamVal0 = 0xAA;
	offRamVal1 = 0xCC;
	offRamVal2 = 3;
	//-----基址变址赋值测试
	for(index=0;index<0x10;index++)
	{
		XBYTE[index+OFFRAMBASE] = 0x55;	
	}		
	return 0;
} 
 // void main(){
  
//	unsigned char temp _at_ 0x1020;
   
 // }







