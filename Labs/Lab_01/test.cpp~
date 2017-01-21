#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>



using namespace std;

int check;
bool checkUpper(string str)
{

int size = str.size();
for (int i = 0; i < size ; i++)
{

 string s = str.substr(i, i+1);

const char *c = s.c_str();
 //char c = char(str.substr(i, i+1);
 if (*c  < 91 && *c > 64 )
{

 check++;

}
else
{
check =0;
}
 
}


if (check == size)
{
return true;
}
else
{
return false;
}



}






int main()
{


//bool upperC = false;

string sample;
string upper;
string lower;
string allCaps;




string noFirst;
int num = 0;


cin >> sample;
ifstream in("words.txt");
string word;


int size = sample.size();

noFirst = sample.substr(1, size-1);
string a = sample.substr(0,1);
a += 32;

const char * c = a.c_str() ;
char firstUpper = *c -32;
char firstLower = *c +32;

lower = firstLower+ noFirst;
upper = firstUpper + noFirst;







//cout << " WORD: "<< upper << endl;;

//cout <<"CAPITALIZED: "<< c << m<<endl;






while (in >> word) 
{



//cout << word << endl;
if( word == sample || word == upper || word == lower || word == allCaps)
{
cout << word<<endl;
num++;

}

if(word.substr(0, size-1) == upper.substr(0,size-1) || word.substr(0, size-1) == lower.substr(0,size-1) || word.substr(0, size-1) == allCaps.substr(0,size-1) || word.substr(0, size-1) == sample.substr(0,size-1))
{

string lastLetter = word.substr(size-1, size);
cout << "LAST LETTER: "<<lastLetter << endl;

const char * c = lastLetter.c_str() ;
if(*c <65 || *c > 122)
{


num++;



}

}
}
cout <<""<<endl;



cout <<"sample: "<<sample<<endl;
cout << "upper: "<<upper<<endl;
cout << "lower: "<<lower<<endl;
cout << "All Caps: "<<allCaps<<endl;
cout << "FOUND: "<< num << endl;
return 0;
}

