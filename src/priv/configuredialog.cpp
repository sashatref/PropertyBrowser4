#include "configuredialog.h"
#include "ui_configuredialog.h"

namespace PropertyBrowser3Qt
{

ConfigureDialog::ConfigureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureDialog)
{
    ui->setupUi(this);

    ui->applyButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));
    ui->closeButton->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));

    ui->setColumnListFontDefaultBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Undo1));
    ui->setHistoryCountDefBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Undo1));
    ui->setMainTableFontDefaultBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Undo1));
}

ConfigureDialog::~ConfigureDialog()
{
    delete ui;
}

void ConfigureDialog::setConf(const TreeConfInfo &_info)
{
    m_conf = _info;

    updateEditors();
}

TreeConfInfo ConfigureDialog::getConf() const
{
    TreeConfInfo out = m_conf;
    out.historyCount = ui->historyCountSpinBox->value();
    return out;
}

void ConfigureDialog::on_closeButton_clicked()
{
    reject();
}

void ConfigureDialog::on_applyButton_clicked()
{
    accept();
}

void ConfigureDialog::on_selectMaintTableFontButton_clicked()
{
    QFontDialog dialog(this);
    dialog.setCurrentFont(m_conf.treeFont);
    if(dialog.exec() == QDialog::Accepted)
    {
        m_conf.treeFont = dialog.currentFont();
        updateEditors();
    }
}

void ConfigureDialog::on_selectColumnListFontButton_clicked()
{
    QFontDialog dialog(this);
    dialog.setCurrentFont(m_conf.listFont);
    if(dialog.exec() == QDialog::Accepted)
    {
        m_conf.listFont = dialog.currentFont();
        updateEditors();
    }
}

void ConfigureDialog::on_setMainTableFontDefaultBtn_clicked()
{
    m_conf.treeFont = QFont();
    updateEditors();
}

void ConfigureDialog::on_setColumnListFontDefaultBtn_clicked()
{
    m_conf.listFont = QFont();
    updateEditors();
}

void ConfigureDialog::on_setHistoryCountDefBtn_clicked()
{
    m_conf.historyCount = 30;
    updateEditors();
}

void ConfigureDialog::updateEditors()
{
    ui->treeFontEdit->setText(m_conf.treeFont.toString());
    ui->listFontEdit->setText(m_conf.listFont.toString());
    ui->historyCountSpinBox->setValue(m_conf.historyCount);
}

}
