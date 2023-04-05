#pragma once

#include "jsonValue.h"

namespace UT::json {
        class Generator final {
            public:
                Generator(const Value& val, std::string& result);
            private:
                void stringify_value(const Value &v);
                void stringify_string(const std::string &str);

                std::string& res_; 
        };
    }