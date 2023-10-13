package org.example;

import java.io.IOException;
import java.time.OffsetDateTime;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import retrofit2.Response;

import io.github.cdimascio.dotenv.Dotenv;

import com.plaid.client.ApiClient;
import com.plaid.client.model.CountryCode;
import com.plaid.client.model.ItemPublicTokenExchangeRequest;
import com.plaid.client.model.ItemPublicTokenExchangeResponse;
import com.plaid.client.model.LinkTokenCreateRequest;
import com.plaid.client.model.LinkTokenCreateRequestUser;
import com.plaid.client.model.LinkTokenCreateResponse;
import com.plaid.client.model.Products;
import com.plaid.client.request.PlaidApi;


public class Main {
    public static void main(String[] args) throws IOException {
        // System.out.println("Hello world!");
        System.out.println("respose: " + createLinkToken());
    }

    public static LinkTokenCreateResponse createLinkToken() throws IOException {
        // String publicToken;
        // String accessToken;
        // String itemId;

        Dotenv dotenv = Dotenv.load();

        // Create your Plaid client
        HashMap<String, String> apiKeys = new HashMap<String, String>();
        apiKeys.put("clientId", dotenv.get("PLAID_CLIENT_ID"));
        apiKeys.put("secret", dotenv.get("PLAID_SECRET")); 
        ApiClient apiClient = new ApiClient(apiKeys);
        apiClient.setPlaidAdapter(ApiClient.Sandbox);
        System.out.println("api-client: " + apiClient.toString());

        PlaidApi plaidClient = apiClient.createService(PlaidApi.class);
        System.out.println("plaid-client: " + plaidClient.toString());

        // Create a User
        LinkTokenCreateRequestUser user = new LinkTokenCreateRequestUser().clientUserId("user-1");
        user.setLegalName("benedicta");
        user.setPhoneNumber("1234567890");
        user.setPhoneNumberVerifiedTime(OffsetDateTime.parse("2023-10-13T15:30:00+01:00"));
        user.setEmailAddress("123@dmomain.com");
        user.setEmailAddressVerifiedTime(OffsetDateTime.parse("2023-10-13T15:30:00+01:00"));
        user.setSsn("123-45-6789");
        user.setDateOfBirth(OffsetDateTime.parse("2001-06-17T15:30:00+01:00"));
        // System.out.println("user: " + user);


        // Create a link_token for the given user
        LinkTokenCreateRequest request = new LinkTokenCreateRequest()
                .clientId(dotenv.get("PLAID_CLIENT_ID"))
                .secret(dotenv.get("PLAID_SECRET"))
                .user(user)
                .clientName("Plaid Test App")
                .products(Arrays.asList(Products.fromValue("auth")))
                // .products(Arrays.asList(Products.fromValue("transactions")))
                .countryCodes(List.of(CountryCode.US))
                .language("en")
                .redirectUri("https://domainname.com/oauth-page.html")
                .webhook("https://webhook.example.com");
        
        System.out.println("request: " + request);
        Response<LinkTokenCreateResponse> response = plaidClient.linkTokenCreate(request).execute();

        // Send the data to the client
        // return null;
        return response.body();
    }
}