#include <stdio.h>
#include <pthread.h> 

#define MAX 1000

int input[MAX];
int INPUTSIZE;
int output[MAX];

void insertionSort(int array[],int start_idx , int end_idx){
    int i = start_idx;

    while(i <= end_idx){
        int key = array[i];
        int pos = i;
        while(pos > 0 && key < array[pos - 1]){
            array[pos] = array[pos - 1];
            pos -= 1;
        }
        array[pos] = key;
        i += 1;
    }
}

void *leftSort(void *args){
    int mid = (int)(INPUTSIZE / 2);
    insertionSort(input,0,mid);
    return NULL;

}

void *rightSort(void *args){
    int mid = (int)(INPUTSIZE / 2);
    insertionSort(input,mid + 1,INPUTSIZE - 1);

    return NULL;
}

void *merge(void *args){
    int mid = (int)(INPUTSIZE / 2); 
    int l_ptr = 0;
    int r_ptr = mid + 1;

    int ctr = 0;
    while(l_ptr <= mid && r_ptr < INPUTSIZE){
        if(input[l_ptr] <= input[r_ptr]){
            output[ctr] = input[l_ptr];
            l_ptr += 1;
        }
        else{
            output[ctr] = input[r_ptr];
            r_ptr += 1;
        }
        ctr += 1;
    }
    while(l_ptr <= mid){
        output[ctr] = input[l_ptr];
        l_ptr += 1;
        ctr += 1;
    }
    while(r_ptr < INPUTSIZE){
        output[ctr] = input[r_ptr];
        r_ptr += 1;
        ctr += 1;
    }
}

void get_input(){
    int count = 0;
    
    do{
        scanf("%d",&input[count++]);
    }while(getchar() != '\n');

    INPUTSIZE = count;
}

void print_output(){
    for(int i = 0; i < INPUTSIZE;i++)
        printf("%d ",output[i]);
}

int main(){
    get_input();

    pthread_t thread1;
    pthread_t thread2;
    pthread_t merge_thread;

    
    pthread_create(&thread1,NULL,leftSort,NULL);
    pthread_create(&thread2,NULL,rightSort,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    pthread_create(&merge_thread,NULL,merge,NULL);
    pthread_join(merge_thread,NULL);

    print_output();
    return 0;
}