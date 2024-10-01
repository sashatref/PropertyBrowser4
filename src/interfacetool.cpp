#include "project_pch.h"
#include "interfacetool.h"
#include "Decorator/decoratorfactory.h"
#include "Decorator/idecoratorbase.h"


namespace PropertyBrowser3Qt
{
    namespace InterfaceTool
    {

    IPropertyBrowserBase *getIPropertyBase(const QVariant &_val)
    {
        IPropertyBrowserBase *base = VariantHelper::castObject<IPropertyBrowserBase>(_val);
        if(base)
        {
            return base;
        }

        return base;
    }

    PropertyInfoMapType getPropInfoMap(const QVariant &_val)
    {
        PropertyInfoMapType map;

        QSharedPointer<IDecoratorBase> dBase = getIDecoratorBase(_val);
        if(dBase)
        {
            dBase->propertyInfoMap(map, _val);
            return map;
        }

        IPropertyBrowserBase *base = getIPropertyBase(_val);
        if(base)
        {
            base->propertyInfoMap(map);
            return map;
        }

        return map;
    }



    void getListItemName(const QVariant &_val, int _index, QString &_text)
    {
        QSharedPointer<IDecoratorBase> dBase = getIDecoratorBase(_val);
        if(dBase)
        {
            dBase->getListItemName(_text, _index, _val);
            return;
        }

        IPropertyBrowserBase *base = getIPropertyBase(_val);
        if(base)
        {
            base->getListItemName(_text, _index);
            return;
        }
    }

    bool checkObject(const QVariant &_variant, QWidget *_parent)
    {
        QSharedPointer<IDecoratorBase> dBase = getIDecoratorBase(_variant);
        if(dBase)
        {
            QString errorStr;
            if(!dBase->checkObject(errorStr, _variant))
            {
                QMessageBox::warning(_parent, _parent->tr("Object check error"), errorStr);
                return false;
            }
            return true;
        }

        IPropertyBrowserBase *base = getIPropertyBase(_variant);
        if(base)
        {
            QString errorStr;
            if(!base->checkObject(errorStr))
            {
                QMessageBox::warning(_parent, _parent->tr("Object check error"), errorStr);
                return false;
            }

            return true;
        }

        return true;
    }

    QSharedPointer<IDecoratorBase> getIDecoratorBase(const QVariant &_val)
    {
        return DecoratorFactory::ins().create(_val.userType());
    }

    void applyItemAsGroup(QTreeWidgetItem *_item)
    {
        QFont f = _item->font(0);
        f.setBold(true);
        _item->setFont(0, f);

        //_item->setTextColor(0, QColor(0x800000));
    }

    void applyItemAsValue(QTreeWidgetItem * /*_item*/)
    {
        //_item->setTextColor(1, Qt::blue);
    }

    }
}


