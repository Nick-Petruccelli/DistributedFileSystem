#include <iostream>
#include "../inc/service_skeleton.hpp"

int main(){
	std::cout << "Naming Server starting..." << std::endl;
	Service_Skeleton service_skeleton;

	service_skeleton.start(5000);
}
