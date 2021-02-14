#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.h"

class TypesAndTraits : public ::testing::Test
{

protected:
    using key_type = size_t;
    using value_type = size_t;

    using map = std::map<key_type, value_type>;
    using iterator = map::iterator;

    using map_key_iterator = key_iterator<iterator>;
    using map_value_iterator = value_iterator<iterator>;
};

class Usage : public ::testing::Test
{
protected:
    std::map<std::string, size_t> data {{"1", 1},
                                        {"2", 3},
                                        {"5", 5},
                                        {"4", 4},
                                        {"7", 7}};
};

//https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Member_Detector
#define GENERATE_HAS_MEMBER_TYPE(Type)                                            \
                                                                                  \
template < class T >                                                              \
class HasMemberType_##Type                                                        \
{                                                                                 \
private:                                                                          \
    using Yes = char[2];                                                          \
    using  No = char[1];                                                          \
                                                                                  \
    struct Fallback { struct Type { }; };                                         \
    struct Derived : T, Fallback { };                                             \
                                                                                  \
    template < class U >                                                          \
    static No& test ( typename U::Type* );                                        \
    template < typename U >                                                       \
    static Yes& test ( U* );                                                      \
                                                                                  \
public:                                                                           \
    static constexpr bool RESULT = sizeof(test<Derived>(nullptr)) == sizeof(Yes); \
};                                                                                \
                                                                                  \
template < class T >                                                              \
struct has_member_type_##Type                                                     \
: public std::integral_constant<bool, HasMemberType_##Type<T>::RESULT>            \
{ };
