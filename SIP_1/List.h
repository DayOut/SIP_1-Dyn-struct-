#pragma once
#include <iostream>

#ifdef UNICODE

#define outstream std::wostream
#define out std::wcout

#else

#define outstream std::ostream
#define out std::cout

#endif // UNICODE


/*
    
    operator=
        ������ ���� �������� � ������ while
        ������� ������� ������ ������ �� ����������� � ����� ���
        ������ deleteCurrElem

    getCurrInfPtr()
        ������� ������

    sortCurr
        ��������� ��� ����� � ����, ������������ ������ ������� ��� ������ ������� ����� ��� �������

    �������� ������ � �����


*/
template <typename LISTTYPE> class ListIterator;

template <typename LISTTYPE>
class List
{

    friend ListIterator<LISTTYPE>;

private:
    template <typename LISTTYPE>
    struct TElem 
    {
        LISTTYPE		inf;
        TElem<LISTTYPE> *next;
    };

    TElem<LISTTYPE>		*headPtr,
                        *tailPtr,
                        *currentPtr;	

public:
    void show();
                        List();
                        List(const List<LISTTYPE>& right);
                        ~List();

    bool				operator!() const;
    List<LISTTYPE>&		operator++();
    const List<LISTTYPE>& operator= (const List<LISTTYPE>& right);
    
    LISTTYPE			getCurrElem();
    LISTTYPE&			getCurrInfPtr(); 
    void				setCurrToHead();

    TElem<LISTTYPE>*	findElem(LISTTYPE value);

    void				addToBegin(const LISTTYPE& value);
    void				addToEnd(const LISTTYPE& value);
    void				addSorted(const LISTTYPE& value);

    void				deleteElem(const LISTTYPE& value);
    void				deleteAllElems();

    void				sort();
    void				sortCurrElem();

    bool				bubleCheck();

    template <typename LISTTYPE> friend outstream& operator << (outstream& output, List<LISTTYPE>& list);

private:
    void				mergeSort(TElem<LISTTYPE> *&root);
    static TElem<LISTTYPE>* mergeList(TElem<LISTTYPE> *list1, TElem<LISTTYPE> *list2);
    void				findMid(TElem<LISTTYPE> *root, TElem<LISTTYPE> *&list1, TElem<LISTTYPE> *&list2);
};


template <typename LISTTYPE>
List<LISTTYPE>::List()
{
    headPtr = tailPtr = currentPtr = NULL;
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
    
    TElem<LISTTYPE> *rightHeadPtr = right.headPtr; 
    TElem<LISTTYPE> *rightCurrentPtr = rightHeadPtr; 

    TElem<LISTTYPE> *tmp = headPtr, *prevTmp = NULL; //������� � ����� ������

    if (rightHeadPtr)
    {
        while (rightCurrentPtr && tmp) // ���� ��� ������ ���� �������� �� ������� � �����
        {
            tmp->inf = rightCurrentPtr->inf;
            tailPtr = tmp;
            tmp = tmp->next;
            rightCurrentPtr = rightCurrentPtr->next;
        }

        if (tmp) // ���� ������ �����
        {
            tailPtr->next = NULL;
            TElem<LISTTYPE> *del;
            while (tmp)
            {
                del = tmp;
                tmp = tmp->next;
                delete del;
            }
        }

        while (rightCurrentPtr) //���� ���� ������ ������
        {
            addToEnd(rightCurrentPtr->inf);
            rightCurrentPtr = rightCurrentPtr->next;
        }
    }
    else
    {
        deleteAllElems();
    }

    return *this;
}

template<typename LISTTYPE>
List<LISTTYPE>& List<LISTTYPE>::operator++()
{
    currentPtr = (currentPtr) ? currentPtr->next : ((headPtr) ? headPtr : NULL);
    return *this;
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
    return currentPtr->inf;
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

template <typename LISTTYPE>
void List<LISTTYPE>::setCurrToHead()
{
        currentPtr = headPtr ? headPtr : NULL;
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

    headPtr ? (tailPtr->next = tmp) : (headPtr = tmp);

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
        TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>;
        tmp->inf = value; 
        tmp->next = currentPtr->next;
        currentPtr->next = tmp;
    }
}

