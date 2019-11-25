def quick_sort(array, left, right,i){
    print(array, left, right)
    if(left >= right){

        return

    }
    low = left
    high = right
    key = array[low]
    while(left < right){
        while(left < right and array[right] > key){
            right -= 1
        }
        array[left] = array[right]
        while(left < right and array[left] <= key){
            left += 1
        }
        array[right] = array[left]
    }
    array[right] = key
    print(i,low, left - 1)
    print(0)
    quick_sort(array, low, left - 1,i+1)
    print(i,low, left - 1)
    print(i,left + 1, high)
    print(0)
    quick_sort(array, left + 1, high,i+1)
}

a=[122,133,1,2,999,0,99]

quick_sort(a,0,len(a)-1,0)

print(a)

