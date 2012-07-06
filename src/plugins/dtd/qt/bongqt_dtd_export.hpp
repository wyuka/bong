#ifndef BONGQT_DTD_EXPORT_H
#define BONGQT_DTD_EXPORT_H

#include <QtCore/QtGlobal>

#ifndef BONGQT_DTD_EXPORT
# if defined(BUILDING_BONGQT)
/* We are building this library */
#  define BONGQT_DTD_EXPORT Q_DECL_EXPORT
# else
/* We are using this library */
#  define BONGQT_DTD_EXPORT Q_DECL_IMPORT
# endif
#endif

#endif // BONGQT_DTD_EXPORT_H
