
#include "data_interface.h"
#include <stdio.h>
#include <memory>
#include <string>

#include <curl/curl.h>
#include <cJSON.h>

using namespace std;

size_t callback(const char* in, size_t size, size_t num, string* out)
{
    const size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}
    
void get_json_data(char *output, const string url)
{

    CURL* curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());   // Set remote URL.
    
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);   // Don't bother trying IPv6, which would increase DNS resolution time.
    
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); // Don't wait forever, time out after 10 seconds.
    
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow HTTP redirects if necessary.
    
    long httpCode(0);
    unique_ptr<string> httpData(new string()); // Response information.
    
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);    // Hook up data handling function.

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);
	
    if (httpCode == 200)
    {
        printf("\nGot successful response from %s\n", url.c_str());
		printf("%s\n", httpData.get()->c_str());
    }
    else
    {
        printf("Couldn't GET from %s - exiting\n", url.c_str());
    }

    return;
}