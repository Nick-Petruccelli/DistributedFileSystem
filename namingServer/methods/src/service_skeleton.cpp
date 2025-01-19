#include "../inc/service_skeleton.hpp"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int Service_Skeleton::start(int port){
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		std::cerr << "Failed to create socket" << std::endl;
		return -1;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(5000);
	hint.sin_addr.s_addr = INADDR_ANY;

	if(bind(sock, (struct sockaddr*)&hint, sizeof(hint)) < 0){
		std::cerr << "Failed to bind socket: " << strerror(errno) << std::endl;
		return -2;
	}

	if(listen(sock, SOMAXCONN) < 0){
		std::cerr << "Failed to listen on socket." << std::endl;
		return -3;
	}
	
	sockaddr_in client;
	socklen_t client_len = sizeof(client);

	while(true){
		int client_sock = accept(sock, (struct sockaddr*)&client, &client_len);
		if(client_sock < 0){
			std::cerr <<  "Failed to accept client connection:" << std::endl;
			return -1;
		}
		char data_buff[4096];
		std::memset(data_buff, 0, 4096);
		int bytes_recv = recv(client_sock, data_buff, 4096, 0);
		if(bytes_recv < 0){
			std::cerr << "Failed to recive from the client" << std::endl;
			continue;
		}
		if(bytes_recv == 0){
			std::cout << "Client disconected." << std::endl;
			break;
		}
		std::cout << "Recived: " << std::string(data_buff, 0, bytes_recv) << std::endl;
		send(client_sock, data_buff, bytes_recv + 1, 0);
		close(client_sock);
	}

	return 0;
}
