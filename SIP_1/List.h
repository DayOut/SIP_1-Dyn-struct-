#pragma once
#define SHOW_FLAG true

template <typename LISTTYPE> class ListIterator;

template <typename LISTTYPE>
class List
{

    friend ListIterator<LISTTYPE>;

private:
    template <typename LISTTYPE>
    struct TElem //��������� ������ �������� ������
    {
        LISTTYPE		inf;
        TElem<LISTTYPE> *next;
    };

    TElem<LISTTYPE>		*headPtr,
        *tailPtr,
        *currentPtr;	// ���������� ��������� �� ������ ������
                        //currentPtr - ��� ��������� �� ������� �������, ���� ����� ���������� - ���������� ������ � ���� �������

    TElem<LISTTYPE>*	getHeadPtr(); // ������
    void                deleteCurrentElement(TElem<LISTTYPE> *prevTmp);

public:
                        List();
                        List(const List<LISTTYPE>& right);
                        ~List();

    bool				operator!() const;
    List<LISTTYPE>&		operator++();
    const List<LISTTYPE>& operator= (const List<LISTTYPE>& right);



    LISTTYPE&			getCurrInfPtr();
    LISTTYPE			getCurrElem();
    void				setCurrToHead();


    TElem<LISTTYPE>*	findElem(LISTTYPE value);

    void				addToBegin(const LISTTYPE& value);

    void				addToEnd(const LISTTYPE& value);

    void				addSorted(const LISTTYPE& value);
    void				sortCurrElem();

    bool				deleteElem(const LISTTYPE& value);
    void				deleteAllElems();

    void				sort();
    void                findTail();
    bool				bubleSort();

    void                show();

private:
    void				mergeSort(TElem<LISTTYPE> **root);
    static TElem<LISTTYPE>* mergeList(TElem<LISTTYPE> *list1, TElem<LISTTYPE> *list2);
    void				findMid(TElem<LISTTYPE> *root, TElem<LISTTYPE> **list1, TElem<LISTTYPE> **list2);
};


template <typename LISTTYPE>
List<LISTTYPE>::List()
{
    headPtr = NULL;
    tailPtr = NULL;
    currentPtr = NULL;
}

template <typename LISTTYPE>
List<LISTTYPE>::List(const List<LISTTYPE>& right)
{
    headPtr = currentPtr = tailPtr = NULL;

    if (right.headPtr)
    {
        *this = right;
    }
}

template <typename LISTTYPE>
List<LISTTYPE>::~List()
{
    deleteAllElems();
}

template <typename LISTTYPE>
bool List<LISTTYPE>::operator!() const
{
    return (headPtr == NULL);
}

template <typename LISTTYPE>
const List<LISTTYPE>& List<LISTTYPE>::operator= (const List<LISTTYPE>& right)
{
    if (this == &right) //�������� �� ���������������� 
    {
        return *this;
    }
    
    TElem<LISTTYPE> *rightHeadPtr = right.headPtr; //��������� ������ ������ �� �������
    TElem<LISTTYPE> *rightCurrentPtr = rightHeadPtr; //������� ������� �� ����� �� ������

    TElem<LISTTYPE> *tmp = headPtr, *prevTmp = NULL; //������� � ����� ������
    if (rightHeadPtr)
    {
        while (rightCurrentPtr && tmp) // ���� ��� ������ ���� �������� �� ������� � �����
        {
            tmp->inf = rightCurrentPtr->inf;
            prevTmp = (tmp) ? tmp : NULL;
            tmp = (tmp->next == headPtr) ? NULL : tmp->next;
            rightCurrentPtr = (rightCurrentPtr->next == rightHeadPtr) ? NULL : rightCurrentPtr->next;
        }

        while (tmp && !rightCurrentPtr) //���� ���� ������ ����� 
        {
            currentPtr = tmp;
            tmp = prevTmp ? prevTmp : tailPtr;
            deleteCurrentElement(prevTmp);
            if (tmp)
                tmp = (tmp->next == headPtr) ? NULL : tmp->next;
            else
            {
                tmp = NULL;
            }
        }

        while (!tmp && rightCurrentPtr) //���� ���� ������ ������
        {
            addToEnd(rightCurrentPtr->inf);
            rightCurrentPtr = (rightCurrentPtr->next == rightHeadPtr) ? NULL : rightCurrentPtr->next;
        }
    }
    else
    {
        deleteAllElems();
    }

    findTail();

    return *this;


    /*
    if (this == &right) //�������� �� ���������������� 
    {
        return *this;
    }

    TElem<LISTTYPE> *rightHead = right.headptr;
    TElem<LISTTYPE> *rightCurrent = rightHead;

    TElem<LISTTYPE> *tmp = headPtr, *prevTmp = NULL; // ������� � ����� ������

    //TODO: ������� ��������� ������ ������ ���� IF

    while (tmp || rightCurrent)
    {
        if (rightCurrent && tmp)
        {
            tmp->inf = rightCurrent->inf;
        }
        else if (tmp && !rightCurrent)
        {
            currentPtr = tmp;
            tmp = prevTmp;
            deleteCurrentElement(prevTmp);
        }
        else if (!tmp && rightCurrent)
        {
            addToEnd(rightCurrent->inf);
        }

        if (prevTmp != tmp)
            prevTmp = (tmp) ? tmp : NULL;

        if (tmp)
            tmp = (tmp->next == NULL) ? NULL : tmp->next;

        if (rightCurrent)
            rightCurrent = (rightCurrent->next == NULL) ? NULL : rightCurrent->next;
    }
    return *this;*/
}

