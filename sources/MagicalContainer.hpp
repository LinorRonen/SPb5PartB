#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <functional>
#include <cstdlib>
#include <memory>

#include "MagicalIterator.hpp"
using namespace std;

namespace ariel
{
    class MagicalContainer
    {
    private:
        std::vector<int> elements;         // Vector of the elements
        std::vector<int *> sortedElements; // Vector of pointers to elements (for AscendingIterator)
        std::vector<int *> primeNumbers;   // Vector of pointers to elements (for SideCrossIterator)
        std::vector<int *> cross;          // Vector of pointers to prime numbers (for PrimeIterator)

        // isPrime() -  check if num is prime or not
        static bool isPrime(int num)
        {
            if (num < 2)
            {
                return false;
            }

            int sqrtNum = static_cast<int>(std::sqrt(num));
            for (int i = 2; i <= sqrtNum; ++i)
            {
                if (num % i == 0)
                {
                    return false;
                }
            }
            return true;
        }

    public:
        // Default constructor
        MagicalContainer() = default;

        // Add an element to the container
        void addElement(int element);

        // Remove an element from the container
        void removeElement(int element);

        // Get the size of the container
        size_t size() const;

        // Get a vector of pointers to the sortedElements vector
        std::vector<int *> getSortedElements() const;

        // Get the size of the sortedElements vector
        size_t sizeSortedElements();

        // Get a vector of pointers to the cross vector
        std::vector<int *> getCross() const;

        // Get the size of the cross vector
        size_t sizeCross();

        // Get a vector of pointers to the primeNumbers vector
        std::vector<int *> getPrimeNumbers() const;

        // Get the size of the primeNumbers vector
        size_t sizePrimeNumbers();

        class AscendingIterator : public MagicalIterator
        {
        private:
            // Pointer to the MagicalContainer object
            MagicalContainer *container;

            // Current index in the container
            size_t currentIndex;

        public:
            // Default constructor
            AscendingIterator() : container(nullptr), currentIndex(0) {}

            // Constructor with container reference
            AscendingIterator(MagicalContainer &container);

            // Constructor with container reference and index
            AscendingIterator(MagicalContainer &container, size_t index);

            // Default destructor
            ~AscendingIterator() override = default;

            // Copy constructor
            AscendingIterator(const AscendingIterator &other);

            // Move constructor
            AscendingIterator(AscendingIterator &&other) noexcept;

            // Copy assignment operator
            AscendingIterator &operator=(const AscendingIterator &other);

            // Move assignment operator
            AscendingIterator &operator=(AscendingIterator &&other) noexcept;

            // Equality comparison operator
            bool operator==(const MagicalIterator &other) const override;

            // Inequality comparison operator
            bool operator!=(const MagicalIterator &other) const override;

            // Less than comparison operator
            bool operator<(const MagicalIterator &other) const override;

            // Greater than comparison operator
            bool operator>(const MagicalIterator &other) const override;

            // Equality comparison operator for AscendingIterator
            bool operator==(const AscendingIterator &other) const;

            // Inequality comparison operator for AscendingIterator
            bool operator!=(const AscendingIterator &other) const;

            // Less than comparison operator for AscendingIterator
            bool operator<(const AscendingIterator &other) const;

            // Greater than comparison operator for AscendingIterator
            bool operator>(const AscendingIterator &other) const;

            // Dereference operator, returns the value at the current iterator position
            int operator*() const;

            // Pre-increment operator, moves the iterator to the next position
            AscendingIterator &operator++();

            // Returns the iterator to the beginning of the container
            AscendingIterator begin();

            // Returns the iterator to the end of the container
            AscendingIterator end() const;
        };

        class SideCrossIterator : public MagicalIterator
        {
        private:
            // Pointer to the MagicalContainer object
            MagicalContainer *container;

            // Current index in the container
            size_t currentIndex;

        public:
            // Default constructor
            SideCrossIterator() : container(nullptr), currentIndex(0) {}

            // Constructor with container reference
            SideCrossIterator(MagicalContainer &container);

            // Constructor with container reference and index
            SideCrossIterator(MagicalContainer &container, size_t index);

            // Default destructor
            ~SideCrossIterator() override = default;

            // Copy constructor
            SideCrossIterator(const SideCrossIterator &other);

            // Move constructor
            SideCrossIterator(SideCrossIterator &&other) noexcept;

            // Copy assignment operator
            SideCrossIterator &operator=(const SideCrossIterator &other);

            // Move assignment operator
            SideCrossIterator &operator=(SideCrossIterator &&other) noexcept;

            // Equality comparison operator
            bool operator==(const MagicalIterator &other) const override;

            // Inequality comparison operator
            bool operator!=(const MagicalIterator &other) const override;

            // Less than comparison operator
            bool operator<(const MagicalIterator &other) const override;

            // Greater than comparison operator
            bool operator>(const MagicalIterator &other) const override;

            // Equality comparison operator for SideCrossIterator
            bool operator==(const SideCrossIterator &other) const;

            // Inequality comparison operator for SideCrossIterator
            bool operator!=(const SideCrossIterator &other) const;

            // Less than comparison operator for SideCrossIterator
            bool operator<(const SideCrossIterator &other) const;

            // Greater than comparison operator for SideCrossIterator
            bool operator>(const SideCrossIterator &other) const;

            // Dereference operator, returns the value at the current iterator position
            int operator*() const;

            // Pre-increment operator, moves the iterator to the next position
            SideCrossIterator &operator++();

            // Returns the iterator to the beginning of the container
            SideCrossIterator begin();

            // Returns the iterator to the end of the container
            SideCrossIterator end() const;
        };

        class PrimeIterator : public MagicalIterator
        {
        private:
            // Pointer to the MagicalContainer object
            MagicalContainer *container;

            // Current index in the container
            size_t currentIndex; 

        public:
            // Default constructor
            PrimeIterator() : container(nullptr), currentIndex(0) {}

            // Constructor with container reference
            PrimeIterator(MagicalContainer &container);

            // Constructor with container reference and index
            PrimeIterator(MagicalContainer &container, size_t index);

            // Default destructor
            ~PrimeIterator() override = default;

            // Copy constructor
            PrimeIterator(const PrimeIterator &other);

            // Move constructor
            PrimeIterator(PrimeIterator &&other) noexcept;

            // Copy assignment operator
            PrimeIterator &operator=(const PrimeIterator &other);

            // Move assignment operator
            PrimeIterator &operator=(PrimeIterator &&other) noexcept;

            // Equality comparison operator
            bool operator==(const MagicalIterator &other) const override;

            // Inequality comparison operator
            bool operator!=(const MagicalIterator &other) const override;

            // Less than comparison operator
            bool operator<(const MagicalIterator &other) const override;

            // Greater than comparison operator
            bool operator>(const MagicalIterator &other) const override;

            // Equality comparison operator for PrimeIterator
            bool operator==(const PrimeIterator &other) const;

            // Inequality comparison operator for PrimeIterator
            bool operator!=(const PrimeIterator &other) const;

            // Less than comparison operator for PrimeIterator
            bool operator<(const PrimeIterator &other) const;

            // Greater than comparison operator for PrimeIterator
            bool operator>(const PrimeIterator &other) const;

            // Dereference operator, returns the value at the current iterator position
            int operator*() const;

            // Pre-increment operator, moves the iterator to the next position
            PrimeIterator &operator++();

            // Returns the iterator to the beginning of the container
            PrimeIterator begin();

            // Returns the iterator to the end of the container
            PrimeIterator end() const;
        };
    };
}
#endif // MAGICALCONTAINER_HPP
