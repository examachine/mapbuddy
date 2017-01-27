//
//
// C++ Implementation for module: MapRPC
//
// Description: 
//
//
// Author: exa
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "MapRPC.hxx"
#include "Map.hxx"
#include "Store.hxx"

void MapRPC::execute(XmlRpcValue& params, XmlRpcValue& result)
{ 
  string user_name = std::string(params[0]);
  Map::Point tl =
    Map::Point(double(params[1][0]["x"]),double(params[1][0]["y"]));
  Map::Point br = 
    Map::Point(double(params[1][1]["x"]),double(params[1][1]["y"]));
  int detail_level = int(params[2]);
  list<Point_Info> rect_points;
  list<Point_Info>::iterator pnt_it;

  store.global_map.query_rect_points(tl,br,detail_level,rect_points);
  {
    XmlRpcValue points;
    int i = 0;
    for (pnt_it=rect_points.begin(); pnt_it!=rect_points.end();
	 pnt_it++, i++) {
      points[i]["uid"] = pnt_it->uid;
      points[i]["type"] = pnt_it->type;
      points[i]["name"] = pnt_it->name;
      points[i]["x"] = pnt_it->x;
      points[i]["y"] = pnt_it->y;
    }
    result["points"] = points;
  }
  
  {
    list<Region_Info> rect_regions;
    list<Region_Info>::iterator ri;
    store.global_map.query_rect_regions(rect_points, rect_regions);
    XmlRpcValue regions;
    int i = 0;
    for (ri = rect_regions.begin(); ri!= rect_regions.end(); ri++,
	   i++) {
      cout << "region " << i << " is " << ri->type << ":" << ri->name << endl;
      regions[i]["type"] = ri->type;
      regions[i]["name"] = ri->name;
      list<int>::iterator vtxi;
      int j = 0;
      for (vtxi=ri->vertices.begin(); vtxi!=ri->vertices.end(); vtxi++, j++) {
        Point_Info* pnt = store.global_map.point_idx[*vtxi];
	regions[i]["vertices"][j]["x"] = pnt->x;
	regions[i]["vertices"][j]["y"] = pnt->y;
      }
      if (rect_regions.size() > 0)
	result["regions"] = regions;
    }
  }
  
}

std::string MapRPC::help() {
    return std::string("query a rectangular area in\
the map, arguments:  userName: string\
queryBox: dimensions of query rectangle, an array of two point\
structs , first one upper left, second one lower right corner\
detailLevel: integer, a detail level from 1 to 10"); 
}
