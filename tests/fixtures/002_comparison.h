/**
    @file
    @author  Alexander Sherikov

    @copyright 2017-2018 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once


class ComparisonSimpleFixture : public FixtureBase
{
    protected:
        template<class t_Configurable, class t_Bridge>
            void test()
        {
            t_Configurable  configurable_out;
            configurable_out.randomize();
            BOOST_CHECK_NO_THROW(
                configurable_out.template writeConfig<t_Bridge>(getInitializer("configurable_match_simple.cfg"));
            );

            // -------

            t_Configurable  configurable_in;
            BOOST_CHECK_NO_THROW(
                configurable_in.template readConfig<t_Bridge>(getInitializer("configurable_match_simple.cfg"));
            );

            // -------

            compare(configurable_out, configurable_in);
        }
};


class ComparisonMultiFixture : public FixtureBase
{
    protected:
        template<class t_Configurable, class t_Bridge>
            void test()
        {
            t_Configurable configurable_out1;
            t_Configurable configurable_out2;

            configurable_out1.randomize();
            configurable_out2.randomize();

            BOOST_CHECK_NO_THROW(
                typename t_Bridge::Writer writer(getInitializer("configurable_match_multi.cfg"));
                configurable_out1.template writeConfig(writer, "node1");
                configurable_out2.template writeConfig(writer, "node2");
            );

            // -------

            t_Configurable configurable_in1;
            t_Configurable configurable_in2;

            BOOST_CHECK_NO_THROW(
                typename t_Bridge::Reader reader(getInitializer("configurable_match_multi.cfg"));
                configurable_in1.template readConfig(reader, "node1");
                configurable_in2.template readConfig(reader, "node2");
            );

            // -------

            compare(configurable_out1, configurable_in1);
            compare(configurable_out2, configurable_in2);
        }
};
