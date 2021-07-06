#include <iostream>
#include <NTL/ZZ.h>
#include <bits/stdc++.h>
using namespace std;
using namespace NTL;

ZZ MOD(ZZ a,ZZ n){
    ZZ q,r;
  	q =a/n;
  	r=a-(q*n);
	if(r<0){
    	if (q<=0){--q;r=a-(q*n);}
    	if(q>0){++q;r=a-(q*n);}
 	 }

  	return r;
}
ZZ binary_expo_modular(ZZ a, ZZ n, ZZ m){
    ZZ result;
    result = ZZ(1);
    while( n != ZZ(0)) {
        if(MOD(n,ZZ(2))!=0){
            result = MOD(result*a,m);}

        a = MOD(a*a,m);
        n >>= 1;
    }
    return result;
}

ZZ calculateJacobian(ZZ a, ZZ n)
{
	if (a==ZZ(0))
		return ZZ(0);

	ZZ ans = ZZ(1);
	if (a < ZZ(0))
	{
		a = -a;
		if (MOD(n,ZZ(4)) == ZZ(3))
			ans = -ans;
	}

	if (a == ZZ(1))
		return ans;

	while (a!=ZZ(0))
	{
		if (a < ZZ(0))
		{
			a = -a;
			if (MOD(n,ZZ(4)) == ZZ(3))
				ans = -ans;
		}

		while (MOD(a,ZZ(2)) == ZZ(0))
		{
			a = a / ZZ(2);
			if (MOD(n,ZZ(8)) == ZZ(3) || MOD(n,ZZ(8)) == ZZ(5))
				ans = -ans;

		}

		swap(a, n);

		if (MOD(a,ZZ(4)) == ZZ(3) && MOD(n,ZZ(4)) == ZZ(3))
			ans = -ans;
		a = MOD(a,n);

		if (a > n / ZZ(2))
			a = a - n;

	}
	if (n == ZZ(1))
		return ans;

	return ZZ(0);
}

bool solovoyStrassen(ZZ p, int iterations)
{
	if (p < ZZ(2))
		return false;
	if (p != ZZ(2) && MOD(p,ZZ(2)) == ZZ(0))
		return false;

	for (int i = 0; i < iterations; i++)
	{
		int aux = 0;
        conv(aux, p);
		ZZ a = ZZ(rand() % (aux - 1) + 1);
		ZZ jacobian = MOD((p + calculateJacobian(a, p)),p);
		ZZ mod = binary_expo_modular(a, (p - ZZ(1)) / ZZ(2), p);
		if (jacobian ==ZZ(0)|| mod != jacobian)
			return false;
	}
	return true;
}

// Driver Code
int main()
{
	int iterations = 10;
	ZZ num2 = ZZ(13);

	if (solovoyStrassen(num2, iterations))
		cout<<num2<<" is prime "<<endl;
	else
		cout<<num2<<" is composite "<<endl;

	return 0;
}
