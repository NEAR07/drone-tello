// Generated by gencpp from file drone_controller/MoveDroneW.msg
// DO NOT EDIT!


#ifndef DRONE_CONTROLLER_MESSAGE_MOVEDRONEW_H
#define DRONE_CONTROLLER_MESSAGE_MOVEDRONEW_H

#include <ros/service_traits.h>


#include <drone_controller/MoveDroneWRequest.h>
#include <drone_controller/MoveDroneWResponse.h>


namespace drone_controller
{

struct MoveDroneW
{

typedef MoveDroneWRequest Request;
typedef MoveDroneWResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct MoveDroneW
} // namespace drone_controller


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::drone_controller::MoveDroneW > {
  static const char* value()
  {
    return "07cc5e7856beb68b29432db43546cf40";
  }

  static const char* value(const ::drone_controller::MoveDroneW&) { return value(); }
};

template<>
struct DataType< ::drone_controller::MoveDroneW > {
  static const char* value()
  {
    return "drone_controller/MoveDroneW";
  }

  static const char* value(const ::drone_controller::MoveDroneW&) { return value(); }
};


// service_traits::MD5Sum< ::drone_controller::MoveDroneWRequest> should match
// service_traits::MD5Sum< ::drone_controller::MoveDroneW >
template<>
struct MD5Sum< ::drone_controller::MoveDroneWRequest>
{
  static const char* value()
  {
    return MD5Sum< ::drone_controller::MoveDroneW >::value();
  }
  static const char* value(const ::drone_controller::MoveDroneWRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::drone_controller::MoveDroneWRequest> should match
// service_traits::DataType< ::drone_controller::MoveDroneW >
template<>
struct DataType< ::drone_controller::MoveDroneWRequest>
{
  static const char* value()
  {
    return DataType< ::drone_controller::MoveDroneW >::value();
  }
  static const char* value(const ::drone_controller::MoveDroneWRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::drone_controller::MoveDroneWResponse> should match
// service_traits::MD5Sum< ::drone_controller::MoveDroneW >
template<>
struct MD5Sum< ::drone_controller::MoveDroneWResponse>
{
  static const char* value()
  {
    return MD5Sum< ::drone_controller::MoveDroneW >::value();
  }
  static const char* value(const ::drone_controller::MoveDroneWResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::drone_controller::MoveDroneWResponse> should match
// service_traits::DataType< ::drone_controller::MoveDroneW >
template<>
struct DataType< ::drone_controller::MoveDroneWResponse>
{
  static const char* value()
  {
    return DataType< ::drone_controller::MoveDroneW >::value();
  }
  static const char* value(const ::drone_controller::MoveDroneWResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // DRONE_CONTROLLER_MESSAGE_MOVEDRONEW_H
