#include "project_pch.h"
#include "fontpropertyitem.h"

FontPropertyItem::FontPropertyItem() :
    AbstractPropertyItem(QVariant::Font)
{

}

QWidget *FontPropertyItem::createEditor(QWidget *_parent)
{
    QFontDialog *editor = new QFontDialog(_parent);
    return editor;
}

void FontPropertyItem::setEditorData(QWidget *_widget)
{
    QFontDialog *editor = static_cast<QFontDialog*>(_widget);
    editor->setCurrentFont(getValue().value<QFont>());
}

void FontPropertyItem::saveEditorData(QWidget *_widget)
{
    QFontDialog *editor = static_cast<QFontDialog*>(_widget);
    setValue(QVariant::fromValue(editor->currentFont()));
}

void FontPropertyItem::updateTextValue()
{
    m_treeItem->setText(1, getValue().toString());
}


bool FontPropertyItem::isDialog() const
{
    return true;
}
