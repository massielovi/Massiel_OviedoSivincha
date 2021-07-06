#include <bits/stdc++.h>
#include <windows.h>
#include <chrono>
#include <psapi.h>
#include <bitset>
#include <NTL/ZZ.h>
#include <iostream>

using namespace std;
using namespace NTL;

ZZ mod(ZZ a,ZZ b){
    ZZ r=a-(b*(a/b));
    if(r<0)r=b-r;
    return r;
}
bool even(ZZ a){
    ZZ r=(a>>1)<<1;
    if(r<0) r=ZZ(2)+r;
    return r==a;
}
ZZ ValAbs(ZZ a){
    if (a<0) return (a*-1);
    return a;
}
ZZ mod_power(ZZ a, ZZ n, ZZ m){
    ZZ result;
    result = ZZ(1);
    while( n != ZZ(0)) {
        if(!even(n))
            result = mod(result*a,m);
        a = mod(a*a,m);
        n >>= 1;
    }
    return result;
}
int ModInteger(int a, int b){
    int r=a-(b*(a/b));
    if(r<0)
        r=b+r;
    return r;
    }
ZZ power(ZZ a, ZZ n){
    ZZ result;
    result = ZZ(1);
    while( n != ZZ(0)) {
        if(mod(n, ZZ(2)) != 0)
            result = result*a;
        a = a*a;
        n >>= 1;
    }
    return result;
}

int contador=0;
string processInfo;

void fillWithMemoryInfo() {
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    if (EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {//obtiene los procesos en aProcesses
        cProcesses = cbNeeded / sizeof(DWORD);// Calcula cuantos procesos fueron retornados
        for (int i = 100; i < cProcesses; i++){
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
            if (NULL != hProcess){
                PROCESS_MEMORY_COUNTERS pmc;
                if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                    processInfo+=(to_string(pmc.PageFaultCount)+to_string(pmc.WorkingSetSize)+
                    to_string(pmc.QuotaPagedPoolUsage)+to_string(pmc.QuotaNonPagedPoolUsage)+to_string(pmc.PeakPagefileUsage));
                }
            }
            CloseHandle(hProcess);
        }
    }
}
vector<int> generateSeed(){
    if((processInfo.size()<contador+15)||processInfo.empty()){
        processInfo.clear();
        fillWithMemoryInfo();
        contador=0;
    }
    vector<int> k;
    for(int i=0, j=contador;i<5;i++,j+=3){
        int n=stoi(processInfo.substr(j,3));
        while(n>255) n>>=1;
        while(n<128) n<<=1;
        k.push_back(n);
    }
    contador+=15;
    return k;
}
vector<bool> RC4(vector<int> semilla){
    vector<int> Or;
    {//permite que S solo pertenezca a este scope
    vector<int> S;
    for(int i=0;i<256;i++) S.push_back(i);
    {//permite que k solo exista en este scope, optimiza memoria
        vector<int> K;
        for(int i=0,k=0;i<=51;i++)
            for(int j=0;j<5;j++,k++)
                K.push_back(semilla[j]);
        for(int i=0,f=0;i<256;i++){
            f= ModInteger(f + S[i] + K[i], 256);
            swap(S[i],S[f]);
        }
    }
    for(int i=0,f=0,k=0;k<8;k++){
        i= ModInteger(i + 1, 256);
        f= ModInteger(f + S.at(i), 256);
        swap(S.at(i),S.at(f));
        Or.push_back(S.at(ModInteger(S.at(i) + S.at(f), 256)));//t
    }
    }
    vector<bool> out;
    for(int i=0;i<8;i++){
        bitset<8> aux(Or[i]);
        for(int j=0;j<8;j++)
            out.push_back(aux[j]);
    }
    return out;
}
void izqRotate(vector<bool> &vec, int times){
    //Rota times veces el vector llevando el primero al ultimo y borrando los primeros
    vec.insert(vec.end(),vec.begin(),vec.begin()+times);//Agrega al final del vector times elementos del inicio del vector
    vec.erase(vec.begin(),vec.begin()+times);//borra los primeros times valores.
}
//Arrays que tienen maximo como numero maximo 64 y son al azar
//PC_1 tiene 56 numeros y PC_2 tiene 48
int PC_1[]={56,48,40,32,24,16,8,0,57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,60,52,44,36,28,20,12,4,27,19,11,3};
int PC_2[]={13,16,10,23,0,4,2,27,14,5,20,9,22,18,11,3,25,7,15,6,26,19,12,1,40,51,30,36,46,54,29,39,50,44,32,47,43,48,38,55,33,52,45,41,49,35,28,31};
int rotaciones[]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1,1,1,2,2,2,2};//propia del DES
//PC eleccion permutada
//Hacemos uso de la generacion de claves de DES
//Donde teoricamente se usan 56 bits de la clave
//Teoricamente son 64 bits del PC_1 pero por paridad que no la necesitaos usamos solo 56 bits
//Teoricamente se usan 48 bist de la subclave para PC_2

