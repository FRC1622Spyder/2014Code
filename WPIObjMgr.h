#pragma once
#include <WPILib.h>
class WPIObjMgr;
namespace Spyder
{
	double GetDeadzone(); //shouldn't this go in a utilities file?
	WPIObjMgr *WPIObjMgr::getSingleton()
	{
		static WPIObjMgr *objMgr = new WPIObjMgr();
		return objMgr;
	}

	struct IOCfg{
		Relay::Direction relayModes[8];
		uint8_t numEncoders;
		uint8_t aChanels[5];
		uint8_t bChanels[5];
		bool encoderReverse[5];
	};
};
	class WPIObjMgr {
		
		Joystick *m_joysticks[4];
		Victor *m_victors[10];
		Solenoid * m_solenoids[8];
		Encoder * m_encoders[5];
		Relay * m_relays[8];
		void baseInit(void);
	public:
		
		WPIObjMgr();
		WPIObjMgr(Spyder::IOCfg);
		bool addEncoder(UINT32 aChan, UINT32 bChan, bool reverse);
		Joystick *GetJoystick(uint8_t port);
		Relay *GetRelay(uint8_t channel);
		Victor* GetVictor(uint8_t channel);
		Solenoid* GetSolenoid(uint8_t channel);
		Encoder* GetEncoder(uint8_t index);
		
	};

