#======================================================================
#
# WORKSPACE -
#
# Created by liubang on 2023/05/21 00:30
# Last Modified: 2023/05/21 00:30
#
#======================================================================

workspace(name = "playground")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

################ for cpp ################
http_archive(
    name = "hedron_compile_commands",
    strip_prefix = "bazel-compile-commands-extractor-3dddf205a1f5cde20faf2444c1757abe0564ff4c",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/3dddf205a1f5cde20faf2444c1757abe0564ff4c.tar.gz",
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()

load("//third_party:repos.bzl", "external_repositories")

external_repositories()

load("@rules_perl//perl:deps.bzl", "perl_register_toolchains", "perl_rules_dependencies")

perl_rules_dependencies()

perl_register_toolchains()

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")

boost_deps()

load("@rules_ragel//ragel:ragel.bzl", "ragel_register_toolchains")

ragel_register_toolchains("7.0.0.11")

################ for golang ################
load("@io_bazel_rules_go//go:deps.bzl", "go_register_toolchains", "go_rules_dependencies")
load("@bazel_gazelle//:deps.bzl", "gazelle_dependencies")

# gazelle:repo bazel_gazelle

load("//:go_deps.bzl", "go_repositories")

# gazelle:repository_macro go_deps.bzl%go_repositories
go_repositories()

go_rules_dependencies()

go_register_toolchains(version = "1.19.5")

gazelle_dependencies()

################ for java ################
load("@contrib_rules_jvm//:repositories.bzl", "contrib_rules_jvm_deps", "contrib_rules_jvm_gazelle_deps")

contrib_rules_jvm_deps()

contrib_rules_jvm_gazelle_deps()

load("@contrib_rules_jvm//:setup.bzl", "contrib_rules_jvm_setup")

contrib_rules_jvm_setup()

load("@contrib_rules_jvm//:gazelle_setup.bzl", "contrib_rules_jvm_gazelle_setup")

contrib_rules_jvm_gazelle_setup()

################ for rust ################
# https://github.com/bazelbuild/rules_rust/releases
http_archive(
    name = "rules_rust",
    sha256 = "36ab8f9facae745c9c9c1b33d225623d976e78f2cc3f729b7973d8c20934ab95",
    urls = ["https://github.com/bazelbuild/rules_rust/releases/download/0.31.0/rules_rust-v0.31.0.tar.gz"],
)

load("@rules_rust//rust:repositories.bzl", "rules_rust_dependencies", "rust_register_toolchains")

rules_rust_dependencies()

rust_register_toolchains()

load("@rules_rust//crate_universe:repositories.bzl", "crate_universe_dependencies")

crate_universe_dependencies(bootstrap = True)

load("@rules_rust//crate_universe:defs.bzl", "crates_repository")

crates_repository(
    name = "crate_index",
    cargo_lockfile = "//rust:Cargo.lock",
    manifests = [
        "//rust:Cargo.toml",
        "//rust/base:Cargo.toml",
        "//rust/helloworld:Cargo.toml",
        "//rust/web:Cargo.toml",
    ],
    rust_version = "1.73.0",
)

load(
    "@crate_index//:defs.bzl",
    crate_index = "crate_repositories",
)

crate_index()
