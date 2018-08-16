/**
    @file
    @author  Alexander Sherikov

    @copyright 2017-2018 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once

namespace ariles
{
    class BridgeParameters
    {
        public:
            bool sloppy_maps_supported_;
            bool native_matrix_supported_;

        public:
            BridgeParameters(   const bool sloppy_maps_supported,
                                const bool native_matrix_supported = false)
            {
                sloppy_maps_supported_ = sloppy_maps_supported;
                native_matrix_supported_ = native_matrix_supported;
            }
    };
}