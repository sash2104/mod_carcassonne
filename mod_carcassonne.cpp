#include "ap_config.h"
#include "apr.h"
#include "apr_lib.h"
#include "apr_strings.h"
#include "apr_network_io.h"
#include "apr_want.h"
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_request.h"
#include "http_protocol.h"
#include <iostream>
#include <string>

extern "C" module AP_MODULE_DECLARE_DATA carcassonne_module;

typedef struct {
  char * message;
} carcassonne_dir_config;

static void *carcassonne_create_dir_config(apr_pool_t *p, char *path)
{
    carcassonne_dir_config *cfg = (carcassonne_dir_config *)apr_pcalloc(p, sizeof(carcassonne_dir_config));
    cfg->message = (char *) "{\"text\":\"carcassonne\"}";
    return cfg;
}

static int carcassonne_handler(request_rec *r)
{
    /* First off, we need to check if this is a call for the "example-handler" handler.
     * If it is, we accept it and do our things, if not, we simply return DECLINED,
     * and the server will try somewhere else.
     */
    if (!r->handler || strcmp(r->handler, "carcassonne")) return (DECLINED);
    // carcassonne_dir_config *cfg = (carcassonne_dir_config *)ap_get_module_config(r->server->module_config, &carcassonne_module);

    /* Now that we are handling this request, we'll write out "Hello, world!" to the client.
     * To do so, we must first set the appropriate content type, followed by our output.
     */
    ap_set_content_type(r, "application/json");
    ap_rprintf(r, "{\"text\":\"carcassonne\"}");

    /* Lastly, we must tell the server that we took care of this request and everything went fine.
     * We do so by simply returning the value OK to the server.
     */
    return OK;
}

static void register_hooks(apr_pool_t *p)
{
  ap_hook_fixups(carcassonne_handler,NULL,NULL,APR_HOOK_MIDDLE);
}

extern "C" {
    module AP_MODULE_DECLARE_DATA carcassonne_module = {
		STANDARD20_MODULE_STUFF,
		carcassonne_create_dir_config,
		NULL,
		NULL,
		NULL,
		NULL,
		register_hooks
	};
};