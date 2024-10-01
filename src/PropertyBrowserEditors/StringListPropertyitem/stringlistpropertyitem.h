#pragma once

#include <PropertyBrowserCore/abstractpropertyitem.h>

class StringListPropertyItem : public AbstractPropertyItem
{
    Q_OBJECT
public:
    StringListPropertyItem();

    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget *_widget) override;
    virtual void saveEditorData(QWidget *_widget) override;
    virtual void updateTextValue() override;
    virtual bool isDialog() const override;
    virtual void updateGeometry(QWidget *_widget, const QStyleOptionViewItem option) override;
    virtual void onSetReadOnly(QWidget *_widget, bool _isReadOnly) override;
    virtual bool isSpecialReadOnlyMode() const override;
};
