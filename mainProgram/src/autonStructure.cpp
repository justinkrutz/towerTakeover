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

void forwardFunction (double distance, int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion)
{
  forwardStruct = {distance, startSpeed, maxSpeed, endSpeed, true};
  if (waitForCompletion)
  {
    waitUntil(!forwardStruct.isMoving);
  }
}

int forwardTask()
{
  double startDistance;
  while(1)
  {
    waitUntil(forwardStruct.isMoving);
    startDistance = forwardDistance;
    while(fabs(forwardDistance - startDistance) < fabs(forwardStruct.distance))
    {
      forwardOutput = rampMath(fabs(forwardDistance - startDistance), fabs(forwardStruct.distance), forwardStruct.startSpeed, forwardStruct.maxSpeed,
      forwardStruct.endSpeed) * fabs(forwardStruct.distance) / forwardStruct.distance;
      task::sleep(20);
    }
    forwardStruct.isMoving = false;
    forwardOutput = 0;
  }
  return(0);
}

/*===========================================================================*/

void strafeFunction (double distance, int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion)
{
  strafeStruct = {distance, startSpeed, maxSpeed, endSpeed, true};
  if (waitForCompletion)
  {
    waitUntil(!strafeStruct.isMoving);
  }
}

int strafeTask()
{
  double startDistance;
  while(1)
  {
    waitUntil(strafeStruct.isMoving);
    startDistance = strafeDistance;
    while(fabs(strafeDistance - startDistance) < fabs(strafeStruct.distance))
    {
      strafeOutput = rampMath(fabs(strafeDistance - startDistance), fabs(strafeStruct.distance), strafeStruct.startSpeed, strafeStruct.maxSpeed,
      strafeStruct.endSpeed) * fabs(strafeStruct.distance) / strafeStruct.distance * strafeSpeedP;
      task::sleep(20);
    }
    strafeStruct.isMoving = false;
    strafeOutput = 0;
  }
  return(0);
}

/*===========================================================================*/

void turnFunction (double distance, int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion)
{
  turnStruct = {distance, startSpeed, maxSpeed, endSpeed, true};
  if (waitForCompletion)
  {
    waitUntil(!turnStruct.isMoving);
  }
}

int turnTask()
{
  double startYaw;
  while(1)
  {
    waitUntil(turnStruct.isMoving);
    startYaw = Inertial.yaw();
    while(fabs(Inertial.yaw() - startYaw) < fabs(turnStruct.distance))
    {
      turnOutput = rampMath(fabs(Inertial.yaw() - startYaw), fabs(turnStruct.distance), turnStruct.startSpeed, turnStruct.maxSpeed,
      turnStruct.endSpeed, 0.2, 0.8) * fabs(turnStruct.distance) / turnStruct.distance;
      task::sleep(20);
    }
    turnStruct.isMoving = false;
    turnOutput = 0;
  }
  return(0);
}

/*===========================================================================*/



void autonInitialize()
{
  task task2 = task( forwardTask );
  task task3 = task( strafeTask );
  task task4 = task( turnTask );
}

void autonStop()
{
  task::stop( forwardTask );
  task::stop( strafeTask );
  task::stop( turnTask );
}