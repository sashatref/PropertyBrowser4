#include "stringlistpropertyitem.h"

#include "stringlisteditor.h"
#include "../editorproperties.h"
#include "loadfileswidget.h"

StringListPropertyItem::StringListPropertyItem() :
    AbstractPropertyItem(QVariant::StringList)
{
    using namespace PropertyBrowser3Qt;

    m_propertiesMap[StringListProperty::EditorSize] = QSize(300,300);
    m_propertiesMap[StringListProperty::EditorType] = StringListProperty::StringListEditor;
    m_propertiesMap[StringListProperty::IsDialog] = true;
    m_propertiesMap[StringListProperty::DefaultDirectory] = "";
    m_propertiesMap[StringListProperty::DialogCaption] = tr("Выберите файлы...");
    m_propertiesMap[StringListProperty::Filter] = "All(*.*)";
    m_propertiesMap[StringListProperty::Options] = 0;
}

QWidget *StringListPropertyItem::createEditor(QWidget *_parent)
{
    using namespace PropertyBrowser3Qt;

    int editorType = m_propertiesMap[StringListProperty::EditorType].toInt();

    QWidget *editor = 0;

    if(editorType == StringListProperty::StringListEditor)
    {
        StringListEditor *listEditor = new StringListEditor(_parent);
        listEditor->setWindowTitle(QString(tr("Радактор строк для <%1>")).arg(getPropertyCaption()));
        editor = listEditor;
    } else if(editorType == StringListProperty::OpenFiles)
    {
        LoadFilesWidget *loadFilesEditor = new LoadFilesWidget(_parent);
        loadFilesEditor->setWindowTitle(QString(tr("Список файлов для <%1>")).arg(getPropertyCaption()));
        loadFilesEditor->setSettings(
                m_propertiesMap[StringListProperty::DialogCaption].toString(),
                m_propertiesMap[StringListProperty::Filter].toString(),
                m_propertiesMap[StringListProperty::DefaultDirectory].toString(),
                m_propertiesMap[StringListProperty::Options].toInt()
                );
        editor = loadFilesEditor;
    }

    return editor;
}

void StringListPropertyItem::setEditorData(QWidget *_widget)
{
    using namespace PropertyBrowser3Qt;

    int editorType = m_propertiesMap[StringListProperty::EditorType].toInt();

    if(editorType == StringListProperty::StringListEditor)
    {
        StringListEditor *listEditor = static_cast<StringListEditor*>(_widget);
        listEditor->setStringList(getValue().toStringList());
    } else if(editorType == StringListProperty::OpenFiles)
    {
        LoadFilesWidget *loadFilesEditor = static_cast<LoadFilesWidget*>(_widget);
        loadFilesEditor->addStringList(getValue().toStringList());
    }
}

void StringListPropertyItem::saveEditorData(QWidget *_widget)
{
    using namespace PropertyBrowser3Qt;

    int editorType = m_propertiesMap[StringListProperty::EditorType].toInt();

    if(editorType == StringListProperty::StringListEditor)
    {
        StringListEditor *listEditor = static_cast<StringListEditor*>(_widget);
        setValue(QVariant::fromValue(listEditor->getStringList()));
    } else if(editorType == StringListProperty::OpenFiles)
    {
        LoadFilesWidget *loadFilesEditor = static_cast<LoadFilesWidget*>(_widget);
        setValue(loadFilesEditor->getStringList());
    }
}

void StringListPropertyItem::updateTextValue()
{
    using namespace PropertyBrowser3Qt;

    int editorType = m_propertiesMap[StringListProperty::EditorType].toInt();

    QString text;
    if(editorType == StringListProperty::StringListEditor)
    {
        text = tr("Строк:");
    } else if(editorType == StringListProperty::OpenFiles)
    {
        text = tr("Файлов:");
    }

    m_treeItem->setText(1, QString("%1 %2").arg(text).arg(getValue().toStringList().size()));
}

bool StringListPropertyItem::isDialog() const
{
    using namespace PropertyBrowser3Qt;

    return m_propertiesMap[StringListProperty::IsDialog].toBool();
}

void StringListPropertyItem::updateGeometry(QWidget *_widget, const QStyleOptionViewItem /*option*/)
{
    using namespace PropertyBrowser3Qt;

    QSize size = m_propertiesMap[StringListProperty::EditorSize].toSize();
    WidgetHelper::setWidgetOnScreenCenter(_widget, _widget->parentWidget(), size.width(), size.height());
}

void StringListPropertyItem::onSetReadOnly(QWidget *_widget, bool _isReadOnly)
{
    using namespace PropertyBrowser3Qt;

    int editorType = m_propertiesMap[StringListProperty::EditorType].toInt();

    if(editorType == StringListProperty::StringListEditor)
    {
        StringListEditor *listEditor = static_cast<StringListEditor*>(_widget);
        listEditor->setReadOnly(_isReadOnly);

    } else if(editorType == StringListProperty::OpenFiles)
    {
        LoadFilesWidget *loadFilesEditor = static_cast<LoadFilesWidget*>(_widget);
        loadFilesEditor->setReadOnly(_isReadOnly);
    }
}

bool StringListPropertyItem::isSpecialReadOnlyMode() const
{
    return true;
}



