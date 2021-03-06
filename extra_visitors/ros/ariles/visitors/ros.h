/**
    @file
    @author Alexander Sherikov

    @copyright 2018 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once

#define ARILES_VISITOR_INCLUDED_ros

#include <ariles/internal/helpers.h>
#include <ariles/internal/node.h>
#include <ariles/visitors/config.h>

#include <ros/ros.h>


namespace ariles
{
    namespace ns_ros
    {
        template <class t_Base, class t_Implementation>
        class ARILES_VISIBILITY_ATTRIBUTE Base : public t_Base
        {
        protected:
            typedef t_Implementation Impl;
            typedef ARILES_SHARED_PTR<t_Implementation> ImplPtr;

        protected:
            ImplPtr impl_;


        private:
            Base(const Base &);
            Base &operator=(const Base &);

        protected:
            Base(){};
            ~Base(){};


        public:
            const serialization::Features &getSerializationFeatures() const
            {
                static serialization::Features parameters(
                        serialization::Features::SLOPPY_MAPS_SUPPORTED
                        | serialization::Features::SLOPPY_PAIRS_SUPPORTED);
                return (parameters);
            }
        };
    }  // namespace ns_ros
}  // namespace ariles


#include "./ros/reader.h"
#include "./ros/writer.h"

namespace ariles
{
    /**
     * @brief ROS parameter server visitor.
     */
    struct ARILES_VISIBILITY_ATTRIBUTE ros
    {
        typedef ariles::cfgread::Visitor<ns_ros::Reader> Reader;
        typedef ariles::cfgwrite::Visitor<ns_ros::Writer> Writer;
    };
}  // namespace ariles
