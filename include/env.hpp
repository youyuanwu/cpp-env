#include <iostream>
#include <cstdlib>
#include <charconv> // number parsing
#include "refl.hpp"

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

template<typename T>
T toType(std::string &s) {
    T value{};

    //if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>) {
        // numbers 
    auto [ptr, error] = std::from_chars(s.data(), s.data() + s.size(), value);

    if (error != std::errc{}) {
        // error with the conversion
        throw new std::invalid_argument("value invalid: " + s);
    } else {
        // conversion successful, do stuff with value
    }

    return value;
}

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

            // member can be numeric type
            //auto x = member.value_type;
            if constexpr (std::is_integral_v<std::remove_reference_t<decltype(member(value))>> || std::is_floating_point_v<std::remove_reference_t<decltype(member(value))>>) {
                    member(value) = toType<std::remove_reference_t<decltype(member(value))>>(val);
            }else if constexpr (std::is_same<std::remove_reference_t<decltype(member(value))>, std::remove_reference_t<decltype(val)>>::value){
                    member(value) = val;
            }else{
                std::cout << "mismatch " << fieldName << '\n'<<'\n';
                //std::cout << decltype(member(value)) << "--" << decltype(val) << '\n';
            }
            
            //member(value) = toType(val)
        }
    });
}