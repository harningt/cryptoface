/* TODO: GENERATE AUTOMATICALLY */
#ifdef INCLUDE_DIGEST_HEADERS
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "adler32.h"
#include "crc.h"
#if 0
#include "haval.h"
#endif
#include "md2.h"
#include "md4.h"
#include "md5.h"
#include "panama.h"
#include "ripemd.h"
#include "sha.h"
#include "tiger.h"
#include "whrlpool.h"
#else
/* LIST OF DIGEST */
DIGEST(Adler32)
DIGEST(CRC32)
#if 0
DIGEST(HAVAL)
DIGEST(HAVAL3)
DIGEST(HAVAL4)
DIGEST(HAVAL5)
#endif
DIGEST(Weak::MD2)
DIGEST(Weak::MD4)
DIGEST(Weak::MD5)
DIGEST(Weak::PanamaHash<CryptoPP::BigEndian>)
DIGEST(Weak::PanamaHash<CryptoPP::LittleEndian>)
DIGEST(RIPEMD128)
DIGEST(RIPEMD160)
DIGEST(RIPEMD256)
DIGEST(RIPEMD320)
DIGEST(SHA1)
DIGEST(SHA224)
DIGEST(SHA256)
DIGEST(SHA384)
DIGEST(SHA512)
DIGEST(Tiger)
DIGEST(Whirlpool)
#endif
