#include <stdio.h>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
	printf("Hello, world\n");

	char ip[] = {"vag"};

	char file_line[512] = {0};

	std::string test_str = "vag=10.20.30.40";
	if(test_str.find(ip) != std::string::npos)
	{
		std::size_t pos = test_str.find("=");
		if(pos == std::string::npos)
		{
			printf("can not find string\n");
			return 0;
		}
		std::string value = test_str.substr(pos+1);
		cout << value << endl;
	}


	std::ifstream is("test.ini", std::ios::in);
	if(is)
	{
		is.getline(file_line, 512);
		std::string temp_str(file_line);
		if(temp_str.find(ip) != std::string::npos)
		{
			std::size_t pos = temp_str.find("=");
			if(pos == std::string::npos)
			{
				printf("can not find string\n");
				return 0;
			}
			std::string value = temp_str.substr(pos+1);
			cout << value << endl;
		}
	}
	
	return 0;
}