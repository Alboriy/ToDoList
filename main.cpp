#include "CallFunc.h"

int main() {
	

	system("color B1"); // цвет текста в консоли
	//Меняет кодировку на windows 1251 при выводе инф. из консоли в файл
	SetConsoleCP(1251);
	//Меняет кодировку на windows 1251 при выводе инф. из файла в консоль
	SetConsoleOutputCP(1251);
	//Для корректной работы программы с кирилицей сохраните файл в формате ANSI

	setlocale(LC_ALL, "RUSSIAN");

	//Объявление динамического массива структуры Списка дел
	ToDoList * toDoSheet = 0;

	//Основные действия
	Action(toDoSheet);

	//Освобождить память
	delete[] toDoSheet;

	return 0;
}