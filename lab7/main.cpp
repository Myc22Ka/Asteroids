#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <concepts>
#include <iterator>

// Concept to check if a type is iterable
template <typename T>
concept Iterable = requires(T t) {
    { std::begin(t) } -> std::input_iterator;
    { std::end(t) } -> std::input_iterator;
};

// Find the maximum element in a container
template <Iterable Container>
auto find_max(const Container &container)
{
    return *std::max_element(std::begin(container), std::end(container));
}

// Find the minimum element in a container
template <Iterable Container>
auto find_min(const Container &container)
{
    return *std::min_element(std::begin(container), std::end(container));
}

// Concept to check if a type is an integral type
template <typename T>
concept Integral = std::is_integral_v<T>;

// Check if a number is prime
template <Integral T>
bool is_prime(T num)
{
    if (num <= 1)
        return false;
    for (T i = 2; i * i <= num; ++i)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

// Concept to check if a type has a size() method
template <typename T>
concept HasSize = requires(T t) {
    { t.size() } -> std::convertible_to<std::size_t>;
};

// A class representing a vector with a size() method
class Vector
{
public:
    std::vector<int> data;

    Vector(std::initializer_list<int> init) : data(init) {}

    std::size_t size() const
    {
        return data.size();
    }
};

// A class representing a list with a size() method
class Lista
{
public:
    std::list<int> data;

    Lista(std::initializer_list<int> init) : data(init) {}

    std::size_t size() const
    {
        return data.size();
    }
};

// Compare the sizes of two containers
template <HasSize T, HasSize U>
bool compare_size(const T &a, const U &b)
{
    return a.size() == b.size();
}

int main()
{
    // Finding min and max in containers
    std::vector<int> vectorExample = {1, 3, 13, 19, 8};
    std::list<double> listExample = {1.1, 5.9, 5.3, 2.1};

    std::cout << "Max in vector: " << find_max(vectorExample) << std::endl;
    std::cout << "Max in list: " << find_max(listExample) << std::endl;
    std::cout << "Min in vector: " << find_min(vectorExample) << std::endl;
    std::cout << "Min in list: " << find_min(listExample) << std::endl;
    std::cout << std::endl;

    // Checking if numbers are prime
    std::cout << "Is 7 a prime number? " << std::boolalpha << is_prime(7) << std::endl;
    std::cout << "Is 15 a prime number? " << std::boolalpha << is_prime(15) << std::endl;
    std::cout << std::endl;

    // Comparing sizes of containers
    Vector vectorExample2 = {1, 2, 3, 4, 5};
    Lista listExample2 = {10, 20, 30, 40, 50};
    std::cout << "Are sizes equal? " << std::boolalpha << compare_size(vectorExample2, listExample2) << std::endl;
    std::cout << std::endl;

    return 0;
}
