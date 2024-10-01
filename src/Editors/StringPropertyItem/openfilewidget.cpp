#include "OpenFileWidget.h"
#include "ui_openfilewidget.h"

OpenFileWidget::OpenFileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenFileWidget),
    m_dialogCaption(tr("Выберите каталог...")),
    m_defaultDir(),
    m_filter(),
    m_options(0),
    m_diglogType(OpenFile)
{
    ui->setupUi(this);

    ui->toolButton->setMenu(m_menu);
    m_menu->addAction(tr("Выбрать ресурс..."), this, &OpenFileWidget::showSelectedResourceDialog);
    m_menu->addAction(tr("Выбрать файл..."), this, &OpenFileWidget::on_toolButton_clicked);
}

OpenFileWidget::~OpenFileWidget()
{
    delete ui;
}

void OpenFileWidget::setPath(const QString &_path)
{
    ui->lineEdit->setText(_path);
    setDefaultDir(_path);
}

QString OpenFileWidget::getPath() const
{
    return ui->lineEdit->text();
}

void OpenFileWidget::setReadOnly(bool _isReadOnly)
{
    ui->lineEdit->setReadOnly(_isReadOnly);
    ui->toolButton->setEnabled(!_isReadOnly);
}

void OpenFileWidget::setDialogCaption(const QString &_caption)
{
    m_dialogCaption = _caption;
}

void OpenFileWidget::setDefaultDir(const QString &_dir)
{
    m_defaultDir = _dir;
}

void OpenFileWidget::setDialogType(int _dialogType)
{
    m_diglogType = _dialogType;
}

void OpenFileWidget::setFilter(const QString &_filter)
{
    m_filter = _filter;
}

void OpenFileWidget::setOptions(int _options)
{
    m_options = _options;
}

void OpenFileWidget::on_toolButton_clicked()
{
    ui->lineEdit->setFocus();
    QString result;


    if(m_diglogType == SaveFile)
    {
       result = QFileDialog::getSaveFileName(this,
                                             m_dialogCaption,
                                             m_defaultDir,
                                             m_filter,
                                             0,
                                             static_cast<QFileDialog::Options>(m_options));
    } else if(m_diglogType == OpenFile)
    {
        result = QFileDialog::getOpenFileName(this,
                                              m_dialogCaption,
                                              m_defaultDir,
                                              m_filter,
                                              0,
                                              static_cast<QFileDialog::Options>(m_options));
    } else if(m_diglogType == SaveDir)
    {
        result = QFileDialog::getExistingDirectory(this,
                                              m_dialogCaption,
                                              m_defaultDir,
                                              static_cast<QFileDialog::Options>(m_options));
    } else if(m_diglogType == OpenDir)
    {
        result = QFileDialog::getExistingDirectory(this,
                                              m_dialogCaption,
                                              m_defaultDir,
                                              static_cast<QFileDialog::Options>(m_options));
    }

    if(result.isEmpty())
    {
        return;
    }

    m_defaultDir = result;
    ui->lineEdit->setText(result);
}

void OpenFileWidget::showSelectedResourceDialog()
{
    ui->lineEdit->setFocus();

    static QVariant state;

    ResourceExplorerDialog dialog(this);
    dialog.loadWidgetState(state);
    dialog.setSelectedFile(ui->lineEdit->text());
    if(dialog.exec() == QDialog::Accepted)
    {
        ui->lineEdit->setText(dialog.getSelectedFile());
    }

    state = dialog.saveWidgetState();
}
