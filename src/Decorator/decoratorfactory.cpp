#include "decoratorfactory.h"

namespace PropertyBrowser3Qt
{
    DecoratorFactory &DecoratorFactory::ins()
    {
        static DecoratorFactory ins;
        return ins;
    }
}
