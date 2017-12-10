#ifndef LIBBLIND_H
#define LIBBLIND_H

#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int Bigint;

class Key
{
public:
	enum class Mode : char
	{
		Public = 0,
		Private,
		PrivateWithPrimes,
	};

	Bigint n = 0;
	Bigint e = 0;
	Bigint d = 0;
	Bigint p = 0;
	Bigint q = 0;

	static Key read(std::istream &istream);
	void write(std::ostream &ostream, Mode mode) const;
};

bool coprime(const Bigint &a, const Bigint &b);
Bigint gcd(Bigint a, Bigint b);
Key generate_key(const int &lenght = 2048);
std::string generate_password();
Bigint generate_prime(const int &lenght);
std::string hash_func(const std::string &string);
bool miller_rabin_test(const Bigint &candidate, const Bigint &cycles);
Bigint modulo_inverse(const Bigint &inverse_of, const Bigint &modulus);
Bigint modulo_power(const Bigint &base, const Bigint &exponent, const Bigint &modulus);
bool naive_primality_test(const Bigint &number);
std::uniform_int_distribution<size_t>::param_type rand_range(size_t a, size_t b);
Bigint random_bigint(const Bigint &min, const Bigint &max);

#endif
