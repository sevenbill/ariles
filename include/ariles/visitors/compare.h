/**
    @file
    @author  Alexander Sherikov

    @copyright 2017-2020 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once

#include "common.h"

namespace ariles
{
    namespace compare
    {
        class ARILES_VISIBILITY_ATTRIBUTE Parameters
        {
        public:
            double float_tolerance_;
            double double_tolerance_;
            bool compare_number_of_entries_;
            bool throw_on_error_;  /// @todo DEPRECATED
            bool nan_equal_;
            bool inf_equal_;
            /// @todo continue on failure.


        public:
            Parameters()
            {
                setDefaults();
            }


            void setDefaults()
            {
                double_tolerance_ = 1e-12;
                float_tolerance_ = 1e-8;
                compare_number_of_entries_ = false;
                throw_on_error_ = false;

                nan_equal_ = true;
                inf_equal_ = true;
            }


            template <typename t_Scalar>
            t_Scalar getTolerance() const;
        };


        class ARILES_VISIBILITY_ATTRIBUTE Visitor : public visitor::Base<compare::Parameters>
        {
        public:
            typedef compare::Parameters Parameters;


        public:
            bool equal_;


        public:
            template <class t_Left, class t_Right>
            bool compare(const t_Left &left, const t_Right &right, const Parameters &param)
            {
                ariles::apply(*this, left, right, param);
                return (equal_);
            }

            using visitor::Base<Parameters>::getDefaultParameters;

            template <class t_Ariles>
            const Parameters &getParameters(const t_Ariles &ariles_class) const
            {
                return (ariles_class.arilesGetParameters(*this));
            }


            template <class t_Left, class t_Right>
            void start(const t_Left &left, const t_Right &right, const std::string &name, const Parameters &param)
            {
                ARILES_TRACE_FUNCTION;
                equal_ = true;
                this->operator()(left, right, name, param);
            }


            template <typename t_Scalar>
            static bool compareFloats(const t_Scalar left, const t_Scalar right, const Parameters &param)
            {
                if (isNaN(left))
                {
                    if (isNaN(right))
                    {
                        return (param.nan_equal_);
                    }
                    else
                    {
                        return (false);
                    }
                }

                if (isInfinity(left))
                {
                    if (isInfinity(right))
                    {
                        if (((left > 0) && (right > 0)) || ((left < 0) && (right < 0)))
                        {
                            return (param.inf_equal_);
                        }
                    }
                    return (false);
                }
                return (std::abs(left - right)
                        <= ((std::abs(left) < std::abs(right) ? std::abs(right) : std::abs(left))
                            * param.double_tolerance_));
            }


            template <class t_Left, class t_Right>
            void operator()(const t_Left &left, const t_Right &right, const std::string &name, const Parameters &param)
            {
                ARILES_TRACE_FUNCTION;
                ARILES_TRACE_ENTRY(name);
                ARILES_TRACE_TYPE(left);
                ARILES_TRACE_TYPE(right);

                try
                {
                    apply_compare(*this, left, right, param);
                    if (false == this->equal_ and true == param.throw_on_error_)
                    {
                        ARILES_THROW("");
                    }
                }
                catch (const std::exception &e)
                {
                    ARILES_THROW("entry: " + name + " // " + std::string(e.what()));
                }
            }
        };


        template <>
        inline double Visitor::Parameters::getTolerance<double>() const
        {
            return (double_tolerance_);
        }

        template <>
        inline float Visitor::Parameters::getTolerance<float>() const
        {
            return (float_tolerance_);
        }


#ifndef ARILES_METHODS_compare
#    define ARILES_METHODS_compare                                                                                     \
        const ariles::compare::Visitor::Parameters &arilesGetParameters(const ariles::compare::Visitor &visitor) const \
        {                                                                                                              \
            ARILES_TRACE_FUNCTION;                                                                                     \
            return (visitor.getDefaultParameters());                                                                   \
        }
#endif
    }  // namespace compare


    typedef compare::Visitor Compare;
}  // namespace ariles
