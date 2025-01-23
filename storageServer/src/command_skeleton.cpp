#include "../inc/command_skeleton.hpp"
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <unistd.h>

int CommandSkeleton::start(int port, std::filesystem::path root){
	m_root = root;

	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(m_sock < 0){
		std::cerr << "Failed to create socket" << std::endl;
		return -1;
	}

	m_hint.sin_family = AF_INET;
	m_hint.sin_port = htons(port);
	m_hint.sin_addr.s_addr = INADDR_ANY;

	if(bind(m_sock, (struct sockaddr*)&m_hint, sizeof(m_hint)) < 0){
		std::cerr << "Failed to bind socket: " << strerror(errno) << std::endl;
		return -2;
	}

	if(listen(m_sock, SOMAXCONN) < 0){
		std::cerr << "Failed to listen on socket." << std::endl;
		return -3;
	}

	int run_err = run();
	return run_err;
}

void CommandSkeleton::stop(){

}

int CommandSkeleton::run(){
	while(true){
		int client_sock = accept(m_sock, (struct sockaddr*)&m_client, &m_client_len);
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
		std::string recv_str = std::string(data_buff, 0, bytes_recv);
		std::cout << "Recived: " << recv_str << std::endl;
		std::vector<std::string> method_call;
		int parse_err = parse_call(recv_str, &method_call);
		int handle_err = handle_call(&method_call, data_buff);
		send(client_sock, data_buff, bytes_recv + 1, 0);
		close(client_sock);
	}
	return 0;
}

int CommandSkeleton::parse_call(std::string recv_str, std::vector<std::string> *method_call){
	int args_start_idx = recv_str.find("(");
	if(args_start_idx == std::string::npos){
		return -1;
	}
	method_call->push_back(recv_str.substr(0, args_start_idx));
	recv_str = recv_str.substr(args_start_idx+1);
	int next_arg_idx = recv_str.find(",");
	if(next_arg_idx == std::string::npos){
		method_call->push_back(recv_str.substr(0, recv_str.find(")")));
		return 0;
	}
	for(int i=0; i<4; i++){
		next_arg_idx = recv_str.find(",");
		if(next_arg_idx == std::string::npos){
			method_call->push_back(recv_str.substr(0, next_arg_idx));
			recv_str = recv_str.substr(next_arg_idx+1);
			break;
		}
		method_call->push_back(recv_str.substr(0, next_arg_idx));
		recv_str = recv_str.substr(next_arg_idx+1);
	}
	return 0;
}

int CommandSkeleton::handle_call(std::vector<std::string> *method_call, char* data_buff){
	if(method_call->size() == 0){
		return -1;
	}
	std::string method = method_call->at(0);
	if(method == "create_file" && method_call->size() == 2){
		int storage_id = create_file(method_call->at(1));
		memset(data_buff, 0, 4096);
		std::sprintf(data_buff, "%d", storage_id);
	}else if(method == "create_dir" && method_call->size() == 2){
		int storage_id = create_dir(method_call->at(1));
		memset(data_buff, 0, 4096);
		if(storage_id >= 0){
			std::sprintf(data_buff, "Created file at %s", method_call->at(1).c_str());
		}else{
			std::sprintf(data_buff, "Failed to create file at %s", method_call->at(1).c_str());
		}
	}else if(method == "del" && method_call->size() == 2){
		int err = del(method_call->at(1));
		memset(data_buff, 0, 4096);
		if(err >= 0){
			std::sprintf(data_buff, "Created dir at %s", method_call->at(1).c_str());
		}else{
			std::sprintf(data_buff, "Failed to create dir at %s", method_call->at(1).c_str());
		}
	}
	return 0;
}


int CommandSkeleton::create_dir(std::filesystem::path path){

	return 0;
}

int CommandSkeleton::create_file(std::filesystem::path path){

	return 0;
}

int CommandSkeleton::del(std::filesystem::path path){

	return 0;
}
