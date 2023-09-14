#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

multimap<string, string> dictionarySearch;
vector<string> dataVector;
bool checkPartOfSpeech = true;
string *firstWordPos(string, int);
string *breakOnPos(string, int);
string *userInputParam(string);
void addToDictionary(string, string);
void bufferDataVector(string keyWord);
void rDataVector();
void printDVector(string keyWord);
void getPartOfSpeech(string keyWord);
void distinct(string);
void firstParameter(string);
void secondParameter(string);
void secondWordExists(string);
void thirdParameter(string);
void fourthParameter(string);
void helpCommands();

int main()
{
    fstream infile;

    cout << "Please enter the input file name: ";
    while (true)
    {
        string dataFile;
        getline(cin, dataFile);
        infile.open(dataFile);
        if (infile)
        {
            cout << "! Loading data... \n";
            cout << "! Loading Completed... \n" << endl;

            bool partOfSpeechT = true;

            string individualLine;
            string words;
            string def; 
            string *theWord;
            string *wordPOS;
            int countWords = 0;

            while (getline(infile, individualLine))
            {
                stringstream wordsInLine(individualLine);

                for (int i = 0; i < 1; i++)
                {
                    wordsInLine >> words;
                    theWord = firstWordPos(words, words.find("|"));
                }

                while (wordsInLine >> words)
                {
                    if (words == "-=>>")
                    {
                    }
                    else if (words.find("|") < 15)
                    {

                        wordPOS = breakOnPos(words, words.find("|"));

                        def.append(wordPOS[0]);
                        def.append(" ");

                        string tempPOS = wordPOS[1] + " : " + def;

                        addToDictionary(theWord[0], tempPOS);

                        def = " ";
                    }
                    else
                    {
                        def.append(words);
                        def.append(" ");
                    }
                }

                string temp = theWord[1] + " : " + def;
                addToDictionary(theWord[0], temp);
                def = " ";

                countWords++;
            }

            infile.close();
            cout << "! Closing data file... " << dataFile << endl;

            cout << "====== Dictionary 340 C++ =====\n";
            cout << "------ Keywords: " << countWords << endl;
            cout << "------ Definitions: " << dictionarySearch.size() << "\n" <<endl;

            bool q = false;
            int searchCounter = 1;
            string userInput;
            string *arrayForInput;

            while (true)
            {
                cout << "Search [" << searchCounter << "]: ";
                getline(cin, userInput);
                arrayForInput = userInputParam(userInput);
                int counter = dictionarySearch.count(arrayForInput[0]);
                bufferDataVector(arrayForInput[0]);

                if (arrayForInput[0] == "!help")
                {
                    helpCommands();
                }
                else if (arrayForInput[0] == "" || arrayForInput[0] == " ")
                {
                    helpCommands();
                }
                else if ((arrayForInput[0] == "!Q") || (arrayForInput[0] == "!q"))
                {
                    cout << endl;
                    cout << "------Thank You-----\n";
                    exit(0);
                }
                else if (counter < 1)
                {
                    cout << "\t|\n";
                    cout << "\t <NOT FOUND> To be considered for the next release. Thank you." << endl;
                    cout << "\t|\n";
                }
                else
                {

                    cout << "\t|\n";
                    secondWordExists(arrayForInput[1]);
                    fourthParameter(arrayForInput[3]);
                    thirdParameter(arrayForInput[2]);
                    secondParameter(arrayForInput[1]);
                    firstParameter(arrayForInput[0]);
                    cout << "\t|\n";
                }
                searchCounter++;
                checkPartOfSpeech = true; 
                dataVector.clear();

            }
        }
        else
        {
            cout << "Opening data file... " << dataFile << endl;
            cout << "<!>ERROR<!> ===> File could not be opened. \n";
            cout << "<!>ERROR<!> ===> Provided file path: " << dataFile << "\n";
            cout << "<!>Enter the CORRECT data file path: ";
        }
    }
}

string *firstWordPos(string wordInLine, int location)
{

    string *output = new string[2];
    for (int i = 0; i < location; i++)
    {
        output[0] += wordInLine[i];
    }
    for (int i = location + 1; i < wordInLine.length(); i++)
    {
        output[1] += wordInLine[i];
    }
    return output;
}

string *breakOnPos(string wordInLine, int location)
{
    string *output = new string[2];

    for (int i = 0; i < location; i++)
    {
        output[0] += wordInLine[i];
    }
    for (int i = location + 1; i < wordInLine.length(); i++)
    {
        output[1] += wordInLine[i];
    }
    return output;
}

void addToDictionary(string word, string def)
{
    dictionarySearch.insert(pair<string, string>(word, def));
}

string *userInputParam(string takenUserInput)
{
    transform(takenUserInput.begin(), takenUserInput.end(), takenUserInput.begin(), ::tolower);

    string *returnVar = new string[4];
    string words;
    int i = 0;

    stringstream wordsInInput(takenUserInput);

    while (wordsInInput >> words && i < 4)
    {
        returnVar[i] = words;
        i++;
    }
    if (i > 4)
    {
        cout << "\t <!> 5th(+) parameter in the input is ignored.";
        cout << " Only 4 parameters are accepted. <!>\n";
        cout << "\t|\n";
    }
    return returnVar;
}

