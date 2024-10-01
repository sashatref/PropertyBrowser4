#include "project_pch.h"
#include "colorpropertyitem.h"


namespace PropertyBrowser3Qt
{

ColorPropertyItem::ColorPropertyItem():
    AbstractPropertyItem(QVariant::Color)
{

}

QWidget *ColorPropertyItem::createEditor(QWidget *_parent)
{
    QColorDialog *editor = new QColorDialog(_parent);
    editor->setOption(QColorDialog::ShowAlphaChannel);
    return editor;
}

void ColorPropertyItem::setEditorData(QWidget *_widget)
{
    QColorDialog *editor = static_cast<QColorDialog*>(_widget);
    editor->setCurrentColor(getValue().value<QColor>());
}

void ColorPropertyItem::saveEditorData(QWidget *_widget)
{
    setValue(static_cast<QColorDialog*>(_widget)->currentColor());
}

bool ColorPropertyItem::checkItem()
{
    if(getRequried() && getValue().toString().trimmed().isEmpty())
    {
        return false;
    }
    return true;
}

}
