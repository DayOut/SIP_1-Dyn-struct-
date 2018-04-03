#pragma once

#include "List.h"

template <typename LISTTYPE>
class ListIterator
{
public:
								ListIterator(const List<LISTTYPE>&);
								ListIterator(const ListIterator<LISTTYPE>&);

	/*
	ListIterator<LISTTYPE>&		operator++();
	ListIterator<LISTTYPE>&		operator=(List<LISTTYPE>& right);
	bool						operator!();
	*/

private:

};

template<typename LISTTYPE>
ListIterator<LISTTYPE>::ListIterator(const List<LISTTYPE>&)
{

}

template<typename LISTTYPE>
ListIterator<LISTTYPE>::ListIterator(const ListIterator<LISTTYPE>&)
{

}