template<typename LISTTYPE>
List<LISTTYPE>& List<LISTTYPE>::operator++()
{
    currentPtr = (currentPtr) ? currentPtr->next : ((headPtr) ? headPtr : NULL);
    return *this;
}

template<typename LISTTYPE>
typename List<LISTTYPE>::TElem<LISTTYPE>* List<LISTTYPE>::getHeadPtr()
{
    return (headPtr) ? headPtr : NULL;
}

template <typename LISTTYPE>
LISTTYPE& List<LISTTYPE>::getCurrInfPtr()
{
    if (headPtr)
    {
        if (currentPtr)
        {
            return currentPtr->inf;
        }
    }
}

template<typename LISTTYPE>
LISTTYPE List<LISTTYPE>::getCurrElem()
{
    if (headPtr)
    {
        return currentPtr ? currentPtr->inf : (currentPtr = headPtr)->inf;
    }
    return false;
}

template<typename LISTTYPE>
void List<LISTTYPE>::deleteCurrentElement(TElem<LISTTYPE> *prevTmp)
{
    TElem<LISTTYPE> *tmp;
    if (headPtr)
    {
        if (currentPtr == headPtr)
        {
            tmp = headPtr;

            if (headPtr->next == NULL)
            {
                headPtr = NULL;
            }
            else
            {
                currentPtr = headPtr->next;
                headPtr = currentPtr;
                tailPtr->next = NULL;
            }
        }
        else
        {
            tmp = currentPtr;
            currentPtr = currentPtr->next;
            prevTmp->next = currentPtr;

        }

        delete tmp;
    }
}

template <typename LISTTYPE>
void List<LISTTYPE>::setCurrToHead()
{
    if (headPtr)
    {
        currentPtr = headPtr;
    }
}

template<typename LISTTYPE>
typename List<LISTTYPE>::TElem<LISTTYPE>* List<LISTTYPE>::findElem(LISTTYPE value)
{
    if (headPtr)
    {
        for (currentPtr = headPtr; currentPtr; currentPtr = currentPtr->next)
        {
            if (currentPtr->inf == value)
            {
                return currentPtr;
            }
        }
    }
    return NULL;
}

template <typename LISTTYPE>
void List<LISTTYPE>::addToBegin(const LISTTYPE& value)
{
    TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // �������� ������ �� ����� �������
    tmp->inf = value;	// ���������� �������� 
    tmp->next = headPtr;
    headPtr = tmp;
    if (tailPtr == NULL)
    {
        tailPtr = headPtr;
    }
}

template <typename LISTTYPE>
void List<LISTTYPE>::addToEnd(const LISTTYPE& value)
{
    TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // �������� ������ �� ����� �������
    tmp->inf = value;	// ���������� �������� 
    tmp->next = NULL;

    if (headPtr)
    {
        tailPtr->next = tmp;
    }
    else
    {
        headPtr = tmp;
    }
    tailPtr = tmp;
}

