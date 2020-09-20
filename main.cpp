#include <stdio.h>
#include <curl/curl.h>

https://gist.github.com/connormanning/41efa6075515019e499c

int main(void)
{
	const char* url = "www.nadfdfdfdfer.com";

	// lubcURL 초기화 
	curl_global_init( CURL_GLOBAL_ALL ) ;

	// context객체의 생성
	CURL* ctx = curl_easy_init() ;

	if( NULL == ctx ){
		printf("Unable to initialize cURL interface\n");
		return -1;
	}

	// context 객체를 설정한다.	
	// 긁어올 url을 명시하고, url이 URL정보임을 알려준다.
	curl_easy_setopt( ctx , CURLOPT_URL,  url ) ;

	// no progress bar:
	curl_easy_setopt( ctx , CURLOPT_NOPROGRESS , 1 ) ;

	/*
	By default, headers are stripped from the output.
	They can be:

	- passed through a separate FILE* (CURLOPT_WRITEHEADER)

	- included in the body's output (CURLOPT_HEADER -> nonzero value)
		(here, the headers will be passed to whatever function
		 processes the body, along w/ the body)

	- handled with separate callbacks (CURLOPT_HEADERFUNCTION)
		(in this case, set CURLOPT_WRITEHEADER to a
		 matching struct for the function)

	*/
	
	// 헤더는 표준에러로 출력하도록 하다. 
	curl_easy_setopt( ctx , CURLOPT_WRITEHEADER , stderr ) ;


	// body 데이터는 표준출력 하도록 한다.
	curl_easy_setopt( ctx , CURLOPT_WRITEDATA , stdout ) ;

	// context 객체의 설정 종료 


	// 웹페이지를 긁어온다. 

	const CURLcode rc = curl_easy_perform( ctx ) ;

	if( CURLE_OK != rc )
	{
		printf("Error from cURL: %s\n", curl_easy_strerror( rc ));
	}
	else
	{

		// get some info about the xfer:
		double statDouble ;
		long statLong ;
		char* statString = NULL ;

		// HTTP 응답코드를 얻어온다. 
		if( CURLE_OK == curl_easy_getinfo( ctx , CURLINFO_HTTP_CODE , &statLong ) ){
			printf("Response code:  %ld\n", statLong);
		}

		// Content-Type 를 얻어온다.
		if( CURLE_OK == curl_easy_getinfo( ctx , CURLINFO_CONTENT_TYPE , &statString ) ){
			printf("Content type: %s\n", statString);
		}

		// 다운로드한 문서의 크기를 얻어온다.
		if( CURLE_OK == curl_easy_getinfo( ctx , CURLINFO_SIZE_DOWNLOAD , &statDouble ) ){
			printf("Download size: %lf bytes\n", statDouble);
		}

		// 
		if( CURLE_OK == curl_easy_getinfo( ctx , CURLINFO_SPEED_DOWNLOAD , &statDouble ) ){
			printf("Download speed: %lf bytes/sec\n", statDouble);
		}

	}

	// cleanup
	curl_easy_cleanup( ctx ) ;
	curl_global_cleanup() ;

	return( 0 ) ;
}