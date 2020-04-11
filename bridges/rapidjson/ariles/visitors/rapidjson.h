/**
    @file
    @author Alexander Sherikov

    @copyright 2017-2020 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once


#include <ariles/internal/helpers.h>
#include <ariles/internal/node.h>
#include <ariles/visitors/config.h>


namespace ariles
{
    namespace bridge
    {
        namespace rapidjson
        {
            template <class t_Base, class t_Implementation>
                class Base : public t_Base
            {
                protected:
                    typedef t_Implementation Impl;
                    typedef ARILES_SHARED_PTR<t_Implementation> ImplPtr;

                protected:
                    ImplPtr impl_;


                private:
                    Base(const Base&);
                    Base& operator=(const Base&);

                protected:
                    Base(){};
                    ~Base(){};


                public:
                    const BridgeFlags &getBridgeFlags() const
                    {
                        static BridgeFlags parameters(
                                BridgeFlags::SLOPPY_MAPS_SUPPORTED
                                | BridgeFlags::SLOPPY_PAIRS_SUPPORTED);
                        return (parameters);
                    }
            };
        }
    }
}



#include "./rapidjson/reader.h"
#include "./rapidjson/writer.h"


#ifdef ARILES_BRIDGE_INCLUDED_jsonnet
#   include "./rapidjson/jsonnet_reader.h"
#   include "./rapidjson/jsonnet_writer.h"
#endif


#define ARILES_BRIDGE_INCLUDED_rapidjson


namespace ariles
{
    /**
     * @brief JSON bridge.
     */
    struct ARILES_VISIBILITY_ATTRIBUTE rapidjson
    {
        typedef ariles::cfgread::Visitor<bridge::rapidjson::Reader> Reader;
        typedef ariles::cfgwrite::Visitor<bridge::rapidjson::Writer> Writer;

#ifdef ARILES_BRIDGE_INCLUDED_jsonnet
        struct ARILES_VISIBILITY_ATTRIBUTE jsonnet
        {
            typedef ariles::cfgread::Visitor<bridge::rapidjson::jsonnet::Reader> Reader;
            typedef ariles::cfgwrite::Visitor<bridge::rapidjson::jsonnet::Writer> Writer;
        };
#endif
    };
}