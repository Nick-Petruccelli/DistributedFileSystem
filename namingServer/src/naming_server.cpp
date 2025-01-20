#include <iostream>
#include "../inc/naming_server.hpp"
#include "../inc/service_skeleton.hpp"

int NamingServer::start(){
	std::cout << "Naming Server starting..." << std::endl;
	ServiceSkeleton service_skeleton;
	TreeNode n1;
	n1.name = "n1";
	n1.storage_server_id = 0;
	m_tree_root.children.push_back(n1);
	service_skeleton.set_root(&m_tree_root);
	service_skeleton.start(5000);
	return 0;
}
