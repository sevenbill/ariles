/**
    @file
    @author  Alexander Sherikov

    @copyright 2017-2018 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/


#define ARILES_API_VERSION 2

#include "utility.h"
#include "all_enabled_bridges.h"

#include "ariles/adapters_all.h"
#include "ariles/ariles2.h"


// ===============================================================
// TYPES
// ===============================================================

#include "types_api_v2/complex_auto_declare.h"
#include "types_api_v2/complex_verbose.h"



// ===============================================================
// FIXTURES
// ===============================================================


#include "fixtures_api_v2/initializers.h"
#include "fixtures_api_v2/000_basic_interface.h"
#include "fixtures_api_v2/002_comparison.h"
#include "fixtures_api_v2/003_comparison_vector.h"
#include "fixtures_api_v2/004_comparison_equivalence.h"


// ===============================================================
// TESTS
// ===============================================================

#define ARILES_TESTS(BRIDGE_ID, NAMESPACE, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(BasicInterfaceFixture, BRIDGE_ID, NAMESPACE, ConfigurableComplexVerbose, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(BasicInterfaceFixture, BRIDGE_ID, NAMESPACE, ConfigurableComplex, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(ComparisonSimpleFixture, BRIDGE_ID, NAMESPACE, ConfigurableComplexVerbose, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(ComparisonSimpleFixture, BRIDGE_ID, NAMESPACE, ConfigurableComplex, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(ComparisonMultiFixture, BRIDGE_ID, NAMESPACE, ConfigurableComplexVerbose, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(ComparisonMultiFixture, BRIDGE_ID, NAMESPACE, ConfigurableComplex, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(ComparisonVectorFixture, BRIDGE_ID, NAMESPACE, ConfigurableComplexVerbose, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(ComparisonVectorFixture, BRIDGE_ID, NAMESPACE, ConfigurableComplex, INITIALIZER) \
    BOOST_FIXTURE_TEST_CASE(ComparisonEquivalenceFixture##_##BRIDGE_ID##_##Equivalence##_##INITIALIZER, \
                            ariles_tests::ComparisonEquivalenceFixture<ariles_tests::initializers::INITIALIZER>) \
    { \
        test<ariles_tests::ConfigurableComplexVerbose, ariles_tests::ConfigurableComplex, ariles::NAMESPACE>(); \
    }


#include "instantiate.h"
