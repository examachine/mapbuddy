//
//
// C++ Implementation for module: RouteRPC
//
// Description: 
//
//
// Author: exa
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "RouteRPC.hxx"
#include "Map.hxx"
#include "Store.hxx"

void RouteRPC::execute(XmlRpcValue& params, XmlRpcValue& result) 
{
  Map::Point a = Map::Point(double(params[0]["x"]),double(params[0]["y"]));
  Map::Point b = Map::Point(double(params[1]["x"]),double(params[1]["y"]));
  list<int> road_segments;
  store.global_map.query_route(a, b, road_segments);
  {
    list<int>::iterator si;
    XmlRpcValue segments;
    int i = 0;
    for (si = road_segments.begin(); si!= road_segments.end(); si++,
	   i++) {
      Region_Info* ri = store.global_map.region_idx[*si];
      cout << "region " << i << " is " << ri->type << ":" << ri->name << endl;
      segments[i]["type"] = ri->type;
      segments[i]["name"] = ri->name;
      list<int>::iterator vtxi;
      int j = 0;
      for (vtxi=ri->vertices.begin(); vtxi!=ri->vertices.end(); vtxi++, j++) {
        Point_Info* pnt = store.global_map.point_idx[*vtxi];
	segments[i]["vertices"][j]["x"] = pnt->x;
	segments[i]["vertices"][j]["y"] = pnt->y;
      }
      if (segments.size() > 0)
	result["segments"] = segments;
    }
  }
}

std::string RouteRPC::help()
{
  return "mapbuddy.route -- query route information from point A\
to point B on map";
}
