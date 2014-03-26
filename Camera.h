

#include <string>
#include <sys/socket.h> //oh god, vxworks, why
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <vxWorks.h>
#include <stdioLib.h>
#include <sockLib.h>
#include <inetLib.h>
#include <strLib.h>
#include <hostLib.h>
#include <ioLib.h>
#include <sstream>

#include "Subsystem.h"
#include "WPIObjMgr.h"
#include "Config.h"
#include "Console.h"

struct Packet
{
	unsigned int id;
	double centerX;
	double centerY;
	unsigned int area;
	double rCenterX;
	double rCenterY;
};

class Camera : public Spyder::Subsystem
{
private:
	WPIObjMgr *objMan;
	
	int sockd;
	char *recv[100];
	struct sockaddr_in servaddr, cientaddr;
	Packet parse(std::string s);
	void getPacket();
	std::string trimZeros(std::string);
public:
	
	Camera() : Spyder::Subsystem("Camera"){}
	virtual ~Camera();
	virtual void Init(Spyder::RunModes runmode, WPIObjMgr *objMan_in);
	virtual void Periodic(Spyder::RunModes runmode);
	virtual void RobotInit();
};

Camera camera;
