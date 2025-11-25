/*
================================================================================
POLECENIE:
Napisz program w języku „C/C++", umożliwiający „doświadczalne" wyznaczenie 
liczby bitów mantysy oraz tzw. epsylona maszynowego, tj. najmniejszej liczby ε 
takiej, że fl(ε + 1) > 1. Wyznacz epsylon maszynowy dla zmiennych typu float 
i double i sprawdź czy da się go wyznaczyć dla zmiennych typu long double. 
Sprawdź też ile cyfr znaczących posiada epsylon maszynowy.
================================================================================

================================================================================
TEORIA - ODPOWIEDŹ NA PYTANIE: 
"Jaki jest związek epsilon z precyzją arytmetyki?"
================================================================================

1. CO TO JEST EPSILON MASZYNOWY?
   
   Epsilon maszynowy (ε) to NAJMNIEJSZA liczba, którą możemy dodać do 1,
   żeby komputer "zauważył" różnicę.
   
   Innymi słowy: fl(1 + ε) > 1, ale fl(1 + ε/2) = 1
   
   Gdzie fl() oznacza "reprezentację zmiennoprzecinkową" (floating point).

2. DLACZEGO TAK SIĘ DZIEJE?
   
   Komputer przechowuje liczby z ograniczoną precyzją (skończona liczba bitów).
   
   Liczba 1 jest zapisana jako: 1.000000000... (pewna liczba zer)
   
   Jeśli dodamy zbyt małą liczbę, wynik po zaokrągleniu nadal będzie = 1,
   bo te dodatkowe cyfry "nie mieszczą się" w pamięci.

3. ZWIĄZEK Z MANTYSĄ:
   
   - Mantysa ma określoną liczbę bitów (np. 23 dla float, 52 dla double)
   - Epsilon ≈ 2^(-liczba_bitów_mantysy)
   - Im więcej bitów mantysy, tym mniejszy epsilon (lepsza precyzja)

4. ZWIĄZEK Z CYFRAMI ZNACZĄCYMI:
   
   - Cyfry znaczące (dziesiętne) ≈ liczba_bitów_mantysy × log10(2)
   - log10(2) ≈ 0.301
   - float: ~23 × 0.301 ≈ 7 cyfr znaczących
   - double: ~52 × 0.301 ≈ 15-16 cyfr znaczących

5. JAK WYZNACZYĆ EPSILON DOŚWIADCZALNIE?
   
   Algorytm:
   a) Zacznij od epsilon = 1
   b) Dziel epsilon przez 2
   c) Sprawdź czy (1 + epsilon) > 1
   d) Jeśli TAK - kontynuuj dzielenie
   e) Jeśli NIE - poprzednia wartość to epsilon maszynowy
   
   Liczba iteracji = liczba bitów mantysy

================================================================================
*/

#include <iostream>     // do wypisywania na ekran (cout)
#include <iomanip>      // do formatowania liczb (setprecision)
#include <cmath>        // do funkcji matematycznych (log10)

using namespace std;

