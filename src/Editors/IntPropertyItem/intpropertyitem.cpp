#include "project_pch.h"
#include "intpropertyitem.h"

#include "../editorproperties.h"
#include "propertybrowser3.h"
#include "defaultinteditor.h"
#include "enuminteditor.h"
#include "flagsinteditor.h"


IntPropertyItem::IntPropertyItem():
    AbstractPropertyItem    (QVariant::Int)
{
    using namespace PropertyBrowser3Qt;

    m_propertiesMap[IntProperty::SpinBoxMinimum] = 0;
    m_propertiesMap[IntProperty::SpinBoxMaximum] = 100000;
    m_propertiesMap[IntProperty::DisplayType] = IntProperty::Default;
}

QWidget *IntPropertyItem::createEditor(QWidget *_parent)
{
    return getHelper()->createEditor(_parent);
}

void IntPropertyItem::setEditorData(QWidget *_widget)
{
    getHelper()->setEditorData(_widget);
}

void IntPropertyItem::saveEditorData(QWidget *_widget)
{
    getHelper()->saveEditorData(_widget);
}

void IntPropertyItem::updateTextValue()
{
    if(!getHelper()->updateTextValue())
    {
        AbstractPropertyItem::updateTextValue();
    }
}

IIntEditor *IntPropertyItem::getHelper()
{
    if(m_helperMap.isEmpty())
    {
        m_helperMap[DefaultInt] = new DefaultIntEditor(this);
        m_helperMap[EnumInt] = new EnumIntEditor(this);
        m_helperMap[FlagsInt] = new FlagsIntEditor(this);
    }

    if(m_metaProperty.isFlagType())
    {
        return m_helperMap[FlagsInt];
    }

    if(m_metaProperty.isEnumType())
    {
        return m_helperMap[EnumInt];
    }

    return m_helperMap[DefaultInt];
}




