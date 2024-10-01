#pragma once

#include <PropertyBrowserCore/abstractpropertyitem.h>

class SizePropertyItem : public AbstractPropertyItem
{
    Q_OBJECT
public:
    SizePropertyItem();
    ~SizePropertyItem();

    // AbstractPropertyItem interface
public:
    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget *_widget) override;
    virtual void saveEditorData(QWidget *_widget) override;
    virtual void updateTextValue() override;

private slots:
    void onPropertyChanged(const QString &_propertyName, const QVariant &_propertyValue);

private:
    QMap<QString, AbstractPropertyItem*> m_subPropMap;
};

