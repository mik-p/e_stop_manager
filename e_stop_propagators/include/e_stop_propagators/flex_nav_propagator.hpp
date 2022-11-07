#pragma once

#include <e_stop_propagators/propagator_base.hpp>

#include <actionlib/client/simple_action_client.h>
#include <mbf_msgs/MoveBaseAction.h>

namespace e_stop_manager
{
class FlexNavPropagator : public EStopPropagator
{
public:
  FlexNavPropagator() : stop_topic_("")
  {
  }

  virtual const bool init(std::shared_ptr<ros::NodeHandle> nh, std::shared_ptr<ros::NodeHandle> pnh)
  {
    pnh->param<std::string>("topic", stop_topic_, stop_topic_);
    return true;
  }

  virtual const bool propagate(std::string notify_topic, std_msgs::Bool msg)
  {
    if ((ros::this_node::getName() + "/" + stop_topic_) == notify_topic)
    {
      // do propagation action
      if (msg.data)
      {
        ROS_WARN_STREAM_NAMED("e_stop_manager", "an e-stop event is propagating to the navigation action interface");

        // create an mbf navigation interface
        // start the action client with automatic spinning thread
        actionlib::SimpleActionClient<mbf_msgs::MoveBaseAction> mbf_client("/move_base_simple/move_base", true);
        mbf_client.cancelAllGoals();
      }
    }

    return true;
  }

protected:
  std::string stop_topic_;
};
}  // namespace e_stop_manager
