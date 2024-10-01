#include "../../project_pch.h"
#include "photouploader.h"

#include "ui_photouploader.h"

#include "ResizableView/resizableview.h"

PhotoUploader::PhotoUploader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhotoUploader)
{
    ui->setupUi(this);
}

PhotoUploader::~PhotoUploader()
{
    delete ui;
}

void PhotoUploader::setPixmap(const QPixmap &_pixmap)
{
    ui->photoView->setPixmap(_pixmap);
}

QPixmap PhotoUploader::getPixmap() const
{
    return ui->photoView->getPixmap();
}

void PhotoUploader::on_loadButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Выберите файл...");
    if(path.isEmpty()) return;

    QPixmap img(path);
    ui->photoView->setPixmap(img);
}

void PhotoUploader::on_applyButton_clicked()
{
    accept();
}

void PhotoUploader::on_removeImgButton_clicked()
{
    ui->photoView->setPixmap(QPixmap());
}

