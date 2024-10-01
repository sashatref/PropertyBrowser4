#pragma once

#include <PropertyBrowserCore/propertyinfo.h>

#include "ipropertyinfomap.h"

namespace PropertyBrowser3Qt {
class IDecoratorBase;

namespace InterfaceTool {

PropertyInfoMapType getPropInfoMap(const QVariant &_val);
IPropertyBrowserBase *getIPropertyBase(const QVariant &_val);

QSharedPointer<IDecoratorBase> getIDecoratorBase(const QVariant &_val);

void getListItemName(const QVariant &_val, int _index, QString &_text);
bool checkObject(const QVariant &_variant, QWidget *_parent);

void applyItemAsGroup(QTreeWidgetItem *_item);
void applyItemAsValue(QTreeWidgetItem *_item);

} // namespace InterfaceTool
} // namespace PropertyBrowser3Qt
