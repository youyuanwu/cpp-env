#include <iostream>
#include <cstdlib>
#include <string>
#include "refl.hpp"

namespace env {

std::string getEnv( std::string const & key , bool & exist)
{
    char * val = std::getenv( key.c_str() );
    if (val == NULL) {
        exist = false;
        return "";
    }
    exist = true;
    return std::string(val);
}

// static assert for constexpr
template<bool flag = false> void static_type_not_supported() { static_assert(flag, "type in user struct is not supported"); }

struct serializable : refl::attr::usage::field
{
};

template <typename T>
void Parse(T&& value)
{
    // iterate over the members of T
    for_each(refl::reflect(value).members, [&](auto member)
    {
        // is_readable checks if the member is a non-const field
        // or a 0-arg const-qualified function marked with property attribute
        if constexpr (is_readable(member) && refl::descriptor::has_attribute<serializable>(member))
        {
            auto fieldName = get_display_name(member);
            bool exist;
            std::string val = getEnv(fieldName, exist);

            std::cout << "fieldName:" << fieldName << '\n';
            std::cout << "val:" << val << '\n';
            std::cout << "exist:" << exist << '\n';

            if constexpr (std::is_same<std::remove_reference_t<decltype(member(value))>, std::string>::value){
                // env is the same that we read
                member(value) = val;
            } else if constexpr (std::is_same<std::remove_reference_t<decltype(member(value))>, int>::value){
                member(value) = std::stoi(val);
            } else if constexpr (std::is_same<std::remove_reference_t<decltype(member(value))>, long>::value){
                member(value) = std::stol(val);
            } else if constexpr (std::is_same<std::remove_reference_t<decltype(member(value))>, long long>::value){
                member(value) = std::stoll(val);
            } else if constexpr (std::is_same<std::remove_reference_t<decltype(member(value))>, float>::value){
                member(value) = std::stof(val);
            } else if constexpr (true){
                // If compiler error out on this line it means that user struct field type is not supported
                static_type_not_supported();
            }

        }
    });
}

} // namespace