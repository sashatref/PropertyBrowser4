#include "VariantListPropertyItem.h"

#include "settingsform.h"
#include "propertybrowser3.h"
#include "../editorproperties.h"

VariantListPropertyItem::VariantListPropertyItem(QObject *callbackListener):
    AbstractPropertyItem(QVariant::List),
    m_callBackListener(callbackListener)
{
    using namespace PropertyBrowser3Qt;

    m_propertiesMap[VariantListProperty::CreateObjectType] = -1;
    m_propertiesMap[VariantListProperty::EditorSize] = QSize(300,500);
}

QWidget *VariantListPropertyItem::createEditor(QWidget *_parent)
{
    using namespace PropertyBrowser3Qt;

    SettingsForm *editor = new SettingsForm(_parent);
    editor->setWindowTitle(getPropertyCaption());
    editor->getPropBrowser()->setMultiObjectListVisible(true);
    editor->getPropBrowser()->setCreateObjectType(m_propertiesMap[VariantListProperty::CreateObjectType].toInt());
    editor->getPropBrowser()->setCallBackObject(m_callBackListener);

    return editor;
}

void VariantListPropertyItem::setEditorData(QWidget *_widget)
{
    SettingsForm *editor = static_cast<SettingsForm*>(_widget);
    editor->setValues(getValue().toList());
    m_propertyType = getValue().userType();
}

void VariantListPropertyItem::saveEditorData(QWidget *_widget)
{
    SettingsForm *editor = static_cast<SettingsForm*>(_widget);
    QVariant variant = QVariant::fromValue(editor->getValues());
    if(!variant.convert(m_propertyType))
    {
        qWarning() << QString("Converting error: QVariantList to type:%1 (%2) for property <%3>")
                      .arg(m_propertyType)
                      .arg(QMetaType::typeName(m_propertyType))
                      .arg(getPropertyName());
        return;
    }

    setValue(variant);
}

void VariantListPropertyItem::updateGeometry(QWidget *_widget, const QStyleOptionViewItem /*option*/)
{
    using namespace PropertyBrowser3Qt;

    QSize size = m_propertiesMap[VariantListProperty::EditorSize].toSize();
    _widget->setGeometry(0,0, size.width(), size.height());
    WidgetHelper::setWidgetOnScreenCenter(_widget, _widget->parentWidget());
}

void VariantListPropertyItem::updateTextValue()
{
    QString text = tr("Элементов: %1").arg(getValue().toList().size());

    if(getValue().canConvert<QString>())
    {
        text = getValue().toString();
    }

    m_treeItem->setText(1, text);
}

bool VariantListPropertyItem::isDialog() const {return true;}
