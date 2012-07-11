#include "dtdfiletypeqt.hpp"

extern "C"
{
    #include <dtdfiletype.h>
}

DtdFileTypeQt::DtdFileTypeQt()
{
     m_fileType = dtd_file_type_new();
}

DtdFileTypeQt::~DtdFileTypeQt()
{
}