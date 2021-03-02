#include <libwebsockets.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_BYTES (10)

static struct lws *web_socket = NULL;

static int callback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_CLIENT_ESTABLISHED:
             printf("CLIENT CONNECTED\n");
             break;
        case LWS_CALLBACK_CLIENT_RECEIVE:
             printf("CLIENT RECEIVED DATA: %p\n", user);
             break;
        case LWS_CALLBACK_CLIENT_CLOSED:
             printf("CLIENT CLOSED\n");
             break;
        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
             printf("CLIENT ERROR\n");
             break;
        default:
             printf("CLIENT UNKNOWN EVENT: %d\n", reason);
             break;
    }
    return 0;
}

static struct lws_protocols protocols[] =
{
	{
		"protocol",
		callback,
		0,
		BUFFER_BYTES,
	},
	{ NULL, NULL, 0, 0 } /* terminator */
};


enum protocols
{
	PROTOCOL_EXAMPLE = 0,
	PROTOCOL_COUNT
};

int main(int argc, char *argv[]) {
    struct lws_context_creation_info info;
    memset( &info, 0, sizeof(info) );
    info.port = CONTEXT_PORT_NO_LISTEN;
	info.protocols = protocols;
	info.gid = -1;
	info.uid = -1;

    struct lws_context *context = lws_create_context( &info );
    time_t old = 0;
    while (1) {
        struct timeval tv;
		gettimeofday( &tv, NULL );

        if( !web_socket && tv.tv_sec != old ) {
            struct lws_client_connect_info ccinfo = {0};
            ccinfo.context = context;
			ccinfo.address = "gateway.discord.gg";
			ccinfo.port = 80;
			ccinfo.path = "/?v=8&encoding=json";
			ccinfo.host = lws_canonical_hostname( context );
			ccinfo.origin = "https://www.discord.com";
			ccinfo.protocol = protocols[PROTOCOL_EXAMPLE].name;
			web_socket = lws_client_connect_via_info(&ccinfo);
        }
        if( tv.tv_sec != old )
		{
			/* Send a random number to the server every second. */
            
			lws_callback_on_writable( web_socket );
			old = tv.tv_sec;
		}
        int logs_info;
		logs_info = lws_service( context, /* timeout_ms = */ 250 );
        printf("LARGE ERROR: %d\n", logs_info);
    }
    lws_context_destroy( context );
	return 0;
}
