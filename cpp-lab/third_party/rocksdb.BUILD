# vim: ft=bzl

genrule(
    name = "build_version",
    srcs = [
        "util/build_version.cc.in",
    ],
    outs = [
        "util/build_version.cc",
    ],
    cmd = "sed -e s/@@GIT_SHA@@/0/ -e s/@@GIT_DATE_TIME@@/$$(date +%F)/ $< > $@",
)

_COMMON_COPTS = [
    "-std=c++11",
    "-fno-omit-frame-pointer",
    "-fno-builtin-memcmp",
    "-momit-leaf-frame-pointer",
    "-msse3",
    "-msse4",
    "-msse4.1",
    "-msse4.2",
    "-mpclmul",
    "-Werror",
    "-Wsign-compare",
    "-Wshadow",
    "-Wno-unused-parameter",
    "-Wno-unused-variable",
    "-Woverloaded-virtual",
    "-Wnon-virtual-dtor",
    "-Wno-missing-field-initializers",
]

filegroup(
    name = "private_hdrs",
    srcs = glob(["**/*.h"], exclude = ["include/**/*.h"]),
)

cc_library(
    name = "rocksdb",
    srcs = [
        ":private_hdrs",
        ":build_version",
        "cache/clock_cache.cc",
        "cache/lru_cache.cc",
        "cache/sharded_cache.cc",
        "db/arena_wrapped_db_iter.cc",
        "db/builder.cc",
        "db/c.cc",
        "db/column_family.cc",
        "db/compacted_db_impl.cc",
        "db/compaction/compaction.cc",
        "db/compaction/compaction_iterator.cc",
        "db/compaction/compaction_job.cc",
        "db/compaction/compaction_picker.cc",
        "db/compaction/compaction_picker_fifo.cc",
        "db/compaction/compaction_picker_level.cc",
        "db/compaction/compaction_picker_universal.cc",
        "db/convenience.cc",
        "db/db_filesnapshot.cc",
        "db/db_impl/db_impl.cc",
        "db/db_impl/db_impl_compaction_flush.cc",
        "db/db_impl/db_impl_debug.cc",
        "db/db_impl/db_impl_experimental.cc",
        "db/db_impl/db_impl_files.cc",
        "db/db_impl/db_impl_open.cc",
        "db/db_impl/db_impl_readonly.cc",
        "db/db_impl/db_impl_secondary.cc",
        "db/db_impl/db_impl_write.cc",
        "db/db_info_dumper.cc",
        "db/db_iter.cc",
        "db/dbformat.cc",
        "db/error_handler.cc",
        "db/event_helpers.cc",
        "db/experimental.cc",
        "db/external_sst_file_ingestion_job.cc",
        "db/file_indexer.cc",
        "db/flush_job.cc",
        "db/flush_scheduler.cc",
        "db/forward_iterator.cc",
        "db/import_column_family_job.cc",
        "db/internal_stats.cc",
        "db/log_reader.cc",
        "db/log_writer.cc",
        "db/logs_with_prep_tracker.cc",
        "db/malloc_stats.cc",
        "db/memtable.cc",
        "db/memtable_list.cc",
        "db/merge_helper.cc",
        "db/merge_operator.cc",
        "db/range_del_aggregator.cc",
        "db/range_tombstone_fragmenter.cc",
        "db/repair.cc",
        "db/snapshot_impl.cc",
        "db/table_cache.cc",
        "db/table_properties_collector.cc",
        "db/transaction_log_impl.cc",
        "db/trim_history_scheduler.cc",
        "db/version_builder.cc",
        "db/version_edit.cc",
        "db/version_set.cc",
        "db/wal_manager.cc",
        "db/write_batch.cc",
        "db/write_batch_base.cc",
        "db/write_controller.cc",
        "db/write_thread.cc",
        "env/env.cc",
        "env/env_chroot.cc",
        "env/env_encryption.cc",
        "env/env_hdfs.cc",
        "env/env_posix.cc",
        "env/file_system.cc",
        "env/fs_posix.cc",
        "env/io_posix.cc",
        "env/mock_env.cc",
        "file/delete_scheduler.cc",
        "file/file_prefetch_buffer.cc",
        "file/file_util.cc",
        "file/filename.cc",
        "file/random_access_file_reader.cc",
        "file/read_write_util.cc",
        "file/readahead_raf.cc",
        "file/sequence_file_reader.cc",
        "file/sst_file_manager_impl.cc",
        "file/writable_file_writer.cc",
        "logging/auto_roll_logger.cc",
        "logging/event_logger.cc",
        "logging/log_buffer.cc",
        "memory/arena.cc",
        "memory/concurrent_arena.cc",
        "memory/jemalloc_nodump_allocator.cc",
        "memtable/alloc_tracker.cc",
        "memtable/hash_linklist_rep.cc",
        "memtable/hash_skiplist_rep.cc",
        "memtable/skiplistrep.cc",
        "memtable/vectorrep.cc",
        "memtable/write_buffer_manager.cc",
        "monitoring/histogram.cc",
        "monitoring/histogram_windowing.cc",
        "monitoring/in_memory_stats_history.cc",
        "monitoring/instrumented_mutex.cc",
        "monitoring/iostats_context.cc",
        "monitoring/perf_context.cc",
        "monitoring/perf_level.cc",
        "monitoring/persistent_stats_history.cc",
        "monitoring/statistics.cc",
        "monitoring/thread_status_impl.cc",
        "monitoring/thread_status_updater.cc",
        "monitoring/thread_status_updater_debug.cc",
        "monitoring/thread_status_util.cc",
        "monitoring/thread_status_util_debug.cc",
        "options/cf_options.cc",
        "options/db_options.cc",
        "options/options.cc",
        "options/options_helper.cc",
        "options/options_parser.cc",
        "options/options_sanity_check.cc",
        "port/port_posix.cc",
        "port/stack_trace.cc",
        "table/adaptive/adaptive_table_factory.cc",
        "table/block_based/block.cc",
        "table/block_based/block_based_filter_block.cc",
        "table/block_based/block_based_table_builder.cc",
        "table/block_based/block_based_table_factory.cc",
        "table/block_based/block_based_table_reader.cc",
        "table/block_based/block_builder.cc",
        "table/block_based/block_prefix_index.cc",
        "table/block_based/data_block_footer.cc",
        "table/block_based/data_block_hash_index.cc",
        "table/block_based/filter_block_reader_common.cc",
        "table/block_based/filter_policy.cc",
        "table/block_based/flush_block_policy.cc",
        "table/block_based/full_filter_block.cc",
        "table/block_based/index_builder.cc",
        "table/block_based/parsed_full_filter_block.cc",
        "table/block_based/partitioned_filter_block.cc",
        "table/block_based/uncompression_dict_reader.cc",
        "table/block_fetcher.cc",
        "table/cuckoo/cuckoo_table_builder.cc",
        "table/cuckoo/cuckoo_table_factory.cc",
        "table/cuckoo/cuckoo_table_reader.cc",
        "table/format.cc",
        "table/get_context.cc",
        "table/iterator.cc",
        "table/merging_iterator.cc",
        "table/meta_blocks.cc",
        "table/persistent_cache_helper.cc",
        "table/plain/plain_table_bloom.cc",
        "table/plain/plain_table_builder.cc",
        "table/plain/plain_table_factory.cc",
        "table/plain/plain_table_index.cc",
        "table/plain/plain_table_key_coding.cc",
        "table/plain/plain_table_reader.cc",
        "table/sst_file_reader.cc",
        "table/sst_file_writer.cc",
        "table/table_properties.cc",
        "table/two_level_iterator.cc",
        "test_util/sync_point.cc",
        "test_util/sync_point_impl.cc",
        "test_util/transaction_test_util.cc",
        "tools/dump/db_dump_tool.cc",
        "tools/ldb_cmd.cc",
        "tools/ldb_tool.cc",
        "tools/sst_dump_tool.cc",
        "trace_replay/block_cache_tracer.cc",
        "trace_replay/trace_replay.cc",
        "util/coding.cc",
        "util/compaction_job_stats_impl.cc",
        "util/comparator.cc",
        "util/compression_context_cache.cc",
        "util/concurrent_task_limiter_impl.cc",
        "util/crc32c.cc",
        "util/dynamic_bloom.cc",
        "util/file_checksum_helper.cc",
        "util/hash.cc",
        "util/murmurhash.cc",
        "util/random.cc",
        "util/rate_limiter.cc",
        "util/slice.cc",
        "util/status.cc",
        "util/string_util.cc",
        "util/thread_local.cc",
        "util/threadpool_imp.cc",
        "util/xxhash.cc",
        "utilities/backupable/backupable_db.cc",
        "utilities/blob_db/blob_compaction_filter.cc",
        "utilities/blob_db/blob_db.cc",
        "utilities/blob_db/blob_db_impl.cc",
        "utilities/blob_db/blob_db_impl_filesnapshot.cc",
        "utilities/blob_db/blob_dump_tool.cc",
        "utilities/blob_db/blob_file.cc",
        "utilities/blob_db/blob_log_format.cc",
        "utilities/blob_db/blob_log_reader.cc",
        "utilities/blob_db/blob_log_writer.cc",
        "utilities/cassandra/cassandra_compaction_filter.cc",
        "utilities/cassandra/format.cc",
        "utilities/cassandra/merge_operator.cc",
        "utilities/checkpoint/checkpoint_impl.cc",
        "utilities/compaction_filters/remove_emptyvalue_compactionfilter.cc",
        "utilities/convenience/info_log_finder.cc",
        "utilities/debug.cc",
        "utilities/env_mirror.cc",
        "utilities/env_timed.cc",
        "utilities/leveldb_options/leveldb_options.cc",
        "utilities/memory/memory_util.cc",
        "utilities/merge_operators/bytesxor.cc",
        "utilities/merge_operators/max.cc",
        "utilities/merge_operators/put.cc",
        "utilities/merge_operators/sortlist.cc",
        "utilities/merge_operators/string_append/stringappend.cc",
        "utilities/merge_operators/string_append/stringappend2.cc",
        "utilities/merge_operators/uint64add.cc",
        "utilities/object_registry.cc",
        "utilities/option_change_migration/option_change_migration.cc",
        "utilities/options/options_util.cc",
        "utilities/persistent_cache/block_cache_tier.cc",
        "utilities/persistent_cache/block_cache_tier_file.cc",
        "utilities/persistent_cache/block_cache_tier_metadata.cc",
        "utilities/persistent_cache/persistent_cache_tier.cc",
        "utilities/persistent_cache/volatile_tier_impl.cc",
        "utilities/simulator_cache/cache_simulator.cc",
        "utilities/simulator_cache/sim_cache.cc",
        "utilities/table_properties_collectors/compact_on_deletion_collector.cc",
        "utilities/trace/file_trace_reader_writer.cc",
        "utilities/transactions/optimistic_transaction.cc",
        "utilities/transactions/optimistic_transaction_db_impl.cc",
        "utilities/transactions/pessimistic_transaction.cc",
        "utilities/transactions/pessimistic_transaction_db.cc",
        "utilities/transactions/snapshot_checker.cc",
        "utilities/transactions/transaction_base.cc",
        "utilities/transactions/transaction_db_mutex_impl.cc",
        "utilities/transactions/transaction_lock_mgr.cc",
        "utilities/transactions/transaction_util.cc",
        "utilities/transactions/write_prepared_txn.cc",
        "utilities/transactions/write_prepared_txn_db.cc",
        "utilities/transactions/write_unprepared_txn.cc",
        "utilities/transactions/write_unprepared_txn_db.cc",
        "utilities/ttl/db_ttl_impl.cc",
        "utilities/write_batch_with_index/write_batch_with_index.cc",
        "utilities/write_batch_with_index/write_batch_with_index_internal.cc",
    ],
    hdrs = glob(["include/rocksdb/**/*.h"]),
    local_defines = [
        "OS_LINUX",
        "ROCKSDB_FALLOCATE_PRESENT",
        "ROCKSDB_MALLOC_USABLE_SIZE",
        "ROCKSDB_PTHREAD_ADAPTIVE_MUTEX",
        "ROCKSDB_RANGESYNC_PRESENT",
        "ROCKSDB_SCHED_GETCPU_PRESENT",
        "ROCKSDB_IOURING_PRESENT",
        "HAVE_SSE42",
        "LIBURING",
        "NUMA",
        "ROCKSDB_PLATFORM_POSIX",
        "ROCKSDB_LIB_IO_POSIX",
        "ROCKSDB_SUPPORT_THREAD_LOCAL",
        "SNAPPY",
        "ZLIB",
        "BZIP2",
        "LZ4",
        "ZSTD",
        "ZSTD_STATIC_LINKING_ONLY",
        "GFLAGS=gflags",
        "ROCKSDB_BACKTRACE",
        "HAVE_PCLMUL",
        "ROCKSDB_JEMALLOC",
    ],
    copts = _COMMON_COPTS,
    includes = [
        "include",
        "util",
    ],
    linkopts = [
        "-ldl",
        "-pthread",
    ],
    linkstatic = True,
    deps = [
        "@snappy//:snappy",
        "@zstd//:zstd",
        "@lz4//:lz4_hc",
        "@zlib//:zlib",
        "@bzip2//:bzip2",
        "@jemalloc//:jemalloc",
        "@liburing//:liburing",
        "@gflags//:gflags",
        "@glog//:glog",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "rocksdb_tools_lib",
    srcs = [
        ":private_hdrs",
        "db/db_test_util.cc",
        "table/mock_table.cc",
        "test_util/fault_injection_test_env.cc",
        "test_util/testharness.cc",
        "test_util/testutil.cc",
        "tools/block_cache_analyzer/block_cache_trace_analyzer.cc",
        "tools/trace_analyzer_tool.cc",
        "utilities/cassandra/test_utils.cc",
    ],
    copts = _COMMON_COPTS,
    deps = [
        ":rocksdb",
    ],
)

cc_binary(
    name = "db_stress",
    srcs = glob([
        "db_stress_tool/*.cc",
        "db_stress_tool/*.h",
    ]),
    copts = _COMMON_COPTS,
    deps = [
        ":rocksdb",
    ],
)

[
    cc_binary(
        name = "%s" % f.replace("/", "_"),
        srcs = [
            "tools/%s.cc" % f,
            ":private_hdrs",
        ],
        copts = _COMMON_COPTS,
        deps = [
            ":rocksdb_tools_lib",
        ],
    )
    for f in [
        "sst_dump",
        "ldb",
        "db_sanity_test",
        "write_stress",
        "db_repl_stress",
        "dump/rocksdb_dump",
        "dump/rocksdb_undump",
    ]
]