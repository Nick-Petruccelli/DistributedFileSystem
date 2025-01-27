#include <iostream>
#include "../inc/storage_server.hpp"
#include "../inc/command_skeleton.hpp"
#include "../inc/storage_skeleton.hpp"
#include <pthread.h>


int StorageServer::start(std::filesystem::path root){
	std::cout << "Storage Server starting..." << std::endl;

	command_skeleton.start(5000, root);
	
	return 0;
}
