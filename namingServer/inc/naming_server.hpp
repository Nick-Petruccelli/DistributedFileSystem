#pragma once
#include "tree_node.hpp"
#include "service_skeleton.hpp"

class NamingServer{
public:
	int start();

private:
	TreeNode m_tree_root;
	ServiceSkeleton m_service_skeleton;
};
