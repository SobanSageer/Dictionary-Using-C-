// Dictionary.cpp

#include "Dict.h"

DictionaryNode::DictionaryNode()
{
	EndOfWord = false;
	for (int i = 0; i < 26; ++i) {
		children[i] = nullptr;
	}
}

Dictionary::Dictionary() {
	root = new DictionaryNode();
}

void Dictionary::insertWord(string word, string meaning)  //O(L), L==length of word
{
	if (word.empty())
		return;

	DictionaryNode* current = root;
	for (char ch : word) {
		if (!isalpha(ch)) {
			continue;
		}
		int index = tolower(ch) - 'a';
		if (current->children[index] == nullptr) {
			current->children[index] = new DictionaryNode();
		}
		current = current->children[index];
	}

	// Check if the word already exists
	if (current->EndOfWord) {
		cout << word << " word already exists in this Dictionary with meaning " << current->meaning << endl;
		return;
	}

	current->EndOfWord = true;
	current->meaning = meaning;
	saveDictionary();
	cout << "Word added to the Trie Tree successfully!" << endl;;
}

bool Dictionary::insertWordDic(string word, string meaning)  //O(L), L==length of word
{
	if (word.empty())
		return false;

	DictionaryNode* current = root;
	for (char ch : word) {
		if (!isalpha(ch)) {
			continue;
		}
		int index = tolower(ch) - 'a';
		if (current->children[index] == nullptr) {
			current->children[index] = new DictionaryNode();
		}
		current = current->children[index];
	}

	// Check if the word already exists
	if (current->EndOfWord) {
		return false;
	}
	else {
		current->EndOfWord = true;
		current->meaning = meaning;
		return true;
	}
}

string Dictionary::searchWordMeaning(string word)  //O(L), L==length of word
{
	if (word.empty())
		return "Word not found ";

	DictionaryNode* current = root;
	for (char ch : word) {
		if (!isalpha(ch)) {
			continue;
		}
		int index = tolower(ch) - 'a';
		if (current->children[index] == nullptr) {
			return "Word not found ";
		}
		current = current->children[index];
	}
	if (current != nullptr && current->EndOfWord) {
		cout << "Meaning: ";
		return current->meaning;
	}
	return "Word not found ";
}

void Dictionary::updateWordMeaning(string word, string newMeaning)  //O(L), L==length of word
{
	if (word.empty())
		return;

	DictionaryNode* current = root;
	for (char ch : word) {
		if (!isalpha(ch)) {
			continue;
		}
		int index = tolower(ch) - 'a';
		if (current->children[index] == nullptr) {
			return; // Word not found in the TrieTree
		}
		current = current->children[index];
	}

	if (current != nullptr && current->EndOfWord) {
		string choice;
		cout << "Are you sure you want to update the meaning of '" << word << "'? (yes/no): ";
		cin >> choice;

		if (choice == "yes") {
			current->meaning = newMeaning; // Update the meaning of the word
			cout << "Meaning of '" << word << "' updated successfully!" << endl;
		}
		else {
			cout << "Meaning of '" << word << "' not updated." << endl;
		}
	}
}

void Dictionary::deleteWord(string word)  //O(L), L==length of word
{
	deleteWordHelper(root, word, 0);
}

void Dictionary::suggestWords(string precede) //O(p + s),  p == length of the prefix, s == number of suggestions generated
{
	
	DictionaryNode* current = root;
	int i = 0;
	for (char ch : precede) {
		
		if (!isalpha(ch)) {
			return;
		}
		int index = tolower(ch) - 'a';
		if (current->children[index] == nullptr) {
			cout << "No Suggestions available for this prefix" << endl;
			return;
		}
		
		
		current = current->children[index];
		i++;
	}
	

	string* suggestions = new string[10];
	int count = 0;
	string word = precede;
	suggestWordsHelper(current, word, suggestions, count);

	cout << "Suggestions for words starting with '" << precede << "':" << endl;
	if (count == 0) {
		
		
		cout << "No words found." << endl;
	}
	else {
		for (int i = 0; i < count; ++i) {
			cout << suggestions[i] << endl;
		}
	}

	delete[] suggestions; // Free allocated memory
}

