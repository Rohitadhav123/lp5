from multiprocessing import Pool
import time

def find_min(arr):
    return min(arr)

def find_max(arr):
    return max(arr)

def find_sum(arr):
    return sum(arr)

def find_avg(arr):
    return sum(arr) / len(arr)

if __name__ == "__main__":

    arr = list(map(int,input("Enter the numbers in the array - ").split()))
    print("Array:", arr)

    #Sequential Operations
    start = time.time()
    minimum = find_min(arr)
    maximum = find_max(arr)
    total = find_sum(arr)
    average = find_avg(arr)

    print("sequential results ")

    print("Min:", minimum)

    print("Max:", maximum)

    print("Sum:", total)

    print("Average:", average)

    print("Time:", time.time() - start)

    #parallel Operations

    start = time.time()

    with Pool() as pool:

        minimum = pool.apply(find_min,(arr,))
        maximum = pool.apply(find_max,(arr,))
        total = pool.apply(find_sum,(arr,))
        average = pool.apply(find_avg,(arr,))

    print("\nParallel Results")

    print("Min:", minimum)

    print("Max:", maximum)

    print("Sum:", total)

    print("Average:", average)

    print("Time:", time.time() - start)