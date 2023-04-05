#include <exception>
#include <memory>
#include <utility>

#include "json.h"
#include "jsonValue.h"
#include "jsonException.h"

namespace UT
{

    void Json::decode(const std::string &content, std::string &status) noexcept
    {
        try
        {
            decode(content);
            status = "parse ok";
        }
        catch (const json::Exception &msg)
        {
            status = msg.what();
        }
        catch (...)
        {
        }
    }

    void Json::decode(const std::string &content)
    {
        v->decode(content);
    }

    void Json::stringify(std::string &content) const noexcept
    {
        v->stringify(content);
    }

    Json::Json() noexcept : v(new json::Value) {}
    Json::~Json() noexcept = default;

    Json::Json(const Json &rhs) noexcept
    {
        v = std::make_unique<json::Value>(*(rhs.v));
    }

    Json &Json::operator=(const Json &rhs) noexcept
    {
        v = std::make_unique<json::Value>(*(rhs.v));
        return *this;
    }

    Json::Json(Json &&rhs) noexcept
    {
        v = std::move(rhs.v);
    }

    Json &Json::operator=(Json &&rhs) noexcept
    {
        v = std::move(rhs.v);
        return *this;
    }

    void Json::swap(Json &rhs) noexcept
    {
        using std::swap;
        swap(v, rhs.v);
    }

    json::type Json::get_type() const noexcept
    {
        if (v == nullptr)
            return json::type::Null;

        return v->get_type();
    }
    void Json::set_null() noexcept
    {
        v->set_type(json::type::Null);
    }

    void Json::set_boolean(bool b) noexcept
    {
        if (b)
            v->set_type(json::type::True);
        else
            v->set_type(json::type::False);
    }
    double Json::get_number() const noexcept
    {
        return v->get_number();
    }

    void Json::set_number(double d) noexcept
    {
        v->set_number(d);
    }

    const std::string Json::get_string() const noexcept
    {
        return v->get_string();
    }
    void Json::set_string(const std::string &str) noexcept
    {
        v->set_string(str);
    }

    size_t Json::get_array_size() const noexcept
    {
        return v->get_array_size();
    }
    Json Json::get_array_element(size_t index) const noexcept
    {
        Json ret;
        ret.v = std::make_unique<json::Value>(v->get_array_element(index));
        return ret;
    }
    void Json::set_array() noexcept
    {
        v->set_array(std::vector<json::Value>{});
    }
    void Json::push_back_array_element(const Json &val) noexcept
    {
        v->push_back_array_element(*val.v);
    }
    void Json::pop_back_array_element() noexcept
    {
        v->pop_back_array_element();
    }
    void Json::insert_array_element(const Json &val, size_t index) noexcept
    {
        v->insert_array_element(*val.v, index);
    }
    void Json::erase_array_element(size_t index, size_t count) noexcept
    {
        v->erase_array_element(index, count);
    }
    void Json::clear_array() noexcept
    {
        v->clear_array();
    }
    void Json::set_object() noexcept
    {
        v->set_object(std::vector<std::pair<std::string, json::Value>>{});
    }
    size_t Json::get_object_size() const noexcept
    {
        return v->get_object_size();
    }
    const std::string &Json::get_object_key(size_t index) const noexcept
    {
        return v->get_object_key(index);
    }
    size_t Json::get_object_key_length(size_t index) const noexcept
    {
        return v->get_object_key_length(index);
    }
    Json Json::get_object_value(size_t index) const noexcept
    {
        Json ret;
        ret.v = std::make_unique<json::Value>(v->get_object_value(index));
        return ret;
    }
    void Json::set_object_value(const std::string& key, const Json &val) noexcept
    {
        v->set_object_value(key, *val.v);
    }
    long long Json::find_object_index(const std::string& key) const noexcept
    {
        return v->find_object_index(key);
    }
    void Json::remove_object_value(size_t index) noexcept
    {
        v->remove_object_value(index);
    }
    void Json::clear_object() noexcept
    {
        v->clear_object();
    }
    bool operator==(const Json &lhs, const Json &rhs) noexcept
    {
        return *lhs.v == *rhs.v;
    }
    bool operator!=(const Json &lhs, const Json &rhs) noexcept
    {
        return *lhs.v != *rhs.v;
    }
    void swap(Json &lhs, Json &rhs) noexcept
    {
        lhs.swap(rhs);
    }
}

std::ostream &UT::json::operator<<(std::ostream &out, type t) noexcept
{
    switch (t)
    {
    case type::Null:
        out << "Null";
        break;
    case type::True:
        out << "True";
        break;
    case type::False:
        out << "False";
        break;
    case type::Number:
        out << "Number";
        break;
    case type::String:
        out << "String";
        break;
    case type::Array:
        out << "Array";
        break;
    case type::Object:
        out << "Object";
        break;
    }

    return out;
}
