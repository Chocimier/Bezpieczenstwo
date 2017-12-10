#include <string>
#include <random>
#include <fstream>

#include <libblind.h>

static const std::string SETUP_MODE("setup");
static const std::string SIGN_SERVICE_MODE("signservice");

static std::random_device rd;
static std::mt19937_64 re(rd());
static std::uniform_int_distribution<size_t> unif_int;

void usage()
{
	//TODO: fill
	std::cout << SETUP_MODE << std::endl;
	std::cout << SIGN_SERVICE_MODE << std::endl;
}

void main_setup()
{
	//TODO: parametrize files
	//TODO: parametrize length
	Key key = generate_key(300);
	std::ofstream priv("prywatny.txt");
	key.write(priv, Key::Mode::PrivateWithPrimes);
	std::ofstream publ("publiczny.txt");
	key.write(publ, Key::Mode::Public);
	// TODO: parametrize password length
	std::string password = generate_password();
	std::cout << password << std::endl;
	//TODO: use better hash
	std::ofstream pass("hasło.txt");
	pass << hash_func(password) << std::endl;
}

void main_sign_service()
{
	std::string hash;
	std::string password;
	//TODO: parametrize file
	std::ifstream hash_file("hasło.txt");
	//TODO: use network

	hash_file >> hash;

	std::getline(std::cin, password);
	if (hash_func(password) != hash)
	{
		return;
	}

	std::cerr << "Hasło jest poprawne" << std::endl;

	std::ifstream key_file("prywatny.txt");
	Key key = Key::read(key_file);

	do
	{
		std::string line;
		std::getline(std::cin, line);
		std::istringstream input(line);
		std::cerr << line << std::endl;
		Bigint x;
		input >> x;
		if (!coprime(x, key.n))
		{
			std::cout << x << " nie należy do Z_n" << std::endl;
			continue;
		}
		std::cout << modulo_power(x, key.d, key.n) << std::endl;
		std::cerr << modulo_power(x, key.d, key.n) << std::endl;
	} while (std::cin.good());
}

int main(int argc, char **argv)
{
	//TODO: params
	if (argc < 2)
	{
		usage();
		return 1;
	}

	if (SETUP_MODE == argv[1])
	{
		main_setup();
	}
	else if (SIGN_SERVICE_MODE == argv[1])
	{
		main_sign_service();
	}
	else
	{
		usage();
	}
}
