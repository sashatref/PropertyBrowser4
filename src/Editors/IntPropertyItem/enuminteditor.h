#pragma once

#include "iinteditor.h"


class EnumIntEditor : public IIntEditor
{
public:
    EnumIntEditor(IntPropertyItem *_parent);

    // IIntEditor interface
public:
    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget *_widget) override;
    virtual void saveEditorData(QWidget *_widget) override;
    virtual bool updateTextValue() override;
};


