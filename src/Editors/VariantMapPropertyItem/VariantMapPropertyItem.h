#pragma once

#include "../abstractpropertyitem.h"

class PROPERTYBROWSER3_EXPORT VariantMapPropertyItem : public AbstractPropertyItem
{
    Q_OBJECT
public:
    VariantMapPropertyItem();

    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget *_widget) override;
    virtual void saveEditorData(QWidget *_widget) override;
    virtual void updateGeometry(QWidget *_widget, const QStyleOptionViewItem option) override;
    virtual void updateTextValue() override;
    virtual bool isDialog() const override;
};
