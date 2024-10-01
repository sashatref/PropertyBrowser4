#include "project_pch.h"
#include "loadfileswidget.h"
#include "ui_loadfileswidget.h"
#include "fileitemdelegate.h"

LoadFilesWidget::LoadFilesWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadFilesWidget)
{
    ui->setupUi(this);
    ui->listWidget->setItemDelegate(m_delegate = new FileItemDelegate(this));
    ui->listWidget->addAction(ui->actionRemoveDuplicates);
    ui->listWidget->addAction(ui->actionRemoveItem);
    ui->listWidget->installEventFilter(this);
}

LoadFilesWidget::~LoadFilesWidget()
{
    delete ui;
}

void LoadFilesWidget::setReadOnly(bool _isReadOnly)
{
    ui->applyButton->setEnabled(!_isReadOnly);
}

void LoadFilesWidget::addStringList(const QStringList &_fileList)
{
    for(int i = 0 ; i < _fileList.size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setText(_fileList.at(i));
        item->setToolTip(_fileList.at(i));
    }
}

QStringList LoadFilesWidget::getStringList() const
{
    QStringList fileList;

    for(int i = 0 ; i< ui->listWidget->count(); i++)
    {
        fileList.append(ui->listWidget->item(i)->text());
    }
    return fileList;
}

void LoadFilesWidget::setSettings(const QString &_dialogCaption, const QString &_filter, const QString &_defaultDir, int _options)
{
    m_dialogCaption = _dialogCaption;
    m_filter = _filter;
    m_defaultDir = _defaultDir;
    m_options = _options;

    m_delegate->setSettings(m_dialogCaption,
                            m_filter,
                            m_defaultDir,
                            m_options);
}

void LoadFilesWidget::on_removeAllButton_clicked()
{
    ui->listWidget->clear();
}

void LoadFilesWidget::on_addButton_clicked()
{
    addStringList(getFiles());
}

void LoadFilesWidget::on_openButton_clicked()
{
    QStringList files = getFiles();
    if(files.size())
    {
        ui->listWidget->clear();
        addStringList(files);
    }
}

QStringList LoadFilesWidget::getFiles()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this,
                                                         m_dialogCaption,
                                                         m_defaultDir,
                                                         m_filter,
                                                         0,
                                                         static_cast<QFileDialog::Options>(m_options));
    return fileList;
}

void LoadFilesWidget::on_actionRemoveDuplicates_triggered()
{
    QStringList files = getStringList();
    files.removeDuplicates();
    ui->listWidget->clear();
    addStringList(files);
}

void LoadFilesWidget::on_actionRemoveItem_triggered()
{
    QList<QListWidgetItem*> selected = ui->listWidget->selectedItems();
    for(int i = selected.size() - 1; i > -1; i--)
    {
        delete selected.at(i);
    }
}


bool LoadFilesWidget::eventFilter(QObject *o, QEvent *e)
{
    if(o == ui->listWidget && e->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);
        if(keyEvent->key() == Qt::Key_Delete)
        {
            on_actionRemoveItem_triggered();
        }
    }

    return QObject::eventFilter(o, e);
}

void LoadFilesWidget::on_cancelButton_clicked()
{
    reject();
}

void LoadFilesWidget::on_applyButton_clicked()
{
    accept();
}
