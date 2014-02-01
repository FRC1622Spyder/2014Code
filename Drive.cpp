#include "Subsystem.h"
#include "WPIObjMgr.h"
#include "Config.h"
#include <math.h>
#include <iostream>

class Drive : public Spyder::Subsystem
{
	
	private:
		Spyder::TwoIntConfig leftJoystick;
		Spyder::TwoIntConfig rightJoystick;
		
		Spyder::ConfigVar<UINT32> leftmotor;
		Spyder::ConfigVar<UINT32> rightmotor;
		
		Spyder::ConfigVar<bool> leftMotorInv;
		Spyder::ConfigVar<bool> rightMotorInv;
		
		
	public:
		Drive()
		{
		}
		
		virtual ~Drive()
		{
		}
		
		virtual void Init(Spyder::RunModes runmode)
		{
		}
		
		virtual void Periodic(Spyder::RunModes runmode)
		{
			switch(runmode){
				case Spyder::M_DISABLED:
					break;
					
				case Spyder::M_TELEOP:
					break;
					
				default:
					break;
			}
			
		}
		
		virtual void RobotInit()
		{
		}
};

Drive drive;
