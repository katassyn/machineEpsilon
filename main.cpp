/*
POLECENIE:
Napisz program w jezyku "C/C++", umozliwiajacy "doswiadczalne" wyznaczenie
liczby bitow mantysy oraz tzw. epsylona maszynowego, tj. najmniejszej liczby epsilon
takiej, ze fl(epsilon + 1) > 1. Wyznacz epsylon maszynowy dla zmiennych typu float
i double i sprawdz czy da sie go wyznaczyc dla zmiennych typu long double.
Sprawdz tez ile cyfr znaczacych posiada epsylon maszynowy.
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {

    cout << "   WYZNACZANIE EPSILON MASZYNOWEGO - DOSWIADCZALNIE" << endl;
    
    /*
    CZESC 1: EPSILON DLA TYPU FLOAT (32 bity)
    Typ float w standardzie IEEE 754:
    - 1 bit znaku
    - 8 bitow cechy (wykladnika)
    - 23 bity mantysy

    Spodziewany epsilon: 2^(-23) = 1.19 * 10^(-7)
    Spodziewana liczba cyfr znaczacych: ~7
    */
    cout << " " << endl;
    cout << "FLOAT (32 bity)" << endl;
    
    float epsilon_float = 1.0f;
    int bity_mantysy_float = 0;

    // Dzielimy przez 2 dopóki (1 + epsilon) jest większe od 1
    while ((1.0f + epsilon_float) > 1.0f) {
        epsilon_float = epsilon_float / 2.0f;   // Dzielimy przez 2 aby przejsc do kolejnego bitu
        bity_mantysy_float++;
    }

    epsilon_float = epsilon_float * 2.0f;
    bity_mantysy_float--;
    
    // Obliczamy liczbe cyfr znaczacych
    // Wzor: cyfry = -log10(epsilon) = bity_mantysy * log10(2)
    float cyfry_float = -log10(epsilon_float);

    cout << "Epsilon maszynowy:        " << scientific << setprecision(10) 
         << epsilon_float << endl;
    cout << "Liczba bitow mantysy:     " << bity_mantysy_float << endl;
    cout << "Liczba cyfr znaczacych:   " << fixed << setprecision(1) 
         << cyfry_float << endl;
    cout << endl;
    
    /*
    CZESC 2: EPSILON DLA TYPU DOUBLE (64 bity)

    Typ double w standardzie IEEE 754:
    - 1 bit znaku
    - 11 bitow cechy (wykladnika)
    - 52 bity mantysy

    Spodziewany epsilon: 2^(-52) = 2.22 * 10^(-16)
    Spodziewana liczba cyfr znaczacych: ~15-16
    */
    cout << " " << endl;
    cout << "DOUBLE (64 bity)" << endl;
    
    double epsilon_double = 1.0;
    int bity_mantysy_double = 0;

    while ((1.0 + epsilon_double) > 1.0) {
        epsilon_double = epsilon_double / 2.0;
        bity_mantysy_double++;
    }

    epsilon_double = epsilon_double * 2.0;
    bity_mantysy_double--;

    // Obliczamy liczbe cyfr znaczacych
    double cyfry_double = -log10(epsilon_double);

    cout << "Epsilon maszynowy:        " << scientific << setprecision(20) 
         << epsilon_double << endl;
    cout << "Liczba bitow mantysy:     " << bity_mantysy_double << endl;
    cout << "Liczba cyfr znaczacych:   " << fixed << setprecision(1) 
         << cyfry_double << endl;
    cout << endl;
    
    /*
    CZESC 3: EPSILON DLA TYPU LONG DOUBLE (80+ bitow)

    Typ long double

    Na x86: 80 bitow
    - 1 bit znaku
    - 15 bitow cechy
    - 64 bity mantysy

    Spodziewany epsilon (dla 80-bit): 2^(-63) = 1.08 * 10^(-19)
    Spodziewana liczba cyfr znaczacych: ~18-19
    */
    
    cout << " " << endl;
    cout << "LONG DOUBLE (80+ bitow, zalezy od platformy)" << endl;
    
    long double epsilon_long = 1.0L;
    int bity_mantysy_long = 0;
    
    // Ta sama logika
    while ((1.0L + epsilon_long) > 1.0L) {
        epsilon_long = epsilon_long / 2.0L;
        bity_mantysy_long++;
    }

    epsilon_long = epsilon_long * 2.0L;
    bity_mantysy_long--;

    long double cyfry_long = -log10l(epsilon_long);

    cout << "Epsilon maszynowy:        " << scientific << setprecision(25) 
         << epsilon_long << endl;
    cout << "Liczba bitow mantysy:     " << bity_mantysy_long << endl;
    cout << "Liczba cyfr znaczacych:   " << fixed << setprecision(1) 
         << cyfry_long << endl;
    cout << endl;
    
    /*
    CZESC 4: PODSUMOWANIE I POROWNANIE Z TEORIA
    */
    cout << " " << endl;
    cout << "PODSUMOWANIE - POROWNANIE Z TEORIA" << endl;
    cout << endl;
    
    cout << "Typ              Bity mantysy   Epsilon          Cyfry znacz." << endl;
    cout << "float         " << setw(12) << bity_mantysy_float
         << "   " << scientific << setprecision(2) << epsilon_float
         << "       " << fixed << setprecision(0) << cyfry_float << endl;
    cout << "double        " << setw(12) << bity_mantysy_double
         << "   " << scientific << setprecision(2) << epsilon_double
         << "       " << fixed << setprecision(0) << cyfry_double << endl;
    cout << "long double   " << setw(12) << bity_mantysy_long
         << "   " << scientific << setprecision(2) << epsilon_long
         << "       " << fixed << setprecision(0) << cyfry_long << endl;
    cout << endl;
    
    cout << "WARTOSCI TEORETYCZNE:" << endl;
    cout << "float:       23 bity mantysy, eps = 2^(-23) ~ 1.19e-07,  ~7 cyfr" << endl;
    cout << "double:      52 bity mantysy, eps = 2^(-52) ~ 2.22e-16, ~16 cyfr" << endl;
    cout << "long double: 63 bity mantysy, eps = 2^(-63) ~ 1.08e-19, ~19 cyfr" << endl;
    cout << endl;
    return 0;
}