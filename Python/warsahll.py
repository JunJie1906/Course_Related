n = int(input('please input n: '))



lst = []



def Read(n):

    for i in range(n):

        

        crt = []



        for j in range(n):

            crt.append(int(input()))

          

        lst.append(crt)





def Print():

    for i in range(len(lst)):

        for j in range(len(lst[i])):

            print(lst[i][j],end = ' ')

        print()



def trans():

    j = 0

    while j<n:



        for i in range(n):

            if A[i][j] == 1:

                for k in range(n):

                    A[i][k] = A[i][k]+A[j][k]

                    if A[i][k]>1:

                        A[i][k] = 1

        j+=1



Read(n)

Print()



A = lst

trans()





Print()
