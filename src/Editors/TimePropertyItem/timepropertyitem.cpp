#include "project_pch.h"
#include "timepropertyitem.h"

TimePropertyItem::TimePropertyItem()
{

}


QWidget *TimePropertyItem::createEditor(QWidget *_parent)
{
    QTimeEdit *edit = new QTimeEdit(_parent);
    //edit->setCalendarPopup(true);
    return edit;
}

void TimePropertyItem::setEditorData(QWidget *_widget)
{
    QTimeEdit *editor = static_cast<QTimeEdit*>(_widget);
    editor->setTime(getValue().value<QTime>());
}

void TimePropertyItem::saveEditorData(QWidget *_widget)
{
    QTimeEdit *editor = static_cast<QTimeEdit*>(_widget);
    setValue(QVariant::fromValue(editor->time()));
}

void TimePropertyItem::updateTextValue()
{
    m_treeItem->setText(1, getValue().value<QTime>().toString("hh:mm"));
}
