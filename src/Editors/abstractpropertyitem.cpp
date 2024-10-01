#include "project_pch.h"
#include "abstractpropertyitem.h"

#include "propertyinfo.h"

AbstractPropertyItem::AbstractPropertyItem(int _propertyType):
    m_treeItem          (0),
    m_propertiesMap     (),
    m_isExpandable      (false),
    m_propertyName      (),
    m_propertyCaption   (),
    m_group             (),
    m_description       (),
    m_isVisible         (true),
    m_isWarning         (false),
    m_isRequried        (false),
    m_isReadOnly        (false),
    m_propertyType      (_propertyType),
    m_value             (),
    m_oldValue          ()
{

}

void AbstractPropertyItem::initProperty(const QString &_propertyName,
                                        const PropertyInfo &_propInfo,
                                        QTreeWidgetItem *_treeItem,
                                        const QMetaProperty &_metaProperty)
{
    setPropertyName(_propertyName);
    setTreeItem(_treeItem);
    setPropertyCaption(_propInfo.m_caption);
    setDescription(_propInfo.m_description);
    setGroup(_propInfo.m_group);
    setRequried(_propInfo.m_isRequried);
    setVisible(!_propInfo.m_isHidden);
    appendProperties(_propInfo.m_properties);
    setReadOnly(_propInfo.m_isReadonly);
    setExpandable(_propInfo.m_isExpandable);
    m_metaProperty = _metaProperty;
}

bool AbstractPropertyItem::isDialog() const
{
    return false;
}

bool AbstractPropertyItem::isPermanent() const
{
    return false;
}

//void AbstractPropertyItem::updatePermanentWidgetValue()
//{
//    if(!isPermanent()) return;
//    QTreeWidget *tree = m_treeItem->treeWidget();
//    QWidget *widget = tree->itemWidget(m_treeItem, 1);
//    setEditorData(widget);
//}

void AbstractPropertyItem::setWarning(bool _isWarning)
{
    m_isWarning = _isWarning;

    if(m_isWarning)
    {
        m_treeItem->setBackgroundColor(1, QColor(173, 91, 91, 100));
        m_treeItem->setBackgroundColor(0, QColor(173, 91, 91, 100));
    } else
    {
        m_treeItem->setBackground(0, QBrush());
        m_treeItem->setBackground(1, QBrush());
    }
}

bool AbstractPropertyItem::getWarning() const
{
    return m_isWarning;
}

void AbstractPropertyItem::setPropertyName(const QString &_propertyName)
{
    m_propertyName = _propertyName;
}

const QString &AbstractPropertyItem::getPropertyName() const
{
    return m_propertyName;
}

const QString &AbstractPropertyItem::getPropertyCaption() const
{
    return m_propertyCaption.isEmpty() ? m_propertyName : m_propertyCaption;
}

void AbstractPropertyItem::setPropertyCaption(const QString &_caption)
{
    m_propertyCaption = _caption;
    m_treeItem->setText(0, m_propertyCaption == "" ? m_propertyName : m_propertyCaption);
}

int AbstractPropertyItem::getPropertyType() const
{
    return m_propertyType;
}

bool AbstractPropertyItem::getRequried() const
{
    return m_isRequried;
}

const QString &AbstractPropertyItem::getDescription() const
{
    return m_description;
}

void AbstractPropertyItem::setGroup(const QString &_group)
{
    m_group = _group;
}

void AbstractPropertyItem::setReadOnly(bool _isReadOnly)
{
    m_isReadOnly = _isReadOnly;
}

bool AbstractPropertyItem::getReadOnly() const
{
    return m_isReadOnly;
}

void AbstractPropertyItem::setDescription(const QString &_description)
{
    m_description = _description;
}

void AbstractPropertyItem::setRequried(bool _isRequeried)
{
    m_isRequried = _isRequeried;
}

void AbstractPropertyItem::setVisible(bool _isVisible)
{
    m_isVisible = _isVisible;
}

void AbstractPropertyItem::setValue(const QVariant &_value, bool notify)
{
    if(m_value == _value)
    {
        return;
    }

    m_value = _value;
    if(m_isReadOnly) return;
    if(notify)
    {
        emit valueChanged(getPropertyName(), m_value);
        emit valueChanged2(getPropertyName(), m_value, m_oldValue);
    }
    m_oldValue = m_value;
    emit onSetValue(m_value);
}

const QVariant &AbstractPropertyItem::getValue() const
{
    return m_value;
}

void AbstractPropertyItem::setTreeItem(QTreeWidgetItem *_item)
{
    m_treeItem = _item;
    m_treeItem->setText(0, m_propertyCaption.isEmpty() ? m_propertyName : m_propertyCaption);
}

void AbstractPropertyItem::initEmptyEditor()
{
    m_value = QVariant();
    updateTextValue();
}

QTreeWidgetItem* AbstractPropertyItem::getTreeItem() const
{
    return m_treeItem;
}

void AbstractPropertyItem::onSetReadOnly(QWidget *_widget, bool _isReadOnly)
{
    Q_UNUSED(_widget);
    Q_UNUSED(_isReadOnly);
}

bool AbstractPropertyItem::isSpecialReadOnlyMode() const
{
    return false;
}

void AbstractPropertyItem::onSaveEditorGeometry(QWidget *_widget)
{
    Q_UNUSED(_widget);
}

void AbstractPropertyItem::updateGeometry(QWidget *_widget, const QStyleOptionViewItem _option)
{
    Q_UNUSED(_widget);
    Q_UNUSED(_option);
}

void AbstractPropertyItem::updateTextValue()
{
    m_treeItem->setText(1, getValue().toString());
}

void AbstractPropertyItem::nonEditorPaint(QPainter *_painter, const QStyleOptionViewItem &_option)
{
    Q_UNUSED(_painter);
    Q_UNUSED(_option);
}

void AbstractPropertyItem::appendProperties(const QMap<int, QVariant> &_properties)
{
    for(int i = 0 ; i < _properties.keys().size();i++)
    {
        int key = _properties.keys().at(i);
        m_propertiesMap[key] = _properties[key];
    }
}

void AbstractPropertyItem::setExpandable(bool _isExpandable)
{
    m_isExpandable = _isExpandable;
}

void AbstractPropertyItem::setValueText(const QString &_text)
{
    m_treeItem->setText(1, _text);
}

QWidget *AbstractPropertyItem::getPermanentWidget() const
{
    return m_treeItem->treeWidget()->itemWidget(m_treeItem, 1);
}
