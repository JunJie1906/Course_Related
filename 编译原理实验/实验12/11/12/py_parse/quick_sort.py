def quick_sort(array, left, right){
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
    quick_sort(array, low, left - 1)
    quick_sort(array, left + 1, high)
}

a1=[4123,2,1,123,20,124,4,235,2,534,56,3,452,16,7,4,6,4,6,456,7]

quick_sort(a1,0,len(a1)-1)

print(a1)





