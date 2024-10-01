#include "PropertyBrowserEditors.h"

#include "PropertyBrowserEditors/BoolPropertyItem/boolpropertyitem.h"
#include "PropertyBrowserEditors/ByteArrayPropertyItem/bytearraypropertyitem.h"
#include "PropertyBrowserEditors/ColorPropertyItem/colorpropertyitem.h"
#include "PropertyBrowserEditors/DatePropertyItem/datepropertyitem.h"
#include "PropertyBrowserEditors/DateTimePropertyItem/datetimepropertyitem.h"
#include "PropertyBrowserEditors/DefaultPropertyItem/defaultpropertyitem.h"
#include "PropertyBrowserEditors/DoublePropertyItem/doublepropertyitem.h"
#include "PropertyBrowserEditors/FontPropertyItem/fontpropertyitem.h"
#include "PropertyBrowserEditors/IntPropertyItem/intpropertyitem.h"
#include "PropertyBrowserEditors/PixmapPropertyItem/PixmapPropertyItem.h"
#include "PropertyBrowserEditors/RectPropertyItem/rectpropertyitem.h"
#include "PropertyBrowserEditors/SizePropertyItem/sizepropertyitem.h"
#include "PropertyBrowserEditors/StringListPropertyitem/stringlistpropertyitem.h"
#include "PropertyBrowserEditors/StringPropertyItem/stringpropertyitem.h"
#include "PropertyBrowserEditors/TimePropertyItem/timepropertyitem.h"
#include "PropertyBrowserEditors/UrlPropertyItem/urlpropertyitem.h"
#include "PropertyBrowserEditors/VariantListPropertyItem/VariantListPropertyItem.h"
#include "PropertyBrowserEditors/VariantMapPropertyItem/VariantMapPropertyItem.h"

namespace PropertyBrowser3Qt {

void AssignEditors(ObjectFactory<AbstractPropertyItem, int> &_factory)
{
    // _factory.add<IntPropertyItem>(QVariant::Int);
    _factory.add<StringPropertyItem>(QVariant::String);
    _factory.add<DoublePropertyItem>(QVariant::Double);
    _factory.add<DatePropertyItem>(QVariant::Date);
    _factory.add<DateTimePropertyItem>(QVariant::DateTime);
    _factory.add<ByteArrayPropertyItem>(QVariant::ByteArray);
    _factory.add<BoolPropertyItem>(QVariant::Bool);
    _factory.add<FontPropertyItem>(QVariant::Font);
    // _factory.add<StringListPropertyItem>(QVariant::StringList);
    // _factory.add<VariantListPropertyItem>(QVariant::List);
    // _factory.add<ColorPropertyItem>            (QVariant::Color);
    _factory.add<UrlPropertyItem>(QVariant::Url);
    _factory.add<TimePropertyItem>(QVariant::Time);
    // _factory.add<PixmapPropertyItem>(QVariant::Pixmap);
    // _factory.add<RectPropertyItem>(QVariant::Rect);
    // _factory.add<SizePropertyItem>(QVariant::Size);
    // _factory.add<VariantMapPropertyItem>(QVariant::Map);
}

} // namespace PropertyBrowser3Qt
