#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;


double sum_of_max(double A[][2],int n,int k, double maxim, double sum)//n:number of bidders, k:index upto which max is calculated
{
    if (k==n)return sum+=maxim;//on reaching leaf add the max of that path to sum
    else{
        for(int j=0;j<2;j++){//update sum and max
            if (maxim<A[k][j])sum =  sum_of_max(A,n,k+1,A[k][j],sum);
            else sum = sum_of_max(A,n,k+1,maxim,sum);
        }
    }
    return sum;
}

struct Bid//used for method2
{
    double bid;
    int k;//k is the index of the bidder
    bool operator<(const Bid& rhs) const{
        return bid < rhs.bid;
    }
};
double method2(Bid arr[],int n)
{
    vector<int>v;
    sort(arr, arr+n);reverse(arr,arr+n);//sorting arr in reverse order
    double sum = 0,prob = 1;
    for (int i = 0; i<n; i++){
        bool in_v = find(v.begin(), v.end(), arr[i].k) != v.end();//checks if k present in v
        if((in_v)) return (sum += (arr[i].bid)*prob);
        else prob*=0.5;
        v.push_back(arr[i].k);//append k to v
        sum += (arr[i].bid)*prob;
    }
}

int main()
{
    //Input format - n followed by 2n numbers.
    int n;
    cin>>n;
    Bid B[n*2];
    double A[n][2];
    for (int i=0;i<n;i++){
        double temp0,temp1;
        cin>>temp0;
        B[2*i].bid = temp0;
        A[i][0]=temp0;
        cin>>temp1;
        B[2*i+1].bid = temp1;
        A[i][1]=temp1;
        B[2*i].k = i;
        B[2*i+1].k = i;
    }

    cout<<method2(B,2*n)<<endl;
    cout<<sum_of_max(A,n,0,0,0)/pow(2,n);
}
