#pragma once

#include "BL_Core.h"

namespace BassLive
{
    template<class T>
    class Buffer
    {
    public:
        //================================================================
        Buffer()
        {
            bufferSize = 1;
            buffer = new T[bufferSize];
        }

        ~Buffer()
        {
            delete[] buffer;
        }

        //================================================================
        UInt size() const
        {
            return bufferSize;
        }

        void resize(UInt size)
        {
            T* bufferToDelete = buffer;

            bufferSize = size > 0 ? size : 1;
            buffer = new T[bufferSize];

            delete[] bufferToDelete;
        }

        //================================================================
        T& operator[](UInt i)
        {
            return (i < bufferSize) ? buffer[i] : buffer[0];
        }

        const T& operator[](UInt i) const
        {
            return (i < bufferSize) ? buffer[i] : buffer[0];
        }
        
    private:
        //================================================================
        UInt bufferSize;
        T* buffer;
    };
}
