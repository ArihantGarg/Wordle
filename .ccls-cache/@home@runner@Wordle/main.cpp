#include <bits/stdc++.h>
using namespace std;

ifstream fin1("validAnswers.txt");
ifstream fin2("validWords.txt");
ofstream fout("words.txt");

int main() {
  int cnt=0;
  int rpt=0;
  string s;

  vector<string> v;
  set<string> s1;

  while(fin1>>s){
    cnt++;
    s=s.substr(0,5);
    v.push_back(s);

    if(s1.find(s)!=s1.end()){
      rpt++;
    }
    s1.insert(s);
  }

  while(fin2>>s){
    cnt++;
    s=s.substr(0,5);
    v.push_back(s);

    if(s1.find(s)!=s1.end()){
      rpt++;
    }
    s1.insert(s);
  }

  sort(v.begin(),v.end());

  for(auto x:v)
    fout<<x<<"\n";

  cout<<cnt<<" "<<rpt<<"\n";
}