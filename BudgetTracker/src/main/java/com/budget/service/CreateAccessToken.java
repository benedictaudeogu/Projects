// package com.budget.service;

// import java.util.List;
// import java.util.Map;

// import org.springframework.boot.CommandLineRunner;
// import org.springframework.stereotype.Service;

// import java.util.Arrays;
// import java.util.HashMap;
// import retrofit2.Response;
// import java.io.IOException;

// import io.github.cdimascio.dotenv.Dotenv;

// import com.plaid.client.ApiClient;
// import com.plaid.client.model.Products;
// import com.plaid.client.model.SandboxPublicTokenCreateRequest;
// import com.plaid.client.model.SandboxPublicTokenCreateResponse;
// import com.plaid.client.request.PlaidApi;
// import com.plaid.client.model.CountryCode;
// import com.plaid.client.model.LinkTokenCreateRequest;
// import com.plaid.client.model.LinkTokenCreateResponse;
// import com.plaid.client.model.LinkTokenCreateRequestUser;
// import com.plaid.client.model.ItemPublicTokenExchangeRequest;
// import com.plaid.client.model.ItemPublicTokenExchangeResponse;


// @Service
// public class CreateAccessToken implements CommandLineRunner{
//     public LinkTokenCreateResponse createDevAccessToken() throws IOException {
//         Dotenv dotenv = Dotenv.load();

//         // Create Plaid client
//         HashMap<String, String> apiKeys = new HashMap<String, String>();
//         apiKeys.put("clientId", dotenv.get("PLAID_CLIENT_ID"));
//         apiKeys.put("secret", dotenv.get("PLAID_SECRET")); 
//         ApiClient apiClient = new ApiClient(apiKeys);
//         apiClient.setPlaidAdapter(dotenv.get("PLAID_ENV"));
//         // System.out.println("apiClient: " + apiClient.toString());
//         PlaidApi plaidClient = apiClient.createService(PlaidApi.class);
//         // System.out.println("plaidClient: " + plaidClient.toString());

//         // Create a User
//         LinkTokenCreateRequestUser user = new LinkTokenCreateRequestUser().clientUserId("user-1-java");

//         // Create a link_token request for the user
//         LinkTokenCreateRequest linkTokenRequest = new LinkTokenCreateRequest()
//                 .user(user)
//                 .clientName("Personal Finance App")
//                 .products(Arrays.asList(Products.TRANSACTIONS, Products.AUTH))
//                 .countryCodes(List.of(CountryCode.US))
//                 .language("en");
//         // System.out.println("link token request: " + linkTokenRequest);

//         // Create link_token
//         Response<LinkTokenCreateResponse> linkTokenResponse = plaidClient.linkTokenCreate(linkTokenRequest).execute();
//         // System.out.println("link token response: " + linkTokenResponse);

//         // Send the data to the client
//         return linkTokenResponse.body();

//         // Synchronously exchange a Link public_token for an API access_token
//         // Required request parameters are always Request object constructor arguments
//         // ItemPublicTokenExchangeRequest request = new ItemPublicTokenExchangeRequest().publicToken(publicToken);
//         // Response<ItemPublicTokenExchangeResponse> response = plaidClient.itemPublicTokenExchange(request).execute();
//         // if (response.isSuccessful()) {
//         //     accessToken = response.body().getAccessToken();
//         // }
//     }
    
//     public ItemPublicTokenExchangeResponse createSandboxAccessToken() throws IOException {
//         Dotenv dotenv = Dotenv.load();

//         // Create Plaid client
//         HashMap<String, String> apiKeys = new HashMap<String, String>();
//         apiKeys.put("clientId", dotenv.get("PLAID_CLIENT_ID"));
//         apiKeys.put("secret", dotenv.get("PLAID_SECRET")); 
//         ApiClient apiClient = new ApiClient(apiKeys);
//         apiClient.setPlaidAdapter(dotenv.get("PLAID_ENV"));
//         PlaidApi plaidClient = apiClient.createService(PlaidApi.class);

//         // Create access_token for sandbox testing
//         SandboxPublicTokenCreateRequest sandboxPublicRequest = new SandboxPublicTokenCreateRequest()
//                 .institutionId("ins_109508")
//                 .initialProducts(Arrays.asList(Products.TRANSACTIONS, Products.AUTH));

//         // System.out.println("sandboxPublicRequest: " + sandboxPublicRequest.toString());

//         Response<SandboxPublicTokenCreateResponse> sandboxPublicResponse = plaidClient.sandboxPublicTokenCreate(sandboxPublicRequest).execute();
//         // System.out.println("sandboxPublicResponse: " + sandboxPublicResponse.toString());
       
//         // The generated public_token can now be exchanged for an access_token
//         ItemPublicTokenExchangeRequest accessRequest = new ItemPublicTokenExchangeRequest().publicToken(sandboxPublicResponse.body().getPublicToken());

//         Response<ItemPublicTokenExchangeResponse> accessResponse = plaidClient.itemPublicTokenExchange(accessRequest).execute();
//         if (accessResponse.body() != null){
//             return accessResponse.body();
//         } 
//         else throw new RuntimeException("Failed to create access token");
//         //  return null;
//     }

//     @Override
//     public void run(String... args) throws Exception {
//         Dotenv dotenv = Dotenv.load();
//         System.out.println("Access Token: " + dotenv.get("ACCESS_TOKEN"));
//     }
// }