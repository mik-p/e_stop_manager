#pragma once

#include <e_stop_propagators/propagator_base.hpp>

#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>

namespace e_stop_manager
{
class NavPropagator : public EStopPropagator
{
public:
  NavPropagator() : stop_topic_("")
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
        actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> mb_client("/move_base_simple/move_base", true);
        mb_client.cancelAllGoals();
      }
    }

    return true;
  }

protected:
  std::string stop_topic_;
};
}  // namespace e_stop_manager
