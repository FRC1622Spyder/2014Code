#include "WPIObjMgr.h"
#include "Config.h"


namespace Spyder
{
	Joystick* GetJoystick(UINT32 port)
	{
		static Joystick* s_joysticks[] = {0, 0, 0, 0};
		if(!s_joysticks[port])
		{
			s_joysticks[port] = new Joystick(port);
		}
		return s_joysticks[port];
	}
	
	Victor* GetVictor(UINT32 channel)
	{
		static std::map<UINT32, Victor*> s_victors;
		if(!s_victors[channel])
		{
			s_victors[channel] = new Victor(1, channel);
		}
		return s_victors[channel];
	}
	Encoder* GetEncoder(UINT32 aChannel, UINT32 bChannel, bool inverse)
	{
		static std::map<UINT32, Encoder*> s_encoders;
		if(!s_encoders[aChannel])
		{
			s_encoders[aChannel] = new Encoder(aChannel, bChannel, inverse);
		}
		return s_encoders[aChannel];
	}
	
	double GetDeadzone()
	{
		static ConfigVar<double> deadzone("controller_deadzone", 0.15);
		return deadzone.GetVal();
	}
	
	Solenoid* GetSolenoid(UINT32 channel)
	{
		static std::map<UINT32, Solenoid*> s_solenoids;
		if(!s_solenoids[channel])
		{
			s_solenoids[channel] = new Solenoid(channel);
		}
		return s_solenoids[channel];
	}
}
