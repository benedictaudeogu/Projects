package org.example;

import com.plaid.client.ApiClient;
import com.plaid.client.request.PlaidApi;
import com.sun.net.httpserver.HttpExchange;
import java.io.IOException;
import java.util.HashMap;

public class PlaidExample {
    private static final String CLIENT_ID = "65249743758f26001a305697";
    private static final String SECRET = "5bc49ce1fe51905231e287a7825c7d";
    public void handle() throws IOException {
        // Create your Plaid client
        HashMap<String, String> apiKeys = new HashMap<String, String>();
        apiKeys.put("clientId", CLIENT_ID);
        apiKeys.put("secret", SECRET);
        ApiClient apiClient = new ApiClient(apiKeys);
        apiClient.setPlaidAdapter(ApiClient.Sandbox);
        PlaidApi plaidClient = apiClient.createService(PlaidApi.class);
    }
}


