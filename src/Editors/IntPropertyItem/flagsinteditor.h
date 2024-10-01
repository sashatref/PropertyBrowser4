#pragma once

#include "iinteditor.h"

#include "../abstractpropertyitem.h"

class FlagsIntEditor : public IIntEditor
{
public:
    FlagsIntEditor(IntPropertyItem *_parent);

    // IIntEditor interface
public:
    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget *_widget) override;
    virtual void saveEditorData(QWidget *_widget) override;
    virtual bool updateTextValue() override;

private slots:
    void onPropertyChanged(const QString &_propertyName, const QVariant &_propertyValue);

private:
    void clear();

    void updateBitValues();

    QMap<QString, AbstractPropertyItem*> m_subPropMap;

    bool isNeedToPropChange = true;
};

