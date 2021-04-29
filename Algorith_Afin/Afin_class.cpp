#include <iostream>
#include<stdlib.h>
#include <string>
#include "Afin_class.h"

using namespace std;

//Maximo comun divisor
int Euclides(int a, int b){
	int q=a/b;
	int r=a-(q*b);
	if(r==0){
		return b;
	}
	else{
		Euclides(b,r);
	}
}

//Euclides extendido: lo modificamos para q retorne x
int Euclides_ext(int a,int b){
	int q=a/b;
	int r=a-(q*b);
	int x1=1;int x2=0;int y1=0;int y2=1;
	int x=x1-(q*x2);
	int y=y1-(q*y2);
	while(r>1){
		
		q=a/b;
		r=a-(q*b);
		a=b;
		b=r;
		x=x1-(q*x2);
		y=y1-(q*y2);
		x1=x2;
		x2=x;
		y1=y2;
		y2=y;
			
	}
	//cout<<"este es x:"<<x<<endl;
	return x;
}

//MOdulo
int MOD(int a,int n){
  	int q =a/n;
  	int r=a-(q*n);//Teniendo en cuenta a = q × n + r
	if(r<0){
    	if (q<=0){--q;r=a-(q*n);}
    	if(q>0){++q;r=a-(q*n);}
 	 }
	//cout<< "cociente:"<<q<<endl;
  	//cout<< "residuo:"<<r<<endl;
  	return r;
}

Afin::Afin(){
	//Realizacion de clave
	pass_b=1+rand()%(26-1);
	int a=1+rand()%(26-1);
	pass_a=Euclides(a,abc.length());
	while (pass_a != 1){
		a=1+rand()%(26-1);
		pass_a=Euclides(a,abc.length());
	}
	//cout<<"claves:"<<endl<<pass_a<<endl<<pass_b<<endl;
}
Afin::Afin (int a, int b){
	pass_a=MOD(Euclides_ext(a,abc.length()),abc.length());
	//cout<<"claves:"<<endl<<pass_a<<endl<<pass_b<<endl;
	pass_b=b;
}
void Afin::cifrado(string message){
			
	for (int i=0;i<message.length();i++){
		int indice=abc.find(message[i]);
		
		if(indice==string::npos){
			message[i]=' ';
		}
		else{
			int cipher=MOD(((pass_a * indice)+pass_b),abc.length());
			message[i]=abc[cipher];
		}
	}

	cout<<"mensaje cifrado:"<<message;
}

void Afin::descifrado(string message){
			
	for (int i=0;i<message.length();i++){
		int indice=abc.find(message[i]);
		if(indice==string::npos){
			message[i]=' ';
		}
		else{
			int encrip=MOD(pass_a*(indice-pass_b),abc.length());
			message[i]=abc[encrip];
		}
	}
	cout<<"mensaje descifrado:"<<message;
}




