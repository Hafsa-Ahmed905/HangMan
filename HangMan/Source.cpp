#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cctype>
#include <stdlib.h>
using namespace std;
bool login(const string& username, const string& password) {//for login by checking username and password from the file users.txt
	ifstream file1("users.txt");
	string line, name, pass;
	getline(file1, line);
	while (getline(file1, line)) {// processing the code for each line
		stringstream str(line);// to extract username and password token(parts) from the line
		getline(str, name, '\t');//reads the username and stores it in name
		getline(str, pass, '\t');//reads tge password and stores it in pass
		if (name == username && pass == password) {
			return true;//checking the username and password
		}

	}
	return false;
}

void userRegister() {//To register a new member
	string username, password;
	cout << "Enter the UserName: ";
	cin >> username;
	cout << "Enter the Password: ";
	cin >> password;
	ofstream file1("users.txt", ios::app);//to add a new member in new line
	if (!file1) {
		cerr << "Error! Unable to Open file" << endl;//error check
	}
	file1 << username << "\t" << password << endl;//saving it in file
	file1.close();
	cout << "Registered successfully" << endl;

}
int readWords(const string& word,string words[], int maxWords) {// This function reads words from the file and returns total words in it.
	
	int totalWords = 0;
	ifstream file1("words.txt");
	if (!file1) {
		cerr << "Error! Unable to Open file" << endl;//error check
		return -1 ;
	}
	else {
		string word;
		while (getline(file1, word) && totalWords < maxWords) {//continues as two conditions are met.First read the next line from file and stores it in variable word.Then Checks if total number  of words is less than Maximum Number allowed.
			words[totalWords] = word;//stores current word in words array
			totalWords++;//incrementation of words
		}
	}
		file1.close();
	
	return totalWords;
}
void displayHangMan(int tries) {//display one body part of hangman with each try failed
	switch (tries) {
	case 0:
		cout << "_________________\n"
			<< "|               |\n"
			<< "|                \n"
			<< "|                \n"
			<< "|                \n"
			<< "|                \n"
			<< "|____\n";
		break;
	case 1:
		cout << "_________________\n"
			<< "|               |\n"
			<< "|               O\n"
			<< "|                \n"
			<< "|                \n"
			<< "|                \n"
			<< "|____\n";
		break;
	case 2:
		cout << "_________________\n"
			<< "|               |\n"
			<< "|               O\n"
			<< "|               |\n"
			<< "|                \n"
			<< "|                \n"
			<< "|____\n";
		break;
	case 3:
		cout << "_________________\n"
			<< "|               |\n"
			<< "|               O\n"
			<< "|              /|\n"
			<< "|                \n"
			<< "|                \n"
			<< "|____\n";
		break;
	case 4:
		cout << "_________________\n"
			<< "|               |\n"
			<< "|               O\n"
			<< "|              /|\\" << endl
			<< "|                \n"
			<< "|                \n"
			<< "|____\n";
		break;
	case 5:
		cout << "_________________\n"
			<< "|               |\n"
			<< "|               O\n"
			<< "|              /|\\" << endl
			<< "|              /\n"
			<< "|                \n"
			<< "|____\n";
		break;
	case 6:
		cout << "_________________\n"
			<< "|               |\n"
			<< "|               O\n"
			<< "|              /|\\" << endl
			<< "|              / \\" << endl
			<< "|                \n"
			<< "|____\n";
		break;

	}
}
void storeRecord(const string& username, const string& status, int score) {//stores the username,score and status after playing game.
	ofstream file("game_records.txt", ios::app);//add the player record in new line
	if (!file) {
		cerr << "Error! Unable to Open File." << endl;//error check
		return;
	}
	file << username << "\t\t" << status << "\t\t" << score << endl;//writes the username,status and score to new file.
	file.close();

}

void hangMan(string username) {
	const int maxWords = 10;
	string words[maxWords];//initialize array 
	int totalWords = readWords("words.txt", words, maxWords);//reads words from the file 
	if (totalWords == 0) {
		cerr << "Error! There are no words in the words file" << endl;//error check
	}
	srand(time(0));
	string word = words[rand() % totalWords];//select a random word from the words given in file
	int totalTries = 6;
	int tries = 0;
	char guess;
	//bool correct = false;
	string guessWord(word.size(), '-');//replacement of word with dashes.
	while (tries < totalTries && guessWord != word) {//loop continues till the number of tries is less than maximum tries and guessed word is not equal to the actual word
		bool correct = false;
		cout << "Enter your guess: ";
		cin >> guess;
		guess = tolower(guess);//converts into lowercase incase user enters uppercase letter.
		for (int i = 0; i < word.size(); i++) {//loop iterates with each letter of word
			if (word[i] == guess) {//if user's guess and letter in word matches,the dash is replaced with guessed letter
				guessWord[i] = guess;
				correct = true;

			}
		}


		if (!correct) {//if the user guesses wrong,tries increment until total tries
			tries++;
			cout << "Incorrect guess! You have " << totalTries - tries << " tries left"<< endl;
		}
		else { cout << "Good guess!"<< endl; }//if he guesses correct, say Good guess to him and continue the game
		displayHangMan(tries);//display the HangMan simultaneously
		cout << "Guessed Word= " << guessWord << endl;
	}
	string status;
	int score = totalTries - tries;


	if (guessWord == word) {//if the user guesses the word 

		cout << "Congratulations! You guessed the word: " << word << endl;
		status = "Won";
		}
		else {//if the user fails to guess the word in 6 tries
			cout << "Sorry, you ran out of tries! The word was: " << word<< endl;
			status = "Lost";
		}
	storeRecord(username, status, score);//stores the user data
	}


int main()
{
	string username, password;
	int option;
	
	while (true)//loop will work until the user chooses to quit
	{
		cout << "Let's play Hangman!" << endl;
		cout << "Choose an Option: " << endl
			<< "1. Login" << endl
			<< "2. Register" << endl
			<< "3. Quit" << endl;
		cin >> option;
		switch (option) {
		case 1: {
			
			bool loginSuccess = false;//for successful login 
			while (!loginSuccess)//loop continues untill successful login occurs
			{

				cout << "Enter username: ";
				cin >> username;
				cout << "Enter password: ";
				cin >> password;

				if (login(username, password)) {//calls the login function.If login is successful,Call the HangMan function to Play game
					cout << "Login Successful!"<< endl;
					loginSuccess = true;
					hangMan(username);
				}
				else {
					cout << "Invalid username or password. Please try again." << endl;//if the login function fails,display error message
				}
				
			}
			break;
		}
		case 2: {
			userRegister();//calls the userRegister function to register new member
			break;
		}

		case 3: {
			cout << "ThankYou for accessing";
			return 0;
		}

		default: {
			cout << "Invalid option.Please try again. " << endl;//in case user enter values other than 1,2 and 3 ,it shows error
			break;
		}
		}
		while (true) {
			char response;
			cout << "Do you want to play again? (Y/N): ";//loop continues until user makes valid choice
			cin >> response;
			if (response == 'y' || response == 'Y') {
				system("CLS");//Used to clear the console
				break;
			}
			else if (response == 'n' || response == 'N') {
				cout << "Thankyou for playing!" << endl;
				return 0;
			}
			else { cout << "Invalid Input.Please Enter Y or N" << endl;//Input Validation
			}
		}
	}
	
	return 0;
}