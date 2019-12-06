#pragma once


#include <type_traits>
#include <functional>

#define define_property(property,typex) \
private:\
typex property; \
public:\
	std::function<void(typex const &)> property##_has_changed; \
	typex const & get_##property() const { return property;} \
 \
template<class Q = typex> \
typename std::enable_if<std::is_floating_point<Q>::value, void>::type set_##property(const Q& value) \
{ \
	if (property != value)\
    {             \
		if (abs(property - value) > 0.00001)\
        {             \
			if(property##_has_changed) {property##_has_changed(value);} \
            property = value; \
        }       \
    }             \
} \
template<class Q = typex> \
typename std::enable_if<!std::is_floating_point<Q>::value, void>::type set_##property(const Q& value) \
{ \
	if (property != value)\
    {             \
			if(property##_has_changed) {property##_has_changed(value);} \
		property = value; \
    }             \
} \

#define update_property(name)\
 if(desc.used.##name) \
 { \
	 set_##name##(desc.##name);\
 } \
