#include<bits/stdc++.h>
using namespace std;

vector<string> getOrderedAnswers(){
  ifstream fin( "Files/validAnswers.txt" );
  string curWord;

  vector<string> orderedAnswersVector;

  while(fin>>curWord){
    cout<<curWord<<endl;
    orderedAnswersVector.push_back(curWord);
  }

  return orderedAnswersVector;
}

int main()
{
  auto v=getOrderedAnswers();

  for(auto x:v)
      cout<<x<<endl;
}