/**
    @file
    @author  Alexander Sherikov

    @copyright 2017-2018 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/


#define ARILES_API_VERSION 2

#include "utility.h"
#include "all_enabled_visitors.h"

#include "ariles/adapters_all.h"
#include "ariles/ariles2.h"


// ===============================================================
// TYPES
// ===============================================================

#include "types/inheritance.h"
#include "types/strictness.h"



// ===============================================================
// FIXTURES
// ===============================================================


#include "fixtures/initializers.h"
#include "fixtures/000_basic_interface.h"
#include "fixtures/002_comparison.h"
#include "fixtures/003_comparison_vector.h"
#include "fixtures/005_comparison_base.h"
#include "fixtures/007_strictness.h"


// ===============================================================
// TESTS
// ===============================================================

#define ARILES_TESTS(VISITOR_ID, NAMESPACE, INITIALIZER)                                                               \
    ARILES_FIXTURE_TEST_CASE(BasicInterfaceFixture, VISITOR_ID, NAMESPACE, ConfigurableDerived, INITIALIZER)           \
    ARILES_FIXTURE_TEST_CASE(ComparisonSimpleFixture, VISITOR_ID, NAMESPACE, ConfigurableDerived, INITIALIZER)         \
    ARILES_FIXTURE_TEST_CASE(ComparisonMultiFixture, VISITOR_ID, NAMESPACE, ConfigurableDerived, INITIALIZER)          \
    ARILES_FIXTURE_TEST_CASE(ComparisonVectorFixture, VISITOR_ID, NAMESPACE, ConfigurableDerived, INITIALIZER)         \
    ARILES_FIXTURE_TEST_CASE_2CLASSES(                                                                                 \
            StrictnessFixture, VISITOR_ID, NAMESPACE, ConfigurableStrictness1, ConfigurableStrictness2, INITIALIZER)   \
    BOOST_FIXTURE_TEST_CASE(                                                                                           \
            ComparisonViaBaseFixture##_##VISITOR_ID##_##INITIALIZER,                                                   \
            ariles_tests::ComparisonViaBaseFixture<ariles_tests::initializers::INITIALIZER>)                           \
    {                                                                                                                  \
        test<ariles_tests::ConfigurableBase, ariles_tests::ConfigurableDerived, ariles::NAMESPACE>();                  \
    }


#include "instantiate.h"
