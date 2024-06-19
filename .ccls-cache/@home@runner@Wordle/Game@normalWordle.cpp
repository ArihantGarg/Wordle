#include<bits/stdc++.h>
using namespace std;

#include "../Headers/gameFunctions.hpp"

vector<string> orderedWords=getOrderedWords();

void makeguess(int guessNumber, string guess){
  cout<<"Guess "<<guessNumber<<": "<<guess<<endl;
}

bool recieveResult(string guess){
  string prompt;
  cin>>prompt;

  if(prompt=="Correct"){
    return 1;
  }
  else if(prompt=="Wrong"){
    return 0;
  }
  else{
    cerr<<"Error"<<endl;
    exit(1);
  }
}

string chooseRandomWord(){
  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

  int randomIndex = rng() % (orderedWords.size());
  return orderedWords[randomIndex];
}

int main()
{
  cout<<"WORDLE BOT HAS STARTED\n";

  string guess="";
  int guessNumber=0;

  do{
    guessNumber++;
    guess=chooseRandomWord();
    makeguess(guessNumber,guess);
  }
  while(!recieveResult(guess));

  cout<<"Number of guesses needed : "<<guessNumber<<endl;
  cout<<"WORDLE BOT IS TERMINATING"<<endl;

  return 0;
}