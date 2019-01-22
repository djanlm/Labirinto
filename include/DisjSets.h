#include <iostream>   // cout, cin, endl
#include <random>     // radom_device, mt19937, std::shuffle.
#include <iomanip>    // std::setw()
#include <string>     // std::string
#include <vector>

class DisjSets
{
  private:
    std::vector<int> s;
    int numOfSets;
  public:
	explicit DisjSets( int numElements ): s( numElements )
	{
		numOfSets=numElements;
    for( int i = 0; i < numElements; i++ )
        s[ i ] = -1;
	}


	int find( int x ) const
	{
    	if( s[ x ] < 0 )
        	return x;
    	else
        	return find( s[ x ] );
	}
    int find( int x )
	{
    	if( s[ x ] < 0 )
        return x;
    	else
        return s[ x ] = find( s[ x ] );
	}
    void unionSets( int root1, int root2 )
	{
    if( s[ root2 ] < s[ root1 ] )  
        s[ root1 ] = root2;        
    else
    {
        if( s[ root1 ] == s[ root2 ] )
            s[ root1 ]--;          
        s[ root2 ] = root1;        
    }
      numOfSets--;
	}

  	int size( ) const
	{
    	return numOfSets;
	}
};
