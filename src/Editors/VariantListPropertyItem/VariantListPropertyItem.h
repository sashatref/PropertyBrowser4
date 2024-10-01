#pragma once
#include "../abstractpropertyitem.h"


class PROPERTYBROWSER3_EXPORT VariantListPropertyItem : public AbstractPropertyItem
{
    Q_OBJECT
public:
    VariantListPropertyItem(QObject *callbackListener = 0);

    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget *_widget) override;
    virtual void saveEditorData(QWidget *_widget) override;
    virtual void updateGeometry(QWidget *_widget, const QStyleOptionViewItem option) override;
    virtual void updateTextValue() override;
    virtual bool isDialog() const override;

private:
    QObject *m_callBackListener;
};
