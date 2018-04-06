#pragma once

#include "List.h"

template <typename LISTTYPE>
class ListIterator
{
    const List &list;
public:
								ListIterator(const List<LISTTYPE>&);
								ListIterator(const ListIterator<LISTTYPE>&);

	
	ListIterator<LISTTYPE>&		operator++();
	ListIterator<LISTTYPE>&		operator=(ListIterator<LISTTYPE>& right);
	bool						operator!();
	

private:
    typename List<LISTTYPE>::TElem<LISTTYPE>* list_ptr, *list_head_ptr;
};

template<typename LISTTYPE>
ListIterator<LISTTYPE>::ListIterator(const List<LISTTYPE>& list)
{
    list_ptr = list.headPtr;
}

template<typename LISTTYPE>
ListIterator<LISTTYPE>::ListIterator(const ListIterator<LISTTYPE>& iterator)
{
    list_ptr = iterator;
}


template <typename LISTTYPE>
ListIterator<LISTTYPE>& ListIterator<LISTTYPE>::operator++()
{
    this = (list_ptr->next) ? list_ptr->next : list_head_ptr;
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
    return (list_ptr->next ? true : false);
}
