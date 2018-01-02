#include <string>
#include <random>
#include <fstream>
#include <iostream>

#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QString>
#include <QtNetwork/QTcpSocket>

#include <libblind.h>

static std::random_device rd;
static std::mt19937_64 re(rd());
static std::uniform_int_distribution<size_t> unif_int;

static struct {
	std::string public_key = "publiczny.txt";
	std::string domain = "localhost";
	int port = 3333;
} program_options;

QString blockingReadLine(QTcpSocket &socket);

QString blockingReadLine(QTcpSocket &socket)
{
	while (!socket.canReadLine())
	{
		socket.waitForReadyRead(2000);
	}
	QString line = socket.readLine();
	line.chop(1);
	if (line.right(1) == "\r")
	{
		line.chop(1);
	}
	return line;
}

int main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);
	QCommandLineParser parser;
	parser.setApplicationDescription("Klient usługi ślepych podpisów");
	parser.addHelpOption();
	parser.addOptions({
		{{"e", "public-key"}, "plik z kluczem publicznym serwera", "ścieżka"},
		{{"d", "domain"}, "adres, pod którym serwer nasłuchuje wiadmości do podpisania", "domena"},
		{{"p", "port"}, "port, na którym serwer nasłuchuje wiadmości do podpisania", "port"},
		//{{"", ""}, ""},
	});
	parser.process(app);
	if (parser.isSet("public-key")) {program_options.public_key = parser.value("public-key").toStdString();}
	if (parser.isSet("domain")) {program_options.domain = parser.value("domain").toStdString();}
	if (parser.isSet("port")) {program_options.port = parser.value("port").toInt();}
	std::ifstream key_file(program_options.public_key);
	Key key = Key::read(key_file);
	QTcpSocket socket;
	socket.connectToHost(QString::fromStdString(program_options.domain), static_cast<quint16>(program_options.port), QIODevice::ReadWrite);
	std::string password;
	std::cout << "Podaj hasło: " << std::flush;
	std::getline(std::cin, password);
	socket.write(QString::fromStdString(password + "\n").toUtf8());
	QString qline = blockingReadLine(socket);
	if (qline.startsWith("ERR "))
	{
		std::cout << qline.mid(4).toStdString() << std::endl;
		return 1;
	}
	do
	{
		std::string line;
		Bigint last = key.n-1;
		std::cout << "Podaj liczbę do podpisania: " << std::flush;
		std::getline(std::cin, line);
		if (line.empty())
		{
			continue;
		}
		Bigint m;
		std::istringstream(line) >> m;
		Bigint r = random_bigint(1, key.n-1);
		Bigint m1 = (m * modulo_power(r, key.e, key.n) % key.n);
		socket.write(QString::fromStdString(m1.str() + "\n").toUtf8());
		qline = blockingReadLine(socket);
		if (!qline.startsWith("ERR "))
		{
			Bigint blind_sign;
			std::istringstream(qline.toStdString()) >> blind_sign;
			Bigint signature = modulo_inverse(r, key.n) * blind_sign % key.n;
			std::cout << m << std::endl;
			std::cout << signature << std::endl;
		}
		else
		{
			std::cout << qline.mid(4).toStdString() << std::endl;
		}
	} while (std::cin.good());
	socket.disconnectFromHost();
}
