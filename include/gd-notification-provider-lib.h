#include <filesystem>
#include <iostream>
#include <Windows.h>

namespace GDNotificationProviderLib {
	class GDNotificationsProvider {
	public:
		HANDLE pipe;
		std::string pipe_name;
		char buffer[1024];
		DWORD cb_to_write, cb_written;

		void connect(std::string pipeName = "\\\\.\\pipe\\GDNotificationsPipe");
		void sendNotification(std::string title, std::string contents);
	};
}