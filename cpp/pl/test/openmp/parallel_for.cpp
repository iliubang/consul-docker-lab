// Copyright (c) 2024 The Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Authors: liubang (it.liubang@gmail.com)

#include <nanobench.h>

#include <cmath>
#include <vector>

static constexpr std::size_t n = 1 << 26;

static void test1() {
    std::vector<float> a(n);
    for (std::size_t i = 0; i < n; ++i) {
        a[i] = std::sin(i);
    }
    ankerl::nanobench::doNotOptimizeAway(a);
}

static void test2() {
    std::vector<float> a(n);

#pragma omp parallel for
    for (std::size_t i = 0; i < n; ++i) {
        a[i] = std::sin(i);
    }

    ankerl::nanobench::doNotOptimizeAway(a);
}

int main(int argc, char* argv[]) {
    // put your code here
    ankerl::nanobench::Bench().run("test1", [&] {
        test1();
    });
    ankerl::nanobench::Bench().run("test2", [&] {
        test2();
    });
    return 0;
}
