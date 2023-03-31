#include "gd-notification-provider-lib.h"

namespace GDNotificationProviderLib {
	class GDNotificationsProvider {
	public:
		HANDLE pipe;
		std::string pipe_name;
		char buffer[1024];
		DWORD cb_to_write, cb_written;

		void connect(std::string pipeName = "\\\\.\\pipe\\GDNotificationsPipe") {
			this->pipe_name = pipeName;

			this->pipe = CreateFile(
				this->pipe_name.c_str(),
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);

			ConnectNamedPipe(this->pipe, NULL);
		}

		void sendNotification(std::string title, std::string contents) {

			std::string lpvMessage;
			lpvMessage = title + "~" + contents;

			this->cb_to_write = (lstrlen(TEXT(lpvMessage.c_str())) + 1) * sizeof(TCHAR);

			WriteFile(
				this->pipe,
				TEXT(lpvMessage.c_str()),
				this->cb_to_write,
				&this->cb_written,             // bytes written 
				NULL);
		}
	};
}