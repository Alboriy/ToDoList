#pragma once
#include "CallFunc.h"

//���������� ���������� ������ �������� � ����
int stateMenu;

//�������� ���� ��� ������ �� ������������
void Menu() {
	cout << ("�opyright Alboriy Gafurov") << "\n\n";
	cout << "�������� ��������: " << endl
		<< "(1) ���� �������" << endl
		<< "(2) ����� �������" << endl
		<< "(3) ���������" << endl
		<< "(4) �������� �������" << endl
		<< "(5) ����� �������" << endl
		<< "(0) ����� �� ���������" << endl
		<< "��� �����: ";
	cin >> stateMenu;
	ReturnInt(stateMenu, 5);
}

//���� ��� �������� ����������� �������
void ShowMenu() {
	cout << "�������� ��������: " << endl
		<< "(1) ������� ��� �������" << endl
		<< "(2) ���������� ������� �� ����" << endl
		<< "(3) ���������� ������� �� �����" << endl
		<< "(4) ���������� ������� �� ���" << endl
		<< "(0) ����� � ������� ����" << endl
		<< "��� �����: ";
	cin >> stateMenu;
	ReturnInt(stateMenu, 4);
}

//���� ��� ������ ������ ������
void SearchMenu() {
	cout << "����� ����� ��� ��������������: " << endl
		<< "(1) �� ��������" << endl
		<< "(2) �� ��������" << endl
		<< "(3) �� ����������" << endl
		<< "(4) �� ����" << endl
		<< "(0) ����� � ������� ����" << endl
		<< "��� �����: ";
	cin >> stateMenu;
	ReturnInt(stateMenu, 4);
}

//����� ������ ����������
void SortMenu() {
	cout << "����� ����� ���������� ��� ��������������: " << endl
		<< "(1) �� ����������" << endl
		<< "(2) �� ����" << endl
		<< "(3) �� �����������" << endl
		<< "(0) ����� �� ����" << endl
		<< "��� �����: ";
	cin >> stateMenu;
	ReturnInt(stateMenu, 3);
}

//�������� ������ ������� �������� �� �����, ������ ������� ������� ����� 4(� ������������ ������ ������� � �����)
int GetArraySize(int& size, string PathToFile, fstream& file) {

	size = 0;
	file.close();
	file.open(PathToFile, fstream::in);

	string str;
	while (!file.eof())
	{
		getline(file, str);
		size++;
		if (str == "") break;
	}
	size = (size - 1) / 4;
	file.close();

	return size;
}

//������� ������ ������ �� ����� � ���������� � ������ ��������
ToDoList* GetStructFromFile(ToDoList* toDoSheet, int size, string PathToFile, fstream& file) {

	//file.close();
	file.open(PathToFile, fstream::in);

	if (file) {

		toDoSheet = new ToDoList[size];

		for (int i = 0; i < size; i++)
		{
			string str;
			getline(file, str);
			toDoSheet[i].Title = str;

			getline(file, str);
			toDoSheet[i].Description = str;

			getline(file, str);
			int res = stoi(str);
			toDoSheet[i].Priority = res;

			getline(file, str, ' ');
			int dd = stoi(str);
			toDoSheet[i].Date.Day = dd;

			getline(file, str, ' ');
			int mm = stoi(str);
			toDoSheet[i].Date.Month = mm;

			getline(file, str);
			int yy = stoi(str);
			toDoSheet[i].Date.Year = yy;

		}
	}
	else {
		cout << "������ �������� �����!" << endl;
	}
	file.close();

	return toDoSheet;
}

//�������� ��������� ����� �� �� ������������
void GetLocaltime() {
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);                         // ������� ����, ���������� � ��������
	timeinfo = localtime(&rawtime);        // ������� ����, �������������� � ���������� �����
	std::cout << "������� ����/����� : " << asctime(timeinfo);
}

// ������� ������������ ������� ��������
void Swap(Dates& x, Dates& y)
{
	Dates temp = x;
	x = y;
	y = temp;
}

