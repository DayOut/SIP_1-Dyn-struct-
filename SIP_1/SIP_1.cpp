/*
	Класс для реализации работы с однонаправленным списком, которая хранит список студентов группы.

	Если что-то не работает - пишите сюда https://t.me/Novarely 
*/


#include "stdafx.h"




template <class T>
class List 
{
private:
	struct TElem //структура самого элемента списка
	{
		T inf; 
		TElem *next;
	};
	
	TElem *head, *elem; // переменная указатель на голову списка
	//elem - это указатель на текущий элемент, пока класс существует - существует список и этот элемент
	

public:
	List() 
	{
		head = NULL;
	}
	
	List(T value)
	{
		head->inf = value;
		head->next = NULL;
	}


	void addToBegin(T value) // add_to_begin / add_begin 
	{
		if(!head) // если список отсутствует ()
		{
			head = new TElem;	// Выделяем память под новый элемент
			head->inf = value;	// записываем значение 
			head->next = NULL;	// указатель на последний элемент
		}
		else
		{
			TElem *tmp = new TElem; // выделяем память на новый элемент
			tmp->inf = value;	// записываем значение 
			tmp->next = head;	
			head = tmp;
		}
	}

	//для кольцевого списка
	/*addToBegin(T value) // add_to_begin / add_begin 
	{
		if(!head) // если список отсутствует ()
		{
			head = new TElem;	// Выделяем память под новый элемент
			head->inf = value;	// записываем значение 
			head->next = head;	// указатель на последний элемент
		}
		else
		{
			TElem *tmp = new TElem; // выделяем память на новый элемент
			while (elem->next != head) // переходим в конец списка
			{
				elem = elem->next; // доходим до конца списка
			}
			tmp->inf = value;	// записываем значение 
			tmp->next = head;	// указатель с первого элемента на второй
			head = tmp;			// меняем голову на новый элемент
			elem->next = head;	// меняем указатель на начало списка
		}
	}
	*/

	//функция добавления элемента в конец списка
	void addToEnd(T value) // add_end / ...
	{
		if(!head) // если список отсутствует ()
		{
			head = new TElem;	// Выделяем память под новый элемент
			head->inf = value;	// записываем значение 
			head->next = NULL;	// указатель на последний элемент
		}
		else
		{
			elem = head;
			while(elem->next)
			{
				elem = elem->next; // доходим до конца списка
			}
			TElem *tmp = new TElem; // выделяем память на новый элемент
			tmp->inf = value;	// записываем значение 
			tmp->next = NULL;	
			elem->next = tmp;
		}
	}

	//функция добавления элемента в конец списка для кольцевого списка
	/*void addToEnd(T value) // add_end / ...
	{
		if (!head) // если список отсутствует ()
		{
			head = new TElem;	// Выделяем память под новый элемент
			head->inf = value;	// записываем значение 
			head->next = head;	// указатель на последний элемент
		}
		else
		{
			elem = head;
			while (elem->next != head) // в случае кольцевого списка проверяем есть ли данный элемент последним
			{
				elem = elem->next; // доходим до конца списка
			}
			TElem *tmp = new TElem; // выделяем память на новый элемент
			tmp->inf = value;	// записываем значение 
			tmp->next = head;	// для кольцевого списка
			elem->next = tmp;
		}
	}*/

	//ф-ция для вывода информационной части жлементов списка (пока используется только для отладки)
	void show()
	{
		elem = head;
		while(elem)
		//while (elem != head || head->next != head) // в случае кольцевого списка проверяем есть ли данный элемент последним
		{
			cout << elem->inf << "\t";
			elem = elem->next; // доходим до конца списка
		}
		cout << endl;
	}

	void sort()
	{
		elem = head;

		TElem *sortedPtr = 0;
		TElem *headSortedPtr = 0;

		for ( ; head; ) 
		{
			TElem *sortedElemPtr = findMin(head);

			if (sortedElemPtr->next == head)
				head = head->next;

			if (!sortedPtr)
			{
				sortedPtr = sortedElemPtr->next;
				sortedElemPtr->next = sortedElemPtr->next->next;
				sortedPtr->next = 0;
				headSortedPtr = sortedPtr;
			}
			else
			{
				sortedPtr->next = sortedElemPtr->next;
				sortedElemPtr->next = sortedElemPtr->next->next;
				sortedPtr = sortedPtr->next;
				sortedPtr->next = 0;
			}
		}

		head = headSortedPtr;
	}

	// returns elem before minimum
	TElem *findMin(TElem *from) 
	{
		TElem *min = new TElem;
		min->inf = 0;
		min->next = head;

		if (from->next)
		{
			for (; from->next; from = from->next)
			{
				if (min->next->inf > from->next->inf)
				{
					min = from;
				}
			}
		}
		else
		{
			return min;
		}
		return min;
	}

	
	//----------------------------------------------------------------------------------------------------------------------------






	/*
		Функция поиска элемента. Поскольку поиск элемента идет по значению, никто не 
		исключает возможность дублирования иноформации, поэтому необходим поиск по 
		всему списку с выводом всех найденых элементов.
		Но для начала поиск будет по принципу "есть ли такой элемент вообще?"
	*/
	TElem search(T value)
	{
		// пока только один элемент искать будем

		// TODO: поиск элемента
	}

	~List()
	{
		if(head)
		{	
			
			while (head->next) // поэлементно удаляем все жлементы списка
			{
				TElem *tmp = head;
				head = head->next;
				delete tmp;
			}
			//далее есть небольшие сомнения в правильности
			// тут у нас остается последний элемент
			delete [] head; // удаляем его

		}
	}

	//для кольцевого списка
	/*
	~List()
	{
		if (head)
		{
			// не совсем уверен, что это правильно, но...
			
			while (head->next) // поэлементно удаляем все жлементы списка
			{
				TElem *tmp = head;
				head = head->next;
				delete tmp;
			}
			//далее есть небольшие сомнения в правильности
			// тут у нас остается последний элемент
			delete[] head; // удаляем его

		}
	}*/
	

};


using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	srand( time(0) );

	List<int> test;
	
	List<int> student_test; 
	int tmp = 0;
	wcout << L"Заполняем массив...\n";
	for(int i=0; i<50000; i++)
	{
		student_test.addToEnd(rand() %100);
	}
	wcout << L"Заполнили массив...\n";
	
	cout << "Сортировка..." << endl; 

	unsigned int start = clock();
	student_test.sort();
	unsigned int end = clock();
	wcout << L"Времени на сортировку: " << end - start << L" мс \n"; 
	

	cout << endl;
	system("pause");
	return 0;
}
