#pragma once
#include "tree_node.hpp"

class RegistrationSkeleton{
public:
	void start(int port);
	void set_root(TreeNode *tree_root);

private:
	int register_storage();

};
