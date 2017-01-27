//
//
// C++ Implementation for module: Map
//
// Description: 
//
//
// Author: exa
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "Map.hxx"

Map::~Map() {
  for (map<int, Point_Info*>::iterator i = point_idx.begin();
       i != point_idx.end(); i++) {
    delete i->second;
  }
  for (map<int, Region_Info*>::iterator i = region_idx.begin();
       i != region_idx.end(); i++) {
    delete i->second;
  }
}

void Map::read_database() {
  read_point_database();
  read_region_database();
  read_route_database();

  multimap<int, Region_Info*>::iterator i;
  cout << "*** points_of_region:" << endl;
  for (i=regions_of_point.begin(); i!=regions_of_point.end(); i++) {
    cout << hex << i->first << " : " << i->second << endl;
  }
}


void Map::read_point_database() {
  ifstream in("data/point.data");
  if (in) {
    while (!in.eof()) {

      int uid;
      string type;
      string name;
      double x;
      double y;
      string description;

      in >> uid;
      if (uid==-1)
	break;
      in >> type >> name >> x >> y >> description;
      cout << uid << ":" << type << ":" << name << ":" << x << ":" <<
	y << endl;
      insert_point(new Point_Info(uid,type,name,x,y,description));
    }
  }
  else {
    cerr << "can't open point database" << endl;
    exit(-1);
  }
  // debug stuff
  cout << "*** point_set: "  << point_set << endl;
  cout << "*** end oint_set: " << endl;
  cout << "*** route_point_set: "  << route_point_set << endl;
  cout << "*** end route_point_set: " << endl;
}

void Map::read_region_database() {
  ifstream in("data/region.data");
  if (in) {
    char line[65536];
    while (!in.eof()) {

      in.getline(line, 65535);
      int uid;
      string type;
      string name;
      list<int> points;
      istringstream in_line(line);

      in_line >> uid;
      if (uid==-1)
	break;
      in_line >> type >> name;
      while (!in_line.eof()) {
	int point;
	in_line >> point;
	points.push_back(point);
      }
      cout << uid << ":" << type << ":" << name
	   << ":" << points.size() << endl;
      if (points.size()<3) {
	cerr << "invalid region: " << name << endl;
	exit(-1);
       }
      insert_region(new Region_Info(uid,type,name,points));
    }
  }
  else {
    cerr << "can't open region database" << endl;
    exit(-1);
  }
}

void Map::read_route_database() {
  ifstream in("data/route.data");
  if (in) {
    char line[65536];
    while (!in.eof()) {
      in.getline(line, 65535);
      string type;
      int source, target, region;
      double weight;
      istringstream in_line(line);

      in_line >> type >> source >> target >> region >> weight;
      if (type=="-1")
	break;
      cout << source << "--" << target << ":" << weight << endl;
      assert(point_idx[source]->type=="RE" || point_idx[source]->type=="RI");
      assert(point_idx[target]->type=="RE" || point_idx[target]->type=="RI" );
      assert(region_idx[region]->type=="RS");
      insert_route(new Route_Info(type, source, target, region, weight));
    }
  }
  else {
    cerr << "can't open region database" << endl;
    exit(-1);
  }
}


// generate uid
int Map::generate_point_uid()
{
  if (point_idx.size()==0)
    return 1;
  else {
    return ((--point_idx.end())->first) + 1;
  }
}

void Map::insert_point(Point_Info* point) {
  Vertex_handle vtx = point_set.insert(Point(point->x, point->y));
  point_info_hash[vtx] = point;
  if (point->type=="RI" || point->type=="RV") {
    Vertex_handle vtx = route_point_set.insert(Point(point->x, point->y));
    route_point_info_hash[vtx] = point;
  }
  point_idx[point->uid] = point;
  point_name_idx[point->name] = point;
}

void Map::insert_region(Region_Info* region) {
  region_idx[region->uid] = region;
  region_name_idx[region->name] = region;
  for (list<int>::iterator i=region->vertices.begin();
       i!=region->vertices.end(); i++) {
    regions_of_point.insert(pair<int,Region_Info*>(*i,region));
  }
}

