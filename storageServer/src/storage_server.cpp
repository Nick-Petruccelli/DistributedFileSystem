#include <iostream>
#include "../inc/storage_server.hpp"
#include "../inc/command_skeleton.hpp"
#include "../inc/storage_skeleton.hpp"
#include <pthread.h>


struct command_thread_in{
	CommandSkeleton* command_skeleton;
	int port;
	std::filesystem::path *root;
};

struct storage_thread_in{
	StorageSkeleton* storage_skeleton;
	int port;
	std::filesystem::path *root;
};

void *start_command_thread(void* in){
	struct command_thread_in *input = (struct command_thread_in*)in;
	CommandSkeleton command_skeleton = *(input->command_skeleton);
	int port = input->port;
	std::filesystem::path root = *(input->root);
	command_skeleton.start(port, root);
	return NULL;
}

void *start_storage_thread(void* in){
	struct storage_thread_in *input = (struct storage_thread_in*)in;
	StorageSkeleton storage_skeleton = *(input->storage_skeleton);
	int port = input->port;
	std::filesystem::path root = *(input->root);
	storage_skeleton.start(port, root);
	return NULL;
}

int StorageServer::start(std::filesystem::path root){
	std::cout << "Storage Server starting..." << std::endl;

	pthread_t command_thread;
	pthread_t storage_thread;

	struct command_thread_in command_in;
	command_in.command_skeleton = &command_skeleton;
	command_in.port = 5000;
	command_in.root = &root;
	std::cout << "Starting command thread." << std::endl;
	pthread_create(&command_thread, NULL, start_command_thread, &command_in);

	struct storage_thread_in storage_in;
	storage_in.storage_skeleton = &storage_skeleton;
	storage_in.port = 5050;
	storage_in.root = &root;
	std::cout << "Starting stroage thread." << std::endl;
	pthread_create(&storage_thread, NULL, start_storage_thread, &storage_in);

	pthread_join(command_thread, NULL);
	pthread_join(storage_thread, NULL);
	/*
	*/
	
	return 0;
}
