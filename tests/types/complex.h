/**
    @file
    @author  Alexander Sherikov

    @copyright 2018 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once

#include "complex_base.h"

class ConfigurableComplex : public ariles::ConfigurableBase, public ConfigurableComplexBase<ConfigurableComplex>
{
    #define ARILES_SECTION_ID "ConfigurableComplex"
    #define ARILES_CONSTRUCTOR ConfigurableComplex


    #define ARILES_ENTRIES_STANDARD_TYPES \
        ARILES_TYPED_ENTRY_(integer,     int) \
        ARILES_TYPED_ENTRY_(unsigned_integer, std::size_t) \
        ARILES_TYPED_ENTRY_(real,        double) \
        ARILES_TYPED_ENTRY_(string,      std::string) \
        ARILES_TYPED_ENTRY_(std_vector,          std::vector<double>) \
        ARILES_TYPED_ENTRY_(std_nested_vector,   std::vector< std::vector<double> >) \
        ARILES_TYPED_ENTRY_(enum, SomeEnum) \
        ARILES_ENTRY_(std_pair) \
        ARILES_ENTRY_(std_map)


#ifdef ARILES_ADAPTER_EIGEN
    #define ARILES_ENTRIES_1 \
        ARILES_ENTRIES_STANDARD_TYPES \
        ARILES_TYPED_ENTRY_(vector,      Eigen::Vector3d) \
        ARILES_TYPED_ENTRY_(matrix,      Eigen::Matrix3d) \
        ARILES_TYPED_ENTRY_(matrix_x,    Eigen::MatrixXd) \
        ARILES_TYPED_ENTRY_(std_vector_evector,  std::vector<Eigen::Vector3d>) \
        ARILES_TYPED_ENTRY_(std_nested_vector_evector, std::vector< std::vector<Eigen::Vector3d> >) \
        ARILES_TYPED_ENTRY_(isometry,    Eigen::Isometry3d) \
        ARILES_TYPED_ENTRY_(quaternion,  Eigen::Quaterniond)
#else
    #define ARILES_ENTRIES_1 ARILES_ENTRIES_STANDARD_TYPES
#endif


#ifdef ARILES_ADAPTER_BOOSTPTR
    #define ARILES_ENTRIES_2 \
        ARILES_ENTRIES_1 \
        ARILES_TYPED_ENTRY_(shared_ptr_double,          boost::shared_ptr<double>) \
        ARILES_TYPED_ENTRY_(shared_ptr_double_null,     boost::shared_ptr<double>)
#else
    #define ARILES_ENTRIES_2 ARILES_ENTRIES_1
#endif


    #define ARILES_ENTRIES ARILES_ENTRIES_2
    #include ARILES_INITIALIZE

#undef ARILES_ENTRIES_STANDARD_TYPES
#undef ARILES_ENTRIES_1
#undef ARILES_ENTRIES_2

    public:
        std::pair<std::string, double>  std_pair_;
        std::map<std::string, std::vector<std::string> > std_map_;


    public:
        ConfigurableComplex()
        {
            setDefaults();
        }

        virtual void setDefaults()
        {
            ConfigurableComplexBase<ConfigurableComplex>::setDefaults();
        }
};
