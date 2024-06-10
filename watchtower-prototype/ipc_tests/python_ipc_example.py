import win32pipe, win32file

def write_to_pipe(message):
    pipe_handle = win32file.CreateFile(r'\\.\\pipe\\my_pipe',
                                       win32file.GENERIC_WRITE, 0, None, 
                                       win32file.OPEN_EXISTING, 0, None)
    win32pipe.SetNamedPipeHandleState(pipe_handle, win32pipe.PIPE_READMODE_MESSAGE, None, None)
    win32file.WriteFile(pipe_handle, message.encode())
    win32file.CloseHandle(pipe_handle)
    
def read_from_pipe():
    pipe_handle = win32file.CreateFile(r'\\.\\pipe\\my_pipe',
                                       win32file.GENERIC_READ, 0, None, 
                                       win32file.OPEN_EXISTING, 0, None)
    win32pipe.SetNamedPipeHandleState(pipe_handle, win32pipe.PIPE_READMODE_MESSAGE, None, None)
    message = win32file.ReadFile(pipe_handle, 4096)[1].decode()
    win32file.CloseHandle(pipe_handle)
    return message

if __name__ == '__main__':
    write_to_pipe('Hello from Python!')
    message = read_from_pipe()
    print("Received message from C++:", message)