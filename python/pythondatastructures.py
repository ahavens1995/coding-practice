#https://medium.com/geekculture/microsoft-software-engineer-interview-handbook-2023-80df999d286f
#main python file

#fancy functions here


#main code here
#print("Hello World");

#Data Structures — Practice common data structures like 
#Array 

def funcForArrays (arrayList):
    for x in arrayList:
        print(x, "\n")



#String 
#HashTable 
#Tree 
#LinkedList 
#Stack 
#Queue
#Graph

#Algorithm — Practice 
#recursion
#breadth-first search
#depth-first search
#divide and conquer
#sorting
#binary tree traversal algorithms


#Computer Science Basics — Go over CS basics related to 
#OS 
#Networks
#DBMS

#Sorting Algorithsm
def bubbleSort (arrayList):
    arrayLength = len(arrayList)
    for i in range(arrayLength):
        swapped = False

        #IT'S THIS WAY BECAUSE WE MOVE IT BACKWARDS!!!
        for j in range(0, arrayLength-i-1):

            if arrayList[j] > arrayList[j+1]:
                arrayList[j], arrayList[j+1] = arrayList[j+1], arrayList[j]
                swapped = True

        if (swapped == False):
            break

def insertionSort(arrayList):
    for i in range(1, len(arrayList)):

        key = arrayList[i]

        j = i-1
        #take the key value and compare it to the 
        while j >= 0 and key < arrayList[j]:
            arrayList[j + 1] = arrayList[j]
            j -= 1
        arrayList[j + 1] = key

def selectionSort(arrayList):

    arrayLength = len(arrayList)
    for i in range(arrayLength):
        
        min_index = i

        for j in range(i+1, arrayLength):
            if arrayList[min_index] > arrayList[j]:
                min_index = j
        
        arrayList[i], arrayList[min_index] = arrayList[min_index], arrayList[i]


### MAIN ###
if __name__ == "__main__":
    sushi = ["salmon", "tuna", "scallop", "crab"]
    numSushis = len(sushi)
    funcForArrays(sushi)

    numArray = [64, 34, 25, 12, 22, 11, 2]
    bubbleSort(numArray)
    print("Sorted Array with Bubble Sort:")
    for i in range(len(numArray)):
        print("%d" % numArray[i], end = " ")
    print("\n")
    
    numArray = [64, 34, 25, 12, 22, 11, 2]
    insertionSort(numArray)
    print("Sorted Array with Insertion Sort:")
    for i in range(len(numArray)):
        print("%d" % numArray[i], end = " ")
    print("\n")

    numArray = [64, 34, 25, 12, 22, 11, 2]
    selectionSort(numArray)
    print("Sorted Array with Selection Sort:")
    for i in range(len(numArray)):
        print("%d" % numArray[i], end = " ")
    print("\n")