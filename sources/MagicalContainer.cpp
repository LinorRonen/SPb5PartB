
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
    void MagicalContainer::addElement(int element)
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

        std::sort(primeNumbers.begin(), primeNumbers.end(), [](const int *num1, const int *num2)
                  { return *num1 < *num2; });

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

    void MagicalContainer::removeElement(int element)
    {
        auto iter = std::find(elements.begin(), elements.end(), element);
        if (iter == elements.end())
        {
            throw std::runtime_error("The element is not found");
        }
        elements.erase(iter);

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

    size_t MagicalContainer::size() const
    {
        return elements.size();
    }

    std::vector<int *> MagicalContainer::getSortedElements() const
    {
        return sortedElements;
    }

    size_t MagicalContainer::sizeSortedElements()
    {
        return sortedElements.size();
    }

    std::vector<int *> MagicalContainer::getCross() const
    {
        return cross;
    }

    size_t MagicalContainer::sizeCross()
    {
        return cross.size();
    }

    std::vector<int *> MagicalContainer::getPrimeNumbers() const
    {
        return primeNumbers;
    }

    size_t MagicalContainer::sizePrimeNumbers()
    {
        return primeNumbers.size();
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container)
        : container(container), currentIndex(0) {}

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, size_t index)
        : container(container), currentIndex(index) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
        : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator &&other) noexcept
        : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
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
        return &container == &other.container && currentIndex == other.currentIndex;
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
        if (currentIndex >= container.sizeSortedElements())
        {
            throw std::runtime_error("Out of range");
        }
        return *container.getSortedElements()[currentIndex];
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        ++currentIndex;
        if (currentIndex > container.sizeSortedElements())
        {
            throw std::runtime_error("Out of range");
        }
        return *this;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    {
        return *this;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const
    {
        return AscendingIterator(container, container.sizeSortedElements());
    }
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
        : container(container), currentIndex(0) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, size_t index)
        : container(container), currentIndex(index) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
        : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator &&other) noexcept
        : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
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

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(SideCrossIterator &&other) noexcept
    {
        if (this != &other)
        {
            container = std::move(other.container);
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
        return *(container.getCross()[currentIndex]);
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {
        ++currentIndex;
        if (currentIndex > container.getCross().size())
        {
            throw std::runtime_error("Out of range");
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {
        return SideCrossIterator(container, 0);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const
    {
        return SideCrossIterator(container, container.sizeCross());
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container)
        : container(container), currentIndex(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, size_t index)
        : container(container), currentIndex(index) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
        : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator &&other) noexcept
        : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
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

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(PrimeIterator &&other) noexcept
    {
        if (this != &other)
        {
            container = std::move(other.container);
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
        return *(container.getPrimeNumbers()[currentIndex]);
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        ++currentIndex;
        if (currentIndex > container.sizePrimeNumbers())
        {
            throw std::runtime_error("Out of range");
        }
        return *this;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
    {
        return *this;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const
    {
        return PrimeIterator(container, container.sizePrimeNumbers());
    }

}
