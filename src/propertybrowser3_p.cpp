#include "propertybrowser3_p.h"

#include "propertybrowser3.h"
#include "ui_propertybrowser3.h"
#include "itemdelegate.h"
#include "Editors/abstractpropertyitem.h"
#include "ipropertyinfomap.h"
#include "changepropertycommand.h"
#include "interfacetool.h"
#include "configuredialog.h"

PropertyBrowser3_P::PropertyBrowser3_P(PropertyBrowser3 *const _q):
    q                       (_q),
    m_undoStack             (new QUndoStack(this)),
    m_isReadOnly            (false),
    m_createObjectType      (0),
    m_topLevelItem          (0),
    m_delegate              (new ItemDelegate(&m_isReadOnly)),
    m_callBackObject2       (0),
    m_propertyInfoMap       (),
    m_propertyItemMap       (),
    m_expandedState         (),
    m_emptyVariant          ()
{

}

PropertyBrowser3_P::~PropertyBrowser3_P()
{
    delete m_delegate;
    delete m_undoStack;
}

void PropertyBrowser3_P::updateStyle()
{
    q->ui->addButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Plus2));
    q->ui->removeButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Minus2));
    q->ui->configButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Setting1));
}

void PropertyBrowser3_P::updateLanguage()
{
    q->ui->retranslateUi(q);
    q->translate();
}



void PropertyBrowser3_P::saveExpandedState()
{
    m_expandedState.clear();

    QList<QTreeWidgetItem*> array = TreeWidgetUtils::getAllSubItems(q->ui->treeWidget->topLevelItem(0));

    for(int i = 0 ; i < array.size(); i++)
    {
        QTreeWidgetItem *item = array[i];
        m_expandedState[item->text(0)] = item->isExpanded();
    }
}

void PropertyBrowser3_P::loadExpandedState()
{
    QList<QTreeWidgetItem*> array = TreeWidgetUtils::getAllSubItems(q->ui->treeWidget->topLevelItem(0));

    for(int i = 0 ; i < array.size(); i++)
    {
        if(m_expandedState.contains(array[i]->text(0)))
        {
            array[i]->setExpanded(m_expandedState[array[i]->text(0)]);
        } else
        {
            array[i]->setExpanded(true);
        }
    }
}

void PropertyBrowser3_P::clearWarnings()
{
    for(auto it = m_propertyItemMap.begin(); it != m_propertyItemMap.end(); ++it)
    {
        it.value()->setWarning(false);
    }
}

void PropertyBrowser3_P::updateProperties(const QVariantList &_valueList, const QStringList &_properties, bool sendNotify)
{
    //TODO: не понятно на сколько оно вообще надо, очень усложняет код

    for(int i = 0 ; i < _properties.size(); i++)
    {
        if(_valueList.size() == 1)
        {
            IGadget *gadget = _valueList[0].value<IGadget*>();

            if(!gadget)
            {
                qDebug() << QString("Property browser doesn't support this type <%1>").arg(_valueList[0].typeName());
                return;
            }

            const QMetaObject *mo = VariantHelper::getMetaObject(_valueList[0]);
            R_ASSERT_X(mo, "const QMetaObject *mo == 0");

            int propertyIndex = mo->indexOfProperty(_properties.at(i).toStdString().c_str());
            QMetaProperty property = mo->property(propertyIndex);

            QVariant value1 = VariantHelper::getProperty(_valueList[0], property.name());

            AbstractPropertyItem *itemToUpdate = m_propertyItemMap[_properties.at(i)];
            if(itemToUpdate)
            {
                itemToUpdate->setValue(value1, sendNotify);
                itemToUpdate->updateTextValue();
            }
        }
    }
}

void PropertyBrowser3_P::createProperties(const QVariantList &_valueList)
{
    using namespace PropertyBrowser3Qt;

    if(_valueList.size() == 0)
    {
        q->clear(); return;
    }

    m_propertyInfoMap = InterfaceTool::getPropInfoMap(_valueList.first());

    const QMetaObject *mo = VariantHelper::getMetaObject(_valueList.first());
    R_ASSERT_X(mo, "const QMetaObject *mo == 0");

    //получаем список всех объектов, для каждого получаем список свойств
//    QMap<QObject*, QStringList> map;
    QStringList properties;

    for(int i = 0 ; i < _valueList.size(); i++)
    {
        for(int j = 0, count = mo->propertyCount(); j < count; j++)
        {
            QMetaProperty property = mo->property(j);
            properties.append(property.name());
        }
    }

    //добавляем сформированный список свойств в дерево.

    for(const QString &it : properties)
    {
        int index = mo->indexOfProperty(it.toUtf8());
        int objectType = mo->property(index).userType();

        AbstractPropertyItem *addedItem = q->addItem(it,
                                                    objectType,
                                                    m_topLevelItem,
                                                    m_propertyInfoMap[it],
                                                    mo->property(index));
        m_propertyItemMap[it] = addedItem;
        connect(addedItem, &AbstractPropertyItem::valueChanged, this, &PropertyBrowser3_P::valueChanged);
        connect(addedItem, &AbstractPropertyItem::valueChanged2, this, &PropertyBrowser3_P::valueChanged2);
    }

    updateProperties(_valueList, properties);
}

