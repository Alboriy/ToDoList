#include "CallFunc.h"

int main() {
	

	system("color B1"); // ���� ������ � �������
	//������ ��������� �� windows 1251 ��� ������ ���. �� ������� � ����
	SetConsoleCP(1251);
	//������ ��������� �� windows 1251 ��� ������ ���. �� ����� � �������
	SetConsoleOutputCP(1251);
	//��� ���������� ������ ��������� � ��������� ��������� ���� � ������� ANSI

	setlocale(LC_ALL, "RUSSIAN");

	//���������� ������������� ������� ��������� ������ ���
	ToDoList * toDoSheet = 0;

	//�������� ��������
	Action(toDoSheet);

	//����������� ������
	delete[] toDoSheet;

	return 0;
}