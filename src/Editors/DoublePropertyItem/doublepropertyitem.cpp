#include "doublepropertyitem.h"

#include "../editorproperties.h"

DoublePropertyItem::DoublePropertyItem():
    AbstractPropertyItem(QVariant::Double)
{
    using namespace PropertyBrowser3Qt;

    m_propertiesMap[DoubleProperty::SpinBoxMinimum] = 0;
    m_propertiesMap[DoubleProperty::SpinBoxMaximum] = 100000;
    m_propertiesMap[DoubleProperty::Precision] = 2;
}

QWidget *DoublePropertyItem::createEditor(QWidget *_parent)
{
    using namespace PropertyBrowser3Qt;

    QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox(_parent);
    doubleSpinBox->setMinimum(m_propertiesMap[DoubleProperty::SpinBoxMinimum].toDouble());
    doubleSpinBox->setMaximum(m_propertiesMap[DoubleProperty::SpinBoxMaximum].toDouble());
    doubleSpinBox->setDecimals(m_propertiesMap[DoubleProperty::Precision].toInt());

    connect(doubleSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [this](double _val)
    {
        setValue(_val);
    });

    return doubleSpinBox;
}

void DoublePropertyItem::setEditorData(QWidget *_widget)
{
    QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(_widget);
    doubleSpinBox->setValue(getValue().toDouble());
}

void DoublePropertyItem::saveEditorData(QWidget *_widget)
{
    QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(_widget);
    setValue(QVariant::fromValue(doubleSpinBox->value()));
}

void DoublePropertyItem::updateTextValue()
{
    using namespace PropertyBrowser3Qt;

    m_treeItem->setText(1, QString::number(getValue().toDouble(), 'f', m_propertiesMap[DoubleProperty::Precision].toInt()));
}

bool DoublePropertyItem::isPermanent() const
{
    return false;
}

//void DoublePropertyItem::updateGeometry(QWidget *_widget, const QStyleOptionViewItem _option)
//{
//    _widget->setGeometry(_option.rect.x(), _option.rect.y(), _option.rect.width() / 2, _option.rect.height());
//}
