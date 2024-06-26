#include "simpleai.h"

int readMaxGuess()
{
    int maxGuess;
    cout << endl << "Enter the number of incorrect guesses: ";
    cin >> maxGuess;
    return maxGuess;
}

int readWordLen()
{
    int wordLen;
    cout << endl << "Enter the number characters of your secret word: ";
    cin >> wordLen;
    return wordLen;
    
}

/***
    Args:
        wordLen (int): The desired length of input word
        vocabulary (vector<string>): The vocabulary
    Returns:
        answer (vector<string>) : A set or word from the vocabulary where the number of character is equal to wordLen
***/
//timf từ độ dài wordlen
vector<string> filterWordsByLen(int wordLen, const vector<string>& vocabulary)
{
    vector<string> answer;
    for(const string& x : vocabulary){
        if(x.length()==wordLen){
            answer.push_back(x);
        }
    }
    return answer;
}

/***
    Args:
        selectedChars (set<char>): The predicted characters
    Returns:
        answer (char) : The next character given the provided word is not in the vocabulary
***/
// tả ra kí tự tiếp theo
char nextCharWhenWordIsNotInDictionary(const set<char>& selectedChars)
{
    char answer;
    for(char x='a'; x<='z'; x++)
    {
        auto c=selectedChars.find(x);
        if(c == selectedChars.end())   {return x;}
    }
    return answer;
}

/***
    Args:
        candidateWords (vector<string>): The candidate words for the current given string 
    Returns:
        answer (map) : The map which count the occurences of character in the set of candidate words
***/
//dem so tu xuat hien ki tu
map<char, int> countOccurrences(const vector<string>& candidateWords)
{
    map<char, int> answer;
    for(int i=0; i<candidateWords.size(); i++){
          for(int j=0; j< candidateWords[i].size(); j++){
                answer[candidateWords[i][j]]++;
          }
    }
    return answer;
}

/***
    Args:
        occurrences (map<char, int>): The map which count the occurences of character in the set of candidate words
        selectedChars (set<char>): The predicted characters
    Returns:
        answer (char) : The most frequent character
***/
//tim ki tu được xuất hiện nhiều nhất mà không nằm trong từ dự đoán
char findMostFrequentChar(const map<char, int>& occurrences, const set<char>& selectedChars)
{
    char answer;
    int maxx1=0;
    for (auto x: occurrences )
    {
       if(selectedChars.find(x.first) == selectedChars.end() && x.second>maxx1 )
       {
            answer=x.first;
            maxx1=x.second;
       }
    }
    return answer;
}

/***
    Args:
        candidateWords (vector<string>): The candidate words for the current given string 
        selectedChars (set<char>): The predicted characters
    Returns:
        answer (char) : The most suitable character for prediction
***/
//tìm kí tự dụ doán tốt nhất dựa trên số làn xuất hiện kí tự 
char findBestChar(const vector<string>& candidateWords, const set<char>& selectedChars)
{
    char answer;
    map<char, int> a = countOccurrences(candidateWords);
    return findMostFrequentChar(a, selectedChars);
}

string getWordMask(char nextChar)
{
    string mask;
    cout << "The next char is: " << nextChar << endl;
    cout << "Please give me your answer: ";
    cin >> mask;
    return mask;
}

/***
    Args:
        ch (char): The predicted character by the AI
        mask (string): The response mask by the player
    Returns:
        answer (bool) : return False if the predicted character is the wrong one, True otherwise
***/
// ktra từ trong mask
bool isCorrectChar(char ch, const string& mask)
{
    for (int i=0; i< mask.size(); i++){
         if (mask[i]==ch){
              return true;
         }
    }
    return false;
}

/***
    Args:
        mask (string): The response mask by the player
    Returns:
        answer (bool) : return False if the provided mask is not a whole word, True otherwise
        (Example: -False: g__d
                  -True:  good)
***/
//  ktra xem từ đã hoàn h=chỉnh chưa
bool isWholeWord(const string& mask)
{
    for (int i=0; i<mask.size(); i++){
        if(mask[i]=='-'){
            return false;
        }
    }
    return true;
}

/***
    This function should be used to support the filterWordsByMask function below
    Args:
        mask (string): The response mask by the player
        word (string): input word
        ch (char): The predicted character by the AI
    Returns:
        answer (bool) : return False if the provided mask and the given word is not in the same form.
        Example: - False: mask(-ood), char 'd' vs word(boot)
                 - True: mask(-ood), char 'd'  vs word(good)
***/
//ktra từ có đã là một từ hoàn chỉnh chưa
bool wordConformToMask(const string& word, const string& mask, char ch) 
{
    if (word.length() != mask.length()) {
        return false;
    }
    for (int i = 0; i < word.length(); ++i) {
        if (word[i] != mask[i] && mask[i] != '-' ) {
            return false;
        }
        else if( mask[i] != '-' and word[i]==ch){
            return false;
        }
    }
    return true;
}

/***
    Args:
        mask (string): The response mask by the player
        words (vector<string>): The candidate words
        ch (char): The predicted character by the AI
    Returns:
        answer (bool) : a list of word which satisfiy the mask and the predicted character
        Examples: input words: (good,boot,hood,...)
                  input mask: -ood
                  predicted char: d
                  Return: good,hood
***/
// lập danh sách dựa trên các từ và ký tự
vector<string> filterWordsByMask(const vector<string>& words, const string& mask, char ch)
{
    vector<string> answer;
    
     for (string x:words)
    {
        if(wordConformToMask(x,mask,ch)) answer.push_back(x); 
    }
    return answer;
}