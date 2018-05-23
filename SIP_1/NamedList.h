#pragma once

#include "List.h"
#include <string>

#ifdef UNICODE 
#define STRINGTYPE wchar_t
#else
#define STRINGTYPE char
#endif

template <typename LISTTYPE>
class NamedList : public List<LISTTYPE>
{
public:
                                NamedList(const std::basic_string<STRINGTYPE>& = "");
                                NamedList(NamedList<LISTTYPE>&);

    void                        setListName(std::basic_string<STRINGTYPE>&);
    std::basic_string<STRINGTYPE>getListName() const;

    const NamedList<LISTTYPE>&  operator=(NamedList<LISTTYPE>&);

    bool                        operator==(NamedList<LISTTYPE>&);
    bool                        operator!=(NamedList<LISTTYPE>&);
    bool                        operator>=(NamedList<LISTTYPE>&);
    bool                        operator<=(NamedList<LISTTYPE>&);
    bool                        operator>(NamedList<LISTTYPE>&);
    bool                        operator<(NamedList<LISTTYPE>&);
private:
    std::basic_string<STRINGTYPE>_ListName;
};




template <typename LISTTYPE>
NamedList<LISTTYPE>::NamedList(const std::basic_string<STRINGTYPE>& str)
{
    _ListName = str;
}

template <typename LISTTYPE>
NamedList<LISTTYPE>::NamedList(NamedList<LISTTYPE>& right)
{
    *this = right;
}

template <typename LISTTYPE>
void NamedList<LISTTYPE>::setListName(std::basic_string<STRINGTYPE>& str)
{
    _ListName = str;
}

template <typename LISTTYPE>
std::basic_string<STRINGTYPE> NamedList<LISTTYPE>::getListName() const
{
    return _ListName;
}

template <typename LISTTYPE>
const NamedList<LISTTYPE>& NamedList<LISTTYPE>::operator=(NamedList<LISTTYPE>& right)
{
    if (this != &right)
    {
        List<LISTTYPE>::operator=(right);
        _ListName = right._ListName;
    }
    return *this;
}

template <typename LISTTYPE>
bool NamedList<LISTTYPE>::operator==(NamedList<LISTTYPE>& rList)
{
    return _ListName.compare(rList._ListName) == 0;
}

template <typename LISTTYPE>
bool NamedList<LISTTYPE>::operator!=(NamedList<LISTTYPE>& rList)
{
    return _ListName.compare(rList._ListName) != 0;
}

template <typename LISTTYPE>
bool NamedList<LISTTYPE>::operator>=(NamedList<LISTTYPE>& rList)
{
    return _ListName.compare(rList._ListName) >= -1;
}

template <typename LISTTYPE>
bool NamedList<LISTTYPE>::operator<=(NamedList<LISTTYPE>& rList)
{
    return _ListName.compare(rList._ListName) <= 1;
}

template <typename LISTTYPE>
bool NamedList<LISTTYPE>::operator>(NamedList<LISTTYPE>& rList)
{
    return _ListName.compare(rList._ListName) == 1;
}

template <typename LISTTYPE>
bool NamedList<LISTTYPE>::operator<(NamedList<LISTTYPE>& rList)
{
    return _ListName.compare(rList._ListName) == -1;
}