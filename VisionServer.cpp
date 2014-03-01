#include "Subsystem.h"
#include "WPIObjMgr.h"
#include "Config.h"
#include "Console.h"
#include <cmath>
#include <iostream>

class VisionServer : public Sppyder::Subsystem
{
private:
	
public:
	VisionServer() : Spyder::Subsystem("VisionServer")
	{
	}
	
	virtual ~VisionServer()
	{
	}
	
	virtual void Init(Spyder::RunModes runmode)
	{
		switch(runmode)
		{
		case Spyder::M_AUTO:
			//auto code
			break;
		case Spyder::M_TELEOP:
			//teleop code
			break;
		default:
			break;
		}
	}
}
