#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "utils.h"

#define NUM_ITERATIONS 5
#define TABLE_SIZE ( 1 << 3 )

unsigned long fibonacci_recursive( unsigned long num ) {
   if ( num < 2 ) {
      return 1;
   } else {
      return fibonacci_recursive( num - 1 ) + fibonacci_recursive( num - 2 );
   }
}

unsigned long fibonacci_memoized( unsigned long* table, unsigned long num ) {
   unsigned long result;
   if ( num  < 2 ) {
      return 1;
   } else {
      if ( 0 != table[ num ] ) {
         return table[ num ];
      } else {
         result = fibonacci_memoized( table, ( num - 1 ) ) +
            fibonacci_memoized( table, ( num - 2 ) );
         table[ num ] = result;
         return result;
      } // end of else !lsearch
   } // end of else num >= 2
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

   if ( argc == 2 ) {
      num = strtol( argv[1], &endptr, 10 );
   } else {
      usage( argv[0] );
      return 1;
   }
   
   unsigned long* table = NULL;
   table = ( unsigned long* )calloc( num, sizeof( unsigned long ) );
   if ( !table ) {
      printf( "ERROR: Calloc failed for table with %ld items.\n", num );
      return -1;
   }

   Time_Point start_point;
   Duration duration;
   // Recursive version
   start_point = Steady_Clock::now();
   for( unsigned long iteration = 0; iteration < num; iteration++ ) {
  
      result = fibonacci_recursive( iteration );
      table[ iteration ] = result;
   
   }
   duration = Steady_Clock::now() - start_point;
   printf( "Fibonacci_recursive( %lu ) is %lu\n", num, result );
   printf( "Calculation of %ld iterations took %10.9f milliseconds.\n", num, duration.count() );

   // Memoized version
   start_point = Steady_Clock::now();
   for( unsigned long iteration = 0; iteration < num; iteration++ ) {
      result = fibonacci_memoized( table, iteration );
   }
   duration = Steady_Clock::now() - start_point;
   printf( "Fibonacci_memoized( %lu ) is %lu\n", num, result );
   printf( "Calculation of %ld iterations took %10.9f milliseconds.\n", num, duration.count() );
   
   return 0;
}
