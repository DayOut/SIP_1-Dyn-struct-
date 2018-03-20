#pragma once

template <typename LISTTYPE>
class List
{
private:
	template <typename LISTTYPE>
	struct TElem //��������� ������ �������� ������
	{
		LISTTYPE inf;
		TElem<LISTTYPE> *next;
	};

	TElem<LISTTYPE> *headPtr, *currentPtr; // ���������� ��������� �� ������ ������
										   //currentPtr - ��� ��������� �� ������� �������, ���� ����� ���������� - ���������� ������ � ���� �������

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
	void deleteElem	(const LISTTYPE& value);
	
	void show();
	void show(TElem<LISTTYPE> *list);

	void Sort();
	

private:
	void mergeSort(struct TElem<LISTTYPE> **root);
	static TElem<LISTTYPE>* mergeList(struct TElem<LISTTYPE> *list1, struct TElem<LISTTYPE> *list2);
	void findMid(struct TElem<LISTTYPE> *root, struct TElem<LISTTYPE> **list1, struct TElem<LISTTYPE> **list2);
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
			std::wcout << L"\n������� " << value << L" ���� � ������ \n";
			return currentPtr;
		}
	}
	std::wcout << L"\n�������� " << value << L" ��� � ������ \n";
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
void List<LISTTYPE>::deleteElem(const LISTTYPE& value)
{
	TElem<LISTTYPE>* tmpPtr = new TElem<LISTTYPE>;
	currentPtr = headPtr;
	if (headPtr->inf == value)
	{
		tmpPtr = headPtr;
		headPtr = headPtr->next;
	}
	else
	{
		while (currentPtr->next)
		{
			if (currentPtr->next->inf == value)
			{
				break;
			}
			currentPtr = currentPtr->next;
		}
		tmpPtr = currentPtr->next;
		currentPtr->next = tmpPtr->next;
	}
		
	delete tmpPtr;
}

template<typename LISTTYPE>
void List<LISTTYPE>::show()
{
	if (COUNT > 100) return;

	currentPtr = headPtr;
	while (currentPtr)
	{
		std::cout << currentPtr->inf << "\t";
		currentPtr = currentPtr->next; // ������� �� ����� ������
	}
	std::cout << std::endl;
}

template<typename LISTTYPE>
void List<LISTTYPE>::show(TElem<LISTTYPE> *list)
{
	TElem<LISTTYPE> *tmp = list;
	for (; tmp; tmp = tmp->next)
		cout << tmp->inf << " ";
	cout << endl;
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




