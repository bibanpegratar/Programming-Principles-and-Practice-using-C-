#include "Exception.h"

namespace Library_f::Exception
{
    Exception::Exception()
        : what_p{"unknown error"}
    {
    }

    Exception::Exception(std::string what)
        : what_p{what}
    {
    }
} // namespace Library_f::Exception