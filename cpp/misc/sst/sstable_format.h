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

#pragma once

#include "cpp/misc/fs/fs.h"
#include "cpp/tools/binary.h"
#include "cpp/tools/status.h"

#include <cstdint>
#include <sstream>
#include <string>

namespace pl {

static constexpr std::size_t FOOTER_LEN = 64;
static constexpr uint64_t SST_MAGIC_NUMBER = 0x833859d02c1dbd75ull;
static constexpr uint32_t BLOCK_TRAILER_LEN = 5; // compression type (1B) + crc (4B)
// sst_type(1B) + sst_version(1B) + patch_id(8B) + sst_id(8B) + filter_type(1B) + bits_per_key(4B) +
// key_num(8B) + min_key_len(4B) + max_key_len(4B)
static constexpr uint32_t FILE_META_MIN_LEN = 39;

// clang-format off
#define __SST_CASE__(t) case t: return #t
// clang-format on

enum class SSTType : uint8_t {
    NONE = 0,   // invalid sst type
    MEMORY = 1, // the sst file is generated by memory dump
    MINOR = 2,  // the sst file is generaged by minor compaction
    MAJOR = 3,  // the sst file is generated by major compaction
};

inline const char* SSTType2String(SSTType t) {
    switch (t) {
        __SST_CASE__(SSTType::NONE);
        __SST_CASE__(SSTType::MEMORY);
        __SST_CASE__(SSTType::MINOR);
        __SST_CASE__(SSTType::MAJOR);
    }
}

enum class SSTVersion : uint8_t {
    NONE = 0,
    V1 = 1, // current sst version is V1
};

inline const char* SSTVersion2String(SSTVersion t) {
    switch (t) {
        __SST_CASE__(SSTVersion::NONE);
        __SST_CASE__(SSTVersion::V1);
    }
}

enum class FilterPolicyType : uint8_t {
    NONE = 0,
    BLOOM_FILTER = 1,
};

inline const char* FilterPolicyType2String(FilterPolicyType t) {
    switch (t) {
        __SST_CASE__(FilterPolicyType::NONE);
        __SST_CASE__(FilterPolicyType::BLOOM_FILTER);
    }
}

enum class CompressionType : uint8_t {
    NONE = 0,
    SNAPPY = 1,
    ZSTD = 2,
};

inline const char* CompressionType2String(CompressionType t) {
    switch (t) {
        __SST_CASE__(CompressionType::NONE);
        __SST_CASE__(CompressionType::SNAPPY);
        __SST_CASE__(CompressionType::ZSTD);
    }
}

#undef __SST_CASE__

using PatchId = uint64_t;
using SSTId = uint64_t;

/**
 * @class BlockHandle
 * @brief 主要是用来构造索引的
 */
class BlockHandle {
public:
    BlockHandle() : offset_(~static_cast<uint64_t>(0)), size_(~static_cast<uint64_t>(0)) {}

    [[nodiscard]] uint64_t offset() const { return offset_; }

    [[nodiscard]] uint64_t size() const { return size_; }

    void setOffset(uint64_t offset) { offset_ = offset; }

    void setSize(uint64_t size) { size_ = size; }

    void encodeTo(std::string* dst) const;

    [[nodiscard]] Status decodeFrom(const Binary& input);

private:
    uint64_t offset_;
    uint64_t size_;
};

/**
 * @class FileMeta
 * @brief record sst file meta data
 */
class FileMeta {
public:
    FileMeta() = default;

    void setSSTType(SSTType type) { sst_type_ = type; }

    void setSSTVersion(SSTVersion version) { sst_version_ = version; }

    void setPatchId(PatchId patch_id) { patch_id_ = patch_id; }

    void setSSTId(SSTId sst_id) { sst_id_ = sst_id; }

    void setFilterPolicyType(FilterPolicyType type) { filter_type_ = type; }

    void setKeyNum(uint64_t key_number) { key_number_ = key_number; }

    void setMinKey(const std::string& key) { min_key_ = key; }

    void setMaxKey(const std::string& key) { max_key_ = key; }

    void setBitsPerKey(uint32_t bpk) { bits_per_key_ = bpk; }

    [[nodiscard]] SSTType sstType() const { return sst_type_; }

    [[nodiscard]] SSTVersion sstVersion() const { return sst_version_; }

    [[nodiscard]] PatchId patchId() const { return patch_id_; }

    [[nodiscard]] SSTId sstId() const { return sst_id_; }

    [[nodiscard]] FilterPolicyType filterPolicyType() const { return filter_type_; }

    [[nodiscard]] const std::string& minKey() const { return min_key_; }

    [[nodiscard]] const std::string& maxKey() const { return max_key_; }

    [[nodiscard]] uint32_t bitsPerKey() const { return bits_per_key_; }

    void encodeTo(std::string* dst) const;

    Status decodeFrom(const Binary& input);

    [[nodiscard]] std::string toString() const {
        std::stringstream ss;
        ss << "sst type: " << SSTType2String(sst_type_) << '\n';
        ss << "sst version: " << SSTVersion2String(sst_version_) << '\n';
        ss << "patch id: " << patch_id_ << '\n';
        ss << "sst id: " << sst_id_ << '\n';
        ss << "filter type: " << FilterPolicyType2String(filter_type_) << '\n';
        ss << "bits per key: " << bits_per_key_ << '\n';
        ss << "key number: " << key_number_ << '\n';
        ss << "min key: " << min_key_ << '\n';
        ss << "max key: " << max_key_ << '\n';
        return ss.str();
    }

private:
    SSTType sst_type_{SSTType::NONE};
    SSTVersion sst_version_{SSTVersion::NONE};
    PatchId patch_id_{0};
    SSTId sst_id_{0};
    FilterPolicyType filter_type_{FilterPolicyType::NONE};
    uint32_t bits_per_key_;
    uint64_t key_number_;
    std::string min_key_;
    std::string max_key_;
};

using FileMetaPtr = std::unique_ptr<FileMeta>;
using FileMetaRef = std::shared_ptr<FileMeta>;

class Footer {
public:
    Footer() = default;

    void setMetaindexHandle(const BlockHandle& block_handle) { filter_handle_ = block_handle; }
    void setFilterHandle(const BlockHandle& block_handle) { filter_handle_ = block_handle; }
    void setIndexHandle(const BlockHandle& block_handle) { index_handle_ = block_handle; }
    void setFileMetaHandle(const BlockHandle& block_handle) { file_meta_handle_ = block_handle; }

    [[nodiscard]] const BlockHandle& metaIndexHandle() const { return filter_handle_; }
    [[nodiscard]] const BlockHandle& filterHandle() const { return filter_handle_; }
    [[nodiscard]] const BlockHandle& indexHandle() const { return index_handle_; }
    [[nodiscard]] const BlockHandle& fileMetaHandle() const { return file_meta_handle_; }

    void encodeTo(std::string* dst) const;
    [[nodiscard]] Status decodeFrom(const Binary& input);

private:
    BlockHandle filter_handle_;
    BlockHandle index_handle_;
    BlockHandle file_meta_handle_;
};

struct BlockContents {
    Binary data;
    bool cachable;
    bool heap_allocated;
};

class BlockReader {
public:
    static Status readBlock(const FsReaderRef& reader,
                            const BlockHandle& handle,
                            BlockContents* result);
};

} // namespace pl
