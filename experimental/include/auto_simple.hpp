#include<main.h>
#include<auto.hpp>
/* Enumerations */
typedef enum _stopType
{
	stopNone =		0b00000000,
	stopSoft =		0b00000001,
	stopHarsh =		0b00000010
} tStopType;

typedef enum _mttMode
{
	mttSimple,
	mttProportional,
	mttCascading
} tMttMode;

/* Variables */
sVector gTargetLast;

/* Functions */
void moveToTargetSimple(float y, float x, float ys, float xs, unsigned int power, unsigned int startPower, float maxErrX, float decelEarly, unsigned int decelPower, float dropEarly = 0, tStopType stopType = stopSoft | stopHarsh, tMttMode mode = mttProportional, bool velSafety = false);
void moveToTargetDisSimple(float a, float d, float ys, float xs, unsigned int power, unsigned int startPower, float maxErrX, float decelEarly, unsigned int decelPower, float dropEarly = 0, tStopType stopType = stopSoft | stopHarsh, tMttMode mode = mttProportional, bool velSafety = false);
void turnToAngleNewAlg(float a, tTurnDir turnDir, float fullRatio, unsigned int coastPower, float stopOffsetDeg, bool mogo = false, bool harshStop = true, bool velSafety = false);
void turnToTargetNewAlg(float y, float x, tTurnDir turnDir, float fullRatio, unsigned int coastPower, float stopOffsetDeg, bool mogo = false, bool harshStop = true, float offset = 0, bool velSafety = false);
void sweepTurnToTarget(float y, float x, float a, float r, tTurnDir turnDir, unsigned int power, bool slow = true, bool velSafety = false);