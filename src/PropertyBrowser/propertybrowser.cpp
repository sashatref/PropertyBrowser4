#include "propertybrowser.h"
#include "ui_propertybrowser.h"

#include "interfacetool.h"
#include "priv/itemdelegate.h"
#include "propertybrowser_p.h"
#include <PropertyBrowserEditors/DefaultPropertyItem/defaultpropertyitem.h>
#include <PropertyBrowserEditors/PropertyBrowserEditors.h>

ObjectFactory<AbstractPropertyItem, int> PropertyBrowser::m_factory;

PropertyBrowser::PropertyBrowser(QWidget *parent)
    : QWidget(parent)
    , d(new PropertyBrowser_P(this))
    , ui(new Ui::PropertyBrowser)
{
    ui->setupUi(this);

    d->updateStyle();

    ui->undoView->setStack(d->m_undoStack);

    ui->label->setVisible(false);

    ui->treeWidget->installEventFilter(d);
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::Interactive);
    ui->splitter_2->setSizes(QList<int>() << 130 << 300);
    ui->splitter->setSizes(QList<int>() << 300 << 130);
    ui->treeWidget->setItemDelegate(d->m_delegate);
    ui->treeWidget->setReadOnly(&d->m_isReadOnly);

    connect(ui->treeWidget,
            &QTreeWidget::currentItemChanged,
            d,
            &PropertyBrowser_P::treeWidgetItemClicked);
    connect(ui->treeWidget,
            &QTreeWidget::customContextMenuRequested,
            d,
            &PropertyBrowser_P::customContextMenu);
    connect(ui->listWidget,
            &QListWidget::itemSelectionChanged,
            d,
            &PropertyBrowser_P::listWidgetItemSelectionChanged);
    connect(ui->addButton, &QToolButton::clicked, d, &PropertyBrowser_P::addButtonClicked);
    connect(ui->removeButton, &QToolButton::clicked, d, &PropertyBrowser_P::removeButtonClicked);
    connect(ui->actionDefault,
            &QAction::triggered,
            d,
            &PropertyBrowser_P::on_actionDefault_triggered);
    connect(ui->actionCopy, &QAction::triggered, d, &PropertyBrowser_P::on_actionCopy_triggered);
    connect(ui->actionPaste, &QAction::triggered, d, &PropertyBrowser_P::on_actionPaste_triggered);
    connect(ui->actionRedo, &QAction::triggered, d, &PropertyBrowser_P::on_actionRedo_clicked);
    connect(ui->actionUndo, &QAction::triggered, d, &PropertyBrowser_P::on_actionUndo_clicked);
    connect(ui->actionShowUndoRedoList,
            &QAction::triggered,
            d,
            &PropertyBrowser_P::on_actionShowUndoRedoList_clicked);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, d, &PropertyBrowser_P::onSearchTextChanged);
    connect(ui->configButton, &QToolButton::clicked, d, &PropertyBrowser_P::onCofigButtonClicked);
}

PropertyBrowser::~PropertyBrowser()
{
    clear();
    delete ui;
    delete d;
}

void PropertyBrowser::closeOpenedEditor()
{
    d->m_delegate->closeEditorIfOpened();
}

bool PropertyBrowser::checkObject()
{
    using namespace PropertyBrowser3Qt;

    return InterfaceTool::checkObject(getVariant(), this);
}

int PropertyBrowser::getConfigLineVisibility() const
{
    return ui->configWidget->isVisible();
}

void PropertyBrowser::setConfigLineVisibility(int _value)
{
    ui->configWidget->setVisible(_value);
    ui->horizontalLine->setVisible(_value);
}

bool PropertyBrowser::getReadOnly() const
{
    return d->m_isReadOnly;
}

void PropertyBrowser::setReadOnly(bool _isReadOnly)
{
    d->m_isReadOnly = _isReadOnly;
    ui->label->setEnabled(!_isReadOnly);

//    for (int i = 0, count = d->m_propertyItemMap.size(); i < count; ++i)
//    {
//        const QString key = d->m_propertyItemMap.keys().at(i);
//        AbstractPropertyItem *item = d->m_propertyItemMap[key];
//        item->onSetReadOnly(_isReadOnly);
//    }
}

bool PropertyBrowser::getLabelVisible() const
{
    return ui->label->isVisible();
}

