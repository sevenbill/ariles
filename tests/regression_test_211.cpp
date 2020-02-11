/**
    @file
    @author  Alexander Sherikov

    @copyright 2017-2018 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#define ARILES_API_VERSION 2

#include "utility.h"


#include "ariles/bridges/rapidjson.h"

// If no bridge header is included, ariles is disabled, and
// ariles::ConfigurableBase is just a dummy class.
#include "ariles/ariles2.h"

#include "ariles/bridges/yaml_cpp.h"


// ===============================================================
// TYPES
// ===============================================================

#include "types_api_v2/simple_auto_declare.h"


// ===============================================================
// FIXTURES
// ===============================================================

#include "fixtures_api_v2/initializers.h"
#include "fixtures_api_v2/000_basic_interface.h"



// ===============================================================
// TESTS
// ===============================================================

#define ARILES_TESTS(BRIDGE_ID, NAMESPACE, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(BasicInterfaceFixture, BRIDGE_ID, NAMESPACE, ConfigurableAutoDeclare, INITIALIZER)

#include "instantiate.h"