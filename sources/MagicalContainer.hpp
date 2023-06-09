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
        void addElement(int element);
        void removeElement(int element);
        size_t size() const;
        std::vector<int *> getSortedElements() const;
        size_t sizeSortedElements();
        std::vector<int *> getCross() const;
        size_t sizeCross();
        std::vector<int *> getPrimeNumbers() const;
        size_t sizePrimeNumbers();

        class AscendingIterator : public MagicalIterator
        {
        private:
            MagicalContainer &container;
            size_t currentIndex;

        public:
            AscendingIterator(MagicalContainer &container);
            AscendingIterator(MagicalContainer &container, size_t index);
            ~AscendingIterator() override = default;
            AscendingIterator(const AscendingIterator &other);
            AscendingIterator(AscendingIterator &&other) noexcept;
            AscendingIterator &operator=(const AscendingIterator &other);
            AscendingIterator &operator=(AscendingIterator &&other) noexcept;

            bool operator==(const MagicalIterator &other) const override;
            bool operator!=(const MagicalIterator &other) const override;
            bool operator<(const MagicalIterator &other) const override;
            bool operator>(const MagicalIterator &other) const override;

            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            bool operator>(const AscendingIterator &other) const;

            int operator*() const;
            AscendingIterator &operator++();
            AscendingIterator begin();
            AscendingIterator end() const;
        };

        class SideCrossIterator : public MagicalIterator
        {
        private:
            MagicalContainer &container;
            size_t currentIndex;

        public:
            SideCrossIterator(MagicalContainer &container);
            SideCrossIterator(MagicalContainer &container, size_t index);
            ~SideCrossIterator() override = default;
            SideCrossIterator(const SideCrossIterator &other);
            SideCrossIterator(SideCrossIterator &&other) noexcept;
            SideCrossIterator &operator=(const SideCrossIterator &other);
            SideCrossIterator &operator=(SideCrossIterator &&other) noexcept;

            bool operator==(const MagicalIterator &other) const override;
            bool operator!=(const MagicalIterator &other) const override;
            bool operator<(const MagicalIterator &other) const override;
            bool operator>(const MagicalIterator &other) const override;

            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;

            int operator*() const;
            SideCrossIterator &operator++();
            SideCrossIterator begin();
            SideCrossIterator end() const;
        };

        class PrimeIterator : public MagicalIterator
        {
        private:
            MagicalContainer &container;
            size_t currentIndex;

        public:
            PrimeIterator(MagicalContainer &container);
            PrimeIterator(MagicalContainer &container, size_t index);
            ~PrimeIterator() override = default;
            PrimeIterator(const PrimeIterator &other);
            PrimeIterator(PrimeIterator &&other) noexcept;
            PrimeIterator &operator=(const PrimeIterator &other);
            PrimeIterator &operator=(PrimeIterator &&other) noexcept;

            bool operator==(const MagicalIterator &other) const override;
            bool operator!=(const MagicalIterator &other) const override;
            bool operator<(const MagicalIterator &other) const override;
            bool operator>(const MagicalIterator &other) const override;

            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            bool operator>(const PrimeIterator &other) const;

            int operator*() const;
            PrimeIterator &operator++();
            PrimeIterator begin();
            PrimeIterator end() const;
        };
    };
}
#endif // MAGICALCONTAINER_HPP
