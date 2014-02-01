#include "Subsystem.h"
#include "WPIObjMgr.h"
#include "Config.h"
#include "Console.h"
#include <iostream>

class Shooter : public Spyder::Subsystem
{
private:
	/*Spyder::ConfigVar<UINT32> motorShoot1;
	Spyder::ConfigVar<UINT32> motorShoot2;
	
	Spyder::ConfigVar<UINT32> pistonSolenoidExt;
	Spyder::ConfigVar<UINT32> pistonSolenoidRet;
	
	Spyder::TwoIntConfig fireButton;*/
	
public:
	Shooter()
	{
		
	}
	virtual ~Shooter()
	{
	}
	
	virtual void Init()
	{
		
	}
	
	virtual void Perodic(Spyder::RunModes runmode)
	{
		switch(runmode)
		{
			case Spyder::M_DISABLED://disabled code here
				
				break;
			case Spyder::M_AUTO://autonomous code here
				
				break;
			case Spyder::M_TELEOP://Tele-operation code here
				
				break;
		};
	}
	
	virtual void RobotInit()
	{
		
	}
};

Shooter shooter;
