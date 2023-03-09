/************************************************************************
* Class: Exception declarations
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
*
*************************************************************************/

#include "Exception.h"

#include <cstring>
#include <iostream>
using std::exchange;


Exception::Exception() : m_msg(nullptr)
{}

Exception::Exception(const char* msg) : m_msg(nullptr)
{
    if (msg != nullptr)
    {
        unsigned int length = strlen(msg);
        m_msg = new char[length + 1];
        strcpy(m_msg, msg);
    }
}

Exception::Exception(const Exception& original) : m_msg(nullptr)
{
    if (original.m_msg != nullptr)
    {
        unsigned int length = strlen(original.m_msg);
        m_msg = new char[length + 1];
        strcpy(m_msg, original.m_msg);
    }
}

Exception::Exception(Exception&& original) : m_msg(std::exchange(original.m_msg, nullptr))
{}


Exception& Exception::operator=(Exception&& rhs)
{
    if (this != &rhs)
    {
        if (m_msg != nullptr)
        {
            delete[] m_msg;
        }
        m_msg = std::move(rhs.m_msg);
    }
    return *this;
}

Exception& Exception::operator=(const Exception& rhs)
{
    if (this != &rhs)
    {
        if (m_msg != nullptr)
        {
            delete[] m_msg;
        }

        m_msg = nullptr;

        if (!rhs.m_msg)
        {
            unsigned int length = strlen(rhs.m_msg);
            m_msg = new char[length + 1];
            strcpy(m_msg, rhs.m_msg);
        }
    }
    return *this;
}




Exception::~Exception()
{
    if (m_msg != nullptr)
    {
        delete[] m_msg;
    }
}

const char* Exception::getMessage() const
{
    return m_msg;
}

void Exception::setMessage(const char* msg)
{
    if (msg != nullptr)
    {
        delete[] m_msg;
    }

    m_msg = nullptr;

    if (msg != nullptr)
    {
        unsigned int length = strlen(msg);
        m_msg = new char[length + 1];
        strcpy(m_msg, msg);
    }
}

std::ostream& operator<<(std::ostream& stream, const Exception& except)
{
    stream << except.m_msg;
    return stream;
}



/*

Exception& Exception::operator=(Exception&& rhs)noexcept
{
    if (this != &rhs)
    {
        if (m_msg != nullptr)
        {
            delete[] m_msg;
        }
        m_msg = std::move(rhs.m_msg);
    }
    return *this;
}

*/