// ������� ������������ ������� ��������
void Swap(ToDoList& x, ToDoList& y) {
	ToDoList temp = x;
	x = y;
	y = temp;
}

//������� ���������� ��������������� �� ���� ������
ToDoList* SortSheets_Date(ToDoList* toDoSheet, int size) {
	//��������� ����������� ����������
	for (int i = 0; i < size - 1; i++)
	{

		for (int g = i + 1; g < size; g++)
		{
			if (toDoSheet[i].Date.Year > toDoSheet[g].Date.Year ||
				toDoSheet[i].Date.Year == toDoSheet[g].Date.Year &&
				toDoSheet[i].Date.Month > toDoSheet[g].Date.Month ||
				toDoSheet[i].Date.Year == toDoSheet[g].Date.Year &&
				toDoSheet[i].Date.Month == toDoSheet[g].Date.Month &&
				toDoSheet[i].Date.Day > toDoSheet[g].Date.Day)
			{
				swap(toDoSheet[i], toDoSheet[g]);
			}
		}
	}
	return toDoSheet;
}

//������� ���������� ��������������� �� ���������� ������
ToDoList* SortSheets_Priority(ToDoList* toDoSheet, int size) {
	//��������� ����������� ����������
	for (int i = 0; i < size - 1; i++)
	{

		for (int g = i + 1; g < size; g++)
		{
			if (toDoSheet[i].Priority > toDoSheet[g].Priority)
			{
				swap(toDoSheet[i], toDoSheet[g]);
			}
		}
	}
	return toDoSheet;
}

//�������� ������� ���������� � ����������� ������
//flag (true) - ����� ����� ������� ��������
//flag (false) - ����� ������ �������� � ������� ��������
void show(ToDoList* toDoSheet, int size, bool flag) {
	if (flag)
	{
		for (int i = 0; i < size; i++)
		{
			cout << "----- * ----- * ----- * -----" << endl;
			cout << "������ �: " << i + 1 << endl;
			cout << "�����: ";
			cout << toDoSheet[i].Title << endl;
			cout << "�������� ������: ";
			cout << toDoSheet[i].Description << endl;
			cout << "���������: ";
			cout << toDoSheet[i].Priority << endl;
			cout << "����: ";
			cout << toDoSheet[i].Date.Day << ".";
			cout << toDoSheet[i].Date.Month << ".";
			cout << toDoSheet[i].Date.Year << endl;
			cout << "\n";
		}
		cout << "\n\n";
	}
	else {
		cout << "----- * ----- * ----- * -----" << endl;
		cout << "�����: ";
		cout << toDoSheet[size].Title << endl;
		cout << "�������� ������: ";
		cout << toDoSheet[size].Description << endl;
		cout << "���������: ";
		cout << toDoSheet[size].Priority << endl;
		cout << "����: ";
		cout << toDoSheet[size].Date.Day << ".";
		cout << toDoSheet[size].Date.Month << ".";
		cout << toDoSheet[size].Date.Year << endl;
		cout << "\n";
	}
}

//�������� ��� ������� �� ������������ �����
void ShowAllInFile(fstream& file, string PathToFile, ToDoList* toDoSheet,int size) {
	
	SortMenu();
	while (stateMenu > 0)
	{
		switch (stateMenu)
		{
		case 1:
			system("cls");//������� �������
			cin.get();

			//������������� ������� �� ����������
			toDoSheet = SortSheets_Priority(toDoSheet, size);
			show(toDoSheet, size, true);

			system("pause");
			system("cls");
			SortMenu();
			break;
		case 2:
			system("cls");//������� �������
			cin.get();

			//������������� ������� �� ����
			toDoSheet = SortSheets_Date(toDoSheet, size);
			show(toDoSheet, size, true);

			system("pause");
			system("cls");
			SortMenu();
			break;
		case 3:
			system("cls");//������� �������
			cin.get();

			//�� ���������, ������ ���������� ��� ����
			show(toDoSheet, size,true);

			system("pause");
			system("cls");
			SortMenu();
			break;
		default:
			break;
		}
	}

}

