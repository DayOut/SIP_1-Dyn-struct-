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

	TElem<LISTTYPE> *headPtr_, *currentPtr_; // переменна€ указатель на голову списка
										   //currentPtr_ - это указатель на текущий элемент, пока класс существует - существует список и этот элемент
	
public:
	int deep = 0;
	long long comparison = 0;
	List();
	List(const List& value);
	~List();

	bool			isEmpty() const;
	bool			operator!() const;
	List<LISTTYPE>& operator=(List<LISTTYPE>& right);
	List<LISTTYPE>& operator++();

	TElem<LISTTYPE>*	getHeadPtr();
	LISTTYPE&			getCurrInfPtr();
	TElem<LISTTYPE>*	findElem(LISTTYPE value);
	void setCurrToHead();

	void addToBegin	(const LISTTYPE& value);
	void addToBegin	(TElem<LISTTYPE>* value);

	void addToEnd	(const LISTTYPE& value);

	void addSorted	(const LISTTYPE& value);
	void sortCurrElem();

	bool deleteElem	(const LISTTYPE& value);
	void deleteAllElems();
	
	void show();
	void show(TElem<LISTTYPE> *list);

	void sort();
	//bubblesort for check

private:
	void mergeSort (struct TElem<LISTTYPE> **root);
	static TElem<LISTTYPE>* mergeList	(struct TElem<LISTTYPE> *list1, struct TElem<LISTTYPE> *list2);
	void findMid (struct TElem<LISTTYPE> *root, struct TElem<LISTTYPE> **list1, struct TElem<LISTTYPE> **list2);
};


template <typename LISTTYPE>
List<LISTTYPE>::List()
{
	headPtr_ = NULL;
}

template <typename LISTTYPE>
List<LISTTYPE>::List(const List<LISTTYPE>& value)
{
	//TODO: Construct with class in input data
	headPtr_->inf = value;
	headPtr_->next = NULL;
}

template <typename LISTTYPE>
List<LISTTYPE>::~List()
{
	if (headPtr_)
	{
		while (headPtr_) // поэлементно удал€ем все жлементы списка
		{
			TElem<LISTTYPE> *tmp = headPtr_;
			headPtr_ = headPtr_->next;
			delete tmp;
		}
	}
}

template <typename LISTTYPE>
bool List<LISTTYPE>::isEmpty() const
{
	return headPtr_ == 0;
}

template <typename LISTTYPE>
bool List<LISTTYPE>::operator!() const
{
	return (headPtr_ == NULL);
}

template <typename LISTTYPE>
 List<LISTTYPE>& List<LISTTYPE>::operator=(List<LISTTYPE>& right)
{
	if (!right.isEmpty())
	{
		// правый список это тот, из которого нужно присвоить значени€
		TElem<LISTTYPE> *rightHead = right.getHeadPtr(); // получение головы списка из правого
		TElem<LISTTYPE> *rightCurrElem = rightHead; // текущий элемент из этого же списка

		if (this == &right) 
		{
			return *this; // проверка на самоприсваивание
		}

		if (!isEmpty())// если левый список был не пустым 
		{
			deleteAllElems();
		}

		do
		{
			addToEnd(rightCurrElem->inf); // просто добавл€ем в конец левого списка элементы из правого
			rightCurrElem = rightCurrElem->next;
		} while (rightCurrElem != NULL);


	}
	return *this;
}

 template<typename LISTTYPE>
 typename List<LISTTYPE>::TElem<LISTTYPE>* List<LISTTYPE>::getHeadPtr()
 {
	 return headPtr_;
 }

 template <typename LISTTYPE>
 LISTTYPE& List<LISTTYPE>::getCurrInfPtr()
 {
	 if (currentPtr_)
	 {
		 return currentPtr_->inf;
	 }
	 else
	 {
		 currentPtr_ = headPtr_;
		 return currentPtr_->inf;
	 }
	 return nullptr; // i have no idea what happened, that you receive this value
 }

template<typename LISTTYPE>
typename List<LISTTYPE>::TElem<LISTTYPE>* List<LISTTYPE>::findElem(LISTTYPE value)
{
	currentPtr_ = headPtr_;
	for (; currentPtr_; currentPtr_ = currentPtr_->next)
	{
		if (currentPtr_->inf == value)
		{
			std::wcout << L"\nЁлемент \"" << value << L"\" есть в списке \n";
			return currentPtr_;
		}
	}
	std::wcout << L"\nЁлемента \"" << value << L"\" нет в списке \n";
	return 0;
}

template <typename LISTTYPE>
void List<LISTTYPE>::setCurrToHead()
{
	currentPtr_ = headPtr_;
}

template<typename LISTTYPE>
List<LISTTYPE>& List<LISTTYPE>::operator++()
{
	if (currentPtr_)
	{
		currentPtr_ = currentPtr_->Next;
	}
	else
	{
		currentPtr_ = headPtr_;
	}
	return *this;
}

