#pragma once

#include "../abstractpropertyitem.h"


class PROPERTYBROWSER3_EXPORT FontPropertyItem : public AbstractPropertyItem
{
public:
    FontPropertyItem();

    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget* _widget) override;
    virtual void saveEditorData(QWidget* _widget) override;
    virtual void updateTextValue() override;
    virtual bool isDialog() const override;
};
