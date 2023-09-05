#include "LinkedList.h"
#include "LinkedList.cpp"
#include <iostream>

using namespace std;
	

int main() {
	setlocale(LC_ALL, "rus");
	menu();
	return 0;
}

int failure() {
	int a;
	while (!(cin >> a) || (cin.peek() != '\n'))
	{
		// достигнут ли конец и введено ли больше одного "слова"
		cin.clear();
		while (cin.get() != '\n');
		cout << "\nОшибка ввода. Попробуйте снова.\n" << endl;
	}
	return a;
}

void menu() {
	int choice, choice2;
	int data;
	int rel_elem;
	int command{};
	int outerListNum;
	int nwListNum;
	OuterNode* relativeList;
	OuterNode* listToDelete;
	OuterNode* outerHead = new OuterNode;
	OuterNode* resList;
	OuterNode* relativeNode;
	InnerNode* result;
	outerHead->firstInnerNode = NULL;
	outerHead->nextOuterNode = NULL;
	while (true) {
		cout << "\nВыберите команду из списка:\n";
		cout << "1. Добавить подсписок в список\n";
		cout << "2. Добавить элемент в конкретный подсписок\n";
		cout << "3. Удалить конкретный подсписок\n";
		cout << "4. Удалить элемент из конкретного подсписка\n";
		cout << "5. Удалить элемент из любого подсписка\n";
		cout << "6. Вывести весь список\n";
		cout << "7. Найти элемент в списке\n";
		cout << "0. Завершить работу программы\n";
		cout << "Номер команды: ";
		command = failure();
		switch (command) {
		case 0:
			clearList(outerHead);
			return;
			break;
		case 1:
			if (isOuterEmpty(outerHead))
			{
				addList(outerHead);
			}
			else {
				cout << "Выберите подсписок, рядом с которым будет добавлен новый подсписок" << endl;
				nwListNum = chooseList(outerHead);
				relativeNode = findList(outerHead, nwListNum);
				if (relativeNode)
				{
					cout << "Введите способ добавления:\n0. Вставить перед элементом\n1. Вставить после элемента" << endl;
					cin >> choice2;
					if (choice2 == 1)
					{
						insertListAfter(relativeNode);
					}
					else if (choice2 == 0)
					{
						insertListBefore(outerHead, relativeNode);
					}
				}
				else
				{
					cout << "Такого подсписка не существует" << endl;
				}
			}
			break;
		case 2:
			cout << "Введите элемент, который хотите добавить" << endl;
			cin >> data;
			if (isOuterEmpty(outerHead))
			{
				addList(outerHead);
				addElement(outerHead, data);
			}
			else
			{
				cout << "Выберите список, в который вы хотите добавить этот элемент" << endl;
				outerListNum = chooseList(outerHead);
				relativeList = findList(outerHead, outerListNum);
				if (relativeList)
				{
					if (isInnerEmty(relativeList))
					{
						addElement(relativeList, data);
					}
					else
					{
						cout << "Введите элемент, рядом с которым будет добавлен новый элемент" << endl;
						cin >> rel_elem;
						InnerNode* relativeElement = findElementInParticularList(relativeList, rel_elem);
						if (relativeElement)
						{
							cout << "Введите способ добавления:\n0. Вставить перед элементом\n1. Вставить после элемента" << endl;
							cin >> choice2;
							if (choice2 == 1)
							{
								insertElementAfter(relativeElement, data);
							}
							else if (choice2 == 0)
							{
								insertElementBefore(relativeList, relativeElement, data);
							}
						}
						else
						{
							cout << "Такого подсписка не существует" << endl;
						}
					}

				}
				else
				{
					cout << "Такого подсписка не существует" << endl;
				}
			}
			break;
		case 3:
			cout << "Выберите подсписок, который хотите удалить" << endl;
			outerListNum = chooseList(outerHead);
			listToDelete = findList(outerHead, outerListNum);
			if (listToDelete != NULL)
			{
				deleteList(outerHead, listToDelete);
			}
			else
			{
				cout << "Такого подсписка не существует" << endl;
			}
			break;
		case 4:
			cout << "Выберите подсписок, из которого вы хотите удалить элемент" << endl;
			outerListNum = chooseList(outerHead);
			resList = findList(outerHead, outerListNum);
			if (resList != NULL)
			{
				cout << "Введите элемент, который вы хотите удалить" << endl;
				cin >> data;
				deleteElementFromParticularList(resList, data);
			}
			else
			{
				cout << "Такого подсписка не существует" << endl;
			}
			break;
		case 5:
			cout << "Введите элемент, который вы хотите удалить из списка" << endl;
			cin >> data;
			if (findElement(outerHead, data))
			{
				deleteElement(outerHead, data);
			}
			else
			{
				cout << "Такого элемента в списке нет" << endl;
			}
			break;
		case 6:
			printList(outerHead);
			break;
		case 7:
			cout << "Введите элемент, который хотите найти" << endl;
			cin >> data;
			result = findElement(outerHead, data);
			if (result != NULL)
			{
				cout << "Элемент есть в списке" << endl;
			}
			else
			{
				cout << "Этого элемента нет в списке" << endl;
			}
			break;
		default:
			cout << "\nТакой команды нет, введите другое число" << endl;
			break;
		}
	}
}