vector<bool> DES(int bits=1024){
    vector<bool> K;//para guardar todas las k
    {
    vector<bool>k=RC4(generateSeed());//64 bools o bits
    int nBits=bits/48+1;
    vector<bool> c; vector<bool> d;
    for(int i=0;i<28;i++) c.push_back(k.at(PC_1[i]));//Añade cierta posicion de k en c entre las posiciones adquiridas esta los primeros 28 numeros de PC_1
    for(int i=28;i<56;i++) d.push_back(k.at(PC_1[i]));//Añade cierta posicion de k en d entre las posiciones adquiridas esta de 28 a 56 numeros de PC_1
    for(int i=0;i<nBits;i++){
        izqRotate(c,rotaciones[i]);
        izqRotate(d,rotaciones[i]);//Rotara los vectores rotaciones[i] veces
        vector<bool> both(c.begin(),c.end());//Vector duplicamos con los valores de c
        both.insert(both.end(),d.begin(),d.end());//Agregamos todo el vector de d
        for(int i=0;i<48;i++) K.push_back(both.at(PC_2[i]));//Agregamos a k cierta posicion de both entre las posiciones 0-48 de Pc_2
    }
    }
    K.resize(bits);//Modifica el k para quedar con cierto numero de bits
    K[0]=1; K[bits-1]=1;//Primer y ultimo valor de k sera 1
    return K;
}
ZZ Random_Number(vector<bool> vec){
    //Recibe el return de DES un numero random con k BITS pedidos
    //Retorna el DES en numeros y no en bits
    ZZ salida(0);
    ZZ i(1);
    for(vector<bool>::reverse_iterator it=vec.rbegin();it!=vec.rend();++it){
        if(*it) salida+=i;
        i<<=1;
    }
    return salida;
}

bool Miller_Rabin(ZZ d, ZZ n){
    ZZ a; a=2;
    ZZ x = mod_power(a, d, n);
    if (x == 1  || x == n-1)return true;
    while (d != n-1){

        x = mod((x * x), n);
        d *= 2;
        if (x == 1)return false;
        if (x == n-1)return true;
    }
    return false;
}
bool isPrime(ZZ n){
    ZZ k; k=0;
    if (n <= 1 or n == 4)return false;
    if (n <= 3)return true;

    ZZ d = n - 1;
    while (even(d)){
        //d /= 2;
        d >>= 1;
        k++;

    }

    for (int i = 0; i < k+1; i++)
         if (!Miller_Rabin(d, n))
              return false;

    return true;
}

