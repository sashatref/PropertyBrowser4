#pragma once

#include <QDialog>
#include <QVariant>

#include "export.h"
#include <HelperLibrary/Widgets/extendeddialog.h>

namespace Ui {
class SettingsForm;
}

class PropertyBrowser3;

class PROPERTYBROWSER3_EXPORT SettingsForm : public ExtendedDialog
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = 0);
    ~SettingsForm();

    PropertyBrowser3 *getPropBrowser();

    template<class T>
    void setValue(const T &_value)
    {
        setValue(QVariant::fromValue(_value));
    }

    void setValue(const QVariant &_value);
    QVariant getValue() const;

    template<class T>
    void setValues(const QList<T> &_values)
    {
        QVariantList list;
        for(int i = 0 ; i < _values.size(); i++)
        {
            list << QVariant::fromValue(_values.at(i));
        }

        setValues(list);
    }

    void setValues(const QVariantList &_values);
    QVariantList getValues() const;

    void setEnabledSaveLoad(bool _e);

signals:
    void valueChanged(const QVariant &_value);
    void valuesChanged(const QVariantList &_values);

private slots:
    void on_applyButton_clicked();
    void on_closeButton_clicked();
    void on_saveBtn_clicked();
    void on_loadBtn_clicked();

private:
    Ui::SettingsForm *ui;
    QString m_lastSavePath;
    virtual void updateLanguage() override;
    virtual void updateStyle() override;
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
};

