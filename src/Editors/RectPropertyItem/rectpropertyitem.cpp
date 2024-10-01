#include "rectpropertyitem.h"
#include "propertybrowser3.h"
#include "propertybrowser3_p.h"
#include "interfacetool.h"
#include "../editorproperties.h"

RectPropertyItem::RectPropertyItem()
{

}

RectPropertyItem::~RectPropertyItem()
{
    qDeleteAll(m_subPropMap);
}


QWidget *RectPropertyItem::createEditor(QWidget *_parent)
{
    Q_UNUSED(_parent)
    return 0;
}


void RectPropertyItem::setEditorData(QWidget *_widget)
{
    Q_UNUSED(_widget)
}

void RectPropertyItem::saveEditorData(QWidget *_widget)
{
    Q_UNUSED(_widget)
}

void RectPropertyItem::updateGeometry(QWidget *_widget, const QStyleOptionViewItem _option)
{
    Q_UNUSED(_widget)
    Q_UNUSED(_option)
}

void RectPropertyItem::updateTextValue()
{
    using namespace PropertyBrowser3Qt;

    AbstractPropertyItem::updateTextValue();

    if(m_treeItem->childCount() == 0)
    {
        PropertyInfoMapType map;
        map["x"] = PropertyInfo(tr("X"));
        map["x"].m_properties[IntProperty::SpinBoxMinimum] = -100000;
        map["x"].m_properties[IntProperty::SpinBoxMaximum] = 100000;
        map["y"] = PropertyInfo(tr("Y"));
        map["y"].m_properties[IntProperty::SpinBoxMinimum] = -100000;
        map["y"].m_properties[IntProperty::SpinBoxMaximum] = 100000;
        map["width"] = PropertyInfo(tr("Ширина"));
        map["width"].m_properties[IntProperty::SpinBoxMinimum] = -100000;
        map["width"].m_properties[IntProperty::SpinBoxMaximum] = 100000;
        map["height"] = PropertyInfo(tr("Высота"));
        map["height"].m_properties[IntProperty::SpinBoxMinimum] = -100000;
        map["height"].m_properties[IntProperty::SpinBoxMaximum] = 100000;

        QStringList items = QStringList()
                << "x"
                << "y"
                << "width"
                << "height";

        QRect rect = getValue().toRect();

        for(int i = 0 ; i < items.size(); i++)
        {
            const QString key = items.at(i);

            AbstractPropertyItem *addedItem = PropertyBrowser3::addItem(
                        key,
                        QVariant::Int,
                        m_treeItem,
                        map[key],
                        QMetaProperty());
            connect(addedItem, &AbstractPropertyItem::valueChanged, this, &RectPropertyItem::onPropertyChanged);

            addedItem->updateTextValue();
            m_subPropMap[key] = addedItem;
        }

        m_subPropMap["x"]->setValue(rect.x());
        m_subPropMap["y"]->setValue(rect.y());
        m_subPropMap["width"]->setValue(rect.width());
        m_subPropMap["height"]->setValue(rect.height());


        for(int i = 0 ; i < map.size(); i++)
        {
            const QString key = map.keys().at(i);
            m_subPropMap[key]->updateTextValue();
        }
    }
}

void RectPropertyItem::onPropertyChanged(const QString &_propertyName, const QVariant &_propertyValue)
{
    QRect oldValue = getValue().toRect();
    QRect newValue = oldValue;

    if(_propertyName == "x")
    {
        newValue = QRect(_propertyValue.toInt(),
                         oldValue.y(),
                         oldValue.width(),
                         oldValue.height());

    } else if(_propertyName == "y")
    {
        newValue = QRect(oldValue.x(),
                        _propertyValue.toInt(),
                         oldValue.width(),
                         oldValue.height());
    } else if(_propertyName == "width")
    {
        newValue = QRect(oldValue.x(),
                         oldValue.y(),
                         _propertyValue.toInt(),
                         oldValue.height());
    } else if(_propertyName == "height")
    {
        newValue = QRect(oldValue.x(),
                         oldValue.y(),
                         oldValue.width(),
                         _propertyValue.toInt());
    }

    setValue(newValue);

    emit valueChanged(getPropertyName(), newValue);
    emit valueChanged2(getPropertyName(), newValue, oldValue);

    AbstractPropertyItem::updateTextValue();
}
