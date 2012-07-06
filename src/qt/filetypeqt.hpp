#include "bongqt_export.hpp"

#include <filetype.h>

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