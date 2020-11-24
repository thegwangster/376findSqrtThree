/** By Gabriel Luo, March 29th 2019
 * For EECS376 Homework 10, University of Michigan.
 * The software is for demo purposes only, 
 * Thus makes no promise for commercial use. 
 * 
 * Usage note: run
 * g++ findSqrtThree.cpp -o approx -std=c++11 -O3
 * ./approx [n]
 * with [n] being the desired number of trials.
 */
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[])
{
    // seeded rand_engine, then model a uniform distribution.
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    static default_random_engine              rand_engine { seed };
    static uniform_real_distribution<double>  unif( (double)0.0, (double)1.0 );

    if ( argc != 2 ) {
        cout << "Usage: \ng++ findSqrtThree.cpp -o approx -std=c++11 -O3\n./approx [n]\n"
             << "Where [n] is the number of trials you determined from part (b).\n";
        exit(1);
    }

    size_t num_of_trials = atoi( argv[1] );
    size_t target_count = 0;

    for ( size_t i = 0; i < num_of_trials; ++i ) {
        double x_coor = unif( rand_engine );
        double y_coor = unif( rand_engine );

        // determine if the point falls in the triangle
        double x_sq = pow( x_coor, 2 );
        double rev_x_sq = pow( 1 - x_coor, 2 );
        double y_sq = pow( y_coor, 2 );

        if ( x_sq     >= 0.25 * ( y_sq + x_sq ) and
             rev_x_sq >= 0.25 * ( y_sq + rev_x_sq) )
            ++ target_count;
        
        // helpful message to remind you that program is running
        if ( i % (num_of_trials / 10) == 0 )
            cout << "Finished " << i / ( num_of_trials / 10 ) * 10 
                 << "% of iterations...\n";
    }
    cout << "=================================\n";
    cout << "Completed running " << num_of_trials << " iterations.\n";
    cout << "    Resulting p = " << setprecision(9);
    cout << (double)target_count / (double)num_of_trials << "\n";
    cout << "Don't forget to manipulate this result"
         << " and report the actual estimation of sqrt(3)\n\n"; 
    return 0;
}
