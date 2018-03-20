#pragma once

template <typename LISTTYPE>
class Tlist
{
private:
	template <typename LISTTYPE>
	struct TElem //структура самого элемента списка
	{
		LISTTYPE inf;
		TElem<LISTTYPE> *next;
	};

	TElem<LISTTYPE> *headPtr, *currentPtr; // переменная указатель на голову списка
										   //currentPtr - это указатель на текущий элемент, пока класс существует - существует список и этот элемент

public:
	Tlist();
	Tlist(const Tlist& value);
	~Tlist();

	bool isEmpty() const;
	bool operator!() const;

	void addToBegin(const LISTTYPE& value);
	void addToEnd(LISTTYPE value);
	void addSorted(LISTTYPE value);
	

	void show();
	void show(TElem<LISTTYPE> *list);

	//----------------------------------------------------------------------------------------------------------------------------
	void mergeSort();
	static TElem<LISTTYPE>* mergeList(struct TElem<LISTTYPE> *list1, struct TElem<LISTTYPE> *list2);
	void findMid(struct TElem<LISTTYPE> *root, struct TElem<LISTTYPE> **list1, struct TElem<LISTTYPE> **list2);
	void mergeSort(struct TElem<LISTTYPE> **root);
	//----------------------------------------------------------------------------------------------------------------------------


};


template <typename LISTTYPE>
Tlist<LISTTYPE>::Tlist()
{
	headPtr = NULL;
}

template <typename LISTTYPE>
Tlist<LISTTYPE>::Tlist(const Tlist<LISTTYPE>& value)
{
	//TODO: Construct with class in input data
	headPtr->inf = value;
	headPtr->next = NULL;
}

template <typename LISTTYPE>
Tlist<LISTTYPE>::~Tlist()
{
	if (headPtr)
	{
		while (headPtr) // поэлементно удаляем все жлементы списка
		{
			TElem<LISTTYPE> *tmp = headPtr;
			headPtr = headPtr->next;
			delete tmp;
		}
	}
}

template <typename LISTTYPE>
bool Tlist<LISTTYPE>::isEmpty() const
{
	return headPtr == 0;
}

template <typename LISTTYPE>
bool Tlist<LISTTYPE>::operator!() const
{
	return (headPtr != NULL);
}

template <typename LISTTYPE>
void Tlist<LISTTYPE>::addToBegin(const LISTTYPE& value)
{
	TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // выделяем память на новый элемент
	tmp->inf = value;	// записываем значение 
	tmp->next = headPtr;
	headPtr = tmp;
}

template <typename LISTTYPE>
void Tlist<LISTTYPE>::addToEnd(LISTTYPE value) // add_end / ...
{
	if (isEmpty()) // если список отсутствует ()
	{
		addToBegin(value);
	}
	else
	{
		currentPtr = headPtr;
		while (currentPtr->next)
		{
			currentPtr = currentPtr->next; // доходим до конца списка
		}
		TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // выделяем память на новый элемент
		tmp->inf = value;	// записываем значение 
		tmp->next = NULL;
		currentPtr->next = tmp;
	}
}

template<typename LISTTYPE>
void Tlist<LISTTYPE>::addSorted(LISTTYPE value)
{
	if (isEmpty() || value <= headPtr->inf)
	{
		addToBegin(value);
	}
	else
	{
		currentPtr = headPtr;
		while (currentPtr->next)
		{
			currentPtr = currentPtr->next; // доходим до конца списка
		}
		TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // выделяем память на новый элемент
		tmp->inf = value;	// записываем значение 
		tmp->next = NULL;
		currentPtr->next = tmp;


	}
}

template<typename LISTTYPE>
void Tlist<LISTTYPE>::show()
{
	if (COUNT > 100) return;

	currentPtr = headPtr;
	while (currentPtr)
	{
		std::cout << currentPtr->inf << "\t";
		currentPtr = currentPtr->next; // доходим до конца списка
	}
	std::cout << std::endl;
}

template<typename LISTTYPE>
void Tlist<LISTTYPE>::show(TElem<LISTTYPE> *list)
{
	TElem<LISTTYPE> *tmp = list;
	for (; tmp; tmp = tmp->next)
		cout << tmp->inf << " ";
	cout << endl;
}

template <typename LISTTYPE>
void Tlist<LISTTYPE>::mergeSort()
{
	mergeSort(&headPtr);
}

template<typename LISTTYPE>
typename Tlist<LISTTYPE>::TElem<LISTTYPE>* Tlist<LISTTYPE>::mergeList(struct TElem<LISTTYPE> *list1, struct TElem<LISTTYPE> *list2)
{
	struct TElem<LISTTYPE> tempheadPtr = { 0, NULL }, *tail = &tempheadPtr;

	while ((list1 != NULL) && (list2 != NULL))
	{
		struct TElem<LISTTYPE> **min = (list1->inf < list2->inf) ? &list1 : &list2;
		struct TElem<LISTTYPE> *next = (*min)->next;
		tail = tail->next = *min;
		*min = next;
	}
	tail->next = list1 ? list1 : list2;
	return tempheadPtr.next;
}

template<typename LISTTYPE>
void Tlist<LISTTYPE>::findMid(struct TElem<LISTTYPE> *root, struct TElem<LISTTYPE> **list1, struct TElem<LISTTYPE> **list2)
{
	/**
	* Возвращает указатель на элемент структуры TElem<LISTTYPE> рядом с серединой списка
	* и после обрезаем оригинальный списко перед этим элементом
	*/
	struct TElem<LISTTYPE> *slow, *fast;

	//в случае пустого списка (или один элемент)
	if ((root == NULL) || (root->next == NULL))
	{
		*list1 = root;
		*list2 = NULL;
		return;
	}
	else
	{
		/*
		два курсора, fast движется в 2 раза быстрее slow, на одну итерацию slow происходит 2 итерации fast
		за счет этого находится середина списка (когда fast == NULL, slow будет ровно в центре списка)
		*/
		slow = root;
		fast = root->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}

		*list1 = root;
		*list2 = slow->next;
		slow->next = NULL;
	}
}

template <typename LISTTYPE>
void Tlist<LISTTYPE>::mergeSort(struct TElem<LISTTYPE> **root)
{
	struct TElem<LISTTYPE> *list1, *list2;
	struct TElem<LISTTYPE> *headPtr = *root;
	if ((headPtr == NULL) || (headPtr->next == NULL))
	{
		return;
	}

	findMid(headPtr, &list1, &list2);

	mergeSort(&list1);
	mergeSort(&list2);

	*root = mergeList(list1, list2);

}



