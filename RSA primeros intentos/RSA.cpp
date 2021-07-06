#include <iostream>
#include<stdlib.h>
#include <time.h>
#include <string>
#include <bits/stdc++.h>
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
//Exponenciacion modular
int Expo_modular(int clave,int m,int n){
  int exp=clave;
  int D=1;
  int Aux=m;
  int i=0;
  bitset<32>cadena(clave);
  while(exp>=1){
    if(cadena[i]==1){
      D=D*Aux;
      D=MOD(D,n);
    }
    exp=exp/2;
    i++;
    Aux=Aux*Aux;
    Aux=MOD(Aux,n);
  }
  //cout<<D<<endl;
  return D;
}
//Generacion de clave
int Generacion(int clave){
  srand(time(NULL));
  int count=3;
  while(count>2){
    count=0;
    for(int i=1;i<clave;i++){
      if(clave%i==0){
        count++;
      }
    }
    if(count<=2){
      break;
    }
    clave=1+rand()%(100-1);
  }
  //cout<<"es primo: "<<p<<endl;
  return clave;
}

class RSA{
	private:
		int p,q,N,d;
		int e;
		string alfabeto="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	public:
		
		RSA(int en, int n){//recibe clave publica y n 
			e=en;N=n;
		}
		RSA (int e){//solo debe reciibir bits
			//generar claves 
			p=Generacion(1+rand()%(100-1));
			q=Generacion(1+rand()%(100-1));
			cout<<"p:"<<p<<" q:"<<q<<endl;
			N=p*q;
			d=MOD(Euclides_ext(e,(q-1)*(p-1)),(q-1)*(p-1));
			cout<<"La clave privada es: "<<d<<endl;
		}
		
		void cifrado(int message){
			message=Expo_modular(e,message,N);
			cout<<"mensaje cifrado:"<<message;
		}
		void descifrado(int message){
			message=Expo_modular(d,message,N);
			cout<<"mensaje descifrado:"<<message;
		}		
	
	
};
int main(){
	int message=549;
	//Emisor
	//RSA a(101,731);
	//a. cifrado (message);
	//Receptor
	RSA b(5);
	b. descifrado (message);
}






