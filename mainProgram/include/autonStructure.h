extern double headingDeg;
extern void autonReset();
extern void autonTaskStart();
extern void forwardFunction (double distance, int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion = true);
extern void strafeFunction  (double distance, int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion = true);
extern void turnFunction    (double distance, int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion = true);
extern void moveTurn        (double distance, double actualDegrees, double sensorDegrees, int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion = true);
extern double forwardOutput;
extern double strafeOutput;
extern double turnOutput;
extern double headingDeg;
extern bool gyroActive;
struct rampStruct
{
  double distance;
  int startSpeed;
  int maxSpeed;
  int endSpeed;
  bool isMoving;
};
extern rampStruct forwardStruct;
extern rampStruct strafeStruct;
extern rampStruct turnStruct;
extern int allianceColor;

extern double gyroYawStart;
#define gyroYaw ((Inertial.rotation(deg) - gyroYawStart))

#define forwardDistanceP (0.0349065850393)
#define strafeDistanceP (0.0310137457045)
#define strafeSpeedP (1.12551980572)

#define forwardDistance ((FrontLeftDrive.rotation(deg) + BackLeftDrive.rotation(deg) + FrontRightDrive.rotation(deg) + BackRightDrive.rotation(deg)) * 0.25 * forwardDistanceP)
#define strafeDistance ((FrontLeftDrive.rotation(deg) - BackLeftDrive.rotation(deg) + BackRightDrive.rotation(deg) - FrontRightDrive.rotation(deg)) * 0.25 * strafeDistanceP)

#define blueAlliance 1
#define redAlliance -1

#define sign(value) (value >= 0 ? 1 : -1)