//���������� ������ � ���� ��� ���������� �����
//���� flag - false  ����� �������������� ���� ���� ��������
void SaveInFile(string filename, ToDoList* sheet, int amount, bool flag) {

	if (flag) {
		ofstream os(filename, ios_base::app); // ���� ��� �����

		if (!os)
		{
			cout << "Cannot open the file to input. \n";
			return;
		}
		else {
			os << sheet[amount].Title << "\n";
			os << sheet[amount].Description << "\n";
			os << sheet[amount].Priority << "\n";
			os << sheet[amount].Date.Day << " " << sheet[amount].Date.Month << " " << sheet[amount].Date.Year << "\n";
		}

		os.close();
	}
	else {
		ofstream os(filename); // ���� ��� �����

		if (!os)
		{
			cout << "Cannot open the file to input. \n";
			return;
		}
		else {
			for (int i = 0; i < amount; i++)
			{
				os << sheet[i].Title << "\n";
				os << sheet[i].Description << "\n";
				os << sheet[i].Priority << "\n";
				os << sheet[i].Date.Day << " " << sheet[i].Date.Month << " " << sheet[i].Date.Year << "\n";
			}
		}
		os.close();
	}

}

//������������� ������� ������� ��������� ��� ���������� � ����
ToDoList* InitStruct(ToDoList* sheet, int amount) {

	if (amount == 0)
	{
		sheet = new ToDoList[amount + 1]; // ��������� ������ ��� ������ ���������
	}
	else
	{
		ToDoList* tempObj = new ToDoList[amount + 1];

		for (int i = 0; i < amount; i++)
		{
			tempObj[i] = sheet[i]; // �������� �� ��������� ������
		}
		delete[] sheet;

		sheet = tempObj;
	}
	return sheet;

}

//������� ������ ������������ �� ���������� �����
void SaveArrayInFile(ToDoList* sheet, string PathToFile, int size, bool flag) {
	int action = 0;
	cout << "������ ��������� �������?: (1 - �� | 0 - ���) ";
	cin >> action;
	ReturnInt(action, 1);

	switch (action)
	{
	case 1:
		system("cls");
		//�������� boolean false - �������� ���������� �����
		SaveInFile(PathToFile, sheet, size, flag);
		break;
	case 0:
		system("cls");
		cout << "��������� ������ (�������� �� ����� �������)!" << endl;
		break;
	default:
		break;
	}
}

//���������� ��������� (ver 1.0)
void FillSheets(ToDoList* sheet, const int amount, string filename, bool flag) {

	if (flag) {
		cout << "������� �������� �������: ";
		getline(cin, sheet[amount].Title);

		cout << "������� ����� �������: ";
		getline(cin, sheet[amount].Description);

		cout << "������� ���������: ";
		cin >> sheet[amount].Priority;
		ReturnInt(sheet[amount].Priority, 10);

		cout << "������� ����: ";
		cin.get();
		cin >> sheet[amount].Date.Day;
		cin.get();
		cin >> sheet[amount].Date.Month;
		cin.get();
		cin >> sheet[amount].Date.Year;

		ReturnDate(sheet[amount].Date.Day, sheet[amount].Date.Month, sheet[amount].Date.Year);


		cout << "\n\n";

		//��������� ������ � ���� (������� ���� ������ � ������ ���������)
		////�������� boolean true - �������� ���������� � ����
		SaveInFile(filename, sheet, amount, true);
	}
	else {
		cout << "������� �������� �������: ";
		getline(cin, sheet[amount].Title);

		cout << "������� ����� �������: ";
		getline(cin, sheet[amount].Description);

		cout << "������� ���������: ";
		cin >> sheet[amount].Priority;
		ReturnInt(sheet[amount].Priority, 10);

		cout << "������� ����: ";
		cin >> sheet[amount].Date.Day;
		cin >> sheet[amount].Date.Month;
		cin >> sheet[amount].Date.Year;

		ReturnDate(sheet[amount].Date.Day, sheet[amount].Date.Month, sheet[amount].Date.Year);

		cout << "\n\n";
	}

}

