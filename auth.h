#ifndef AUTH_H
#define false 1
#define true 0

#define BOT_TOKEN "TOKENHERE"
#define IS_BOT false

#ifdef BOT_TOKEN
#if (IS_BOT == false)
#define BOT_HEADERS "{ \"Content-Type\": \"application/json\", \"Authorization\": \"TOKENHERE\" }"
#endif

#if (IS_BOT == true)
#define BOT_HEADERS "{ \"Content-Type\": \"application/json\", \"Authorization\": \"Bot TOKENHERE\" }"
#endif

#endif
#endif
