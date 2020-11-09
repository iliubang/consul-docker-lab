# vim: ft=bzl

cc_library(
    name = "fizz",
    srcs = [
        "fizz/crypto/Utils.cpp",
        "fizz/crypto/exchange/X25519.cpp",
        "fizz/crypto/aead/OpenSSLEVPCipher.cpp",
        "fizz/crypto/aead/IOBufUtil.cpp",
        "fizz/crypto/signature/Signature.cpp",
        "fizz/crypto/Hkdf.cpp",
        "fizz/crypto/KeyDerivation.cpp",
        "fizz/crypto/Sha256.cpp",
        "fizz/crypto/Sha384.cpp",
        "fizz/crypto/openssl/OpenSSLKeyUtils.cpp",
        "fizz/record/Types.cpp",
        "fizz/record/RecordLayer.cpp",
        "fizz/record/EncryptedRecordLayer.cpp",
        "fizz/record/PlaintextRecordLayer.cpp",
        "fizz/server/AeadTokenCipher.cpp",
        "fizz/server/AeadCookieCipher.cpp",
        "fizz/server/ServerProtocol.cpp",
        "fizz/server/CertManager.cpp",
        "fizz/server/State.cpp",
        "fizz/server/FizzServer.cpp",
        "fizz/server/TicketCodec.cpp",
        "fizz/server/CookieCipher.cpp",
        "fizz/server/ReplayCache.cpp",
        "fizz/server/SlidingBloomReplayCache.cpp",
        "fizz/protocol/AsyncFizzBase.cpp",
        "fizz/protocol/Types.cpp",
        "fizz/protocol/Exporter.cpp",
        "fizz/protocol/DefaultCertificateVerifier.cpp",
        "fizz/protocol/Events.cpp",
        "fizz/protocol/KeyScheduler.cpp",
        "fizz/protocol/Certificate.cpp",
        "fizz/protocol/CertDecompressionManager.cpp",
        "fizz/protocol/Params.cpp",
        "fizz/protocol/ZlibCertificateCompressor.cpp",
        "fizz/protocol/ZlibCertificateDecompressor.cpp",
        "fizz/protocol/clock/SystemClock.cpp",
        "fizz/extensions/delegatedcred/DelegatedCredentialClientExtension.cpp",
        "fizz/extensions/delegatedcred/DelegatedCredentialFactory.cpp",
        "fizz/extensions/delegatedcred/DelegatedCredentialUtils.cpp",
        "fizz/extensions/delegatedcred/Types.cpp",
        "fizz/extensions/exportedauth/ExportedAuthenticator.cpp",
        "fizz/extensions/tokenbinding/Types.cpp",
        "fizz/extensions/tokenbinding/TokenBindingConstructor.cpp",
        "fizz/extensions/tokenbinding/TokenBindingClientExtension.cpp",
        "fizz/extensions/tokenbinding/Validator.cpp",
        "fizz/client/State.cpp",
        "fizz/client/ClientProtocol.cpp",
        "fizz/client/PskSerializationUtils.cpp",
        "fizz/client/SynchronizedLruPskCache.cpp",
        "fizz/client/EarlyDataRejectionPolicy.cpp",
        "fizz/util/FizzUtil.cpp",
    ],
    hdrs = glob([
        "fizz/client/*.h",
        "fizz/crypto/*.h",
        "fizz/crypto/aead/*.h",
        "fizz/crypto/exchange/*.h",
        "fizz/crypto/signature/*.h",
        "fizz/crypto/openssl/*.h",
        "fizz/extensions/delegatedcred/*.h",
        "fizz/extensions/exportedauth/*.h",
        "fizz/extensions/tokenbinding/*.h",
        "fizz/protocol/*.h",
        "fizz/protocol/clock/*.h",
        "fizz/record/*.h",
        "fizz/server/*.h",
        "fizz/util/*.h",
        "fizz/tool/*.h",
    ]),
    includes = ["."],
    copts = [
        "-std=c++14",
    ],
    deps = [
        "@folly//:folly",
    ],
    visibility = ["//visibility:public"],
)
