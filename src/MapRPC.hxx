//
//
// C++ Interface for module: MapRPC
//
// Description: 
//
//
// Author: exa
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef MapRPC_Interface
#define MapRPC_Interface

#include "General.hxx"
#include "XmlRpc.h"
using namespace XmlRpc;

// Arguments are as follows:
// param 0, userName: string
// param 1, queryBox: dimensions of query rectangle, an array of two point
//  structs , first one upper left, second one lower right corner
// param 2, detailLevel: integer, a detail level from 1 to 10

// Resulting map information with respect to query rect is a struct
// two fields: points and regions
// points:
//   array of point structs (name, type: string, x and y: double)
// regions:
// each region is a struct:
// name: string
// outlineColor: integer
// fillColor: integer
// points: an array of point indices each of which is an integer
class MapRPC : public XmlRpcServerMethod
{
public:
  MapRPC(XmlRpcServer* s) : XmlRpcServerMethod("mapbuddy.map", s) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result);
  std::string help();

};



#endif
