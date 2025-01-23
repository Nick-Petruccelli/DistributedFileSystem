#pragma once

#include <filesystem>

class StorageSkeleton{
public:
	void start(int port, std::filesystem::path root);
	void stop();
private:
	void run();
	int read(std::filesystem::path path);
	int write(std::filesystem::path path);
	int size(std::filesystem::path path);
private:
	std::filesystem::path root;
};
