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

#include "cpp/misc/sst/comparator.h"

namespace pl {

Comparator::~Comparator() = default;

class BytewiseComparator : public Comparator {
public:
    BytewiseComparator() = default;

    [[nodiscard]] const char* name() const override { return "BytewiseComparator"; };

    [[nodiscard]] int compare(const Binary& a, const Binary& b) const override {
        return a.compare(b);
    }
};

Comparator* bytewiseComparator() { return new BytewiseComparator(); }

} // namespace pl
