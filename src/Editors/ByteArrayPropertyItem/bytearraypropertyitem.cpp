#include "project_pch.h"
#include "bytearraypropertyitem.h"
#include "bytearrayeditor.h"

#include "../editorproperties.h"

namespace PropertyBrowser3Qt
{

ByteArrayPropertyItem::ByteArrayPropertyItem():
    AbstractPropertyItem(QVariant::ByteArray)
{
    m_propertiesMap[ByteArrayProperty::EditorSize] = QSize(770,500);
    m_propertiesMap[ByteArrayProperty::ArraySize] = 8;
    m_propertiesMap[ByteArrayProperty::DataSizeEditable] = false;
}

QWidget *ByteArrayPropertyItem::createEditor(QWidget *_parent)
{
    ByteArrayEditor *editor = new ByteArrayEditor(_parent);

    editor->setDataSizeEditable(m_propertiesMap[ByteArrayProperty::DataSizeEditable].toBool());
    editor->setDataSize(m_propertiesMap[ByteArrayProperty::ArraySize].toInt());
    return editor;
}

void ByteArrayPropertyItem::setEditorData(QWidget *_widget)
{
    ByteArrayEditor *editor = static_cast<ByteArrayEditor*>(_widget);

    editor->setData(getValue().toByteArray());
}

void ByteArrayPropertyItem::saveEditorData(QWidget *_widget)
{
    ByteArrayEditor *editor = static_cast<ByteArrayEditor*>(_widget);

    setValue(editor->getData());
}

void ByteArrayPropertyItem::updateGeometry(QWidget *_widget, const QStyleOptionViewItem)
{
    QSize size = m_propertiesMap[ByteArrayProperty::EditorSize].toSize();
    _widget->setGeometry(0,0, size.width(), size.height());
    WidgetHelper::setWidgetOnScreenCenter(_widget, _widget->parentWidget());
}

void ByteArrayPropertyItem::updateTextValue()
{
    QString value;
    QByteArray ba = getValue().toByteArray();

    for(int i = 0 ; i < ba.size(); i++)
    {
        value += QString::number(ba.at(i), 16).right(2);
        if(i != ba.size() - 1)
        {
            value += ", ";
        }
    }

    getTreeItem()->setText(1, value);
}

bool ByteArrayPropertyItem::checkItem()
{
    if(getRequried() && getValue().toByteArray().isEmpty())
    {
        return false;
    }
    return true;
}

bool ByteArrayPropertyItem::isDialog() const
{
    return true;
}

}
