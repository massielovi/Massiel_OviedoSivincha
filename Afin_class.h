
#include <string>
using namespace std;


class Afin{
	private:
		string abc="abcdefghijklmnopqrstuvwxyz";//tama�o 26
		int pass_a,pass_b;
	public:
		Afin();
		Afin (int a, int b);
		void cifrado(string message);
		void descifrado(string message)	;	
};
