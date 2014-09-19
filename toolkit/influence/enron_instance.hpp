#include "malloc.hpp"
#include <iostream>
using namespace std;


class vertex_data
{
public:
	int id;
	
	vertex_data()
	{
	}
	vertex_data(int idd) : id(idd){
	}
	friend std::ostream & operator<< (std::ostream & output, const vertex_data &v) 
	{
		output<<"id: "<<v.id<<std::endl;
		return output;  
	}


}; //end of vertex_data

class edge_data
{
public:
	int id;
	
	edge_data(){}
	edge_data(int idd) :id(idd)
	{
	};
}; // end of edge_data;

namespace sae{
namespace serialization{

namespace custom_serialization_impl {

     /*
     * VertexInstance
     */
    template <>
    struct deserialize_impl<ISerializeStream, vertex_data> {
        static void run(ISerializeStream& istr, vertex_data& vdata) {
	 
            istr>>vdata.id;
            
        }
    };

    template <>
    struct serialize_impl<OSerializeStream, vertex_data> {
        static void run(OSerializeStream& ostr, const vertex_data& vdata) {
	 
	   ostr<<vdata.id;
        }
    };
     /*
     * EdgeInstance
     */
    template <>
    struct deserialize_impl<ISerializeStream, edge_data> {
        static void run(ISerializeStream& istr, edge_data& edata) {
	    
            istr>>edata.id;
        }
    };

    template <>
    struct serialize_impl<OSerializeStream, edge_data> {
        static void run(OSerializeStream& ostr, const edge_data& edata) {
	    
            ostr<<edata.id;
        }
    };




}
}
}