void PropertyBrowser3_P::initListWidget(const QVariantList &_valueList)
{
    using namespace PropertyBrowser3Qt;

    saveExpandedState();

    q->ui->listWidget->clear();

    for(int i = 0 ; i < _valueList.size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(q->ui->listWidget);

        QString text = QString(tr("Item: %1")).arg(i);

        InterfaceTool::getListItemName(_valueList[i], i, text);

        item->setText(text);
        item->setData(Qt::UserRole, _valueList[i]);
    }

    const int listItemsCount = q->ui->listWidget->count();
    if(listItemsCount != 0)
    {
        q->ui->listWidget->setCurrentRow(listItemsCount - 1);
        q->ui->listWidget->item(listItemsCount - 1)->setSelected(true);
    }
}

void PropertyBrowser3_P::initVariantList(const QVariantList &_valueList)
{
    using namespace PropertyBrowser3Qt;

    q->clear();

    m_topLevelItem = new QTreeWidgetItem(q->ui->treeWidget);
    m_topLevelItem->setText(0, tr("Root"));
    InterfaceTool::applyItemAsGroup(m_topLevelItem);

    createProperties(_valueList);

    loadExpandedState();
}


void PropertyBrowser3_P::on_actionDefault_triggered()
{
    QVariant var2 = q->getVariant();
    QVariant copyVar(var2.userType(), 0);

    QList<QTreeWidgetItem*> items = q->ui->treeWidget->selectedItems();
    for(int i = 0 ; i < items.size(); i++)
    {
        QVariant var = items.at(i)->data(1, Qt::UserRole);
        AbstractPropertyItem *item = getPropertyItem(var);
        if(item)
        {
            item->setValue(VariantHelper::getProperty(copyVar, item->getPropertyName()));
            item->updateTextValue();
        }
    }
}

//выбираем списков выделеннех элементов дерева, проверяем есть ли в них AbstractPropertyItem
//если есть, то все значения складываем в список
//список сериализуем в QByteArray, QByteArray складываем в QMimeData
//QMimeData скаладываем в буфер обмена
void PropertyBrowser3_P::on_actionCopy_triggered()
{
    QList<QTreeWidgetItem*> items = q->ui->treeWidget->selectedItems();

    QVariantList selectedProperties;

    QMimeData *mimeData = new QMimeData();

    for(int i = 0 ; i < items.size(); i++)
    {
        QVariant var = items.at(i)->data(1, Qt::UserRole);
        AbstractPropertyItem *item = getPropertyItem(var);
        if(item)
        {
            selectedProperties.append(item->getValue());
        }
    }

    QByteArray baProperties;
    SerializerQt::Serializer::saveXmlNode(selectedProperties, baProperties);

    mimeData->setData("propertyBrowser3", baProperties);

    qApp->clipboard()->setMimeData(mimeData);
}

//считываем QByteArray из QMimeData из буфера обмена
//десериализуем QVariantList
//для выделенных веток дерева пытаемся установить значение.
void PropertyBrowser3_P::on_actionPaste_triggered()
{
    QByteArray baProperties = qApp->clipboard()->mimeData()->data("propertyBrowser3");

    QVariantList values;
    SerializerQt::Serializer::loadXmlNode(values, baProperties);

    QList<QTreeWidgetItem*> items = q->ui->treeWidget->selectedItems();

    int count = qMin(items.size(), values.size());

    for(int i = 0 ; i < count; i++)
    {
        QVariant var = items.at(i)->data(1, Qt::UserRole);
        AbstractPropertyItem *propItem = getPropertyItem(var);
        if(propItem && !propItem->getReadOnly())
        {
            propItem->setValue(values.at(i));
            propItem->updateTextValue();
        }
    }
}

void PropertyBrowser3_P::on_actionRedo_clicked()
{
    m_undoStack->redo();
}

void PropertyBrowser3_P::on_actionUndo_clicked()
{
    m_undoStack->undo();
}

void PropertyBrowser3_P::on_actionShowUndoRedoList_clicked(bool isChecked)
{
    q->ui->undoView->setVisible(isChecked);
}


void PropertyBrowser3_P::addButtonClicked()
{
    QVariant newObj;
    if(m_callBackObject2 && m_callBackObject2->metaObject()->indexOfMethod("createNewObject(int)") != -1)
    {
        QMetaObject::invokeMethod(m_callBackObject2,
                                  "createNewObject",
                                  Qt::DirectConnection,
                                  Q_RETURN_ARG(QVariant, newObj),
                                  Q_ARG(int, m_createObjectType));
    } else
    {
        newObj = QVariant(m_createObjectType, 0);
    }

    if(!newObj.isValid())
    {
        QMessageBox::warning(q, tr("Ошибка"), tr("Невозможно сконструировать тип <%1>").arg(m_createObjectType));
        return;
    }

    QVariantList list = q->getVariantList();
    list.push_back(newObj);
    initListWidget(list);
}

