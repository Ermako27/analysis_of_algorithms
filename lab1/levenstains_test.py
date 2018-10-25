from random import choice
from time import time, clock
from main import levenshtain, recursive_levenshtain, damerau_levenshtain
import pandas as pd
import numpy as np


def word_generate(lenght):
    letters = 'qwertyuiopasdfghjklzxcvbnm'

    res = ''
    for i in range(lenght):
        res += choice(letters)
    return res

print(word_generate(5))

def test():
    l = 100
    for i in range(10):
        word1 = word_generate(l+i*100)
        word2 = word_generate(l+i*100)

        levenstain_times = []
        damerau_levenshtain_times = []
        for i in range(100):

            start = clock()
            levenshtain(word1,word2)
            end = clock()
            r = end - start
            levenstain_times.append(r)

            start = clock()
            damerau_levenshtain(word1,word2)
            end = clock()
            r = end - start
            damerau_levenshtain_times.append(r)
        levenshtain_res.append(np.mean(levenstain_times))
        damerau_levenshtain_res = []
            




test()