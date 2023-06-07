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

        /*void updateSortedElements()
        {
            sortedElements.clear();
            sortedElements.reserve(elements.size());
            for (int &element : elements)
            {
                sortedElements.push_back(&element);
            }
            std::sort(sortedElements.begin(), sortedElements.end(), [](const int *num1, const int *num2)
                      { return *num1 < *num2; });
        }*/

        /*void updatePrimeNumbers()
        {
            primeNumbers.clear();
            for (int &num : elements)
            {
                if (isPrime(num))
                {
                    primeNumbers.push_back(&num);
                }
            }
            std::sort(primeNumbers.begin(), primeNumbers.end(), [](const int *num1, const int *num2)
                      { return *num1 < *num2; });
        }*/

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
        // addElement(int element)

        void addElement(int element)
        {
            elements.push_back(element);

            sortedElements.clear();
            cross.clear();

            sortedElements.reserve(elements.size());
            cross.reserve(elements.size());

            primeNumbers.clear();
            primeNumbers.reserve(elements.size());

            for (int &primeElement : elements)
            {
                if (isPrime(primeElement))
                {
                    primeNumbers.push_back(&primeElement);
                }
            }

            for (int &sortedElement : elements)
            {
                sortedElements.push_back(&sortedElement);
            }

            std::sort(sortedElements.begin(), sortedElements.end(), [](const int *num1, const int *num2)
                      { return *num1 < *num2; });
            size_t start = 0;
            size_t end = size() - 1;

            if (size() == 1)
            {
                cross.push_back(sortedElements.at(0));
            }

            else
            {
                while (start <= end && end != 0)
                {
                    cross.push_back(sortedElements.at(start));

                    if (start != end)
                    {
                        cross.push_back(sortedElements.at(end));
                    }

                    start++;
                    end--;
                }
            }
        }

        void removeElement(int element)
        {
            auto iter = std::find(elements.begin(), elements.end(), element);
            if (iter == elements.end())
            {
                throw std::runtime_error("The element is not found");
            }
            elements.erase(iter);
        }

        // sizeElements()
        size_t size() const
        {
            return elements.size();
        }

        // getSortedElements()
        std::vector<int *> getSortedElements() const
        {
            return this->sortedElements;
        }

        // sizeSortedElements()
        size_t sizeSortedElements()
        {
            return this->sortedElements.size();
        }

        // getCross()
        std::vector<int *> getCross() const
        {
            return this->cross;
        }

        // sizeCross()
        size_t sizeCross()
        {
            return this->cross.size();
        }

        // getPrimeNumbers()
        std::vector<int *> getPrimeNumbers() const
        {
            return this->primeNumbers;
        }

        // sizePrimeNumbers()
        size_t sizePrimeNumbers()
        {
            return this->primeNumbers.size();
        }

        /*std::vector<int> &get_vector()
        {
            return elements;
        }*/
        /*void Setelements(std::vector<int> &container)
        {
            elements = container;
        }*/

        class AscendingIterator : public MagicalIterator
        {
        private:
            MagicalContainer &container;

            size_t currentIndex;

        public:
            AscendingIterator(MagicalContainer &container) : container(container), currentIndex(0) {}

            AscendingIterator(MagicalContainer &container, size_t index) : container(container), currentIndex(index) {}

            ~AscendingIterator() override = default;

            AscendingIterator(const AscendingIterator &other) : container(other.container), currentIndex(other.currentIndex) {}

            AscendingIterator(AscendingIterator &&other) noexcept : container(other.container), currentIndex(other.currentIndex) {}

            AscendingIterator &operator=(const AscendingIterator &other)
            {
                if (this != &other)
                {
                    if (&container != &other.container)
                    {
                        throw std::runtime_error("Iterators are pointing to different containers");
                    }
                    currentIndex = other.currentIndex;
                }
                return *this;
            }

            AscendingIterator &operator=(AscendingIterator &&other) noexcept
            {
                if (this != &other)
                {
                    container = other.container;
                    currentIndex = other.currentIndex;
                }
                return *this;
            }

            bool operator==(const MagicalIterator &other) const override
            {
                const AscendingIterator *otherPtr = dynamic_cast<const AscendingIterator *>(&other);
                if (otherPtr == nullptr)
                {
                    throw std::runtime_error("It is nullptr");
                }
                return *this == *otherPtr;
            }

            // operator!=(const MagicalIterator &other)
            bool operator!=(const MagicalIterator &other) const override
            {
                return !(*this == other);
            }

            // operator<(const MagicalIterator &other)
            bool operator<(const MagicalIterator &other) const override
            {
                const AscendingIterator *otherPtr = dynamic_cast<const AscendingIterator *>(&other);
                if (otherPtr == nullptr)
                {
                    throw std::runtime_error("It is nullptr");
                }
                return *this < *otherPtr;
            }

            // operator>(const MagicalIterator &other)
            bool operator>(const MagicalIterator &other) const override
            {
                const AscendingIterator *otherPtr = dynamic_cast<const AscendingIterator *>(&other);
                if (otherPtr == nullptr)
                {
                    throw std::runtime_error("It is nullptr");
                }
                return *this > *otherPtr;
            }

            // operator==(const AscendingIterator &other)
            bool operator==(const AscendingIterator &other) const
            {
                return &container == &other.container && currentIndex == other.currentIndex;
            }

            // operator!=(const AscendingIterator &other)
            bool operator!=(const AscendingIterator &other) const
            {
                return !(*this == other);
            }

            // operator<(const AscendingIterator &other)
            bool operator<(const AscendingIterator &other) const
            {
                return currentIndex < other.currentIndex;
            }

            // operator>(const AscendingIterator &other)
            bool operator>(const AscendingIterator &other) const
            {
                return currentIndex > other.currentIndex;
            }

            // operator*()
            int operator*() const
            {
                if (currentIndex >= container.sizeSortedElements())
                {
                    throw std::runtime_error("Out of range");
                }
                return *container.getSortedElements()[currentIndex];
            }

            // operator++()
            AscendingIterator &operator++()
            {
                ++currentIndex;
                if (currentIndex > container.sizeSortedElements())
                {
                    throw std::runtime_error("Out of range");
                }
                return *this;
            }

            // begin()
            AscendingIterator begin()
            {
                return *this;
            }

            // end()
            AscendingIterator end() const
            {
                return AscendingIterator(container, container.sizeSortedElements());
            }
        };

        class SideCrossIterator : public MagicalIterator
        {
        private:
            MagicalContainer &container;

            size_t currentIndex;

        public:
            SideCrossIterator(MagicalContainer &container) : container(container), currentIndex(0) {}

            SideCrossIterator(MagicalContainer &container, size_t index) : container(container), currentIndex(index) {}

            ~SideCrossIterator() override = default;

            SideCrossIterator(const SideCrossIterator &other) : container(other.container), currentIndex(other.currentIndex) {}

            SideCrossIterator(SideCrossIterator &&other) noexcept : container(other.container), currentIndex(other.currentIndex) {}

            SideCrossIterator &operator=(const SideCrossIterator &other)
            {
                if (this != &other)
                {
                    if (&container != &other.container)
                    {
                        throw std::runtime_error("The iterators are pointing to different containers");
                    }
                    currentIndex = other.currentIndex;
                }

                return *this;
            }

            SideCrossIterator &operator=(SideCrossIterator &&other) noexcept
            {
                if (this != &other)
                {
                    container = std::move(other.container);
                    currentIndex = other.currentIndex;
                }
                return *this;
            }

            bool operator==(const MagicalIterator &other) const override
            {
                const SideCrossIterator &otherIterator = dynamic_cast<const SideCrossIterator &>(other);
                return currentIndex == otherIterator.currentIndex;
            }

            bool operator!=(const MagicalIterator &other) const override
            {
                const SideCrossIterator &otherIterator = dynamic_cast<const SideCrossIterator &>(other);
                return currentIndex != otherIterator.currentIndex;
            }

            bool operator<(const MagicalIterator &other) const override
            {
                const SideCrossIterator &otherIterator = dynamic_cast<const SideCrossIterator &>(other);
                return currentIndex < otherIterator.currentIndex;
            }

            bool operator>(const MagicalIterator &other) const override
            {
                const SideCrossIterator &otherIterator = dynamic_cast<const SideCrossIterator &>(other);
                return currentIndex > otherIterator.currentIndex;
            }

            bool operator==(const SideCrossIterator &other) const
            {
                return currentIndex == other.currentIndex;
            }

            bool operator!=(const SideCrossIterator &other) const
            {
                return currentIndex != other.currentIndex;
            }

            bool operator<(const SideCrossIterator &other) const
            {
                return currentIndex < other.currentIndex;
            }

            bool operator>(const SideCrossIterator &other) const
            {
                return currentIndex > other.currentIndex;
            }

            int operator*() const
            {
                return *(container.getCross()[currentIndex]);
            }

            SideCrossIterator &operator++()
            {
                ++currentIndex;
                if (currentIndex > container.getCross().size())
                {
                    throw std::runtime_error("Out of range");
                }
                return *this;
            }
            // begin()
            SideCrossIterator begin()
            {
                return SideCrossIterator(container, 0);
            }

            // end()
            SideCrossIterator end() const
            {
                return SideCrossIterator(container, container.sizeCross());
            }
        };

        class PrimeIterator : public MagicalIterator
        {

        private:
            MagicalContainer &container;

            size_t currentIndex;

        public:
            PrimeIterator(MagicalContainer &container) : container(container), currentIndex(0) {}

            PrimeIterator(MagicalContainer &container, size_t index) : container(container), currentIndex(index) {}

            ~PrimeIterator() override = default;

            PrimeIterator(const PrimeIterator &other) : container(other.container), currentIndex(other.currentIndex) {}

            PrimeIterator(PrimeIterator &&other) noexcept : container(other.container), currentIndex(other.currentIndex) {}

            PrimeIterator &operator=(const PrimeIterator &other)
            {

                if (this != &other)
                {
                    if (&container != &other.container)
                    {
                        throw std::runtime_error("The iterators are pointing to different containers");
                    }
                    currentIndex = other.currentIndex;
                }
                return *this;
            }

            PrimeIterator &operator=(PrimeIterator &&other) noexcept
            {
                if (this != &other)
                {
                    container = std::move(other.container);
                    currentIndex = other.currentIndex;
                }
                return *this;
            }

            bool operator==(const MagicalIterator &other) const override
            {
                const PrimeIterator &otherIterator = dynamic_cast<const PrimeIterator &>(other);
                return currentIndex == otherIterator.currentIndex;
            }

            bool operator!=(const MagicalIterator &other) const override
            {
                const PrimeIterator &otherIterator = dynamic_cast<const PrimeIterator &>(other);
                return currentIndex != otherIterator.currentIndex;
            }

            bool operator<(const MagicalIterator &other) const override
            {
                const PrimeIterator &otherIterator = dynamic_cast<const PrimeIterator &>(other);
                return currentIndex < otherIterator.currentIndex;
            }

            bool operator>(const MagicalIterator &other) const override
            {
                const PrimeIterator &otherIterator = dynamic_cast<const PrimeIterator &>(other);
                return currentIndex > otherIterator.currentIndex;
            }

            bool operator==(const PrimeIterator &other) const
            {
                return currentIndex == other.currentIndex;
            }

            bool operator!=(const PrimeIterator &other) const
            {
                return currentIndex != other.currentIndex;
            }

            bool operator<(const PrimeIterator &other) const
            {
                return currentIndex < other.currentIndex;
            }

            bool operator>(const PrimeIterator &other) const
            {
                return currentIndex > other.currentIndex;
            }

            int operator*() const
            {
                return *(container.getPrimeNumbers()[currentIndex]);
            }

            PrimeIterator &operator++()
            {
                ++currentIndex;
                if (currentIndex > container.sizePrimeNumbers())
                {
                    throw std::runtime_error("Out of range");
                }
                return *this;
            }

            PrimeIterator begin()
            {
                // return PrimeIterator(container, 0);
                return *this;
            }

            PrimeIterator end() const
            {
                return PrimeIterator(container, container.sizePrimeNumbers());
            }
        };
    };
}
#endif // MAGICALCONTAINER_HPP