template<typename LISTTYPE>
void List<LISTTYPE>::sortCurrElem()
{   
    // currentPtr - ������� ������� (�����������)
    if (headPtr)
    {
        TElem <LISTTYPE> *pos = NULL; // ������� ����� �������� ���� ��������� current
        TElem <LISTTYPE> *prev = NULL, *cur = headPtr; // ������� ����� current � ��������� ������
        bool findFlag = false;
        
        while (cur != currentPtr) // ���� �� ������ ���������� ����� ������� (elem)
        {            
            if (cur->inf >= currentPtr->inf) // ���� ����� ����� ��� �������
            {
                pos = prev;
                findFlag = true;
                break;
            }
            prev = cur;
            cur = cur->next;
        }

        for (; cur != currentPtr; prev = cur, cur = cur->next);


        if (!findFlag) // ���� ���� �� ���� ������� ����� ������� ��� elem
        {
            cur = cur->next;
            pos = prev;

            while(cur)
            {
                if (cur->inf > currentPtr->inf) // ���� ��� ������ ���� � �� ����� (������ ���� ��������� ����� ������)
                {
                    if (pos) // �������� �� ������ ���� ��������� ����� ��������� � �������
                    {
                        currentPtr == headPtr ? headPtr = currentPtr->next : prev->next = currentPtr->next;
                        /*if (currentPtr == headPtr)
                        {
                            headPtr = currentPtr->next;
                        }

                        if (prev)
                        {
                            prev->next = currentPtr->next; // �������� �������  
                        }*/
                        currentPtr->next = pos ? pos->next : headPtr; //�������
                        pos->next = currentPtr;
                    }

                    return;
                }
                pos = cur;
                cur = cur->next;
            }

            /*  
                ���� � ������ ��� � �� ����� ����� -> ���� ��������� � �����
                ����� �� ��������� ��� � �����, ����� ������� ����, ��� ��� � ����� ������ ������� ���� ������ � ����� ������
             */
           
            currentPtr == headPtr ? headPtr = currentPtr->next : prev->next = currentPtr->next;
            /* //��������� �������� - ������ ���������� ����:
            if (currentPtr == headPtr)
            {
                headPtr = currentPtr->next;
            }

            if (prev)
            {
                prev->next = currentPtr->next; // �������� �������  
            }*/

            if (pos)
            {
                currentPtr->next = pos->next; //�������
                pos->next = currentPtr;
                if (pos == tailPtr)
                    tailPtr = currentPtr;
            }
            
            return;
        }
            
        if (currentPtr == tailPtr)
            tailPtr = prev;

        prev->next = currentPtr->next;// �������� �������
        currentPtr->next = pos ? pos->next : headPtr;//�������

        if (pos)
        {
            pos->next = currentPtr;
            if (pos == tailPtr)
                tailPtr = currentPtr;
        }

        if (currentPtr->next == headPtr)
        {
            headPtr = currentPtr;
        }

       
    }
}

template<typename LISTTYPE>
void List<LISTTYPE>::deleteElem(const LISTTYPE& value)
{
    TElem<LISTTYPE>* tmpPtr = NULL;

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
                tmpPtr = currentPtr->next;
                currentPtr->next = tmpPtr->next;
                break;
            }

            currentPtr = currentPtr->next;
        }
    }

    if (tmpPtr)
    {
        delete tmpPtr;
    }
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
    headPtr = currentPtr = tailPtr = NULL;
}

template <typename LISTTYPE>
void List<LISTTYPE>::sort()
{
    if (headPtr)
    {
        mergeSort(headPtr);

        TElem<LISTTYPE> *tmp = headPtr;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tailPtr = tmp;
    }
}


