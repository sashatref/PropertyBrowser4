#pragma once

#include <QDialog>

namespace Ui {
class ByteArrayEditor;
}

namespace PropertyBrowser3Qt
{

class ByteArrayEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ByteArrayEditor(QWidget *parent = 0);
    ~ByteArrayEditor();
    void setDataSizeEditable(bool _isEditable);
    void setDataSize(int _size);
    void setData(const QByteArray &_byteArray);
    QByteArray getData() const;

private slots:
    void on_dataSizeSpinBox_valueChanged(int arg1);
    void on_cancelButton_clicked();
    void on_applyButton_clicked();

private:
    int m_dataSize;
    Ui::ByteArrayEditor *ui;
};

}
