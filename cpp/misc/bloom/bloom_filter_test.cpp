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

#include "cpp/misc/bloom/bloom_filter.h"
#include "cpp/misc/scope/scope.h"
#include "cpp/misc/random/random.h"

#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST(bloom, bloom) {
    pl::BloomFilter filter(32);

    auto* binaries = new pl::Binary[100];

    SCOPE_EXIT { delete[] binaries; };

    std::vector<std::string> strs(100);

    for (int i = 0; i < 100; ++i) {
        strs[i] = pl::random_string(i + 10);
        binaries[i] = pl::Binary(strs[i]);
    }

    std::string dst;
    filter.create(binaries, 100, &dst);

    pl::Binary ff(dst);

    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(filter.contains(binaries[i], ff));
        auto str = pl::random_string(128);
        EXPECT_FALSE(filter.contains(str, ff));
    }
}
