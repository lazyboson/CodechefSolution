//https://www.codechef.com/FLPAST01/problems/RADGEE
#include <iostream>
#include <vector>
using namespace std;


vector<long long> multiply(vector<long long>& A, vector<long long>& B)
{
    size_t n = A.size();
    size_t m = B.size();
    vector<long long> product(n+m-1,0);

    // Multiply two polynomials term by term

    // Take ever term of first polynomial
    for (int i=0; i<n; i++)
    {
        // Multiply the current term of first polynomial
        // with every term of second polynomial.
        for (int j=0; j<m; j++)
            product[i+j] += A[i]*B[j];
    }
    return product;
}



// Driver program to test above functions
int main()
{
    int testcases, n,m;
    cin>>testcases;
    while (testcases--) {
        cin >> n >> m;
        vector<long long> first_poly_coefficeint(n), second_poly_coefficient(m);
        for(int i=0; i<n; i++)
            cin >> first_poly_coefficeint[i];
	for(int i=0; i<m; i++)
            cin >> second_poly_coefficient[i];
        vector<long long> ans = multiply(first_poly_coefficeint, second_poly_coefficient);
        for(int i=0; i <n+m-1; i++)
            cout << ans[i] << " ";
        cout <<"\n";
    }
    return 0;
}