//�������� ������� � ����
void AddSheet(fstream& file, ToDoList* toDoSheet, int amount, string PathToFile, int YesOrNot) {

	do {
		toDoSheet = InitStruct(toDoSheet, amount);//�������� ������ ��� ��������� � �������
		FillSheets(toDoSheet, amount, PathToFile, true);//��������� ��������� -  �������� true ��� ������ � ���������� � ���� - false ������ ��� ������
		amount++;
		cout << "���������� ���� ������ ? (1 - �� | 0 - ���)" << "\n";
		cin >> YesOrNot;
		ReturnInt(YesOrNot, 1);
		cin.get();
		file.close();
	} while (YesOrNot != 0);

}

//�������� �����
void RemoveFile(string PathToFile) {

	if (remove(PathToFile.c_str()) != 0)
		perror("������ ��� �������� �����!");
	else
		puts("���� ������� ������ -_-");

}

//�������� ������� � �����
void DeleteWork(ToDoList* toDoSheet, string PathToFile, int size, fstream& file) {
	//���������� ������ �������
	size = GetArraySize(size, PathToFile, file);

	if (size <= 0) {
		cout << ("���� ���������� ��� �� �������� ������") << "\n\n";
	}
	else {
		//�������� ������ ������� �� �����
		toDoSheet = GetStructFromFile(toDoSheet, size, PathToFile, file);
		//���������� ���� ������ �������� � �������
		show(toDoSheet, size, true);

		int action;
		cout << "�� ������ ������� ���� ����? (1 - �� | 0 - ���): ";
		cin >> action;
		ReturnInt(action, 1);

		if (action == 1) {
			RemoveFile(PathToFile);
			cout << "\n\n";
		}
		else {
			//����� ������ ������� � ��������
			action = 0;
			cout << "\n\n";
			cout << "����� ������� �� ������ �������?: ";
			cin >> action;
			ReturnInt(action, size);

			//��������� ����������� ��������� ������������� ������� 
			//� ���� ����������� ������� �� ����������� ������
			action > 0 ? action -= 1 : action = 0;

			int newSize = size - 1;

			ToDoList* deletedSheet = new ToDoList[newSize];

			//������� ������������� ������ ������ -- �������
			if (action <= newSize) {
				//���� �������� ��������� ������� � ������ ��������
				//���� ���������� ������ �� �������� ������� � �����
				for (int i = 0, k = 0; i <= newSize; i++, k++)
				{
					if (i < action) {
						deletedSheet[k].Title = toDoSheet[i].Title;
						deletedSheet[k].Description = toDoSheet[i].Description;
						deletedSheet[k].Priority = toDoSheet[i].Priority;
						deletedSheet[k].Date.Day = toDoSheet[i].Date.Day;
						deletedSheet[k].Date.Month = toDoSheet[i].Date.Month;
						deletedSheet[k].Date.Year = toDoSheet[i].Date.Year;
					}
					else if (i == action) {
						//��������� ����������� ������ ������ � ������ ������ �����
						if (i == newSize) {
							continue;
						}
						else { i += 1; }

						deletedSheet[k].Title = toDoSheet[i].Title;
						deletedSheet[k].Description = toDoSheet[i].Description;
						deletedSheet[k].Priority = toDoSheet[i].Priority;
						deletedSheet[k].Date.Day = toDoSheet[i].Date.Day;
						deletedSheet[k].Date.Month = toDoSheet[i].Date.Month;
						deletedSheet[k].Date.Year = toDoSheet[i].Date.Year;

					}
					else if (i > action) {
						deletedSheet[k].Title = toDoSheet[i].Title;
						deletedSheet[k].Description = toDoSheet[i].Description;
						deletedSheet[k].Priority = toDoSheet[i].Priority;
						deletedSheet[k].Date.Day = toDoSheet[i].Date.Day;
						deletedSheet[k].Date.Month = toDoSheet[i].Date.Month;
						deletedSheet[k].Date.Year = toDoSheet[i].Date.Year;
					}
				}
				show(deletedSheet, size - 1, true);
			}
			else {
				cout << "����� ������������ ��������!" << "\n\n";
			}
			file.close();
			SaveArrayInFile(deletedSheet, PathToFile, newSize, false);
			delete[] deletedSheet;
		}
	}
}

