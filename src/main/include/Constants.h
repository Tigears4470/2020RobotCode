/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

// Ports

const int LEFT_MOTOR = 0;
const int SPINNER_PORT = 1;
const int RIGHT_MOTOR = 6;
const int SHOOTER_PORT = 2;
const int ELEVATOR_PORT = 3;

const int JOYSTICK_PORT = 0;

const int COLOR_SENSOR_ADDRESS = 0x52;

//Colors
const int c_BLUE[3] = {30, 110, 115}; //0,255,255
const int c_GREEN[3] = {40, 150, 65}; //0,255,0
const int c_RED[3] = {130, 90, 35}; //255,0,0
const int c_YELLOW[3] = {80, 145, 30}; //255,255,0

const int MAX_COLOR_RANGE = 255;

const int RED_SLOT = 0;
const int GREEN_SLOT = 1;
const int BLUE_SLOT = 2;

const int COLOR_SQUARED = 2;

const int BUFFER = 10;

const int REVOLUTIONS_NEEDED = 3;

const double SPINNER_SPEED = 0.5;
const double SPINNER_STOP_SPEED = 0;

// Joystick Buttons
const int ROTATE_WHEEL_BUTTON = 2;
const int SET_COLOR_BUTTON = 3;
const int SHOOTER_SHOOT = 4;
const int SHOOTER_SUCK = 5;
const int SHOOT_STOP = 6;


//Control Theory
const double ACCELERATION_CONSTANT = 0.02;

//Speeds
const double SHOOTER_SHOOT_SPEED = 0.5;
const double SHOOTER_STOP_SPEED = 0.0;
const double SHOOTER_SUCK_SPEED = -0.5;
