#include <string>
#include <random>
#include <fstream>

#include <QtCore/QCryptographicHash>

#include "../include/libblind.h"

static std::random_device rd;
static std::mt19937_64 re(rd());
static std::uniform_int_distribution<size_t> unif_int;

Key Key::read(std::istream &istream)
{
	Key key;
	std::string header;
	std::getline(istream, header);
	if (header == "klucz publiczny")
	{
		istream >> std::hex >> key.e;
		istream >> key.n;
	}
	else if (header == "klucz prywatny")
	{
		istream >> std::hex >> key.d;
		istream >> key.n;
	}
	else if (header == "klucz prywatny z liczbami pierwszymi")
	{
		istream >> std::hex >> key.d;
		istream >> key.n;
		istream >> std::dec >> key.p;
		istream >> key.q;
	}
	return key;
}

void Key::write(std::ostream &ostream, Key::Mode mode) const
{
	switch (mode)
	{
		break; case Mode::Public:
			ostream << "klucz publiczny" << std::endl;
			ostream << std::hex << e << std::endl;
			ostream << n << std::endl;
		break; case Mode::Private:
			ostream << "klucz prywatny" << std::endl;
			ostream << std::hex << d << std::endl;
			ostream << n << std::endl;
		break; case Mode::PrivateWithPrimes:
			ostream << "klucz prywatny z liczbami pierwszymi" << std::endl;
			ostream << std::hex << d << std::endl;
			ostream << n << std::endl;
			ostream << std::dec << p << std::endl;
			ostream << q << std::endl;
		break; default:
		break;
	}
}

bool coprime(const Bigint &a, const Bigint &b)
{
	return gcd(a, b) == 1;
}

Bigint gcd(Bigint a, Bigint b)
{
	Bigint t;
	while (b != 0)
	{
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}

Key generate_key(const int &length)
{
	Key key;
	//TODO: make them different length
	key.p = generate_prime(length / 2);
	key.q = generate_prime(length / 2);
	//TODO: check n's length
	key.n = key.p*key.q;
	key.e = (1 << 16) + 1;
	Bigint phi = (key.p-1)*(key.q-1);
	key.d = modulo_inverse(key.e, phi);
	return key;
}

std::string generate_password(int length)
{
	std::string password;
	for (int i = 0; i < length; ++i)
	{
		password.push_back(static_cast<char>(unif_int(re, rand_range('!', '~'))));
	}
	return password;
}

Bigint generate_prime(const int &length)
{
	Bigint random;
	int i = 0;
	do
	{
		nextrandom:
		random = boost::multiprecision::pow(Bigint(2), static_cast<unsigned>(length-1));
		random += random_bigint(0, boost::multiprecision::pow(Bigint(2), static_cast<unsigned>(length-2)))*2;
		random += 1;
		for (int j: {3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,67,71,73,79,83,89,97})
		{
			if (random % j == 0)
			{
				goto nextrandom;
			}
		}
	} while (!miller_rabin_test(random, 40));
	return random;
}

std::string hash_func(const std::string &string)
{
	QCryptographicHash hasher(QCryptographicHash::Sha3_512);
	hasher.addData(string.data(), static_cast<int>(string.size()));
	return hasher.result().toHex().toStdString();
}

bool miller_rabin_test(const Bigint &candidate, const Bigint &cycles)
{
	Bigint d = candidate - 1;
	Bigint s = 0;
	Bigint a;
	Bigint x;
	while ((d & 1) == 0)
	{
		++s;
		d /= 2;
	}
	for (Bigint i = 0; i < cycles; ++i)
	{
		a = random_bigint(2, candidate-2);
		x = modulo_power(a, d, candidate);
		if (x == 1 || x == candidate-1)
		{
			continue;
		}
		for (Bigint j=1; j < s && x != candidate-1; ++j)
		{
			x = modulo_power(x, 2, candidate);
			if (x == 1)
			{
				return false;
			}
		}
		if (x != candidate-1)
		{
			return false;
		}
	}
	return true;
}

Bigint modulo_inverse(const Bigint &inverse_of, const Bigint &modulus)
{
	Bigint u = 1;
	Bigint w = inverse_of;
	Bigint x = 0;
	Bigint z = modulus;
	Bigint q;
	while (w != 0)
	{
		if (w < z)
		{
			u.swap(x);
			w.swap(z);
		}
		q = w / z;
		u -= q*x;
		w -= q*z;
	}
	if (x < 0)
	{
		x += modulus;
	}
	return x;
}

Bigint modulo_power(const Bigint &base, const Bigint &exponent, const Bigint &modulus)
{
	return powm(base, exponent, modulus);
}

bool naive_primality_test(const Bigint &number)
{
	for (Bigint i = 2; i*i <= number; ++i)
	{
		if ((number % i) == 0)
		{
			return false;
		}
	}
	return true;
}

std::uniform_int_distribution<size_t>::param_type rand_range(size_t a, size_t b)
{
	return std::uniform_int_distribution<size_t>::param_type(a, b);
}

Bigint random_bigint(const Bigint &min, const Bigint &max)
{
	//TODO: just use templates
	Bigint random;
	Bigint range = max - min + 1;
	Bigint length = 0;
	while (range > 0)
	{
		++length;
		range /= 2;
	}
	range = max - min;
	do
	{
		random = 0;
		for (Bigint i = 0; i < length; ++i)
		{
			random *= Bigint(2);
			if (unif_int(re, rand_range(0, 1)))
			{
				random += 1;
			}
		}
	} while (random > range);
	return random + min;
}
