#include "../inc/tree_node.hpp"
#include <iostream>

int TreeNode::get_storage(std::string path){
	if(path == name){
		if(children.size() != 0){
			return -2;
		}
		return storage_server_id;
	}
	size_t next_slash_idx = path.find("/");
	if(next_slash_idx == std::string::npos){
		for(TreeNode *child : children){
			if(child->name == path)
				return child->storage_server_id;
		return -1;
		}
	}
	std::string next_node_name = path.substr(0, next_slash_idx);
	path = path.substr(next_slash_idx+1);
	for(TreeNode *child : children){
		if(child->name != next_node_name)
			continue;
		return child->get_storage(path);
	}
	return -1;
}

int TreeNode::create_file(std::string path){
	size_t next_slash_idx = path.find("/");
	std::string next_node_name = path.substr(0, next_slash_idx);
	if(next_slash_idx == std::string::npos){
		if(next_node_name == ""){
			next_node_name = path;
		}
		TreeNode *new_file = new TreeNode();
		new_file->name = next_node_name;
		new_file->storage_server_id = 1;
		children.push_back(new_file);
		return new_file->storage_server_id;
	}
	path = path.substr(next_slash_idx+1);
	int path_valid = -1;
	std::cout << next_node_name << std::endl;
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

int TreeNode::create_dir(std::string path){
	size_t next_slash_idx = path.find("/");
	std::string next_node_name = path.substr(0, next_slash_idx);
	if(next_slash_idx == std::string::npos){
		if(next_node_name == ""){
			next_node_name = path;
		}
		TreeNode *new_dir = new TreeNode();
		new_dir->name = next_node_name;
		new_dir->storage_server_id = -1;
		new_dir->is_dir = true;
		children.push_back(new_dir);
		return 0;
	}
	path = path.substr(next_slash_idx+1);
	int path_valid = -1;
	for(TreeNode *child : children){
		if(next_node_name != child->name){
			continue;
		}
		path_valid = child->create_dir(path);
		if(path_valid != -1){
			return path_valid;
		}
	}
	return path_valid;
}

int TreeNode::del(std::string path){
	if(path == name){
		if(children.size() != 0){
			return -2;
		}
		return storage_server_id;
	}
	size_t next_slash_idx = path.find("/");
	if(next_slash_idx == std::string::npos){
		for(TreeNode *child : children){
			if(child->name != path)
				continue;
			children.remove(child);
			child->delete_branch();
			return 0;
		}
		return -1;
	}
	std::string next_node_name = path.substr(0, next_slash_idx);
	path = path.substr(next_slash_idx+1);
	for(TreeNode *child : children){
		if(child->name != next_node_name)
			continue;
		return child->del(path);
	}
	return -1;
}

void TreeNode::delete_branch(){
	for(TreeNode *child : children){
		child->delete_branch();
	}
	delete this;
}