void bufferDataVector(string keyWord)
{
    for (auto itr = dictionarySearch.begin(); itr != dictionarySearch.end(); itr++)
    {
        if (itr->first == keyWord)
        {
            dataVector.push_back(itr->second);
        }
    }
    sort(dataVector.begin(), dataVector.end());
}

void rDataVector()
{
    vector<string> temp;

    for (auto itr = dataVector.rbegin(); itr != dataVector.rend(); itr++)
    {
        temp.push_back(*itr);
    }
    dataVector.clear();
    dataVector = temp;
    temp.clear();
}

void printDVector(string keyWord)
{
    for (int i = 0; i < dataVector.size(); i++)
    {
        cout << "\t " << keyWord << " " << dataVector.at(i) << endl;
    }
}

void getPartOfSpeech(string keyWord)
{
    vector<string> tempVector;
    string tempTwo, tempThree;

    for (int i = 0; i < dataVector.size(); i++)
    {

        stringstream partOfSpeech(dataVector.at(i));

        while ((partOfSpeech >> tempTwo))
        {
            int imp = tempTwo.find_first_of(" ");

            tempThree = tempTwo.substr(0, imp);

            if (tempThree == keyWord)
            {
                tempVector.push_back(dataVector.at(i));
            }
        }
    }

    dataVector.clear();
    dataVector = tempVector;
    tempVector.clear();
}

void distinct(string keyWord)
{
    vector<string> temp;

    temp.push_back(dataVector.at(0));

    for (int i = 0; i < dataVector.size(); i++)
    {

        if (find(temp.begin(), temp.end(), dataVector.at(i)) != temp.end())
        {
            //idk why but i keep this it breaks 
        }

        else
        {
            temp.push_back(dataVector.at(i));
        }
    }
    dataVector.clear();
    dataVector = temp;
    temp.clear();
}

//Function to get the word definition
void firstParameter(string keyWord)
{

    printDVector(keyWord);
}

void secondParameter(string keyWord)
{
    if (keyWord == "")
    {
        //idk why but i keep this it breaks 
    }
    else if (keyWord == "distinct")
    {
        distinct(keyWord);
    }
    else if (keyWord == "reverse")
    {
        rDataVector();
    }
    else if (checkPartOfSpeech == false)
    {
        cout << "\t <The entered 2nd parameter '" << keyWord << "' is NOT a part of speech.>\n";
        cout << "\t <The entered 2nd parameter '" << keyWord << "' is NOT 'distinct'.>\n";
        cout << "\t <The entered 2nd parameter '" << keyWord << "' is NOT 'reverse'.>\n";
        cout << "\t <The entered 2nd parameter '" << keyWord << "' was disregarded.>\n";
        cout << "\t <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>\n";
        cout << "\t|\n";
    }
    else
    {
        getPartOfSpeech(keyWord);
    }
}

void thirdParameter(string keyWord)
{
    if (keyWord == "")
    {
        //idk why but i keep this it breaks 
    }
    else if (keyWord == "distinct")
    {
        distinct(keyWord);
    }
    else if (keyWord == "reverse")
    {
        rDataVector();
    }
    else
    {
        cout << "\t <The entered 3rd parameter '" << keyWord << "' is NOT 'distinct'.>\n";
        cout << "\t <The entered 3rd parameter '" << keyWord << "' is NOT 'reverse'.>\n";
        cout << "\t <The entered 3rd parameter '" << keyWord << "' was disregarded.>\n";
        cout << "\t <The 3rd parameter should be 'distinct' or 'reverse'.>\n";
        cout << "\t|\n";
    }
}

void fourthParameter(string keyWord)
{
    if (keyWord == "")
    {
        //idk why but i keep this it breaks 
    }
    else if (keyWord == "reverse")
    {
        rDataVector();
    }
    else
    {
        cout << "\t <The entered 4th parameter '" << keyWord << "' is NOT 'reverse'.>\n";
        cout << "\t <The entered 4th parameter '" << keyWord << "' was disregarded.>\n";
        cout << "\t <The 4th parameter should be 'reverse'.>\n";
        cout << "\t|\n";
    }
}

void secondWordExists(string keyWord)
{

    vector<string> tempVector;
    string tempOne, tempThree;

    for (int i = 0; i < dataVector.size(); i++)
    {
        stringstream pos(dataVector.at(i));
        while ((pos >> tempOne))
        {
            int imp = tempOne.find_first_of(" ");

            tempThree = tempOne.substr(0, imp);

            if (tempThree == keyWord)
            {
                tempVector.push_back(dataVector.at(i));
            }
        }
    }

    if (tempVector.size() < 1)
    {
        checkPartOfSpeech = false;
    }
    tempVector.clear();
}

void helpCommands(){
    cout << "\n \t | \n";
    cout << "\t PARAMETER HOW-TO, please enter: \n";
    cout << "\t 1. A search key -then 2. An optional part of speech -then \n";
    cout << "\t 3. An optional 'distinct' -then 4. An optional 'reverse' ";
    cout << "\n \t | \n";

}