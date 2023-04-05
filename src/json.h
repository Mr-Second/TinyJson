#pragma once

#include <ostream>
#include <memory>
#include <string>

namespace UT
{
    namespace json
    {
        enum class type : int
        {
            Null,
            True,
            False,
            Number,
            String,
            Array,
            Object
        };

        std::ostream& operator<<(std::ostream& out, type t) noexcept;

        class Value;
    }

    class Json final
    {
    public:
        void decode(const std::string &content, std::string &status) noexcept;
        void decode(const std::string &content);
        void stringify(std::string &content) const noexcept;

        Json() noexcept;
        ~Json() noexcept;

        Json(const Json &rhs) noexcept;
        Json &operator=(const Json &rhs) noexcept;

        Json(Json &&rhs) noexcept;
        Json &operator=(Json &&rhs) noexcept;

        void swap(Json &rhs) noexcept;

    public:
        Json &operator=(bool b) noexcept
        {
            set_boolean(b);
            return *this;
        }

        Json &operator=(double number) noexcept
        {
            set_number(number);
            return *this;
        }

        Json &operator=(const std::string &str) noexcept
        {
            set_string(str);
            return *this;
        }

    public:
        json::type get_type() const noexcept;
        void set_null() noexcept;
        void set_boolean(bool b) noexcept;

        double get_number() const noexcept;
        void set_number(double d) noexcept;

        const std::string get_string() const noexcept;
        void set_string(const std::string &str) noexcept;

        size_t get_array_size() const noexcept;
        Json get_array_element(size_t index) const noexcept;
        void set_array() noexcept;
        void push_back_array_element(const Json &val) noexcept;
        void pop_back_array_element() noexcept;
        void insert_array_element(const Json &val, size_t index) noexcept;
        void erase_array_element(size_t index, size_t count) noexcept;
        void clear_array() noexcept;

        void set_object() noexcept;
        size_t get_object_size() const noexcept;
        const std::string &get_object_key(size_t index) const noexcept;
        size_t get_object_key_length(size_t index) const noexcept;

        Json get_object_value(size_t index) const noexcept;
        void set_object_value(const std::string& key, const Json &val) noexcept;
        long long find_object_index(const std::string& key) const noexcept;
        void remove_object_value(size_t index) noexcept;
        void clear_object() noexcept;

    private:
        std::unique_ptr<json::Value> v;

        friend bool operator==(const Json &lhs, const Json &rhs) noexcept;
        friend bool operator!=(const Json &lhs, const Json &rhs) noexcept;
    };

    bool operator==(const Json &lhs, const Json &rhs) noexcept;
    bool operator!=(const Json &lhs, const Json &rhs) noexcept;
    void swap(Json &lhs, Json &rhs) noexcept;
}