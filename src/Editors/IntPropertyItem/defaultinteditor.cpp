#include "defaultinteditor.h"

#include "intpropertyitem.h"
#include "../editorproperties.h"

DefaultIntEditor::DefaultIntEditor(IntPropertyItem *_parent):
    IIntEditor(_parent)
{

}


QWidget *DefaultIntEditor::createEditor(QWidget *_parent)
{
    using namespace PropertyBrowser3Qt;

    QSpinBox *spinBox = new QSpinBox(_parent);
    spinBox->setMinimum(m_baseIntEditor->m_propertiesMap[IntProperty::SpinBoxMinimum].toInt());
    spinBox->setMaximum(m_baseIntEditor->m_propertiesMap[IntProperty::SpinBoxMaximum].toInt());
    return spinBox;
}

void DefaultIntEditor::setEditorData(QWidget *_widget)
{
    QSpinBox *spinBox = static_cast<QSpinBox*>(_widget);
    spinBox->setValue(m_baseIntEditor->getValue().toInt());
}

void DefaultIntEditor::saveEditorData(QWidget *_widget)
{
    QSpinBox *spinBox = static_cast<QSpinBox*>(_widget);
    m_baseIntEditor->setValue(QVariant::fromValue(spinBox->value()));
}

bool DefaultIntEditor::updateTextValue()
{
    using namespace PropertyBrowser3Qt;

    switch(m_baseIntEditor->m_propertiesMap[IntProperty::DisplayType].toInt())
    {
    case IntProperty::Kb:
        m_baseIntEditor->m_treeItem->setText(1, QString("%1 KB").arg(m_baseIntEditor->getValue().toInt() / 1000));
        return true;
        break;
    case IntProperty::Mb:
        m_baseIntEditor->m_treeItem->setText(1, QString("%1 MB").arg(m_baseIntEditor->getValue().toInt() / 1000000));
        return true;
        break;
    case IntProperty::Gb:
        m_baseIntEditor->m_treeItem->setText(1, QString("%1 GB").arg(m_baseIntEditor->getValue().toInt() / 1000000000));
        return true;
        break;
    }

    return false;
}
