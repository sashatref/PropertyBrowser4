#include "idecoratorbase.h"


namespace PropertyBrowser3Qt
{
void IDecoratorBase::propertyInfoMap(PropertyInfoMapType &m, const QVariant &_v)
{
    m_val = _v;
    propertyInfoMap(m);
}

void IDecoratorBase::getListItemName(QString &_text, int _index, const QVariant &_v)
{
    m_val = _v;
    getListItemName(_text, _index);
}

bool IDecoratorBase::checkObject(QString &_errorStr, const QVariant &_v) const
{
    m_val = _v;
    return checkObject(_errorStr);
}

const QVariant &IDecoratorBase::getValue() const
    {
        return m_val;
    }
}

