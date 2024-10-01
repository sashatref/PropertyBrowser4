#include "project_pch.h"
#include "changepropertycommand.h"

#include "Editors/abstractpropertyitem.h"


ChangePropertyCommand::ChangePropertyCommand(const QString &_propertyName,
                                             const QVariant &_propertyNewValue,
                                             const QVariant &_propertyOldValue,
                                             PropertyBrowser3 *_propertyBrowser,
                                             QUndoCommand *parent):
    QUndoCommand        (parent),
    m_propertyName      (_propertyName),
    m_propertyNewValue  (_propertyNewValue),
    m_propertyOldValue  (_propertyOldValue),
    m_propertyBrowser   (_propertyBrowser)
{
    AbstractPropertyItem *item = m_propertyBrowser->getProperty(m_propertyName);
    if(item)
    {
        setText(QObject::tr("Свойство <%1> изменено")
                .arg(item->getPropertyCaption()));
    }
}

void ChangePropertyCommand::undo()
{
    m_propertyBrowser->setPropertyValue(m_propertyName, m_propertyOldValue, false);
    m_propertyBrowser->setSingleRowColor(m_propertyName, QColor(255,255, 70, 100));
}

void ChangePropertyCommand::redo()
{
    m_propertyBrowser->setPropertyValue(m_propertyName, m_propertyNewValue, false);
    m_propertyBrowser->setSingleRowColor(m_propertyName, QColor(255,255, 70, 100));
}

int ChangePropertyCommand::id() const
{
    return 0;
}

bool ChangePropertyCommand::mergeWith(const QUndoCommand * /*other*/)
{
    return false;
}
