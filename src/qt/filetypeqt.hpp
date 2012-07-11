#ifndef __FILETYPE_QT_H__
#define __FILETYPE_QT_H__

#include "bongqt_export.hpp"

struct _FileType;

class BONGQT_EXPORT FileTypeQt
{
public:
    FileTypeQt()
    {
        m_fileType = 0;
    }

    _FileType* getPointer()
    {
        return m_fileType;
    }

protected:
    _FileType* m_fileType;
};

#endif // __FILETYPE_QT_H__