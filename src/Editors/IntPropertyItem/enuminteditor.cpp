#include "enuminteditor.h"
#include "intpropertyitem.h"
#include "../editorproperties.h"

EnumIntEditor::EnumIntEditor(IntPropertyItem *_parent):
    IIntEditor(_parent)
{

}


QWidget *EnumIntEditor::createEditor(QWidget *_parent)
{
    return new QComboBox(_parent);
}

void EnumIntEditor::setEditorData(QWidget *_widget)
{
    using namespace PropertyBrowser3Qt;

    QComboBox *combo = static_cast<QComboBox*>(_widget);
    QVariantMap map = m_baseIntEditor->getProperty(EnumProperty::FriendlyNamesMap).toMap();

    for(int i = 0 ; i < m_baseIntEditor->m_metaProperty.enumerator().keyCount(); i++)
    {
        int value = m_baseIntEditor->m_metaProperty.enumerator().value(i);
        QString name = m_baseIntEditor->m_metaProperty.enumerator().key(i);

        if(map.contains(name))
        {
            name = map[name].toString();
        }

        combo->addItem(name, value);

        if(m_baseIntEditor->getValue().toInt() == value)
        {
            combo->setCurrentIndex(i);
        }
    }
}

void EnumIntEditor::saveEditorData(QWidget *_widget)
{
    QComboBox *combo = static_cast<QComboBox*>(_widget);
    m_baseIntEditor->setValue(combo->currentData().toInt());
}

bool EnumIntEditor::updateTextValue()
{
    using namespace PropertyBrowser3Qt;

    QString stringValue = m_baseIntEditor->m_metaProperty.enumerator().valueToKey(
                m_baseIntEditor->getValue().toInt());
    QVariantMap map = m_baseIntEditor->getProperty(EnumProperty::FriendlyNamesMap).toMap();
    if(map.contains(stringValue))
    {
        stringValue = map[stringValue].toString();
    }

    m_baseIntEditor->setValueText(stringValue);

    return true;
}
