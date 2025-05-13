import random
import string
import time
import pandas as pd
from collections import defaultdict

def generate_key(length=15):
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

def generate_text(length, key):
    text = ''.join(random.choices(string.ascii_letters + string.digits + ' ', k=length))
    num_insertions = random.randint(1, 100)
    positions = random.sample(range(length), num_insertions)
    for pos in positions:
        text = text[:pos] + key + text[pos:]
    return text

def sequential_search(text, key):
    count = 0
    n = len(text)
    m = len(key)
    for i in range(n - m + 1):
        match = True
        for j in range(m):
            if text[i + j] != key[j]:
                match = False
                break
        if match:
            count += 1
    return count

class BoyerMoore:
    def __init__(self, pattern):
        self.pattern = pattern
        self.bad_char = self.bad_character_table(pattern)
        self.good_suffix = self.good_suffix_table(pattern)

    def bad_character_table(self, pattern):
        table = {}
        for i in range(len(pattern) - 1):
            table[pattern[i]] = len(pattern) - 1 - i
        return table

    def good_suffix_table(self, pattern):
        m = len(pattern)
        suffix_table = [0] * m
        last_prefix_pos = m
        for i in range(m - 1, -1, -1):
            if self.is_prefix(pattern, i + 1):
                last_prefix_pos = i + 1
            suffix_table[m - 1 - i] = last_prefix_pos - i

        prefix_table = [0] * m
        for i in range(m):
            prefix_table[i] = last_prefix_pos

        for i in range(m - 1):
            slen = self.suffix_length(pattern, i)
            prefix_table[slen] = m - 1 - i

        return prefix_table

    def is_prefix(self, pattern, p):
        m = len(pattern)
        for i in range(p):
            if pattern[i] != pattern[m - p + i]:
                return False
        return True

    def suffix_length(self, pattern, i):
        length = 0
        m = len(pattern)
        for j in range(i, -1, -1):
            if pattern[j] == pattern[m - 1 - i + j]:
                length += 1
            else:
                break
        return length

    def search(self, text):
        m, n = len(self.pattern), len(text)
        if m > n:
            return 0
        bad_char = self.bad_char
        good_suffix = self.good_suffix
        count = 0
        i = 0
        while i <= n - m:
            j = m - 1
            while j >= 0 and self.pattern[j] == text[i + j]:
                j -= 1
            if j < 0:
                count += 1
                i += good_suffix[0] if good_suffix[0] != 0 else 1
            else:
                char = text[i + j]
                bad_char_shift = bad_char.get(char, m) - (m - 1 - j) if char in bad_char else m
                good_suffix_shift = good_suffix[j + 1] if j + 1 < m else 1
                i += max(bad_char_shift, good_suffix_shift)
        return count


class KMP:
    def __init__(self, pattern):
        self.pattern = pattern
        self.lps = self.compute_lps(pattern)

    def compute_lps(self, pattern):
        m = len(pattern)
        lps = [0] * m
        length = 0
        i = 1
        while i < m:
            if pattern[i] == pattern[length]:
                length += 1
                lps[i] = length
                i += 1
            else:
                if length != 0:
                    length = lps[length - 1]
                else:
                    lps[i] = 0
                    i += 1
        return lps

    def search(self, text):
        m, n = len(self.pattern), len(text)
        lps = self.lps
        i = j = 0
        count = 0
        while i < n:
            if self.pattern[j] == text[i]:
                i += 1
                j += 1
            if j == m:
                count += 1
                j = lps[j - 1]
            elif i < n and self.pattern[j] != text[i]:
                if j != 0:
                    j = lps[j - 1]
                else:
                    i += 1
        return count

num_iterations = 10000
text_lengths = list(range(1000, 25001, 1000))
results = defaultdict(lambda: {'sequential': 0, 'boyer_moore': 0, 'kmp': 0})

for _ in range(num_iterations):
    key = generate_key()
    for length in text_lengths:
        text = generate_text(length, key)

        start = time.time()
        sequential_search(text, key)
        time_sequential = time.time() - start

        bm = BoyerMoore(key)
        start = time.time()
        bm.search(text)
        time_bm = time.time() - start

        kmp = KMP(key)
        start = time.time()
        kmp.search(text)
        time_kmp = time.time() - start

        results[length]['sequential'] += time_sequential
        results[length]['boyer_moore'] += time_bm
        results[length]['kmp'] += time_kmp

data = {
    "Длина строки": [],
    "Последовательный алгоритм": [],
    "Бойер-Мур": [],
    "Кнут-Моррис-Пратт": []
}

for length in text_lengths:
    data["Длина строки"].append(length)
    data["Последовательный алгоритм"].append(round(results[length]['sequential'] / num_iterations, 6))
    data["Бойер-Мур"].append(round(results[length]['boyer_moore'] / num_iterations, 6))
    data["Кнут-Моррис-Пратт"].append(round(results[length]['kmp'] / num_iterations, 6))

df = pd.DataFrame(data)
df.to_excel("search_results.xlsx", index=False, float_format="%.6f")

for length in text_lengths:
    print(f"Длина строки: {length}")
    print(f"  Последоватльный алгоритм: {results[length]['sequential'] / num_iterations:.6f} сек")
    print(f"  Бойер-Мур: {results[length]['boyer_moore'] / num_iterations:.6f} сек")
    print(f"  Кнут-Моррис-Пратт: {results[length]['kmp'] / num_iterations:.6f} сек")
    print("-")
