from django.contrib.auth.hashers import Argon2PasswordHasher

class ConfiguredArgon2PasswordHasher(Argon2PasswordHasher):
    time_cost = 4
    memory_cost = 512
