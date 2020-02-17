#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

const double eps = 0.0001;
int counter = 0;

//1-2 from 2 to 3
//1-3 from 0 to 1
//2-3 from 1 to 2

float f4(float x){
   return (sqrt(x));
}

float f5(float x){
   return (x * x);
}

float f6(float x){
   return (1 / x);
}

extern float f1(float x);
extern float f2(float x);
extern float f3(float x);

float intersection(float from , float to , float(*func1)(float) , float(*func2)(float)){
    float temp;
    counter = 0;
    while(to - from >= eps){
        counter++;
        temp = (to + from) / 2;
        if((func1(to) - func2(to)) * (func1(temp) - func2(temp)) < 0){
            from = temp;
        }else{
            to = temp;
        }
    }
    return ((to + from) / 2);
}

float zero(float i){
  return 0.0;
}

float squadintegral(float from , float to , float(*func1)(float) , float(*func2)(float)){
    float temp = 0;
    for(float i = from ; i < to ; temp += fabs(func1(i + eps/2) - func2(i + eps/2)) , i += eps);
    return (temp * eps);
}

//get opt c

int main(int argc , char **argv){
    //____________
    if(argc > 1){
      if((!strcmp(argv[1] , "-help")) || (!strcmp(argv[1] , "-?"))){
        printf("main -f1 - first function e^(-x)+3 and floating parm\nmain -f2 - second function 2*x-2 and floating parm\nmain -f3 - third function 1/x and floating parm\nmain -db - Debug Mode\n");
        return 0;
      }
      if(!strcmp(argv[1] , "-f1")){
        float tmp;
        printf("Input floating parm!\n");
        scanf("%f" , &tmp);
        printf("%f\n" , f1(tmp));
        return 0;
      }
      if(!strcmp(argv[1] , "-f2")){
        float tmp;
        printf("Input floating parm!\n");
        scanf("%f" , &tmp);
        printf("%f\n" , f2(tmp));
        return 0;
      }
      if(!strcmp(argv[1] , "-f3")){
        float tmp;
        printf("Input floating parm!\n");
        scanf("%f" , &tmp);
        printf("%f\n" , f3(tmp));
        return 0;
      }
      if(!strcmp(argv[1] , "-db")){
        printf("Debug Mode!\n");
        printf("f1 - first function e^(-x)+3 and floating parm\nf2 - second function 2*x-2 and floating parm\nf3 - third function 1/x and floating parm\nisec <f><f> - point of intersection functions input func number f1<1>, f2<2>, f3<3>\nsq - calc square under graphic, input function number and two point parm\nexit - stop debug\n");
        while(1){
          char parm[121];
          printf("Input parm of debug!\n");
          scanf("%s" , parm);
          if(!strcmp(parm , "f1")){
            float tmp;
            printf("Input floating parm!\n");
            scanf("%f" , &tmp);
            printf("%f\n" , f1(tmp));
            continue;
          }
          if(!strcmp(parm , "f2")){
            float tmp;
            printf("Input floating parm!\n");
            scanf("%f" , &tmp);
            printf("%f\n" , f2(tmp));
            continue;
          }
          if(!strcmp(parm , "f3")){
            float tmp;
            printf("Input floating parm!\n");
            scanf("%f" , &tmp);
            printf("%f\n" , f3(tmp));
            continue;
          }
          if(!strcmp(parm , "isec")){
            int n1 , n2;
            printf("Input number of function 1 and 2!\n");
            scanf("%d%d" , &n1 , &n2);
            if(n1 == 1 && n2 == 2){
              printf("Proint of intersection: %f\n" , intersection(2 , 3 , f1 , f2));
            }
            if(n1 == 1 && n2 == 3){
              printf("Proint of intersection: %f\n" , intersection(0 , 1 , f1 , f3));
            }
            if(n1 == 2 && n2 == 3){
              printf("Proint of intersection: %f\n" , intersection(1 , 2 , f2 , f3));
            }
            printf("Count of iterations: %d\n" , counter);
            continue;
          }
          if(!strcmp(parm , "sq")){
            int n1;
            float a , b;
            printf("Input number of function and two point!\n");
            scanf("%d%f%f" , &n1 , &a , &b);
            if(a > b){
              printf("Error! First parm should be >=\n");
              continue;
            }
            if(n1 == 1){
              printf("Square: %f\n" , squadintegral(a , b , f1 , zero));
            }
            if(n1 == 2){
              printf("Square: %f\n" , squadintegral(a , b , f2 , zero));
            }
            if(n1 == 3){
              if(a < 0){
                printf("Error! Undef func!\n");
                continue;
              }
              printf("Square: %f\n" , squadintegral(a , b , f3 , zero));
            }
            continue;
          }
          if(!strcmp(parm , "exit")){
            printf("Stop debug!\n");
            printf("Stop program...\n");
            return 0;
          }
        }
      }
    }
    //____________
    printf("%f\n" , intersection(0.5 , 2 , f5 , f4));
    printf("Square: %f\n" , squadintegral(0 , 1 , f4 , f5));
    //printf("%f %f\n" , intersection(0 , 1 , f1 , f3) , f1(intersection(0 , 1 , f1 , f3)));
    //printf("%f %f\n" , intersection(1 , 2 , f2 , f3) , f2(intersection(1 , 2 , f2 , f3)));
    float temp = squadintegral(intersection(0 , 1 , f1 , f3) , intersection(1 , 2 , f2 , f3) , f1 , f3);
    temp += squadintegral(intersection(1 , 2 , f2 , f3) , intersection(2 , 3 , f1 , f2) , f1 , f2);
    printf("%f\n" , temp);
    return 0;
}
