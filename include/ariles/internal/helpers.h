/**
    @file
    @author  Alexander Sherikov

    @copyright 2017-2018 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once

#include <string>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <cstdlib>


#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_base_of.hpp>


#include "build_config.h"
#include "cpput_config.h"
#include "cpput_exception.h"
#include "cpput_floating_point_utils.h"
#include "cpput_misc.h"
#include "cpput_flags.h"

// #define ARILES_TRACE_ENABLE
#include "trace.h"


/// @todo DEPRECATED C++11
#define ARILES_EMPTY_MACRO


#define ARILES_IS_ENUM_ENABLER_TYPE(Enum) \
    const typename boost::enable_if_c< (boost::is_enum<Enum>::value) >::type

#define ARILES_IS_BASE_ENABLER(Base, Derived) \
    const typename boost::enable_if_c< (boost::is_base_of<Base, Derived>::value) >::type * = NULL

#define ARILES_IS_BASE_DISABLER(Base, Derived) \
    const typename boost::enable_if_c< not (boost::is_base_of<Base, Derived>::value) >::type * = NULL


#define ARILES_BASIC_SIGNED_INTEGER_TYPES_LIST \
    ARILES_BASIC_TYPE(int) \
    ARILES_BASIC_TYPE(short) \
    ARILES_BASIC_TYPE(long) \
    ARILES_BASIC_TYPE(char)

#define ARILES_BASIC_UNSIGNED_INTEGER_TYPES_LIST \
    ARILES_BASIC_TYPE(unsigned int) \
    ARILES_BASIC_TYPE(unsigned short) \
    ARILES_BASIC_TYPE(unsigned long) \
    ARILES_BASIC_TYPE(unsigned char)

#define ARILES_BASIC_INTEGER_TYPES_LIST \
    ARILES_BASIC_SIGNED_INTEGER_TYPES_LIST \
    ARILES_BASIC_UNSIGNED_INTEGER_TYPES_LIST

#define ARILES_BASIC_REAL_TYPES_LIST \
    ARILES_BASIC_TYPE(float) \
    ARILES_BASIC_TYPE(double) \

#define ARILES_BASIC_NUMERIC_TYPES_LIST \
    ARILES_BASIC_INTEGER_TYPES_LIST \
    ARILES_BASIC_REAL_TYPES_LIST \
    ARILES_BASIC_TYPE(bool)

#define ARILES_BASIC_TYPES_LIST \
    ARILES_BASIC_NUMERIC_TYPES_LIST \
    ARILES_BASIC_TYPE(std::string)


#ifndef ARILES_VISIBILITY_ATTRIBUTE
#   include "cpput_visibility.h"
#   define ARILES_VISIBILITY_ATTRIBUTE ARILES_LIB_EXPORT
#endif


namespace ariles
{
    template <class t_Pointer>
    class PointerHandler
    {
    };
}


namespace ariles
{
    namespace utils
    {
        template<class T>   struct DecayConst
        {
            typedef T Type;
        };
        template<class T>   struct DecayConst<const T>
        {
            typedef T Type;
        };
    }
}

#include "../configurable_flags.h"
#include "../bridge_flags.h"
