#ifndef BONGQT_EXPORT_H
#define BONGQT_EXPORT_H

#include <QtCore/QtGlobal>

#ifndef BONGQT_EXPORT
# if defined(BUILDING_BONGQT)
/* We are building this library */
#  define BONGQT_EXPORT Q_DECL_EXPORT
# else
/* We are using this library */
#  define BONGQT_EXPORT Q_DECL_IMPORT
# endif
#endif

#endif // BONGQT_EXPORT_H
