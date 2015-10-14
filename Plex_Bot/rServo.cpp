#include "rServo.h"

rServo::rServo(void)
{
	//intanciate object
}

//Attach servos no need with the control board but still declares position
void rServo::attach(int ServoNumber, int Offset, int _min, int _max)
{
	//declare starting place in servo chain
	_servoAddress = ServoNumber;
	//asign starting position for servo and move there
	adjCenter(Offset);
	//Adjusts the maximum and minimum travel of the servos
	adjLimit(_min, _max);
}


//Moves the servo up and down from 0. -90 would is down and 90 is up, all from netrual.
void rServo::move(int pos)
{
	//Limit the angle before it gets to the funtion
	int newPos = limitPos(pos + _servoOffest);
	
	//Add the value of servoOffset to the position. 
	driver.setPWM(_servoAddress, 0, position(newPos));
}

//Used to adjust the center of the servo and store that value
void rServo::adjCenter(int r)
{
	_servoOffest = r;
}

//Change the limiting angles for the servo offset
void rServo::adjLimit(int min, int max)
{
	_servoMinPos = min;
	_servoMaxPos = max;
}

//Adjust the servo min and max of the servo timing
void rServo::adjTiming(int min, int max)
{
	_servoMinTiming = min;
	_servoMaxTiming = max;
}

//Returns the position the servo is moved to given the angle
int rServo::position(int angle)
{
	return map(angle, -90, 90, _servoMinTiming, _servoMaxTiming);}


//This takes in the adjusted position of the servo 
//and returns the limit if the limit is being exceeded
int rServo::limitPos(int angle)
{
	
	if (angle < _servoMinPos) {
		return _servoMinPos;
	}
	if (angle > _servoMaxPos) {
		return _servoMaxPos;
	}
	return angle;
}
