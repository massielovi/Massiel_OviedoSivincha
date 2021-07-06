#include <iostream>
#include<stdlib.h>
#include <time.h>
#include <string>
#include <sstream> 
#include <vector>
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
//con vector:
/*vector Euclides_ext(int a,int b){
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
	vector<int> result(2);
	result={x,y};
	//cout<<"este es x:"<<x<<endl;
	return result;
}*/

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
		//string abc="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
		string abc="abcdefghijklmnopqrstuvwxyz ";
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
		
		string cifrado(string message){
			int last=abc.length()-1;
			ostringstream cadenaSalida; 
		    cadenaSalida<<last;
		    string cifras=cadenaSalida.str();
		    
			string mensaje;
			//encontramos los indices de las letras del mensaje
			for (int i=0;i<message.length();i++){
					
					int indice=abc.find(message[i]);
					stringstream indices;
		    		indices <<indice;
		    		string num = indices.str();
		    		//Aqui agregamos los ceros deacuerdo a las cifras 
					if(cifras.length()!=num.length()){
						int aux=cifras.length()-num.length();
						string agregar(aux,'0');
						num=agregar+num;
					}
					mensaje.append(num);
			}
			//encontrar numero de digitos haciendolo string y numero de digitos es la longitud del string
			ostringstream Digitos; 
		    Digitos<<N;
		    string N_digitos=Digitos.str();
			int j=0;
			string cifrado;
			while(j<mensaje.length()){
				//cout<<"este es j:"<<j<<endl;
				string aux=mensaje.substr(j,N_digitos.length()-1);
				//Convertimos el sring en entero
				j=j+(N_digitos.length()-1);
				stringstream geek(aux);
		    	int x = 0;
		    	geek >> x;
				int message=Expo_modular(e,x,N);
				
				stringstream final;
				final <<message;
				string finals=final.str();
		    	//Aqui agregamos los ceros deacuerdo a las cifras 
				if(N_digitos.length()!=finals.length()){
					int aux=N_digitos.length()-finals.length();
					string agregar(aux,'0');
					finals=agregar+finals;
				}
				cifrado.append(finals);
			}
			return cifrado;
			//cout<<"mensaje CIFRADOOO:"<<cifrado<<endl;

		}
		string descifrado(string cifrado){
			 N=1003;
			 d=619;//de prueba
			ostringstream Digitos; 
		    Digitos<<N;
		    string N_digitos=Digitos.str();
			
			//declaramos nuestro mensaje cifrado
			int k=0;
			string retornamos;//guardamos el mensaje descifrado
			while(k<cifrado.length()){
				//cout<<"este es j:"<<j<<endl;
				string aux=cifrado.substr(k,N_digitos.length());
				//Convertimos el string en entero
				k=k+N_digitos.length();
				stringstream geek(aux);
		    	int x = 0;
		    	geek >> x;
				int message=Expo_modular(d,x,N);
				//convertimos en string para aumentar 0
				stringstream final;
				final <<message;
				string finals=final.str();
		    	//Aqui agregamos los ceros deacuerdo a las cifras 
				if((N_digitos.length()-1)!=finals.length()){
					int aux=(N_digitos.length()-1)-finals.length();
					string agregar(aux,'0');
					finals=agregar+finals;
				}
				retornamos.append(finals);
			}
			//cout<<"retornamos:"<<retornamos<<endl;
			//cifras del ultimo indice del abecedario
			int last=abc.length()-1;
			ostringstream cadenaSalida; 
		    cadenaSalida<<last;
		    string cifras=cadenaSalida.str();
		    
			string mensaje_descifrado;
			int l=0;
			//encontramos los indices de las letras del mensaje
			while(l<retornamos.length()){
				string aux=retornamos.substr(l,cifras.length());
				l=l+cifras.length();//Convertimos el string en entero
				stringstream geek(aux);
		    	int x = 0;
		    	geek >> x;
				mensaje_descifrado=mensaje_descifrado+abc[x];
			}
			return mensaje_descifrado;		
		}		
	
	
};
int main(){
	
	//int message=549;
	string message="comehere ";
	string abc="abcdefghijklmnopqrstuvwxyz ";
	string cifrar="023403530811005403060545";
	//Emisor
	//RSA a(3,1003);
	//cout<<a. cifrado (message);
	//Receptor
	RSA b(3);
	cout<<b.descifrado (cifrar);
	
	
//CIFRADO	
	//cifras del ultimo indice del abecedario:
	
	

/*	
//DESCIFRADO:
	//int N=1003;
	int d=619;
	//encontrar numero de digitos haciendolo string y numero de digitos es la longitud del string
	ostringstream Digitos; 
    Digitos<<N;
    string N_digitos=Digitos.str();
	
	//declaramos nuestro mensaje cifrado
	int k=0;
	string retornamos;//guardamos el mensaje descifrado
	while(k<cifrado.length()){
		//cout<<"este es j:"<<j<<endl;
		string aux=cifrado.substr(k,N_digitos.length());
		//Convertimos el string en entero
		k=k+N_digitos.length();
		stringstream geek(aux);
    	int x = 0;
    	geek >> x;
		int message=Expo_modular(d,x,N);
		//convertimos en string para aumentar 0
		stringstream final;
		final <<message;
		string finals=final.str();
    	//Aqui agregamos los ceros deacuerdo a las cifras 
		if((N_digitos.length()-1)!=finals.length()){
			int aux=(N_digitos.length()-1)-finals.length();
			string agregar(aux,'0');
			finals=agregar+finals;
		}
		retornamos.append(finals);
	}
	//cout<<"retornamos:"<<retornamos<<endl;
	//cifras del ultimo indice del abecedario
	int last=abc.length()-1;
	ostringstream cadenaSalida; 
    cadenaSalida<<last;
    string cifras=cadenaSalida.str();*/
  /*  
	string mensaje_descifrado;
	int l=0;
	//encontramos los indices de las letras del mensaje
	while(l<retornamos.length()){
		string aux=retornamos.substr(l,cifras.length());
		l=l+cifras.length();//Convertimos el string en entero
		stringstream geek(aux);
    	int x = 0;
    	geek >> x;
		mensaje_descifrado=mensaje_descifrado+abc[x];
	}
	return mensaje_descifrado;
	//cout<<endl<<"a mimiiir:"<<mensaje_descifrado<<endl;
*/
	
	
}
