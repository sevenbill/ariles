/**
    @file
    @author  Alexander Sherikov

    @copyright 2018 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once



namespace ariles_tests
{
    /**
     * @brief Configurable class without extra constructors.
     */
    class ConfigurableEmpty : public ariles::DefaultBase
    {
#define ARILES_ENTRIES
#include ARILES_INITIALIZE


    public:
        ConfigurableEmpty()
        {
            ariles::apply<ariles::Defaults>(*this);
        }


        /**
         * @brief This method must be defined
         */
        void arilesVisit(const ariles::Defaults & /*visitor*/, const ariles::Defaults::Parameters & /*param*/)
        {
        }


        void randomize()
        {
            ariles::apply<ariles::PostProcess>(*this);
        }
    };
}  // namespace ariles_tests
