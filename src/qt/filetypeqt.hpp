#ifndef __FILETYPE_QT_H__
#define __FILETYPE_QT_H__

#include "bongqt_export.hpp"

extern "C"
{
    #include <filetype.h>
}

class BONGQT_EXPORT FileTypeQt
{
public:
    FileTypeQt()
    {
        m_fileType = 0;
    }
    FileType* getPointer()
    {
        return m_fileType;
    }

protected:
    FileType* m_fileType;
};

#endif // __FILETYPE_QT_H__