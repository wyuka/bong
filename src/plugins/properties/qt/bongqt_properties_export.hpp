#ifndef BONGQT_PROPERTIES_EXPORT_H
#define BONGQT_PROPERTIES_EXPORT_H

#include <QtCore/QtGlobal>

#ifndef BONGQT_PROPERTIES_EXPORT
# if defined(BUILDING_BONGQT)
/* We are building this library */
#  define BONGQT_PROPERTIES_EXPORT Q_DECL_EXPORT
# else
/* We are using this library */
#  define BONGQT_PROPERTIES_EXPORT Q_DECL_IMPORT
# endif
#endif

#endif // BONGQT_PROPERTIES_EXPORT_H
