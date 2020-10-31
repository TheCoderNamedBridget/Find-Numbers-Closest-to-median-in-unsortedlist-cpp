
/******************************************************************************

Bridget Naylor
Date: 10/30/2020
CECS 328 Section 7
Lab 4 
*******************************************************************************/
#include <stdlib.h>     /* srand, rand */
#include <iostream>
using namespace std;

//returns index of the partition value
int partition( int a[], int start, int end, bool useAbs )
{
    //cout<<"start "<<start<<" end "<<end<<endl;
    if ( start == end )
    {
        return start;
    }
    
    //cout<<"parts "<<start<<" e "<<end<<endl;
    int pivIndex = start;
    int midIndex = start + (end - start)/2;

    bool goLeft = true;
    bool goRight = true;
    
    int piv = a[pivIndex];
    a[start] = a[midIndex];
    a[midIndex] = piv;
    int leftPivIndex = midIndex - 1;
    int rightPivIndex = midIndex + 1;
    for ( int k = start; k < end; k ++ )
    {
        if ( leftPivIndex < start )
        {
            //cout<<"Hereleft"<<endl;
            //do stuff for left side
            goLeft = false;
        }
        if ( rightPivIndex > end )
        {
            //cout<<"Hereright"<<endl;
            //do stuff for left side
            goRight = false;
        }
        if ( !useAbs )
        {
            
            if ( goLeft && goRight && a[leftPivIndex] > piv && a[rightPivIndex] < piv )//if emlent on left and right need switching switch
            {
                //cout<<"double switch"<<endl;
                int temp = a[leftPivIndex];
                a[leftPivIndex] = a[rightPivIndex];
                a[rightPivIndex] = temp;
            }
            else if ( goRight && (a[rightPivIndex] < piv) )//only switch right
            {
                int pivPlusOne = a[midIndex + 1];
                a[midIndex + 1] = a[rightPivIndex];
                a[rightPivIndex] = pivPlusOne;
                
                //switches piv and element to the right of piv
                int pivValue = a[midIndex];
                a[midIndex] = a[midIndex + 1];
                a[midIndex + 1] = pivValue;
                
                midIndex++;
                
            }
            else if ( goLeft && (a[leftPivIndex] > piv) )//only switch left
            {
                //cout<<"left switch"<<endl;
                //switches element to left of piv with other left element <> piv
                int pivMinusOne = a[midIndex - 1];
                a[midIndex - 1] = a[leftPivIndex];
                a[leftPivIndex] = pivMinusOne;
                
                //switches piv and element to the right of piv
                int pivValue = a[midIndex];
                a[midIndex] = a[midIndex - 1];
                a[midIndex - 1] = pivValue;
                
                midIndex--;
            }
            leftPivIndex --;
            rightPivIndex ++;
        }
        else if ( useAbs )
        {
            if ( goLeft && goRight && abs(a[leftPivIndex]) > abs(piv) && abs(a[rightPivIndex]) < abs(piv) )//if emlent on left and right need switching switch
            {
                //cout<<"double switch"<<endl;
                int temp = a[leftPivIndex];
                a[leftPivIndex] = a[rightPivIndex];
                a[rightPivIndex] = temp;
            }
            else if ( goRight && (abs(a[rightPivIndex]) < abs(piv)) )//only switch right
            {
                int pivPlusOne = a[midIndex + 1];
                a[midIndex + 1] = a[rightPivIndex];
                a[rightPivIndex] = pivPlusOne;
                
                //switches piv and element to the right of piv
                int pivValue = a[midIndex];
                a[midIndex] = a[midIndex + 1];
                a[midIndex + 1] = pivValue;
                
                midIndex++;
                
            }
            else if ( goLeft && (abs(a[leftPivIndex]) > abs(piv)) )//only switch left
            {
                //cout<<"left switch"<<endl;
                //switches element to left of piv with other left element <> piv
                int pivMinusOne = a[midIndex - 1];
                a[midIndex - 1] = a[leftPivIndex];
                a[leftPivIndex] = pivMinusOne;
                
                //switches piv and element to the right of piv
                int pivValue = a[midIndex];
                a[midIndex] = a[midIndex - 1];
                a[midIndex - 1] = pivValue;
                
                midIndex--;
            }
            leftPivIndex --;
            rightPivIndex ++;
        }
        
        
    }//end of for loop
    return midIndex;
}

