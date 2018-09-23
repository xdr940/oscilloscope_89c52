#include <stdio.h>
#include <math.h>
#define typ float
typedef struct {
	float real;
	float image;
}complex;
//求共轭 
complex conjugate(complex a){
	complex b;
	b.real=a.real;
	b.image=-a.image;
	return b;
}
//复数加 
complex add(complex a,complex b){
	complex c;
	c.real=a.real+b.real;
	c.image=a.image+b.image;
	return c; 
	
} 
complex minus(complex a,complex b){
	complex c;
	c.real=a.real-b.real;
	c.image=a.image-b.image;
	return c;
}

typ amp(complex a){
	return sqrt((a.real*a.real)+(a.image*a.image));
}

void FFT16(float x[],float F[]){//这里改代码 
	
/*-------第0级(时域输入)--------------*/	

/*-----第1级-----------------*/	
	complex X7[2];
	complex X8[2];
	complex X9[2];
	complex X10[2];
	complex X11[2];
	complex X12[2];
	complex X13[2];		 
	complex X14[2];
	
/*-----第2级-----------------*/		
	
	complex X3[4];
	complex X4[4];
	complex X5[4];
	complex X6[4];
/*-----第3级-----------------*/	 
	complex X1[8];
	complex X2[8]; 
	
/*------第四级（频域输出）------------*/	
	complex X[16]; 


	
	/*d蝶形运算*/
	
//------------------------	
	X7[0].real=x[0];
	X7[0].image=x[8];
	
	X7[1].real=x[0];
	X7[1].image=-x[8];
//-------------------------	
	X8[0].real=x[4];
	X8[0].image=x[12];
	
	X8[1].real=x[4];
	X8[1].image=-x[12];
//-----------------------------	
	X9[0].real=x[2];
	X9[0].image=x[10];
	X9[1].real=x[2];
	X9[1].image=-x[10];
//-------------------------------	
	X10[0].real=x[6];
	X10[0].image=x[14];
	X10[1].real=x[6];
	X10[1].image=-x[6];
	
	
	X11[0].real=x[1];
	X11[0].image=x[9];
	X11[1]=conjugate(X11[0]);
	
	X12[0].real=x[5];
	X12[0].image=x[13];
	X12[1]=conjugate(X12[0]);
	
	X13[0].real=x[3];
	X13[0].image=x[11];
	X13[1]=conjugate(X13[0]);
	
	X14[0].real=x[7];
	X14[0].image=x[15];
	X14[1]=conjugate(X14[0]);
	
/*-----------第二级-------------------------*/	
	
	X3[0]=add(X7[0],X8[0]);
	X3[1]=add(X7[1],X8[1]);
	X3[2]=minus(X7[0],X8[0]);
	X3[3]=minus(X7[1],X8[1]);
	
	X4[0]=add(X9[0],X10[0]);
	X4[1]=add(X9[1],X10[1]);
	X4[2]=minus(X9[0],X10[0]);
	X4[3]=minus(X9[1],X10[1]);
	
	X5[0]=add(X11[0],X12[0]);
	X5[1]=add(X11[1],X12[1]);
	X5[2]=minus(X11[0],X12[0]);
	X5[3]=minus(X11[1],X12[1]);
	
	X6[0]=add(X13[0],X14[0]);
	X6[1]=add(X13[1],X14[1]);
	X6[2]=minus(X13[0],X14[0]);
	X6[3]=minus(X13[1],X14[1]);
	/*-----------第3级-------------------------*/
	
		int j;
		for(j=0;j<4;j++){ 
			X1[j]=add(X3[j],X4[j]);
			X1[j+4]=minus(X3[0],X4[0]); 
		}
	
		for(j=0;j<4;j++){
			X2[j]=add(X5[j],X6[j]);
			X2[j+4]=minus(X5[0],X6[0]);
		}
	
	
		
/*-------------第四级（频域输出）---------------------*/	
	for(j=0;j<8;j++){
		X[j]=add(X1[j],X2[j]);
		X[j+8]=minus(X1[j],X2[j]);
	}
	int i=0;
	for(;i<16;i++){
		F[i]=amp(X[i]);	
	}
	
	
	
}


int main(){
	
	//delta 
	typ x[16]={0,0,0,0,
			   1,0,0,0,
			   0,0,0,0,
			   0,0,0,0} ;
		   
	//const 
/*	typ x[16]={1,1,1,1,
			   1,1,1,1,
			   1,1,1,1,
			   1,1,1,1} ;*/
		
	/*	typ x[16]={0,0,0,0,
			   0,0,0,0,
			   1,1,1,1,
			   1,1,1,1} ;*/
			   	   
			   		   
		float F[16]={0};
	FFT16(x,F);
	
	float temp;
	int i=0;
	for(;i<16;i++){
		printf("%f\n",F[i]);
		
	}
	
	

	
	
	return 0;
	
	
	
}
 
