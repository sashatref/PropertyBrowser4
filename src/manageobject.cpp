#include "manageobject.h"
#include "ui_manageobject.h"

namespace PropertyBrowser3Qt
{

ManageObject::ManageObject(QWidget *parent) :
    ExtendedWidget  (parent),
    ui              (new Ui::ManageObject)
{
    ui->setupUi(this);

    initAll();
}

ManageObject::~ManageObject()
{
    delete ui;
}

PropertyBrowser3 *ManageObject::getPB()
{
    return ui->propertyBrowser;
}

void ManageObject::setValue(const QVariant &_value)
{
    const bool isAdd = VariantHelper::getProperty(_value, "id").toInt() == -1;

    ui->propertyBrowser->setVariant(_value);
    ui->removeButton->setEnabled(!isAdd);

    initText();
}

void ManageObject::initText()
{
    using namespace HelperLibrary;

    const QVariant val = ui->propertyBrowser->getVariant();

    bool isAdd = VariantHelper::getProperty(val, "id").toInt() == -1;
    const IGadget *gadget = val.value<IGadget*>();
    if(!gadget)
    {
        qCritical() << QString("Can't cast type <%1> - <%2> to IGadget*")
                       .arg(val.userType())
                       .arg(val.typeName());
        qCritical() << UserExceptions::BaseException();
    }

    QString title;
    if(isAdd)
    {
        title = tr("Добавить запись <%1>").arg(gadget->classDescription());
    } else
    {
        title = tr("Редактировать запись <%1>").arg(gadget->classDescription());
    }
    ui->propertyBrowser->setLabelText(title);
    setWindowTitle(title);
}


QVariant ManageObject::saveWidgetState() const
{
    LayoutSaver saver;

    saver.saveGeometry(this, "geometry");
    saver.save(ui->propertyBrowser, "propBrowser");

    return saver;
}

void ManageObject::loadWidgetState(const QVariant &_state)
{
    const LayoutSaver saver = _state.toMap();

    saver.loadGeometry(this, "geometry");
    saver.load(ui->propertyBrowser, "propBrowser");
}

void ManageObject::updateLanguage()
{
    ui->retranslateUi(this);
    initText();
}

void ManageObject::updateStyle()
{
    ui->removeButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Minus2));
    ui->applyButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));
    ui->closeButton->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));
}

void ManageObject::initUiComponets()
{
}

void ManageObject::initConnections()
{
    connect(ui->removeButton, &QToolButton::clicked, this, &ManageObject::onRemoveButtonClicked);
    connect(ui->closeButton, &QToolButton::clicked, this, &ManageObject::onCloseButtonClicked);
    connect(ui->applyButton, &QToolButton::clicked, this, &ManageObject::onApplyButtonClicked);
}

void ManageObject::registerCustomTypes()
{
}

void ManageObject::onCloseButtonClicked()
{
    emit closeClicked();
}

void ManageObject::onApplyButtonClicked()
{
    if(!ui->propertyBrowser->checkTree()) return;
    if(!ui->propertyBrowser->checkObject()) return;

    emit applyValue(ui->propertyBrowser->getVariant());
}

void ManageObject::onRemoveButtonClicked()
{
    QVariant var = ui->propertyBrowser->getVariant();
    int indexToDelete = VariantHelper::getProperty(var, "id").toInt();
    if(indexToDelete == -1) return;

    int resBtn = QMessageBox::question(this,
                                       tr("Уверены?"),
                                       tr("Действительно хотите удалить запись с ID: %1?").arg(indexToDelete));
    if (resBtn == QMessageBox::Yes)
    {
        emit removeValue(ui->propertyBrowser->getVariant());
    }
}

}



