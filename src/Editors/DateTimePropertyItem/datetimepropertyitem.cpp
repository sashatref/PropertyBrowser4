#include "project_pch.h"
#include "datetimepropertyitem.h"

DateTimePropertyItem::DateTimePropertyItem() :
    AbstractPropertyItem(QVariant::DateTime)
{

}

QWidget *DateTimePropertyItem::createEditor(QWidget *_parent)
{
    QDateTimeEdit *editor = new QDateTimeEdit(_parent);
    //editor->setCalendarPopup(true);
    return editor;
}

void DateTimePropertyItem::setEditorData(QWidget *_widget)
{
    QDateTimeEdit *editor = static_cast<QDateTimeEdit*>(_widget);
    editor->setDateTime(getValue().toDateTime());
}

void DateTimePropertyItem::saveEditorData(QWidget *_widget)
{
    QDateTimeEdit *editor = static_cast<QDateTimeEdit*>(_widget);
    setValue(QVariant::fromValue(editor->dateTime()));
}

void DateTimePropertyItem::updateTextValue()
{
    m_treeItem->setText(1, QLocale().toString(getValue().toDateTime(), QLocale::ShortFormat));
}
