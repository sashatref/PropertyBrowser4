#pragma once

#include <QDialog>

namespace Ui {
class PhotoUploader;
}

class PhotoUploader : public QDialog
{
    Q_OBJECT

public:
    explicit PhotoUploader(QWidget *parent = 0);
    ~PhotoUploader();

    void setPixmap(const QPixmap &_pixmap);
    QPixmap getPixmap() const;

private slots:
    void on_loadButton_clicked();
    void on_applyButton_clicked();
    void on_removeImgButton_clicked();

private:
    Ui::PhotoUploader *ui;

    QByteArray m_data;
};
