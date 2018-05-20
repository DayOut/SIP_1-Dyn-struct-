#pragma once

#include <string>
#include <iostream>
#include <tchar.h>

#ifdef UNICODE 
#define listStream std::wostream
#define listInStream std::wistream
#define out std::wcout
#else
#define outstream std::ostream
#define inStream std::istream
#define out std::cout
#endif


class Student
{
public:
                                Student();
                                Student(const Student&);

    void                        setName(std::basic_string<TCHAR>&);
    void                        setLastname(std::basic_string<TCHAR>&);
    void                        setSurname(std::basic_string<TCHAR>&);
    void                        setYearOfBirht(int);
    void                        setAverMark(float);

    std::basic_string<TCHAR>    getName()       const;
    std::basic_string<TCHAR>    getLastname()   const;
    std::basic_string<TCHAR>    getSurname()    const;
    short int                   getYearOfBirht()const;
    float                       getAverMark()   const;

    Student&                    operator=(const Student&);
    bool                        operator==(const Student&);
    bool                        operator!=(const Student&);
    bool                        operator>=(const Student&);
    bool                        operator<=(const Student&);
    bool                        operator>(const Student&);
    bool                        operator<(const Student&);

    friend outstream&           operator<<(outstream&, Student&);
    friend inStream&            operator >> (inStream&, Student&);

private:
    
    int                         compareStudents(const Student&) const;

    std::basic_string<TCHAR>    _name{};
    std::basic_string<TCHAR>    _lastname{};
    std::basic_string<TCHAR>    _surname{};
    short int                   _yearOfBirht;
    float                       _averMark;
};
