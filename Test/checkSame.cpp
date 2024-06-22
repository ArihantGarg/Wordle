#include <bits/stdc++.h>
using namespace std;

int main()
{
  ifstream fin1("Files/wordleGuessCount.txt");
  ifstream fin2("Files/webGuessCount.txt");

  ofstream fout("Files/Logs.txt");

  int n1,n2,spare;
  string s1,s2;

  int i=0;

  while(fin1>>n1)
  {
    fin2>>n2;
    fin1>>s1;
    fin2>>s2;
    fin1>>spare;

    if(s1!=s2)
        fout<<"Error in word "<<s2<<endl;
    else if(n1!=n2)
        fout<<"Error in count "<<s1<<": "<<n1<<" , "<<s2<<": "<<n2<<endl;

    i++;
    cout<<i<<endl;
  }

  return 0;
}
