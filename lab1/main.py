def print_matrix(m):
    for row in m:
        for elem in row:
            print('[',elem,']', end=' ')
        print()

def levenshtain(a, b):
    a = a.lower()
    b = b.lower()
    n, m = len(a), len(b)

    current_row = range(n+1)
    for i in range(1, m+1):
        previous_row, current_row = current_row, [i]+[0]*n
        for j in range(1,n+1):
            add, delete, change = previous_row[j]+1, current_row[j-1]+1, previous_row[j-1]
            if a[j-1] != b[i-1]:
                change += 1
            current_row[j] = min(add, delete, change)


    return current_row[n]


def damerau_levenshtain(a, b):
    a = a.lower()
    b = b.lower()
    n, m = len(a), len(b)

    current_row = range(n+1)
    previous_row = current_row
    for i in range(1, m+1):
        prev_previous_row, previous_row, current_row = previous_row, current_row, [i]+[0]*n
        for j in range(1,n+1):
            
            add, delete, change = previous_row[j]+1, current_row[j-1]+1, previous_row[j-1]
            if a[j-1] != b[i-1]:
                change += 1
            current_row[j] = min(add, delete, change)

            if ((i>1) and (j>1) and (a[j-1] == b[i-2]) and (a[j-2] == b[i-1])):
                current_row[j] = min(current_row[j], prev_previous_row[j-2] + change)
    return current_row[n]

def recursive_levenshtain(s1, s2):
    s1 = s1.lower()
    s2 = s2.lower()

    lenS1 = len(s1)
    lenS2 = len(s2)

    if (s1 == 0 and s2 == 0):
        return -1
    if (lenS1 == 0):
        return lenS2
    if (lenS2 == 0):
        return lenS1

    matr = [[0 for j in range(lenS2)] for i in range(lenS1)]
    
    for i in range(lenS1):
        matr[i][0] = i
    for i in range(lenS2):
        matr[0][i] = i


    if s1[-1] == s2[-1]:
        cost = 0
    else:
        cost = 1
    return min(recursive_levenshtain(s1[:lenS1-1],s2)+1,
        recursive_levenshtain(s1, s2[:lenS2-1])+1,
        recursive_levenshtain(s1[:lenS1-1], s2[:lenS2-1])+cost)


def panda(s1, s2):
    l1 = len(s1)
    l2 = len(s2)
    if l1 == 1 and l2 == 1:  # if s1 and s2 is symbols
        if s1 == s2:  # and they match
            return 0
        else:
            return 1
    else:
        if (l1 > l2 == 1) or (l2 > l1 == 1):  # but if one of str is not a symbols
            return abs(l1 - l2) + 1 # return distance for N inserts + penalty

    t = 0
    if s1[-1] != s2[-1]:  # if the last symbols of strings aren't match
        t = 1

    return min(panda(s1[:l1 - 1], s2) + 1,
               panda(s1, s2[:l2 - 1]) + 1,
               panda(s1[:l1 - 1], s2[:l2 - 1]) + t)



def main():
    s1 = 'мгу'
    s2 = 'мгту'

    res2 = levenshtain(s1,s2)
    res3 = damerau_levenshtain(s1,s2)
    res4 = recursive_levenshtain(s1,s2)
    res5 = panda(s1,s2)

    print(res2 ,res3, res4, res5)

if __name__ == '__main__':
    main()
