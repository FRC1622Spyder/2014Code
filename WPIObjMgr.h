#pragma once
#include <WPILib.h>

namespace Spyder
{
	Joystick *GetJoystick(UINT32 port);
	Relay *GetRelay(UINT32 channel);
	Victor* GetVictor(UINT32 channel);
	Solenoid* GetSolenoid(UINT32 channel);
	Encoder* GetEncoder(UINT32 aChannel, UINT32 bChannel, bool inverse);
	double GetDeadzone();
};
