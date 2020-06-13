// Copyright (c) 2018 The COLX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "curl.h"
#include "tinyformat.h"

#include <curl/curl.h>

static void CurlGlobalInit()
{
    static bool initialized = false;
    if (!initialized) {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        initialized = true;
    }
}

struct CurlScopeInit
{
    CurlScopeInit() {
        CurlGlobalInit();
        curl_ = curl_easy_init();
    }

    ~CurlScopeInit() {
        if (curl_) curl_easy_cleanup(curl_);
    }

    inline CURL* instance() { return curl_; }

    inline operator CURL*() { return curl_; }

private:
    CurlScopeInit(const CurlScopeInit&);
    CurlScopeInit& operator=(const CurlScopeInit&);

private:
    CURL *curl_;
};

bool GetRedirect(const CUrl& url, CUrl& redirect, std::string& error)
{
    CurlScopeInit curl;
    CURLcode res;
    char *location;
    long response_code;

    if (!curl.instance()) {
        error = "curl init failed";
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        error = tfm::format("curl_easy_perform failed: %s", curl_easy_strerror(res));
        return false;
    }

    res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    if ((res == CURLE_OK) && ((response_code / 100) != 3)) {
        /* a redirect implies a 3xx response code */
        error = "Not a redirect";
        return false;
    }
    else {
        res = curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &location);
        if ((res == CURLE_OK) && location) {
            /* This is the new absolute URL that you could redirect to, even if
             * the Location: response header may have been a relative URL. */
            redirect = location;
            return true;
        }
        else {
            error = tfm::format("curl_easy_getinfo failed: %s", curl_easy_strerror(res));
            return false;
        }
    }
}