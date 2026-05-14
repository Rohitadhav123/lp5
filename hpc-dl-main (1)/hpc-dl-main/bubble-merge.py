from multiprocessing import Pool
import time


# Sequential Bubble Sort
def bubble_sort(arr):

    n = len(arr)

    for i in range(n):

        for j in range(n - 1):

            if arr[j] > arr[j + 1]:

                arr[j], arr[j + 1] = arr[j + 1], arr[j]

    return arr


# Function for parallel comparison
def compare(pair):

    a, b = pair

    return min(a, b), max(a, b)


# Parallel Bubble Sort
def parallel_bubble_sort(arr):

    n = len(arr)

    for i in range(n):

        pairs = []

        positions = []

        # Even phase
        start = i % 2

        for j in range(start, n - 1, 2):

            pairs.append((arr[j], arr[j + 1]))

            positions.append(j)

        with Pool() as pool:

            result = pool.map(compare, pairs)

        # Put sorted pairs back
        for k in range(len(result)):

            j = positions[k]

            arr[j], arr[j + 1] = result[k]

    return arr


# Merge function
def merge(left, right):

    result = []

    i = j = 0

    while i < len(left) and j < len(right):

        if left[i] < right[j]:

            result.append(left[i])

            i += 1

        else:

            result.append(right[j])

            j += 1

    result += left[i:]

    result += right[j:]

    return result


# Sequential Merge Sort
def merge_sort(arr):

    if len(arr) <= 1:

        return arr

    mid = len(arr) // 2

    left = merge_sort(arr[:mid])

    right = merge_sort(arr[mid:])

    return merge(left, right)


# Parallel Merge Sort
def parallel_merge_sort(arr):

    if len(arr) <= 1:

        return arr

    mid = len(arr) // 2

    with Pool(2) as pool:

        left, right = pool.map(
            merge_sort,
            [arr[:mid], arr[mid:]]
        )

    return merge(left, right)


# Main
if __name__ == "__main__":

    arr = list(map(
        int,
        input("Enter array elements: ").split()
    ))

    print("Original Array:", arr)

    start = time.time()

    print("Sequential Bubble Sort:",
          bubble_sort(arr.copy()))

    print("Time:",
          time.time() - start)

    start = time.time()

    print("Parallel Bubble Sort:",
          parallel_bubble_sort(arr.copy()))

    print("Time:",
          time.time() - start)

    start = time.time()

    print("Sequential Merge Sort:",
          merge_sort(arr.copy()))

    print("Time:",
          time.time() - start)

    start = time.time()

    print("Parallel Merge Sort:",
          parallel_merge_sort(arr.copy()))

    print("Time:",
          time.time() - start)