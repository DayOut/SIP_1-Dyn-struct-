#pragma once
int rec = 0, comp = 0;


template <typename LISTTYPE>
class List
{
private:
	template <typename LISTTYPE>
	struct TElem //��������� ������ �������� ������
	{
		LISTTYPE		inf;
		TElem<LISTTYPE> *next;
	};

	TElem<LISTTYPE>		*headPtr, 
						*currentPtr;	// ���������� ��������� �� ������ ������
										//currentPtr - ��� ��������� �� ������� �������, ���� ����� ���������� - ���������� ������ � ���� �������
	int					size = 0;
	
public:
						List();
						List(const List& value);
						~List();

	void				setSize(int value);
	int					getSize();

	bool				isEmpty() const;
	bool				operator!() const;
	List<LISTTYPE>&		operator=(List<LISTTYPE>& right);
	List<LISTTYPE>&		operator++();

	TElem<LISTTYPE>*	getHeadPtr();

	LISTTYPE&			getCurrInfPtr();
	LISTTYPE			getCurrElem();
	void				setCurrToHead();

	TElem<LISTTYPE>*	findElem(LISTTYPE value);

	void				addToBegin	(const LISTTYPE& value);
	void				addToBegin	(TElem<LISTTYPE>* value);

	void				addToEnd	(const LISTTYPE& value);

	void				addSorted	(const LISTTYPE& value);
	void				sortCurrElem();

	bool				deleteElem	(const LISTTYPE& value);
	void				deleteAllElems();
	
	void				show();
	void				show(TElem<LISTTYPE> *list);

	void				sort();
	void				bubleSort();

private:
	void				mergeSort (struct TElem<LISTTYPE> **root);
	static TElem<LISTTYPE>* mergeList	(struct TElem<LISTTYPE> *list1, struct TElem<LISTTYPE> *list2);
	void				findMid (struct TElem<LISTTYPE> *root, struct TElem<LISTTYPE> **list1, struct TElem<LISTTYPE> **list2);
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
		while (headPtr) // ����������� ������� ��� �������� ������
		{
			TElem<LISTTYPE> *tmp = headPtr;
			headPtr = headPtr->next;
			delete tmp;
		}
	}
}

template <typename LISTTYPE>
void List<LISTTYPE>::setSize(int value)
{
	size = value;
}

template <typename LISTTYPE>
int List<LISTTYPE>::getSize()
{
	return size;
}

template <typename LISTTYPE>
bool List<LISTTYPE>::isEmpty() const
{
	return headPtr == 0;
}

template <typename LISTTYPE>
bool List<LISTTYPE>::operator!() const
{
	return (headPtr == NULL);
}

template <typename LISTTYPE>
List<LISTTYPE>& List<LISTTYPE>::operator=(List<LISTTYPE>& right)
{
	if (!right.isEmpty())
	{
		// ������ ������ ��� ���, �� �������� ����� ��������� ��������
		TElem<LISTTYPE> *rightHead = right.getHeadPtr(); // ��������� ������ ������ �� �������
		TElem<LISTTYPE> *rightCurrElem = rightHead; // ������� ������� �� ����� �� ������

		if (this == &right) 
		{
			return *this; // �������� �� ����������������
		}

		if (!isEmpty())// ���� ����� ������ ��� �� ������ 
		{
			deleteAllElems();
		}

		TElem<LISTTYPE> *tmpHeadPtr = new TElem<LISTTYPE>;
		tmpHeadPtr->inf = rightHead->inf;
		tmpHeadPtr->next = NULL;

		headPtr = tmpHeadPtr;
		currentPtr = headPtr;
		
		if (rightCurrElem->next)
		{
			rightCurrElem = rightCurrElem->next;
		}

		do
		{
			//addToEnd(rightCurrElem->inf); // ������ ��������� � ����� ������ ������ �������� �� �������
			TElem<LISTTYPE> *tmpPtr = new TElem<LISTTYPE>; // �������� ������ �� ����� �������
			tmpPtr->inf = rightCurrElem->inf;	// ���������� �������� 
			tmpPtr->next = NULL;

			currentPtr->next= tmpPtr;
			rightCurrElem	= rightCurrElem->next;
			currentPtr		= currentPtr->next;
		} while (rightCurrElem != NULL);

		currentPtr = headPtr;
		size = right.getSize();
	}
	return *this;
}

