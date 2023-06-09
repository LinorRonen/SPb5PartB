
#include "MagicalContainer.hpp"
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <functional>

#include <cstdlib>
#include <memory>

namespace ariel
{
    // addElement(int element)
    void MagicalContainer::addElement(int element)
    {
        // Add the element to the elements vector
        elements.push_back(element);

        // 1) Clear the sortedElements, primeNumbers and cross vectors.
        // 2)Reserve space in the sortedElements, primeNumbers and cross vectors
        sortedElements.clear();
        sortedElements.reserve(elements.size());
        cross.clear();
        cross.reserve(elements.size());
        primeNumbers.clear();
        primeNumbers.reserve(elements.size());

        // Iterate over the elements vector
        for (int &primeElement : elements)
        {
            // Check if the element is prime and add its pointer to the primeNumbers vector
            if (isPrime(primeElement))
            {
                primeNumbers.push_back(&primeElement);
            }
        }

        // Sort the primeNumbers vector in ascending order
        std::sort(primeNumbers.begin(), primeNumbers.end(), [](const int *num1, const int *num2)
                  { return *num1 < *num2; });

        // Iterate over the elements vector
        for (int &sortedElement : elements)
        {
            // Add the pointer of each element to the sortedElements vector
            sortedElements.push_back(&sortedElement);
        }

        // Sort the sortedElements vector in ascending order
        std::sort(sortedElements.begin(), sortedElements.end(), [](const int *num1, const int *num2)
                  { return *num1 < *num2; });

        // Set the start and end indices for generating the cross vector
        size_t start = 0;
        size_t end = size() - 1;

        // Check if the container has only one element
        if (size() == 1)
        {
            cross.push_back(sortedElements.at(0));
        }
        else
        {
            // Generate the cross vector by alternating between the start and end indices
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

    // removeElement(int element)
    void MagicalContainer::removeElement(int element)
    {
        auto iter = std::find(elements.begin(), elements.end(), element);
        if (iter == elements.end())
        {
            throw std::runtime_error("The element is not found.");
        }
        elements.erase(iter);

        sortedElements.clear();
        sortedElements.reserve(elements.size());
        cross.clear();
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

    // Return the size of the container.
    size_t MagicalContainer::size() const
    {
        return elements.size();
    }

    // Return a copy of the sortedElements vector.
    std::vector<int *> MagicalContainer::getSortedElements() const
    {
        return sortedElements;
    }

    // Return the size of the sortedElements vector.
    size_t MagicalContainer::sizeSortedElements()
    {
        return sortedElements.size();
    }

    // Return a copy of the cross vector.
    std::vector<int *> MagicalContainer::getCross() const
    {
        return cross;
    }

    // Return the size of the cross vector.
    size_t MagicalContainer::sizeCross()
    {
        return cross.size();
    }

    // Return a copy of the primeNumbers vector.
    std::vector<int *> MagicalContainer::getPrimeNumbers() const
    {
        return primeNumbers;
    }

    // Return the size of the primeNumbers vector.
    size_t MagicalContainer::sizePrimeNumbers()
    {
        return primeNumbers.size();
    }

    // AscendingIterator iterator

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container)
        : container(&container), currentIndex(0) {}

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, size_t index)
        : container(&container), currentIndex(index) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
        : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator &&other) noexcept
        : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if (this != &other)
        {
            if (container != other.container)
            {
                throw std::runtime_error("Iterators are pointing to different containers");
            }
            currentIndex = other.currentIndex;
        }
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(AscendingIterator &&other) noexcept
    {
        if (this != &other)
        {
            container = other.container;
            currentIndex = other.currentIndex;
        }
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const MagicalIterator &other) const
    {
        const AscendingIterator *otherPtr = dynamic_cast<const AscendingIterator *>(&other);
        if (otherPtr == nullptr)
        {
            throw std::runtime_error("It is nullptr");
        }
        return *this == *otherPtr;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const MagicalIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::AscendingIterator::operator<(const MagicalIterator &other) const
    {
        const AscendingIterator *otherPtr = dynamic_cast<const AscendingIterator *>(&other);
        if (otherPtr == nullptr)
        {
            throw std::runtime_error("It is nullptr");
        }
        return *this < *otherPtr;
    }

    bool MagicalContainer::AscendingIterator::operator>(const MagicalIterator &other) const
    {
        const AscendingIterator *otherPtr = dynamic_cast<const AscendingIterator *>(&other);
        if (otherPtr == nullptr)
        {
            throw std::runtime_error("It is nullptr");
        }
        return *this > *otherPtr;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
    {
        return container == other.container && currentIndex == other.currentIndex;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        return currentIndex < other.currentIndex;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        return currentIndex > other.currentIndex;
    }

    int MagicalContainer::AscendingIterator::operator*() const
    {
        if (currentIndex >= container->sizeSortedElements())
        {
            throw std::runtime_error("Out of range");
        }
        return *container->getSortedElements()[currentIndex];
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        ++currentIndex;
        if (currentIndex > container->sizeSortedElements())
        {
            throw std::runtime_error("Out of range");
        }
        return *this;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    {
        return AscendingIterator(*container, 0);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const
    {
        return AscendingIterator(*container, container->sizeSortedElements());
    }

    // SideCrossIterator iterator

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
        : container(&container), currentIndex(0) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, size_t index)
        : container(&container), currentIndex(index) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
        : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator &&other) noexcept
        : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (this != &other)
        {
            if (container != other.container)
            {
                throw std::runtime_error("The iterators are pointing to different containers");
            }
            currentIndex = other.currentIndex;
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(SideCrossIterator &&other) noexcept
    {
        if (this != &other)
        {
            container = other.container;
            currentIndex = other.currentIndex;
        }
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const MagicalIterator &other) const
    {
        const SideCrossIterator &otherIterator = dynamic_cast<const SideCrossIterator &>(other);
        return currentIndex == otherIterator.currentIndex;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const MagicalIterator &other) const
    {
        const SideCrossIterator &otherIterator = dynamic_cast<const SideCrossIterator &>(other);
        return currentIndex != otherIterator.currentIndex;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const MagicalIterator &other) const
    {
        const SideCrossIterator &otherIterator = dynamic_cast<const SideCrossIterator &>(other);
        return currentIndex < otherIterator.currentIndex;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const MagicalIterator &other) const
    {
        const SideCrossIterator &otherIterator = dynamic_cast<const SideCrossIterator &>(other);
        return currentIndex > otherIterator.currentIndex;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {
        return currentIndex == other.currentIndex;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        return currentIndex != other.currentIndex;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        return currentIndex < other.currentIndex;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        return currentIndex > other.currentIndex;
    }

    int MagicalContainer::SideCrossIterator::operator*() const
    {
        return *(container->getCross()[currentIndex]);
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {
        ++currentIndex;
        if (currentIndex > container->sizeCross())
        {
            throw std::runtime_error("Out of range");
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {
        return SideCrossIterator(*container, 0);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const
    {
        return SideCrossIterator(*container, container->sizeCross());
    }

    // PrimeIterator

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container)
        : container(&container), currentIndex(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, size_t index)
        : container(&container), currentIndex(index) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
        : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator &&other) noexcept
        : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        if (this != &other)
        {
            if (container != other.container)
            {
                throw std::runtime_error("The iterators are pointing to different containers");
            }
            currentIndex = other.currentIndex;
        }
        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(PrimeIterator &&other) noexcept
    {
        if (this != &other)
        {
            container = other.container;
            currentIndex = other.currentIndex;
        }
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const MagicalIterator &other) const
    {
        const PrimeIterator &otherIterator = dynamic_cast<const PrimeIterator &>(other);
        return currentIndex == otherIterator.currentIndex;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const MagicalIterator &other) const
    {
        const PrimeIterator &otherIterator = dynamic_cast<const PrimeIterator &>(other);
        return currentIndex != otherIterator.currentIndex;
    }

    bool MagicalContainer::PrimeIterator::operator<(const MagicalIterator &other) const
    {
        const PrimeIterator &otherIterator = dynamic_cast<const PrimeIterator &>(other);
        return currentIndex < otherIterator.currentIndex;
    }

    bool MagicalContainer::PrimeIterator::operator>(const MagicalIterator &other) const
    {
        const PrimeIterator &otherIterator = dynamic_cast<const PrimeIterator &>(other);
        return currentIndex > otherIterator.currentIndex;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
    {
        return currentIndex == other.currentIndex;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
    {
        return currentIndex != other.currentIndex;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
    {
        return currentIndex < other.currentIndex;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        return currentIndex > other.currentIndex;
    }

    int MagicalContainer::PrimeIterator::operator*() const
    {
        return *(container->getPrimeNumbers()[currentIndex]);
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        ++currentIndex;
        if (currentIndex > container->sizePrimeNumbers())
        {
            throw std::runtime_error("Out of range");
        }
        return *this;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
    {
        return PrimeIterator(*container, 0);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const
    {
        return PrimeIterator(*container, container->sizePrimeNumbers());
    }

}
