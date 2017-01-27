//
//
// C++ Interface for module: Info
//
// Description: Data structs for info types in our GIS
//
//
// Author: exa
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef Info_Interface
#define Info_Interface

#include "General.hxx"

class Mobile_Info {
public:
  Mobile_Info(int _uid, string _type, string _name) 
    : uid(_uid), type(_type), name(_name) {}
  int uid;
  string type, name;
};

class Point_Info : public Mobile_Info {
public:
  Point_Info(int _uid, string _type, string _name, double _x,
	     double _y, string desc) 
    : Mobile_Info(_uid, _type, _name), x(_x), y(_y), description(desc) {}
  
  double x,y;
  string description;
};

class Region_Info :  public Mobile_Info {
public:
  Region_Info(int _uid, string& _type, string& _name, list<int>&_vtx) 
    : Mobile_Info(_uid, _type, _name), vertices(_vtx) {}
  
  list<int> vertices;
};

class Route_Info  {
public:
  enum Route_Type { Road, Urban, Highway };

  Route_Info(string& _type, int _src, int _dest, int _rgn, double len)
    : src(_src), dest(_dest), region(_rgn), length(len)
  {
    if (_type=="R")
      type = Road;
    else if (_type=="U")
      type = Urban;
    else if (_type=="H")
      type = Highway;
    else {
      cerr << "invalid route type: " << type << endl;
      exit(-1);
    }
  }
  Route_Type type;
  int src, dest;
  int region;
  float length;
};
#endif
