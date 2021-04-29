#include <iostream>
#include <string>
using namespace std;
void Cripto(string message){
	// trabajamos con una sola palabra
	string word;
	for(int i=0;i<message.length();i++){
		if(message[i]==' ' ){
			word=message.substr(0,i);
			break;
		}
		if(i== message.length()-1){
			word=message.substr(0,i+1);
			break;
		}
		
	}
	cout<<word;
	
	//Empezamos a encontrar la clave:
	
	string abc="abcdefghijklmnopqrstuvwxyz";
	//cout<<abc.length();	
	for(int j=0;j<abc.length();j++){
		cout<<endl<<endl<<"\t"<<"clave:"<<j<<endl;
		for(int i=0;i<word.length();i++){
			int indice=abc.find(word[i]);
			if(indice-j<0){
				int q=(-(indice-j))/abc.length();
				indice=(indice-j)+(abc.length()*(q+1));
				if(indice>=abc.length()){
					indice=indice-abc.length();
				}
				cout<<abc[indice];
			}
			else{cout<<abc[indice-j];}
			
		}
		
	}
}
int main(){
	string message;
	cout<<"Ingrese el cifrado:";
	getline(cin,message);
	Cripto(message);
	return 0;
}
