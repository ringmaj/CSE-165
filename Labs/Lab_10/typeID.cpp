#include <iostream>
#include "SomeHeader.h"
#include <vector>


using namespace std;


int main(){



vector<A*> myVec;

initVec(myVec);

for(int i = 0; i < myVec.size(); i++)
{
	cout<<typeid(myVec[i]).name()<<endl;
}





}