template<typename LISTTYPE>
bool List<LISTTYPE>::bubleCheck() {
    TElem<LISTTYPE> *tmp = NULL, *prev = NULL;
    tmp = headPtr;
    bool flag = false, isChanged = false;
    do
    {
        flag = false;
        tmp = headPtr;
        while (tmp->next)
        {
            if (tmp->inf > tmp->next->inf)
            {
                return false;
            }
            prev = tmp;
            tmp = tmp->next;
        }
    } while (flag);

    return true;
}

template<typename LISTTYPE>
void List<LISTTYPE>::mergeSort(TElem<LISTTYPE> *&root)
{
    TElem<LISTTYPE> *list1, *list2;
    TElem<LISTTYPE> *headPtr1 = root;

    if ((headPtr1 == NULL) || (headPtr1->next == NULL))
    {
        return;
    }

    findMid(headPtr1, list1, list2);

    mergeSort(list1);
    mergeSort(list2);

    root = mergeList(list1, list2);
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
void List<LISTTYPE>::findMid(TElem<LISTTYPE> *root, TElem<LISTTYPE> *&list1, TElem<LISTTYPE> *&list2)
{
    /**
    * ���������� ��������� �� ������� ��������� TElem<LISTTYPE> ����� � ��������� ������
    * � ����� �������� ������������ ������ ����� ���� ���������
    */
    TElem<LISTTYPE> *slow, *fast;

    //� ������ ������� ������ (��� ���� �������)
    if ((root == NULL) || (root->next == NULL))
    {
        list1 = root;
        list2 = NULL;
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

        list1 = root;
        list2 = slow->next;
        slow->next = NULL;
    }

    
}

template <typename LISTTYPE>
outstream& operator << (outstream& output, List<LISTTYPE>& list)
{

    for (ListIterator<LISTTYPE> iter = list; !iter; ++iter)
    {
        output << *iter << __T(" ");
    }
    output << "\t head: " << list.headPtr->inf << " tail: " << list.tailPtr->inf;
    return output;
}



//------Iterator-----------------------------------------------------------------------------------------

template <typename LISTTYPE>
class ListIterator
{
public:
    ListIterator();
    ListIterator(List<LISTTYPE>&);
    ListIterator(ListIterator<LISTTYPE>&);

    ListIterator<LISTTYPE>&		operator++();
    ListIterator<LISTTYPE>&		operator=(ListIterator<LISTTYPE>& right);
    ListIterator<LISTTYPE>&		operator=(const List<LISTTYPE>& right);
    bool						operator!();
    LISTTYPE                    operator*();


private:
    typename List<LISTTYPE>::TElem<LISTTYPE> *listPtr;
};

template<typename LISTTYPE>
ListIterator<LISTTYPE>::ListIterator()
{
    listPtr = NULL;

}

template<typename LISTTYPE>
ListIterator<LISTTYPE>::ListIterator(List<LISTTYPE>& list)
{
    listPtr  = list.headPtr;

}

template<typename LISTTYPE>
ListIterator<LISTTYPE>::ListIterator(ListIterator<LISTTYPE>& iterator)
{
    listPtr = iterator.listPtr;
}

template <typename LISTTYPE>
ListIterator<LISTTYPE>& ListIterator<LISTTYPE>::operator++()
{
    if (listPtr != 0)
    {
        listPtr = listPtr->next;
    }
    return *this;
}

template <typename LISTTYPE>
ListIterator<LISTTYPE>&	ListIterator<LISTTYPE>::operator=(ListIterator<LISTTYPE>& right)
{
    if (this != &right)
    {
        listPtr = right.listPtr;
    }
    return *this;
}

template <typename LISTTYPE>
ListIterator<LISTTYPE>&	ListIterator<LISTTYPE>::operator= (const List<LISTTYPE>& list)
{
    if (this != &list)
    {
        listPtr = list.headPtr;
    }
    return *this;
}

template <typename LISTTYPE>
bool ListIterator<LISTTYPE>::operator!()
{
    return listPtr;
}

template <typename LISTTYPE>
LISTTYPE ListIterator<LISTTYPE>::operator*()
{
    if (!listPtr)
    {
    }
    return (listPtr) ? listPtr->inf : NULL;
}