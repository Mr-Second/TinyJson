#pragma once

#include <string>
#include <stdexcept>

namespace UT
{
    namespace json {
        class Exception final: public std::logic_error {
            public:
            explicit Exception(const std::string& errMsg): logic_error(errMsg) {}
        };
    };
}
