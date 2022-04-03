/*
Name: Muhammad Waqar Makki
Reg:  L1F18BSCS0028
CC-Section-G2
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include<cstring>
#include<algorithm>
using namespace std;

#include"Stack.h"

// Scanner...

int totalTokens;

void readTable(int TT[45][21]){

	ifstream fin("transitionTable.txt");
	if (!fin){
		cout << "File not found..." << endl;
	}
	else{
		for (int i = 0; i < 45; i++)
		for (int j = 0; j < 21; j++)
			fin >> TT[i][j];
		fin.close();
	}
}

void readStates(int *states){

	ifstream fin("states.txt");
	if (!fin){
		cout << "File not found..." << endl;
	}
	else{
		for (int i = 0; i < 45; i++)
			fin >> states[i];
		fin.close();
	}
}

void initlize_M(int *m){

	for (int i = 0; i < 131; i++){
		if ((i > 64 && i < 91) || (i > 96 && i < 123))
			m[i] = 1;
		else if (i > 47 && i < 58)
			m[i] = 2;
		else if (i == 33)
			m[i] = 3;
		else if (i == 61)
			m[i] = 4;
		else if (i == 42)
			m[i] = 5;
		else if (i == 43)
			m[i] = 6;
		else if (i == 47)
			m[i] = 7;
		else if (i == 45)
			m[i] = 8;
		else if (i == 62)
			m[i] = 9;
		else if (i == 60)
			m[i] = 10;
		else if (i == 38)
			m[i] = 11;
		else if (i == 124)
			m[i] = 12;
		else if (i == 37)
			m[i] = 13;
		else if (i == 58)
			m[i] = 14;
		else if (i == 91)
			m[i] = 15;
		else if (i == 123)
			m[i] = 16;
		else if (i == 125)
			m[i] = 17;
		else if (i == 93)
			m[i] = 18;
		else if (i == 95)
			m[i] = 19;
		else if (i == 46)
			m[i] = 20;
		else if (i == 130)
			m[i] = 21;
		else
			m[i] = -1;
	}
}

void createToken(int num, char *arr){
	
	ofstream fout("tokens.txt", fstream::app);
	string s,s1=arr;
	switch (num){
	case 1:
		fout << "< " << arr << ", identifier >\n";
		break;
	case 2:
		fout << "< " << arr << ", number >\n";
		break;
	case 3:
		fout << "< " << arr << ", != >\n";
		break;
	case 4:
		fout << "< " << arr << ", <> >\n";
		break;
	case 5:
		fout << "< " << arr << ", =:= >\n";
		break;
	case 6:
		fout << "< " << arr << ", == >\n";
		break;
	case 7:
		fout << "< " << arr << ", * >\n";
		break;
	case 8:
		fout << "< " << arr << ", + >\n";
		break;
	case 9:
		fout << "< " << arr << ", / >\n";
		break;
	case 10:
		fout << "< " << arr << ", - >\n";
		break;
	case 11:
		fout << "< " << arr << ", >> >\n";
		break;
	case 12:
		fout << "< " << arr << ", << >\n";
		break;
	case 13:
		fout << "< " << arr << ", ++ >\n";
		break;
	case 14:
		fout << "< " << arr << ", =+ >\n";
		break;
	case 15:
		fout << "< " << arr << ", %% >\n";
		break;
	case 16:
		fout << "< " << arr << ", || >\n";
		break;
	case 17:
		fout << "< " << arr << ", => >\n";
		break;
	case 18:
		fout << "< " << arr << ", =< >\n";
		break;
	case 19:
		fout << "< " << arr << ", % >\n";
		break;
	case 20:
		fout << "< " << arr << ", : >\n";
		break;
	case 21:
		fout << "< " << arr << ", :: >\n";
		break;
	case 22:
		fout << "< " << arr << ", -- >\n";
		break;
	case 23:
		fout << "< " << arr << ", [ >\n";
		break;
	case 24:
		fout << "< " << arr << ", { >\n";
		break;
	case 25:
		fout << "< " << arr << ", < >\n";
		break;
	case 26:
		fout << "< " << arr << ", >  >\n";
		break;
	case 27:
		fout << "< " << arr << ", } >\n";
		break;
	case 28:
		fout << "< " << arr << ", ] >\n";
		break;
	case 29:
		fout << "<" << arr << ", keyword >\n";
	}
	totalTokens++;
	fout.close();
}

void readKeywords(string *&k){

	ifstream fin("keywords.txt");
	if (!fin){
		cout << "File not found..." << endl;
	}
	else{
		int i = 0;
		while (!fin.eof())
			getline(fin, k[i++]);
	}
	fin.close();
}

bool checkKeywords(string *keywords, char *out){

	string str;
	for (int i = 0; i < 60; i++){
		str = keywords[i];
		if (str == out)
			return true;
	}
	return false;
}

void scanner(){
	ifstream fin("input.txt");
	if (!fin)
		cout << "Unable to open the file...\n\n";
	else{

		string *keywords = new string[60];
		readKeywords(keywords);

		int size = 0;
		char arr[1000];
		while (!fin.eof())
			fin >> arr[size++];

		int TT[45][21];
		readTable(TT);

		int states[45];
		readStates(states);

		int m[131];
		initlize_M(m);

		int cs = 0, curr = 0, c = 0, p2 = 0;
		arr[size - 1] = '\0';
		char out[20] = { '\0' };
		while (curr < size){
			if (!states[cs]){
				int x = m[arr[curr]] - 1;
				cs = TT[cs][x];
				out[p2++] = arr[curr];
				if (checkKeywords(keywords, out)){
					createToken(29, out);
					cs = 0;
					for (int i = 0; i < p2; i++)
						out[i] = '\0';
					p2 = 0;
					curr++;
					continue;
				}
			}
			else{
				if (states[cs] < 0){
					int t = states[cs];
					t *= -1;
					out[p2 - 1] = '\0';
					createToken(t, out);
					cs = 0;
					for (int i = 0; i < p2 - 1; i++)
						out[i] = '\0';
					p2 = 0;
					curr--;
					continue;
				}
				else{
					createToken(states[cs], out);
					cs = 0;
					for (int i = 0; i < p2; i++)
						out[i] = '\0';
					p2 = 0;
					continue;
				}
			}
			curr++;
		}
		cout << "Possible Lexemes are stored in 'Output.txt'\n\n" << endl;
		fin.close();
	}
}

// Parser...

// Global Variables...
Stack<int> Stk;
int **ParseTable;
string *TokenMap;
int NumberOfTokens;
int **Rules;
string *Variables;
int totalErrors;

// Functions...
void readParseTable() {
	int row; int col;
	ifstream fin("parseTable.txt", ios::in);
	fin >> row;
	fin >> col;
	ParseTable = new int*[row];
	for (int i = 0; i < row; i++) {
		ParseTable[i] = new int[col];
		for (int j = 0; j < col; j++) {
			fin >> ParseTable[i][j];
		}
	}
}

void readProductions() {
	int row; int col;
	ifstream fin("Productions.txt", ios::in);
	fin >> row;
	Rules = new int*[row];
	for (int i = 0; i < row; i++) {
		fin >> col;
		Rules[i] = new int[col + 1];
		Rules[i][0] = col;
		for (int j = 1; j < col + 1; j++)
			fin >> Rules[i][j];
	}
}

void readTokenMap() {
	ifstream fin("TokenMap.txt", ios::in);
	fin >> NumberOfTokens;
	TokenMap = new string[NumberOfTokens];
	for (int i = 0; i < NumberOfTokens; i++)
		fin >> TokenMap[i];
}

void readVariables(){
	ifstream fin("variables.txt", ios::in);
	int size = 0;
	fin >> size;
	Variables = new string[size];
	for (int i = 0; i < size; i++)
		fin >> Variables[i];
}

int MatchTokenInMap(string S) {
	for (int i = 0; i < NumberOfTokens; i++)
	if (S.compare(TokenMap[i]) == 0)
		return (i + 1) * -1;
	// Match not found...
	return 0;
}

void PrintStack(ofstream &fout, int s = 0) {

	if (s == 0){
		if (Stk.isEmpty())
			return;
		int value = Stk.pop();

		PrintStack(fout);
		if (value == -25){
			cout << "$ ";
			fout << "$ ";
		}
		else if (value == -100){
			cout << "NULL ";
			fout << "NULL ";
		}
		else if (value > 0){
			cout << Variables[--value] << " ";
			fout << Variables[value] << " ";
			value++;
		}
		else if (value < 0){
			value *= -1;
			cout << TokenMap[--value] << " ";
			fout << TokenMap[value] << " ";
			value++;
			value *= -1;
		}
		Stk.push(value);
	}
	else{
		s *= -1;
		cout << TokenMap[--s];
		fout << TokenMap[s];
	}
}

void Parsing(int C, ofstream &fout) {

	ofstream fError("Errors.txt", ios::app);
	while (true){
		if (Stk.isEmpty()){
			cout << "Pop and Scan Error()\n";
			PrintStack(fError);
			cout << endl;
			fout << endl;
			fError << "\t\t\t\tPop and Scan Error()\n";
		}

		PrintStack(fout);
		cout << endl;
		fout << endl;
		int R = Stk.pop();

		if (R == -100)				// if stack top is null then pop()
			R = Stk.pop();
		if (R == C){				// if top of stack is same as top of input...
			cout << "\t\t\t\t\t\t\t\t Matched...\n\n";
			fout << "\t\t\t\t\t\t\t\t Matched...\n\n";
			return;
		}
		else if (R > C){			// top of stack is a variable...
			int c = (C*-1);
			if (R < 0)
				R *= -1;
			int val = ParseTable[--R][--c];
			if (val == 101){
				totalErrors++;
				cout << "Pop Error()\n";
				PrintStack(fError);
				cout << endl;
				fout << endl;
				fError << "\t\t\t\tPop Error()\n";
				return;
			}
			else if (val == 102){
				totalErrors++;
				cout << "Scan Error()\n";
				PrintStack(fError);
				cout << endl;
				fout << endl;
				fError << "\t\t\t\tScan Error()\n";
				return;
			}
			else{
				val--;
				for (int i = Rules[val][0]; i >= 1; i--)
					Stk.push(Rules[val][i]);
			}
		}
		else
			return;
	}
}

void Parser(string S, ofstream &fout) {
	int C = MatchTokenInMap(S);
	if (C == 0) {
		cout << "Token not found...\n" << endl;
		fout << "Token not found...\n" << endl;
		return;
	}
	else{
		cout << "\t\t\t\t\t\t\t\t ";
		PrintStack(fout, C);
		cout << endl;
		fout << endl;
		Parsing(C, fout);
	}
}

void readTokens(string *&tokens){
	ifstream fin("tokens1.txt",ios::in);
	int size = 0;
	string line;
	int i = 0;
	string word1 = "", word2 = "";
	bool flag = false;
	while (getline(fin, line)){
		word1 = "", word2 = "", flag = false;
		for (int j = 1; j < line.size() - 2; j++){
			if (line[j] == ','){
				flag = true;
				continue;
			}
			if (flag == false)
				word1 += line[j];
			else
				word2 += line[j];
		}
		if (word2 == " keyword"){
			word1.erase(remove(word1.begin(), word1.end(), ' '), word1.end());
			tokens[i++] = word1;
			size++;
		}
		else if (word2 == " ::"){
			tokens[i++] = ":";
			tokens[i++] = ":";
			size += 2;
		}
		else{
			word2.erase(remove(word2.begin(), word2.end(), ' '), word2.end());
			tokens[i++] = word2;
			size++;
		}
	}
	totalTokens = size;
	fin.close();
}

void readTokenFromFile() {
	ofstream fout("Output.txt", ios::app);
	string *tokens = new string[totalTokens+10];
	readTokens(tokens);
	for (int l = 0; l < totalTokens; l++)
		Parser(tokens[l], fout);
	PrintStack(fout);
	cout << endl << endl;
}

void parser(){

	// -25 denotes $ sign
	Stk.push(-25);
	Stk.push(1);

	readVariables();
	readParseTable();
	readProductions();
	readTokenMap();

	cout << "Stack\t\t\t\t\t\t\t\tInput Element\n";
	cout << "===============================================================================\n";

	readTokenFromFile();

	if (totalErrors == 0)
		cout << "String Parsed without any ERRORS...\n\n";
	else
		cout << "String parsed with " << totalErrors << " ERRORS\n\n";

}

int main(){

	scanner();

	parser();

	system("pause");
	return 0;
}