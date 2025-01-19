# ifndef SERVICE_SKELETON
# define SERVICE_SKELETON
#include <list>
#include <string>
# endif

class Service_Skeleton{
	public:
		int start(int port);
		int stop();

	private:
		std::string get_storage(std::string path);
		bool is_directory(std::string path);
		std::list<std::string> list_dir(std::string path);
		bool create_file(std::string path);
		bool create_dir(std::string path);
		bool del(std::string path);

	private:
		int port;
};
