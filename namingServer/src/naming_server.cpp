#include <iostream>
#include "../inc/naming_server.hpp"
#include "../inc/service_skeleton.hpp"
#include <pthread.h>


void *start_service_skeleton(void *in){
	ServiceSkeleton service_skeleton = *((ServiceSkeleton*)in);
	service_skeleton.start(5000);
	return NULL;
}

int NamingServer::start(){
	std::cout << "Naming Server starting..." << std::endl;
	ServiceSkeleton service_skeleton;
	//RegistrationSkeleton registration_skeleton;
	TreeNode n1;
	n1.name = "n1";
	n1.storage_server_id = 0;
	m_tree_root.name = "/";
	m_tree_root.children.push_back(&n1);
	service_skeleton.set_root(&m_tree_root);
	pthread_t service_skeleton_thread;
	pthread_t registration_skeleton_thread;
	pthread_create(&service_skeleton_thread, NULL, start_service_skeleton, &service_skeleton);
	pthread_join(service_skeleton_thread, NULL);
	return 0;
}
