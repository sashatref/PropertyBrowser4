#include "project_pch.h"
#include "settingsform.h"
#include "ui_settingsform.h"
#include "propertybrowser3.h"



SettingsForm::SettingsForm(QWidget *parent) :
    ExtendedDialog  (parent),
    ui              (new Ui::SettingsForm)
{
    ui->setupUi(this);

    initAll();

    setEnabledSaveLoad(false);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

PropertyBrowser3 *SettingsForm::getPropBrowser()
{
    return ui->propertyBrowser;
}

void SettingsForm::setValue(const QVariant &_value)
{
    ui->propertyBrowser->setVariant(_value);
}

QVariant SettingsForm::getValue() const
{
    return ui->propertyBrowser->getVariant();
}

void SettingsForm::setValues(const QVariantList &_values)
{
    ui->propertyBrowser->setVariantList(_values);
}

QVariantList SettingsForm::getValues() const
{
    return ui->propertyBrowser->getVariantList();
}

void SettingsForm::setEnabledSaveLoad(bool _e)
{
    ui->saveBtn->setVisible(_e);
    ui->loadBtn->setVisible(_e);
}

void SettingsForm::on_applyButton_clicked()
{
    ui->propertyBrowser->closeOpenedEditor();
    if(!ui->propertyBrowser->checkObject()) return;

    emit valueChanged(ui->propertyBrowser->getVariant());
    emit valuesChanged(ui->propertyBrowser->getVariantList());
    accept();
}

void SettingsForm::on_closeButton_clicked()
{
    reject();
}

void SettingsForm::updateLanguage()
{
    ui->retranslateUi(this);
}

void SettingsForm::updateStyle()
{
    ui->applyButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));
    ui->closeButton->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));
    ui->saveBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Save1));
    ui->loadBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_FileOpen1));
}



void SettingsForm::loadState(const LayoutSaver &_saver)
{
    _saver.loadGeometry(this, "g");
    _saver.load(ui->propertyBrowser, "pb");
    _saver.load(m_lastSavePath, "lastSavePath");
}

void SettingsForm::saveState(LayoutSaver &_saver) const
{
    _saver.saveGeometry(this, "g");
    _saver.save(ui->propertyBrowser, "pb");
    _saver.save(m_lastSavePath, "lastSavePath");
}

void SettingsForm::on_saveBtn_clicked()
{
    const QString path = QFileDialog::getSaveFileName(this, tr("Выберите файл"), m_lastSavePath, "*.xml");
    if(path.isEmpty())
    {
        return;
    }

    m_lastSavePath = path;

    SerializerQt::Serializer::save(ui->propertyBrowser->getVariantList(), QDir(path), "root");
    QMessageBox::information(this, tr("Успешно"), tr("Файл [%1] сохранен").arg(path));
}

void SettingsForm::on_loadBtn_clicked()
{
    const QString path = QFileDialog::getOpenFileName(this, tr("Выберите файл"), m_lastSavePath, "*.xml");
    if(path.isEmpty())
    {
        return;
    }

    m_lastSavePath = path;

    QVariantList v = ui->propertyBrowser->getVariantList();
    SerializerQt::Serializer::load(v, QDir(path), "root");
    ui->propertyBrowser->setVariantList(v);
}
