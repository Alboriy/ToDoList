#pragma once
#include "CallFunc.h"

//Глобальная переменная выбора действия в меню
int stateMenu;

//Основное меню для ряботы со справочником
void Menu() {
	cout << ("©opyright Alboriy Gafurov") << "\n\n";
	cout << "Выберите действие: " << endl
		<< "(1) Ввод заметки" << endl
		<< "(2) Вывод заметок" << endl
		<< "(3) Изменение" << endl
		<< "(4) Удаление заметки" << endl
		<< "(5) Поиск заметки" << endl
		<< "(0) Выход из программы" << endl
		<< "Ваш выбор: ";
	cin >> stateMenu;
	ReturnInt(stateMenu, 5);
}

//Меню для контроля отображения заметок
void ShowMenu() {
	cout << "Выберите действие: " << endl
		<< "(1) Вывести все заметки" << endl
		<< "(2) Отобразить заметки на день" << endl
		<< "(3) Отобразить заметки на месяц" << endl
		<< "(4) Отобразить заметки на год" << endl
		<< "(0) Выход в главное меню" << endl
		<< "Ваш выбор: ";
	cin >> stateMenu;
	ReturnInt(stateMenu, 4);
}

//Меню для выбора метода поиска
void SearchMenu() {
	cout << "Какой поиск вам предпочтителен: " << endl
		<< "(1) По названию" << endl
		<< "(2) По описанию" << endl
		<< "(3) По приоритету" << endl
		<< "(4) По дате" << endl
		<< "(0) Выход в главное меню" << endl
		<< "Ваш выбор: ";
	cin >> stateMenu;
	ReturnInt(stateMenu, 4);
}

//Выбор метода сортировки
void SortMenu() {
	cout << "Какой метод сортировки вам предпочтителен: " << endl
		<< "(1) По приоритету" << endl
		<< "(2) По дате" << endl
		<< "(3) Не сортировать" << endl
		<< "(0) Выход из меню" << endl
		<< "Ваш выбор: ";
	cin >> stateMenu;
	ReturnInt(stateMenu, 3);
}

//Получает размер массива структур из файла, размер каждого элемент равен 4(в соответствии записи заметок в файле)
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

//Потоком читает данные из файла и записывает в массив стурктур
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
		cout << "Ошибка открытия файла!" << endl;
	}
	file.close();

	return toDoSheet;
}

//Получить системное время на ПК пользователя
void GetLocaltime() {
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);                         // текущая дата, выраженная в секундах
	timeinfo = localtime(&rawtime);        // текущая дата, представленная в нормальной форме
	std::cout << "Текущая дата/время : " << asctime(timeinfo);
}

// Функция перестановки местами значений
void Swap(Dates& x, Dates& y)
{
	Dates temp = x;
	x = y;
	y = temp;
}

// Функция перестановки местами значений
void Swap(ToDoList& x, ToDoList& y) {
	ToDoList temp = x;
	x = y;
	y = temp;
}

