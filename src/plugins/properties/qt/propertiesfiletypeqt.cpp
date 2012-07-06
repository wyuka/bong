#include "propertiesfiletypeqt.hpp"

PropertiesFileTypeQt::PropertiesFileTypeQt()
{
     m_fileType = properties_file_type_new();
}

PropertiesFileTypeQt::~PropertiesFileTypeQt()
{
    //g_object_unref(m_fileType);
}