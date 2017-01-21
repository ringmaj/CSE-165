#include <stdio.h>
#include <stdlib.h>
#include <math.h>  

void binary(int n)
{

int power = 0;
int sum = 0;
int add = 1;



int i;
for( i = 1; i < 100; i++)
{

	if(pow(2, i) <= n)
	 power++;

	//cout<<"HIGHEST POWER: "<<power<<endl;



}



for(i = power; i >=0 ; i--)
{

	if((pow(2, i) + sum) <= n)
	{
      sum = pow(2, i) + sum;
	 printf("1");
	}
	else
	{
	 printf("0");
	}

	//cout<<"HIGHEST POWER: "<<power<<endl;



}



}



int main()
{

int n=0;
 scanf("%d",&n);


while(n != -1)
{
	 printf("%x ",n);
	binary(n);

 scanf("%d",&n);



}

return 0;









return 0;





}