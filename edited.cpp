#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool wordtest(string word);
//Precondition: Entering a string from the words file.
//Postcondition: This fuction will return true if the argument exists.
bool search(string line, string word);
//Precondition: Enter the gotten line from scentences.txt and word you are testing for from words.txt.
//Postcondition: Serches to see if word is in line will return true if word is in line.
char searchtwo (string wordOne, string wordTwo);
//Precondition: Enter the gotten word from match.txt and word you are testing for from words.txt.
//Postcondition: Serches to see if the words match.
//int numberofwords(string wordOne, string wordTwo, string wordThree, string wordFour, string wordfive, string wordSix, string wordSeven, string wordEight);
//Precondition: Enter all words string from words.txt
//Postcondion: Will return an int value equal to the number of words in words.txt.
int matcher (string wordOne);
//Precondition: Use word you wish to find matches for as the argument.
//Postcondition: Will output all sentences from sentences.txt that contain the wordOne argument to match
int findAndReplace (string wordOne, string wordTwo);

int main(){
    string wordOne, wordTwo, wordThree, wordFour, wordFive, wordSix, wordSeven, wordEight; 
    string line;
    int place, x, pos;
    int firstStat;
    ifstream words, sentences, matchin; //defining input streams
    ofstream match, replace, allwords; //defining output streams
    words.open("words.txt");
    if (words.fail()){ //Error checking.
        cerr << "Error opening words.txt" << endl;
        return(1);
    }
    words >> wordOne >> wordTwo >> wordThree >> wordFour >> wordFive >> wordSeven >> wordEight;
    words.close();
    matcher(wordOne);
    findAndReplace(wordOne, wordTwo);
}

int matcher(string wordOne){
    //string wordOne = "apple";
    ifstream sentences; //input stream
    ofstream match; //output stream
    sentences.open("sentences.txt");
    if (sentences.fail()){
        cerr << "Error finding/creating sentances.txt" << endl;
        //return (2);
    }
    match.open("match.txt");
    if (sentences.fail()){ //Error checking.
        cerr << "Error opening sentences.txt" << endl;
        //return(3);
    }
    char letter; //variables
    string line;
    bool sentenceStart = true;
    bool sentenceEnd;
    while (sentences.eof() == false){
        sentences.get(letter);
        while (sentenceEnd == true && letter == ' '){ //this gets rid of spaces after the period.
            sentences.get(letter);
        }
        sentenceEnd = false;        
        if (letter == '\n'){ //this gets rid of newline charecters.
            sentences.get(letter);
        }
        if (sentenceStart == true && letter >= 97 && letter <= 122){
            line = ""; //This empties the string.
            letter = letter - 32;
            line = letter;
            sentenceStart = false;
        }
        else if (sentenceStart == true){
            line = ""; //This empties the string.
            line = letter;
            sentenceStart = false;
        }
        else if (sentenceStart == false){
            line = line + letter;
        }
        if (letter == '.'){
            sentenceStart = true;
            sentenceEnd = true;
        }
        if (sentenceEnd == true){
            bool check = false; //checks if wordOne is in the sentence.
            check = search(line, wordOne);
            if (check == true){
                match << line << endl;
            }
            else if (check == false){
                //do nothing
            }
        }
    }
    sentences.close(); //closing streams
    match.close();
}
                
bool search (string line, string word){
    int x = 0; //x and y count position in string.
    int y = 0;
    for (int i = 0; i < line.length(); i++){ 
        if (word[x] == line[y] || word[x] == line[y] + 32 || word[x] + 32 == line [y]){ //This checks for match case insesitivily. Checks letter by letter.
            x++;
            if (word.length() == x && line[y + 1] == ' ' || line[y + 1] == '.'){ //This checks for match and prevents compund words from returning true such as apple vs apples.
                return true;
            }
        }
        else{
            x = 0; // Resets in the case of a partial match eariler in the sentance. 
        }
        y++;
        if (word.length() == x && y == line.length()){ //This checks for match and prevents compund words from returning true such as apple vs apples, But in the case of the end of the sentance rather then the middle.
            return true;
        }
    }
}
  

bool wordtest(string word){
    if(word[0] != ' '){
        return false;
    }
    else {
        return true;
    }
}

char searchtwo(string wordOne, string word){
    int x = 0;
    for (int i = 0; i < wordOne.length(); i++){
        if (wordOne[i] == word[i] || wordOne[i] == word[i] + 32 || wordOne[i] == word[i] - 32){
            x++;
        }
    }
    if (wordOne.length() == x && word[word.length() - 1] == '.'){
        return ('p'); //this means true with period at the end.
    }
    else if (wordOne.length() == x && wordOne.length() == word.length()){
        return ('t'); //this means true without period.
    }
    else{
        return ('f');
    }
}   

int findAndReplace (string wordOne, string wordTwo){
    ifstream matchin; 
    ofstream replace;
    matchin.open("match.txt");
    if (matchin.fail()){
        cerr << "Error opening match.txt" << endl;
        return (1);
    }
    replace.open("replace.txt");
    if (replace.fail()){
        cerr << "Error creating/editing replace.txt" << endl;
        return (2);
    }
    string word, line;
    char letter;
    bool sentenceStart = true;
    matchin >> noskipws;
    while (matchin.eof() == false){
        matchin >> word;
        replace << word;
        /*
        matchin.get(letter);
        if(letter != ' ' || letter != '\n'){
            word = word + letter;
        }
        else{
            replace << letter;
        }
        if (searchtwo(wordOne, word) == 'f'){
            replace << word;
        }
        else if (searchtwo(wordOne, word) == 't'){
            replace << wordTwo;
        }
        else if (searchtwo(wordOne, word) == 'p'){
            replace << wordTwo << ".";
        }
    }
    */}
}
    
