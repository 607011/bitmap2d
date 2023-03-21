#include <algorithm>
#include <array>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <utility>
#include <type_traits>

template <size_t Rows, size_t Cols, typename BaseT = size_t>
class bitmap2d
{
public:
    bitmap2d()
    {
        static_assert(std::is_integral<BaseT>::value, "Integral required for BaseT.");
        static_assert(std::is_unsigned<BaseT>::value, "Unsigned integral required for BaseT.");
        static_assert(Rows > 0 && Cols > 0, "Number of rows and columns must be greater than 0.");
        std::fill(data_.begin(), data_.end(), 0);
    }

    void set(size_t row, size_t col, bool val)
    {
#ifndef BITMAP_UNCHECKED
        if (row > Rows)
        {
            throw std::out_of_range("row is out of range. max: " + std::to_string(Rows) + "; is: " + std::to_string(row));
        }
        if (col > Cols)
        {
            throw std::out_of_range("col is out of range. max: " + std::to_string(Cols) + "; is: " + std::to_string(col));
        }
#endif
        size_t const idx = (row * Cols + col) / (sizeof(BaseT) * CHAR_BIT);
        size_t const shift = (row * Cols + col) % (sizeof(BaseT) * CHAR_BIT);
        if (val)
        {
            data_[idx] |= static_cast<BaseT>(1) << shift;
        }
        else
        {
            data_[idx] &= ~(static_cast<BaseT>(1) << shift);
        }
    }

    inline void set(size_t row, size_t col)
    {
        set(row, col, true);
    }

    inline void unset(size_t row, size_t col)
    {
        set(row, col, false);
    }

    bool get(size_t row, size_t col) const
    {
#ifndef BITMAP_UNCHECKED
        if (row > Rows)
        {
            throw std::out_of_range("row is out of range. max: " + std::to_string(Rows) + "; is: " + std::to_string(row));
        }
        if (col > Cols)
        {
            throw std::out_of_range("col is out of range. max: " + std::to_string(Cols) + "; is: " + std::to_string(col));
        }
#endif
        size_t const idx = (row * Cols + col) / (sizeof(BaseT) * CHAR_BIT);
        size_t const shift = (row * Cols + col) % (sizeof(BaseT) * CHAR_BIT);
        BaseT result = data_.at(idx) & (static_cast<BaseT>(1) << shift);
        return result != static_cast<BaseT>(0);
    }

    inline constexpr size_t rows() const noexcept
    {
        return Rows;
    }

    inline constexpr size_t cols() const noexcept
    {
        return Cols;
    }

    inline BaseT const *data() const noexcept
    {
        return data_.data();
    }

    inline constexpr size_t size() const noexcept
    {
        return data_.size();
    }

private:
    std::array<BaseT, std::max(1UL, Rows *Cols / (sizeof(BaseT) * CHAR_BIT))> data_;
};
