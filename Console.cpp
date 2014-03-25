#include "Console.h"
#include <sstream>

bool Spyder::Console::Connect(const std::string &strIP, unsigned short usPort)
{
	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(m_socket == -1)
	{
		return false;
	}
	memset((void*)&m_serverAddr, 0, sizeof(m_serverAddr));
	m_serverAddr.sin_len = sizeof(sockaddr_in);
	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_port = usPort;
	m_serverAddr.sin_addr.s_addr = inet_addr(const_cast<char*>(strIP.c_str()));// I'm so sorry for this
	return true;
}

bool Spyder::Console::SendPacket(const std::string &strSubsystem, Packet& packet)
{
	std::stringstream ss;
	int length = strSubsystem.length();
	ss << std::string((char*)&length, 4); //store first 4 digits of length
	ss << strSubsystem; // append contents of strSubsystem
	ss << packet.GetData(); // append contents of the packet (string data)
	if(sendto(
			m_socket, //socket
			const_cast<char*>(ss.str().c_str()), //buffer
			ss.str().length(), //buffer length
			0, //flags; can include MSG_OOB (out of band data), and/or MSG_DONTROUTE. other UNIX flags are not supported.
			(sockaddr*)&m_serverAddr, //recipent addr
			m_serverAddr.sin_len) //length of addr
			== -1)
	{
		return false;
	}
	return true;
}

Spyder::Console* Spyder::Console::GetSingleton()
{
	static Spyder::Console *c = new Console;
	return c;
}

Spyder::Console::Console()
{
}
Spyder::Console::~Console()
{
}
