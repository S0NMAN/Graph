/************************************************************************
* Class: Exception
*
* Purpose: This class will be used to handle the following exceptions:
*				a.	Specifying an index smaller than the lower bounds.
*				b.	Specifying an index larger than the upper bounds.
*
* Manager functions:
* Exception ( )
* Exception(const char* msg)
* Exception (const Exception & original)
* plus the move semantics
* operator = (const Exception & original)
* ~Exception()
*
*
*
* Setters and Getters:
* const char* getMessage()
* setMessage(const char * msg)
* GetLength()
* SetLength(int length)
*
*
*
*
*************************************************************************/




#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC


#include<cstring>
#include <iostream>


class Exception
{

public:
    Exception();
    Exception(const char* msg);
    Exception(const Exception& original);
    Exception(Exception&& original);
    Exception& operator=(const Exception& rhs);
    Exception& operator=(Exception&& rhs);
    ~Exception();

    const char* getMessage() const;
    void setMessage(const char* msg);
    friend std::ostream& operator<<(std::ostream& stream, const Exception& except);

private:
    char* m_msg;
};
