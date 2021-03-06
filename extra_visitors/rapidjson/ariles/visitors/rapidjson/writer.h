/**
    @file
    @author Alexander Sherikov

    @copyright 2018-2020 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once

namespace ariles
{
    namespace ns_rapidjson
    {
        namespace impl
        {
            class ARILES_VISIBILITY_ATTRIBUTE Writer;
        }


        /**
         * @brief Configuration writer class
         */
        class ARILES_VISIBILITY_ATTRIBUTE Writer : public ns_rapidjson::Base<ariles::write::Visitor, impl::Writer>
        {
        public:
            explicit Writer(const std::string &file_name, const Flags &flags = Flags::DEFAULT);
            explicit Writer(std::ostream &output_stream, const Flags &flags = Flags::DEFAULT);

            void flush();


            void descend(const std::string &map_name);
            void ascend();

            void startMap(const std::size_t /*num_entries*/);
            void startArray(const std::size_t size, const bool /*compact*/ = false);

            void shiftArray();
            void endArray();



#define ARILES_BASIC_TYPE(type) void writeElement(const type &element);

            ARILES_MACRO_SUBSTITUTE(ARILES_BASIC_TYPES_LIST)

#undef ARILES_BASIC_TYPE
        };
    }  // namespace ns_rapidjson
}  // namespace ariles
