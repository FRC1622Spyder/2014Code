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
		switch(runmode)
		{
		case Spyder::M_TELEOP:
			Spyder::GetRelay(8)->Set(Relay::kForward);
			break;
		case Spyder::M_AUTO:
			Spyder::GetRelay(8)->Set(Relay::kForward);
			break;
		case Spyder::M_DISABLED:
			Spyder::GetRelay(8)->Set(Relay::kOff);
			break;
		default:
			Spyder::GetRelay(8)->Set(Relay::kForward);
		}
	}
	virtual void RobotInit()
	{
	}
};
Camera camera;
