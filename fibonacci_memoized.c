#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define NUM_ITERATIONS 5

typedef struct lookup_item_s {
   unsigned long num;
   unsigned long result;
} lookup_item_t;

unsigned long fibonacci_recursive( unsigned long num ) {
   if ( num < 2 ) {
      return 1;
   } else {
      return fibonacci_recursive( num - 1 ) + fibonacci_recursive( num - 2 );
   }
}

void usage( char* argv ) {
   printf( "Usage: %s <options>\n", argv );
   printf( "Options one of:\n" );
   printf( "%4s%56s\n",
      "<num>", "which Fibonacci number to output." );
}

// Need repeated calls to fibonacci for memoization to pay off
int main( int argc, char** argv ) {
   unsigned long num = 0;
   unsigned long result = 0;
   char* endptr = NULL;
   clock_t start_time = 0;
   clock_t end_time = 0;
   double cpu_time_duration = 0;
   double total_duration = 0;

   if ( argc == 2 ) {
      num = strtol( argv[1], &endptr, 10 );
   } else {
      usage( argv[0] );
      return 1;
   }
   
   lookup_item_t* table = NULL;
   table = ( lookup_item_t* )malloc( sizeof( lookup_item_t ) * num );
   if ( !table ) {
      printf( "ERROR: Malloc failed for table with %ld items.\n", num );
      return 1;
   }

   // Recursive version
   start_time = clock();
   for( unsigned long iteration = 0; iteration < num; iteration++ ) {
  
      result = fibonacci_recursive( iteration );

      table[ iteration ].num = iteration;
      table[ iteration ].result = result;
      printf( "Fibonacci( %lu ) is %lu\n", table[ iteration ].num, table[ iteration ].result );
   
   }
   end_time = clock();
   cpu_time_duration = ( double )( end_time - start_time ) / ( double )CLOCKS_PER_SEC;
   printf( "Calculation of %ld iterations took %10.9f seconds.\n", num, cpu_time_duration );

   // Memoized  version
   start_time = clock();
   for( unsigned long iteration = 0; iteration < num; iteration++ ) {
  
      //result = fibonacci_recursive( iteration );

      table[ iteration ].num = iteration;
      table[ iteration ].result = result;
      printf( "Fibonacci( %lu ) is %lu\n", table[ iteration ].num, table[ iteration ].result );
   
   }
   end_time = clock();
   cpu_time_duration = ( double )( end_time - start_time ) / ( double )CLOCKS_PER_SEC;
   printf( "Calculation of %ld iterations took %10.9f seconds.\n", num, cpu_time_duration );

   return 0;
}
