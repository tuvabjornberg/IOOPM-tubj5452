# include <stdio.h>
# include <stdlib.h>
# include <math.h>

int main(int argc, char *argv[]){
// not optimized
    //int input = atoi(argv[1]); 
    //int answer = 1; 
    //for (int i = 2; i <= input; i++) {
    //    for (int N = 2; N <= input; N++) {
    //        if (i * N == input) {
    //            answer = 0; 
    //            break; 
    //        }
    //    }
    // if (!answer) {
    //      break;     
    //}
    //}
    //if (answer) {
    //    printf("%d is a prime number", input); 
    //}
    //else {
    //    printf("%d is not a prime number", input); 
    //}

//optimized
    int input = atoi(argv[1]); 
    int answer = 1; 

    //float tmp = sqrt(input); 
    //int limit = floor(tmp) + 1; 

    for (int i = 2; i <= floor(sqrt(input)) + 1; i++) {
       if (input % i == 0) {
            answer = 0; 
            break; 
        }
    }
    if (answer) {
        printf("%d is a prime number", input); 
    }
    else {
        printf("%d is not a prime number", input); 
    }

}