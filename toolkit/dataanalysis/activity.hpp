#pragma once
#include <time.h>
#include "serialization/serialization.hpp"

using namespace std;

struct UUser{
    string userid;
};

struct Activity{
    string name;
    double trendency;
};

struct UserEdge
{
    int times;
};

namespace sae {
    namespace serialization {
        namespace custom_serialization_impl {
            template <>
            struct serialize_impl<sae::serialization::OSerializeStream, Activity> {
                static void run(sae::serialization::OSerializeStream& ostr, const Activity& a) {
                    ostr << a.name;
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, Activity> {
                static void run(sae::serialization::ISerializeStream& istr, Activity& a) {
                    istr >> a.name;
                }
            };
        }
    }
}

namespace sae {
    namespace serialization {
        namespace custom_serialization_impl {
            template <>
            struct serialize_impl<sae::serialization::OSerializeStream, UUser> {
                static void run(sae::serialization::OSerializeStream& ostr, const UUser& a) {
                    ostr << a.userid;
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, UUser> {
                static void run(sae::serialization::ISerializeStream& istr, UUser& a) {
                    istr >> a.userid;
                }
            };
        }
    }
}

namespace sae {
    namespace serialization {
        namespace custom_serialization_impl {
            template <>
            struct serialize_impl<sae::serialization::OSerializeStream, UserEdge> {
                static void run(sae::serialization::OSerializeStream& ostr, const UserEdge& a) {
                    ostr << a.times;
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, UserEdge> {
                static void run(sae::serialization::ISerializeStream& istr, UserEdge& a) {
                    istr >> a.times;
                }
            };
        }
    }
}
