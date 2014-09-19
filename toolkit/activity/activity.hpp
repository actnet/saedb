#pragma once
#include <time.h>
#include "serialization/serialization.hpp"
#include "vectorimporter.hpp"

struct UUser{
    string userid;
    // string username;
    // string userimage;
    friend std::ostream & operator<< (std::ostream & output, const UUser &u)
    {
        output<<"UUser("<<u.userid<<")"<<std::endl;
        return output;
    }
};

struct Text{
    string Verb;
    string Object;
    friend std::ostream & operator<< (std::ostream & output, const Text &t)
    {
        output<<"Text("<<t.Verb<<" "<<t.Object<<")"<<std::endl;
        return output;
    }
};

struct NextActivity{
    string name;
    double dur;
    //NextActivities
};

//microblogid|uid|lantitude|longtitude|timestamp|sentiment
struct Instance{
    string microblogid;
    string userid;
    double longtitude;
    double lantitude;
    time_t timestamp;
    string sentiment;
    friend std::ostream & operator<< (std::ostream & output, const Instance &i)
    {
        output<<"Instance("<<i.microblogid<<" "<<i.userid<<" "<<i.sentiment<<")"<<std::endl;
        return output;
    }
};

struct Activity{
    string name;
    Text text;
    vector<double> feature;
    vector<string> pois;
    int instanceNum;
    vector<Instance> instances;
    friend std::ostream & operator<< (std::ostream & output, const Activity &a)
    {
        output<<"Activity(\n"<<a.name<<"\n"<<a.text;
        for(int i = 0; i < a.instanceNum; i++)
            output<<a.instances[i];
        output<<")\n";
        return output;
    }
};

//next edge
struct Next{
    string name;
    double dur;
    //NextActivities
};

//center activity
struct ActivityCenter{
    string name;
};
//center edge
struct CenterEdge
{
    int edge;
};
//center edge
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
                    ostr << a.text.Verb << a.text.Object;
                    ostr << a.feature << a.pois << a.instanceNum;
                    for(int i = 0; i < a.instanceNum; i++)
                    {
                        ostr << a.instances[i].microblogid << a.instances[i].userid << a.instances[i].longtitude << a.instances[i].lantitude << a.instances[i].timestamp << a.instances[i].sentiment;
                    }
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, Activity> {
                static void run(sae::serialization::ISerializeStream& istr, Activity& a) {
                    istr >> a.name;
                    istr >> a.text.Verb >> a.text.Object;
                    istr >> a.feature >> a.pois >> a.instanceNum;
                    for(int i = 0; i < a.instanceNum; i++)
                    {
                        // POI *poi = new POI;
                        // istr >> poi->Id >> poi->Name >> poi->Type >> poi->City >> poi->Lat >> poi->Lng;
                        Instance instance;
                        istr >> instance.microblogid >> instance.userid >> instance.longtitude >> instance.lantitude >> instance.timestamp >> instance.sentiment;
                        a.instances.push_back(instance);
                    }
                }
            };
        }
    }
}

namespace sae {
    namespace serialization {
        namespace custom_serialization_impl {
            template <>
            struct serialize_impl<sae::serialization::OSerializeStream, ActivityCenter> {
                static void run(sae::serialization::OSerializeStream& ostr, const ActivityCenter& a) {
                    ostr << a.name;
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, ActivityCenter> {
                static void run(sae::serialization::ISerializeStream& istr, ActivityCenter& a) {
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
            struct serialize_impl<sae::serialization::OSerializeStream, Next> {
                static void run(sae::serialization::OSerializeStream& ostr, const Next& a) {
                    ostr << a.name << a.dur;
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, Next> {
                static void run(sae::serialization::ISerializeStream& istr, Next& a) {
                    istr >> a.name >> a.dur;
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

namespace sae {
    namespace serialization {
        namespace custom_serialization_impl {
            template <>
            struct serialize_impl<sae::serialization::OSerializeStream, CenterEdge> {
                static void run(sae::serialization::OSerializeStream& ostr, const CenterEdge& a) {
                    ostr << a.edge;
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, CenterEdge> {
                static void run(sae::serialization::ISerializeStream& istr, CenterEdge& a) {
                    istr >> a.edge;
                }
            };
        }
    }
}

