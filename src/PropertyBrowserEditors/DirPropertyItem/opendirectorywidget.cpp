#include "opendirectorywidget.h"
#include "ui_opendirectorywidget.h"

#include <QFileDialog>

OpenDirectoryWidget::OpenDirectoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenDirectoryWidget),
    m_defaultDir(),
    m_dialogCaption(tr("Выберите каталог..."))
{
    ui->setupUi(this);
}

OpenDirectoryWidget::~OpenDirectoryWidget()
{
    delete ui;
}

void OpenDirectoryWidget::setPath(const QString &_path)
{
    ui->lineEdit->setText(_path);
}

QString OpenDirectoryWidget::getPath() const
{
    return ui->lineEdit->text();
}

void OpenDirectoryWidget::setDialogCaption(const QString &_caption)
{
    m_dialogCaption = _caption;
}

void OpenDirectoryWidget::setDefaultDir(const QString &_dir)
{
    m_defaultDir = _dir;
}

void OpenDirectoryWidget::on_toolButton_clicked()
{
    ui->lineEdit->setFocus();
    QString result = QFileDialog::getExistingDirectory(this, m_dialogCaption, m_defaultDir);

    if(result.isEmpty())
    {
        return;
    }

    m_defaultDir = result;
    ui->lineEdit->setText(result);
}
