//
//
// C++ Implementation for module: PointRPCs
//
// Description: 
//
//
// Author: exa
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "PointRPCs.hxx"
#include "Map.hxx"
#include "Store.hxx"

void GetPointRPC::execute(XmlRpcValue& params, XmlRpcValue& result)
{
  int user_map = params[0];
  cout << "user map? " << user_map ;//<< " point uid: " << point_id << endl;
  int point_id = params[1];
  Map* map;
  if (user_map)
    map = &store.user_map;
  else
    map = &store.global_map;
  if (map->point_idx.find(point_id)!=map->point_idx.end()) {
    Point_Info* info = map->point_idx[point_id];
    result["name"] = info->name;
    result["type"] = info->type;
    result["x"] = info->x;
    result["y"] = info->y;
    result["description"] = info->description;
  }
}

// insert a user point
void InsertPointRPC::execute(XmlRpcValue& params, XmlRpcValue& result)
{
  Point_Info* point = new Point_Info(store.user_map.generate_point_uid(),
				     params[0]["type"],
				     params[0]["name"],
				     params[0]["x"],
				     params[0]["y"],
				     params[0]["description"]);
  store.user_map.insert_point(point);
  result[0] = point->uid;
}

// delete a user point

void DeletePointRPC::execute(XmlRpcValue& params, XmlRpcValue& result)
{

  int point_id=params[0];
  map<int, Point_Info*>::iterator i = store.user_map.point_idx.find(point_id);
  if (i!=store.user_map.point_idx.end()) {
    store.user_map.point_idx.erase(i);
  }
}

void NearestPointRPC::execute(XmlRpcValue& params, XmlRpcValue& result)
{
  Map* map = &store.global_map;
  Map::Point a = Map::Point(double(params[0]["x"]),double(params[0]["y"]));
  
  // find the closest points to a and b in database 
  Map::Vertex_handle ap = map->point_set.nearest_neighbor(a);
  
  if (ap != NULL) {
    Point_Info* info = map->point_info_hash[ap];
    result["uid"] = info->uid;
    result["name"] = info->name;
    result["type"] = info->type;
    result["x"] = info->x;
    result["y"] = info->y;
    result["description"] = info->description;
  }

}
