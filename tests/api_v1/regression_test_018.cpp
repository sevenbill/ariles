/**
    @file
    @author  Alexander Sherikov

    @copyright 2017-2018 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/


#include "utility.h"
#include "all_enabled_bridges.h"


#include "ariles/adapters_all.h"
#include "ariles/ariles.h"


// ===============================================================
// TYPES
// ===============================================================

#include "types/pointers.h"



// ===============================================================
// FIXTURES
// ===============================================================


#include "fixtures/initializers.h"
#include "fixtures/000_basic_interface.h"
#include "fixtures/001_constructor_interface.h"
#include "fixtures/002_comparison.h"
#include "fixtures/004_comparison_equivalence.h"


// ===============================================================
// TESTS
// ===============================================================

#define ARILES_TESTS(VISITOR_ID, NAMESPACE, INITIALIZER)                                                               \
    ARILES_FIXTURE_TEST_CASE(BasicInterfaceFixture, VISITOR_ID, NAMESPACE, ConfigurablePointers, INITIALIZER)          \
    ARILES_FIXTURE_TEST_CASE(ConstructorInterfaceFixture, VISITOR_ID, NAMESPACE, ConfigurablePointers, INITIALIZER)    \
    ARILES_FIXTURE_TEST_CASE(ComparisonSimpleFixture, VISITOR_ID, NAMESPACE, ConfigurablePointers, INITIALIZER)        \
    ARILES_FIXTURE_TEST_CASE(ComparisonMultiFixture, VISITOR_ID, NAMESPACE, ConfigurablePointers, INITIALIZER)

#include "instantiate.h"
