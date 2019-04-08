/*
 *  Copyright (C) 1997-2015 JDE Developers Team
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
 *  Authors :
 *       Victor Arribas Raigadas <v.arribas.urjc@gmai.com>
 */


#include "formula1/interfaces/pose3di.h"

using namespace formula1::interfaces;
using namespace jderobot;
using namespace ignition;

Pose3DI::Pose3DI (const formula1::Formula1Sensors *sensor, formula1::Formula1Control *control):
    data(new Pose3DData(0,0,0,0,0,0,0,0)),
    sensor(sensor),
    control(control)
{}

Pose3DI::~Pose3DI ()
{}

Pose3DDataPtr
Pose3DI::getPose3DData ( const Ice::Current& ){
    math::Pose3d pose = sensor->pose;

    data->x = pose.Pos().X();
    data->y = pose.Pos().Y();
    data->z = pose.Pos().Z();
    data->h = 1;
    data->q0 = pose.Rot().W();
    data->q1 = pose.Rot().X();
    data->q2 = pose.Rot().Y();
    data->q3 = pose.Rot().Z();

    return data;
}

Ice::Int
Pose3DI::setPose3DData ( const jderobot::Pose3DDataPtr & data, const Ice::Current& ){
    math::Pose3d pose(math::Vector3d(data->x, data->y, data->z),
                            math::Quaterniond(data->q0, data->q1, data->q2, data->q3));
    control->teleport(pose);
    return 0;
}