int quickSelect( int a[], int s, int e, int k, bool useAbs )
{
    int n = e + 1;//size
    int pivIndex = partition( a, s, e, useAbs );
    // cout<<"Partition piv index = "<<pivIndex<<" Value = "<<a[pivIndex]<<endl;
    // cout<<"s "<<s<<" e "<<e<<endl;
    // cout<<"s == e "<<(s == e)<<endl;
    // cout<<"k "<<k<<" pivot index "<< (pivIndex + 1)<<endl;
    if ( k - 1 == pivIndex -s)
    {
        //cout<<"basecase "<<endl;
        return a[pivIndex];
    }
    else if ( pivIndex - s > k - 1 )//k is to right of piv index
    {
        
        //cout<<"rightcase "<<endl;
        return quickSelect( a, s, pivIndex - 1, k, useAbs );
    }
    //cout<<"leftcase "<<endl;
    return quickSelect( a, pivIndex + 1, e, k - pivIndex + s - 1, useAbs );
    
    
}

int quickSelectIndexReturn( int a[], int s, int e, int k, bool useAbs)
{
    int n = e + 1;//size
    int pivIndex = partition( a, s, e, useAbs );
    // cout<<"Partition piv index = "<<pivIndex<<" Value = "<<a[pivIndex]<<endl;
    // cout<<"s "<<s<<" e "<<e<<endl;
    // cout<<"s == e "<<(s == e)<<endl;
    // cout<<"k "<<k<<" pivot index "<< (pivIndex + 1)<<endl;
    if ( k - 1 == pivIndex -s)
    {
        return pivIndex;
    }
    else if ( pivIndex - s > k - 1 )//k is to right of piv index
    {
        
        //cout<<"rightcase "<<endl;
        return quickSelectIndexReturn( a, s, pivIndex - 1, k, useAbs );
    }
    //cout<<"leftcase "<<endl;
    return quickSelectIndexReturn( a, pivIndex + 1, e, k - pivIndex + s - 1, useAbs );
    
    
}

int main()
{
    //PART A
    int n = 0;
    int k = 0;
    while ( n < 1)
    {
        cout<<"Enter a positive non zero integer: ";
        cin >> n;
    }
    int a[n];
    
    srand (time(NULL));
    for ( int i = 0; i < n; i++ )
    {
        int posOrNeg = rand() % 2 + 1;
        int posNum = rand() % 101;//0 - 100
        int negNum = rand() % 101 -100;//-100 - -1

        if ( posOrNeg == 2 )//posOrNeg = 2 +> do pos
        {
            a[i] = posNum;
        }
        else//do neg
        {
            a[i] = negNum;
        }
    }
    for ( int j = 0; j < n; j++)
    {
        cout<<"a[j] in main "<<a[j]<<endl;
    }
    
    while ( k < 1 || k > n )
    {
        cout<<"Enter a number between 1 and "<<n<<" k = ";
        cin>>k;
    }
    k = k + 1;
    //find median median = size / 2
    bool useAbs = false;
    int median = quickSelect( a, 0, n - 1, (n / 2) + 1, useAbs );
    cout<<"QuickSelect Median: "<<median<<endl;
    
    int diff[n];
    //time complexity = O(n)
    for ( int i = 0; i < n; i ++ )
    {
        
        //{-55,-3,3,8,34};
        if ( (a[i] > 0 && median <= 0 ))
        {
            diff[i] = a[i] + median;
        }
        else 
        {
            diff[i] = a[i] - median;
        }
        //cout<<"Diff index "<<i<<" "<<diff[i]<<endl;
        
    }
    
    //find the k closest numbers to median.
    //use diff list
    //call quick select on the diff list for 1st smallest, 2nd smallest up to k smallest 
    //runtime quick select = n run n times = n^2
    //Solution 2 just iterate to the right of 0(median-median value)
    useAbs = true;
    int endingIndexPrintTo = quickSelectIndexReturn( diff, 0, n - 1, k, useAbs );
    //O(k)
    if ( endingIndexPrintTo > 2 )
    {
        cout<<"Values Closest To Median "<<endl;
    }
    else
    {
        cout<<"Value Closest To Median "<<endl;
    }
    for ( int l = 1; l < endingIndexPrintTo + 1; l++ )
    {
        if ( (diff[l] > 0 && median <= 0 ))
        {
            diff[l] = diff[l] - median;
        }
        else 
        {
            diff[l] = diff[l] + median;
        }
        cout<<diff[l]<<endl;
    }

    return 0;
}