template<typename LISTTYPE>
List<LISTTYPE>& List<LISTTYPE>::operator++()
{
	if (currentPtr)
	{
		currentPtr = currentPtr->next;
	}
	else
	{
		currentPtr = headPtr;
	}
	return *this;
}

template<typename LISTTYPE>
typename List<LISTTYPE>::TElem<LISTTYPE>* List<LISTTYPE>::getHeadPtr()
 {

	 return headPtr;
 }

template <typename LISTTYPE>
LISTTYPE& List<LISTTYPE>::getCurrInfPtr()
 {
	 if (currentPtr)
	 {
		 return currentPtr->inf;
	 }
	 else
	 {
		 currentPtr = headPtr;
		 return currentPtr->inf;
	 }
	 return nullptr; // i have no idea what happened, if you receive this value
 }

template<typename LISTTYPE>
LISTTYPE List<LISTTYPE>::getCurrElem()
{
	if (!currentPtr)
	{
		currentPtr = headPtr;
	}
	return currentPtr->inf;
}

template <typename LISTTYPE>
void List<LISTTYPE>::setCurrToHead()
{
	currentPtr = headPtr;
}

template<typename LISTTYPE>
typename List<LISTTYPE>::TElem<LISTTYPE>* List<LISTTYPE>::findElem(LISTTYPE value)
{
	currentPtr = headPtr;
	for (; currentPtr; currentPtr = currentPtr->next)
	{
		if (currentPtr->inf == value)
		{
			std::wcout << L"\n������� \"" << value << L"\" ���� � ������ \n";
			return currentPtr;
		}
	}
	std::wcout << L"\n�������� \"" << value << L"\" ��� � ������ \n";
	return 0;
}

template <typename LISTTYPE>
void List<LISTTYPE>::addToBegin(const LISTTYPE& value)
{
	TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // �������� ������ �� ����� �������
	tmp->inf = value;	// ���������� �������� 
	tmp->next = headPtr;
	headPtr = tmp;
}

template <typename LISTTYPE>
void List<LISTTYPE>::addToBegin(TElem<LISTTYPE>* value)
{
	TElem<LISTTYPE> *tmp = value; // �������� ������ �� ����� �������
	tmp->next = headPtr;
	headPtr = tmp;
}

template <typename LISTTYPE>
void List<LISTTYPE>::addToEnd(const LISTTYPE& value) // add_end / ...
{
	if (isEmpty()) // ���� ������ ����������� ()
	{
		addToBegin(value);
	}
	else
	{
		currentPtr = headPtr;
		while (currentPtr->next)
		{
			currentPtr = currentPtr->next; // ������� �� ����� ������
		}
		TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // �������� ������ �� ����� �������
		tmp->inf = value;	// ���������� �������� 
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
		TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // �������� ������ �� ����� �������
		tmp->inf = value;	// ���������� �������� 
		tmp->next = currentPtr->next;
		currentPtr->next = tmp;
	}
}

