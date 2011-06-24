cryptoface
==========
Cryptoface is a cryptographic interface library for unified and simplified
access to other cryptographic libraries.  It is also a subproject of the
**ehrCom Communications Project** and will serve as the underlying security
provider.

Objectives
----------
The goal of this library is to provide a comprehensive cryptographic suite
with flexible implementation selection to implement features such as:

 * symmetric cryptographic streams
 * asymmetric cryptography to support
   * signatures
   * key exchange
   * key agreement
 * data digest / hash
 * message authentication codes (ex: HMAC, OMAC)
 * certificate processing
 * message processing (ex: CMS)

Licensing
---------
The library is licensed under MIT licensing terms.  Please see the included
LICENSE file for better details about the project.

Components
----------

### cryptoface
Base support library for cryptoface and the gateway interface to cryptoface
providers. It contains the code necessary to interact with the providers and
the exposed functionality.
Currently exposes basic digest functionality.

### cf_test
Test executable exercising the cryptoface interface for simple example / future unit testing.

### luacf
Lua interface to consume cryptoface. May later be integrated more deeply if selected as a configuration language.

Requires Lua.

### cf_botan
Cryptoface provider using [Botan] as the underlying implementation.
Currently exposes basic digest functionality.  Some hashing capabilities
not implemented due to interface difference.  Digest cloning not
available.

### cf_cryptopp
Cryptoface provider using [Crypto++] as the underlying implementation.
Currently exposes basic digest functionality.  Some hashing capabilities
not implemented due to interface difference.  Digest cloning not
available.

### cf_openssl
Cryptoface provider using [OpenSSL] as the underlying implementation.
Currently exposes basic digest functionality.

### cf_mhash
Cryptoface provider using [Mhash] as the underlying implementation.
Currently exposes basic digest functionality.

### cf_gcrypt
Cryptoface provider using [libgcrypt] (see [gnupg]) as the underlying implementation.
Currently exposes basic digest functionality.

### cf_tomcrypt
Cryptoface provider using [LibTomCrypt][LibTomCrypt] as the underlying implementation.
Currently exposes basic digest functionality.

Requirements
------------
The project is built using CMake and links in 3rd party cryptographic libraries
for support.

It has been tested to build using [CMake 2.6] on Windows and Linux.

Compiler versions tested:

 * gcc 4.5.0 - MinGW - 32-bit Windows
 * gcc 4.5.1 - Gentoo Linux - 32-bit and 64-bit

Subproject dependencies:

 * cf_botan: Botan - tested against 1.8 and 1.10 (Linux)
 * cf_cryptopp: Crypto++ - tested against 5.6.0 (Linux)
 * cf_openssl: OpenSSL - tested against 1.0.0a (Linux)
 * cf_mhash: MHash - tested against 0.9.9 (Linux and Windows)
 * cf_gcrypt: libgcrypt - tested against 1.4.6 (Linux)
 * cg_tomcrypt: LibTomcrypt - tested against 1.17 (Linux)
 * luacf: lua 5.1.x

  [Botan]: http://botan.randombit.net/
  [Crypto++]: http://www.cryptopp.com/
  [OpenSSL]: http://www.openssl.org
  [mhash]: http://mhash.sourceforge.net/
  [gnupg]: http://www.gnupg.org/
  [libgcrypt]: http://www.gnupg.org/documentation/manuals/gcrypt/
  [LibTomCrypt]: http://libtom.org/?page=features&whatfile=crypt

  [CMake 2.6]: http://www.cmake.org/cmake/resources/software.html
