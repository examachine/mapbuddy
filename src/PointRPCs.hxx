//
//
// C++ Interface for module: PointRPCs
//
// Description: 
//
//
// Author: exa
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef PointRPCs_Interface
#define PointRPCs_Interface

#include "General.hxx"
#include "XmlRpc.h"
using namespace XmlRpc;

// param[0] a point id
class GetPointRPC : public XmlRpcServerMethod
{
public:
  GetPointRPC(XmlRpcServer* s) : XmlRpcServerMethod("mapbuddy.getPoint", s) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result);

};

// insert a user point
class InsertPointRPC : public XmlRpcServerMethod
{
public:
  InsertPointRPC(XmlRpcServer* s) : XmlRpcServerMethod("mapbuddy.insertPoint", s) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result);

};

// delete a user point
class DeletePointRPC : public XmlRpcServerMethod
{
public:
  DeletePointRPC(XmlRpcServer* s) : XmlRpcServerMethod("mapbuddy.deletePoint", s) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result);

};


// find nearest point in global map
class NearestPointRPC : public XmlRpcServerMethod
{
public:
  NearestPointRPC(XmlRpcServer* s) : XmlRpcServerMethod("mapbuddy.nearestPoint", s) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result);
};


#endif
