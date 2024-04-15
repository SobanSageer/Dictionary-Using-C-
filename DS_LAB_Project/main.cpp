// main.cpp

#include "Dictionary.h"

int main() {
	Dictionary trie;

	int choice;
	string word, meaning, filename;
	do {
		setConsoleColor(1,15);
		printMenu();
		cin >> choice;

		switch (choice) {
		case 1:
			setConsoleColor(15, 1);
			cout << "Enter a word to insert into the Trie Tree: ";
			cin >> word;
			cout << "Enter the meaning of the word: ";
			cin.ignore(); // Ignore the newline character 
			cin >> meaning;
			trie.insertWord(word, meaning);
			break;
		case 2:
			setConsoleColor(15, 1);
			cout << "Enter a word to search in the Trie Tree: ";
			cin >> word;
			cout  << trie.searchWordMeaning(word) << endl;
			break;
		case 3:
			setConsoleColor(15, 1);
			cout << "Enter a word to update its meaning: ";
			cin >> word;
			cout << "Enter the new meaning of the word: ";
			cin.ignore();
			cin >> meaning;
			trie.updateWordMeaning(word, meaning);
			break;
		case 4:
			setConsoleColor(15, 1);
			cout << "Enter a word to delete from the Trie Tree: ";
			cin >> word;
			trie.deleteWord(word);
			cout << "Word deleted from the Trie Tree." << endl;
			break;
		case 5:
			setConsoleColor(15, 1);
			cout << "Enter a prefix to get word suggestions: ";
			cin >> word;
			trie.suggestWords(word);
			break;
		case 6:
			setConsoleColor(15, 1);
			system("cls");
			trie.loadDictionary("Dictionary.txt");
			break;

		case 8:
			setConsoleColor(15, 1);
			cout << "Exiting..." << endl;
			break;
		case 7:
			setConsoleColor(15, 1);
			cout << "Enter the filename to save the dictionary: ";
			cin >> filename;
			trie.saveDictionary(filename);
			cout << "Dictionary saved to " << filename << endl;
			break;

		default:
			setConsoleColor(15, 1);
			cout << "Invalid choice. Please enter a valid option." << endl;
			break;
		}
		setConsoleColor(1, 15);
		cout << "Press Enter to continue...";
		cin.ignore();
		cin.get();
		system("cls");

	} while (choice != 8);
	system("pause");
	return 0;
}