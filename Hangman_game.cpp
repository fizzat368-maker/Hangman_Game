#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

void Color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}

void printBorder()
{
    Color(14);
    cout << endl ;
    for (int i = 0; i < 59; i++)
    {
        cout << "-";
    }
    cout << endl;
}

void printTitle()
{
    printBorder();
    printBorder();
    Color(6);
    cout << endl << setw(50)<<"W E L C O M E   T O   W O R D N O O S E " << endl;
    printBorder();
    printBorder();
    Color(6);
    cout << endl << setw(50) << "P R O J E C T  B Y  F I Z Z A  T A H I R" << endl;
    printBorder();
    cout << endl;
}
// Function to print a message centered
void printMessage(string message)
{
    Color(5);
    int totalWidth = 70;
    int padding = (totalWidth - message.length()) / 2;
    cout << string(padding, ' ') << message << endl;
}
// Function to determine if a position should be a hint
bool isHintPosition(int pos, int length)
{
    if (length <= 2)
        return false;              
    else if (length == 3)
        return pos == 2;         
    else
        return pos == 0 || pos == length - 1; 
}

void printHangMan(int wrongGuess)
{
    Color(13);
    cout << endl << " Hangman : " << endl;
    cout << "  +===+" << endl;
    cout << "  |   |" << endl;


    if (wrongGuess >= 1)
        cout << "  |   O" << endl;
    else
        cout << "  |    " << endl;

    if (wrongGuess == 2)
        cout << "  |   |" << endl;
    else if (wrongGuess == 3)
        cout << "  |  /|" << endl;
    else if (wrongGuess >= 4)
        cout << "  |  /|\\" << endl;
    else
        cout << "  |    " << endl;


    if (wrongGuess >= 5)
        cout << "  |   |" << endl;
    else
        cout << "  |    " << endl;


    if (wrongGuess == 6)
        cout << "  |  / \\" << endl;
    else if (wrongGuess == 5)
        cout << "  |  /" << endl;
    else
        cout << "  |    " << endl;

    cout << "  |" << endl;
    cout << "-----" << endl << endl;
}

// Function to display the word with guessed letters and hints
void printWord(string word, string guessed)
{
    Color(11);
    cout << "Word : ";

    for (int i = 0; i < word.length(); i++)
    {
        bool found = false;
        for (int j = 0; j < guessed.length(); j++)
        {
            if (word[i] == guessed[j])
            {
                found = true;
                break;
            }
        }

        bool isHintPresent = isHintPosition(i, word.length());

        if (found || isHintPresent)
        {
            if (isHintPresent && !found)
            {
                Color(14);
                cout << word[i] << " ";
                Color(11);
            }
            else
            {
                cout << word[i] << " ";
            }
        }
        else
        {
            cout << "_ ";
        }
    }
    cout << endl << endl;
}

// Function to display available letters (hide guessed letters)
void printAvailableLetters(string guessedLetters)
{
    Color(10);
    printBorder();
    cout << "A V A I L A B L E  L E T T E R S" << endl;

    cout << " ";
    for (char ch = 'A'; ch <= 'M'; ch++)
    {
        bool alreadyGuessed = false;
        for (int i = 0; i < guessedLetters.length(); i++)
        {
            if (guessedLetters[i] == ch)
            {
                alreadyGuessed = true;
                break;
            }
        }

        if (!alreadyGuessed)
        {
            Color(10);
            cout << ch << " ";
        }
        else
        {
            Color(8); 
            cout << "- ";
        }
    }
    cout << endl;
    cout << " ";
    for (char ch = 'N'; ch <= 'Z'; ch++)
    {
        bool alreadyGuessed = false;
        for (int i = 0; i < guessedLetters.length(); i++)
        {
            if (guessedLetters[i] == ch)
            {
                alreadyGuessed = true;
                break;
            }
        }

        if (!alreadyGuessed)
        {
            Color(10);
            cout << ch << " ";
        }
        else
        {
            Color(8); 
            cout << "- ";
        }
    }
    Color(7); 
    cout  << endl;
    printBorder();
    cout << endl;
}
//check if word is completed 
bool isComp(string word, string guessedLetter)
{
    for (int i = 0; i < word.length(); i++)
    {
        bool found = false;
        for (int j = 0; j < guessedLetter.length(); j++)
        {
            if (word[i] == guessedLetter[j])
            {
                found = true;
                break;
            }
        }

        bool isHint = isHintPosition(i, word.length());

        if (!found && !isHint)
            return false;
    }
    return true;
}

