#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>  

using namespace std;


int decimal(char s[])
{

	int maxPow = strlen(s)-1;
	int sum = 0;
	int j = 0;



	cout <<"LENGTH: "<<maxPow<<endl;


for(int j = 0; j <= maxPow; j++)
{



	if( s[j]  == '1')
	{

       sum += pow(2, maxPow);

       maxPow--;

	   
	}
	else
	{
		maxPow--;

	}
	

	//cout<<"HIGHEST POWER: "<<power<<endl;




}






cout<<"SUM IS: "<<sum<<endl;

return sum;
}











void binary(int n)
{

int power = 0;
int sum = 0;
int add = 1;
string reversed;



for(int i = 1; i < 100; i++)
{

	if(pow (2, i) <= n)
	 power++;

	//cout<<"HIGHEST POWER: "<<power<<endl;



}



for(int i = power; i >=0 ; i--)
{

	if((pow (2, i) + sum) <= n)
	{
      sum = pow (2, i) + sum;
	 cout << 1;
	 reversed += "0";
	}
	else
	{
	 cout<<0;
	 	 reversed += "1";
	}

	//cout<<"HIGHEST POWER: "<<power<<endl;




}

cout<<" "<<reversed;

}

int main()
{


int n=0;
char s[5];
cin >> s;


while(n != -1)
{

  decimal(s);

	cout << n<<" ";
	binary(n);

	cin >> n;


}

return 0;





}