int main() {
    
    cout << "============================================================" << endl;
    cout << "   WYZNACZANIE EPSILON MASZYNOWEGO - DOSWIADCZALNIE" << endl;
    cout << "============================================================" << endl;
    cout << endl;
    
    /*
    ========================================================================
    CZĘŚĆ 1: EPSILON DLA TYPU FLOAT (32 bity)
    ========================================================================
    
    Typ float w standardzie IEEE 754:
    - 1 bit znaku
    - 8 bitów cechy (wykładnika)
    - 23 bity mantysy
    
    Spodziewany epsilon: 2^(-23) ≈ 1.19 × 10^(-7)
    Spodziewana liczba cyfr znaczących: ~7
    */
    
    cout << "------------------------------------------------------------" << endl;
    cout << "FLOAT (32 bity)" << endl;
    cout << "------------------------------------------------------------" << endl;
    
    float epsilon_float = 1.0f;     // Zaczynamy od 1 (f oznacza float)
    int bity_mantysy_float = 0;     // Licznik bitów mantysy
    
    // Pętla szukająca epsilon
    // Dzielimy przez 2 dopóki (1 + epsilon) jest większe od 1
    while ((1.0f + epsilon_float) > 1.0f) {
        epsilon_float = epsilon_float / 2.0f;   // Dzielimy przez 2
        bity_mantysy_float++;                    // Zwiększamy licznik
    }
    
    // Po wyjściu z pętli, epsilon jest ZA MAŁY (1 + eps = 1)
    // Więc musimy wrócić do poprzedniej wartości (pomnożyć przez 2)
    epsilon_float = epsilon_float * 2.0f;
    bity_mantysy_float--;  // Korygujemy licznik
    
    // Obliczamy liczbę cyfr znaczących
    // Wzór: cyfry = -log10(epsilon) ≈ bity_mantysy × log10(2)
    float cyfry_float = -log10(epsilon_float);
    
    // Wypisujemy wyniki
    cout << "Epsilon maszynowy:        " << scientific << setprecision(10) 
         << epsilon_float << endl;
    cout << "Liczba bitow mantysy:     " << bity_mantysy_float << endl;
    cout << "Liczba cyfr znaczacych:   " << fixed << setprecision(1) 
         << cyfry_float << endl;
    cout << endl;
    
    /*
    ========================================================================
    CZĘŚĆ 2: EPSILON DLA TYPU DOUBLE (64 bity)
    ========================================================================
    
    Typ double w standardzie IEEE 754:
    - 1 bit znaku
    - 11 bitów cechy (wykładnika)
    - 52 bity mantysy
    
    Spodziewany epsilon: 2^(-52) ≈ 2.22 × 10^(-16)
    Spodziewana liczba cyfr znaczących: ~15-16
    */
    
    cout << "------------------------------------------------------------" << endl;
    cout << "DOUBLE (64 bity)" << endl;
    cout << "------------------------------------------------------------" << endl;
    
    double epsilon_double = 1.0;    // Zaczynamy od 1
    int bity_mantysy_double = 0;    // Licznik bitów mantysy
    
    // Ta sama logika co dla float
    while ((1.0 + epsilon_double) > 1.0) {
        epsilon_double = epsilon_double / 2.0;
        bity_mantysy_double++;
    }
    
    // Wracamy do poprzedniej wartości
    epsilon_double = epsilon_double * 2.0;
    bity_mantysy_double--;
    
    // Obliczamy liczbę cyfr znaczących
    double cyfry_double = -log10(epsilon_double);
    
    // Wypisujemy wyniki
    cout << "Epsilon maszynowy:        " << scientific << setprecision(20) 
         << epsilon_double << endl;
    cout << "Liczba bitow mantysy:     " << bity_mantysy_double << endl;
    cout << "Liczba cyfr znaczacych:   " << fixed << setprecision(1) 
         << cyfry_double << endl;
    cout << endl;
    
    /*
    ========================================================================
    CZĘŚĆ 3: EPSILON DLA TYPU LONG DOUBLE (80+ bitów)
    ========================================================================
    
    Typ long double - UWAGA: zależy od kompilatora i systemu!
    
    Na x86 (Linux/GCC): 80 bitów
    - 1 bit znaku
    - 15 bitów cechy
    - 64 bity mantysy
    
    Na Windows (MSVC): często = double (64 bity)
    
    Spodziewany epsilon (dla 80-bit): 2^(-63) ≈ 1.08 × 10^(-19)
    Spodziewana liczba cyfr znaczących: ~18-19
    
    CZY DA SIĘ WYZNACZYĆ?
    TAK, ale wynik zależy od platformy!
    */
    
    cout << "------------------------------------------------------------" << endl;
    cout << "LONG DOUBLE (80+ bitow, zalezy od platformy)" << endl;
    cout << "------------------------------------------------------------" << endl;
    
    long double epsilon_long = 1.0L;    // L oznacza long double
    int bity_mantysy_long = 0;
    
    // Ta sama logika
    while ((1.0L + epsilon_long) > 1.0L) {
        epsilon_long = epsilon_long / 2.0L;
        bity_mantysy_long++;
    }
    
    // Wracamy do poprzedniej wartości
    epsilon_long = epsilon_long * 2.0L;
    bity_mantysy_long--;
    
    // Obliczamy liczbę cyfr znaczących
    long double cyfry_long = -log10l(epsilon_long);  // log10l dla long double
    
    // Wypisujemy wyniki
    cout << "Epsilon maszynowy:        " << scientific << setprecision(25) 
         << epsilon_long << endl;
    cout << "Liczba bitow mantysy:     " << bity_mantysy_long << endl;
    cout << "Liczba cyfr znaczacych:   " << fixed << setprecision(1) 
         << cyfry_long << endl;
    cout << endl;
    
    /*
    ========================================================================
    CZĘŚĆ 4: PODSUMOWANIE I PORÓWNANIE Z TEORIĄ
    ========================================================================
    */
    
    cout << "============================================================" << endl;
    cout << "PODSUMOWANIE - POROWNANIE Z TEORIA (IEEE 754)" << endl;
    cout << "============================================================" << endl;
    cout << endl;
    
    cout << "Typ           | Bity mantysy | Epsilon        | Cyfry znacz." << endl;
    cout << "--------------|--------------|----------------|-------------" << endl;
    cout << "float         | " << setw(12) << bity_mantysy_float 
         << " | " << scientific << setprecision(2) << epsilon_float 
         << "       | " << fixed << setprecision(0) << cyfry_float << endl;
    cout << "double        | " << setw(12) << bity_mantysy_double 
         << " | " << scientific << setprecision(2) << epsilon_double 
         << "       | " << fixed << setprecision(0) << cyfry_double << endl;
    cout << "long double   | " << setw(12) << bity_mantysy_long 
         << " | " << scientific << setprecision(2) << epsilon_long 
         << "       | " << fixed << setprecision(0) << cyfry_long << endl;
    cout << endl;
    
    cout << "WARTOSCI TEORETYCZNE (IEEE 754):" << endl;
    cout << "float:       23 bity mantysy, eps = 2^(-23) ~ 1.19e-07,  ~7 cyfr" << endl;
    cout << "double:      52 bity mantysy, eps = 2^(-52) ~ 2.22e-16, ~16 cyfr" << endl;
    cout << "long double: 63 bity mantysy, eps = 2^(-63) ~ 1.08e-19, ~19 cyfr" << endl;
    cout << endl;

    cout << endl;
    cout << "============================================================" << endl;
    cout << "KONIEC PROGRAMU" << endl;
    cout << "============================================================" << endl;
    
    return 0;
}

