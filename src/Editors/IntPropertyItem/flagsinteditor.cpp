#include "flagsinteditor.h"

#include "../abstractpropertyitem.h"
#include "../editorproperties.h"
#include "intpropertyitem.h"
#include "../../propertybrowser3.h"

FlagsIntEditor::FlagsIntEditor(IntPropertyItem *_parent):
    IIntEditor(_parent)
{

}


QWidget *FlagsIntEditor::createEditor(QWidget * /*_parent*/)
{
    return nullptr;
}

void FlagsIntEditor::setEditorData(QWidget * /*_widget*/)
{
}

void FlagsIntEditor::saveEditorData(QWidget * /*_widget*/)
{
}

bool FlagsIntEditor::updateTextValue()
{
    using namespace PropertyBrowser3Qt;

    clear();

    int value = m_baseIntEditor->getValue().toInt();

    QMetaEnum enumerator = m_baseIntEditor->m_metaProperty.enumerator();

    for(int i = 0 ; i < enumerator.keyCount(); i++)
    {
        int bitMask = enumerator.value(i);
        QString name = enumerator.key(i);

        AbstractPropertyItem *addedItem = PropertyBrowser3::addItem(
                    name,
                    QVariant::Bool,
                    m_baseIntEditor->m_treeItem,
                    PropertyInfo(),
                    QMetaProperty());

        QVariantMap map = m_baseIntEditor->m_propertiesMap[FlagsProperty::FriendlyNamesMap].toMap();
        if(map.contains(name))
        {
            addedItem->setPropertyCaption(map[name].toString());
        }

        bool testBit = ((value & bitMask) == bitMask);
        addedItem->setValue(testBit);
        //addedItem->updateTextValue();
        connect(addedItem, &AbstractPropertyItem::valueChanged, this, &FlagsIntEditor::onPropertyChanged);
        m_subPropMap[name] = addedItem;
    }

    updateBitValues();

    return true;
}

void FlagsIntEditor::onPropertyChanged(const QString &_propertyName, const QVariant &_propertyValue)
{
    if(isNeedToPropChange)
    {
        int bitMask = m_baseIntEditor->m_metaProperty.enumerator().keyToValue(qPrintable(_propertyName));
        int totalValue = m_baseIntEditor->getValue().toInt();

        if(_propertyValue.toBool())
        {
            totalValue |= bitMask;
        } else
        {
            totalValue &= (~bitMask);
        }

        if(bitMask == 0)
        {
            totalValue = 0;
        }

        m_baseIntEditor->setValue(totalValue);
        updateBitValues();
    }
}

void FlagsIntEditor::clear()
{
    for(int i = 0 ; i < m_subPropMap.size(); i++)
    {
        QString key = m_subPropMap.keys().at(i);
        delete m_subPropMap[key]->getTreeItem();
        delete m_subPropMap[key];
    }
    m_subPropMap.clear();
}

void FlagsIntEditor::updateBitValues()
{
    using namespace PropertyBrowser3Qt;

    isNeedToPropChange = false;

    QStringList listValues;

    int totalValue = m_baseIntEditor->getValue().toInt();

    for(int i = 0 ; i < m_subPropMap.keys().size(); i++)
    {
        QString name = m_subPropMap.keys().at(i);
        int bitMask = m_baseIntEditor->m_metaProperty.enumerator().keyToValue(qPrintable(name));

        //это для Enum = 0 элемента
        if(bitMask == 0 && totalValue != 0)
        {
            m_subPropMap[name]->setValue(false);
            continue;
        }

        bool isSet = ((totalValue & bitMask) == bitMask);

        m_subPropMap[name]->setValue(isSet);
        if(isSet)
        {
            QVariantMap map = m_baseIntEditor->m_propertiesMap[FlagsProperty::FriendlyNamesMap].toMap();
            if(map.contains(name))
            {
                name = map[name].toString();
            }

            listValues.append(name);
        }
    }

    m_baseIntEditor->setValueText(listValues.join("|"));

    isNeedToPropChange = true;
}
