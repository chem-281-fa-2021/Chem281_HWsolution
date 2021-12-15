#include <iostream>
#include <stack>
#include <algorithm>
#include <armadillo>
#include <time.h>
using namespace std;

template <class T>
int compare(T &a1, T &a2)
{
    if (a1 < a2)
        return -1;
    if (a1 == a2)
        return 0;
    return 1;
}

template <class T>
inline void swap(T *a, int i, int j)
{
    T temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}
template <class T>
void quicksort(T *a, int left, int right)
{
    if (right > left )
    {
        T pivot = a[right];
        int i = left;
        int j = right - 1;
        do
        {
            while (compare(a[i], pivot) < 0)
                i++;
            while (compare(a[j], pivot) > 0 && j > left)
                j--;
            // cout << i << " " << j << endl;
            if (i >= j)
                break; // cross-over

            swap(a, i, j);
        } while (1);
        swap(a, i, right);
        int splitPoint = i;
        quicksort(a, left, splitPoint - 1);
        quicksort(a, splitPoint + 1, right);
    }
}

template <class T>
void insertionSort(T* a, int n)
{
    // cout <<" insertion is called"<< endl;
    // for (unsigned int iy = 0; iy < n; iy++)
    //     cout << a[iy] <<" ";
    //     cout << endl;
    for (unsigned int i = 1; i < n; i++)
    {
        T candidate = a[i];
        // cout <<i <<" " <<candidate<< endl;
        int k = i -1;
        while (compare(candidate, a[k]) < 0){
            a[k + 1] = a[k];
            k--;
            if(k<0) break;
        }
        k++;
        if (k != i)
            a[k] = candidate;
    }
}


template <class T>
void quicksortm(T *a, int left, int right, int m)
{
    // cout << left<< " " << right <<  " " << right - left + 1 <<  endl;
    if(right <= left)
        return;
    if(right - left <= m){
        T *p = &a[left];
        insertionSort<T>(p, right - left + 1);
        return;
    }
    T pivot = a[right];
    int i = left;
    int j = right - 1;
    do
    {
        while (compare(a[i], pivot) < 0)
            i++;
        while (compare(a[j], pivot) > 0 && j > left)
            j--;
        // cout << i << " " << j << endl;
        if (i >= j)
            break; // cross-over

        swap(a, i, j);
    } while (1);
    swap(a, i, right);
    int splitPoint = i;

    quicksortm(a, left, splitPoint - 1, m);
    quicksortm(a, splitPoint + 1, right, m);
}

int main()
{
    // arma::uvec m ={ 4, 4, 8, 8, 18, 18, 25, 25, 100, 1000};
    // arma::uvec m ={0, 1, 2, 3, 4, 5, 7 , 9, 12, 15, 18, 21, 25, 100, 1000};
    arma::uvec m ={0, 1, 2, 3, 4, 5, 7 , 9, 12, 15, 18, 21, 25, 50, 100, 300, 1000};
    m.t().print("m");
    arma::rowvec time_m= arma::zeros(m.n_elem).t();
    // avec.load("input_6.2");
    size_t size_vec = 100000;

    // arma::vec avec=arma::randu(100);
    // double *a = avec.memptr();
    // quicksortm<double>(a, 0, avec.n_elem - 1, 7);
    // // quicksort<double>(a, 0, avec.n_elem - 1);
    // // insertionSort<double>(a, avec.n_elem );
    // avec.print("after sort");

    clock_t t;
    arma::rowvec avec(size_vec);
    arma::rowvec testvec(size_vec);
    double *a = testvec.memptr();
    // time_m.print();
    // avec.print();
    for (unsigned int j = 0; j < 100; j++){
        avec.randn();
        for (unsigned int k = 0; k < m.n_elem; k++){
            testvec =avec;
            // testvec.print("before sort");
            sleep(0.5);
            t = clock();
            quicksortm<double>(a, 0, testvec.n_elem - 1, m(k));
            t = clock() - t;
            // testvec.print("after sort");
            time_m(k) += (double)t /CLOCKS_PER_SEC;
        }
    }
    time_m.print();
    return 0;
}