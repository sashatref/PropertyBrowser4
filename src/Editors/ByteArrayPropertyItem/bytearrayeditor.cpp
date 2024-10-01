#include "project_pch.h"
#include "bytearrayeditor.h"
#include "ui_bytearrayeditor.h"
#include "qhexedit.h"

namespace PropertyBrowser3Qt
{

ByteArrayEditor::ByteArrayEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ByteArrayEditor)
{
    ui->setupUi(this);
    setDataSize(8);
}

ByteArrayEditor::~ByteArrayEditor()
{
    delete ui;
}

void ByteArrayEditor::setDataSizeEditable(bool _isEditable)
{
    ui->dataSizeSpinBox->setEnabled(_isEditable);
}

void ByteArrayEditor::setDataSize(int _size)
{
    m_dataSize = _size;
    QByteArray ba = ui->hexEditor->data();
    ba.resize(_size);
    ui->dataSizeSpinBox->setValue(_size);

    ui->hexEditor->setData(ba);
}

void ByteArrayEditor::setData(const QByteArray &_byteArray)
{
    QByteArray ba = _byteArray;

    if(!ui->dataSizeSpinBox->isEnabled())
    {
        ba.resize(m_dataSize);
    }

    ui->hexEditor->setData(ba);
    ui->dataSizeSpinBox->setValue(ba.size());
}

QByteArray ByteArrayEditor::getData() const
{
    QByteArray ba = ui->hexEditor->data();
    ba.resize(m_dataSize);
    return ba;
}

void ByteArrayEditor::on_dataSizeSpinBox_valueChanged(int arg1)
{
    setDataSize(arg1);
}

void ByteArrayEditor::on_cancelButton_clicked()
{
    close();
}

void ByteArrayEditor::on_applyButton_clicked()
{
    accept();
}

}
