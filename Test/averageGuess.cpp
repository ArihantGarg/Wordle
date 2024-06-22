#include <bits/stdc++.h>
using namespace std;

int main()
{
  ifstream fin("Files/wordleGuessCount.txt");
  long long guessSum=0;
  long long num=0;

  int curGuessCount=0;
  string curWord="";

  vector<pair<int,string>> v;

  while(fin>>curGuessCount)
  {
    fin>>curWord;
    guessSum+=curGuessCount;
    num++;
    v.push_back(make_pair(curGuessCount,curWord));

    fin>>curWord;
  }

  cout<<guessSum<<" "<<num<<endl;

  double averageGuess = ((double)(guessSum))/num;

  cout<<averageGuess<<endl;

  // sort(v.begin(),v.end(),[](auto a,auto b){
  //   return a.second<b.second;
  // });

  // for(int i=0;i<v.size();i++){
  //   cout<<v[i].first<<" "<<v[i].second<<endl;
  // }

  // for(int i=1;i<v.size();i++){
  //   if(v[i].second==v[i-1].second)
  //     cout<<i<<" , "<<v[i].second<<endl;
  // }
}
