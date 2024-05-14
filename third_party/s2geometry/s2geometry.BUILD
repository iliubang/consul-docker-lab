# Copyright (c) 2024 The Authors. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Authors: liubang (it.liubang@gmail.com)

cc_library(
    name = "s2",
    srcs = glob(["src/s2/util/**/*.cc"]) + [
        "src/s2/encoded_s2cell_id_vector.cc",
        "src/s2/encoded_s2point_vector.cc",
        "src/s2/encoded_s2shape_index.cc",
        "src/s2/encoded_string_vector.cc",
        "src/s2/id_set_lexicon.cc",
        "src/s2/mutable_s2shape_index.cc",
        "src/s2/r2rect.cc",
        "src/s2/s1angle.cc",
        "src/s2/s1chord_angle.cc",
        "src/s2/s1interval.cc",
        "src/s2/s2boolean_operation.cc",
        "src/s2/s2buffer_operation.cc",
        "src/s2/s2builder.cc",
        "src/s2/s2builder_graph.cc",
        "src/s2/s2builderutil_closed_set_normalizer.cc",
        "src/s2/s2builderutil_find_polygon_degeneracies.cc",
        "src/s2/s2builderutil_get_snapped_winding_delta.cc",
        "src/s2/s2builderutil_lax_polygon_layer.cc",
        "src/s2/s2builderutil_lax_polyline_layer.cc",
        "src/s2/s2builderutil_s2point_vector_layer.cc",
        "src/s2/s2builderutil_s2polygon_layer.cc",
        "src/s2/s2builderutil_s2polyline_layer.cc",
        "src/s2/s2builderutil_s2polyline_vector_layer.cc",
        "src/s2/s2builderutil_snap_functions.cc",
        "src/s2/s2cap.cc",
        "src/s2/s2cell.cc",
        "src/s2/s2cell_id.cc",
        "src/s2/s2cell_index.cc",
        "src/s2/s2cell_union.cc",
        "src/s2/s2centroids.cc",
        "src/s2/s2closest_cell_query.cc",
        "src/s2/s2closest_edge_query.cc",
        "src/s2/s2closest_point_query.cc",
        "src/s2/s2contains_vertex_query.cc",
        "src/s2/s2convex_hull_query.cc",
        "src/s2/s2coords.cc",
        "src/s2/s2crossing_edge_query.cc",
        "src/s2/s2debug.cc",
        "src/s2/s2earth.cc",
        "src/s2/s2edge_clipping.cc",
        "src/s2/s2edge_crosser.cc",
        "src/s2/s2edge_crossings.cc",
        "src/s2/s2edge_distances.cc",
        "src/s2/s2edge_tessellator.cc",
        "src/s2/s2error.cc",
        "src/s2/s2furthest_edge_query.cc",
        "src/s2/s2hausdorff_distance_query.cc",
        "src/s2/s2latlng.cc",
        "src/s2/s2latlng_rect.cc",
        "src/s2/s2latlng_rect_bounder.cc",
        "src/s2/s2lax_loop_shape.cc",
        "src/s2/s2lax_polygon_shape.cc",
        "src/s2/s2lax_polyline_shape.cc",
        "src/s2/s2loop.cc",
        "src/s2/s2loop_measures.cc",
        "src/s2/s2max_distance_targets.cc",
        "src/s2/s2measures.cc",
        "src/s2/s2memory_tracker.cc",
        "src/s2/s2metrics.cc",
        "src/s2/s2min_distance_targets.cc",
        "src/s2/s2padded_cell.cc",
        "src/s2/s2point_compression.cc",
        "src/s2/s2point_region.cc",
        "src/s2/s2pointutil.cc",
        "src/s2/s2polygon.cc",
        "src/s2/s2polyline.cc",
        "src/s2/s2polyline_alignment.cc",
        "src/s2/s2polyline_measures.cc",
        "src/s2/s2polyline_simplifier.cc",
        "src/s2/s2predicates.cc",
        "src/s2/s2projections.cc",
        "src/s2/s2r2rect.cc",
        "src/s2/s2region.cc",
        "src/s2/s2region_coverer.cc",
        "src/s2/s2region_intersection.cc",
        "src/s2/s2region_term_indexer.cc",
        "src/s2/s2region_union.cc",
        "src/s2/s2shape_index.cc",
        "src/s2/s2shape_index_buffered_region.cc",
        "src/s2/s2shape_index_measures.cc",
        "src/s2/s2shape_measures.cc",
        "src/s2/s2shape_nesting_query.cc",
        "src/s2/s2shapeutil_build_polygon_boundaries.cc",
        "src/s2/s2shapeutil_coding.cc",
        "src/s2/s2shapeutil_contains_brute_force.cc",
        "src/s2/s2shapeutil_conversion.cc",
        "src/s2/s2shapeutil_edge_iterator.cc",
        "src/s2/s2shapeutil_get_reference_point.cc",
        "src/s2/s2shapeutil_visit_crossing_edge_pairs.cc",
        "src/s2/s2text_format.cc",
        "src/s2/s2wedge_relations.cc",
        "src/s2/s2winding_operation.cc",
    ],
    hdrs = glob(["src/s2/**/*.h"]),
    includes = ["src/"],
    visibility = ["//visibility:public"],
    deps = [
        "@openssl//:ssl",
        "@abseil-cpp//absl/algorithm:algorithm",
        "@abseil-cpp//absl/algorithm:container",
        "@abseil-cpp//absl/base:base",
        "@abseil-cpp//absl/base:config",
        "@abseil-cpp//absl/base:core_headers",
        "@abseil-cpp//absl/base:dynamic_annotations",
        "@abseil-cpp//absl/base:endian",
        "@abseil-cpp//absl/base:log_severity",
        "@abseil-cpp//absl/base:malloc_internal",
        "@abseil-cpp//absl/cleanup:cleanup",
        "@abseil-cpp//absl/cleanup:cleanup_internal",
        "@abseil-cpp//absl/container:btree",
        "@abseil-cpp//absl/container:common",
        "@abseil-cpp//absl/container:compressed_tuple",
        "@abseil-cpp//absl/container:container_memory",
        "@abseil-cpp//absl/container:fixed_array",
        "@abseil-cpp//absl/container:flat_hash_map",
        "@abseil-cpp//absl/container:flat_hash_set",
        "@abseil-cpp//absl/container:hash_policy_traits",
        "@abseil-cpp//absl/container:hashtable_debug",
        "@abseil-cpp//absl/container:hashtable_debug_hooks",
        "@abseil-cpp//absl/container:hashtablez_sampler",
        "@abseil-cpp//absl/container:inlined_vector",
        "@abseil-cpp//absl/container:inlined_vector_internal",
        "@abseil-cpp//absl/container:layout",
        "@abseil-cpp//absl/container:node_hash_map",
        "@abseil-cpp//absl/container:node_hash_set",
        "@abseil-cpp//absl/container:node_slot_policy",
        "@abseil-cpp//absl/container:raw_hash_map",
        "@abseil-cpp//absl/container:raw_hash_set",
        "@abseil-cpp//absl/crc:crc32c",
        "@abseil-cpp//absl/debugging:failure_signal_handler",
        "@abseil-cpp//absl/debugging:leak_check",
        "@abseil-cpp//absl/debugging:stacktrace",
        "@abseil-cpp//absl/debugging:symbolize",
        "@abseil-cpp//absl/flags:commandlineflag",
        "@abseil-cpp//absl/flags:config",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:marshalling",
        "@abseil-cpp//absl/flags:parse",
        "@abseil-cpp//absl/flags:reflection",
        "@abseil-cpp//absl/flags:usage",
        "@abseil-cpp//absl/functional:any_invocable",
        "@abseil-cpp//absl/functional:bind_front",
        "@abseil-cpp//absl/functional:function_ref",
        "@abseil-cpp//absl/hash:city",
        "@abseil-cpp//absl/hash:hash",
        "@abseil-cpp//absl/log:absl_check",
        "@abseil-cpp//absl/log:absl_log",
        "@abseil-cpp//absl/log:check",
        "@abseil-cpp//absl/log:die_if_null",
        "@abseil-cpp//absl/log:flags",
        "@abseil-cpp//absl/log:globals",
        "@abseil-cpp//absl/log:initialize",
        "@abseil-cpp//absl/log:log",
        "@abseil-cpp//absl/log:log_entry",
        "@abseil-cpp//absl/log:log_sink",
        "@abseil-cpp//absl/log:log_sink_registry",
        "@abseil-cpp//absl/log:log_streamer",
        "@abseil-cpp//absl/log:structured",
        "@abseil-cpp//absl/memory:memory",
        "@abseil-cpp//absl/meta:type_traits",
        "@abseil-cpp//absl/numeric:bits",
        "@abseil-cpp//absl/numeric:int128",
        "@abseil-cpp//absl/numeric:representation",
        "@abseil-cpp//absl/random:bit_gen_ref",
        "@abseil-cpp//absl/random:distributions",
        "@abseil-cpp//absl/random:random",
        "@abseil-cpp//absl/random:seed_gen_exception",
        "@abseil-cpp//absl/random:seed_sequences",
        "@abseil-cpp//absl/status:status",
        "@abseil-cpp//absl/status:statusor",
        "@abseil-cpp//absl/strings:cord",
        "@abseil-cpp//absl/strings:internal",
        "@abseil-cpp//absl/strings:str_format",
        "@abseil-cpp//absl/strings:strings",
        "@abseil-cpp//absl/synchronization:synchronization",
        "@abseil-cpp//absl/time:time",
        "@abseil-cpp//absl/time/internal/cctz:civil_time",
        "@abseil-cpp//absl/time/internal/cctz:time_zone",
        "@abseil-cpp//absl/types:any",
        "@abseil-cpp//absl/types:bad_any_cast",
        "@abseil-cpp//absl/types:bad_optional_access",
        "@abseil-cpp//absl/types:bad_variant_access",
        "@abseil-cpp//absl/types:compare",
        "@abseil-cpp//absl/types:optional",
        "@abseil-cpp//absl/types:span",
        "@abseil-cpp//absl/types:variant",
        "@abseil-cpp//absl/utility:utility",
    ],
)

cc_library(
    name = "s2testing",
    srcs = [
        "src/s2/s2builderutil_testing.cc",
        "src/s2/s2shapeutil_testing.cc",
        "src/s2/s2testing.cc",
        "src/s2/thread_testing.cc",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":s2",
        "@googletest//:gtest",
    ],
)