template <typename LISTTYPE>
void List<LISTTYPE>::addToBegin(const LISTTYPE& value)
{
	TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // выдел€ем пам€ть на новый элемент
	tmp->inf = value;	// записываем значение 
	tmp->next = headPtr_;
	headPtr_ = tmp;
}

template <typename LISTTYPE>
void List<LISTTYPE>::addToBegin(TElem<LISTTYPE>* value)
{
	TElem<LISTTYPE> *tmp = value; // выдел€ем пам€ть на новый элемент
	tmp->next = headPtr_;
	headPtr_ = tmp;
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
		currentPtr_ = headPtr_;
		while (currentPtr_->next)
		{
			currentPtr_ = currentPtr_->next; // доходим до конца списка
		}
		TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // выдел€ем пам€ть на новый элемент
		tmp->inf = value;	// записываем значение 
		tmp->next = NULL;
		currentPtr_->next = tmp;
	}
}

template<typename LISTTYPE>
void List<LISTTYPE>::addSorted(const LISTTYPE& value)
{
	if (isEmpty() || value <= headPtr_->inf)
	{
		addToBegin(value);
	}
	else
	{
		currentPtr_ = headPtr_;
		while (currentPtr_->next)
		{
			if (currentPtr_->next->inf > value)
			{
				break;
			}
			currentPtr_ = currentPtr_->next;
		}
		TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // выдел€ем пам€ть на новый элемент
		tmp->inf = value;	// записываем значение 
		tmp->next = currentPtr_->next;
		currentPtr_->next = tmp;
	}
}


template<typename LISTTYPE>
void List<LISTTYPE>::sortCurrElem()
{
	//find an element
	TElem<LISTTYPE>* tmp = 0;
	bool findFlag = false;

	if (headPtr_ == currentPtr_)
	{
		headPtr_ = headPtr_->next;
		findFlag = true;
	}

	for (; !findFlag && currentPtr_; currentPtr_ = currentPtr_->next)
	{
		if (currentPtr_->next && currentPtr_->next->inf == currentPtr_->inf)
		{
			std::wcout << L"\nЁлемент " << currentPtr_->inf << L" есть в списке \n";

			//cut this elem from the list
			tmp = currentPtr_->next;
			currentPtr_->next = tmp->next;

			findFlag = true;
			break;
		}
	}

	if (!findFlag)
	{
		std::wcout << L"Element doesn't not exist! \n";
		return;
	}

	// done, now sort it

	if (isEmpty())
	{
		addToBegin(currentPtr_->inf);
	}
	else
	{
		TElem<LISTTYPE> *tmpCurrentPtr = headPtr_;
		while (tmpCurrentPtr->next)
		{
			if (tmpCurrentPtr->inf < currentPtr_->inf)
			{
				break;
			}
			currentPtr_ = currentPtr_->next;
		}
		currentPtr_->next = tmpCurrentPtr->next;
		tmpCurrentPtr->next = currentPtr_;

	}	
}

template<typename LISTTYPE>
bool List<LISTTYPE>::deleteElem(const LISTTYPE& value)
{
	TElem<LISTTYPE>* tmpPtr = new TElem<LISTTYPE>;
	bool findFlag = false;

	currentPtr_ = headPtr_;

	if (headPtr_->inf == value)
	{
		tmpPtr = headPtr_;
		headPtr_ = headPtr_->next;
		delete tmpPtr;
		findFlag = true;
	}
	else
	{
		while (currentPtr_->next)
		{
			if (currentPtr_->next->inf == value)
			{
				findFlag = true;
				break;
			}
			else
			{
				currentPtr_ = currentPtr_->next;
			}
		}
		if (findFlag)
		{
			tmpPtr = currentPtr_->next;
			currentPtr_->next = tmpPtr->next;
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
	currentPtr_ = headPtr_;

	while (headPtr_)
	{
		currentPtr_ = headPtr_;
		headPtr_ = headPtr_->next;
		delete currentPtr_;
	}
	std::wcout << L"All elems deleted!\n";
	currentPtr_ = NULL;
}

template<typename LISTTYPE>
void List<LISTTYPE>::show()
{
	if (COUNT > 100) return;
	if(headPtr_)
	{	
		currentPtr_ = headPtr_;
		while (currentPtr_)
		{
			std::cout << currentPtr_->inf << "\t";
			currentPtr_ = currentPtr_->next; // доходим до конца списка
		}
		std::cout << std::endl;
	}
	else
	{
		std::wcout << "List is empty!\n";
	}
}

template<typename LISTTYPE>
void List<LISTTYPE>::show(TElem<LISTTYPE> *list)
{
	if (headPtr_)
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
void List<LISTTYPE>::sort()
{
	mergeSort(&headPtr_);
}

template <typename LISTTYPE>
void List<LISTTYPE>::mergeSort(struct TElem<LISTTYPE> **root)
{
	deep++;
	struct TElem<LISTTYPE> *list1, *list2;
	struct TElem<LISTTYPE> *headPtr_ = *root;
	if ((headPtr_ == NULL) || (headPtr_->next == NULL))
	{
		return;
	}

	findMid(headPtr_, &list1, &list2);

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
			comparison++;
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




