/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: bohrerl
 *
 * Created on 12 novembre 2018, 13:00
 */

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

/*
 * 
 */

bool estImpairCroisee(int n);
bool estPairCroisee(int n);

bool estImpairQcqCroisee(int n);
bool estPairQcqCroisee(int n);

template<class T>
int dichoInter(vector<T> v, T val);

template<class T>
int dichoRec(vector<T> v, T val);
template<class T>
int dichoRecWorker(vector<T> v, int inf, int sup, T val);

template<class T>
T maxVect(vector<T>& v);

template<class T>
T maxVectWorker(vector<T>& v, int inf, int sup);

double puissance(float x, int n);
double puissanceNbMult(float x, int n, int& nbmult);

int factorielleIter(int n){
    int r = 1;
    int i = 1;
    while (i <= n){
        r = r * i;
        i++;
    }
    return r;
}

int factorielleRec(int n){
    if (n == 0){
        return 1;
    }else return factorielleRec(n-1) * n;
}

bool estPair(int n){
    if (n == 1){
        return false;
    }else if (n == 0){
        return true;
    }else return estPair(n-2);
}

bool estPairQcq(int n){
    if (n < 0){
        if (n == -1){
            return false;
        }
        else return estPairQcq(n + 2);
    }else if (n > 0){
        if (n == 1){
            return false;
        }
        else return estPairQcq(n - 2);
    }
    else return true;
}
    
bool estPairCroisee(int n){
    if (n == 0) {
        return true;
    }else if (n == 1){
        return false;
    }else{
        return !estImpairCroisee(n - 2);
    }
}

bool estImpairCroisee(int n){
    if (n == 1) {
        return true;
    }else if (n == 0){
        return false;
    }else{
        return !estPairCroisee(n - 2);
    }
}    

bool estPairQcqCroisee(int n){
    if (n < -1){
        return !estImpairQcqCroisee(n + 2);
    }else if ( n > 1){
        return !estImpairQcqCroisee(n - 2);
    }else if (n == 0){
        return true;
    }else return false;
}

bool estImpairQcqCroisee(int n){
    if (n < -1){
        return !estPairQcqCroisee(n + 2);
    }else if ( n > 1){
        return !estPairQcqCroisee(n - 2);
    }else if (n != 0){
        return true;
    }else return false;
}

template<class T>
int dichoIter(vector<T> v, T val){
    int sup = v.size()-1;
    
    if (v[sup] < val){
        return -1;
    } else {
        int m;
        int inf = 0;
        while (inf <= sup){
            m = (inf + sup) / 2;
            if (v[m] < val){
                inf = m + 1;
            } else {
                sup = m -1;
            }
        }
        if (v[inf] == val){
            return inf;
        } else {
            return -1;
        }
    }
}

template<class T>
int dichoRec(vector<T> v, T val){
    if(v[v.size()-1] < val){
        return -1;
    } else {
        return dichoRecWorker(v, 0, v.size() -1 , val);
    }
}

template<class T>
int dichoRecWorker(vector<T> v, int inf, int sup, T val){
    if (inf > sup){
        if (v[inf] == val){
            return inf;
        }else {
            return -1;
        }
    } else {
        int m = (inf + sup) / 2;
        if (v[m] < val){
            return dichoRecWorker(v, m+1, sup, val);
        } else return dichoRecWorker(v, inf, m-1, val);
    }
}

void hanoi(int nbDisques, char depart, char intermediaire, char arrivee){
    if (nbDisques == 1){
        cout << "deplacement du disque " << nbDisques << " du piquet " << depart << " vers " << arrivee << endl; 
    }else{
        hanoi(nbDisques-1, depart, arrivee, intermediaire);
        cout << "deplacement du disque " << nbDisques << " du piquet " << depart << " vers " << arrivee << endl; 
        hanoi(nbDisques-1, intermediaire, depart, arrivee);
    }
    
}

template<class T>
T maxVect(vector<T>& v){
    if (v.empty()) {
        return 0;
    }if (v.size() == 1){
        return v[0];
    }else {
        return maxVectWorker(v,0,v.size()-1);
    }
}

template<class T>
T maxVectWorker(vector<T>& v, int inf, int sup){
    if (inf > sup){
        return 0;
    }
    else if (inf == sup){
        return v[inf];
    }
    else{
        int m = (inf+sup)/2;
        T m1 = maxVectWorker(v,inf,m);
        T m2 = maxVectWorker(v,m+1,sup);
        if (m1>m2) return m1;
        else return m2;
    }
}

double puissance(float x, int n){
    if (n == 0) {
        return 1;
    }
    else return x * puissance(x, n - 1);
}

double puissanceNbMult(float x, int n, int& nbmult){
    if (n == 0) {
        if(nbmult > 0) nbmult--;
        return 1;
    }else{
        return x * puissanceNbMult(x, n - 1, (nbmult+=1));
    }
}

double puissanceDRNbMult(float x, int n, int& nbmult){
    if (n == 0) {
        return 1;
        if(nbmult > 0) nbmult--;
    }else if (n == 1){
        return x;
    }else if (estPair(n)){
        nbmult += 1;
        double i = puissanceDRNbMult(x, n/2, nbmult);
        return i * i;
    }else{
        nbmult += 2;
        double i = puissanceDRNbMult(x, n/2, nbmult);
        return x * i * i;
    }
}

template<class T>
void minMaxIter(vector<T>& v, T& min, T& max, int& nbComp){
    for(auto elem : v){
        nbComp += 2;
        if (elem < min){
            min = elem;
        }
        else if(elem > max){
            max = elem;
        }
    }
}

template<class T>
void minMaxDR(vector<T>& v, T& min, T& max, int& nbComp){
    for(auto elem : v){
        nbComp += 2;
        if (elem < min){
            min = elem;
        }
        else if(elem > max){
            max = elem;
        }
    }
}

template<class T>
void minMaxDRWorker(vector<T>& v, T& min, T& max, int& nbComp){
    if (min > max){
        int temp = max;
        max = min;
        min = temp;
    }
    if else (min != max){
        int m = (min+max)/2;
        T m1 = maxVectWorker(v,min,m);
        T m2 = maxVectWorker(v,m+1,max);
        if (m1>m2) return m1;
        else return m2;
    }
}

int main(int argc, char** argv) {

    vector<int> v = {1,2,3,4,5,6,7,8,9};
    
    cout << estImpairQcqCroisee(-3) << endl;
    cout << dichoRec(v, 5) << endl;
    
    hanoi(2,'a','b','c');
    
    cout << maxVect(v) << endl;
    
    cout << puissance(5, 0) << endl;
    int i = 0;
    cout << puissanceNbMult(2, 32, i) << endl;
    cout << "i = " << i << endl;
    i = 0;
    cout << puissanceDRNbMult(2, 32, i) << endl;
    cout << "i = " << i << endl;
    
    int max = 0;
    int min = 1000000;
    int nbComp = 0;
    
    minMaxIter(v,min,max,nbComp);
    
    cout << min << ", " << max << ", " << nbComp << endl;
    
    return 0;
}

