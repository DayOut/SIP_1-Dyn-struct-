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
        убрать кучу проверок в первом while
        удалять остаток левого списка не поэлементно а сразу все
        убрать deleteCurrElem

    getCurrInfPtr()
        сделать паблик

    sortCurr
        соединить два цикла в один, использовать проход первого для поиска нужного места для вставки

    оператор вывода в поток


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

        if (tmp) // если только левый
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
    // curr - текущий элемент (сортируемый)
    if (headPtr)
    {
        TElem <LISTTYPE> *pos = NULL; // элемент после которого надо вставлять current
        TElem <LISTTYPE> *tmp = new TElem<LISTTYPE>;
        tmp->next = headPtr;
        TElem <LISTTYPE> *prev = tmp; // элемент перед current

        while (prev->next != currentPtr) // пока не найдем предыдущий перед текущим (elem)
        {
            if (!pos && prev->next->inf > currentPtr->inf) // Если нашли место для вставки
            {
                pos = prev;
            }

            prev = prev->next;
        }

        prev->next = currentPtr->next; // вырезаем элемент

        if (currentPtr == headPtr) 
        {
            headPtr = prev->next;
        }
        else if (currentPtr == tailPtr)
        {
            tailPtr = prev;
        }

        if (!pos || pos == currentPtr) // если таки не была найдена новая позиция для elem
        {
            pos = tmp;

            while (pos->next->inf < currentPtr->inf) 
            {
                pos = pos->next; 
                if (!pos->next) // если уже прошли цикл и не нашли (значит надо вставлять после хвоста)
                {
                    break;
                }
            }
        }

        //вставка
        currentPtr->next = pos->next;
        pos->next = currentPtr;

        if (pos == tailPtr || currentPtr->next == headPtr) // если целевая позиция - после хвоста
        {
            (currentPtr->next == headPtr) ? headPtr = currentPtr : tailPtr = currentPtr;
        }
        delete tmp;
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

template <typename LISTTYPE>
outstream& operator << (outstream& output, List<LISTTYPE>& list)
{

    for (ListIterator<LISTTYPE> iter = list; !iter; ++iter)
    {
        output << *iter << __T(" ");
    }
    return output;
}



//------Iterator-----------------------------------------------------------------------------------------

template <typename LISTTYPE>
class ListIterator
{
public:
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
        listPtr = right;
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
    return (listPtr ? true : false);
}

template <typename LISTTYPE>
LISTTYPE ListIterator<LISTTYPE>::operator*()
{
    return (listPtr) ? listPtr->inf : NULL;
}