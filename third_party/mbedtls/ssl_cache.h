#ifndef MBEDTLS_SSL_CACHE_H
#define MBEDTLS_SSL_CACHE_H
#include "third_party/mbedtls/config.h"
#include "third_party/mbedtls/ssl.h"

/**
 * \name SECTION: Module settings
 *
 * The configuration options you can set for this module are in this section.
 * Either change them in config.h or define them on the compiler command line.
 * \{
 */

#if !defined(MBEDTLS_SSL_CACHE_DEFAULT_TIMEOUT)
#define MBEDTLS_SSL_CACHE_DEFAULT_TIMEOUT       86400   /*!< 1 day  */
#endif

#if !defined(MBEDTLS_SSL_CACHE_DEFAULT_MAX_ENTRIES)
#define MBEDTLS_SSL_CACHE_DEFAULT_MAX_ENTRIES      50   /*!< Maximum entries in cache */
#endif

/* \} name SECTION: Module settings */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mbedtls_ssl_cache_context mbedtls_ssl_cache_context;
typedef struct mbedtls_ssl_cache_entry mbedtls_ssl_cache_entry;

/**
 * \brief   This structure is used for storing cache entries
 */
struct mbedtls_ssl_cache_entry
{
#if defined(MBEDTLS_HAVE_TIME)
    mbedtls_time_t timestamp;           /*!< entry timestamp    */
#endif
    mbedtls_ssl_session session;        /*!< entry session      */
#if defined(MBEDTLS_X509_CRT_PARSE_C) && \
    defined(MBEDTLS_SSL_KEEP_PEER_CERTIFICATE)
    mbedtls_x509_buf peer_cert;         /*!< entry peer_cert    */
#endif
    mbedtls_ssl_cache_entry *next;      /*!< chain pointer      */
};

/**
 * \brief Cache context
 */
struct mbedtls_ssl_cache_context
{
    mbedtls_ssl_cache_entry *chain;     /*!< start of the chain     */
    int timeout;                /*!< cache entry timeout    */
    int max_entries;            /*!< maximum entries        */
};

/**
 * \brief          Initialize an SSL cache context
 *
 * \param cache    SSL cache context
 */
void mbedtls_ssl_cache_init( mbedtls_ssl_cache_context *cache );

/**
 * \brief          Cache get callback implementation
  *
 * \param data     SSL cache context
 * \param session  session to retrieve entry for
 */
int mbedtls_ssl_cache_get( void *data, mbedtls_ssl_session *session );

/**
 * \brief          Cache set callback implementation
 *
 * \param data     SSL cache context
 * \param session  session to store entry for
 */
int mbedtls_ssl_cache_set( void *data, const mbedtls_ssl_session *session );

#if defined(MBEDTLS_HAVE_TIME)
/**
 * \brief          Set the cache timeout
 *                 (Default: MBEDTLS_SSL_CACHE_DEFAULT_TIMEOUT (1 day))
 *
 *                 A timeout of 0 indicates no timeout.
 *
 * \param cache    SSL cache context
 * \param timeout  cache entry timeout in seconds
 */
void mbedtls_ssl_cache_set_timeout( mbedtls_ssl_cache_context *cache, int timeout );
#endif /* MBEDTLS_HAVE_TIME */

/**
 * \brief          Set the maximum number of cache entries
 *                 (Default: MBEDTLS_SSL_CACHE_DEFAULT_MAX_ENTRIES (50))
 *
 * \param cache    SSL cache context
 * \param max      cache entry maximum
 */
void mbedtls_ssl_cache_set_max_entries( mbedtls_ssl_cache_context *cache, int max );

/**
 * \brief          Free referenced items in a cache context and clear memory
 *
 * \param cache    SSL cache context
 */
void mbedtls_ssl_cache_free( mbedtls_ssl_cache_context *cache );

#ifdef __cplusplus
}
#endif

#endif /* ssl_cache.h */