void PropertyBrowser::setLabelVisible(bool _isVisible)
{
    ui->label->setVisible(_isVisible);
}

QString PropertyBrowser::getLabelText() const
{
    return ui->label->text();
}

void PropertyBrowser::setLabelText(const QString &_text)
{
    ui->label->setText(_text);
}

QFont PropertyBrowser::getLabelFont() const
{
    return ui->label->font();
}

void PropertyBrowser::setLabelFont(const QFont &_font)
{
    ui->label->setFont(_font);
}

int PropertyBrowser::getLabelMargin() const
{
    return ui->label->margin();
}

void PropertyBrowser::setLabelMargin(int _margin)
{
    ui->label->setMargin(_margin);
}

void PropertyBrowser::registerType()
{
    Converters::registerToListConverter<int>();
}

void PropertyBrowser::setSingleRowColor(const QString &_propertyName, const QColor &_color)
{
    for(auto it = d->m_propertyItemMap.begin(); it != d->m_propertyItemMap.end(); ++it)
    {
        QString key = it.key();
        AbstractPropertyItem *currItem = it.value();
        if(key == _propertyName)
        {
            currItem->getTreeItem()->setBackgroundColor(1, _color);
        } else
        {
            currItem->getTreeItem()->setBackground(1, QBrush());
        }
    }
}

void PropertyBrowser::clearUndoList()
{
    d->m_undoStack->clear();
}

void PropertyBrowser::registerTypeEditor(int _type,
                                         std::function<AbstractPropertyItem *()> _createFunc)
{
    m_factory.add(_type, _createFunc);
}

void PropertyBrowser::registerEnumEditor(int _type)
{
    // m_factory.add(_type, []{return new IntPropertyItem();});
}

void PropertyBrowser::setSearchLineVisible(bool _isVisible)
{
    ui->searchLineEdit->setVisible(_isVisible);
}

bool PropertyBrowser::getSearchLineVisible() const
{
    return ui->searchLineEdit->isVisible();
}

void PropertyBrowser::setAddButtonEnable(bool _isEnable)
{
    ui->addButton->setEnabled(_isEnable);
}

bool PropertyBrowser::getAddButtonEnable() const
{
    return ui->addButton->isEnabled();
}

void PropertyBrowser::setControlPanelVisible(bool _isVisible)
{
    ui->horizontalWidget->setVisible(_isVisible);
}

bool PropertyBrowser::getControlPanelVisible() const
{
    return ui->horizontalWidget->isVisible();
}

void PropertyBrowser::setRemoveButtonEnable(bool _isEnable)
{
    ui->removeButton->setEnabled(_isEnable);
}

bool PropertyBrowser::getRemoveButtonEnable() const
{
    return ui->removeButton->isEnabled();
}

void PropertyBrowser::setCallBackObject(QObject *const _object)
{
    d->m_callBackObject2 = _object;
}

bool PropertyBrowser::getDragAndDropEnable() const
{
    return ui->listWidget->dragEnabled();
}

void PropertyBrowser::setDragAndDropEnable(bool _isEnable)
{
    ui->listWidget->setDragEnabled(_isEnable);
}

QVariant PropertyBrowser::getSelectedObject() const
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.size() == 0) return QVariant();

    return items.first()->data(Qt::UserRole);
}

void PropertyBrowser::selectRowWhere(std::function<bool(const QVariant &)> _callback)
{
    ui->listWidget->clearSelection();

    for (int i = 0, count = ui->listWidget->count(); i < count; ++i)
    {
        QListWidgetItem *item = ui->listWidget->item(i);

        if(_callback(item->data(Qt::UserRole)))
        {
            item->setSelected(true);
            ui->listWidget->scrollToItem(item, QAbstractItemView::EnsureVisible);
            return;
        }
    }
}

void PropertyBrowser::setDescriptionVisible(bool _isVisible)
{
    ui->textBrowser->setVisible(_isVisible);
}

bool PropertyBrowser::getDescriptionVisible() const
{
    return ui->textBrowser->isVisible();
}

void PropertyBrowser::setMultiObjectListVisible(bool _isVisible)
{
    ui->widget->setVisible(_isVisible);
}

bool PropertyBrowser::getMultiObjectListVisible() const
{
    return ui->widget->isVisible();
}

