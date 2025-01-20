#pragma once
#include <string>
#include <list>

class TreeNode{
public:
	int get_storage(std::string path);
	int create_file(std::string path);
public:
	int storage_server_id;
	std::string name;
	std::list<TreeNode*> children;
};
