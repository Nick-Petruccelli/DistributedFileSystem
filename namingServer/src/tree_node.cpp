#include "../inc/tree_node.hpp"

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
	for(TreeNode child : children){
		id_found = child.get_storage(path);
		if(id_found != -1){
			return id_found;
		}
	}
	return -1;
}
