#include "../inc/storage_skeleton.hpp"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <unistd.h>

int StorageSkeleton::start(int port, std::filesystem::path root){
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

int StorageSkeleton::run(){
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

int StorageSkeleton::parse_call(std::string recv_str, std::vector<std::string> *method_call){
	int args_start_idx = recv_str.find("(");
	if(args_start_idx == std::string::npos){
		return -1;
	}
	method_call->push_back(recv_str.substr(0, args_start_idx));
	recv_str = recv_str.substr(args_start_idx+1);
	int next_arg_idx;
	for(int i=0; i<4; i++){
		next_arg_idx = recv_str.find(",");
		if(next_arg_idx == std::string::npos){
			method_call->push_back(recv_str.substr(0, recv_str.find(")")));
			std::cout << "args[" << i+1 << "] = " << method_call->back() << std::endl;
			return 0;
		}
		/*
		if(next_arg_idx == std::string::npos){
			method_call->push_back(recv_str.substr(0, next_arg_idx));
			std::cout << "args[" << i+1 << "] = " << method_call->back() << std::endl;
			recv_str = recv_str.substr(next_arg_idx+1);
			break;
		}
		*/
		method_call->push_back(recv_str.substr(0, next_arg_idx));
		recv_str = recv_str.substr(next_arg_idx+1);
	}
	return 0;
}

int StorageSkeleton::handle_call(std::vector<std::string> *method_call, char* data_buff){
	if(method_call->size() == 0){
		return -1;
	}
	std::string method = method_call->at(0);
	if(method == "read" && method_call->size() == 4){
		memset(data_buff, 0, 4096);
		int err= read(data_buff, method_call->at(1), std::stoi(method_call->at(2)), std::stoi(method_call->at(3)));
		if(err < 0){
			memset(data_buff, 0, 4096);	
			std::sprintf(data_buff, "Wrote to %s", method_call->at(1).c_str());
		}
	}else if(method == "write" && method_call->size() == 4){
		int storage_id = write(method_call->at(1), std::stoi(method_call->at(2)), &(method_call->at(3)));
		memset(data_buff, 0, 4096);
		if(storage_id >= 0){
			std::sprintf(data_buff, "Wrote to %s", method_call->at(1).c_str());
		}else{
			std::sprintf(data_buff, "Failed to write to %s", method_call->at(1).c_str());
		}
	}else if(method == "size" && method_call->size() == 2){
		std::uintmax_t size = get_size(method_call->at(1));
		memset(data_buff, 0, 4096);

		if(size < 0){
			std::sprintf(data_buff, "File size could not be read.");
		}else{
			std::sprintf(data_buff, "Size: %ld", size);
		}
	}
	return 0;
}

int StorageSkeleton::read(char* data_buff, std::filesystem::path path, int off_set, int num_bytes){
	std::filesystem::path full_path = m_root / path;
	std::ifstream file(full_path, std::ios::in | std::ios::binary);
	if(!file.is_open())
		return -1;
	file.seekg(off_set, std::ios::beg);
	file.read(data_buff, num_bytes);
	for(int i=0; i<10; i++){
		std::cout << data_buff[i];
	}
	std::cout << std::endl;
	return 0;
}

int StorageSkeleton::write(std::filesystem::path path, int off_set, std::string *data){
	std::cout << "hit write" << std::endl;
	std::cout << "path: " << path << std::endl;
	std::cout << "data: " << *data << std::endl;
	std::filesystem::path full_path = m_root / path;
	std::fstream file(full_path, std::ios::in | std::ios::out | std::ios::binary);
	if(!file.is_open())
		return -1;
	file.seekp(off_set, std::ios::beg);
	file.write(data->c_str(), data->size());
	return 0;
}

std::uintmax_t StorageSkeleton::get_size(std::filesystem::path path){
	std::filesystem::path full_path = m_root / path;
	try{
		return std::filesystem::file_size(full_path);
	}catch(const std::filesystem::filesystem_error& err){
		return -1;
	}
	return 0;
}
