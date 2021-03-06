// CST126_Lab4.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<iostream>
using namespace std;
#include<string>
#include<fstream>


struct date
{
	int year;
};
typedef struct date DATE;


void Read_origin_year(ifstream &filein, DATE &date)
{
	filein >> date.year;
}


struct Word
{
	string word;
	string definition;
	DATE origin_year;

};
typedef struct Word WORD;


struct node
{
	WORD data;
	struct node *next;
};
typedef struct node NODE;

struct list
{
	NODE *head;
	NODE *end;
};
typedef struct list LIST;

void IniList(LIST &l)
{
	l.head = NULL;
	l.end = NULL;
}

NODE *InitalizeNode(WORD x)
{
	NODE *p = new NODE;
	if (p == NULL)
	{
		return NULL;
	}
	p->data = x;
	p->next = NULL;
	return p;
}

void Add_EndNode(LIST &l, NODE *p)
{
	if (l.head == NULL)
	{
		l.head = l.end = p;
	}
	else
	{
		l.end->next = p;
		l.end = p;
	}
}


void Read_Word(ifstream &filein, WORD & w)
{
	getline(filein, w.word, ',');
	filein.seekg(1, 1);
	getline(filein, w.definition, ',');
	filein.seekg(1, 1);
	Read_origin_year(filein, w.origin_year);
	filein.seekg(2, 1);

	string temp;
	getline(filein, temp);
}

void WordList(ifstream &filein, LIST &l)
{
	while (!filein.eof())
	{
		WORD word;
		Read_Word(filein, word);
		NODE *p = InitalizeNode(word);
		Add_EndNode(l, p);
	}
}

void DeleteNode(LIST &l)
{
	NODE *p = NULL;
	while (l.head != NULL)
	{
		p = l.head;
		l.head = l.head->next;
		delete p;
	}
}

string _word(string word)
{
	int length = word.length();
	int i;
	for (i = length - 1; i >= 0; i--)
	{
		if (word[i] == ' ')
		{
			break;
		}
	}
	return word.substr(i + 1);

}
// display function
void display(WORD word)
{
	cout << word.word << ": " << word.definition << ". First used in " << word.origin_year.year << endl;
}

void display_word(LIST l)
{
	int dem = 1;
	for (NODE *k = l.head; k != NULL; k = k->next)
	{
		display(k->data);
	}
}

void LookUpWord(LIST l, string word)
{
	for (NODE *k = l.head; k != NULL; k = k->next)
	{

		string ten = _word(k->data.word);
		if (_stricmp((char *)ten.c_str(), (char *)word.c_str()) == 0)
		{
			display(k->data);
			cout << endl << endl;
		}
	}
}

int main()
{
	char dict[10][1][255] =
	{
		"CRC",
		"The_Three_C's",
		"Epic",
		"Project_Chartering",
		"Kanban",
		"AntiPattern",
		"Unit_Testing",
		"User_Stories",
		"Three_Amigos",
		"Timebox"
	};

	for (int i = 0; i < 10; i++)    //This loops on the rows.
	{
		cout << *dict[i] << endl;
	}
	LIST l;
	IniList(l);
	// open file
	ifstream filein;
	filein.open("Words.TXT", ios::in);
	WordList(filein, l);

	string userinput;
	cout << "\nWhat term do you want? ";
	getline(cin, userinput);

	LookUpWord(l, userinput);

	DeleteNode(l);
	filein.close();

	system("pause");
	return 0;
}