template<typename LISTTYPE>
void List<LISTTYPE>::addSorted(const LISTTYPE& value)
{
    if (!this || value <= headPtr->inf)
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
    if (headPtr && tailPtr) {
        if (!currentPtr)
        {
            currentPtr = headPtr;
        }

        TElem<LISTTYPE> *tmp = headPtr;
        if (currentPtr == headPtr) //���� ������� ������
        {
            headPtr = headPtr->next; //�������� �������
        }
        else
        {
            //������� ������� ����� ������� � �������� �������
            while (tmp->next != currentPtr)
            {
                tmp = tmp->next;
            }

            if (tmp->next != tailPtr) // ���� �� �����
            {
                tmp->next = currentPtr->next;
            }
            else // ���� �����
            {
                tailPtr = tmp;
                tailPtr->next = NULL;
            }
        }


        // ���� ��������� ������� ����� ������������ ������ ������������ - ���� ����� � �� �������� ������ � ����� ���� � ������
        tmp = currentPtr->next ? ((currentPtr->inf > currentPtr->next->inf) ? currentPtr->next : headPtr) : headPtr;

        // ��� �� ����� ������� ���
        // tmp = headPtr;

        if (currentPtr->inf <= headPtr->inf)
        {
            currentPtr->next = headPtr;
            headPtr = currentPtr;
        }

        while (currentPtr->inf > tmp->inf)
        {
            if (tmp->next && currentPtr->inf <= tmp->next->inf) //����� ������ �����
            {
                currentPtr->next = tmp->next; //���������
                tmp->next = currentPtr;
                break;
            }
            else if (tmp == tailPtr) //���� ����� �� ����� ������
            {
                currentPtr->next = NULL;
                tailPtr->next = currentPtr;
                tailPtr = currentPtr;
                break;
            }
            tmp = tmp->next;
        }
    }
}

template<typename LISTTYPE>
bool List<LISTTYPE>::deleteElem(const LISTTYPE& value)
{
    TElem<LISTTYPE>* tmpPtr = NULL;
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
    currentPtr = tailPtr = NULL;
}

template <typename LISTTYPE>
void List<LISTTYPE>::sort()
{
    mergeSort(&headPtr);
    findTail();
}

template <typename LISTTYPE>
void List<LISTTYPE>::findTail()
{
    tailPtr = NULL;

    if (headPtr)
    {
        TElem<LISTTYPE> *tmp = headPtr;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tailPtr = tmp;
    }
}

template<typename LISTTYPE>
bool List<LISTTYPE>::bubleSort() {
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
                return false;
            }
            prev = currentPtr;
            currentPtr = currentPtr->next;
        }
    } while (flag);

    return true;
}

template <typename LISTTYPE>
void List<LISTTYPE>::mergeSort(TElem<LISTTYPE> **root)
{
    TElem<LISTTYPE> *list1, *list2;
    TElem<LISTTYPE> *headPtr1 = *root;

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
typename List<LISTTYPE>::TElem<LISTTYPE>* List<LISTTYPE>::mergeList(TElem<LISTTYPE> *list1, TElem<LISTTYPE> *list2)
{
    TElem<LISTTYPE> tempheadPtr = { 0, NULL }, *tail = &tempheadPtr;

    while ((list1 != NULL) && (list2 != NULL))
    {
        TElem<LISTTYPE> **min = (list1->inf < list2->inf) ? &list1 : &list2;
        TElem<LISTTYPE> *next = (*min)->next;
        tail = tail->next = *min;
        *min = next;
    }
    tail->next = list1 ? list1 : list2;
    return tempheadPtr.next;
}

template<typename LISTTYPE>
void List<LISTTYPE>::findMid(TElem<LISTTYPE> *root, TElem<LISTTYPE> **list1, TElem<LISTTYPE> **list2)
{
    /**
    * ���������� ��������� �� ������� ��������� TElem<LISTTYPE> ����� � ��������� ������
    * � ����� �������� ������������ ������ ����� ���� ���������
    */
    TElem<LISTTYPE> *slow, *fast;

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

template<typename LISTTYPE>
void List<LISTTYPE>::show()
{
    if (SHOW_FLAG)
    {
        if (headPtr)
        {
            TElem<LISTTYPE> *tmp = headPtr;
            while (tmp)
            {
                std::cout << tmp->inf << "\t";
                tmp = tmp->next; // ������� �� ����� ������
            }
            std::cout << std::endl;
        }
        else
        {
            std::wcout << L"������ ����!\n";
        }
    }
}


