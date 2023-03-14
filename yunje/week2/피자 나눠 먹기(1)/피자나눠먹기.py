def solution(n):
    answer = n // 7
    if n % 7 != 0:
        answer += 1
    return answer


"""
def solution(n):
    return (n - 1) // 7 + 1
"""
