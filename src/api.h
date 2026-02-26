#include <HTTPClient.h>

class API {
    public:
        static String HTTPPost(String url, String body);
        static String HTTPGet(String url);
};