void PropertyBrowser::setDescriptionFont(const QFont &_font)
{
    ui->textBrowser->setFont(_font);
}

const QFont &PropertyBrowser::getDescriptionFont() const
{
    return ui->textBrowser->font();
}

void PropertyBrowser::setListFont(const QFont &_font)
{
    ui->listWidget->setFont(_font);
}

const QFont &PropertyBrowser::getListFont() const
{
    return ui->listWidget->font();
}

void PropertyBrowser::setTreeFont(const QFont &_font)
{
    ui->treeWidget->setFont(_font);
}

const QFont &PropertyBrowser::getTreeFont() const
{
    return ui->treeWidget->font();;
}

AbstractPropertyItem *PropertyBrowser::getProperty(const QString &_propertyName)
{
    if(d->m_propertyItemMap.contains(_propertyName))
    {
        return d->m_propertyItemMap[_propertyName];
    }

    return nullptr;
}

void PropertyBrowser::translate()
{  
    using namespace PropertyBrowser3Qt;

    QVariant var = getVariant();
    QObject *obj = ObjectHelper::getObject(var, false);
    IGadget *gadget = GadgetHelper::getIGadget(var, false);

    if(!obj && !gadget) return;

    d->m_propertyInfoMap = InterfaceTool::getPropInfoMap(var);

    for(auto it = d->m_propertyItemMap.begin(); it != d->m_propertyItemMap.end(); ++it)
    {
        if(d->m_propertyInfoMap.contains(it.key()))
        {
            it.value()->getTreeItem()->parent()->setText(0, d->m_propertyInfoMap[it.key()].m_group);
            it.value()->setPropertyCaption(d->m_propertyInfoMap[it.key()].m_caption);
            it.value()->setDescription(d->m_propertyInfoMap[it.key()].m_description);
            it.value()->updateTextValue();
        }
    }

    d->treeWidgetItemClicked(0, 0);
}

bool PropertyBrowser::checkTree()
{
    d->clearWarnings();

    for(auto it = d->m_propertyItemMap.begin(); it != d->m_propertyItemMap.end(); ++it)
    {
        if(!it.value()->checkItem())
        {
            it.value()->setWarning(true);
            QMessageBox::information(this, tr("Ошибка проверки"), it.value()->getCheckErrorMessage());
            return false;
        }
    }

    return true;
}

void PropertyBrowser::clear()
{
    qDeleteAll(d->m_propertyItemMap);

    d->m_delegate->m_stopSave = true;
    d->m_topLevelItem = 0;
    ui->treeWidget->clear();
    d->m_propertyItemMap.clear();
    d->m_delegate->m_stopSave = false;
}

void PropertyBrowser::setVariant(const QVariant &_value)
{
    QVariantList list;
    list.push_back(_value);
    setVariantList(list);
}

QVariant PropertyBrowser::getVariant() const
{
    QListWidgetItem *currentItem = ui->listWidget->currentItem();
    if(currentItem)
    {
        return currentItem->data(Qt::UserRole);
    }
    if(ui->listWidget->count() > 0)
    {
        return ui->listWidget->item(0)->data(Qt::UserRole);
    }
    return QVariant();
}

void PropertyBrowser::setVariantList(const QVariantList &_valueList)
{
    QVariantList list = _valueList;

    for(auto &item : list)
    {
        item.detach();
    }

    d->initListWidget(list);
}

QVariantList PropertyBrowser::getVariantList() const
{
    QVariantList list;
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        list.append(ui->listWidget->item(i)->data(Qt::UserRole));
    }
    return list;
}

void PropertyBrowser::setReadOnly(const QString &_propertyName, bool _isReadOnly)
{
    if(d->m_propertyItemMap.contains(_propertyName))
    {
        d->m_propertyItemMap[_propertyName]->setReadOnly(_isReadOnly);
    }
}

void PropertyBrowser::selectAllObjects()
{
    ui->listWidget->selectAll();
}

const QVariant &PropertyBrowser::propertyValue(const QString &_propertyName) const
{
    if(d->m_propertyItemMap.contains(_propertyName))
    {
        return d->m_propertyItemMap[_propertyName]->getValue();
    } else
    {
        return d->m_emptyVariant;
    }
}

