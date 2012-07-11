#ifndef __PROPERTIES_FILETYPE_QT__
#define __PROPERTIES_FILETYPE_QT__

#include "bongqt_properties_export.hpp"

#include <filetypeqt.hpp>

class BONGQT_PROPERTIES_EXPORT PropertiesFileTypeQt : public FileTypeQt
{
public:
    PropertiesFileTypeQt();
    ~PropertiesFileTypeQt();
};

#endif // __PROPERTIES_FILETYPE_QT__