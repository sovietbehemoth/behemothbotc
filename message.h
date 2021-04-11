#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json-c/json.h>
#include <curl/curl.h>

#include "auth.h"

//handle data from response. Handle incoming response data from posted message (OPTIONAL)
size_t __msg_send_callback__(char* contents, size_t size, size_t nmemb, void *userdata) {
    return nmemb * size;
}

//Send a message to a specified channel
int message_send(const char content[], char channel[18]) {
    CURLcode ret;
    CURL *hnd;
    struct curl_slist *slist1;

    //form authorization header
    char token_i[60];   
    char auth_i[16 + strlen(BOT_TOKEN)];
    strcpy(auth_i, "Authorization: ");
    strcpy(token_i, BOT_TOKEN);
    strcat(auth_i, token_i);

    //form request url
    char url[37];
    char channel_id[18];
    char trailing_url[10];
    strcpy(url, "https://discord.com/api/v8/channels/");
    strcpy(channel_id, channel);
    strcat(url, channel_id);
    strcpy(trailing_url, "/messages");
    strcat(url, trailing_url);

    //form content json
    char post1[strlen(content) + 30];
    char postcontents[strlen(content)];
    char posttrail[17];
    strcpy(post1, "{\"content\":\"");
    strcpy(postcontents, content);
    strcat(post1, postcontents);
    strcpy(posttrail, "\", \"tts\": false}");
    strcat(post1, posttrail);

    //append headers to request
    slist1 = NULL;
    slist1 = curl_slist_append(slist1, "Content-Type: application/json");
    slist1 = curl_slist_append(slist1, auth_i);

    hnd = curl_easy_init();
    curl_easy_setopt(hnd, CURLOPT_URL, url);
    curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, post1);
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, __msg_send_callback__);

    ret = curl_easy_perform(hnd);

    curl_easy_cleanup(hnd);
    hnd = NULL;
    curl_slist_free_all(slist1);
    slist1 = NULL;
    return ret;
}