//Функция возвращает отсортированный по дате массив
ToDoList* SortSheets_Date(ToDoList* toDoSheet, int size) {
	//Выполняем пузырьковую сортировку
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

//Функция возвращает отсортированный по приоритету массив
ToDoList* SortSheets_Priority(ToDoList* toDoSheet, int size) {
	//Выполняем пузырьковую сортировку
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

//Показать заметки хранящиеся в оперативной памяти
//flag (true) - вывод всего массива структур
//flag (false) - вывод одного элемента в массиве структур
void show(ToDoList* toDoSheet, int size, bool flag) {
	if (flag)
	{
		for (int i = 0; i < size; i++)
		{
			cout << "----- * ----- * ----- * -----" << endl;
			cout << "Задача №: " << i + 1 << endl;
			cout << "Титул: ";
			cout << toDoSheet[i].Title << endl;
			cout << "Описание задачи: ";
			cout << toDoSheet[i].Description << endl;
			cout << "Приоритет: ";
			cout << toDoSheet[i].Priority << endl;
			cout << "Дата: ";
			cout << toDoSheet[i].Date.Day << ".";
			cout << toDoSheet[i].Date.Month << ".";
			cout << toDoSheet[i].Date.Year << endl;
			cout << "\n";
		}
		cout << "\n\n";
	}
	else {
		cout << "----- * ----- * ----- * -----" << endl;
		cout << "Титул: ";
		cout << toDoSheet[size].Title << endl;
		cout << "Описание задачи: ";
		cout << toDoSheet[size].Description << endl;
		cout << "Приоритет: ";
		cout << toDoSheet[size].Priority << endl;
		cout << "Дата: ";
		cout << toDoSheet[size].Date.Day << ".";
		cout << toDoSheet[size].Date.Month << ".";
		cout << toDoSheet[size].Date.Year << endl;
		cout << "\n";
	}
}

//Показать все заметки из прочитанного файла
void ShowAllInFile(fstream& file, string PathToFile, ToDoList* toDoSheet,int size) {
	
	SortMenu();
	while (stateMenu > 0)
	{
		switch (stateMenu)
		{
		case 1:
			system("cls");//очистка консоли
			cin.get();

			//Отсортировать заметки по приоритету
			toDoSheet = SortSheets_Priority(toDoSheet, size);
			show(toDoSheet, size, true);

			system("pause");
			system("cls");
			SortMenu();
			break;
		case 2:
			system("cls");//очистка консоли
			cin.get();

			//Отсортировать заметки по дате
			toDoSheet = SortSheets_Date(toDoSheet, size);
			show(toDoSheet, size, true);

			system("pause");
			system("cls");
			SortMenu();
			break;
		case 3:
			system("cls");//очистка консоли
			cin.get();

			//Не сортирует, просто отображает что есть
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

//Добавление данных в файл или перезапись файла
//Если flag - false  тогда перезаписывает лишь одно значение
void SaveInFile(string filename, ToDoList* sheet, int amount, bool flag) {

	if (flag) {
		ofstream os(filename, ios_base::app); // файл для ввода

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
		ofstream os(filename); // файл для ввода

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

//Инициализация размера массива структуры при добавлении в файл
ToDoList* InitStruct(ToDoList* sheet, int amount) {

	if (amount == 0)
	{
		sheet = new ToDoList[amount + 1]; // выделение памяти для первой структуры
	}
	else
	{
		ToDoList* tempObj = new ToDoList[amount + 1];

		for (int i = 0; i < amount; i++)
		{
			tempObj[i] = sheet[i]; // копируем во временный объект
		}
		delete[] sheet;

		sheet = tempObj;
	}
	return sheet;

}

//Функция опроса пользователя на сохранения файла
void SaveArrayInFile(ToDoList* sheet, string PathToFile, int size, bool flag) {
	int action = 0;
	cout << "Хотите сохранить заметки?: (1 - ДА | 0 - НЕТ) ";
	cin >> action;
	ReturnInt(action, 1);

	switch (action)
	{
	case 1:
		system("cls");
		//параметр boolean false - означает перезапись файла
		SaveInFile(PathToFile, sheet, size, flag);
		break;
	case 0:
		system("cls");
		cout << "Продожить работу (кликните по любой клавише)!" << endl;
		break;
	default:
		break;
	}
}

//Заполнение структуры (ver 1.0)
void FillSheets(ToDoList* sheet, const int amount, string filename, bool flag) {

	if (flag) {
		cout << "Введите название заметки: ";
		getline(cin, sheet[amount].Title);

		cout << "Введите текст заметки: ";
		getline(cin, sheet[amount].Description);

		cout << "Введите приоритет: ";
		cin >> sheet[amount].Priority;
		ReturnInt(sheet[amount].Priority, 10);

		cout << "Введите дату: ";
		cin.get();
		cin >> sheet[amount].Date.Day;
		cin.get();
		cin >> sheet[amount].Date.Month;
		cin.get();
		cin >> sheet[amount].Date.Year;

		ReturnDate(sheet[amount].Date.Day, sheet[amount].Date.Month, sheet[amount].Date.Year);


		cout << "\n\n";

		//Сохранить данные в файл (целевой файл указан в первом аргументе)
		////параметр boolean true - означает добавление в файл
		SaveInFile(filename, sheet, amount, true);
	}
	else {
		cout << "Введите название заметки: ";
		getline(cin, sheet[amount].Title);

		cout << "Введите текст заметки: ";
		getline(cin, sheet[amount].Description);

		cout << "Введите приоритет: ";
		cin >> sheet[amount].Priority;
		ReturnInt(sheet[amount].Priority, 10);

		cout << "Введите дату: ";
		cin >> sheet[amount].Date.Day;
		cin >> sheet[amount].Date.Month;
		cin >> sheet[amount].Date.Year;

		ReturnDate(sheet[amount].Date.Day, sheet[amount].Date.Month, sheet[amount].Date.Year);

		cout << "\n\n";
	}

}

//Добавить заметку в файл
void AddSheet(fstream& file, ToDoList* toDoSheet, int amount, string PathToFile, int YesOrNot) {

	do {
		toDoSheet = InitStruct(toDoSheet, amount);//Выделяем память под структуру в массиве
		FillSheets(toDoSheet, amount, PathToFile, true);//Заполняем структуру -  аргумент true для записи и сохранения в файл - false только для записи
		amount++;
		cout << "Продолжить ввод данных ? (1 - Да | 0 - Нет)" << "\n";
		cin >> YesOrNot;
		ReturnInt(YesOrNot, 1);
		cin.get();
		file.close();
	} while (YesOrNot != 0);

}

//Удаление файла
void RemoveFile(string PathToFile) {

	if (remove(PathToFile.c_str()) != 0)
		perror("Ошибка при удалении файла!");
	else
		puts("Файл успешно удален -_-");

}

//Удаление заметок в файле
void DeleteWork(ToDoList* toDoSheet, string PathToFile, int size, fstream& file) {
	//определить размер массива
	size = GetArraySize(size, PathToFile, file);

	if (size <= 0) {
		cout << ("Файл недоступен или не содержит данных") << "\n\n";
	}
	else {
		//Заполить массив данными из файла
		toDoSheet = GetStructFromFile(toDoSheet, size, PathToFile, file);
		//Отобразить весь массив структур в консоли
		show(toDoSheet, size, true);

		int action;
		cout << "Вы хотите удалить весь файл? (1 - ДА | 0 - НЕТ): ";
		cin >> action;
		ReturnInt(action, 1);

		if (action == 1) {
			RemoveFile(PathToFile);
			cout << "\n\n";
		}
		else {
			//Выбор номера заметки к удалению
			action = 0;
			cout << "\n\n";
			cout << "Какую заметку вы хотите удалить?: ";
			cin >> action;
			ReturnInt(action, size);

			//Исключить возможность указывать отрицательные значени 
			//и дать возможность удалять по порядковому номеру
			action > 0 ? action -= 1 : action = 0;

			int newSize = size - 1;

			ToDoList* deletedSheet = new ToDoList[newSize];

			//Условие предотвращает утечку памяти -- затычка
			if (action <= newSize) {
				//цикл удаления указанной заметки в массив структур
				//цикл записывает данные из текущего массива в новый
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
						//Исключить возможность утечки памяти и записи пустых полей
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
				cout << "Ввели недопустимое значение!" << "\n\n";
			}
			file.close();
			SaveArrayInFile(deletedSheet, PathToFile, newSize, false);
			delete[] deletedSheet;
		}
	}
}

//Редактирование заметок
void ReductWork(ToDoList* toDoSheet, string PathToFile, fstream& file) {

	//определить размер массива
	int size = GetArraySize(size, PathToFile, file);

	if (size <= 0) {
		cout << ("Файл недоступен или не содержит данных") << "\n\n";
	}
	else {
		//Заполить массив данными из файла
		toDoSheet = GetStructFromFile(toDoSheet, size, PathToFile, file);
		//Отобразить весь массив структур в консоли
		show(toDoSheet, size, true);


		//Выбор номера заметки к удалению
		int action;
		cout << "\n\n";
		cout << "Какую заметку вы хотите изменить?: ";
		cin >> action;
		cout << "\n\n";

		//Исключить возможность указывать отрицательные значени 
		//и дать возможность удалять по порядковому номеру
		action > 0 ? action -= 1 : action = 0;

		//Условие предотвращает утечку памяти -- затычка
		if (action <= size) {
			cin.get();
			FillSheets(toDoSheet, action, PathToFile, false);
			show(toDoSheet, size, true);
		}
		else {
			cout << "Ввели недопустимое значение!" << "\n\n";
		}
		file.close();
		SaveArrayInFile(toDoSheet, PathToFile, size, false);
	}
}

//Поиск заметок по названию
void SearchWork_Title(ToDoList* toDoSheet, string PathToFile, int size) {

	string str, search;
	cout << "Введите содержание для выполниния поиска: ";
	cin >> search;

	for (int i = 0; i < size; i++)
	{
		str = toDoSheet[i].Title;
		size_t found = str.find(search);
		if (found != string::npos)
		{
			//false - для вывода элемента с индексом i 
			show(toDoSheet, i, false);
		}
	}

}

//Поиск заметок по описанию
void SearchWork_Description(ToDoList* toDoSheet, string PathToFile, int size) {

	string str, search;
	cout << "Введите содержание для выполниния поиска: ";
	cin >> search;

	for (int i = 0; i < size; i++)
	{
		str = toDoSheet[i].Description;
		size_t found = str.find(search);
		if (found != string::npos)
		{
			//false - для вывода элемента с индексом i 
			show(toDoSheet, i, false);
		}
	}

}

//Поиск заметок по приоритету
void SearchWork_Priority(ToDoList* toDoSheet, string PathToFile, int size) {

	int search = 0;
	cout << "По какому приоритету сделать поиск?: ";
	cin >> search;

	for (int i = 0; i < size; i++)
	{
		if (search == toDoSheet[i].Priority) {
			//аргумент false для отображения элемента по индексу i
			show(toDoSheet, i, false);
		}
	}

}

//Поиск заметок по дате
void SearchWork_Date(ToDoList* toDoSheet, string PathToFile, int size) {

	int day = 0, month = 0, year = 0;
	cout << "По какой дате сделать поиск?: ";
	cin >> day >> month >> year;

	for (int i = 0; i < size; i++)
	{
		if (day == toDoSheet[i].Date.Day && month == toDoSheet[i].Date.Month && year == toDoSheet[i].Date.Year) {
			//аргумент false для отображения элемента по индексу i
			show(toDoSheet, i, false);
		}
	}

}

//Поиск заметок
void SearchWork(ToDoList* toDoSheet, string PathToFile, fstream& file) {

	//определить размер массива
	int size = GetArraySize(size, PathToFile, file);

	if (size <= 0) {
		cout << ("Файл недоступен или не содержит данных") << "\n\n";
		system("pause");
	}
	else {
		//Заполить массив данными из файла
		toDoSheet = GetStructFromFile(toDoSheet, size, PathToFile, file);

		SearchMenu();

		while (stateMenu > 0)
		{
			switch (stateMenu)
			{
			case 1:
				system("cls");//очистка консоли
				cin.get();

				//Поиск по названию заметки
				SearchWork_Title(toDoSheet, PathToFile, size);

				system("pause");
				system("cls");
				SearchMenu();
				break;
			case 2:
				system("cls");//очистка консоли
				cin.get();

				//Поиск по описанию
				SearchWork_Description(toDoSheet, PathToFile, size);

				system("pause");
				system("cls");
				SearchMenu();
				break;
			case 3:
				system("cls");//очистка консоли
				cin.get();

				//Поиск по приоритету
				SearchWork_Priority(toDoSheet, PathToFile, size);

				system("pause");
				system("cls");
				SearchMenu();
				break;
			case 4:
				system("cls");//очистка консоли
				cin.get();

				//Поиск по дате
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

//Показывает заметки на выбранный день
void ShowSheetsToDay(ToDoList* toDoSheet, int size) {

	int search = 0;
	bool flag = false;

	cout << "Заметки на какой день вывести?: ";
	//Ввод числа для поиска по дню
	cin >> search;
	ReturnInt(search, 31);

	for (int i = 0; i < size; i++)
	{
		if (search == toDoSheet[i].Date.Day) {
			flag = true;
			//аргумент false для отображения элемента по индексу i
			show(toDoSheet, i, false);
		}
	}
	if (!flag) {
		cout << "\n";
		cout << "Данных для отображения нет!" << "\n\n";
	}
}

//Показывает заметки на выбранный месяц
void ShowSheetsToMonth(ToDoList* toDoSheet, int size) {
	int search = 0;
	bool flag = false;
	cout << "Заметки на какой месяц вывести?: ";
	//Ввод числа для поиска по месяцу
	cin >> search;
	ReturnInt(search, 12);

	for (int i = 0; i < size; i++)
	{
		if (search == toDoSheet[i].Date.Month) {
			flag = true;
			//аргумент false для отображения элемента по индексу i
			show(toDoSheet, i, false);
		}
	}
	if (!flag) {
		cout << "\n";
		cout << "Данных для отображения нет!" << "\n\n";
	}
}

//Показывает заметки на выбранный год
void ShowSheetsToYear(ToDoList* toDoSheet, int size) {
	int search = 0;
	bool flag = false;
	cout << "Заметки на какой год вывести?: ";
	//Ввод числа для поиска по году
	cin >> search;
	ReturnInt(search, 9999);

	for (int i = 0; i < size; i++)
	{
		if (search == toDoSheet[i].Date.Year) {
			flag = true;
			//аргумент false для отображения элемента по индексу i
			show(toDoSheet, i, false);
		}
	}
	if (!flag) {
		cout << "\n";
		cout << "Данных для отображения нет!" << "\n\n";
	}
}

//Общая функция отображения заметок (хоть всё, хоть с отбором)
void CompilationOfShow(fstream& file, string PathToFile, ToDoList* toDoSheet) {

	//определить размер массива
	int size = GetArraySize(size, PathToFile, file);

	//Проверка - содежит файл данные или нет || существует ли файл вообще
	if (size <= 0) {
		cout << ("Файл недоступен или не содержит данных") << "\n\n";
		system("pause");
	}
	else {

		//Заполить массив данными из файла
		toDoSheet = GetStructFromFile(toDoSheet, size, PathToFile, file);
		ShowMenu();

		while (stateMenu > 0)
		{
			switch (stateMenu)
			{
			case 1:
				system("cls");//очистка консоли
				cin.get();

				//Вывести все заметки из файла
				ShowAllInFile(file, PathToFile, toDoSheet,size);

				system("cls");
				ShowMenu();
				break;
			case 2:
				system("cls");//очистка консоли
				cin.get();

				//Отобразить заметки на день
				ShowSheetsToDay(toDoSheet, size);

				system("pause");
				system("cls");
				ShowMenu();
				break;
			case 3:
				system("cls");//очистка консоли
				cin.get();

				//Отобразить заметки на месяц
				ShowSheetsToMonth(toDoSheet, size);

				system("pause");
				system("cls");
				ShowMenu();
				break;
			case 4:
				system("cls");//очистка консоли
				cin.get();

				//Отобразить заметки на год
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

//Функция проверяет на верно введенное целое число
int ReturnInt(int& integer, int size) {

	while (integer > size || integer < 0)
	{
		cout << "Некоректнные данные -- Повторите ввод: ";
		cin >> integer;
		while (cin.fail()) {
			cout << "Некоректнные данные -- Повторите ввод: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> integer;
		}
	}

	return integer;
}

//Функция проверяет на верно введенную дату
void ReturnDate(int& day, int& month, int& year) {

	while (day > 31 || day < 0)
	{
		cout << "Некоректнный день -- Повторите ввод: ";
		cin >> day;
		while (cin.fail()) {
			cout << "Некоректнные день -- Повторите ввод: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> day;
		}
	}

	while (month > 12 || month < 0)
	{
		cout << "Некоректнный месяц -- Повторите ввод: ";
		cin >> month;
		while (cin.fail()) {
			cout << "Некоректнные месяц -- Повторите ввод: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> month;
		}
	}

	while (year > 9999 || year < 0)
	{
		cout << "Некоректнный год -- Повторите ввод: ";
		cin >> year;
		while (cin.fail()) {
			cout << "Некоректнные год -- Повторите ввод: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> year;
		}
	}

}

//Основная функция для работы с программой заметок
void Action(ToDoList* toDoSheet) {

	//Кол-во дел по умолчанию
	int amount = 0;

	//Продолжать добавлять новые фильмы или нет
	int YesOrNot = 0;

	//Определение имени файла
	string PathToFile = "Sheets.txt";

	//Открываем файл в режиме чтения и записи
	fstream file;
	file.open(PathToFile, fstream::in | fstream::out | fstream::app);

	//Выводим меню для выбора действия
	Menu();

	while (stateMenu > 0)
	{
		switch (stateMenu)
		{
		case 1:
			system("cls");//очистка консоли
			cin.get();

			//Ввод данных в файл (ver 2.0)
			AddSheet(file, toDoSheet, amount, PathToFile, YesOrNot);

			system("pause");
			system("cls");
			Menu();
			break;
		case 2:
			system("cls");//очистка консоли
			cin.get();

			//вывод всего файла в консоль
			CompilationOfShow(file, PathToFile, toDoSheet);

			system("cls");
			Menu();
			break;
		case 3:
			system("cls");//очистка консоли
			cin.get();

			//Изменить содержимое файла
			ReductWork(toDoSheet, PathToFile, file);

			system("pause");
			system("cls");
			Menu();
			break;
		case 4:
			system("cls");//очистка консоли
			cin.get();

			//Удаление заметки из файла
			DeleteWork(toDoSheet, PathToFile, amount = 0, file);

			system("pause");
			system("cls");
			Menu();
			break;
		case 5:
			system("cls");//очистка консоли
			cin.get();

			//Поиск заметки в файле
			SearchWork(toDoSheet, PathToFile, file);

			system("cls");
			Menu();
			break;
		default:
			break;
		}
	}

}