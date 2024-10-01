#pragma once

#include <HelperLibrary/objectfactory.h>
#include <HelperLibrary/Decorator/basedecorator.h>
#include "../export.h"

#include "idecoratorbase.h"

namespace PropertyBrowser3Qt
{

class PROPERTYBROWSER3_EXPORT DecoratorFactory : public HelperLibraryNS::BaseDecoratorFactory<IDecoratorBase>
{
public:
    static DecoratorFactory &ins();
};

}
