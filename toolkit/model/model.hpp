#pragma once
#include <time.h>
#include "serialization/serialization.hpp"

using namespace std;

struct VData {
    string name;
    vector<double> attribute;
    double value;
};

struct EData {
    string name;
    vector<double> attribute;
    double value;
};


namespace sae {
    namespace serialization {
        namespace custom_serialization_impl {
            template <>
            struct serialize_impl<sae::serialization::OSerializeStream, VData> {
                static void run(sae::serialization::OSerializeStream& ostr, const VData& a) {
                    ostr << a.name << a.attribute << a.value;
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, VData> {
                static void run(sae::serialization::ISerializeStream& istr, VData& a) {
                    istr >> a.name >> a.attribute >> a.value;
                }
            };
        }
    }
}

namespace sae {
    namespace serialization {
        namespace custom_serialization_impl {
            template <>
            struct serialize_impl<sae::serialization::OSerializeStream, EData> {
                static void run(sae::serialization::OSerializeStream& ostr, const EData& a) {
                    ostr << a.name << a.attribute << a.value;
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, EData> {
                static void run(sae::serialization::ISerializeStream& istr, EData& a) {
                    istr >> a.name >> a.attribute >> a.value;
                }
            };
        }
    }
}
