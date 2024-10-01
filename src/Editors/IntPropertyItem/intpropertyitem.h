#pragma once

#include "../abstractpropertyitem.h"
#include "iinteditor.h"

class PROPERTYBROWSER3_EXPORT IntPropertyItem : public AbstractPropertyItem
{
    Q_OBJECT
    friend class EnumIntEditor;
    friend class DefaultIntEditor;
    friend class FlagsIntEditor;
public:
    IntPropertyItem();

    enum
    {
        DefaultInt,
        EnumInt,
        FlagsInt
    };

    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget *_widget) override;
    virtual void saveEditorData(QWidget *_widget) override;
    virtual void updateTextValue() override;

private:
    IIntEditor *getHelper();

    QMap<int, IIntEditor*> m_helperMap;
};
