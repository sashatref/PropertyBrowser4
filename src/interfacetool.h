#pragma once

#include "propertyinfo.h"
#include "ipropertyinfomap.h"
#include "export.h"

namespace PropertyBrowser3Qt
{
    class IDecoratorBase;



    namespace InterfaceTool
    {
        PropertyInfoMapType PROPERTYBROWSER3_EXPORT getPropInfoMap(const QVariant &_val);
        IPropertyBrowserBase PROPERTYBROWSER3_EXPORT *getIPropertyBase(const QVariant &_val);

        QSharedPointer<IDecoratorBase> getIDecoratorBase(const QVariant &_val);

        void PROPERTYBROWSER3_EXPORT getListItemName(const QVariant &_val, int _index, QString &_text);
        bool PROPERTYBROWSER3_EXPORT checkObject(const QVariant &_variant, QWidget *_parent);


        void applyItemAsGroup(QTreeWidgetItem *_item);
        void applyItemAsValue(QTreeWidgetItem *_item);
    }
}


