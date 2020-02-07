#include "vex.h"

using namespace vex;


#define forwardDistanceP (28.647889757)
#define strafeDistanceP (32.243767313)
#define strafeSpeedP (1.12551980572)

#define forwardDistance (frontLeft.rotation(deg) + backLeft.rotation(deg) + frontRight.rotation(deg) + backRight.rotation(deg)) / 4 / forwardDistanceP
#define strafeDistance (frontLeft.rotation(deg) - backLeft.rotation(deg) + backRight.rotation(deg) - frontRight.rotation(deg)) / 4 / strafeDistanceP


int rampMath(double input, double totalRange, int startOutput, int maxOutput, int endOutput, double rampUpP = 0.1, double rampDownP = 0.12) {
  int output;
  double rampUpRange = ((maxOutput - startOutput)*rampUpP);
  double rampDownRange = ((maxOutput - endOutput)*rampDownP);
  double rampUpMuliplier = ((maxOutput - startOutput) / rampUpRange);
  double rampDownMuliplier = ((maxOutput - endOutput) / rampDownRange);
      if (fabs(input) <= fabs(rampUpRange)) {
        output = ((input * rampUpMuliplier) + startOutput);
      } else if (fabs(input) >= (fabs(totalRange) - fabs(rampDownRange))) {
        output = ((totalRange - input) * rampDownMuliplier + endOutput);
      } else {
        output = (maxOutput);
      }
  return output;
}

struct rampStruct
{
  double position;
  double distance;
  int startSpeed;
  int maxSpeed;
  int endSpeed;
  bool isMoving;
};

rampStruct forwardStruct {};
rampStruct strafeStruct {};
rampStruct turnStruct {};

double forwardOutput;
double strafeOutput;
double turnOutput;

/*===========================================================================*/

void forwardFunction ( double position, double distance,int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion)
{
  forwardStruct = {position, distance, startSpeed, maxSpeed, endSpeed, true};
  if (waitForCompletion)
  {
    waitUntil(!forwardStruct.isMoving);
  }
}

int forwardTask()
{
  while(1)
  {
    while(!forwardStruct.isMoving)
    {
      forwardOutput = forwardStruct.position;
      vex::task::sleep(20);
    }
    vex::task::sleep(20);
    while(fabs(forwardDistance - forwardStruct.position) < fabs(forwardStruct.distance))
    {
      forwardOutput = rampMath(fabs(forwardDistance - forwardStruct.position), fabs(forwardStruct.distance), forwardStruct.startSpeed, forwardStruct.maxSpeed,
      forwardStruct.endSpeed) * fabs(forwardStruct.distance) / forwardStruct.distance;
      vex::task::sleep(20);
    }
    forwardStruct.isMoving = false;
    forwardStruct.position = forwardStruct.position + forwardStruct.distance;
  }
  return(0);
}

/*===========================================================================*/

void strafeFunction ( double position, double distance,int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion)
{
  strafeStruct = {position, distance, startSpeed, maxSpeed, endSpeed, true};
  if (waitForCompletion)
  {
    waitUntil(!strafeStruct.isMoving);
  }
}

int strafeTask()
{
  while(1)
  {
    while(!strafeStruct.isMoving)
    {
      strafeOutput = strafeStruct.position;
      vex::task::sleep(20);
    }
    vex::task::sleep(20);
    while(fabs(strafeDistance - strafeStruct.position) < fabs(strafeStruct.distance))
    {
      strafeOutput = rampMath(fabs(strafeDistance - strafeStruct.position), fabs(strafeStruct.distance), strafeStruct.startSpeed, strafeStruct.maxSpeed,
      strafeStruct.endSpeed) * fabs(strafeStruct.distance) / strafeStruct.distance;
      vex::task::sleep(20);
    }
    strafeStruct.isMoving = false;
    strafeStruct.position = strafeStruct.position + strafeStruct.distance;
  }
  return(0);
}

/*===========================================================================*/

void turnFunction ( double position, double distance,int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion)
{
  turnStruct = {position, distance, startSpeed, maxSpeed, endSpeed, true};
  if (waitForCompletion)
  {
    waitUntil(!turnStruct.isMoving);
  }
}

int turnTask()
{
  while(1)
  {
    while(!turnStruct.isMoving)
    {
      turnOutput = turnStruct.position - Inertial.yaw();
      vex::task::sleep(20);
    }
    vex::task::sleep(20);
    while(fabs(Inertial.yaw() - turnStruct.position) < fabs(turnStruct.distance))
    {
      turnOutput = rampMath(fabs(Inertial.yaw() - turnStruct.position), fabs(turnStruct.distance), turnStruct.startSpeed, turnStruct.maxSpeed,
      turnStruct.endSpeed, 0.2, 0.8) * fabs(turnStruct.distance) / turnStruct.distance;
      vex::task::sleep(20);
    }
    turnStruct.isMoving = false;
    turnStruct.position = turnStruct.position + turnStruct.distance;
  }
  return(0);
}

/*===========================================================================*/

int drivetrainTask()
{
  while(1)
  {
  double moveForward = forwardOutput;
  double moveStrafe  = strafeOutput * strafeSpeedP;
  double moveTurn    = turnOutput;

  frontRight.spin(fwd, moveForward - moveStrafe - moveTurn, pct);
  frontLeft.spin(fwd,  moveForward + moveStrafe + moveTurn, pct);
  backRight.spin(fwd,  moveForward + moveStrafe - moveTurn, pct);
  backLeft.spin(fwd,   moveForward - moveStrafe + moveTurn, pct);
  }

  return(0);
}

void autonInitialize()
{
  task task1 = task( drivetrainTask );
  task task2 = task( forwardTask );
  task task3 = task( strafeTask );
  task task4 = task( turnTask );
}

void autonStop()
{
  task::stop( drivetrainTask );
  task::stop( forwardTask );
  task::stop( strafeTask );
  task::stop( turnTask );
}