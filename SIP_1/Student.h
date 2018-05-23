#pragma once

#include <string>
#include <iostream>
#include <tchar.h>

#ifdef UNICODE 
#define listStream std::wostream
#define listInStream std::wistream
#define out std::wcout
#define STRINGTYPE wchar_t
#else
#define outstream std::ostream
#define inStream std::istream
#define out std::cout
#define STRINGTYPE char
#endif


class Student
{
public:
                                Student();
                                Student(const Student&);

    void                        setName(std::basic_string<STRINGTYPE>&);
    void                        setLastname(std::basic_string<STRINGTYPE>&);
    void                        setSurname(std::basic_string<STRINGTYPE>&);
    void                        setYearOfBirht(int);
    void                        setAverMark(float);

    std::basic_string<STRINGTYPE>getName()       const;
    std::basic_string<STRINGTYPE>getLastname()   const;
    std::basic_string<STRINGTYPE>getSurname()    const;
    short int                   getYearOfBirht()const;
    float                       getAverMark()   const;

    Student&                    operator=(const Student&);
    bool                        operator==(const Student&);
    bool                        operator!=(const Student&);
    bool                        operator>=(const Student&);
    bool                        operator<=(const Student&);
    bool                        operator>(const Student&);
    bool                        operator<(const Student&);

    friend outstream&           operator << (outstream&, Student&);
    friend inStream&            operator >> (inStream&, Student&);

private:
    
    int                         compareStudents(const Student&) const;

    std::basic_string<STRINGTYPE>_name{};
    std::basic_string<STRINGTYPE>_lastname{};
    std::basic_string<STRINGTYPE>_surname{};
    short int                   _yearOfBirht;
    float                       _averMark;
};
