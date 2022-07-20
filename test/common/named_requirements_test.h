/*
    Copyright (c) 2022 Intel Corporation

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef __TBB_test_common_named_requirements_test_H_
#define __TBB_test_common_named_requirements_test_H_

#include <atomic>

struct CreateFlag {};

struct MinimalisticRange {
    MinimalisticRange(const MinimalisticRange&) = default;
    MinimalisticRange(MinimalisticRange&, oneapi::tbb::split) {}
    ~MinimalisticRange() = default;

    bool empty() const { return true; }
    bool is_divisible() const { return false; }

    MinimalisticRange() = delete;
    MinimalisticRange& operator=(const MinimalisticRange&) = delete;

    static MinimalisticRange build() { return MinimalisticRange(CreateFlag{}); }
private:
    MinimalisticRange(CreateFlag) {}
}; // struct MinimalisticRange

struct MinimalisticValue {
    MinimalisticValue() = delete;
    MinimalisticValue(const MinimalisticValue&) = default;
    ~MinimalisticValue() = default;
    MinimalisticValue& operator=(const MinimalisticValue&) = default;

    static MinimalisticValue build() { return MinimalisticValue(CreateFlag{}); }

private:
    MinimalisticValue(CreateFlag) {}
}; // struct MinimalisticValue

struct MinimalisticReduction {
    MinimalisticValue operator()(const MinimalisticValue& x, const MinimalisticValue&) const { return x; }

    MinimalisticReduction() = delete;
    MinimalisticReduction(const MinimalisticReduction&) = delete;
    MinimalisticReduction& operator=(const MinimalisticReduction&) = delete;

    static MinimalisticReduction* build_ptr() {
        MinimalisticReduction* ptr = static_cast<MinimalisticReduction*>(::operator new(sizeof(MinimalisticReduction)));
        ::new(ptr) MinimalisticReduction(CreateFlag{});
        return ptr;
    }

    static void eliminate(MinimalisticReduction* ptr) {
        ptr->~MinimalisticReduction();
        ::operator delete(ptr);
    }
private:
    MinimalisticReduction(CreateFlag) {}
    ~MinimalisticReduction() = default;
}; // struct MinimalisticReduction

#endif // __TBB_test_common_named_requirements_test_H_
