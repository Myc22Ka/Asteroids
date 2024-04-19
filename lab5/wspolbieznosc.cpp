#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <vector>
#include <cmath>
#include <functional>

using namespace std;

double moja_funkcja(double x)
{
    return sqrt(x);
}

double calka(function<double(double)> f, double a, double b, double dx = 1e-6)
{
    double znak = 1.0;

    if (a > b)
    {
        swap(a, b);
        znak = -1.0;
    }

    double wynik = 0.0;
    for (double x = a; x < b; x += dx)
    {
        wynik += f(x) * dx;
    }

    return wynik * znak;
}

double calka_rownolegle(int n_watkow, function<double(double)> f, double a, double b, double dx = 1e-6)
{
    vector<future<double>> podwyniki;

    for (int i = 0; i < n_watkow; i++)
    {
        const double szer_przedzialu = abs(b - a) / n_watkow;

        const double a_i = a + i * szer_przedzialu;
        const double b_i = a_i + szer_przedzialu;

        podwyniki.push_back(async(launch::async, [=]
                                  { return calka(f, a_i, b_i, dx); }));
    }

    double wynik = 0.0;
    for (auto &podwynik : podwyniki)
    {
        wynik += podwynik.get();
    }

    return wynik;
}

double zmierz_czas(function<void()> f)
{
    auto start = chrono::high_resolution_clock::now();
    f();
    auto stop = chrono::high_resolution_clock::now();
    return chrono::duration<double>(stop - start).count();
}

double calcValue(double value)
{
    return value / 4;
}

int main()
{
    const int N_WATOW = 10;
    constexpr double A = 1.0;
    constexpr double B = 100.0;
    cout << "Zadanie 1.\n";

    const double t_na_jednym = zmierz_czas([]
                                           { cout << "Na jednym watku: " << calka(moja_funkcja, A, B) << "\n"; });

    cout << "Czas na jednym watku " << t_na_jednym << "s\n\n";

    const double t_na_wielu = zmierz_czas([]
                                          { cout << "Na " << N_WATOW << " watkach: " << calka_rownolegle(N_WATOW, moja_funkcja, A, B) << "\n"; });
    cout << "Czas na wielu watkach: " << t_na_wielu << "s\n";

    cout << "Czas sie poprawil o: " << t_na_jednym / t_na_wielu << "s\n";

    cout << "Zadanie 2.\n";

    double value;
    cout << "Podaj kwote: ";
    cin >> value;

    packaged_task<double(double)> task(calcValue);
    auto res = task.get_future();

    thread t(move(task), value);

    t.join();
    cout << "Przeliczona wartosc: " << res.get() << "\n";
}