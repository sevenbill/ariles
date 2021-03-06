/**
    @file
    @author  Alexander Sherikov

    @copyright 2017-2020 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once


namespace ariles
{
    namespace visitor
    {
        class ARILES_VISIBILITY_ATTRIBUTE Visitor
        {
        protected:
            Visitor(){};
            ~Visitor(){};
        };


        template <class t_Parameters>
        class ARILES_VISIBILITY_ATTRIBUTE Base : public Visitor
        {
        protected:
            Base(){};
            ~Base(){};

            const t_Parameters &getDefaultParameters() const
            {
                const static t_Parameters parameters;
                return parameters;
            }
        };
    }  // namespace visitor


    namespace entry
    {
#define ARILES_METHODS(Namespace, VisitorQualifier, MethodQualifier)                                                   \
    virtual void arilesVirtualVisit(                                                                                   \
            VisitorQualifier ariles::Namespace::Visitor &visitor, const ariles::Namespace::Visitor::Parameters &param) \
            MethodQualifier                                                                                            \
    {                                                                                                                  \
        ARILES_TRACE_FUNCTION;                                                                                         \
        this->arilesVisit(visitor, param);                                                                             \
    }                                                                                                                  \
    using ariles::Namespace::Base::arilesGetParameters;


        template <class t_Visitor>
        class ARILES_VISIBILITY_ATTRIBUTE Base
        {
        public:
            virtual void arilesVirtualVisit(t_Visitor &, const typename t_Visitor::Parameters &) = 0;

            virtual const typename t_Visitor::Parameters &arilesGetParameters(const t_Visitor &visitor) const
            {
                ARILES_TRACE_FUNCTION;
                return (visitor.getDefaultParameters());
            }
        };


        template <class t_Visitor>
        class ARILES_VISIBILITY_ATTRIBUTE ConstBase
        {
        public:
            virtual void arilesVirtualVisit(t_Visitor &, const typename t_Visitor::Parameters &) const = 0;

            virtual const typename t_Visitor::Parameters &arilesGetParameters(const t_Visitor &visitor) const
            {
                ARILES_TRACE_FUNCTION;
                return (visitor.getDefaultParameters());
            }
        };
    }  // namespace entry
}  // namespace ariles

#ifndef ARILES_DISABLE
#    ifndef ARILES_ENABLED
#        define ARILES_ENABLED
#    endif
#endif

#ifdef ARILES_ENABLED

namespace ariles
{
    // -----
    template <class t_Ariles, class t_Visitor>
    void apply(
            t_Visitor &visitor,
            t_Ariles &ariles_class,
            const std::string &name,
            const typename t_Visitor::Parameters &param,
            ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        visitor.start(ariles_class, name, param);
    }


    template <class t_Ariles, class t_Visitor>
    void apply(
            t_Visitor &visitor,
            t_Ariles &ariles_class,
            const char *name,
            const typename t_Visitor::Parameters &param,
            ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        visitor.start(ariles_class, name, param);
    }


    template <class t_Visitor, class t_Ariles>
    void apply(
            t_Visitor &visitor,
            t_Ariles &ariles_class,
            const typename t_Visitor::Parameters &param,
            ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        ariles::apply(visitor, ariles_class, ariles_class.arilesDefaultID(), param);
    }


    template <class t_Visitor, class t_Ariles>
    void apply(
            t_Visitor &visitor,
            t_Ariles &ariles_class,
            const std::string &name,
            ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        ariles::apply(visitor, ariles_class, name, visitor.getParameters(ariles_class));
    }


    template <class t_Visitor, class t_Ariles>
    void apply(
            t_Visitor &visitor,
            t_Ariles &ariles_class,
            const char *name,
            ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        ariles::apply(visitor, ariles_class, name, visitor.getParameters(ariles_class));
    }


    template <class t_Visitor, class t_Ariles>
    void apply(t_Visitor &visitor, t_Ariles &ariles_class, ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        ariles::apply(visitor, ariles_class, ariles_class.arilesDefaultID());
    }


    template <class t_Visitor, class t_Ariles>
    void apply(t_Ariles &ariles_class, ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        t_Visitor visitor;
        ariles::apply(visitor, ariles_class);
    }
    // -----



    // -----
    template <class t_Visitor, class t_Ariles, class t_Arg>
    void apply(
            t_Arg &arg,
            t_Ariles &ariles_class,
            ARILES_IS_BASE_DISABLER(ariles::visitor::Visitor, t_Arg),
            ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        t_Visitor visitor(arg);
        ariles::apply(visitor, ariles_class);
    }


    template <class t_Visitor, class t_Ariles, class t_Arg>
    void apply(
            t_Arg &arg,
            t_Ariles &ariles_class,
            const char *name,
            ARILES_IS_BASE_DISABLER(ariles::visitor::Visitor, t_Arg),
            ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        t_Visitor visitor(arg);
        ariles::apply(visitor, ariles_class, name);
    }


    template <class t_Visitor, class t_Ariles, class t_Arg>
    void apply(
            const t_Arg &arg,
            t_Ariles &ariles_class,
            ARILES_IS_BASE_DISABLER(ariles::visitor::Visitor, t_Arg),
            ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        t_Visitor visitor(arg);
        ariles::apply(visitor, ariles_class);
    }


    template <class t_Visitor, class t_Ariles, class t_Arg>
    void apply(
            t_Arg &arg,
            t_Ariles &ariles_class,
            const typename t_Visitor::Parameters &param,
            ARILES_IS_BASE_DISABLER(ariles::visitor::Visitor, t_Arg),
            ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        t_Visitor visitor(arg);
        ariles::apply(visitor, ariles_class, param);
    }


    template <class t_Visitor, class t_Ariles>
    void apply(
            const std::string &arg,
            t_Ariles &ariles_class,
            const unsigned int flags,
            ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        t_Visitor visitor(arg);
        ariles::apply(visitor, ariles_class, typename t_Visitor::Parameters(flags));
    }
    // -----


    // -----
    template <class t_Visitor, class t_Left, class t_Right>
    void apply(
            t_Visitor &visitor,
            t_Left &left,
            t_Right &right,
            const std::string &name,
            const typename t_Visitor::Parameters &param,
            ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        try
        {
            visitor.start(left, right, name, param);
        }
        catch (std::exception &e)
        {
            if (true == param.throw_on_error_)
            {
                ARILES_THROW(std::string("Comparison failed: ") + e.what());
            }
            visitor.equal_ = false;
        }
    }


    template <class t_Visitor, class t_Left, class t_Right>
    void apply(
            t_Visitor &visitor,
            t_Left &left,
            t_Right &right,
            ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        ariles::apply(visitor, left, right, left.arilesDefaultID(), visitor.getParameters(left));
    }


    template <class t_Visitor, class t_Left, class t_Right>
    void apply(
            t_Visitor &visitor,
            t_Left &left,
            t_Right &right,
            const typename t_Visitor::Parameters &param,
            ARILES_IS_BASE_ENABLER(ariles::visitor::Visitor, t_Visitor))
    {
        ARILES_TRACE_FUNCTION;
        ariles::apply(visitor, left, right, left.arilesDefaultID(), param);
    }
    // -----
}  // namespace ariles

#else

namespace ariles
{
    // -----
    template <class t_One, class t_Two, class t_Three, class t_Four, class t_Five>
    void apply(t_One, t_Two, t_Three, t_Four, t_Five)
    {
    }

    template <class t_One, class t_Two, class t_Three, class t_Four>
    void apply(t_One, t_Two, t_Three, t_Four)
    {
    }

    template <class t_One, class t_Two, class t_Three>
    void apply(t_One, t_Two, t_Three)
    {
    }

    template <class t_One, class t_Two>
    void apply(t_One, t_Two)
    {
    }

    template <class t_One, class t_Two>
    void apply(t_Two)
    {
    }
    // -----
}  // namespace ariles

#endif
