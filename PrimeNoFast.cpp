/*
#MAR
#MAKAUT
#Coding_solution
The sieve of Eratosthenes is one of the most efficient ways to find all primes smaller than but when the value of n is very large following is applied.
Segmented Sieve
The idea of segmented sieve is to divide the range [0..n-1] in different segments and compute primes in all segments one by one.
This algorithm first applies Simple Sieve to find primes smaller than or equal to √(n). 
Using Simple Sieve, we needed O(n) space which may not be feasible for large value of n.
So here we need the O(√n) space and we process smaller ranges at a time(locality of reference).
Disadvantages with Simple Sieve:
The Sieve of Eratosthenes is good effective algorithm, but on considering the situation when the value of n is large, the Simple Sieve faces following issues.
• An array of size Θ(n) may not fit in memory hence more memory is required
• The simple Sieve is not cache friendly even for slightly bigger n. The algorithm traverses the array without locality of reference 
Time Complexity: O (n*log(log(n))) 
Now the time complexity (or number of operations) by Segmented Sieve is same as Simple Sieve.
It has advantages for large ‘n’ as it has better locality of reference thus allowing better caching by the CPU and also requires less memory space.
*/

#include <bits/stdc++.h> 
    using namespace std; 
    void simpleSieve(int limit, vector<int> &prime) 
    {     bool mark[limit+1]; 
        memset(mark, true, sizeof(mark));   
        for (int p=2; p*p<limit; p++) 
        {   if (mark[p] == true) 
            { for (int i=p*2; i<limit; i+=p) 
                    mark[i] = false; 
            }}
        for (int p=2; p<limit; p++) 
        {   if (mark[p] == true) 
            {   prime.push_back(p); 
                cout << p << " "; 
            } } } 
     
    void segmentedSieve(int n) 
    {   int limit = floor(sqrt(n))+1; 
        vector<int> prime;  
        simpleSieve(limit, prime);
        int low = limit; 
        int high = 2*limit; 
        while (low < n) 
        { 
            if (high >= n)  
               high = n; 
            bool mark[limit+1]; 
            memset(mark, true, sizeof(mark)); 
            for (int i = 0; i < prime.size(); i++) 
            {
                int loLim = floor(low/prime[i]) * prime[i]; 
                if (loLim < low) 
                    loLim += prime[i]; 
                for (int j=loLim; j<high; j+=prime[i]) 
                    mark[j-low] = false; 
            } 
            for (int i = low; i<high; i++) 
                if (mark[i - low] == true) 
                    cout << i << " "; 
            low = low + limit; 
            high = high + limit; 
        } 
    } 
     
    int main() 
    { 
        int n ;//= 100;
        cout<<"Ent n";
        cin>>n;
        cout << "Primes smaller than " << n << ":n"; 
        segmentedSieve(n); 
        return 0; 
    } 

    /*
    OUTPUT
    Ent n50
    Primes smaller than 50:n2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 
    */
