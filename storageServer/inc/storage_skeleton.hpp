#pragma once

#include <cstdint>
#include <filesystem>
#include <netinet/in.h>
#include <vector>
#include <string>

class StorageSkeleton{
public:
	int start(int port, std::filesystem::path root);
	void stop();
private:
	int run();
	int parse_call(std::string recv_str, std::vector<std::string> *method_call);
	int handle_call(std::vector<std::string> *method_call, char* data_buff);
	int read(char* data_buff, std::filesystem::path path, int off_set, int num_bytes);
	int write(std::filesystem::path path, int off_set, std::string *data);
	std::uintmax_t get_size(std::filesystem::path path);
private:
	std::filesystem::path m_root;
	int m_sock;
	sockaddr_in m_hint;
	sockaddr_in m_client;
	socklen_t m_client_len = sizeof(m_client);
	bool m_is_running = false;
	int m_port;
};
