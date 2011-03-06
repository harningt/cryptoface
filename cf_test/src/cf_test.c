#include "cryptoface.h"
#include "provider.h"
#include "digest.h"

#include <stdio.h>

#ifdef WIN32
const char *paths[] = {
	".\\cf_mhash.dll",
	".\\cf_openssl.dll",
	".\\cf_tomcrypt.dll",
	".\\cf_gcrypt.dll",
	NULL
};
#else
const char *paths[] = {
	"./cf_mhash.so",
	"./cf_openssl.so",
	"./cf_tomcrypt.so",
	"./cf_gcrypt.so",
	NULL
};
#endif


static void test_digest(cf_provider_t provider, cf_digest_id_t id) {
	cf_digest_t digest;
	char data[6] = "Hello";
	unsigned char buffer[64];
	size_t buffer_size = sizeof(buffer);
	unsigned i;

	if(CF_S_OK != cf_digest_init(&digest, provider, id)) {
		printf("FAILED TO INIT DIGEST: 0x%.8x  %i\n", id, id);
		return;
	}
	if(CF_S_OK != cf_digest_update(digest, data, sizeof(data))) {
		printf("FAILED TO UPDATE DIGEST\n");
		cf_digest_finish(digest, NULL, NULL);
		return;
	}
	if(CF_S_OK != cf_digest_finish(digest, buffer, &buffer_size)) {
		printf("FAILED TO COMPLETE DIGEST\n");
		cf_digest_finish(digest, NULL, NULL);
		return;
	}
	printf("HASH: [");
	for(i = 0; i < buffer_size; i++) {
		printf("%.2X", buffer[i]);
	}
	printf("]\n");
}

static void test_digests(cf_provider_t provider) {
	void *iter = NULL;
	cf_rv_t ret = cf_digest_list_begin(provider, &iter);
	if(CF_S_OK != ret)
		goto fail;
	while(ret == CF_S_OK) {
		struct cf_digest_info info;
		ret = cf_digest_list_next(provider, &iter, &info);
		if(ret == CF_S_OK) {
			printf("ALG[%i]:  [%s]  SIZE: [%i]\n", info.id, info.name, info.block_size);
			test_digest(provider, info.id);
		}
	}
	if(ret != CF_S_COMPLETE)
		goto fail;
	goto success;
fail:
	printf("FAILED: %.8x\n", ret);
success:
	if(iter)
		cf_digest_list_end(provider, &iter);
}

static void test_provider(cf_provider_t provider) {
	test_digests(provider);
}

static void test_path(const char *path) {
	cf_provider_t provider = NULL;
	cf_rv_t ret;
	printf("TESTING: %s\n", path);
	ret = cf_provider_init(&provider, NULL, path);
	if(CF_S_OK != ret)
		goto fail;
	test_provider(provider);
	goto success;
fail:
	printf("FAILED ... return value 0x%.8x\n", ret);
success:
	if(provider)
		cf_provider_destroy(provider);
}

int main(int argc, const char **argv) {
	const char **path_iter = paths;
	for(;*path_iter;++path_iter) {
		test_path(*path_iter);
	}
	return 0;
}
