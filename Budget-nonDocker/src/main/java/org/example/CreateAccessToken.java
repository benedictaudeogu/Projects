package org.example;

import java.util.List;
import java.util.Arrays;
import java.util.HashMap;
import retrofit2.Response;
import java.io.IOException;

import io.github.cdimascio.dotenv.Dotenv;

import com.plaid.client.ApiClient;
import com.plaid.client.model.Products;
import com.plaid.client.request.PlaidApi;
import com.plaid.client.model.CountryCode;
import com.plaid.client.model.LinkTokenCreateRequest;
import com.plaid.client.model.LinkTokenCreateResponse;
import com.plaid.client.model.LinkTokenCreateRequestUser;
import com.plaid.client.model.ItemPublicTokenExchangeRequest;
import com.plaid.client.model.ItemPublicTokenExchangeResponse;


public class CreateAccessToken {
    public static void main(String[] args) throws IOException {
        // System.out.println("Hello world!");
        System.out.println("link token respose body: " + createAccessToken());
    }

    public static LinkTokenCreateResponse createAccessToken() throws IOException {
        Dotenv dotenv = Dotenv.load();

        // Create Plaid client
        HashMap<String, String> apiKeys = new HashMap<String, String>();
        apiKeys.put("clientId", dotenv.get("PLAID_CLIENT_ID"));
        apiKeys.put("secret", dotenv.get("PLAID_SECRET")); 
        ApiClient apiClient = new ApiClient(apiKeys);
        apiClient.setPlaidAdapter(dotenv.get("PLAID_ENV"));
        System.out.println("apiClient: " + apiClient.toString());
        PlaidApi plaidClient = apiClient.createService(PlaidApi.class);
        System.out.println("plaidClient: " + plaidClient.toString());

        // Create a User
        LinkTokenCreateRequestUser user = new LinkTokenCreateRequestUser().clientUserId("user-1-java");

        // Create a link_token request for the user
        LinkTokenCreateRequest linkTokenRequest = new LinkTokenCreateRequest()
                .user(user)
                .clientName("Personal Finance App")
                .products(Arrays.asList(Products.TRANSACTIONS, Products.AUTH))
                .countryCodes(List.of(CountryCode.US))
                .language("en");
        System.out.println("link token request: " + linkTokenRequest);

        // Create link_token
        Response<LinkTokenCreateResponse> linkTokenResponse = plaidClient.linkTokenCreate(linkTokenRequest).execute();
        System.out.println("link token response: " + linkTokenResponse);
        
        // Send the data to the client
        return linkTokenResponse.body();

        // Synchronously exchange a Link public_token for an API access_token
        // Required request parameters are always Request object constructor arguments
        // ItemPublicTokenExchangeRequest request = new ItemPublicTokenExchangeRequest().publicToken(publicToken);
        // Response<ItemPublicTokenExchangeResponse> response = plaidClient.itemPublicTokenExchange(request).execute();
        // if (response.isSuccessful()) {
        //     accessToken = response.body().getAccessToken();
        // }
    }        
}