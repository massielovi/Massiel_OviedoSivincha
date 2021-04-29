#include <iostream>
#include <string>
#include <string.h>
using namespace std;
//cesar
void cifrado(string message, int clave){
	string abc="abcdefghijklmnopqrstuvwxyz";
	cout<<"Se esta cifrando este mensaje con cesar... ";
	for (int i=0;i<message.length();i++){
		int indice=abc.find(message[i]);
		if(indice==string::npos){
			message[i]=' ';
		}
		else{
			if(indice+clave>abc.length()-1){
				int q=(indice+clave)/abc.length();
				//indice=(indice+clave)-abc.length();
				indice=(indice+clave)-(abc.length()*q);//uso del modulo
				message[i]=abc[indice];
			}
			else{message[i]=abc[indice+clave];
		}}
	}
	cout<<endl <<"Mensaje cifrado :/"<<message<<"/";
}
void descifrado(string message,int clave){
	string abc="abcdefghijklmnopqrstuvwxyz";
	
	for (int i=0;i<message.length();i++){
		int indice=abc.find(message[i]);
		if(indice==string::npos){
			message[i]=' ';
		}
		else{
			if(indice-clave<0){
				int q=(-(indice-clave))/abc.length();
				indice=(indice-clave)+(abc.length()*(q+1));//uso del modulo
				if(indice>=abc.length()){
					indice=indice-abc.length();
				}
				message[i]=abc[indice];
			}
			else{message[i]=abc[indice-clave];}
		}
	}
	cout<<endl<<"Mensaje decifrado:"<<message;
	
}
int main(){
	string message;
	int clave;
	cout<<"Ingrese el mensaje:";
	getline(cin,message);
	cout<<"Ingrese la clave:";
	cin>>clave;
	cifrado(message,clave);
	
	}
