vector<string> getOrderedAnswers(){
  ifstream fin( "validAnswers.txt" );
  string curWord;

  vector<string> orderedAnswers;

  while(fin>>curWord){
    orderedAnswers.push_back(curWord);
  }

  return orderedAnswers;
}

vector<string> getOrderedWords(){
  ifstream fin( "allWords.txt" );
  string curWord;

  vector<string> orderedAnswers;

  while(fin>>curWord){
    orderedAnswers.push_back(curWord);
  }

  return orderedAnswers;
}

bool checkValidWord(string word,vector<string> &orderedWords){
  int l=0;
  int r=orderedWords.size()-1;

  while(l<=r){
    int mid=(l+r)/2;

    if(word<=orderedWords[mid])
      r=mid;
    else
      l=mid+1;
  }

  return (word==orderedWords[l]);
}

string chooseAnswer(vector<string> &orderedAnswers){
  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

  int answerIndex = rng() % (orderedAnswers.size());

  return orderedAnswers[answerIndex];
}