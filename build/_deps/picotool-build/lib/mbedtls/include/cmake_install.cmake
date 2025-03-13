# Install script for directory: D:/pico-sdk/lib/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/sumobot/build/_deps")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/msys64/ucrt64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE MESSAGE_NEVER PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/aes.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/aesni.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/arc4.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/aria.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/asn1.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/asn1write.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/base64.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/bignum.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/blowfish.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/bn_mul.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/camellia.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ccm.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/certs.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/chacha20.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/chachapoly.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/check_config.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/cipher.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/cipher_internal.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/cmac.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/compat-1.3.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/config.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/config_psa.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/constant_time.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ctr_drbg.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/debug.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/des.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/dhm.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ecdh.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ecdsa.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ecjpake.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ecp.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ecp_internal.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/entropy.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/entropy_poll.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/error.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/gcm.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/havege.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/hkdf.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/hmac_drbg.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/md.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/md2.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/md4.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/md5.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/md_internal.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/net.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/net_sockets.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/nist_kw.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/oid.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/padlock.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/pem.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/pk.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/pk_internal.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/pkcs11.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/pkcs12.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/pkcs5.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/platform.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/platform_time.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/platform_util.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/poly1305.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/psa_util.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ripemd160.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/rsa.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/rsa_internal.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/sha1.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/sha256.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/sha512.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ssl.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ssl_cache.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ssl_cookie.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ssl_internal.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/ssl_ticket.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/threading.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/timing.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/version.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/x509.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/x509_crl.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/x509_crt.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/x509_csr.h"
    "D:/pico-sdk/lib/mbedtls/include/mbedtls/xtea.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE MESSAGE_NEVER PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_builtin_composites.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_builtin_primitives.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_compat.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_config.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_driver_common.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_extra.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_platform.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_se_driver.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_sizes.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_struct.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_types.h"
    "D:/pico-sdk/lib/mbedtls/include/psa/crypto_values.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "D:/sumobot/build/_deps/picotool-build/lib/mbedtls/include/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
