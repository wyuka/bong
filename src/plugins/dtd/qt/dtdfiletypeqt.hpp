#ifndef __DTD_FILETYPE_QT__
#define __DTD_FILETYPE_QT__

#include "bongqt_dtd_export.hpp"

#include <filetypeqt.hpp>

extern "C"
{
    #include <dtdfiletype.h>
}

class BONGQT_DTD_EXPORT DtdFileTypeQt : public FileTypeQt
{
public:
    DtdFileTypeQt();
    ~DtdFileTypeQt();
};

#endif // __DTD_FILETYPE_QT__