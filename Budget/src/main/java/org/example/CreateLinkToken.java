package org.example;

import java.io.IOException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import retrofit2.Response;

import io.github.cdimascio.dotenv.Dotenv;

import com.plaid.client.ApiClient;
import com.plaid.client.model.CountryCode;
import com.plaid.client.model.LinkTokenCreateRequest;
import com.plaid.client.model.LinkTokenCreateRequestUser;
import com.plaid.client.model.LinkTokenCreateResponse;
import com.plaid.client.model.Products;
import com.plaid.client.request.PlaidApi;

public class CreateLinkToken {
    public static void main(String[] args) throws IOException {
        // System.out.println("Hello world!");
        System.out.println("respose body: " + createLinkToken());
    }

    public static LinkTokenCreateResponse createLinkToken() throws IOException {
        Dotenv dotenv = Dotenv.load();

        // Create your Plaid client
        HashMap<String, String> apiKeys = new HashMap<String, String>();
        apiKeys.put("clientId", dotenv.get("PLAID_CLIENT_ID"));
        apiKeys.put("secret", dotenv.get("PLAID_SECRET")); 
        ApiClient apiClient = new ApiClient(apiKeys);
        apiClient.setPlaidAdapter(ApiClient.Sandbox);
        // System.out.println("apiClient: " + apiClient.toString());
        PlaidApi plaidClient = apiClient.createService(PlaidApi.class);
        // System.out.println("plaidClient: " + plaidClient.toString());

        // Create a User
        LinkTokenCreateRequestUser user = new LinkTokenCreateRequestUser().clientUserId("user-1");

        // Create a link_token request for the given user
        LinkTokenCreateRequest request = new LinkTokenCreateRequest()
                .user(user)
                .clientName("Personal Finance App")
                .products(Arrays.asList(Products.TRANSACTIONS, Products.AUTH))
                .countryCodes(List.of(CountryCode.US))
                .language("en");
        
        System.out.println("request: " + request);
        Response<LinkTokenCreateResponse> response = plaidClient.linkTokenCreate(request).execute();
        System.out.println("response: " + response);
        
        // Send the data to the client
        return response.body();
    }
}