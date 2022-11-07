E-Stop propagators
===

Allows e-stops events to be handled by plugins so that e-stop actions can be propagated using pre-existing interfaces. These tasks are not necessarily as time sensitive as the actual e-stop event. This interface decouples the safety critical event and the resultant actions that need to be taken across the robot's network to maintain defined behaviour.

For example:
---

In a navigation situation. Say that a hardware e-stop is triggered, the e-stop manager registers this change. Then a propagator that was listening to this change can call actionlib to cancel all current navigation goals using the pre-existing navigation stack interfaces.

In a UI setting. A pre-existing REST-API call can be executed by a propagator to disable a button.