/*
================================================================================
ODPOWIEDZI NA PYTANIA Z POLECENIA:
================================================================================

1. JAKI JEST ZWIĄZEK EPSILON Z PRECYZJĄ ARYTMETYKI?

   Epsilon maszynowy bezpośrednio określa PRECYZJĘ obliczeń:
   
   - Jest to względny błąd reprezentacji każdej liczby
   - Każda liczba x jest reprezentowana z błędem względnym ≤ ε/2
   - Im mniejszy epsilon, tym dokładniejsze obliczenia
   
   Praktycznie: jeśli epsilon = 10^(-16), to wyniki są dokładne
   na około 16 cyfr znaczących.

2. ILE CYFR ZNACZĄCYCH POSIADA EPSILON MASZYNOWY?

   Wzór: cyfry_znaczące ≈ -log10(epsilon) ≈ bity_mantysy × 0.301
   
   - float:       ~7 cyfr znaczących
   - double:      ~15-16 cyfr znaczących  
   - long double: ~18-19 cyfr znaczących

3. CZY DA SIĘ WYZNACZYĆ EPSILON DLA LONG DOUBLE?

   TAK, ale wynik zależy od platformy:
   - Linux/GCC: prawdziwy 80-bitowy long double (63 bity mantysy)
   - Windows/MSVC: często long double = double (52 bity mantysy)
   - Niektóre systemy: 128-bitowy (quad precision)

4. JAK DZIAŁA ALGORYTM WYZNACZANIA EPSILON?

   a) Zaczynamy od epsilon = 1
   b) Dzielimy epsilon przez 2 (to odpowiada "przesunięciu" o 1 bit)
   c) Sprawdzamy czy (1 + epsilon) > 1
   d) Powtarzamy aż warunek przestanie być spełniony
   e) Cofamy się o jedną iterację
   
   Liczba iteracji = liczba bitów mantysy

================================================================================
*/