#include <iostream>
#include <string>
#include <vector>
using namespace std;
string Ordenar(int fil, string message){//uso esta funcion para los casos donde un espacio equivale a '-' 
		for(int a=0;a<message.length();a++){
			if (message[a]==' '  ){message[a]='-';}
		}
	;
	return message;
}
class Send_message{
	private:
		int filas;
		string message,message_arreglado;
		vector <char> criptado="Hsdo inewgnam ncpyaie ?ro 0edt2  h0yue2o";
	public:
		Send_message(int f,string m){// contructor de la clase
			filas=f;message=m;
			}
		void cifrado(){// ordenamos el mensaje e imprimimos el cifrado del mensaje
			message_arreglado=Ordenar(filas,message);
			int a=(filas*2)-2;//Primera diferencia con la que jugaremos con el valor
			int a_1=a;//Nos ayuda como valor estatico
			for(int b=0;b<filas;b++){
				int i=b;//ayuda a volver el valor de b
				if(b==0 or b==filas-1){
					while (b<message_arreglado.length()){
						criptado.push_back(message_arreglado[b]);
						b=b+a_1;}
				}
				else {
					criptado.push_back(message_arreglado[b]);
					while (b<message_arreglado.length()){
							b=b+a;
							if(b>=message_arreglado.length()){break;}
							criptado.push_back(message_arreglado[b]);
							b=b+(i*2);
							if(b>=message_arreglado.length()){break;}
							criptado.push_back(message_arreglado[b]);
					}
				}
				a=a-2;b=i;
			}
			//Imprimimos el criptado
			cout<<"Cyphertext: ";
			for(int j=0;j<criptado.size();j++){
				//message[j]=cript[j];
				cout<<criptado[j];}
			cout<<endl;
		}	
		void decifrado(){
			int a=(filas*2)-2;//volvemos a iniciar a
			int a_1=a;//Nos ayuda como valor estatico
			char decriptado[criptado.size()];//creamos un array char para acceder a sus
			int pos=0;//para recorrer vector
			int* ptr = & pos;//para que el valor recorra libremente cambiandose valores
			for(int b=0;b<filas;b++){
				int i=b;//pivote de ayuda
				if(b==0 or b==filas-1){
					while (b<criptado.size()){
						decriptado[b]=criptado[*ptr];
						*ptr=*ptr+1;
						b=b+a_1;}
				}
				else {
					decriptado[b]=criptado[*ptr];*ptr=*ptr+1;
					while (b<criptado.size()){
							b=b+a;
							if(b>=criptado.size()){break;}
							decriptado[b]=criptado[*ptr];*ptr=*ptr+1;
							b=b+(i*2);
							if(b>=criptado.size()){break;}
							decriptado[b]=criptado[*ptr];*ptr=*ptr+1;
					}
				}
				a=a-2;b=i;
			}
			//Imprimimos mensaje decifrado
			cout<<"Mensaje: ";
			for(int j=0;j<criptado.size();j++){
				if (decriptado[j]=='-'){decriptado[j]=' ';
				}
				cout<<decriptado[j];}
			cout<<endl;
			}
};

int main() {
	int filas;
	string mensaje;//Aqui hacemos nuestra facilidad para ingresar la clave junto al mensaje
	cout<<"Ingresa key(f):";cin>>filas;
	cout<<endl<<"Ingresa el mensaje que quieres enviar:";
	getline(cin, mensaje);getline(cin, mensaje);
	Send_message Emisor (filas,mensaje);
	Emisor.cifrado();
	Emisor.decifrado();
	return 0;
}