//check if letter is present in word to be guessed
bool isPresent(char letter, string word)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] == letter)
            return true;
    }
    return false;
}
//check if input is already guessed
bool guessedAlready(char letter, string guessedLetter)
{
    for (int i = 0; i < guessedLetter.length(); i++)
    {
        if (guessedLetter[i] == letter)
            return true;
    }
    return false;
}
//load file and select word randomly 
string* loadWordFromFile(const string& filename, int& wordCount)
{
    ifstream file(filename);
    if (!file)
        return 0;

    int capacity = 10;
    wordCount = 0;
    string* words = new string[capacity];
    string line;

    while (getline(file, line))
    {
        if (wordCount == capacity)
        {
            capacity = capacity * 2;
            string* newWords = new string[capacity];
            for (int i = 0; i < wordCount; i++)
            {
                newWords[i] = words[i];
            }
            delete[] words;
            words = newWords;
        }
        words[wordCount++] = line;
    }
    file.close();
    return words;
}
//pick random from file
string pickRandom(string* words, int count)
{
    if (count == 0 or words == nullptr)
    {
        return "W O R D N O O S E";
    }
    srand(time(0));
    int index = rand() % count;
    return words[index];
}

void showInstructions()
{
    system("cls");
    printTitle();
    Color(11);
    cout << "G A M E  I N S T R U C T I O N S :" << endl << endl;
    Color(7);
    cout << "1. A random word will be chosen for you to guess." << endl;
    cout << "2. You need to guess word letter by letter " << endl;
    cout << "3. Each wrong guess will add a part to hangman" << endl;
    cout << "4. You have 6 wrong guess attempts" << endl;
    cout << "5. Win by guessing all letters before the hangman is complete" << endl;
    cout << "6. Only enter single letters (A-Z)" << endl;
    cout << "7. All yellow letters are hint- given for free" << endl<<endl;
    system("pause");
    Color(14);
    cout << "Press any key to return to menu...";
    cin.get();
    system("pause");
}

int showMenu()
{
    system("cls");
    printTitle();
    Color(11);
    cout << "MAIN MENU:" << endl << endl;
    Color(7);
    cout << "1. Start Game" << endl;
    cout << "2. Instructions" << endl;
    cout << "3. Exit" << endl << endl;
    Color(14);
    cout << "Enter your choice (1-3): ";

    int choice;
    cin >> choice;
    return choice;
}

void playGame()
{
    system("cls");
    int wordCount = 0;

    string* words = loadWordFromFile("words.txt", wordCount);
    string wordToGuess = pickRandom(words, wordCount); //picks random 

    for (int i = 0; i < wordToGuess.length(); i++)
    {
        if (wordToGuess[i] >= 'a' and wordToGuess[i] <='z')
            wordToGuess[i] = wordToGuess[i] - 'a' + 'A';
    }
    string guessedLetters = "";

    int wrongGuesses = 0;
    const int maxWrong = 6;

    while (wrongGuesses < maxWrong and !isComp(wordToGuess, guessedLetters))
    {
        system("cls");
        printTitle();

        printHangMan(wrongGuesses);
        printWord(wordToGuess, guessedLetters);
        Color(13);
        cout << "Hint : Letters in yellow are given as hint " << endl;
        Color(7);
        printAvailableLetters(guessedLetters);
        Color(7);

        cout << "Wrong guesses : " << wrongGuesses << " /" << maxWrong << endl;
        Color(14);
        cout << "Enter a letter : ";
        char userInput;
        cin >> userInput;

        if (userInput >= 'a' and userInput <= 'z')
        {
            userInput = userInput - 'a' + 'A';
        }

        if (userInput < 'A' or userInput >'Z')
        {
            Color(12);
            cout << "Please enter a valid letter (A-Z)" << endl;
            system("pause");
            continue;
        }

        if (guessedAlready(userInput, guessedLetters))
        {
            Color(12);
            cout << "You already guessed this letter " << endl;
            system("pause");
            continue;
        }

        guessedLetters += userInput;
        if (!isPresent(userInput, wordToGuess))
        {
            wrongGuesses++;
            Color(12);
            cout << "Wrong guess" << endl;
        }
        else
        {
            Color(10);
            cout << "Good guess" << endl;
        }
        system("pause");
    }
    system("cls");
    printTitle();
    printHangMan(wrongGuesses);
    printWord(wordToGuess, guessedLetters);

    if (isComp(wordToGuess, guessedLetters))
    {
        Color(10);
        cout << "Congratulations, you won" << endl;
        cout << "The word was : " << wordToGuess << endl;
    }
    else
    {
        Color(12);
        cout << "Game over, you lost" << endl;
        cout << "The word was " << wordToGuess << endl;
    }

    delete[] words;
    Color(14);
    cout << endl << "Press any key to return to menu";
    cin.ignore();
    cin.get();
    system("cls");
}


int main()
{
    srand(time(0));
    while (true)
    {
        int choice = showMenu();

        switch (choice)
        {
            case 1:
                playGame();
                break;

            case 2:
                showInstructions();
                break;
            
            case 3:
                Color(11);
                cout << endl << "Thankyou for playing wordnoose !" << endl;
                Color(7);
                return 0;

            default:
                Color(12);
                cout << endl << "Invalid choice, try again" << endl;
                system("pause");
                break;
        }
    }
    return 0;
}


