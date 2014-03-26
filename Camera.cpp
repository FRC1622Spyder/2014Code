#include "Camera.h"

void Camera::init(Spyder::RunModes runmode, WPIObjMgr *objMan_in)
{
	this->objMan = objMan_in;
	
	//udp client setup:
	this->sockd = socket(AF_INET, SOCK_DGRAM, 0);
	
	bzero(&this->servaddr, sizeof(this->servaddr));
	
	this->servaddr.sin_family = AF_INET;
	this->servaddr.sin_addr.s_addr = inet_addr("10.16.22.5");
	this->servaddr.sin_port = htons(60);
	this->getPacket();
}
std::string Camera::trimZeros(std::string s) // remove leading 0's if any are found
{
	std::string tmp = "";
	size_t loc = s.find_first_not_of('0');
	if(loc != std::string::npos&&s!="") tmp = s.substr(loc); 
	else tmp = s;
	return tmp;
}
void Camera::getPacket()
{
	sendto(this->sockd, "\n", 1, 0, (struct sockaddr *)&this->servaddr, sizeof(this->servaddr));
	int n = recvfrom(this->sockd, this->recv, 100, 0, NULL, NULL);
	this->parse(std::string(this->recv));
}

Packet Camera::parse(std::string s)
{
	///sample data string:
	/// 00ID01T0xCen005T366.5yCen005T283.5area003T143rXCe008T0.145313rYCe005T0.515
	///  The first triad will read "ID10T" for any ID with 10 characters. 
	///  If we do manage to get over a billion objects, someone was quite the ID10T 
	///  with the filtering.
	
	Packet p;
	std::string tmp = "";
	for( uint8_t i = 0; i<=6; i++)
	{
		tmp = s.substr(0, 4); //grab the first chunck of data. may look like 00ID.
		//figure out what tag this is:
		std::string ID_str = this->trimZeros(tmp);
		//use the delimiter as a reference point.
		//the padded length info is directly to the left, and the data is directly to the right
		size_t currentDelimiter = s.find_first_of('T');
		size_t beginLength = currentDelimiter - 2;
		tmp = s.substr(beginLength, 2); //get the length, as a string
		tmp = this->trimZeros(tmp);
		size_t length = atoi(tmp.c_str()); //convert the length to an integer
		tmp = s.substr(currentDelimiter +1, length); //get the string data
		tmp = this->trimZeros(tmp);
		//assume everything is a double.
		double data = atof(tmp.c_str());
		//now, discard the string data we just processed from s and do it again.
		s = s.substr(currentDelimiter+length+1);	//simply replace s with the section of s we have not processed yet.	
		
		if(id_str=="ID")
		{		
		  p.id=(unsigned int)data;
		}	
	  else if(id_str=="xCen")
		{
		  p.centerX=(double)data;
		}	
	  else if(id_str=="yCen")
		{
		  p.centerY=(double)data;
		}
			
	  else if(id_str=="area")
		{
		  p.area=(unsigned int)data;
		}
	  
	  else if(id_str=="rXCe")
		{
		  p.rCenterX=(double)data;
		}		
		
	  else if(id_str=="rYCe")
		{
		  p.rCenterY=(double)data;
		}
		
	  else
		{
		  //couldn't match, warn user.
		  std::cout << "Camera::parse(): couln't parse: '" << id_str <<"' ignoring." <<std::endl;
		}
	}
	return p;
}
