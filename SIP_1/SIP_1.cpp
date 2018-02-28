/*
	Класс для реализации работы с однонаправленным списком, которая хранит список студентов группы.
*/


#include "stdafx.h"
#include <iostream>
#include <ctime>


template <class T>
class List 
{
private:
	struct TElem //структура самого элемента списка
	{
		T Inf; 
		TElem *Next;
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
		head->Inf = value;
		head->Next = NULL;
	}


	void addToBegin(T value) // add_to_begin / add_begin 
	{
		if(!head) // если список отсутствует ()
		{
			head = new TElem;	// Выделяем память под новый элемент
			head->Inf = value;	// записываем значение 
			head->Next = NULL;	// указатель на последний элемент
		}
		else
		{
			TElem *tmp = new TElem; // выделяем память на новый элемент
			tmp->Inf = value;	// записываем значение 
			tmp->Next = head;	
			head = tmp;
		}
	}

	//для кольцевого списка
	/*addToBegin(T value) // add_to_begin / add_begin 
	{
		if(!head) // если список отсутствует ()
		{
			head = new TElem;	// Выделяем память под новый элемент
			head->Inf = value;	// записываем значение 
			head->Next = head;	// указатель на последний элемент
		}
		else
		{
			TElem *tmp = new TElem; // выделяем память на новый элемент
			while (elem->Next != head) // переходим в конец списка
			{
				elem = elem->Next; // доходим до конца списка
			}
			tmp->Inf = value;	// записываем значение 
			tmp->Next = head;	// указатель с первого элемента на второй
			head = tmp;			// меняем голову на новый элемент
			elem->Next = head;	// меняем указатель на начало списка
		}
	}
	*/


	//функция добавления элемента в конец списка
	bool addToEnd(T value) // add_end / ...
	{
		if(!head) // если список отсутствует ()
		{
			head = new TElem;	// Выделяем память под новый элемент
			head->Inf = value;	// записываем значение 
			head->Next = NULL;	// указатель на последний элемент
			//head->Next = head;	// указатель на последний элемент
		}
		else
		{
			elem = head;
			while(elem->Next)
			//while (elem->Next != head) // в случае кольцевого списка проверяем есть ли данный элемент последним
			{
				elem = elem->Next; // доходим до конца списка
			}
			TElem *tmp = new TElem; // выделяем память на новый элемент
			tmp->Inf = value;	// записываем значение 
			tmp->Next = NULL;	
			//tmp->Next = head;	// для кольцевого списка
			elem->Next = tmp;
		}
		
		return true;
	}

	void show()
	{
		elem = head;
		while(elem)
		//while (elem != head || head->Next != head) // в случае кольцевого списка проверяем есть ли данный элемент последним
		{
			cout << elem->Inf << "\t";
			elem = elem->Next; // доходим до конца списка
		}
	}

	~List() //Этот деструктор подойдет, по идее, для всех типов списков (двунаправленные/кольцевые/однонаправленные)
	{
		if(head)
		{	
			while (head->Next) // поэлементно удаляем все жлементы списка
			{
				TElem *tmp = head;
				head = head->Next;
				delete tmp;
			}
			//далее есть небольшие сомнения в правильности
			// тут у нас остается последний элемент
			delete [] head; // удаляем его

		}
	}


};
/*
 card* delete_spisok(card * car)
{
	card *p=car;
    while (p->next)
	{
		card *tmp;
		tmp = p;
		p = p->next;
		delete tmp;
	}
	p=p->next;
	delete []p;
	car=NULL;
	cout << endl;
	return car;
}*/
 /*
	28-02-18:
		- доделал деструктор
 
 */

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	srand( time(0) );

	List<int> student_test; 
	int tmp = 0;
	for(int i=0; i<8; i++)
	{
		student_test.addToEnd(i);
	}
	student_test.show();

	tmp = rand()%100;
	cout << endl << "Add to end " << tmp << endl;
	student_test.addToEnd(tmp);
	student_test.show();
	cout << endl;

	tmp = rand()%100;
	cout << endl << "Add to end " << tmp << endl;
	student_test.addToBegin(tmp);
	student_test.show();
	

	

	cout << endl;
	system("pause");
	return 0;
}

/*
List::~List() //Деструктор вынесен за класс
{
    while (Head!=NULL)  //Пока по адресу не пусто 
     {    
        element *temp=Head->Next; //Временная переменная для хранения адреса следующего элемента
        delete Head; //Освобождаем адрес обозначающий начало
        Head=temp; //Меняем адрес на следующий
     }
}
*/