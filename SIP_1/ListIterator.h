#pragma once

#include "List.h"

template <typename LISTTYPE>
class ListIterator
{
public:
								ListIterator(const List<LISTTYPE>&);
								ListIterator(const ListIterator<LISTTYPE>&);

	
	ListIterator<LISTTYPE>&		operator++();
    /*
	ListIterator<LISTTYPE>&		operator=(List<LISTTYPE>& right);
	bool						operator!();
	*/

private:
    typename List<LISTTYPE>::TElem<LISTTYPE>* list_ptr;
};

template<typename LISTTYPE>
ListIterator<LISTTYPE>::ListIterator(const List<LISTTYPE>& list)
{
    list_ptr = list.headPtr;
}

template<typename LISTTYPE>
ListIterator<LISTTYPE>::ListIterator(const ListIterator<LISTTYPE>&)
{
    
}


template <typename LISTTYPE>
ListIterator<LISTTYPE>& ListIterator<LISTTYPE>::operator++()
{
    list_ptr = list_ptr->next;
    return *this;
}
