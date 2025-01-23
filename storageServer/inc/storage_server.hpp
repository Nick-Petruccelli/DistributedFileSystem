#pragma once

#include "storage_skeleton.hpp"
#include "command_skeleton.hpp"
#include "registration_stub.hpp"
#include <filesystem>

class NamingServer{
public:
	int start(std::filesystem::path root);

private:
	std::filesystem::path root;
	StorageSkeleton storage_skeleton;
	CommandSkeleton command_skeleton;
	RegistrationStub registration_stub;
};