//�������������� �������
void ReductWork(ToDoList* toDoSheet, string PathToFile, fstream& file) {

	//���������� ������ �������
	int size = GetArraySize(size, PathToFile, file);

	if (size <= 0) {
		cout << ("���� ���������� ��� �� �������� ������") << "\n\n";
	}
	else {
		//�������� ������ ������� �� �����
		toDoSheet = GetStructFromFile(toDoSheet, size, PathToFile, file);
		//���������� ���� ������ �������� � �������
		show(toDoSheet, size, true);


		//����� ������ ������� � ��������
		int action;
		cout << "\n\n";
		cout << "����� ������� �� ������ ��������?: ";
		cin >> action;
		cout << "\n\n";

		//��������� ����������� ��������� ������������� ������� 
		//� ���� ����������� ������� �� ����������� ������
		action > 0 ? action -= 1 : action = 0;

		//������� ������������� ������ ������ -- �������
		if (action <= size) {
			cin.get();
			FillSheets(toDoSheet, action, PathToFile, false);
			show(toDoSheet, size, true);
		}
		else {
			cout << "����� ������������ ��������!" << "\n\n";
		}
		file.close();
		SaveArrayInFile(toDoSheet, PathToFile, size, false);
	}
}

//����� ������� �� ��������
void SearchWork_Title(ToDoList* toDoSheet, string PathToFile, int size) {

	string str, search;
	cout << "������� ���������� ��� ���������� ������: ";
	cin >> search;

	for (int i = 0; i < size; i++)
	{
		str = toDoSheet[i].Title;
		size_t found = str.find(search);
		if (found != string::npos)
		{
			//false - ��� ������ �������� � �������� i 
			show(toDoSheet, i, false);
		}
	}

}

//����� ������� �� ��������
void SearchWork_Description(ToDoList* toDoSheet, string PathToFile, int size) {

	string str, search;
	cout << "������� ���������� ��� ���������� ������: ";
	cin >> search;

	for (int i = 0; i < size; i++)
	{
		str = toDoSheet[i].Description;
		size_t found = str.find(search);
		if (found != string::npos)
		{
			//false - ��� ������ �������� � �������� i 
			show(toDoSheet, i, false);
		}
	}

}

//����� ������� �� ����������
void SearchWork_Priority(ToDoList* toDoSheet, string PathToFile, int size) {

	int search = 0;
	cout << "�� ������ ���������� ������� �����?: ";
	cin >> search;

	for (int i = 0; i < size; i++)
	{
		if (search == toDoSheet[i].Priority) {
			//�������� false ��� ����������� �������� �� ������� i
			show(toDoSheet, i, false);
		}
	}

}

//����� ������� �� ����
void SearchWork_Date(ToDoList* toDoSheet, string PathToFile, int size) {

	int day = 0, month = 0, year = 0;
	cout << "�� ����� ���� ������� �����?: ";
	cin >> day >> month >> year;

	for (int i = 0; i < size; i++)
	{
		if (day == toDoSheet[i].Date.Day && month == toDoSheet[i].Date.Month && year == toDoSheet[i].Date.Year) {
			//�������� false ��� ����������� �������� �� ������� i
			show(toDoSheet, i, false);
		}
	}

}

