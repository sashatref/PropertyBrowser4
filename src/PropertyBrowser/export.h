#pragma once

#include <QtCore/qglobal.h>

#ifdef PropertyBrowser3_BUILD_STATIC
    #define PROPERTYBROWSER3_EXPORT
#else
    #if defined(PROPERTYBROWSER3)
        #define PROPERTYBROWSER3_EXPORT Q_DECL_EXPORT
    #else
        #define PROPERTYBROWSER3_EXPORT Q_DECL_IMPORT
    #endif
#endif
