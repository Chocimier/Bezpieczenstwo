#include <string>
#include <random>
#include <fstream>

#include <libblind.h>

static std::random_device rd;
static std::mt19937_64 re(rd());
static std::uniform_int_distribution<size_t> unif_int;

//TODO: use network
//TODO: parametrize files

int main()
{
	std::ifstream key_file("publiczny.txt");
	Key key = Key::read(key_file);
	std::ofstream server_in("server.in");
	std::ifstream server_out("server.out");
	std::string password;
	std::getline(std::cin, password);
	server_in << password << std::endl;
	do
	{
		std::string line;
		std::getline(std::cin, line);
		std::istringstream input(line);
		Bigint m;
		Bigint blind_sign;
		input >> m;
		Bigint r = random_bigint(1, key.n-1);
		server_in << (m * modulo_power(r, key.e, key.n) % key.n) << std::endl;
		server_out >> blind_sign;
		Bigint sign = modulo_inverse(r, key.n) * blind_sign % key.n;
		std::cout << m << std::endl;
		std::cout << sign << std::endl;
	} while (std::cin.good());
}