//����� �������
void SearchWork(ToDoList* toDoSheet, string PathToFile, fstream& file) {

	//���������� ������ �������
	int size = GetArraySize(size, PathToFile, file);

	if (size <= 0) {
		cout << ("���� ���������� ��� �� �������� ������") << "\n\n";
		system("pause");
	}
	else {
		//�������� ������ ������� �� �����
		toDoSheet = GetStructFromFile(toDoSheet, size, PathToFile, file);

		SearchMenu();

		while (stateMenu > 0)
		{
			switch (stateMenu)
			{
			case 1:
				system("cls");//������� �������
				cin.get();

				//����� �� �������� �������
				SearchWork_Title(toDoSheet, PathToFile, size);

				system("pause");
				system("cls");
				SearchMenu();
				break;
			case 2:
				system("cls");//������� �������
				cin.get();

				//����� �� ��������
				SearchWork_Description(toDoSheet, PathToFile, size);

				system("pause");
				system("cls");
				SearchMenu();
				break;
			case 3:
				system("cls");//������� �������
				cin.get();

				//����� �� ����������
				SearchWork_Priority(toDoSheet, PathToFile, size);

				system("pause");
				system("cls");
				SearchMenu();
				break;
			case 4:
				system("cls");//������� �������
				cin.get();

				//����� �� ����
				SearchWork_Date(toDoSheet, PathToFile, size);

				system("pause");
				system("cls");
				SearchMenu();
				break;
			default:
				break;
			}
		}
	}
}

//���������� ������� �� ��������� ����
void ShowSheetsToDay(ToDoList* toDoSheet, int size) {

	int search = 0;
	bool flag = false;

	cout << "������� �� ����� ���� �������?: ";
	//���� ����� ��� ������ �� ���
	cin >> search;
	ReturnInt(search, 31);

	for (int i = 0; i < size; i++)
	{
		if (search == toDoSheet[i].Date.Day) {
			flag = true;
			//�������� false ��� ����������� �������� �� ������� i
			show(toDoSheet, i, false);
		}
	}
	if (!flag) {
		cout << "\n";
		cout << "������ ��� ����������� ���!" << "\n\n";
	}
}

//���������� ������� �� ��������� �����
void ShowSheetsToMonth(ToDoList* toDoSheet, int size) {
	int search = 0;
	bool flag = false;
	cout << "������� �� ����� ����� �������?: ";
	//���� ����� ��� ������ �� ������
	cin >> search;
	ReturnInt(search, 12);

	for (int i = 0; i < size; i++)
	{
		if (search == toDoSheet[i].Date.Month) {
			flag = true;
			//�������� false ��� ����������� �������� �� ������� i
			show(toDoSheet, i, false);
		}
	}
	if (!flag) {
		cout << "\n";
		cout << "������ ��� ����������� ���!" << "\n\n";
	}
}

//���������� ������� �� ��������� ���
void ShowSheetsToYear(ToDoList* toDoSheet, int size) {
	int search = 0;
	bool flag = false;
	cout << "������� �� ����� ��� �������?: ";
	//���� ����� ��� ������ �� ����
	cin >> search;
	ReturnInt(search, 9999);

	for (int i = 0; i < size; i++)
	{
		if (search == toDoSheet[i].Date.Year) {
			flag = true;
			//�������� false ��� ����������� �������� �� ������� i
			show(toDoSheet, i, false);
		}
	}
	if (!flag) {
		cout << "\n";
		cout << "������ ��� ����������� ���!" << "\n\n";
	}
}

