/**
    @file
    @author Alexander Sherikov

    @copyright 2018 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once


#include <ariles/internal/helpers.h>
#include <ariles/internal/node.h>
#include <ariles/visitors/config.h>

#include <ros/ros.h>


namespace ariles
{
    namespace bridge
    {
        namespace ros
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


#include "./ros/reader.h"
#include "./ros/writer.h"

#define ARILES_BRIDGE_INCLUDED_ros

namespace ariles
{
    /**
     * @brief ROS parameter server bridge.
     */
    struct ARILES_VISIBILITY_ATTRIBUTE ros
    {
        typedef ariles::cfgread::Visitor<bridge::ros::Reader> Reader;
        typedef ariles::cfgwrite::Visitor<bridge::ros::Writer> Writer;
    };
}