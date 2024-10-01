#pragma once

#include "../ipropertyinfomap.h"

namespace PropertyBrowser3Qt
{

class PROPERTYBROWSER3_EXPORT IDecoratorBase : public IPropertyBrowserBase
{
public:
    using IPropertyBrowserBase::propertyInfoMap;
    using IPropertyBrowserBase::getListItemName;
    using IPropertyBrowserBase::checkObject;

    void propertyInfoMap(PropertyInfoMapType &m, const QVariant &_v);
    void getListItemName(QString &_text, int _index, const QVariant &_v);
    bool checkObject(QString &_errorStr, const QVariant &_v) const;

protected:
    const QVariant &getValue() const;

private:
    mutable QVariant m_val;
};

}