bool Lucas_Lehmer(ZZ p) {

  ZZ num = power(ZZ(2), p) - 1;

  ZZ nextval = mod(ZZ(4), num);

  for (ZZ i = ZZ(1); i < p - 1; i++)
    nextval = mod((nextval * nextval - 2), num);

  return (nextval == ZZ(0));
}
ZZ calculateJacobian(ZZ a, ZZ n){
	if (a==ZZ(0))
		return ZZ(0);

	ZZ ans = ZZ(1);
	if (a < ZZ(0))
	{
		a = -a;
		if (mod(n, ZZ(4)) == ZZ(3))
			ans = -ans;
	}

	if (a == ZZ(1))
		return ans;

	while (a!=ZZ(0))
	{
		if (a < ZZ(0))
		{
			a = -a;
			if (mod(n, ZZ(4)) == ZZ(3))
				ans = -ans;
		}

		while (mod(a, ZZ(2)) == ZZ(0))
		{
			a = a / ZZ(2);
			if (mod(n, ZZ(8)) == ZZ(3) || mod(n, ZZ(8)) == ZZ(5))
				ans = -ans;

		}

		swap(a, n);

		if (mod(a, ZZ(4)) == ZZ(3) && mod(n, ZZ(4)) == ZZ(3))
			ans = -ans;
		a = mod(a, n);

		if (a > n / ZZ(2))
			a = a - n;

	}
	if (n == ZZ(1))
		return ans;

	return ZZ(0);
}
bool SolovoyStrassen(ZZ p, int iterations){
	if (p < ZZ(2))
		return false;
	if (p != ZZ(2) && mod(p, ZZ(2)) == ZZ(0))
		return false;

	for (int i = 0; i < iterations; i++)
	{
		int aux = 0;
        conv(aux, p);
		ZZ a = ZZ(rand() % (aux - 1) + 1);
		ZZ jacobian = mod((p + calculateJacobian(a, p)), p);
		ZZ mod = mod_power(a, (p - ZZ(1)) / ZZ(2), p);
		if (jacobian ==ZZ(0)|| mod != jacobian)
			return false;
	}
	return true;
}

int main(){
    ////// Miller
    //ZZ num;
    //cout<<"sidovnsdjvn"<<endl;
    cout<<Random_Number(DES(32));
    //vector<bool>k=;
    //cout<<RC4(generateSeed());
    //num = conv<ZZ>("55079");
    //num = conv<ZZ>("2405004167");
    //num = conv<ZZ>("13899400287462393527");
    //num = conv<ZZ>("265733069836953021104589357293605940039");
    //num = conv<ZZ>("105418067230565229302401311614871856367337516926256261485610678970677326732123");
    //num = conv<ZZ>("11067322688211763879127710781245770200266306579753149074670002771714059738841730056577765602839652195914873916936503030794140872851579504321364488742771259");
    //num = conv<ZZ>("176656997303223902095560256491598180971380732993768921435351520271158961476748001277698565063028402764520109441247809203999420881922890353371040260979842426191177375275250990256146658405602103682083965762652790303682088948560995391904786385195323037525430801172918718937212475657313929650740839978361468109599");
    //num = conv<ZZ>("176656997303223902095560256491598180971380732993768921435351520271158961476748001277698565063028402764520109441247809203999420881922890353371040260979842426191177375275250990256146658405602103682083911507094056460942324895003030838848437920445828939149753194797933424971295561580693952160572169974924758566779891767759568217500311694093771493781455874622444242562578701082351821304930719483209293008469245826413837567768393873673624867353355756939051761882984937863386361165973965470732189084373611074509055365762652790303682088948560995391904786385195323037525430801172918718937212475657313929650740839978361468109599");

/*
    if(isPrime(num))
        cout << num << " es primo" << endl;
    else
        cout << num << " no es primo" << endl;*/

    ////// Lucas-Lehmer
    /*ZZ p = Random_Number(8);
    ZZ num = power(ZZ(2), p) - 1;

    if (Lucas_Lehmer(p))
    cout << num << " es primo.";
    else
    cout << num << " no es primo.";*/

    //SolovoyStrassen
    /*int iterations = 10;
	//ZZ num = Random_Number(16);

	if (SolovoyStrassen(num, iterations))
		cout<<num<<" is prime "<<endl;
	else
		cout<<num<<" no es primo"<<endl;

    return 0;
    //ZZ p = ZZ(13);
    //ZZ p = ZZ(31);
    ZZ p = ZZ(50);
    //ZZ p = ZZ(61);
    ZZ num = power(ZZ(2), p) - ZZ(1);

    if(Lucas_Lehmer(p))
        cout << num << " es primo" << endl;
    else
        cout << num << " no es primo" << endl;*/
}