void PropertyBrowser3_P::removeButtonClicked()
{
    qDeleteAll(q->ui->listWidget->selectedItems());
    q->clear();
    QVariantList varList = q->getVariantList();
    if(varList.size() > 0)
    {
        q->ui->listWidget->item(varList.size() - 1)->setSelected(true);
        listWidgetItemSelectionChanged();
    }
}

void PropertyBrowser3_P::customContextMenu(const QPoint &_point)
{
    QMenu menu;
    menu.addAction(q->ui->actionCopy);
    menu.addAction(q->ui->actionPaste);
    menu.addAction(q->ui->actionDefault);
    menu.addSeparator();
    menu.addAction(q->ui->actionUndo);
    menu.addAction(q->ui->actionRedo);

    menu.exec(q->ui->treeWidget->mapToGlobal(_point));
}

void PropertyBrowser3_P::treeWidgetItemClicked(QTreeWidgetItem *_currentItem, QTreeWidgetItem * /*_prevItem*/)
{
    if(!_currentItem) {q->ui->textBrowser->clear(); return;}

    QVariant var = _currentItem->data(1, Qt::UserRole);
    AbstractPropertyItem *propItem = getPropertyItem(var);
    if(propItem)
    {
        q->ui->textBrowser->setText(QString("<b>%1</b><br>%2")
                                    .arg(_currentItem->text(0))
                                    .arg(propItem->getDescription()));
    } else
    {
        q->ui->textBrowser->clear();
    }
}

void PropertyBrowser3_P::listWidgetItemSelectionChanged()
{
    QVariantList list;

    for(auto *it : q->ui->listWidget->selectedItems())
    {
        list.push_back(it->data(Qt::UserRole));
    }
    initVariantList(list);
    m_undoStack->clear();
    q->setSingleRowColor("", QColor());
}

void PropertyBrowser3_P::valueChanged(const QString &_propertyName, const QVariant &_value)
{
    QList<QListWidgetItem*> selected = q->ui->listWidget->selectedItems();

    for(QListWidgetItem *it : selected)
    {
        QVariant var = it->data(Qt::UserRole);

        IGadget *gadget = var.value<IGadget*>();

        if(!gadget) return;

        const QMetaObject *mo = VariantHelper::getMetaObject(var);
        R_ASSERT_X(mo, "const QMetaObject *mo == 0");

        int index = mo->indexOfProperty(_propertyName.toStdString().c_str());

        if(!mo->property(index).isWritable()) return;

        VariantHelper::setProperty(var, mo->property(index).name(), _value);

        updateProperties(QVariantList() << var, m_propertyItemMap.keys(), false);
    }

    emit q->propertyValueChanged(_propertyName, _value);
}

void PropertyBrowser3_P::valueChanged2(const QString &_propertyName, const QVariant &_newValue, const QVariant &_oldValue)
{
    if(_newValue != _oldValue)
    {
        m_undoStack->push(new ChangePropertyCommand(_propertyName, _newValue, _oldValue, q));
    }
}

void PropertyBrowser3_P::onSearchTextChanged(const QString &_text)
{
    ///<ищем совпадения в списке студентов, игнорируя регистр букв, те что совпали отображаем, остальные скрываем
    for(int i = 0 ; i < q->ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = q->ui->listWidget->item(i);

        if(item->text().contains(_text, Qt::CaseInsensitive))
        {
            item->setHidden(false);
        } else
        {
            item->setHidden(true);
        }
    }
}

void PropertyBrowser3_P::onCofigButtonClicked()
{
    using namespace PropertyBrowser3Qt;

    ConfigureDialog conf(q);

    conf.setConf({m_treeFont, m_listFont, m_searchHistoryCount});
    if(conf.exec() == QDialog::Accepted)
    {
        TreeConfInfo res = conf.getConf();
        m_listFont = res.listFont;
        m_treeFont = res.treeFont;
        m_searchHistoryCount = res.historyCount;
        applyConf();
    }
}

void PropertyBrowser3_P::applyConf()
{
    q->ui->treeWidget->setFont(m_treeFont);
    q->ui->listWidget->setFont(m_listFont);
    //q->ui->searchToolBar->setMaximusHistoryItem(m_historyCount);
}

AbstractPropertyItem *PropertyBrowser3_P::getPropertyItem(QVariant &_var)
{
    QObject *obj = _var.value<QObject*>();
    return dynamic_cast<AbstractPropertyItem*>(obj);
}

bool PropertyBrowser3_P::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == q->ui->treeWidget)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

            if(keyEvent->modifiers().testFlag(Qt::ControlModifier))
            {
                switch(keyEvent->key())
                {
                case Qt::Key_L:
                    q->ui->actionShowUndoRedoList->trigger();
                    break;
                case Qt::Key_Z:
                    on_actionUndo_clicked();
                    break;
                case Qt::Key_Y:
                    on_actionRedo_clicked();
                    break;
                case Qt::Key_C:
                    on_actionCopy_triggered();
                    break;
                case Qt::Key_V:
                    on_actionPaste_triggered();
                    break;
                }
            }
        }
    }

    return QObject::eventFilter(watched, event);
}
