#pragma once

#include "List.h"

template <typename LISTTYPE>
class ListIterator
{
    const List &list;
public:
    ListIterator(const List<LISTTYPE>&);
    ListIterator(const ListIterator<LISTTYPE>&);

    void                        setIteratorToHead();

    ListIterator<LISTTYPE>&		operator++();
    ListIterator<LISTTYPE>&		operator=(ListIterator<LISTTYPE>& right);
    bool						operator!();


private:
    typename List<LISTTYPE>::TElem<LISTTYPE>* listPtr, *listHeadPtr;
};

template<typename LISTTYPE>
ListIterator<LISTTYPE>::ListIterator(const List<LISTTYPE>& list)
{
    listPtr = list.headPtr;
}

template<typename LISTTYPE>
ListIterator<LISTTYPE>::ListIterator(const ListIterator<LISTTYPE>& iterator)
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
