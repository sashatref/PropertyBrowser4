#pragma once

#include "propertyinfo.h"
#include "export.h"

/*!
 * \brief The IPropertyBrowserBase class
 */

namespace PropertyBrowser3Qt
{

class PROPERTYBROWSER3_EXPORT IPropertyBrowserBase
{
public:
    virtual void propertyInfoMap(PropertyInfoMapType &m) const
    {
        Q_UNUSED(m);
    }

    virtual void getListItemName(QString &_text, int _index) const
    {
        Q_UNUSED(_text);
        Q_UNUSED(_index);
    }

    virtual bool checkObject(QString &_errorStr) const
    {
        Q_UNUSED(_errorStr);
        return true;
    }

    virtual ~IPropertyBrowserBase() = default;
};

}
