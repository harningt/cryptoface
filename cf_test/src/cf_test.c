#include "cryptoface.h"
#include "provider.h"
#include "digest.h"

#include <stdio.h>

const char *paths[] = {
	"./cf_mhash.so",
	NULL
};

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
