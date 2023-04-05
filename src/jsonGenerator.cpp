#include "jsonGenerator.h"

namespace UT {
    namespace json {
        Generator::Generator(const Value &val, std::string &result): res_(result)
        {
            res_.clear();
            stringify_value(val);  
        }

        void Generator::stringify_value(const Value &v)
        {
            switch (v.get_type())
            {
                case type::Null: res_ += "null"; break;
                case type::True: res_ += "true"; break;
                case type::False: res_ += "false"; break;
                case type::Number: {
                    char buffer[32] = {0};
                    sprintf(buffer, "%.17g", v.get_number());
                    res_ += buffer;
                }
                break;
                case type::String: stringify_string(v.get_string()); break;
                case type::Array: 
                    res_ += '[';
                    for(int i = 0; i < v.get_array_size(); ++i) {
                        if(i > 0) res_ += ',';
                        stringify_value(v.get_array_element(i));
                    }
                    res_ += ']';
                    break;
                case type::Object: 
                    res_ += '{';
                    for(int i = 0; i < v.get_object_size(); ++i) {
                        if(i > 0) res_ += ',';
                        stringify_string(v.get_object_key(i));
                        res_ += ':';
                        stringify_value(v.get_object_value(i));
                    }
                    res_ += '}';
                    break;
            }
        }

        void Generator::stringify_string(const std::string &str)
        {
            res_ += '\"';
            for(auto it = str.begin(); it != str.end(); ++it) {
                unsigned char ch = *it;
                switch (ch)
                {
                    case '\"': res_ += "\\\""; break;
                    case '\\': res_ += "\\\\"; break;
                    case '\b': res_ += "\\b"; break;
                    case '\f': res_ += "\\f"; break;
                    case '\n': res_ += "\\n"; break;
                    case '\r': res_ += "\\r"; break; 
                    case '\t': res_ += "\\t"; break; 

                    default: 
                        if(ch < 0x20) {
                            char buffer[7] = {0};
                            sprintf(buffer, "\\u%04X", ch);
                            res_ += buffer;
                        } else
                            res_ += *it;
                }
            }

            res_ += '\"';
        }
    }
}