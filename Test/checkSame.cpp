#include <bits/stdc++.h>
using namespace std;

int main()
{
  ifstream fin1("Files/wordleGuessCount.txt");
  ifstream fin2("Files/temp.txt");

  string s1,s2;

  int i=0;

  while(fin1>>s1)
  {
    fin2>>s2;

    if(s1!=s2)
        cout<<"Error"<<endl;
    else
        i++;
  }

  cout<<"End "<<i;

  return 0;
}
