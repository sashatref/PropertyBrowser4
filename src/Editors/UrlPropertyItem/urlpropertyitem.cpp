#include "project_pch.h"
#include "urlpropertyitem.h"

QWidget *UrlPropertyItem::createEditor(QWidget *_parent)
{
    QLineEdit *editor = new QLineEdit(_parent);
    editor->setFrame(false);
    return editor;
}

void UrlPropertyItem::setEditorData(QWidget *_widget)
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(_widget);
    lineEdit->setText(getValue().toUrl().toDisplayString());
    lineEdit->deselect();
}

void UrlPropertyItem::saveEditorData(QWidget *_widget)
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(_widget);
    QUrl url = QUrl::fromUserInput(lineEdit->text());
    setValue(QVariant::fromValue(url));
}

bool UrlPropertyItem::checkItem()
{
    if(getRequried() && getValue().toUrl().isEmpty())
    {
        return false;
    }
    return true;
}
