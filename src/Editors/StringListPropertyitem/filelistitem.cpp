#include "project_pch.h"
#include "filelistitem.h"
#include "ui_filelistitem.h"

FileListItem::FileListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileListItem)
{
    ui->setupUi(this);
}

FileListItem::~FileListItem()
{
    delete ui;
}

void FileListItem::setPath(const QString &_path)
{
    ui->lineEdit->setText(_path);
    ui->lineEdit->selectAll();
}

QString FileListItem::getPath() const
{
    return ui->lineEdit->text();
}

void FileListItem::setSettings(const QString &_dialogCaption, const QString &_filter, const QString &_defaultDir, int _options)
{
    m_dialogCaption = _dialogCaption;
    m_filter = _filter;
    m_defaultDir = _defaultDir;
    m_options = _options;
}

void FileListItem::on_openButton_clicked()
{
    ui->lineEdit->setFocus();
    QString text = QFileDialog::getOpenFileName(this,
                                                m_dialogCaption,
                                                ui->lineEdit->text(),
                                                m_filter,
                                                0,
                                                static_cast<QFileDialog::Options>(m_options));
    if(!text.isEmpty())
    {
        ui->lineEdit->setText(text);
    }
}
