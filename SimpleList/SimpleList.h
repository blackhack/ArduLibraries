// SimpleList.h

#ifndef _SIMPLELIST_h
#define _SIMPLELIST_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef NULL
#define NULL 0
#endif

template<typename T>
class SimpleList
{
public:

    SimpleList()
    {
        _list = NULL;
        _size = 0;
    }

    ~SimpleList()
    {
        delete[] _list;
        _list = NULL;
        _size = 0;
    }

    void push_back(T obj)
    {
        ++_size;

        T* newBuffer = new T[_size];

        for (unsigned int i = 0; i < _size - 1; ++i)
            newBuffer[i] = _list[i];

        newBuffer[_size - 1] = obj;

        delete[] _list;
        _list = newBuffer;
    }

    void push_front(T obj)
    {
        ++_size;

        T* newBuffer = new T[_size];

        newBuffer[0] = obj;
        for (unsigned int i = 1; i < _size; ++i)
            newBuffer[i] = _list[i - 1];

        delete[] _list;
        _list = newBuffer;
    }

    void pop_back()
    {
        if (empty())
            return;

        --_size;
        if (empty())
        {
            delete[] _list;
            return;
        }

        T* newBuffer = new T[_size];

        for (unsigned int i = 0; i < _size; ++i)
            newBuffer[i] = _list[i];

        delete[] _list;
        _list = newBuffer;
    }

    void pop_front()
    {
        if (empty())
            return;

        --_size;
        if (empty())
        {
            delete[] _list;
            return;
        }

        T* newBuffer = new T[_size];

        for (unsigned int i = 0; i < _size; ++i)
            newBuffer[i] = _list[i + 1];

        delete[] _list;
        _list = newBuffer;
    }

    typedef T* iterator;

    iterator erase(iterator &itr)
    {
        if (empty())
            return NULL;

        --_size;
        if (empty())
        {
            delete[] _list;
            return NULL;
        }

        T* newBuffer = new T[_size];

        bool sum = false;
        unsigned int pos = 0;
        for (unsigned int i = 0; i < _size; ++i)
        {
            if (_list + i == itr)
            {
                sum = true;
                pos = i;
            }

            if (sum)
                newBuffer[i] = _list[i + 1];
            else
                newBuffer[i] = _list[i];
        }

        delete[] _list;
        _list = newBuffer;

        itr = _list + pos;

        return itr;
    }

    inline iterator begin() { return (empty() ? NULL : _list); }
    inline iterator end() { return (empty() ? NULL : _list + _size); }
    
    void clear() 
    {
        if (_list)
            delete[] _list;
        _list = NULL;
        _size = 0;
    }
    

    inline bool empty() { return !_size; }
    inline unsigned int size() { return _size; }
private:
    T* _list;
    unsigned int _size;
};

#endif
