#pragma once
#include <iostream>
//#include "ListIterator.h"


/*
    
    operator=
        убрать кучу проверок в первом while
        удалять остаток левого списка не поэлементно а сразу все
        убрать deleteCurrElem

    getCurrInfPtr()
        сделать паблик

    sortCurr
        соединить два цикла в один, использовать проход первого для поиска нужного места для вставки



*/
//template <typename LISTTYPE> class ListIterator;

template <typename LISTTYPE>
class List
{

    //friend ListIterator<LISTTYPE>;

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

    void                deleteCurrentElement(TElem<LISTTYPE> *prevTmp);
    
    void                findTail();

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
    if (this == &right) //проверка на самоприсваивание 
    {
        return *this;
    }
    
    TElem<LISTTYPE> *rightHeadPtr = right.headPtr; 
    TElem<LISTTYPE> *rightCurrentPtr = rightHeadPtr; 

    TElem<LISTTYPE> *tmp = headPtr, *prevTmp = NULL; //курсоры в левом списке

    if (rightHeadPtr)
    {
        while (rightCurrentPtr && tmp) // пока оба списка есть копируем из правого в левый
        {
            tmp->inf = rightCurrentPtr->inf;
            tailPtr = tmp;
            tmp = tmp->next;
            rightCurrentPtr = rightCurrentPtr->next;
        }

        if(tailPtr)
            tailPtr->next = NULL;

        if (tmp) // если только левый
        {
            TElem<LISTTYPE> *del;
            while (tmp)
            {
                del = tmp;
                tmp = tmp->next;
                delete del;
            }
        }

        while (rightCurrentPtr) //если есть только правый
        {
            addToEnd(rightCurrentPtr->inf);
            rightCurrentPtr = rightCurrentPtr->next;
        }
    }
    else
    {
        deleteAllElems();
    }

    //findTail();

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
    if (headPtr)
    {
        TElem<LISTTYPE> *tmp;
        if (currentPtr == headPtr)
        {
            tmp = headPtr;

            if (headPtr->next != NULL)
            {
                currentPtr = headPtr->next;
                headPtr = currentPtr;
            }
            else
            {
                headPtr = tailPtr = currentPtr = NULL;
            }
        }
        else if (currentPtr == tailPtr)
        {
            tmp = currentPtr;
            currentPtr = prevTmp;
            tailPtr = prevTmp;
            tailPtr->next = NULL;
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
    TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // выделяем память на новый элемент
    tmp->inf = value;	// записываем значение 
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
    TElem<LISTTYPE> *tmp = new TElem<LISTTYPE>; // выделяем память на новый элемент
    tmp->inf = value;	// записываем значение 
    tmp->next = NULL;

    headPtr ? (tailPtr->next = tmp) : (headPtr = tmp);

    /*if (headPtr)
    {
        tailPtr->next = tmp;
    }
    else
    {
        headPtr = tmp;
    }*/
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
    if (headPtr && currentPtr) 
    {
        TElem<LISTTYPE> *tmp = headPtr;
        if (currentPtr == headPtr) //если текущий голова
        {
            headPtr = headPtr->next; //вырезаем элемент
        }
        else
        {
            //находим элемент перед текущим и вырезаем текущий
            while (tmp->next != currentPtr)
            {
                tmp = tmp->next;
            }

            if (tmp->next != tailPtr) // если не хвост
            {
                tmp->next = currentPtr->next;
            }
            else // если хвост
            {
                tailPtr = tmp;
                tailPtr->next = NULL;
            }
        }

        // Если следующий элемент после сортируемого меньше сортируемого - идем сразу в ту половину списка а иначе идем с начала
        tmp = currentPtr->next ? ((currentPtr->inf > currentPtr->next->inf) ? currentPtr->next : headPtr) : headPtr;

        // Или же лучше сделать так
        // tmp = headPtr;

        if (currentPtr->inf <= headPtr->inf)
        {
            currentPtr->next = headPtr;
            headPtr = currentPtr;
        }

        while (currentPtr->inf > tmp->inf)
        {
            if (tmp->next && currentPtr->inf <= tmp->next->inf) //нашли нужное место
            {
                currentPtr->next = tmp->next; //вставляем
                tmp->next = currentPtr;
                break;
            }
            else if (tmp == tailPtr) //если дошли до конца списка
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
    mergeSort(headPtr);
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
bool List<LISTTYPE>::bubleCheck() {
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
    * Возвращает указатель на элемент структуры TElem<LISTTYPE> рядом с серединой списка
    * и после обрезаем оригинальный списко перед этим элементом
    */
    TElem<LISTTYPE> *slow, *fast;

    //в случае пустого списка (или один элемент)
    if ((root == NULL) || (root->next == NULL))
    {
        list1 = root;
        list2 = NULL;
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

        list1 = root;
        list2 = slow->next;
        slow->next = NULL;
    }

    
}


template<typename LISTTYPE>
void List<LISTTYPE>::show()
{
    TElem<LISTTYPE> *tmp = headPtr;
    while (tmp)
    {
        std::cout << tmp->inf << "\t";
        tmp = tmp->next;    
    }
    std::cout << std::endl;
}