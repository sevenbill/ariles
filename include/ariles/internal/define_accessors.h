/**
    @file
    @author  Alexander Sherikov
    @copyright 2014-2017 INRIA. Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)
    @copyright 2017-2018 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief Inclusion of this file results in generation of functions which
    read and write entries 'ARILES_ENTRIES' defined in the including
    header from / to a configuration file.
*/

#ifndef ARILES_DOXYGEN_PROCESSING
    public:
        #ifdef ARILES_ENTRIES
            #define ARILES_NAMED_ENTRY(entry, name)
            #define ARILES_PARENT(entry)
            #define ARILES_TYPED_NAMED_ENTRY(type, entry, name)  type    entry;

            ARILES_MACRO_SUBSTITUTE(ARILES_ENTRIES)

            #undef ARILES_NAMED_ENTRY
            #undef ARILES_PARENT
            #undef ARILES_TYPED_NAMED_ENTRY

            #define ARILES_TYPED_NAMED_ENTRY(type, entry, name)  ARILES_NAMED_ENTRY(entry, name)
        #endif
#endif


#ifdef ARILES_ENABLED
#   ifndef ARILES_ENTRIES
#       error "ARILES_ENTRIES must be defined."
#   endif


    #ifndef ARILES_DOXYGEN_PROCESSING

    protected:
        #ifdef ARILES_ENTRIES

        // Define write methods

            #define ARILES_NAMED_ENTRY(entry, name)  ARILES_WRITE_NAMED_ENTRY(entry, name)
            #define ARILES_PARENT(entry)       ARILES_WRITE_PARENT(entry)

            template <class t_Writer>
                void writeConfigEntriesTemplate(t_Writer & writer) const
            {
                ARILES_MACRO_SUBSTITUTE(ARILES_ENTRIES)
            }

            #undef ARILES_NAMED_ENTRY
            #undef ARILES_PARENT


        // Define read methods

            #define ARILES_NAMED_ENTRY(entry, name)  ARILES_READ_NAMED_ENTRY(entry, name)
            #define ARILES_PARENT(entry)       ARILES_READ_PARENT(entry)

            template <class t_Reader>
                void readConfigEntriesTemplate( t_Reader & reader,
                                                const bool crash_on_missing_entry = false)
            {
                ARILES_MACRO_SUBSTITUTE(ARILES_ENTRIES)
                finalize();
            }

            #undef ARILES_NAMED_ENTRY
            #undef ARILES_PARENT


        // Count number of entries and define a function, which returns it.

            #define ARILES_NAMED_ENTRY(entry, name)  +1
            #define ARILES_PARENT(entry)       +entry::getNumberOfEntries()

            std::size_t getNumberOfEntries() const
            {
                static const std::size_t    num_entries = (0 ARILES_MACRO_SUBSTITUTE(ARILES_ENTRIES) );
                return(num_entries);
            }

            #undef ARILES_NAMED_ENTRY
            #undef ARILES_PARENT


            #undef ARILES_TYPED_NAMED_ENTRY
        #endif
    #endif


    public:
        // Define constructors if requested
        #ifdef ARILES_CONSTRUCTOR
            /**
             * Define constructors for the given class.
             */
            template <class t_Reader>
                ARILES_CONSTRUCTOR(
                        t_Reader &reader,
                        const std::string &node_name,
                        const bool crash_on_missing_entry = true)
            {
                readConfig(reader, node_name, crash_on_missing_entry);
            }

            template <class t_Reader>
                explicit ARILES_CONSTRUCTOR(
                        t_Reader &reader,
                        const bool crash_on_missing_entry = true)
            {
                readConfig(reader, crash_on_missing_entry);
            }
        #endif


        // Define node name
        #ifdef ARILES_SECTION_ID
            const std::string & getConfigSectionID() const
            {
                static const std::string name(ARILES_SECTION_ID);
                return (name);
            }
        #endif


        // Format-specific stuff
        #define ARILES_NAMESPACE(config_namespace) \
            virtual void writeConfigEntries(ariles::config_namespace::Writer & writer) const \
            { \
                writeConfigEntriesTemplate(writer); \
            } \
            virtual void readConfigEntries( ariles::config_namespace::Reader & reader, \
                                            const bool crash_flag) \
            {\
                readConfigEntriesTemplate(reader, crash_flag);\
            }

            ARILES_MACRO_SUBSTITUTE(ARILES_NAMESPACE_LIST)

        #undef ARILES_NAMESPACE


        /**
         * @brief Read configuration (assuming the configuration node
         * to be in the root).
         *
         * @param[in] reader configuration reader
         * @param[in] crash_on_missing_entry
         */
        template <class t_Reader>
            void readConfig(t_Reader            & reader,
                            const bool          crash_on_missing_entry = true)
        {
            ariles::reader::readEntry(reader, *this, this->getConfigSectionID(), crash_on_missing_entry);
        }


        /**
         * @brief Read configuration (assuming the configuration node
         * to be in the root).
         *
         * @param[in] reader configuration reader
         * @param[in] crash_on_missing_entry
         * @param[in] node_name   node name, the default is used if empty
         */
        template <class t_Reader>
            void readConfig(t_Reader            & reader,
                            const std::string   & node_name,
                            const bool          crash_on_missing_entry = true)
        {
            ariles::reader::readEntry(reader, *this, node_name, crash_on_missing_entry);
        }


        /**
         * @brief Read configuration (assuming the configuration node
         * to be in the root).
         *
         * @param[in] reader configuration reader
         * @param[in] crash_on_missing_entry
         * @param[in] node_name   node name, the default is used if empty
         *
         * @note Intercept implicit conversion of a pointer to bool.
         */
        template <class t_Reader>
            void readConfig(t_Reader            & reader,
                            const char          * node_name,
                            const bool          crash_on_missing_entry = true)
        {
            ariles::reader::readEntry(reader, *this, node_name, crash_on_missing_entry);
        }


        /**
         * @brief Read configuration (assuming the configuration node
         * to be in the root).
         *
         * @param[in] file_name file name
         * @param[in] crash_on_missing_entry
         */
        template <class t_Reader>
            void readConfig(const std::string &file_name,
                            const bool        crash_on_missing_entry = true)
        {
            t_Reader reader(file_name);
            ariles::reader::readEntry(reader, *this, this->getConfigSectionID(), crash_on_missing_entry);
        }


        /**
         * @brief Read configuration (assuming the configuration node
         * to be in the root).
         *
         * @param[in] file_name file name
         * @param[in] node_name   node name, the default is used if empty
         * @param[in] crash_on_missing_entry
         */
        template <class t_Reader>
            void readConfig(const std::string &file_name,
                            const std::string &node_name,
                            const bool        crash_on_missing_entry = true)
        {
            t_Reader reader(file_name);
            ariles::reader::readEntry(reader, *this, node_name, crash_on_missing_entry);
        }


        /**
         * @brief Read configuration (assuming the configuration node
         * to be in the root).
         *
         * @param[in] file_name file name
         * @param[in] crash_on_missing_entry
         * @param[in] node_name   node name, the default is used if empty
         *
         * @note Intercept implicit conversion of a pointer to bool.
         */
        template <class t_Reader>
            void readConfig(const std::string &file_name,
                            const char        *node_name,
                            const bool        crash_on_missing_entry = true)
        {
            t_Reader reader(file_name);
            ariles::reader::readEntry(reader, *this, node_name, crash_on_missing_entry);
        }


        // ============================================


        /**
         * @brief Write configuration
         *
         * @param[in,out] writer configuration writer
         */
        template <class t_Writer>
            void writeConfig(t_Writer& writer) const
        {
            writeConfig(writer, this->getConfigSectionID());
        }


        /**
         * @brief Write configuration
         *
         * @param[in,out] writer configuration writer
         * @param[in] node_name   node name, the default is used if empty
         */
        template <class t_Writer>
            void writeConfig(t_Writer& writer,
                             const std::string &node_name) const
        {
            writer.initRoot();
            ariles::writer::writeEntry(writer, *this, node_name);
            writer.flush();
        }


        /**
         * @brief Write configuration.
         *
         * @param[in] file_name file name
         */
        template <class t_Writer>
            void writeConfig(const std::string &file_name) const
        {
            t_Writer writer(file_name);
            writeConfig(writer);
        }


        /**
         * @brief Write configuration.
         *
         * @param[in] file_name file name
         * @param[in] node_name   node name, the default is used if empty
         */
        template <class t_Writer>
            void writeConfig(const std::string &file_name,
                             const std::string &node_name) const
        {
            t_Writer writer(file_name);
            writeConfig(writer, node_name);
        }

#endif //ARILES_ENABLED

#undef ARILES_SECTION_ID
#undef ARILES_CONSTRUCTOR
#undef ARILES_ENTRIES