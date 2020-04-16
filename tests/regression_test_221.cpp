/**
    @file
    @author  Alexander Sherikov

    @copyright 2017-2018 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/


#define ARILES_API_VERSION 2

#include "utility.h"

#ifdef ARILES_BRIDGE_array
#include "ariles/visitors/array.h"
#endif

#include "ariles/adapters_all.h"
#include "ariles/ariles2.h"


// ===============================================================
// TYPES
// ===============================================================

#include "types_api_v2/complex_auto_declare.h"
#include "types_api_v2/empty.h"


// ===============================================================
// FIXTURES
// ===============================================================


#include "fixtures_api_v2/initializers.h"
#include "fixtures_api_v2/013_write_array.h"


// ===============================================================
// TESTS
// ===============================================================

#define ARILES_TESTS(VISITOR_ID, NAMESPACE, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(ArrayFixture, VISITOR_ID, NAMESPACE, ConfigurableComplex, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(ArrayFixture, VISITOR_ID, NAMESPACE, ConfigurableEmpty, INITIALIZER)

#include "instantiate.h"
