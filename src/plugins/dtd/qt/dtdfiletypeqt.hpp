#include "bongqt_dtd_export.hpp"

#include <filetypeqt.hpp>
#include <dtdfiletype.h>

class BONGQT_DTD_EXPORT DtdFileTypeQt : public FileTypeQt
{
public:
    DtdFileTypeQt();
    ~DtdFileTypeQt();
};