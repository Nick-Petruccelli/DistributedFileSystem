#include "../inc/tree_node.hpp"
#include <iostream>

int TreeNode::get_storage(std::string path){
	if(path == name){
		if(children.size() != 0){
			return -2;
		}
		return storage_server_id;
	}
	size_t next_file_start = path.find("/");
	if(next_file_start == std::string::npos){
		return -1;
	}
	path = path.substr(next_file_start+1);
	int id_found = -1;
	for(TreeNode *child : children){
		id_found = child->get_storage(path);
		if(id_found != -1){
			return id_found;
		}
	}
	return -1;
}

int TreeNode::create_file(std::string path){
	size_t next_slash_idx = path.find("/");
	std::string next_node_name = path.substr(0, next_slash_idx);
	if(next_slash_idx == std::string::npos || next_slash_idx == 0){
		if(next_node_name == ""){
			next_node_name = path.substr(1);
		}
		TreeNode *new_file = new TreeNode();
		new_file->name = next_node_name;
		new_file->storage_server_id = 1;
		children.push_back(new_file);
		return new_file->storage_server_id;
	}
	path = path.substr(next_slash_idx+1);
	int path_valid = -1;
	for(TreeNode *child : children){
		if(next_node_name != child->name){
			continue;
		}
		path_valid = child->create_file(path);
		if(path_valid != -1){
			return path_valid;
		}
	}
	return path_valid;
}
