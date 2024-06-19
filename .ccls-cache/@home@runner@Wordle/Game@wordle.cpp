#include<bits/stdc++.h>
using namespace std;

#include "../Headers/gameFunctions.hpp"

vector<string> orderedWords=getOrderedWords();
vector<string> orderedAnswers=getOrderedAnswers();

string generatedAnswer=chooseAnswer(orderedAnswers);

set<string> setWords(orderedWords.begin(),orderedWords.end());

void makeguess(int guessNumber, string guess){
  // cout<<"Guess "<<guessNumber<<": "<<guess<<endl;
}

string getResultPrompt(string guess){
  if(guess==generatedAnswer){
    return "Correct";
  }
  else{
    return "Wrong";
  }
}

bool recieveResult(string guess){
  string prompt=getResultPrompt(guess);

  if(prompt=="Correct"){
    return 1;
  }
  else if(prompt=="Wrong"){
    setWords.erase(guess);
    return 0;
  }
  else{
    cerr<<"Error"<<endl;
    exit(1);
  }
}

int main()
{
  // cout<<"WORDLE BOT HAS STARTED\n";
  // cout<<"Word to be guessed by program : "<<generatedAnswer<<"\n";

  string guess="";
  int guessNumber=0;

  

  do{
    guessNumber++;
    guess=chooseAnswer(setWords);
    makeguess(guessNumber,guess);
  }
  while(!recieveResult(guess));

  // cout<<"Number of guesses needed : "<<guessNumber<<endl;
  // cout<<"WORDLE BOT IS TERMINATING"<<endl;

  ofstream fout("Files/wordleGuessCount.txt",ios::app);

  fout<<guessNumber<<" "<<generatedAnswer<<endl;

  return 0;
}