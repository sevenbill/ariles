/**
    @file
    @author  Alexander Sherikov
    @copyright 2020 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)
*/



#define ARILES_NAMED_ENTRY_generic_all(v, entry, name) visitor(entry, #name, parameters);
#define ARILES_PARENT_generic_all(v, entry)

#define ARILES_VISIT_generic_all                                                                                       \
    template <class t_Visitor>                                                                                         \
    void arilesVisit(                                                                                                  \
            t_Visitor &visitor,                                                                                        \
            const typename t_Visitor::Parameters &parameters,                                                          \
            ARILES_IS_BASE_ENABLER(ariles2::visitor::GenericVisitor, t_Visitor))                                        \
    {                                                                                                                  \
        ARILES2_UNUSED_ARG(visitor);                                                                                    \
        ARILES2_UNUSED_ARG(parameters);                                                                                 \
        ARILES_TRACE_FUNCTION;                                                                                         \
        arilesVisitParents(visitor, parameters);                                                                       \
        ARILES_ENTRIES(generic_all)                                                                                    \
    }                                                                                                                  \
    template <class t_Visitor>                                                                                         \
    void arilesVisit(                                                                                                  \
            t_Visitor &visitor,                                                                                        \
            const typename t_Visitor::Parameters &parameters,                                                          \
            ARILES_IS_BASE_ENABLER(ariles2::visitor::GenericVisitor, t_Visitor)) const                                  \
    {                                                                                                                  \
        ARILES2_UNUSED_ARG(visitor);                                                                                    \
        ARILES2_UNUSED_ARG(parameters);                                                                                 \
        ARILES_TRACE_FUNCTION;                                                                                         \
        arilesVisitParents(visitor, parameters);                                                                       \
        ARILES_ENTRIES(generic_all)                                                                                    \
    }
