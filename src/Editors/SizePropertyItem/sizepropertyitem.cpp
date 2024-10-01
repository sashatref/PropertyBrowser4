#include "sizepropertyitem.h"
#include "../editorproperties.h"
#include "../../propertybrowser3.h"

SizePropertyItem::SizePropertyItem()
{

}

SizePropertyItem::~SizePropertyItem()
{
    qDeleteAll(m_subPropMap);
}

QWidget *SizePropertyItem::createEditor(QWidget *_parent)
{
    Q_UNUSED(_parent)
    return 0;
}

void SizePropertyItem::setEditorData(QWidget *_widget)
{
    Q_UNUSED(_widget)
}

void SizePropertyItem::saveEditorData(QWidget *_widget)
{
    Q_UNUSED(_widget)
}

void SizePropertyItem::updateTextValue()
{
    using namespace PropertyBrowser3Qt;

    AbstractPropertyItem::updateTextValue();

    if(m_treeItem->childCount() == 0)
    {
        PropertyInfoMapType map;
        map["width"] = PropertyInfo(tr("Ширина"));
        map["width"].m_properties[IntProperty::SpinBoxMinimum] = -100000;
        map["width"].m_properties[IntProperty::SpinBoxMaximum] = 100000;
        map["height"] = PropertyInfo(tr("Высота"));
        map["height"].m_properties[IntProperty::SpinBoxMinimum] = -100000;
        map["height"].m_properties[IntProperty::SpinBoxMaximum] = 100000;

        QStringList items = QStringList()
                << "width"
                << "height";

        QSize size = getValue().toSize();

        for(int i = 0 ; i < items.size(); i++)
        {
            const QString key = items.at(i);

            AbstractPropertyItem *addedItem = PropertyBrowser3::addItem(
                        key,
                        QVariant::Int,
                        m_treeItem,
                        map[key],
                        QMetaProperty());
            connect(addedItem, &AbstractPropertyItem::valueChanged, this, &SizePropertyItem::onPropertyChanged);

            addedItem->updateTextValue();
            m_subPropMap[key] = addedItem;
        }

        m_subPropMap["width"]->setValue(size.width());
        m_subPropMap["height"]->setValue(size.height());


        for(int i = 0 ; i < map.size(); i++)
        {
            const QString key = map.keys().at(i);
            m_subPropMap[key]->updateTextValue();
        }
    }
}

void SizePropertyItem::onPropertyChanged(const QString &_propertyName, const QVariant &_propertyValue)
{
    QSize oldValue = getValue().toSize();
    QSize newValue = oldValue;

    if(_propertyName == "width")
    {
        newValue = QSize(_propertyValue.toInt(),
                         oldValue.height());
    } else if(_propertyName == "height")
    {
        newValue = QSize(oldValue.width(),
                         _propertyValue.toInt());
    }

    setValue(newValue);

    emit valueChanged(getPropertyName(), newValue);
    emit valueChanged2(getPropertyName(), newValue, oldValue);

    AbstractPropertyItem::updateTextValue();
}
