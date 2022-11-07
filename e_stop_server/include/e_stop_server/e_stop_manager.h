#pragma once

#include <ros/ros.h>
#include <std_msgs/Bool.h>

#include <e_stop_manager_msgs/SetEStop.h>
#include <e_stop_manager_msgs/EStopList.h>

// plugins
#include <pluginlib/class_loader.h>
#include <e_stop_propagators/propagator_base.hpp>

namespace e_stop_manager
{
class EStopManager
{
public:
  ~EStopManager()
  {
    // explicit before the class loader destructs
    for (auto& prop_ptr : propagator_list_)
    {
      if (prop_ptr)
      {
        prop_ptr.reset();
      }
    }
  }

  EStopManager(ros::NodeHandle& nh, ros::NodeHandle& pnh);

private:
  void publishEStops(bool force_e_stop = false);

  bool setEStopServiceCB(e_stop_manager_msgs::SetEStop::Request& request,
                         e_stop_manager_msgs::SetEStop::Response& response);

  ros::NodeHandle& nh_;
  ros::NodeHandle& pnh_;

  ros::ServiceServer set_e_stop_service_;

  e_stop_manager_msgs::EStopList e_stop_list_msg_;
  ros::Publisher e_stop_list_pub_;

  std::map<ros::Publisher, std::vector<std::string>> e_stop_pub_;

  // lib container
  std::shared_ptr<pluginlib::ClassLoader<e_stop_manager::EStopPropagator>> p_loader_;

  // plugins
  std::vector<boost::shared_ptr<EStopPropagator>> propagator_list_;
};
}  // namespace e_stop_manager
