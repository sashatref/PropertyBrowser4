#pragma once

#include "../abstractpropertyitem.h"


class PROPERTYBROWSER3_EXPORT DatePropertyItem : public AbstractPropertyItem
{
public:
    DatePropertyItem();

    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget* _widget) override;
    virtual void saveEditorData(QWidget* _widget) override;
    virtual void updateTextValue() override;
};
