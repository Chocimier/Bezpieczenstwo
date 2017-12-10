#include <string>
#include <random>
#include <fstream>
#include <iostream>

#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QEventLoop>
#include <QtCore/QList>
#include <QtCore/QString>

#include "bserver.h"
#include "Server.h"

#include <libblind.h>

static const std::string SETUP_MODE("setup");
static const std::string SIGN_SERVICE_MODE("signservice");

static std::random_device rd;
static std::mt19937_64 re(rd());
static std::uniform_int_distribution<size_t> unif_int;

static struct {
	std::string mode;
	int key_length = 2048;
	std::string private_key = "prywatny.txt";
	std::string public_key = "publiczny.txt";
	std::string hash_file = "skrót.txt";
	Key::Mode private_key_mode = Key::Mode::Private;
	int password_length = 20;
	int port = 3333;
} program_options;

void main_setup()
{
	Key key = generate_key(program_options.key_length);
	std::ofstream priv(program_options.private_key);
	key.write(priv, program_options.private_key_mode);
	std::ofstream publ(program_options.public_key);
	key.write(publ, Key::Mode::Public);
	std::string password = generate_password(program_options.password_length);
	std::cout << password << std::endl;
	std::ofstream pass(program_options.hash_file);
	pass << hash_func(password) << std::endl;
}

std::pair<bool, Bigint> sign(const Bigint &number)
{
	std::ifstream key_file(program_options.private_key);
	Key key = Key::read(key_file);
	if (!coprime(number, key.n))
	{
		return {false, 0};
	}
	return {true, modulo_power(number, key.d, key.n)};
}

bool password_matches(const std::string &password)
{
	std::string hash;
	std::ifstream(program_options.hash_file) >> hash;
	return hash_func(password) == hash;
}

void main_sign_service()
{
	Server *tcpServer = new Server(QCoreApplication::instance());
	if (!tcpServer->listen({QHostAddress::LocalHost}, static_cast<quint16>(program_options.port)))
	{
		std::cerr << "Słuchaj, dzieweczko! - Ona nie słucha" << std::endl;
		return;
	}
	QEventLoop().exec();
}

int main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);
	QCommandLineParser parser;
	parser.setApplicationDescription("Serwer ślepych podpisów");
	parser.addHelpOption();
	parser.addOptions({
		{{"m", "mode"}, QString::fromStdString("tryb pracy: " + SETUP_MODE + " lub " + SIGN_SERVICE_MODE), "tryb"},
		{{"l", "key-length"}, "długość klucza w bitach", "długość"},
		{{"d", "private-key"},
			"w trybie setup: plik, do którego zostanie zapisany klucz prywatny\n"
				"w trybie signservice: plik z kluczem prywatnym do wczytania",
			"ścieżka"
		},
		{{"e", "public-key"}, "plik, do którego zostanie zapisany klucz publiczny", "ścieżka"},
		{{"a", "password-hash-file"},
			"w trybie setup: plik, do którego zostanie zapisany skrót hasła\n"
				"w trybie signservice: plik ze skrótem hasła do wczytania",
			"ścieżka"
		},
		{"primes", "zapisuje do pliku z kluczem prywatnym również liczby pierwsze"},
		{"password-length", "liczba znaków hasła", "długość"},
		{{"p", "port"}, "port, na którym serwer nasłuchuje wiadmości do podpisania", "port"},
		//{{"", ""}, ""},
	});
	parser.process(app);

	if (parser.isSet("mode")) {program_options.mode = parser.value("mode").toStdString();}
	if (parser.isSet("key-length")) {program_options.key_length = parser.value("key-length").toInt();}
	if (parser.isSet("private-key")) {program_options.private_key = parser.value("private-key").toStdString();}
	if (parser.isSet("public-key")) {program_options.public_key = parser.value("public-key").toStdString();}
	if (parser.isSet("password-hash-file")) {program_options.hash_file = parser.value("password-hash-file").toStdString();}
	if (parser.isSet("primes")) {program_options.private_key_mode = Key::Mode::PrivateWithPrimes;}
	if (parser.isSet("password-length")) {program_options.password_length = parser.value("password-length").toInt();}
	if (parser.isSet("port")) {program_options.port = parser.value("port").toInt();}

	if (program_options.mode == SETUP_MODE)
	{
		main_setup();
	}
	else if (program_options.mode == SIGN_SERVICE_MODE)
	{
		main_sign_service();
	}
	else
	{
		parser.showHelp();
	}
}
