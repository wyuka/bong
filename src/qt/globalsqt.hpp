#ifndef __GLOBALS_QT_H__
#define __GLOBALS_QT_H__

#include "bongqt_export.hpp"

extern "C"
{
    #include <glib-object.h>
}
#include <QtCore/QtCore>


BONGQT_EXPORT gchar* qstringToGchar(QString &text);
BONGQT_EXPORT void initBongQt();

#endif // __GLOBALS_QT_H__