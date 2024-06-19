vector<string> getOrderedAnswers(){
  ifstream fin( "Files/validAnswers.txt" );
  string curWord;

  vector<string> orderedAnswersVector;

  while(fin>>curWord){
    orderedAnswersVector.push_back(curWord);
  }

  return orderedAnswersVector;
}

vector<string> getOrderedWords(){
  ifstream fin( "Files/allWords.txt" );
  string curWord;

  vector<string> orderedAnswersVector;

  while(fin>>curWord){
    orderedAnswersVector.push_back(curWord);
  }

  return orderedAnswersVector;
}

bool checkValidWord(string word,vector<string> &orderedWordsVector){
  int l=0;
  int r=orderedWordsVector.size()-1;

  while(l<r){
    int mid=(l+r)/2;

    if(word<=orderedWordsVector[mid])
      r=mid;
    else
      l=mid+1;
  }

  return (word==orderedWordsVector[l]);
}

string chooseAnswer(vector<string> &orderedAnswersVector){
  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

  int answerIndex = rng() % (orderedAnswersVector.size());

  return orderedAnswersVector[answerIndex];
}

string chooseAnswer(set<string> &orderedAnswersSet){
  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

  // Calculate a random index
  int answerIndex = rng() % orderedAnswersSet.size();

  // Use an iterator to find the element at the random index
  auto it = orderedAnswersSet.begin();
  advance(it, answerIndex);

  // Return the element pointed to by the iterator
  return *it;
}

bool checkCorrectGuess(string guess,string answer){
  return (guess==answer);
}

string computeGuess(string guess,string answer,vector<string> &orderedWordsVector,vector<string> &orderedAnswersVector){
  if(!checkValidWord(guess,orderedWordsVector))
    return "Invalid Guess";
  if(!checkCorrectGuess(guess,answer))
    return "Incorrect Guess";
  return "Correct Guess";
}