//����� ������� ����������� ������� (���� ��, ���� � �������)
void CompilationOfShow(fstream& file, string PathToFile, ToDoList* toDoSheet) {

	//���������� ������ �������
	int size = GetArraySize(size, PathToFile, file);

	//�������� - ������� ���� ������ ��� ��� || ���������� �� ���� ������
	if (size <= 0) {
		cout << ("���� ���������� ��� �� �������� ������") << "\n\n";
		system("pause");
	}
	else {

		//�������� ������ ������� �� �����
		toDoSheet = GetStructFromFile(toDoSheet, size, PathToFile, file);
		ShowMenu();

		while (stateMenu > 0)
		{
			switch (stateMenu)
			{
			case 1:
				system("cls");//������� �������
				cin.get();

				//������� ��� ������� �� �����
				ShowAllInFile(file, PathToFile, toDoSheet,size);

				system("cls");
				ShowMenu();
				break;
			case 2:
				system("cls");//������� �������
				cin.get();

				//���������� ������� �� ����
				ShowSheetsToDay(toDoSheet, size);

				system("pause");
				system("cls");
				ShowMenu();
				break;
			case 3:
				system("cls");//������� �������
				cin.get();

				//���������� ������� �� �����
				ShowSheetsToMonth(toDoSheet, size);

				system("pause");
				system("cls");
				ShowMenu();
				break;
			case 4:
				system("cls");//������� �������
				cin.get();

				//���������� ������� �� ���
				ShowSheetsToYear(toDoSheet, size);

				system("pause");
				system("cls");
				ShowMenu();
				break;
			default:
				break;
			}
		}
	}

}

//������� ��������� �� ����� ��������� ����� �����
int ReturnInt(int& integer, int size) {

	while (integer > size || integer < 0)
	{
		cout << "������������ ������ -- ��������� ����: ";
		cin >> integer;
		while (cin.fail()) {
			cout << "������������ ������ -- ��������� ����: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> integer;
		}
	}

	return integer;
}

//������� ��������� �� ����� ��������� ����
void ReturnDate(int& day, int& month, int& year) {

	while (day > 31 || day < 0)
	{
		cout << "������������ ���� -- ��������� ����: ";
		cin >> day;
		while (cin.fail()) {
			cout << "������������ ���� -- ��������� ����: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> day;
		}
	}

	while (month > 12 || month < 0)
	{
		cout << "������������ ����� -- ��������� ����: ";
		cin >> month;
		while (cin.fail()) {
			cout << "������������ ����� -- ��������� ����: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> month;
		}
	}

	while (year > 9999 || year < 0)
	{
		cout << "������������ ��� -- ��������� ����: ";
		cin >> year;
		while (cin.fail()) {
			cout << "������������ ��� -- ��������� ����: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> year;
		}
	}

}

//�������� ������� ��� ������ � ���������� �������
void Action(ToDoList* toDoSheet) {

	//���-�� ��� �� ���������
	int amount = 0;

	//���������� ��������� ����� ������ ��� ���
	int YesOrNot = 0;

	//����������� ����� �����
	string PathToFile = "Sheets.txt";

	//��������� ���� � ������ ������ � ������
	fstream file;
	file.open(PathToFile, fstream::in | fstream::out | fstream::app);

	//������� ���� ��� ������ ��������
	Menu();

	while (stateMenu > 0)
	{
		switch (stateMenu)
		{
		case 1:
			system("cls");//������� �������
			cin.get();

			//���� ������ � ���� (ver 2.0)
			AddSheet(file, toDoSheet, amount, PathToFile, YesOrNot);

			system("pause");
			system("cls");
			Menu();
			break;
		case 2:
			system("cls");//������� �������
			cin.get();

			//����� ����� ����� � �������
			CompilationOfShow(file, PathToFile, toDoSheet);

			system("cls");
			Menu();
			break;
		case 3:
			system("cls");//������� �������
			cin.get();

			//�������� ���������� �����
			ReductWork(toDoSheet, PathToFile, file);

			system("pause");
			system("cls");
			Menu();
			break;
		case 4:
			system("cls");//������� �������
			cin.get();

			//�������� ������� �� �����
			DeleteWork(toDoSheet, PathToFile, amount = 0, file);

			system("pause");
			system("cls");
			Menu();
			break;
		case 5:
			system("cls");//������� �������
			cin.get();

			//����� ������� � �����
			SearchWork(toDoSheet, PathToFile, file);

			system("cls");
			Menu();
			break;
		default:
			break;
		}
	}

}