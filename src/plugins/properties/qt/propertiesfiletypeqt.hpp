#include "bongqt_properties_export.hpp"

#include <filetypeqt.hpp>
#include <propertiesfiletype.h>

class BONGQT_PROPERTIES_EXPORT PropertiesFileTypeQt : public FileTypeQt
{
public:
    PropertiesFileTypeQt();
    ~PropertiesFileTypeQt();
};