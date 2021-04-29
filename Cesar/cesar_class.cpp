#include <iostream>
#include <string>
#include <string.h>
using namespace std;
//cesar

class Cesar {
	private:
		string abc="abcdefghijklmnopqrstuvwxyz";
		string message;
		int clave;
	public:
	Cesar(string mensaje, int password){
		message=mensaje;clave=password;
		}
	void cifrado(){
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
	void decifrado(){
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
	};


int main(){
	string message;
	int clave;
	cout<<"Ingrese el mensaje:";
	getline(cin,message);
	cout<<"Ingrese la clave:";
	cin>>clave;
	
	Cesar Emisor(message,clave);
	Emisor.cifrado();
	//Emisor.decifrado();
	/*Cesar Receptor(message,clave);
	Receptor.cifrado();
	Receptor.decifrado();*/
	
	
	return 0;
}
	
	
