#include <string>
#include <iostream>
#include <cstdio>
#include <vector>

#include <windows.h>

#include "../serial/include/serial/serial.h"

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

void enumerate_ports()
{
	vector<serial::PortInfo> devices_found = serial::list_ports();

	vector<serial::PortInfo>::iterator iter = devices_found.begin();

	while (iter != devices_found.end())
	{
		serial::PortInfo device = *iter++;

		printf("(%s, %s, %s)\n", device.port.c_str(), device.description.c_str(),
			device.hardware_id.c_str());
	}
}

int run(int argc, char **argv)
{
	try {
		enumerate_ports();

		string port;
		std::cin >> port;

		// Argument is the baudrate
		unsigned long baud = 0;
		sscanf_s(argv[1], "%lu", &baud);

		// port, baudrate, timeout in milliseconds
		serial::Serial conn(port, baud, serial::Timeout::simpleTimeout(1000));

		std::cout << "running" << endl;
		string last_msg;
		while (true) {
			string msg;
			msg.push_back('\0');
			if (GetAsyncKeyState('W')) msg += 'u';
			if (GetAsyncKeyState('A')) msg += 'l';
			if (GetAsyncKeyState('S')) msg += 'd';
			if (GetAsyncKeyState('D')) msg += 'r';

			if (GetAsyncKeyState('I')) msg += 't';
			if (GetAsyncKeyState('J')) msg += 's';
			if (GetAsyncKeyState('K')) msg += 'x';
			if (GetAsyncKeyState('L')) msg += 'c';

			if (GetAsyncKeyState(0x1B /*escape*/)) msg += '+';

			if (msg == last_msg) continue;
			std::cout << "updating , buttons=" << msg << endl;
			last_msg = msg;
			conn.write(msg);
		}

		system("pause");
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << endl;
		system("pause");
		return -1;
	}
	return 0;
}

int main(int argc, char **argv) {
	try {
		return run(argc, argv);
	}
	catch (exception &e) {
		cerr << "Unhandled Exception: " << e.what() << endl;
	}
}
