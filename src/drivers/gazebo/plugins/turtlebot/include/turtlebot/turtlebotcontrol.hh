/*
 *  Copyright (C) 1997-2017 JDE Developers Team
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see http://www.gnu.org/licenses/.
 *
 *  REMIX of https://github.com/jderobot-varribas/gazeboplugin-quadrotor2/blob/2.1.0/include/quadrotor/quadrotorcontrol.hh
 *  Victor Arribas Raigadas <v.arribas.urjc@gmai.com>
 *  
 *  Authors:
 *       Francisco Perez Salgado <f.pererz475@gmai.com>
 */

#ifndef TURTLEBOTCONTROL_H
#define TURTLEBOTCONTROL_H


#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>

#include "transport/transport.hh"

#include <turtlebot/turtlebotsensors.hh>

namespace turtlebot{

class TurtlebotControl {
public:
    TurtlebotControl();
    virtual ~TurtlebotControl();
    void setSensors(TurtlebotSensors *sensors);

/// Control commands
public:
    //void takeoff();
    //void land();
    //void setTargetVelocity(gazebo::math::Twist twist);
    //void teleport(gazebo::math::Pose pose);

    std::string _log_prefix;
    struct motor_t {
        float v;
        float w;
        float l;
    };
    motor_t robotMotors;

/// Control
protected:
   TurtlebotSensors *sensors;

/// Gazebo
public:
    void Load(gazebo::physics::ModelPtr model, sdf::ElementPtr _sdf);
    void Init(TurtlebotSensors* sensors);
    void OnUpdate(const gazebo::common::UpdateInfo & _info);
    void teleport(math::Pose3d pose);

private:
    gazebo::event::ConnectionPtr updateConnection;
    gazebo::physics::ModelPtr model;
    gazebo::physics::InertialPtr inertial;
    gazebo::physics::JointPtr leftJoint, rightJoint;

    gazebo::transport::NodePtr node;
    gazebo::transport::SubscriberPtr velSub;
    double wheelSpeed[2];
    double torque;
    double wheelSeparation;
    double wheelRadius;
    gazebo::common::Time prevUpdateTime;

};


typedef boost::shared_ptr<TurtlebotControl> TurtlebotControlPtr;

}//NS

#endif // QUADROTORPLUGIN_H
