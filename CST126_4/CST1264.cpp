// CST126_4.cpp : Defines the entry point for the console application.
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

void reading_year_function(ifstream &filein, DATE &date)
{
	filein >> date.year;
}

// struct
struct Word
{
	string word;
	string definition;
	DATE year;

};
typedef struct Word Word;

struct node
{
	Word data;
	struct node *next;
};
typedef struct node NODE;

struct list
{
	NODE *head;
	NODE *end;
};
typedef struct list LIST;


void InitList(LIST & list)
{
	list.head = NULL;
	list.end = NULL;
}


NODE *IniNode(Word x)
{
	NODE *p = new NODE;
	if (p == NULL)
	{
		cout << "\nError";
		return NULL;
	}
	p->data = x;
	p->next = NULL;
	return p;
}


void Addnode(LIST &l, NODE *p)
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

//method reading data from file
void reading_file(ifstream &filein, Word &d)
{

	getline(filein, d.word, ','); // stop at ,
	filein.seekg(1, 1);
	getline(filein, d.definition, ','); // stop at ,
	filein.seekg(1, 1);
	reading_year_function(filein, d.year);
	filein.seekg(2, 1);
	string temp;
	getline(filein, temp);
}


//read data from file
void ReadListDefination(ifstream &filein, LIST &l)
{
	//read until the end
	while (!filein.eof())
	{
		// read word
		Word d;
		reading_file(filein, d);
		// read definition
		NODE *p = IniNode(d);
		// add word to node
		Addnode(l, p);
	}
}

// free memory
void free_memory(LIST & list)
{
	NODE *p = NULL;
	while (list.head != NULL)
	{
		p = list.head;
		list.head = list.head->next;
		delete p;
	}
}


string dictionary(string dict)
{

	int length = dict.length();
	int i;
	for (i = length - 1; i >= 0; i--)
	{
		if (dict[i] == ' ')
		{
			break;
		}
	}

	return dict.substr(i + 1);

}


void Display(Word d)
{
	cout << d.word << " :" << d.definition << ". First used in " << d.year.year;
}

void DictionaryList_Display(LIST l)
{
	/*int count = 1;*/
	for (NODE *k = l.head; k != NULL; k = k->next)
	{
		Display(k->data);
	}
}
// look up definition based on name
void definition_Lookup(LIST l, string dict)
{
	for (NODE *k = l.head; k != NULL; k = k->next)
	{
		string d = dictionary(k->data.word);
		if (_stricmp((char *)d.c_str(), (char *)dict.c_str()) == 0)
		{
			Display(k->data);
			cout << endl << endl;

		}
	}
}



int main()
{

	char dict[10][3][255] =
	{
		"CRC cards","CRC cards (for Class, Responsibilities, Collaborators) are an activity bridging the worlds of role-playing games and object-oriented design.","1988",
		"The Three C’s","Card, Conversation, Confirmation; this formula (from Ron Jeffries) captures the components of a User Story.","2001",
		"Epic","a large user story that cannot be delivered as defined within a single iteration or is large enough that it can be split into smaller user stories.","2004",
		"Project Chartering","The team develops and maintains a high-level summary of the project's key success factors, synthetic enough that it can be displayed on one wall of the team room as a flipchart-sized sheet of paper.","2006",
		"Kanban","a means to design, manage, and improve flow systems for knowledge work. The method also allows organizations to start with their existing workflow and drive evolutionary change.","2004",
		"AntiPattern","are common solutions to common problems where the solution is ineffective and may result in undesired consequences.","1995",
		"Unit Testing","a short program fragment written and maintained by the developers on the product team, which exercises some narrow part of the product's source code and checks the results.","1976",
		"User Stories","In consultation with the customer or product owner, the team divides up the work to be done into functional increments called 'user stories'.","2001",
		"Three Amigos","refers to the primary perspectives to examine an increment of work before, during, and after development.","2009",
		"Timebox","a previously agreed period of time during which a person or a team works steadily towards completion of some goal.","1998"
	};

	for (int i = 0; i < 10; i++)    //This loops on the rows.
	{
		cout << *dict[i] << endl;
	}

	LIST dictionary;
	InitList(dictionary);
	// open file
	ifstream filein;
	filein.open("Words.TXT", ios::in);
	ReadListDefination(filein, dictionary);


	string word;
	cout << "\n\nWhat term do you want? ";
	getline(cin, word); //get word
	definition_Lookup(dictionary, word); //call definition_Lookup

	free_memory(dictionary);
	filein.close();

	system("pause");
	return 0;
}