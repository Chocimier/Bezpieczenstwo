#include <string>
#include <fstream>

#include <libblind.h>

int main()
{
	std::ifstream key_file("publiczny.txt");
	Key key = Key::read(key_file);
	do
	{
		std::string line;
		std::getline(std::cin, line);
		std::istringstream input(line);
		Bigint message;
		input >> message;
		std::getline(std::cin, line);
		if (line.empty())
		{
			break;
		}
		input = std::istringstream(line);
		Bigint sign;
		input >> sign;
		Bigint signed_message = modulo_power(sign, key.e, key.n);
		std::cout << std::boolalpha << (message == signed_message) << std::endl;
	} while (std::cin.good());
}
