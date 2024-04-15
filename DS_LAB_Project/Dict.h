// Dictionary.h

#ifndef DICTIONARY_H
#define DICTIONARY_H

//necessary libraries
#include <iostream> //for input, output
#include <fstream> //for file handling
#include <string>  //for strings
#include <Windows.h>  //for colors
using namespace std;

class DictionaryNode  // Dictionary Node Class
{
public:
	DictionaryNode();
	DictionaryNode* children[26];
	bool EndOfWord;
	string meaning;
};

class Dictionary //Dictionary Main Class
{
private:
	DictionaryNode* root;

public:
	Dictionary();

	void insertWord(string word, string meaning);    //insert words
	bool insertWordDic(string word, string meaning);     //returns true/false
	string searchWordMeaning(string word);     //search meaning
	void updateWordMeaning(string word, string newMeaning);    //update word
	void deleteWord(string word);     //delete word
	void suggestWords(string precede);     //suggestions
	void loadDictionary(const string& filename);    // load file
	void saveDictionary();    //save file

private:
	bool deleteWordHelper(DictionaryNode* current, string word, int level); //helps deletion
	void suggestWordsHelper(DictionaryNode* node, string& word, string* suggestions, int& count); //helps in suggestions
	bool isEmpty(DictionaryNode* node); //checks for empty nodes , used in deletion
	void saveDictionaryhelper(const string& filename, DictionaryNode* node, string word); //helps in saving file

};

void printMenu();// prints menu 
void setConsoleColor(int color, int bg); //console color
#endif // DICTIONARY_H


