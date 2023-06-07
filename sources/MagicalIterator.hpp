#pragma once

namespace ariel
{
    class MagicalIterator
    {
    public:
        MagicalIterator() = default;
        virtual ~MagicalIterator() = default;
        MagicalIterator(const MagicalIterator &other) = default;
        MagicalIterator(MagicalIterator &&other) = default;
        MagicalIterator &operator=(const MagicalIterator &other) = default;
        MagicalIterator &operator=(MagicalIterator &&other) = default;

        virtual bool operator==(const MagicalIterator &other) const = 0;
        virtual bool operator!=(const MagicalIterator &other) const = 0;
        virtual bool operator<(const MagicalIterator &other) const = 0;
        virtual bool operator>(const MagicalIterator &other) const = 0;
    };
} // namespace ariel
