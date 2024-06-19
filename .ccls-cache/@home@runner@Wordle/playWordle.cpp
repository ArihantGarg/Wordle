#include<bits/stdc++.h>
using namespace std;

#include "functions.hpp"

vector<string> orderedAnswers=getOrderedAnswers();
vector<string> orderedWords=getOrderedWords();

int main()
{
  for(int i=0;i<10;i++)
    cout<<chooseAnswer(orderedAnswers)<<"\n";
}