#include "../inc/storage_server.hpp"

int main(){
	StorageServer storage_server;
	std::filesystem::path root = "/home/nickp/test_storage/";
	storage_server.start(root);
}