void Dictionary::loadDictionary(const string& filename) //O(c + w * l), c == no. of characters in file, w == no. of words, l == average length words
{
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Error opening file: " << filename << endl;
		return;
	}

	string word = "", meaning = "";
	char ch;
	bool isWord = true, lineEnd = false;
	int count = 0;
	while (file.get(ch)) {
		if (ch == '\n') {
			lineEnd = true;
		}

		if ((ch == '\n' || ch == '\t' || ch == ' ') && !lineEnd) {
			isWord = false;
			continue;
		}

		if (isWord) {
			word += ch;
		}
		else {
			meaning += ch;
		}

		if (lineEnd) {
			lineEnd = false;

			if (!insertWordDic(word, meaning)) {
				// cout << word <<  "this word already exist  " << endl;
				count++;
			}

			// Clear word and meaning for the next line
			word = "";
			meaning = "";
			isWord = true;
		}
	}

	file.close();
	cout << "Dictionary loaded successfully!" << endl;
	cout << "There are ( " << count << " ) repeated words in the loaded Dictionary " << endl;
}

void Dictionary::saveDictionary() //O(n + c) n==no. of nodes, c== no. of characters
{
	saveDictionaryhelper("Dictionary.txt", root, "");
}

bool Dictionary::deleteWordHelper(DictionaryNode* current, string word, int level) //O(L), L==length of word
{
	if (current == nullptr) {
		return false;
	}

	if (level == word.length()) {
		if (current->EndOfWord) {
			current->EndOfWord = false;
			current->meaning = ""; // Remove the meaning
			return isEmpty(current);
		}
		return false;
	}

	int index = word[level] - 'a';
	if (deleteWordHelper(current->children[index], word, level + 1)) {
		delete current->children[index];
		current->children[index] = nullptr;
		return !current->EndOfWord && isEmpty(current);
	}
	return false;
}

void Dictionary::suggestWordsHelper(DictionaryNode* node, string& word, string* suggestions, int& count) //O(N), N==total nodes (worst case)
{
	
	if (node == nullptr) {
		return;
	}

	if (node->EndOfWord) {
		if (count < 10) {
			suggestions[count++] = word;
		}
		else {
			return; // Limit reached
		}
	}

	for (int i = 0; i < 26; ++i) {
		if (node->children[i] != nullptr) {
			word += char('a' + i);
			suggestWordsHelper(node->children[i], word, suggestions, count);
			word.pop_back(); // Remove the last character manually
		}
	}
}

bool Dictionary::isEmpty(DictionaryNode* node) //O(1)
{
	for (int i = 0; i < 26; ++i) {
		if (node->children[i] != nullptr) {
			return false;
		}
	}
	return true;
}

void Dictionary::saveDictionaryhelper(const string& filename, DictionaryNode* node, string word) {
	ofstream file(filename, ios::app); // Append mode
	if (!file.is_open()) {
		cout << "Error creating/opening file: " << filename << endl;
		return;
	}

	if (node->EndOfWord) {
		file << word << "\t" << node->meaning << endl;
	}

	for (int i = 25; i >= 0; --i) {
		if (node->children[i] != nullptr) {
			string newWord = word + char('a' + i);
			saveDictionaryhelper(filename, node->children[i], newWord);
		}
	}

	file.close();
}


void setConsoleColor(int textColor, int bgColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor | (bgColor << 4));
}
void printMenu() {
	system("cls");

	cout << "-------------------------------------" << endl;
	cout << "           DICTIONARY APP           " << endl;
	cout << "-------------------------------------" << endl;
	cout << "1. Insert a word with meaning" << endl;
	cout << "2. Search for the meaning of a word" << endl;
	cout << "3. Update the meaning of a word" << endl;
	cout << "4. Delete a word" << endl;
	cout << "5. Suggest words based on a prefix" << endl;
	cout << "6. Load dictionary from file" << endl;
	cout << "7. Save dictionary to file" << endl;
	cout << "8. Exit" << endl;

	cout << "-------------------------------------" << endl;
	cout << "Enter your choice: ";
}