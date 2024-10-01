#include "dirpropertyitem.h"
#include "opendirectorywidget.h"
#include <QDir>

#include <QDebug>

DirPropertyItem::DirPropertyItem()
{
    m_propertiesMap[DefaultCaption] = tr("Выберите каталог...");
    m_propertiesMap[DefaultDir] = "";

    qWarning() << "Stop using QDir";
    qWarning() << Q_FUNC_INFO;
}

QWidget *DirPropertyItem::createEditor(QWidget *_parent)
{
    OpenDirectoryWidget *editor = new OpenDirectoryWidget(_parent);
    editor->setDefaultDir(m_propertiesMap[DefaultDir].toString());
    editor->setDialogCaption(m_propertiesMap[DefaultCaption].toString());
    return editor;
}

void DirPropertyItem::setEditorData(QWidget *_widget)
{
    OpenDirectoryWidget *editor = static_cast<OpenDirectoryWidget*>(_widget);
    editor->setPath(getValue().value<QDir>().path());
}

void DirPropertyItem::saveEditorData(QWidget *_widget)
{
    OpenDirectoryWidget *editor = static_cast<OpenDirectoryWidget*>(_widget);
    QDir var = editor->getPath();
    setValue(QVariant::fromValue(var));
}

void DirPropertyItem::updateTextValue()
{
    m_treeItem->setText(1, getValue().value<QDir>().path());
}

Q_DECLARE_METATYPE(QDir)
