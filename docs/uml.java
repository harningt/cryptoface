package cryptoface.core;

import java.util.Map;
import java.util.ArrayList;
import java.util.Arrays;

/**
 * @opt all
 * @opt inferdep
 * @opt inferrel
 * @opt collpackages java.util.*
 * @opt hide java.*
 * @hidden
 */
class UMLOptions {}

/**
 * @opt !constructors
 * @opt !attributes
 * @hidden
 */
class cf_attr_id_t {}

enum cf_rv_t {
	CF_S_OK,
	CF_S_IN_USE,
	CF_S_COMPLETE,
	CF_E_UNKNOWN,
	CF_E_NOT_IMPLEMENTED,
	CF_E_MEM,
	CF_E_INSUFFICIENT_BUFFER,
	CF_E_INVALID_ARGUMENTS
}

/**
 * @opt !constructors
 * @opt !attributes
 * @hidden
 */
class cf_attrs {}

/**
 * @opt !constructors
 * @hidden
 */
class cf_named_attr_id {
	public String name;
	public cf_attr_id_t id;
}

/**
 * @hidden
 */
class cf_digest_id_t {}

/**
 * @opt !constructors
 */
class cf_digest_info {
	public cf_digest_id_t id;
	public String name;
	public int block_size;
}

/**
 * @hidden
 */
class refpointer {}

/**
 * @depend - <constructs> - cf_digest_t
 */
class cf_provider_t {
	cf_digest_info[] digests;

	public cf_provider_t(final cf_attrs attrs, String path);
	public cf_rv_t destroy();

	public cf_digest_t cf_digest_init(cf_digest_id_t id);

	public refpointer cf_digest_list_begin();
	public cf_digest_info cf_digest_next(refpointer iter);
	public cf_rv_t cf_digest_end(refpointer iter);

}

/**
 * @hidden
 */
class intref {}

/**
 * @opt !constructors
 */
class cf_digest_t {
	public cf_rv_t update(final byte []data, int data_len);
	public cf_rv_t finish(byte[] buffer, intref buffer_len);
	public cf_digest_t clone();
};
