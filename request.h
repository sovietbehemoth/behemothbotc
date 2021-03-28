#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

size_t callback(char *contents, size_t size, size_t nmemb, void *userdata) {
    printf("%s\n", contents);
    /*cJSON *json = cJSON_Parse(contents);
    cJSON *user;
    user = cJSON_GetObjectItemCaseSensitive(json, "username");
    printf("%s", user->valuestring);*/
    return size * nmemb;
}

int message_send(char* content, char* url) {
  CURLcode ret;
  CURL *hnd;
  struct curl_slist *slist1;

  char* USER_TOKEN = "NzA5MjQzMjE3NDc2MDU5MjA5.YFwWJg.QDzeLWZRFk-4trZbRcYwVrpfs_c";
  char token_i[60];
  char auth_i[20];
  strcpy(auth_i, "Authorization: ");
  strcpy(token_i, "NzA5MjQzMjE3NDc2MDU5MjA5.YFwWJg.QDzeLWZRFk-4trZbRcYwVrpfs_c");
  strcat(auth_i, token_i);

  slist1 = NULL;
  slist1 = curl_slist_append(slist1, "Content-Type: application/json");
  slist1 = curl_slist_append(slist1, auth_i);

  hnd = curl_easy_init();
  curl_easy_setopt(hnd, CURLOPT_URL, url);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"content\":\"hello\"}");
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)19);
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, callback);
  curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
  curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
  curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

  ret = curl_easy_perform(hnd);

  if (ret != CURLE_OK) {
    # error Request failed
    __kernel_sighandler_t
  }

  curl_easy_cleanup(hnd);
  hnd = NULL;
  curl_slist_free_all(slist1);
  slist1 = NULL;

  return (int)ret;
}

/*
{"id": "825223465228566588", "type": 0, "content": "hello", "channel_id": "813616278006398997", "author": {"id": "709243217476059209", "username": "PurpleCreeper64", "avatar": "ba32beb1ecdd17b6f59e6a3d9c3383c4", "discriminator": "1633", "public_flags": 0}, "attachments": [], "embeds": [], "mentions": [], "mention_roles": [], "pinned": false, "mention_everyone": false, "tts": false, "timestamp": "2021-03-27T04:23:26.021000+00:00", "edited_timestamp": null, "flags": 0, "referenced_message": null}
