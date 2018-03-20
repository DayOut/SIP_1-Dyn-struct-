#pragma once

template <typename LISTTYPE>
class List
{
private:
	template <typename LISTTYPE>
	struct TElem //структура самого элемента списка
	{
		LISTTYPE inf;
		TElem<LISTTYPE> *next;
	};

	TElem<LISTTYPE> *headPtr, *currentPtr; // переменна€ указатель на голову списка
										   //currentPtr - это указатель на текущий элемент, пока класс существует - существует список и этот элемент

public:
	List();
	List(const List& value);
	~List();

	bool isEmpty() const;
	bool operator!() const;

	TElem<LISTTYPE>* findElem(LISTTYPE value);

	void addToBegin	(const LISTTYPE& value);
	void addToEnd	(const LISTTYPE& value);
	void addSorted	(const LISTTYPE& value);

	bool deleteElem	(const LISTTYPE& value);
	void deleteAllElems();
	
	void show();
	void show(TElem<LISTTYPE> *list);

	void Sort();

private:
	void mergeSort (struct TElem<LISTTYPE> **root);
	static TElem<LISTTYPE>* mergeList	(struct TElem<LISTTYPE> *list1, struct TElem<LISTTYPE> *list2);
	void findMid (struct TElem<LISTTYPE> *root, struct TElem<LISTTYPE> **list1, struct TElem<LISTTYPE> **list2);
};


template <typename LISTTYPE>
List<LISTTYPE>::List()
{
	headPtr = NULL;
}

template <typename LISTTYPE>
List<LISTTYPE>::List(const List<LISTTYPE>& value)
{
	//TODO: Construct with class in input data
	headPtr->inf = value;
	headPtr->next = NULL;
}

template <typename LISTTYPE>
List<LISTTYPE>::~List()
{
	if (headPtr)
	{
		while (headPtr) // поэлементно удал€ем все жлементы списка
		{
			TElem<LISTTYPE> *tmp = headPtr;
			headPtr = headPtr->next;
			delete tmp;
		}
	}
}

template <typename LISTTYPE>
bool List<LISTTYPE>::isEmpty() const
{
	return headPtr == 0;
}

template <typename LISTTYPE>
bool List<LISTTYPE>::operator!() const
{
	return (headPtr != NULL);
}

template<typename LISTTYPE>
typename List<LISTTYPE>::TElem<LISTTYPE>* List<LISTTYPE>::findElem(LISTTYPE value)
{
	currentPtr = headPtr;
	for (; currentPtr; currentPtr = currentPtr->next)
	{
		if (currentPtr->inf == value)
		{
			std::wcout << L"\nЁлемент " << value << L" есть в списке \n";
			return currentPtr;
		}
	}
	std::wcout << L"\nЁлемента " << value << L" нет в списке \n";
	return 0;
}

template <typename LISTTYPE>
void List<LISTTYPE>::addToBegin(const LISTTYPE& value)
{
	TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // выдел€ем пам€ть на новый элемент
	tmp->inf = value;	// записываем значение 
	tmp->next = headPtr;
	headPtr = tmp;
}

template <typename LISTTYPE>
void List<LISTTYPE>::addToEnd(const LISTTYPE& value) // add_end / ...
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
		TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // выдел€ем пам€ть на новый элемент
		tmp->inf = value;	// записываем значение 
		tmp->next = NULL;
		currentPtr->next = tmp;
	}
}

template<typename LISTTYPE>
void List<LISTTYPE>::addSorted(const LISTTYPE& value)
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
			if (currentPtr->next->inf > value)
			{
				break;
			}
			currentPtr = currentPtr->next;
		}
		TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // выдел€ем пам€ть на новый элемент
		tmp->inf = value;	// записываем значение 
		tmp->next = currentPtr->next;
		currentPtr->next = tmp;
	}
}

template<typename LISTTYPE>
bool List<LISTTYPE>::deleteElem(const LISTTYPE& value)
{
	TElem<LISTTYPE>* tmpPtr = new TElem<LISTTYPE>;
	bool findFlag = false;

	currentPtr = headPtr;

	if (headPtr->inf == value)
	{
		tmpPtr = headPtr;
		headPtr = headPtr->next;
		delete tmpPtr;
		findFlag = true;
	}
	else
	{
		while (currentPtr->next)
		{
			if (currentPtr->next->inf == value)
			{
				findFlag = true;
				break;
			}
			else
			{
				currentPtr = currentPtr->next;
			}
		}
		if (findFlag)
		{
			tmpPtr = currentPtr->next;
			currentPtr->next = tmpPtr->next;
			delete tmpPtr;
		}
	}

	if (!findFlag)
	{
		std::wcout << L"Elem was not found... \n";
	}
	return findFlag;
}

template<typename LISTTYPE>
void List<LISTTYPE>::deleteAllElems() 
{
	currentPtr = headPtr;

	while (headPtr)
	{
		currentPtr = headPtr;
		headPtr = headPtr->next;
		delete currentPtr;
	}
	std::wcout << L"All elems deleted!\n";
	currentPtr = NULL;
}

template<typename LISTTYPE>
void List<LISTTYPE>::show()
{
	if (COUNT > 100) return;
	if(headPtr)
	{	
		currentPtr = headPtr;
		while (currentPtr)
		{
			std::cout << currentPtr->inf << "\t";
			currentPtr = currentPtr->next; // доходим до конца списка
		}
		std::cout << std::endl;
	}
	else
	{
		std::wcout << "List is empty!";
	}
}

template<typename LISTTYPE>
void List<LISTTYPE>::show(TElem<LISTTYPE> *list)
{
	if (headPtr)
	{
		TElem<LISTTYPE> *tmp = list;
		for (; tmp; tmp = tmp->next)
			cout << tmp->inf << " ";
		cout << endl;
	}
	else
	{
		std::wcout << "List is empty!";
	}
}

template <typename LISTTYPE>
void List<LISTTYPE>::Sort()
{
	mergeSort(&headPtr);
}

template <typename LISTTYPE>
void List<LISTTYPE>::mergeSort(struct TElem<LISTTYPE> **root)
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

template<typename LISTTYPE>
typename List<LISTTYPE>::TElem<LISTTYPE>* List<LISTTYPE>::mergeList(struct TElem<LISTTYPE> *list1, struct TElem<LISTTYPE> *list2)
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
void List<LISTTYPE>::findMid(struct TElem<LISTTYPE> *root, struct TElem<LISTTYPE> **list1, struct TElem<LISTTYPE> **list2)
{
	/**
	* ¬озвращает указатель на элемент структуры TElem<LISTTYPE> р€дом с серединой списка
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
		два курсора, fast движетс€ в 2 раза быстрее slow, на одну итерацию slow происходит 2 итерации fast
		за счет этого находитс€ середина списка (когда fast == NULL, slow будет ровно в центре списка)
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




