#include "project_pch.h"
#include "stringlisteditor.h"
#include "ui_stringlisteditor.h"

StringListEditor::StringListEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StringListEditor)
{
    ui->setupUi(this);

    ui->applyButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));
    ui->closeButton->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));
}

StringListEditor::~StringListEditor()
{
    delete ui;
}

void StringListEditor::setReadOnly(bool _isReadOnly)
{
    ui->applyButton->setEnabled(!_isReadOnly);
    ui->textEdit->setReadOnly(_isReadOnly);
}

void StringListEditor::setStringList(const QStringList &_list)
{
    for(int i = 0 ; i < _list.size(); i++)
    {
        ui->textEdit->append(_list.at(i));
    }
}

QStringList StringListEditor::getStringList() const
{
    QStringList values = ui->textEdit->toPlainText().split("\n");
    for(int i = values.size() - 1; i > -1; i--)
    {
        if(values.at(i).isEmpty())
        {
            values.removeAt(i);
        }
    }

    return values;
}

void StringListEditor::on_closeButton_clicked()
{
    reject();
}

void StringListEditor::on_applyButton_clicked()
{
    accept();
}
