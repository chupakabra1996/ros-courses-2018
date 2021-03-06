/*
 * MIT License
 *
 * Copyright (c) 2018 Ramil Safin
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * @author Ramil Safin.
 */

#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

#include <cmath>

enum class RotationSide {
  NONE, LEFT, RIGHT
};

class ForwardRotateExplorer {
public:
  constexpr static auto FORWARD_SPEED = 0.2f;
  constexpr static auto ANGULAR_SPEED = 0.2f;

  constexpr static auto MIN_DIST_FROM_OBSTACLE = 1;

  ForwardRotateExplorer();

  void startMoving();

private:
  ros::NodeHandle node;
  ros::Publisher commandPub;
  ros::Subscriber laserSub;

  bool isRotating_{false};
  RotationSide rotationSide_{RotationSide::NONE};

  void moveForward();

  void rotateToFreeSpace();

  RotationSide findFreeSpaceRotationSide(const sensor_msgs::LaserScan::ConstPtr& scan);

  bool isObstacleInFront(const sensor_msgs::LaserScan::ConstPtr& scan);

  bool isInRange(float value, float min, float max);

  void onLaserScanData(const sensor_msgs::LaserScan::ConstPtr& scan);
};
