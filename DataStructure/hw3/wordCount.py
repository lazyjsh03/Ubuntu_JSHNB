import sys
from collections import Counter
import operator

WORD_COUNT = 10
DIC_WORD = 0
DIC_FREQ = 1
TUP_FREQ = 0
TUP_WORD = 1

if len(sys.argv) != 3:
    print("사용법: python3 wordCount.py 탐색지정단어 탐색지정빈도\n")
    sys.exit(1)

file_name = "./tom-word-list.txt"
search_word = sys.argv[1]
search_freq = int(sys.argv[2])

f = open(file_name, encoding="utf-8")
count = Counter(f.read().split())
dict_word_freq = dict(count)

print("[P1] 입력 단어 내역:")
print("입력 단어 총 갯수= ", sum(dict_word_freq.values()), end=", ")
print("고유 단어 총 갯수= ", len(dict_word_freq))

print("\n[P2] 탐색지정 단어와 출현빈도:")
print("오름차순 정렬된 단어 기준 상하위 10개 단어와 출현빈도:")
list_word_freq = sorted(dict_word_freq.items(),
        key = operator.itemgetter(DIC_WORD))

for i in range(WORD_COUNT):
    print(list_word_freq[i])
print(".............");
for i in range(WORD_COUNT):
    print(list_word_freq[i - WORD_COUNT])

if dict_word_freq.get(search_word) == None:
    print("\n탐색지정단어(%s) 없음" % search_word)
else:
    print("\n탐색지정단어('%s', %d)" % (search_word,
            dict_word_freq.get(search_word)))

print("\n[P3] 탐색지정빈도와 단어:")
print("출현빈도 기준 내림차순 정렬된 상하위 10개 출현빈도와 단어:")
tuple_freq_word = {(v, k) for k, v in dict_word_freq.items()}
tuple_freq_word = sorted(tuple_freq_word,
        key = operator.itemgetter(DIC_WORD), reverse = True)

for i in range(WORD_COUNT):
    print(tuple_freq_word[i])
print("...............");
for i in range(WORD_COUNT):
    print(tuple_freq_word[i - WORD_COUNT])

if search_freq <= 0:
    print("탐색지정빈도(%d) 입력 오류" % search_freq)
    sys.exit(2)
else:
    print("\n탐색지정빈도(%d)\n" % search_freq)
    found = False
    for index in range(len(tuple_freq_word)):
        if search_freq == tuple_freq_word[index][TUP_FREQ]:
            found = True
            print("(%d, '%s')" % (tuple_freq_word[index][TUP_FREQ],
                    tuple_freq_word[index][TUP_WORD]))
    if found == False:
        print(" 해당 단어 없음")