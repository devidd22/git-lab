#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <immintrin.h>
#include <vector>
#include <sys/random.h>
#include <ctime>
#include <random> // Necesar pentru metoda 5

using namespace std;

// Metoda 1: rand() clasic din C
int get_random_std() {
    return rand() % 200;
}

// Metoda 2: Instrucțiune hardware directă (RDRAND)
int get_random_rdrand() {
    unsigned int ret;
    if (_rdrand32_step(&ret) == 1) return ret;
    return -1;
}

// Metoda 3: Citire directă din fișierul de entropie al OS-ului
int get_random_dev_urandom() {
    int ret;
    FILE *urandom = fopen("/dev/urandom", "r");
    if (urandom) {
        fread(&ret, sizeof(ret), 1, urandom);
        fclose(urandom);
        return ret;
    }
    return -1;
}

// Metoda 4: Apel de sistem Linux (getrandom)
int get_random_getrandom() {
    int ret;
    if (getrandom(&ret, sizeof(ret), 0) > 0) return ret;
    return -1;
}

// Metoda 5: Modern C++11 (Mersenne Twister) - Aceasta lipsea!
int get_random_cpp11() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 199);
    return dis(gen);
}

typedef int (*fp)();

int main() {
    int n;
    cout << "Please enter a number: ";
    cin >> n;

    srand((unsigned)time(NULL));

    // Vectorul cu toate cele 5 metode
    vector<fp> randoms = { 
        get_random_getrandom, 
        get_random_dev_urandom, 
        get_random_rdrand, 
        get_random_std,
        get_random_cpp11 
    };

    // REPARAREA BUCLEI: i < 5 (face fix 5 pasi: 0, 1, 2, 3, 4)
    for (int i = 0; i < 5; i++) {
        // Folosim i % 5 pentru a trece prin toate metodele din vector
        if ((randoms[i % 5]() % 200) >= 0) { 
            n += 1; 
        } else {
            i--; // Daca metoda a esuat, mai incercam o data
        }
    }

    cout << "Your number + 5 is: " << n << endl;
    return 0;
}
