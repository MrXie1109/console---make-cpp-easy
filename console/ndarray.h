/*

Copyright (c) 2026 MrXie1109

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <initializer_list>
#include <functional>
#include <memory>
#include "csexc.h"
#include "sfinae.h"

namespace console
{
    template <class T>
    class ndarray
    {
        std::vector<T> data_;
        std::vector<size_t> shape_;
        std::vector<size_t> stride_;

        class ndarrayView
        {
            T *data;
            size_t offset;
            size_t dims;
            const size_t *shape;
            const size_t *stride;

        public:
            ndarrayView(T *data,
                        size_t offset,
                        size_t dims,
                        const size_t *shape,
                        const size_t *stride)
                : data(data),
                  offset(offset),
                  dims(dims),
                  shape(shape),
                  stride(stride) {}

            const ndarrayView &operator=(const T &t)
            {
                if (dims != 0)
                    throw ndarray_error(std::to_string(dims) + " dims left");
                data[offset] = t;
                return *this;
            }

            const ndarrayView &operator=(T &&t)
            {
                if (dims != 0)
                    throw ndarray_error(std::to_string(dims) + " dims left");
                data[offset] = std::move(t);
                return *this;
            }

            operator T &()
            {
                if (dims != 0)
                    throw ndarray_error(std::to_string(dims) + " dims left");
                return data[offset];
            }

            operator const T &() const
            {
                if (dims != 0)
                    throw ndarray_error(std::to_string(dims) + " dims left");
                return data[offset];
            }

            ndarrayView operator[](size_t index)
            {
                if (dims == 0)
                    throw ndarray_error("No dims left");
                if (index >= *shape)
                    throw ndarray_error(
                        "index " + std::to_string(index) +
                        "out of range 0 ~ " + std::to_string(*shape));
                return ndarrayView{
                    data,
                    offset + index * *stride,
                    dims - 1,
                    shape + 1,
                    stride + 1};
            }

            const ndarrayView operator[](size_t index) const
            {
                if (dims == 0)
                    throw ndarray_error("No dims left");
                if (index >= *shape)
                    throw ndarray_error(
                        "index " + std::to_string(index) +
                        "out of range 0 ~ " + std::to_string(*shape));
                return ndarrayView{
                    data,
                    offset + index * *stride,
                    dims - 1,
                    shape + 1,
                    stride + 1};
            }

            friend std::ostream &operator<<(std::ostream &os,
                                            const ndarrayView &view)
            {
                if (view.dims == 0)
                {
                    return os << view.data[view.offset];
                }

                // 递归打印子视图
                os << "[";
                for (size_t i = 0; i < *view.shape; ++i)
                {
                    if (i > 0)
                        os << ", ";
                    ndarrayView subView(view.data,
                                        view.offset + i * *view.stride,
                                        view.dims - 1,
                                        view.shape + 1,
                                        view.stride + 1);
                    os << subView;
                }
                os << "]";
                return os;
            }
        };

    public:
        ndarray(std::initializer_list<size_t> init)
            : shape_(init), stride_(init.size())
        {
            if (init.size() == 0)
                return;
            size_t size_of_data = 1;
            for (size_t i : init)
            {
                size_of_data *= i;
            }
            data_ = std::vector<T>(size_of_data);
            size_t size_of_block = 1;
            for (size_t i = shape_.size() - 1; i < shape_.size(); i--)
            {
                stride_[i] = size_of_block;
                size_of_block *= shape_[i];
            }
        }

        template <typename Container>
        ndarray(std::initializer_list<size_t> init, Container &&cont,
                typename enable_if_container<Container>::type * = 0)
            : ndarray(init)
        {
            size_t copy_size = std::min(cont.size(), data_.size());
            auto it = cont.begin();
            for (size_t i = 0; i < copy_size; ++i)
                data_[i] = *it++;
        }

        template <typename F, typename... Args>
        ndarray(std::initializer_list<size_t> init, F &&f, Args &&...args,
                typename is_callable<F, T>::type * = 0)
            : ndarray(init)
        {
            for (T &item : data_)
                item = f(std::forward<Args>(args)...);
        }

        template <typename U>
        ndarray(std::initializer_list<size_t> init, U &&value,
                typename std::enable_if<
                    !is_container<U>::value &&
                    !is_callable<U, T>::value>::type * = 0)
            : ndarray(init)
        {
            for (T &item : data_)
                item = std::forward<U>(value);
        }

        ndarray(std::vector<size_t> init)
            : shape_(init), stride_(init.size())
        {
            if (init.size() == 0)
                return;
            size_t size_of_data = 1;
            for (size_t i : init)
            {
                size_of_data *= i;
            }
            data_ = std::vector<T>(size_of_data);
            size_t size_of_block = 1;
            for (size_t i = shape_.size() - 1; i < shape_.size(); i--)
            {
                stride_[i] = size_of_block;
                size_of_block *= shape_[i];
            }
        }

        template <typename Container>
        ndarray(std::vector<size_t> init, Container &&cont,
                typename enable_if_container<Container>::type * = 0)
            : ndarray(init)
        {
            size_t copy_size = std::min(cont.size(), data_.size());
            auto it = cont.begin();
            for (size_t i = 0; i < copy_size; ++i)
                data_[i] = *it++;
        }

        template <typename F, typename... Args>
        ndarray(std::vector<size_t> init, F &&f, Args &&...args,
                typename is_callable<F, T>::type * = 0)
            : ndarray(init)
        {
            for (T &item : data_)
                item = f(std::forward<Args>(args)...);
        }

        template <typename U>
        ndarray(std::vector<size_t> init, U &&value,
                typename std::enable_if<
                    !is_container<U>::value &&
                    !is_callable<U, T>::value>::type * = 0)
            : ndarray(init)
        {
            for (T &item : data_)
                item = std::forward<U>(value);
        }

        ndarrayView operator[](size_t index)
        {
            if (shape_.empty())
                throw ndarray_error("Empty array");
            if (index >= shape_[0])
                throw ndarray_error(
                    "index " + std::to_string(index) +
                    " out of range 0 ~ " + std::to_string(shape_[0]));
            return ndarrayView(data_.data(),
                               index * stride_[0],
                               shape_.size() - 1,
                               shape_.data() + 1,
                               stride_.data() + 1);
        }

        const ndarrayView operator[](size_t index) const
        {
            if (shape_.empty())
                throw ndarray_error("Empty array");
            if (index >= shape_[0])
                throw ndarray_error(
                    "index " + std::to_string(index) +
                    " out of range 0 ~ " + std::to_string(shape_[0]));
            return ndarrayView(const_cast<T *>(data_.data()),
                               index * stride_[0],
                               shape_.size() - 1,
                               shape_.data() + 1,
                               stride_.data() + 1);
        }

        template <typename... Args>
        T &at(Args... indices)
        {
            if (sizeof...(Args) != shape_.size())
                throw ndarray_error("Index count mismatch");
            size_t idxs[] = {size_t(indices)...};
            size_t offset = 0;
            for (size_t i = 0; i < shape_.size(); i++)
            {
                if (idxs[i] >= shape_[i])
                    throw ndarray_error("Index out of range");
                offset += idxs[i] * stride_[i];
            }
            return data_[offset];
        }

        template <typename... Args>
        const T &at(Args... indices) const
        {
            if (sizeof...(Args) != shape_.size())
                throw ndarray_error("Index count mismatch");
            size_t idxs[] = {size_t(indices)...};
            size_t offset = 0;
            for (size_t i = 0; i < shape_.size(); i++)
            {
                if (idxs[i] >= shape_[i])
                    throw ndarray_error("Index out of range");
                offset += idxs[i] * stride_[i];
            }
            return data_[offset];
        }

        template <typename... Args>
        void reshape(Args... indices)
        {
            size_t new_shape_arr[] = {size_t(indices)...};
            std::vector<size_t> new_shape(new_shape_arr, new_shape_arr + sizeof...(indices));
            size_t new_size = 1;
            for (size_t dim : new_shape)
                new_size *= dim;
            if (new_size != data_.size())
                throw ndarray_error("mismatched size");
            shape_ = new_shape;
            stride_.resize(shape_.size());
            size_t size_of_block = 1;
            for (size_t i = shape_.size() - 1; i < shape_.size(); i--)
            {
                stride_[i] = size_of_block;
                size_of_block *= shape_[i];
            }
        }

        const std::vector<size_t> &shape() const { return shape_; }

        const std::vector<size_t> &stride() const { return stride_; }

        size_t size() const { return data_.size(); }

        size_t dims() const { return shape_.size(); }

        bool empty() const { return data_.empty(); }

        ndarray operator+(const T &scalar) const
        {
            ndarray result(shape_);
            for (size_t i = 0; i < data_.size(); ++i)
            {
                result.data_[i] = data_[i] + scalar;
            }
            return result;
        }

        ndarray operator-(const T &scalar) const
        {
            ndarray result(shape_);
            for (size_t i = 0; i < data_.size(); ++i)
            {
                result.data_[i] = data_[i] - scalar;
            }
            return result;
        }

        ndarray operator*(const T &scalar) const
        {
            ndarray result(shape_);
            for (size_t i = 0; i < data_.size(); ++i)
            {
                result.data_[i] = data_[i] * scalar;
            }
            return result;
        }

        ndarray operator/(const T &scalar) const
        {
            ndarray result(shape_);
            for (size_t i = 0; i < data_.size(); ++i)
            {
                result.data_[i] = data_[i] / scalar;
            }
            return result;
        }

        ndarray operator+(const ndarray &other) const
        {
            if (shape_ != other.shape_)
                throw ndarray_error("Shape mismatch");

            ndarray result(shape_);
            for (size_t i = 0; i < data_.size(); ++i)
            {
                result.data_[i] = data_[i] + other.data_[i];
            }
            return result;
        }

        ndarray operator-(const ndarray &other) const
        {
            if (shape_ != other.shape_)
                throw ndarray_error("Shape mismatch");

            ndarray result(shape_);
            for (size_t i = 0; i < data_.size(); ++i)
            {
                result.data_[i] = data_[i] - other.data_[i];
            }
            return result;
        }

        ndarray operator*(const ndarray &other) const
        {
            if (shape_ != other.shape_)
                throw ndarray_error("Shape mismatch");

            ndarray result(shape_);
            for (size_t i = 0; i < data_.size(); ++i)
            {
                result.data_[i] = data_[i] * other.data_[i];
            }
            return result;
        }

        ndarray operator/(const ndarray &other) const
        {
            if (shape_ != other.shape_)
                throw ndarray_error("Shape mismatch");

            ndarray result(shape_);
            for (size_t i = 0; i < data_.size(); ++i)
            {
                result.data_[i] = data_[i] / other.data_[i];
            }
            return result;
        }

        ndarray &operator+=(const T &scalar)
        {
            for (auto &val : data_)
                val += scalar;
            return *this;
        }

        ndarray &operator-=(const T &scalar)
        {
            for (auto &val : data_)
                val -= scalar;
            return *this;
        }

        ndarray &operator*=(const T &scalar)
        {
            for (auto &val : data_)
                val *= scalar;
            return *this;
        }

        ndarray &operator/=(const T &scalar)
        {
            for (auto &val : data_)
                val /= scalar;
            return *this;
        }

        ndarray &operator+=(const ndarray &other)
        {
            if (shape_ != other.shape_)
                throw ndarray_error("Shape mismatch");
            for (size_t i = 0; i < data_.size(); ++i)
            {
                data_[i] += other.data_[i];
            }
            return *this;
        }

        ndarray &operator-=(const ndarray &other)
        {
            if (shape_ != other.shape_)
                throw ndarray_error("Shape mismatch");
            for (size_t i = 0; i < data_.size(); ++i)
            {
                data_[i] -= other.data_[i];
            }
            return *this;
        }

        ndarray &operator*=(const ndarray &other)
        {
            if (shape_ != other.shape_)
                throw ndarray_error("Shape mismatch");
            for (size_t i = 0; i < data_.size(); ++i)
            {
                data_[i] *= other.data_[i];
            }
            return *this;
        }

        ndarray &operator/=(const ndarray &other)
        {
            if (shape_ != other.shape_)
                throw ndarray_error("Shape mismatch");
            for (size_t i = 0; i < data_.size(); ++i)
            {
                data_[i] /= other.data_[i];
            }
            return *this;
        }

        ndarray operator-() const
        {
            ndarray result(shape_);
            for (size_t i = 0; i < data_.size(); ++i)
            {
                result.data_[i] = -data_[i];
            }
            return result;
        }

        ndarray operator+() const
        {
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const ndarray &self)
        {
            if (self.empty())
                return os << "[]";
            std::function<void(size_t, size_t, size_t)> print_dim;
            print_dim = [&](size_t dim, size_t start, size_t end)
            {
                if (dim == self.dims() - 1)
                {
                    os << "[";
                    for (size_t i = 0; i < self.shape_[dim]; ++i)
                    {
                        if (i > 0)
                            os << ", ";
                        os << self.data_[start + i * self.stride_[dim]];
                    }
                    os << "]";
                }
                else
                {
                    os << "[";
                    for (size_t i = 0; i < self.shape_[dim]; ++i)
                    {
                        if (i > 0)
                            os << ", ";
                        print_dim(dim + 1,
                                  start + i * self.stride_[dim],
                                  end);
                    }
                    os << "]";
                }
            };
            print_dim(0, 0, self.size());
            return os;
        }
    };
}
