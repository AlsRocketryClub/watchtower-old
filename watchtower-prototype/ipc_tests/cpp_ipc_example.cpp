#include <windows.h>
#include <iostream>
#include <string>

void createPipe() {
	const char* pipeName = "\\\\.\\pipe\\my_pipe";
	HANDLE hPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 4096, 4096, 0, NULL);
	if (hPipe == INVALID_HANDLE_VALUE) {
		DWORD error = GetLastError();
		std::cerr << "Failed to create named pipe. Error code:" << error << std::endl;
	}
	else {
		std::cout << "Named pipe created successfully." << std::endl;
		CloseHandle(hPipe);
	}
}

void writeToPipe(const std::string &message) {
	HANDLE pipe;
	const char *pipeName = "\\\\.\\pipe\\my_pipe";
	
	pipe = CreateFile(
		pipeName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

	if (pipe != INVALID_HANDLE_VALUE) {
		DWORD bytesWritten;
		WriteFile(
			pipe,
			message.c_str(),
			message.size(),
			&bytesWritten,
			NULL
		);
		CloseHandle(pipe);
	}
	else {
		DWORD error = GetLastError();
		std::cout << "Failed to open pipe for writing. Error code: " << error << std::endl;
	}
}

std::string readFromPipe() {
	HANDLE pipe;
	const char *pipeName = "\\\\.\\pipe\\my_pipe";
	
	pipe = CreateFile(
		pipeName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

	if (pipe != INVALID_HANDLE_VALUE) {
		DWORD bytesRead;
		char buffer[256];
		ReadFile(
			pipe,
			buffer,
			sizeof(buffer),
			&bytesRead,
			NULL
		);
		CloseHandle(pipe);
		return std::string(buffer);
	}
	else {
		DWORD error = GetLastError();
		std::cout << "Failed to open pipe for reading. Error code: " << error << std::endl;
		return "";
	}
}

int main() {
	std::string message = "Hello from C++!";
	createPipe();
	writeToPipe(message);

	//std::string response = readFromPipe();
	//std::cout << "Received message from Python: " << response << std::endl;
	return 0;
}
