#!/usr/bin/env python

# Bezpieczeństwo komputerowe
# Lista 2 zadanie 1
# Piotr Wójcik

import sys
f = {'N': 124, 'a': 8478, ' ': 16587, 's': 4066, 'z': 6212, 'e': 8507, 'r': 3408, 'o': 6924, 'k': 2699, 'w': 3250, 'n': 4381, 'i': 7449, 'c': 3974, 'l': 4128, 't': 2949, 'p': 2232, 'u': 1774, 'y': 3225, 'm': 3033, 'h': 1007, ',': 2094, 'j': 1952, 'd': 2749, '.': 717, 'W': 137, 'b': 1453, 'g': 1283, 'f': 132, ';': 85, 'P': 145, 'Z': 68, 'I': 34, 'T': 88, 'U': 29, 'S': 105, 'O': 84, 'R': 33, 'B': 86, 'C': 90, '—': 450, 'A': 97, '!': 349, 'G': 51, ':': 113, '?': 182, 'K': 93, '…': 355, 'M': 71, '*': 176, '(': 9, ')': 9, 'J': 135, 'D': 51, 'E': 4, 'Ś': 5, '»': 6, '«': 6, 'L': 17, '-': 184, 'H': 19, 'F': 4, 'Ż': 19, '„': 24, '”': 24, '8': 4, '1': 24, '2': 10, '6': 7, '5': 11, '3': 4, 'v': 4, 'Ź': 2, '4': 4, '0': 30, 'Ó': 1, 'é': 3, '7': 3, '9': 4, 'Ł': 1, "'": 1, 'q': 2}

def weight(pos, code):
    if chr(code) in f:
        return f[chr(code)]*(1000 if pos == 0 and 'A' <= chr(code) <= 'Z' else 1)
    elif ord(' ') <= code <= ord('~'):
        return 1
    else:
        return -1000000

text = sys.stdin.read()
cryptograms = text.split('\n\n')
cryptograms = [i.split() for i in cryptograms]
cryptograms = [[int(j, 2) for j in i] for i in cryptograms]

key = []
for i in range(len(max(cryptograms, key=len))):
    best = 0
    best_weight = 0
    for k in range(256):
        weight_sum = 0
        for c in cryptograms:
            if len(c) > i:
             weight_sum += weight(i, c[i] ^ k)
        if weight_sum > best_weight:
            best_weight = weight_sum
            best = k
    key.append(best)

for c in cryptograms:
    for i in range(len(c)):
        print(chr(c[i] ^ key[i]), end='')
    print()
    print()

