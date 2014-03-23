#include "WPIObjMgr.h"
#include "Config.h"


namespace Spyder
{
	double GetDeadzone()
	{
		static ConfigVar<double> deadzone("controller_deadzone", 0.15);
		return deadzone.GetVal();
	}
		
};	
	void WPIObjMgr::baseInit()
	{
		for(uint8_t i = 0; i<4; i++) //joystick init
		{
			this->m_joysticks[i] = new Joystick((uint32_t)i+1); 
		}
		for(uint8_t i = 0; i<10;i++)//victors
		{
			this->m_victors[i] = new Victor((uint32_t)i);
		}
		for(uint8_t i = 0; i<8;i++)//solenoids
		{
			this->m_solenoids[i] = new Solenoid((uint32_t)i);
		}
	}
	
	bool WPIObjMgr::addEncoder(UINT32 aChan, UINT32 bChan, bool reverse)
	{
		for(uint8_t i=0; i<5;i++)
		{
			if(this->m_encoders[i]==NULL)
			{
				this->m_encoders[i] = new Encoder(aChan, bChan, reverse);
				return true; //slot available, return.
			}
		}
		return false; //no more encoder slots available
	}
	
	WPIObjMgr::WPIObjMgr()
	{
		this->baseInit();
		for(uint8_t i=0; i<8;i++)
		{
			this->m_relays[i] = new Relay((uint32_t)i, Relay::kBothDirections);
		}

		
	}
	
	WPIObjMgr::WPIObjMgr(Spyder::IOCfg config)
	{
		this->baseInit();
		for(uint8_t i = 0; i<8; i++)//relays
		{
			this->m_relays[i] = new Relay((uint32_t)i, config.relayModes[i]);
		}
		for(uint8_t i=0; i<config.numEncoders;i++) //encoders
		{
			this->m_encoders[i] = new Encoder((UINT32) config.aChanels[i], 
					(UINT32) config.bChanels[i], config.encoderReverse);
		}
	}
	
	Joystick* WPIObjMgr::GetJoystick(uint8_t port)
	{
		return this->m_joysticks[port];
	}
	
	Relay* WPIObjMgr::GetRelay(uint8_t channel)
	{
		return this->m_relays[channel];
	}
	
	Victor* WPIObjMgr::GetVictor(uint8_t channel)
	{
		return this->m_victors[channel];
	}
	
	Encoder* WPIObjMgr::GetEncoder(uint8_t index)
	{
		return this->m_encoders[index];
	}
	
	Solenoid* WPIObjMgr::GetSolenoid(uint8_t channel)
	{
		return this->m_solenoids[channel];
	}
	