template<typename LISTTYPE>
void List<LISTTYPE>::sortCurrElem()
{
	//find an element
	TElem<LISTTYPE>* tmp = 0;
	bool findFlag = false;

	if (headPtr == currentPtr)
	{
		headPtr = headPtr->next;
		findFlag = true;
	}

	for (; !findFlag && currentPtr; currentPtr = currentPtr->next)
	{
		if (currentPtr->next && currentPtr->next->inf == currentPtr->inf)
		{
			std::wcout << L"\n������� " << currentPtr->inf << L" ���� � ������ \n";

			//cut this elem from the list
			tmp = currentPtr->next;
			currentPtr->next = tmp->next;

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
		addToBegin(currentPtr->inf);
	}
	else
	{
		TElem<LISTTYPE> *tmpCurrentPtr = headPtr;
		while (tmpCurrentPtr->next)
		{
			if (tmpCurrentPtr->next->inf > currentPtr->inf)
			{
				break;
			}
			tmpCurrentPtr = tmpCurrentPtr->next;
		}
		currentPtr->next = tmpCurrentPtr->next;
		tmpCurrentPtr->next = currentPtr;

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
	if (size > 100) return;
	if(headPtr)
	{	
		currentPtr = headPtr;
		while (currentPtr)
		{
			std::cout << currentPtr->inf << "\t";
			currentPtr = currentPtr->next; // ������� �� ����� ������
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
void List<LISTTYPE>::sort()
{
	mergeSort(&headPtr);
}

template<typename LISTTYPE>
void List<LISTTYPE>::bubleSort() {
	TElem<LISTTYPE> *tmp = NULL, *prev = NULL;
	currentPtr = headPtr;
	bool flag = false, isChanged = false;
	do
	{
		flag = false;
		currentPtr = headPtr;
		while (currentPtr->next)
		{
			if (currentPtr->inf > currentPtr->next->inf)
			{
				isChanged = true;
				if (currentPtr == headPtr)
				{
					tmp = currentPtr;
					currentPtr = tmp->next;
					tmp->next = currentPtr->next;
					currentPtr->next = tmp;
					headPtr = currentPtr;
					flag = true;
				}
				else
				{
					tmp = currentPtr;
					currentPtr = tmp->next;
					tmp->next = currentPtr->next;
					currentPtr->next = tmp;
					prev->next = currentPtr;
					flag = true;
				}
			}
			prev = currentPtr;
			currentPtr = currentPtr->next;
		}
	} while (flag);
	if(!isChanged)
		std::cout << "���������� ���� ��������� �����." << std::endl;
	else 
		std::cout << "���� ������ � ��������������� ������." << std::endl;
}
/*
template<typename LISTTYPE>
void List<LISTTYPE>::bubleSort()
{
	bool swapFlag = false;
	TElem<LISTTYPE>* l1 = headPtr, *l2 = 0;
	for (l2; l2; l2 = l2->next)
	{
		for(l1; l1->next; l1 = l1->next)
		{ 
			if (l1->inf > l1->next->inf)
			{
				LISTTYPE tmp = l1->inf;
				l1->inf = l1->next->inf;
				l1->next->inf = tmp;
				swapFlag = true;
			}

		}
	}

	if (!swapFlag)
	{
		std::cout << "������������ �� �����������! \n";
	}
	else
	{
		std::cout << "������������ ����! D: \n";
	}
}*/

template <typename LISTTYPE>
void List<LISTTYPE>::mergeSort(struct TElem<LISTTYPE> **root)
{
	struct TElem<LISTTYPE> *list1, *list2;
	struct TElem<LISTTYPE> *headPtr1 = *root;

	if ((headPtr1 == NULL) || (headPtr1->next == NULL))
	{
		return;
	}

	findMid(headPtr1, &list1, &list2);

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
		comp++;
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
	* ���������� ��������� �� ������� ��������� TElem<LISTTYPE> ����� � ��������� ������
	* � ����� �������� ������������ ������ ����� ���� ���������
	*/
	struct TElem<LISTTYPE> *slow, *fast;

	//� ������ ������� ������ (��� ���� �������)
	if ((root == NULL) || (root->next == NULL))
	{
		*list1 = root;
		*list2 = NULL;
		return;
	}
	else
	{
		/*
		��� �������, fast �������� � 2 ���� ������� slow, �� ���� �������� slow ���������� 2 �������� fast
		�� ���� ����� ��������� �������� ������ (����� fast == NULL, slow ����� ����� � ������ ������)
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




