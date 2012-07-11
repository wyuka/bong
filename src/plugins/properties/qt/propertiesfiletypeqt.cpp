#include "propertiesfiletypeqt.hpp"

extern "C"
{
    #include <propertiesfiletype.h>
}

PropertiesFileTypeQt::PropertiesFileTypeQt()
{
     m_fileType = properties_file_type_new();
}

PropertiesFileTypeQt::~PropertiesFileTypeQt()
{
}