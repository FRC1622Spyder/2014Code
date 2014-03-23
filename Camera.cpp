#include "Subsystem.h"
#include "WPIObjMgr.h"
#include "Config.h"
#include "Console.h"
class Camera : public Spyder::Subsystem
{
private:
	//Relay lights;
public:
	Camera() : Spyder::Subsystem("Camera")//, lights(8)
	{
	}
	virtual ~Camera()
	{
	}
	virtual void Init(Spyder::RunModes runmode)
	{
	}
	virtual void Periodic(Spyder::RunModes runmode)
	{
		
	}
	virtual void RobotInit()
	{
	}
};
Camera camera;
