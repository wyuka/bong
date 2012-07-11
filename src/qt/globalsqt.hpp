#ifndef __GLOBALS_QT_H__
#define __GLOBALS_QT_H__

#include "bongqt_export.hpp"

#include <QtCore/QtCore>

extern "C"
{
    #include <glib-object.h>
}

BONGQT_EXPORT gchar* qstringToGchar(QString &text);

#endif // __GLOBALS_QT_H__