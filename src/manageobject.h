#pragma once

#include <QWidget>
#include <HelperLibrary/Widgets/extendedwidget.h>
#include "propertybrowser3.h"
#include "export.h"

namespace Ui {
class ManageObject;
}

namespace PropertyBrowser3Qt
{

class PROPERTYBROWSER3_EXPORT ManageObject : public ExtendedWidget
{
    Q_OBJECT

public:
    explicit ManageObject(QWidget *parent = 0);
    ~ManageObject();

    PropertyBrowser3 *getPB();

    void setValue(const QVariant &_value);

signals:
    void applyValue(const QVariant &_value);
    void removeValue(const QVariant &_value);
    void closeClicked();

private:
    Ui::ManageObject *ui;
    void initText();

    // ISaveWidget interface
public:
    virtual QVariant saveWidgetState() const override;
    virtual void loadWidgetState(const QVariant &_state) override;
    virtual void updateLanguage() override;
    virtual void updateStyle() override;

protected:
    virtual void initUiComponets() override;
    virtual void initConnections() override;
    virtual void registerCustomTypes() override;

private slots:
    void onCloseButtonClicked();
    void onApplyButtonClicked();
    void onRemoveButtonClicked();
};

}

