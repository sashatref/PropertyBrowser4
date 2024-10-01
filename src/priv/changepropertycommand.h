#pragma once

#include <QUndoCommand>
#include <QVariant>
#include "propertybrowser3.h"

class ChangePropertyCommand : public QUndoCommand
{
public:
    ChangePropertyCommand(const QString &_propertyName,
                          const QVariant &_propertyNewValue,
                          const QVariant &_propertyOldValue,
                          PropertyBrowser3 *_propertyBrowser,
                          QUndoCommand *parent = 0);

    virtual void undo() override;
    virtual void redo() override;
    virtual int id() const override;
    virtual bool mergeWith(const QUndoCommand *other) override;

private:
    QString m_propertyName;
    QVariant m_propertyNewValue;
    QVariant m_propertyOldValue;
    PropertyBrowser3 *m_propertyBrowser;
    QUndoStack *m_stack;
};
