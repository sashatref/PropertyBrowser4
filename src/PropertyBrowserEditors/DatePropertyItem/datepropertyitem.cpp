#include "project_pch.h"
#include "datepropertyitem.h"

DatePropertyItem::DatePropertyItem() :
    AbstractPropertyItem(QVariant::Date)
{
}

QWidget *DatePropertyItem::createEditor(QWidget *_parent)
{
    QDateEdit *editor = new QDateEdit(_parent);
    editor->setCalendarPopup(true);
    return editor;
}

void DatePropertyItem::setEditorData(QWidget *_widget)
{
    QDateEdit *editor = static_cast<QDateEdit*>(_widget);
    editor->setDate(getValue().toDate());
}

void DatePropertyItem::saveEditorData(QWidget *_widget)
{
    QDateEdit *editor = static_cast<QDateEdit*>(_widget);
    setValue(QVariant::fromValue(editor->date()));
}

void DatePropertyItem::updateTextValue()
{
    m_treeItem->setText(1, QLocale().toString(getValue().toDate(), QLocale::ShortFormat));
}