void PropertyBrowser::setPropertyValue(const QString &_propertyName,
                                       const QVariant &_value,
                                       bool notify)
{
    if(d->m_propertyItemMap.contains(_propertyName))
    {
        d->m_propertyItemMap[_propertyName]->setValue(_value, notify);
        d->m_propertyItemMap[_propertyName]->updateTextValue();
    }
}

void PropertyBrowser::setCreateObjectType(const int _type)
{
    d->m_createObjectType = _type;
}

int PropertyBrowser::getCreateObjectType() const
{
    return d->m_createObjectType;
}

void PropertyBrowser::closeEvent(QCloseEvent *event)
{
    emit propertyBrowserClosed();
    QWidget::closeEvent(event);
}

void PropertyBrowser::changeEvent(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::LanguageChange:
        d->updateLanguage();
        break;
    case QEvent::StyleChange:
        d->updateStyle();
    default:
        break;
    }
    QWidget::changeEvent(event);
}

void PropertyBrowser::showEvent(QShowEvent *)
{
    ui->treeWidget->header()->resizeSections(QHeaderView::Stretch);
}

void PropertyBrowser::registerBaseTypes()
{
    using namespace PropertyBrowser3Qt;

    AssignEditors(m_factory);
}

AbstractPropertyItem *PropertyBrowser::addItem(const QString &_propertyName,
                                               int _propertyType,
                                               QTreeWidgetItem *_treeItem,
                                               const PropertyInfo &_propInfo,
                                               const QMetaProperty &_metaProperty)
{
    using namespace PropertyBrowser3Qt;

    if(!_treeItem) return 0;
    QTreeWidgetItem *groupTreeItem = TreeWidgetUtils::findByName(_treeItem, _propInfo.m_group, 0);

    if(!groupTreeItem)
    {
        if(_propInfo.m_group == "")
        {
            groupTreeItem = _treeItem;
        } else
        {
            groupTreeItem = new QTreeWidgetItem(_treeItem);
            groupTreeItem->setText(0, _propInfo.m_group);

            InterfaceTool::applyItemAsGroup(groupTreeItem);
        }
    }

    QTreeWidgetItem *item = new QTreeWidgetItem(groupTreeItem);
    item->setHidden(_propInfo.m_isHidden);
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    groupTreeItem->setExpanded(true);

    InterfaceTool::applyItemAsValue(item);

    AbstractPropertyItem *propertyItem = 0;

    if(m_factory.isRegistered(_propertyType))
    {
        propertyItem = m_factory.create(_propertyType);
    } else
    {
        propertyItem = new DefaultPropertyItem();
    }

    if(propertyItem)
    {
        propertyItem->initProperty(_propertyName, _propInfo, item, _metaProperty);
    }

    if(propertyItem->isPermanent())
    {
        QWidget *wdg = propertyItem->createEditor(_treeItem->treeWidget());
        //propertyItem->onSetReadOnly(wdg, d->m_isReadOnly);
        _treeItem->treeWidget()->setItemWidget(item, 1, wdg);
    }

    item->setData(1, Qt::UserRole, QVariant::fromValue(propertyItem));

    return propertyItem;
}

QVariant PropertyBrowser::saveWidgetState() const
{
    LayoutSaver saver;
    saver.saveGeometry(this, "geometry");
    saver.save(ui->splitter, "splitter1");
    saver.save(ui->splitter_2, "splitter2");
    saver.save(ui->treeWidget->header(), "treeState");
    saver.save(ui->undoView->isVisible(), "undoLogVisible");
    saver.save(d->m_treeFont, "treeFont");
    saver.save(d->m_listFont, "listFont");
    saver.save(d->m_searchHistoryCount, "searchHistoryCount");

    return saver;
}

void PropertyBrowser::loadWidgetState(const QVariant &_data)
{
    const LayoutSaver saver = _data.toMap();
    saver.loadGeometry(this, "geometry");
    saver.load(ui->splitter, "splitter1");
    saver.load(ui->splitter_2, "splitter2");
    saver.load(ui->treeWidget->header(), "treeState");
    ui->undoView->setVisible(saver["undoLogVisible"].toBool());

    saver.load(d->m_treeFont, "treeFont");
    saver.load(d->m_listFont, "listFont");
    saver.load(d->m_searchHistoryCount, "searchHistoryCount");

    d->applyConf();
}

QString PropertyBrowser::getWidgetUniqueName() const
{
    return objectName();
}
