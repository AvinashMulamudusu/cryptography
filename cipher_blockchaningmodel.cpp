#include <stdio.h>
#include <string.h>

static void display(int intArray[], int length){
   int i=0;
   printf("Array : [");
   for(i = 0; i < length; i++) {
      printf(" %d ", intArray[i]);
   }
   printf(" ]\n ");   
}

int main() {
   int i = 0;
   int intArray[8];          
   for ( i = 0; i < 8; i++ ) {
      intArray[ i ] = 0; 
   }
   printf("Array with default data.");
   display(intArray,8);     
   for(i = 0; i < 8; i++) {
      printf("Adding %d at index %d\n",i,i);
      intArray[i] = i;
   }
   printf("\n");
   printf("Array after adding data. ");
   display(intArray,8);
   int index = 5;
   intArray[index] = 10;

   printf("Array after updating element at index %d.\n",index);
   display(intArray,8);
   printf("Data at index %d:%d\n" ,index,intArray[index]);
   int value = 4;
   for(i = 0; i < 8; i++) {
      if(intArray[i] == value ){
         printf("value %d Found at index %d \n", intArray[i],i);
         break;
      }
   }
   return 0;
}
