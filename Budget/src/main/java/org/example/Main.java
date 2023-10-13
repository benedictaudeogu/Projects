package org.example;

import java.io.IOException;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;

import com.plaid.client.ApiClient;
import com.plaid.client.model.CountryCode;
import com.plaid.client.model.LinkTokenCreateRequest;
import com.plaid.client.model.LinkTokenCreateRequestUser;
import com.plaid.client.model.LinkTokenCreateResponse;
import com.plaid.client.model.Products;
import com.plaid.client.request.PlaidApi;

import retrofit2.Response;

public class Main {
    public static void main(String[] args) throws IOException {
        System.out.println("Hello world!");
        System.out.println(createLinkToken());
    }

    public static LinkTokenCreateResponse createLinkToken() throws IOException {
        // Create your Plaid client
        HashMap<String, String> apiKeys = new HashMap<String, String>();
        apiKeys.put("clientId", "65249743758f26001a305697");
        apiKeys.put("secret", "c7db7a1d828379c477563dd9c3fcec");
        ApiClient apiClient = new ApiClient(apiKeys);
        apiClient.setPlaidAdapter(ApiClient.Sandbox);

        PlaidApi plaidClient = apiClient.createService(PlaidApi.class);
        System.out.println(plaidClient.toString());

        // Create a User
        User userFromDB = new User();
        userFromDB.setId("user-id");
        

        String clientUserId = userFromDB.getId();
        LinkTokenCreateRequestUser user = new LinkTokenCreateRequestUser().clientUserId(clientUserId);

        // Create a link_token for the given user
        LinkTokenCreateRequest request = new LinkTokenCreateRequest()
                .user(user)
                .clientName("Plaid Test App")
                .products(Collections.singletonList(Products.fromValue("auth")))
                .countryCodes(List.of(CountryCode.US))
                .language("en")
                .redirectUri("https://domainname.com/oauth-page.html")
                .webhook("https://webhook.example.com");

        Response<LinkTokenCreateResponse> response = plaidClient.linkTokenCreate(request).execute();

        // Send the data to the client
        return response.body();
    }
}