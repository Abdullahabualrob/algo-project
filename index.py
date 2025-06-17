def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr


def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        left = merge_sort(arr[:mid])
        right = merge_sort(arr[mid:])

        merged = []
        i = j = 0

        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                merged.append(left[i])
                i += 1
            else:
                merged.append(right[j])
                j += 1

        merged.extend(left[i:])
        merged.extend(right[j:])
        return merged
    else:
        return arr


def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    else:
        pivot = arr[0]
        less = [x for x in arr[1:] if x < pivot]
        equal = [x for x in arr if x == pivot]
        greater = [x for x in arr[1:] if x > pivot]
        return quick_sort(less) + equal + quick_sort(greater)
import random

def generate_array(size, order='random'):
    arr = [random.randint(0, 10000) for _ in range(size)]
    if order == 'sorted':
        return sorted(arr)
    elif order == 'reversed':
        return sorted(arr, reverse=True)
    elif order == 'partial':
        half = size // 2
        return sorted(arr[:half]) + arr[half:]
    return arr
import time

def measure_time(sort_function, arr):
    start = time.time()
    sort_function(arr.copy())
    end = time.time()
    return (end - start) * 1000  # بالميلي ثانية
