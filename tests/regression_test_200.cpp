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

#include "types_api_v2/simple_verbose.h"
#include "types_api_v2/simple_auto_declare.h"
#include "types_api_v2/simple_no_auto_id.h"
#include "types_api_v2/no_setdefaults.h"
#include "types_api_v2/empty.h"



// ===============================================================
// FIXTURES
// ===============================================================

#include "fixtures_api_v2/initializers.h"
#include "fixtures_api_v2/000_basic_interface.h"



// ===============================================================
// TESTS
// ===============================================================

#define ARILES_TESTS(BRIDGE_ID, NAMESPACE, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(BasicInterfaceFixture, BRIDGE_ID, NAMESPACE, ConfigurableEmpty, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(BasicInterfaceFixture, BRIDGE_ID, NAMESPACE, ConfigurableVerbose, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(BasicInterfaceFixture, BRIDGE_ID, NAMESPACE, ConfigurableAutoDeclare, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(BasicInterfaceFixture, BRIDGE_ID, NAMESPACE, ConfigurableNoAutoID, INITIALIZER) \
    ARILES_FIXTURE_TEST_CASE(BasicInterfaceFixture, BRIDGE_ID, NAMESPACE, ConfigurableNoSetDefaults, INITIALIZER)

#include "instantiate.h"
