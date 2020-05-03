def gen_9_numbers(s):
    return str(abs(hash(s)))[:9]


print(gen_9_numbers('123'))