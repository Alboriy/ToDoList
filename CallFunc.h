#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <ctime>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;



//Cтруктура даты заметки
 struct Dates {

	int Day = 00;
	int Month = 00;
	int Year = 0000;

};

//Структура списка дел
 struct ToDoList {

	string Title;
	string Description;
	int Priority = 0;
	Dates Date;

};


 //Прототипы функций
 void FillSheets(ToDoList* shop, const int amount, string filename, bool flag);
 ToDoList* InitStruct(ToDoList* sheet, int amount);
 void ShowAllInFile(fstream& file,string,ToDoList*,int size);
 void SaveInFile(string filename, ToDoList* sheet, int amount,bool flag);
 void AddSheet(fstream& file, ToDoList* toDoSheet, int amount, string PathToFile, int YesOrNot);
 void Action(ToDoList* toDoSheet);
 void DeleteWork(ToDoList* toDoSheet, string PathToFile, int size, fstream& file);
 void RemoveFile(string PathToFile);
 void SearchWork(ToDoList* toDoSheet, string PathToFile, fstream& file);
 void ReductWork(ToDoList* toDoSheet, string PathToFile, fstream& file);
 void SearchWork_Date(ToDoList* toDoSheet, string PathToFile, int size);
 void SearchWork_Priority(ToDoList* toDoSheet, string PathToFile, int size);
 void SearchWork_Description(ToDoList* toDoSheet, string PathToFile, int size);
 void SearchWork_Title(ToDoList* toDoSheet, string PathToFile, int size);
 ToDoList* SortSheets_Priority(ToDoList* toDoSheet, int size);
 ToDoList* SortSheets_Date(ToDoList* toDoSheet, int size);
 void Swap(ToDoList& x, ToDoList& y);
 void Swap(Dates& x, Dates& y);
 int ReturnInt(int& integer, int size);
 void ReturnDate(int& day, int& month, int& year);

 void GetLocaltime();





 //Вывод содержимого текстового файла
 //2 аргумент - передается путь к файлу
 /*void ShowFile(fstream& file, string PathToFile) {

	file.open(PathToFile, fstream::in);

	if (!file)
	{
		cout << "File could not be opened for reading" << "\n";
		exit(1);
	}
	else
	{
		string str;
		while (!file.eof())
		{
			getline(file, str);
			cout << str << "\n";
		}
	}
 }*/