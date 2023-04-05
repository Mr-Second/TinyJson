#pragma once

#include <string>
#include <vector>
#include <variant>
#include <utility>

#include "json.h"

namespace UT::json {
        class Value final {
            public:
                Value() noexcept {num_ = 0;};
                Value(const Value& rhs) noexcept {init(rhs);}
                Value& operator=(const Value& rhs) noexcept;
                ~Value() noexcept;

            public:
                void decode(const std::string& content);
                void stringify(std::string& content) const noexcept;

                type get_type() const noexcept;
                void set_type(type t) noexcept;

                double get_number() const noexcept;
                void set_number(double d) noexcept;

                const std::string& get_string() const noexcept;
                void set_string(const std::string& str) noexcept;

                size_t get_array_size() const noexcept;
                const Value& get_array_element(size_t index) const noexcept;
                void set_array(const std::vector<Value>&) noexcept;
                void push_back_array_element(const Value& val) noexcept;
                void pop_back_array_element() noexcept;
                void insert_array_element(const Value& val, size_t index) noexcept;
                void erase_array_element(size_t index, size_t count) noexcept;
                void clear_array() noexcept;

                size_t get_object_size() const noexcept;
                const std::string& get_object_key(size_t index) const noexcept;
                size_t get_object_key_length(size_t index) const noexcept;

                const Value& get_object_value(size_t index) const noexcept;
                void set_object_value(const std::string& key, const Value& val) noexcept;
                void set_object(const std::vector<std::pair<std::string, Value>>& obj) noexcept;

                long long find_object_index(const std::string& key) const noexcept;
                void remove_object_value(size_t index) noexcept;

                void clear_object() noexcept;

            private:
                void init(const Value& rhs) noexcept;
                void free() noexcept;

                json::type type_ = json::type::Null;

                union {
                    double num_;
                    std::string str_;
                    std::vector<Value> arr_;
                    std::vector<std::pair<std::string, Value>> obj_;
                };

                friend bool operator==(const Value& rhs, const Value& lhs) noexcept;
        };

        bool operator==(const Value& rhs, const Value& lhs) noexcept;
        bool operator!=(const Value& rhs, const Value& lhs) noexcept;
    }