void Map::insert_route(Route_Info* route) {
  property_map<graph_t, edge_weight_t>::type weightmap = get(edge_weight, g);
  property_map<graph_t, route_type_t>::type routetypemap = get(route_type, g);
  property_map<graph_t, route_region_t>::type routeregionmap = get(route_region, g);
  edge_descriptor e; bool inserted;
  tie(e, inserted) = add_edge(route->src, route->dest, g);
  weightmap[e] = route->length;
  routetypemap[e] = route->type;
  routeregionmap[e] = route->region;
}


// x1, y1: upper left corner
// x2, y2: lower right corner
// rect_points: empty list for resulting point infos
void Map::query_rect_points(Point pt1, Point pt3, int detail_level,
			    list<Point_Info>& rect_points) {
  cout << pt1 << " -- " << pt3 << endl;
  Point pt2 = Point(pt3.x(),pt1.y());
  Point pt4 = Point(pt1.x(),pt3.y());

  std::list<Vertex_handle> LV;
  std::list<Vertex_handle>::iterator it;
  
  point_set.range_search(pt1,pt2,pt3,pt4, std::back_inserter(LV));
  cout << "rect query result " << LV.size() << " points!" << endl;
  for (it=LV.begin();it != LV.end(); it++) {
    std::cout << (*it)->point() << "\n"; 
    Point& p = (*it)->point();
    Point_Info *point_info = point_info_hash[*it];
    Point_Info p_info (point_info->uid, point_info->type, point_info->name,
		       p.x(),p.y(),point_info->description);
    rect_points.push_back(p_info);
  }
  
}

// yea, let's make some assumptions about pointers in this system
// this is almost guaranteed to work
struct comp_region_ptr {
  bool operator () (Region_Info* a, Region_Info* b) {
    return reinterpret_cast<unsigned int>(a) <
      reinterpret_cast<unsigned int>(b);
  }
};

// this is a workaround until we find a suitable
// geometric data structure for querying regions efficiently
void Map::query_rect_regions(list<Point_Info>& rect_points,
			     list<Region_Info>& rect_regions) {
  vector<Region_Info*> null_set, result_set;
  list< vector<Region_Info*> > set_region_sets;

  list<Point_Info>::iterator pi;
  comp_region_ptr compare;
  for (pi=rect_points.begin(); pi!=rect_points.end(); pi++) {
    typedef multimap<int, Region_Info*>::iterator iterator;
    pair<iterator,iterator> range = regions_of_point.equal_range(pi->uid);
    set_region_sets.push_back(null_set);
    vector<Region_Info*> & last = set_region_sets.back();
    for (iterator i=range.first; i!=range.second; i++) {
      last.push_back(i->second);
    }
    sort(last.begin(), last.end(), compare); // make set
  }
  // accumulate() sucks, we can just code it here
  list< vector<Region_Info*> >::iterator i;
  for (i=set_region_sets.begin(); i!=set_region_sets.end(); i++) {
    vector<Region_Info*> tmp_set = result_set;
    result_set.clear();
    set_union(i->begin(), i->end(), tmp_set.begin(), tmp_set.end(),
	      back_inserter(result_set));
  }
  // convert the stupid vector to a list of region infos
  for (vector<Region_Info*>::iterator i=result_set.begin();
       i!=result_set.end(); i++) {
    rect_regions.push_back(**i);
  }
}

// query a route from point a to point b and return the result
// in road_segments which is a list of region uids which can be
// used to construct complete information for the route
void Map::query_route(Point a, Point b, list<int>& road_segments)
{
  // find the closest points to a and b in database 
  Vertex_handle ap = route_point_set.nearest_neighbor(a);
  Vertex_handle bp = route_point_set.nearest_neighbor(b);
  
  assert(ap != NULL);
  assert(bp != NULL);

  cout << "Find a route from " << ap->point() << " to " << bp->point()
       << endl;

  int start_vertex = route_point_info_hash[ap]->uid;
  int end_vertex = route_point_info_hash[bp]->uid;

  std::vector<vertex_descriptor> p(num_vertices(g));
  std::vector<int> d(num_vertices(g));
  vertex_descriptor s = vertex(start_vertex, g);
  dijkstra_shortest_paths(g, s, predecessor_map(&p[0]));
  
  for (int vtx = end_vertex; vtx != start_vertex; vtx = p[vtx]) {
    road_segments.push_front(vtx);
  }
  
}
