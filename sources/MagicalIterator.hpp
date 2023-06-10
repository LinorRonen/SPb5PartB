#pragma once

namespace ariel
{
    class MagicalIterator
    {
    public:
        // Default constructor
        MagicalIterator() = default;

        // Default destructor
        virtual ~MagicalIterator() = default;

        // Copy constructor
        MagicalIterator(const MagicalIterator &other) = default;

        // Move constructor
        MagicalIterator(MagicalIterator &&other) = default;

        // Copy assignment operator
        MagicalIterator &operator=(const MagicalIterator &other) = default;

        // Move assignment operator
        MagicalIterator &operator=(MagicalIterator &&other) = default;

        // Less than comparison operator
        virtual bool operator<(const MagicalIterator &other) const = 0;

        // Greater than comparison operator
        virtual bool operator>(const MagicalIterator &other) const = 0;

        // Equality comparison operator
        virtual bool operator==(const MagicalIterator &other) const = 0;

        // Inequality comparison operator
        virtual bool operator!=(const MagicalIterator &other) const = 0;
    };
} // namespace ariel
