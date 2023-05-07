#ifndef CURL_PLUS_PLUS_HPP
#define	CURL_PLUS_PLUS_HPP

#include <curl/curl.h>
#include <stdexcept>
#include <sstream>

class CURLplusplus
{
private:
    CURL* curl;
    std::stringstream ss;
    long http_code;

public:
    CURLplusplus()
        : curl(curl_easy_init())
        , http_code(0)
    {

    }

    ~CURLplusplus()
    {
        if (curl) curl_easy_cleanup(curl);
    }

    std::string Get(const std::string& url)
    {
        CURLcode res;

        /*curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
        curl_easy_setopt(curl, CURLOPT_URL, searchURL.c_str());

#ifdef SKIP_PEER_VERIFICATION
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();*/

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

        ss.str("");
        http_code = 0;
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            throw std::runtime_error(curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        return ss.str();
    }

    long GetHttpCode()
    {
        return http_code;
    }

private:
    static size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp)
    {
        return static_cast<CURLplusplus*>(userp)->Write(buffer, size, nmemb);
    }

    size_t Write(void* buffer, size_t size, size_t nmemb)
    {
        ss.write((const char*)buffer, size * nmemb);
        return size * nmemb;
    }
};

#endif CURL_PLUS_PLUS_HPP