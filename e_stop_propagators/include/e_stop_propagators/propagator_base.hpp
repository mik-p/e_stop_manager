#pragma once

#include <ros/ros.h>
#include <std_msgs/Bool.h>

namespace e_stop_manager
{
/**
 * @brief base propagator class definition for plugin-lib
 *
 */
class EStopPropagator
{
public:
  virtual ~EStopPropagator()
  {
  }

  // plugin api
  virtual const bool init(std::shared_ptr<ros::NodeHandle> nh, std::shared_ptr<ros::NodeHandle> pnh) = 0;
  virtual const bool propagate(std::string notify_topic, std_msgs::Bool msg) = 0;

protected:
  EStopPropagator()
  {
  }
};
}  // namespace e_stop_manager
