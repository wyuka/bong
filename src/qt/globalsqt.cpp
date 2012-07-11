#include "globalsqt.hpp"
#include "bongqt_export.hpp"

#include <glib-object.h>
#include <QtCore/QtCore>

extern "C"
{
    #include <glib-object.h>
}

gchar* qstringToGchar(QString &text)
{
    gchar *output = NULL;
    if (text.isEmpty())
        return NULL;
    QByteArray arr = text.toUtf8();
    output = g_strdup(arr.constData());
    return output;
}