#include "project_pch.h"
#include "defaultpropertyitem.h"

#include "propertybrowser3.h"
#include "propertybrowser3_p.h"
#include "interfacetool.h"


DefaultPropertyItem::DefaultPropertyItem() :
    AbstractPropertyItem(QVariant::Invalid)
{

}

DefaultPropertyItem::~DefaultPropertyItem()
{
    qDeleteAll(m_subPropMap);
}

QWidget *DefaultPropertyItem::createEditor(QWidget * /*_parent*/)
{
    return 0;
}

void DefaultPropertyItem::setEditorData(QWidget * /*_widget*/)
{
    m_propertyType = getValue().userType();
}

void DefaultPropertyItem::saveEditorData(QWidget * /*_widget*/)
{

}

void DefaultPropertyItem::updateTextValue()
{
    using namespace PropertyBrowser3Qt;

    AbstractPropertyItem::updateTextValue();

    //добавление элементов дерева для вложенных классов
    if(m_isExpandable && m_treeItem->childCount() == 0)
    {
        QVariant val = getValue();

        QObject* object = getValue().value<QObject*>();
        IGadget* gadget = getValue().value<IGadget*>();

        if(!object && !gadget) return;

        PropertyInfoMapType propertyInfoMap = InterfaceTool::getPropInfoMap(val);
        const QMetaObject *mo = VariantHelper::getMetaObject(val);

        for(int i = mo->propertyOffset(), count = mo->propertyCount(); i < count; i++)
        {
            QMetaProperty property = mo->property(i);
            int objectType = property.userType();
            QString propertyName = property.name();

            AbstractPropertyItem *addedItem = PropertyBrowser3::addItem(
                        propertyName,
                        objectType,
                        m_treeItem,
                        propertyInfoMap[propertyName],
                        property);
            connect(addedItem, &AbstractPropertyItem::valueChanged, this, &DefaultPropertyItem::onPropertyChanged);

            if(object)
            {
                addedItem->setValue(property.read(object));
            } else if(gadget)
            {
                addedItem->setValue(property.readOnGadget(gadget));
            }

            addedItem->updateTextValue();
            m_subPropMap[propertyName] = addedItem;
        }
    }
}

void DefaultPropertyItem::onPropertyChanged(const QString &_propertyName, const QVariant &_propertyValue)
{
    QVariant oldValue = getValue();
    oldValue.detach();

    QVariant var = QVariant::fromValue(getValue());
    QObject* object = var.value<QObject*>();
    if(object)
    {
        object->setProperty(_propertyName.toStdString().c_str(), _propertyValue);
    }
    IGadget* gad = var.value<IGadget*>();
    if(gad)
    {
        gad->setProperty(_propertyName, _propertyValue);
    }

    setValue(var);

    emit valueChanged(getPropertyName(), var);
    emit valueChanged2(getPropertyName(), var, oldValue);

    AbstractPropertyItem::updateTextValue();
}
