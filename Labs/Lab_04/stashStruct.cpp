#include "Stash.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{


int num;

cin >> num;

int size = num;

Stash st; 
st.initialize(sizeof(double));



while(num != 0)
{


double n;
cin >> n;

void *ptr = &n;
st.add(ptr);

//void *voidPtr = st.fetch(begin);




//double a = *((double*)voidPtr);

//cout<<a<<endl;

num--;

}


for(int i = 0; i < size; i++)
{

//cout<< "test "<<i<<endl;
void *voidPtr = st.fetch(i);


double a = *((double*)voidPtr);

cout<<a<<endl;

}


st.cleanup();


return 0;


}
