#pragma once

#include <HelperLibrary/objectfactory.h>
#include <HelperLibrary/Decorator/basedecorator.h>

#include "idecoratorbase.h"

namespace PropertyBrowser3Qt
{

class DecoratorFactory : public HelperLibraryNS::BaseDecoratorFactory<IDecoratorBase>
{
public:
    static DecoratorFactory &ins();
};

}
