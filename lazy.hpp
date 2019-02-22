#ifndef LAZY_HPP
#define LAZY_HPP

#include <optional>
#include <functional>

template <typename In, typename Out, typename PrevIter>
struct MapIterator
{
    std::function<Out (const In &)> fn;
    PrevIter prev;

    std::optional<Out> next()
    {
        auto next_item = prev.next();

        if (next_item != std::nullopt)
        {
            return fn(*next_item);
        }

        return std::nullopt;
    }

    void for_each(const std::function<void (int)> &fn)
    {
        for (auto iter = next(); iter != std::nullopt; iter = next())
        {
            fn(*iter);
        }
    }
};

template <typename T, typename PrevIter>
struct FilterIterator
{
    std::function<bool (const T &)> test;
    PrevIter prev;

    std::optional<T> next()
    {
        for (auto iter = prev.next(); iter != std::nullopt; iter = prev.next())
        {
            if (test(*iter))
            {
                return iter;
            }
        }

        return std::nullopt;
    }

    template <typename In, typename Out>
    MapIterator<In, Out, FilterIterator> map(const std::function<Out (const In &)> &fn)
    {
        MapIterator<In, Out, FilterIterator> next;

        next.fn = fn;
        next.prev = *this;

        return next;
    }
};

struct RangeIterator
{
    int start = 0;
    int end = 0;

    std::optional<int> next()
    {
        if (start >= end) return {};

        return start++;
    }

    template <typename In, typename Out>
    MapIterator<In, Out, RangeIterator> map(const std::function<Out (const In &)> &fn)
    {
        MapIterator<In, Out, RangeIterator> iter;

        iter.fn = fn;
        iter.prev = *this;

        return iter;
    }

    template <typename T>
    FilterIterator<T, RangeIterator> filter(const std::function<bool (const T &)> &fn)
    {
        FilterIterator<T, RangeIterator> iter;

        iter.test = fn;
        iter.prev = *this;

        return iter;
    }

    void for_each(const std::function<void (int)> &fn)
    {
        for (auto iter = next(); iter != std::nullopt; iter = next())
        {
            fn(*iter);
        }
    }
};

RangeIterator range(int start, int end)
{
    RangeIterator range;

    range.start = start;
    range.end = end;

    return range;
}

#endif // LAZY_HPP
