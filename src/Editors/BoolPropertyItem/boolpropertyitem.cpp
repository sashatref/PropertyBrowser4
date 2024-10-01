#include "project_pch.h"
#include "boolpropertyitem.h"

namespace PropertyBrowser3Qt
{

BoolPropertyItem::BoolPropertyItem():
    AbstractPropertyItem(QVariant::Bool)
{
}

QWidget *BoolPropertyItem::createEditor(QWidget *_parent)
{
    QCheckBox *check = new QCheckBox(_parent);
    check->setEnabled(!m_isReadOnly);

    connect(check, &QCheckBox::stateChanged, this, [this](int _state)
    {
        setValue(_state == Qt::Checked);
    });

    connect(this, &BoolPropertyItem::onSetValue, check, [this, check](const QVariant &_val)
    {
        check->setCheckState(_val.toBool() ? Qt::Checked : Qt::Unchecked);
    });

    return check;
}

void BoolPropertyItem::setEditorData(QWidget *_widget)
{
    QCheckBox *check = static_cast<QCheckBox*>(_widget);
    if(!check) return;
    check->setChecked(getValue().toBool());
}

void BoolPropertyItem::saveEditorData(QWidget *_widget)
{
    QCheckBox *check = static_cast<QCheckBox*>(_widget);
    if(!check) return;

    bool value = check->isChecked();

    if(value != getValue().toBool())
    {
        setValue(QVariant::fromValue(value));
    }
}

void BoolPropertyItem::updateTextValue()
{
    QCheckBox *check = static_cast<QCheckBox*>(getPermanentWidget());
    if(!check) return;

    check->setCheckState(getValue().toBool() ? Qt::Checked : Qt::Unchecked);
}


void BoolPropertyItem::nonEditorPaint(QPainter * /*_painter*/, const QStyleOptionViewItem &/*_option*/)
{
//    QCheckBox *check = new QCheckBox();
//    check->setChecked(getValue().toBool());

//    QPixmap pixmap = check->grab();

//    int yOffset = (_option.rect.height() - pixmap.height()) / 2;

//    _painter->drawPixmap(_option.rect.x(),
//                         _option.rect.y() + yOffset,
//                         pixmap.width(),
//                         pixmap.height(),
//                         pixmap);
}

bool BoolPropertyItem::isPermanent() const
{
    return true;
}

void BoolPropertyItem::onSetReadOnly(QWidget * /*_widget*/, bool _isReadOnly)
{
    QCheckBox *check = static_cast<QCheckBox*>(getPermanentWidget());
    if(!check) return;
    check->setEnabled(!_isReadOnly);
}

bool BoolPropertyItem::isSpecialReadOnlyMode() const
{
    return true;
}



}
