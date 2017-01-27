//
//
// C++ Interface for module: Map
//
// Description: 
//
//
// Author: exa
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef Map_Interface
#define Map_Interface

#include <CGAL/Cartesian.h>
#include <list>
#include <CGAL/Point_set_2.h>
#include <CGAL/Unique_hash_map.h>

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
using namespace boost;

#include "General.hxx"

#include <Info.hxx>


class Map {
public:
  Map() {}
  ~Map();

  typedef CGAL::Cartesian<double> K;
  typedef CGAL::Point_set_2<K>::Vertex_handle Vertex_handle;
  typedef CGAL::Point_2<K> Point;

  // Point database

  CGAL::Point_set_2<K> point_set; // geometric search index
  CGAL::Unique_hash_map<Vertex_handle, Point_Info*> point_info_hash; 
  
  CGAL::Point_set_2<K> route_point_set; // geometric search index for route endpoints
  CGAL::Unique_hash_map<Vertex_handle, Point_Info*> route_point_info_hash; 
  
  map<int, Point_Info*> point_idx; // primary index
  map<string, Point_Info*> point_name_idx; // index for names
  
  // Region database

  map<int, Region_Info*> region_idx; // primary index
  map<string, Region_Info*> region_name_idx; // index for names
  multimap<int, Region_Info* > regions_of_point; // inverse index for regions

  // Route database
  struct route_type_t {
    typedef edge_property_tag kind;
  };
  route_type_t route_type;
  struct route_region_t {
    typedef edge_property_tag kind;
  };
  route_region_t route_region;
  typedef property < edge_weight_t, float,
		     property< route_type_t, Route_Info::Route_Type,
		     property< route_region_t, int > > >
    edge_property;
  typedef adjacency_list < listS, vecS, directedS,
			   no_property, edge_property > graph_t;
  typedef graph_traits < graph_t >::vertex_descriptor vertex_descriptor;
  typedef graph_traits < graph_t >::edge_descriptor edge_descriptor;
  typedef std::pair<int, int> Edge;

  graph_t g;

  void read_database();
  void read_point_database();
  void read_region_database();
  void read_route_database();

  int generate_point_uid();
  void insert_point(Point_Info*);
  void insert_region(Region_Info*);
  void insert_route(Route_Info*);

  void query_rect_points(Point tl, Point br, int detail_level,
			 list<Point_Info>& rect_points);
  void query_rect_regions(list<Point_Info>& rect_points,
			  list<Region_Info>& region_points);
  void query_route(Point a, Point b, list<int>& road_segments);
};

#endif
