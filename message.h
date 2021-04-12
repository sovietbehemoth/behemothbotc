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
    //curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, __msg_send_callback__);

    ret = curl_easy_perform(hnd);

    curl_easy_cleanup(hnd);
    hnd = NULL;
    curl_slist_free_all(slist1);
    slist1 = NULL;
    return ret;
}

int recv_callback_execute(char* contents, int pos) {
    contents[0] = ' ';
    contents[pos] = ' ';
    struct json_object *parsed_json;
    struct json_object *msg_content;
    struct json_object *msg_author;
    struct json_object *msg_author_username;
    parsed_json = json_tokener_parse(contents);
    json_object_object_get_ex(parsed_json, "content", &msg_content);
    json_object_object_get_ex(parsed_json, "author", &msg_author);
    json_object_object_get_ex(msg_author, "username", &msg_author_username);
    printf("%s\n", json_object_get_string(msg_author_username));
}

char chn[1000];
int chn_att_l = 0;
int chn_cnt_l = 0;
size_t __msg_recv_callback__(char* contents, size_t size, size_t nmemb, void *userdata) {
    char fchar[2];
    char lchar[2];
    lchar[0] = contents[strlen(contents)-1];
    fchar[0] = contents[0];
    if (strcmp(fchar, "[") == 0 && strcmp(lchar, "]") == 0 && chn_att_l == 0) {
        strcat(chn, contents);
        recv_callback_execute(chn, strlen(contents)-1);
    } else {
        strcat(chn, contents);
        chn_cnt_l = chn_cnt_l + strlen(contents);
        char form[2];
        form[0] = chn[0];
        chn_att_l = chn_att_l+1;
        if (chn_att_l == 2) {
            recv_callback_execute(chn, chn_cnt_l-1);
        }
    }
    return nmemb * size;
}

int message_get(const char* channel) {
    CURLcode ret;
    CURL *hnd;
    struct curl_slist *slist1;

    char token_i[60];   
    char auth_i[16 + strlen(BOT_TOKEN)];
    strcpy(auth_i, "Authorization: ");
    strcpy(token_i, BOT_TOKEN);
    strcat(auth_i, token_i);

    char url[45];
    char channel_id[18];
    char trailing_url[18];
    strcpy(url, "https://discord.com/api/v8/channels/");
    strcpy(channel_id, channel);
    strcat(url, channel_id);
    strcpy(trailing_url, "/messages?limit=1");
    strcat(url, trailing_url);

    slist1 = NULL;
    slist1 = curl_slist_append(slist1, "Content-Type: application/json");
    slist1 = curl_slist_append(slist1, auth_i);

    hnd = curl_easy_init();
    curl_easy_setopt(hnd, CURLOPT_URL, url);
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, __msg_recv_callback__);

    ret = curl_easy_perform(hnd);

    curl_easy_cleanup(hnd);
    hnd = NULL;
    curl_slist_free_all(slist1);
    slist1 = NULL;
    return ret;
}
