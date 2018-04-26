#pragma once

template <typename LISTTYPE>
class ListIterator
{
public:
    ListIterator(List<LISTTYPE>&);
    ListIterator(ListIterator<LISTTYPE>&);

    void                        setIteratorToHead();

    ListIterator<LISTTYPE>&		operator++();
    ListIterator<LISTTYPE>&		operator=(ListIterator<LISTTYPE>& right);
    bool						operator!();
    LISTTYPE                    operator*();


private:
    typename List<LISTTYPE>::TElem<LISTTYPE> *listPtr, *listHeadPtr;
};

template<typename LISTTYPE>
ListIterator<LISTTYPE>::ListIterator(List<LISTTYPE>& list)
{
    listPtr = listHeadPtr = list.headPtr;

}

template<typename LISTTYPE>
ListIterator<LISTTYPE>::ListIterator(ListIterator<LISTTYPE>& iterator)
{
    listPtr = iterator;
}

template<typename LISTTYPE>
void ListIterator<LISTTYPE>::setIteratorToHead()
{
    listPtr = listHeadPtr;
}



template <typename LISTTYPE>
ListIterator<LISTTYPE>& ListIterator<LISTTYPE>::operator++()
{
    this = (listPtr->next) ? listPtr->next : listHeadPtr;
    return *this;
}

template <typename LISTTYPE>
ListIterator<LISTTYPE>&	ListIterator<LISTTYPE>::operator=(ListIterator<LISTTYPE>& right)
{
    if (this != right)
    {
        *this = right;
    }
    return *this;
}

template <typename LISTTYPE>
bool ListIterator<LISTTYPE>::operator!()
{
    return (listPtr->next ? true : false);
}

template <typename LISTTYPE>
LISTTYPE ListIterator<LISTTYPE>::operator*()
{
    return (listPtr) ? listPtr->inf : NULL;
}