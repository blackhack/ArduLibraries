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
        _preAlloc = 0;
    }

    ~SimpleList()
    {
        delete[] _list;
        _list = NULL;
        _size = 0;
        _preAlloc = 0;
    }

    void push_back(T obj)
    {
        ++_size;

        bool alloc = (_preAlloc < _size);

        T* newBuffer = alloc ? new T[_size] : _list;

        if (alloc)
        {
            for (unsigned int i = 0; i < _size - 1; ++i)
                newBuffer[i] = _list[i];
        }

        newBuffer[_size - 1] = obj;

        if (alloc)
        {
            delete[] _list;
            _list = newBuffer;
        }
    }

    void push_front(T obj)
    {
        ++_size;

        bool alloc = (_preAlloc < _size);

        T* newBuffer = alloc ? new T[_size] : _list;

        for (unsigned int i = _size - 1; i > 0; --i)
            newBuffer[i] = _list[i - 1];
        newBuffer[0] = obj;


        if (alloc)
        {
            delete[] _list;
            _list = newBuffer;
        }
    }

    void pop_back()
    {
        if (empty())
            return;

        --_size;
        if (empty())
        {
            if (!_preAlloc)
                delete[] _list;
            return;
        }

        bool alloc = (!_preAlloc || _preAlloc < _size + 1);

        T* newBuffer = alloc ? new T[_size] : _list;

        if (alloc)
        {
            for (unsigned int i = 0; i < _size; ++i)
                newBuffer[i] = _list[i];

            delete[] _list;
            _list = newBuffer;
        }
    }

    void pop_front()
    {
        if (empty())
            return;

        --_size;
        if (empty())
        {
            if (!_preAlloc)
                delete[] _list;
            return;
        }

        bool alloc = (!_preAlloc || _preAlloc < _size + 1);

        T* newBuffer = alloc ? new T[_size] : _list;

        for (unsigned int i = 0; i < _size; ++i)
            newBuffer[i] = _list[i + 1];

        if (alloc)
        {
            delete[] _list;
            _list = newBuffer;
        }
    }

    void reserve(unsigned int size)
    {
        if (size <= _size)
            return;

        _preAlloc = size;

        T* newBuffer = new T[_preAlloc];

        for (unsigned int i = 0; i < _size; ++i)
            newBuffer[i] = _list[i];

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
            if (!_preAlloc)
                delete[] _list;
            return NULL;
        }

        bool alloc = (!_preAlloc || _preAlloc < _size + 1);

        T* newBuffer = alloc ? new T[_size] : _list;

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

        if (alloc)
        {
            delete[] _list;
            _list = newBuffer;
        }

        itr = _list + pos;

        return itr;
    }

    inline iterator begin() { return (empty() ? NULL : _list); }
    inline iterator end() { return (empty() ? NULL : _list + _size); }

    void clear()
    {
        if (_list && !_preAlloc)
        {
            delete[] _list;
            _list = NULL;
        }
        _size = 0;
    }

    inline bool empty() { return !_size; }
    inline unsigned int size() { return _size; }
    inline unsigned int capacity() { return (_size > _preAlloc ? _size : _preAlloc); }
private:
    T* _list;
    unsigned int _size;
    unsigned int _preAlloc;
};

#endif
