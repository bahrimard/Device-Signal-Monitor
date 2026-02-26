#include <api.h>

String API::HTTPPost(String url, String body) {

    if (WiFi.status() != WL_CONNECTED) {
        return "";
    }

    if (WiFi.status() != WL_CONNECTED) 
        return "Connection failed.";
    else {
        String returnString = "";
    
        // WiFiClientSecure client;
        // client.setInsecure();
        WiFiClient client;
        HTTPClient http;
        http.setTimeout(3000);
        http.begin(client, url);
        http.addHeader("Content-Type", "application/json");
        Serial.println("Request to this url : " + url);
        Serial.println("With payload: " + body);
        int httpResponseCode = http.POST(body);
        if (httpResponseCode == HTTP_CODE_OK) {
            String payload = http.getString();
            http.end();
            returnString = payload;
        }
        return returnString;
    }
}

String API::HTTPGet(String url) {
    if (WiFi.status() != WL_CONNECTED) return "Connection failed.";
    String returnString = "";
    Serial.println("Request to this url : " + url);
    HTTPClient http;
    http.begin(url);
    Serial.println("HTTP Begin()");
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.GET();
    Serial.println("Response Code : " + String(httpResponseCode));
    if (httpResponseCode > 0) {
        String payload = http.getString();
        Serial.println("Payload: "+payload);
        http.end();
        returnString = payload;
    }
    return returnString;
}