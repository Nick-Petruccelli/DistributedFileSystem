#pragma once

#include "tree_node.hpp"
#include <list>
#include <string>
#include <netinet/in.h>
#include <vector>

class ServiceSkeleton{
	public:
		int start(int port);
		void stop();
		void set_root(TreeNode* tree_root);

	private:
		int run();
		void exit_sig_handel(int sig);
		int parse_call(std::string recv_str, std::vector<std::string> *method_call);
		int handle_call(std::vector<std::string> *call_recived, char* data_buff);
		int get_storage(std::string path);
		bool is_directory(std::string path);
		std::list<std::string> list_dir(std::string path);
		int create_file(std::string path);
		int create_dir(std::string path);
		int del(std::string path);

	private:
		TreeNode* m_tree_root;
		int m_sock;
		sockaddr_in m_hint;
		sockaddr_in m_client;
		socklen_t m_client_len = sizeof(m_client);
		bool m_is_running = false;
		int m_port;
};
