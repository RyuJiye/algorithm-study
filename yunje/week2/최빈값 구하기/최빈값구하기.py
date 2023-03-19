def solution(array):
    keys = set(array)
    dict = {}
    frequency = []
    for key in keys:
        dict[key] = array.count(key)
    for key in keys:
        if dict[key] == max(dict.values()):
            frequency.append(key)
    if len(frequency) > 1:
        answer = -1
    else:
        answer = frequency[0]
    return answer


"""
def solution(array):
    while len(array) != 0:
        for i, a in enumerate(set(array)):
            array.remove(a)
        if i == 0: return a
    return -1
"""
