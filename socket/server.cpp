#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class Server
{
	public:
		Server(const sa_family_t family, const int type, const int protocol, const string ip, const uint16_t port, const int backlog)
		{
			clientSfd = -1;
			mSfd = socket(family, type, protocol);
			if(mSfd == -1)
				throw runtime_error("create socket");
			sockaddr_in addr{ family, htons(port) };
			if(ip.empty())
				addr.sin_addr.s_addr = htonl(INADDR_ANY);
			else
				inet_pton(AF_INET, ip.c_str(), reinterpret_cast<char*>(&addr.sin_addr.s_addr));
			if(bind(mSfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)))
				throw runtime_error("bind socket");
			if(listen(mSfd, backlog))
				throw runtime_error("listen socket");
		}

		~Server()
		{
			if(mSfd != -1)
				close(mSfd);
			if(clientSfd != -1)
				close(clientSfd);
		}

		int initServer(const sa_family_t family, const int type, const int protocol, const string ip, const uint16_t port, const int backlog)
		{
			if(mSfd != -1)
			{
				close(mSfd);
				mSfd = -1;
			}
			if(clientSfd != -1)
			{
				close(clientSfd);
				clientSfd = -1;
			}

			mSfd = socket(family, type, protocol);
			if(mSfd == -1)
				throw runtime_error("create socket");
			sockaddr_in addr{ family, htons(port) };
			if(ip.empty())
				addr.sin_addr.s_addr = htonl(INADDR_ANY);
			else
				inet_pton(AF_INET, ip.c_str(), reinterpret_cast<char*>(&addr.sin_addr.s_addr));
			if(bind(mSfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)))
				throw runtime_error("bind socket");
			if(listen(mSfd, backlog))
				throw runtime_error("listen socket");
		}

		bool serverAccept()
		{
			clientAddrLen = sizeof(clientAddr);
			if((clientSfd = accept(mSfd, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen)) == -1)
			{
				perror("accept");
				return false;
			}
			char tempBuf[16]{};
			inet_ntop(AF_INET, reinterpret_cast<void*>(&clientAddr.sin_addr.s_addr), tempBuf, 16);
			cout << "收到请求：\n" << "客户端IP - " << tempBuf << endl;
			return true;
		}

		ssize_t readData(char *dataBuf, const size_t bufSize)
		{
			if(mSfd == -1 || clientSfd == -1)
				return -1;
			return read(clientSfd, dataBuf, bufSize);
		}

		ssize_t writeData(const char *data, const size_t dataLen)
		{
			if(data == nullptr)
				return 0;
			return write(clientSfd, data, dataLen);
		}

		int closeClientSocket()
		{
			int ret = close(clientSfd);
			clientSfd = -1;
			return ret;
		}

		int closeServerSocket()
		{
			int ret = close(mSfd);
			mSfd = -1;
			return ret;
		}

	private:
		int mSfd;
		int clientSfd;
		sockaddr_in clientAddr;
		socklen_t clientAddrLen;

};

#define POST 6699

size_t toUpperAll(char *data, const size_t size)
{
	int i = 0;
	while(i < size)
	{
		data[i] = toupper(data[i]);
		++i;
	}
	return i;
}

int main()
{
	try
	{
		Server server(AF_INET, SOCK_STREAM, 0, "", POST, 128);
		constexpr size_t bufSize = BUFSIZ;
		char dataBuf[bufSize]{};

		cout << "服务器已启动..." << endl;

		server.serverAccept();
		while(true)
		{
			ssize_t dataSize = server.readData(dataBuf, bufSize);
			toUpperAll(dataBuf, dataSize);
			dataSize = server.writeData(dataBuf, dataSize);
			if(dataSize == 0)
				break;
			cout << "状态：转换并发送" << dataSize << "字节数据" << endl;
		}
	} catch(runtime_error &err) {
		perror(err.what());
		exit(1);
	}
	cout << "服务器终止运行..." << endl;
#if 0
	while(server.serverAccept())
	{
		ssize_t dataSize = server.readData(dataBuf, bufSize);
		toUpperAll(dataBuf, dataSize);
		dataSize = server.writeData(dataBuf, dataSize);
		cout << "转换并发送" << dataSize << "字节数据" << endl;
	}
#endif
	return 0;
}
