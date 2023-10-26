package com.budget.service;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;

import org.springframework.stereotype.Service;

import com.plaid.client.ApiClient;
import com.plaid.client.model.CountryCode;
import com.plaid.client.model.ItemPublicTokenExchangeRequest;
import com.plaid.client.model.ItemPublicTokenExchangeResponse;
import com.plaid.client.model.LinkTokenCreateRequest;
import com.plaid.client.model.LinkTokenCreateRequestUser;
import com.plaid.client.model.LinkTokenCreateResponse;
import com.plaid.client.model.Products;
import com.plaid.client.model.RemovedTransaction;
import com.plaid.client.model.SandboxPublicTokenCreateRequest;
import com.plaid.client.model.SandboxPublicTokenCreateResponse;
import com.plaid.client.model.Transaction;
import com.plaid.client.model.TransactionsSyncRequest;
import com.plaid.client.model.TransactionsSyncRequestOptions;
import com.plaid.client.model.TransactionsSyncResponse;
import com.plaid.client.request.PlaidApi;

import io.github.cdimascio.dotenv.Dotenv;
import retrofit2.Response;

@Service
public class BudgetService {
    public static String accessToken;
    public String itemId;

    public void setAccessToken(String accessToken){
        BudgetService.accessToken = accessToken;
    }

    public String getAccessToken(){
        return accessToken;
    }

    public PlaidApi createPlaidClient(){
        Dotenv dotenv = Dotenv.load();

        HashMap<String, String> apiKeys = new HashMap<String, String>();
        apiKeys.put("clientId", dotenv.get("PLAID_CLIENT_ID"));
        apiKeys.put("secret", dotenv.get("PLAID_SECRET")); 
        ApiClient apiClient = new ApiClient(apiKeys);
        apiClient.setPlaidAdapter(dotenv.get("PLAID_ENV"));
        PlaidApi plaidClient = apiClient.createService(PlaidApi.class);

        return plaidClient;
    }

    PlaidApi plaidClient = createPlaidClient();

    public LinkTokenCreateResponse getDevAccessToken() throws IOException {
        // Create a User
        LinkTokenCreateRequestUser user = new LinkTokenCreateRequestUser().clientUserId("user-1-java");

        // Create a link_token request for the user
        LinkTokenCreateRequest linkTokenRequest = new LinkTokenCreateRequest()
                .user(user)
                .clientName("Personal Finance App")
                .products(Arrays.asList(Products.TRANSACTIONS, Products.AUTH))
                .countryCodes(List.of(CountryCode.US))
                .language("en");

        // Create link_token
        Response<LinkTokenCreateResponse> linkTokenResponse = plaidClient.linkTokenCreate(linkTokenRequest).execute();

        // Send the data to the client
        return linkTokenResponse.body();
    }

    // Create access_token for sandbox testing - bypasses link flow
    public String getSandboxAccessToken() throws IOException {
        SandboxPublicTokenCreateRequest sandboxPublicRequest = new SandboxPublicTokenCreateRequest()
            .institutionId("ins_109508")
            .initialProducts(Arrays.asList(Products.TRANSACTIONS, Products.AUTH));

        Response<SandboxPublicTokenCreateResponse> sandboxPublicResponse = plaidClient.sandboxPublicTokenCreate(sandboxPublicRequest).execute();
           
        // The generated public_token can now be exchanged for an access_token
        ItemPublicTokenExchangeRequest accessRequest = new ItemPublicTokenExchangeRequest().publicToken(sandboxPublicResponse.body().getPublicToken());

        Response<ItemPublicTokenExchangeResponse> accessResponse = plaidClient.itemPublicTokenExchange(accessRequest).execute();
        if (accessResponse.isSuccessful() && accessResponse.body() != null){
            setAccessToken(accessResponse.body().getAccessToken()); //set global access token
            System.out.println("getSandboxAccessToken(): " + accessResponse.body().getAccessToken());
            System.out.println("static accessToken: " + accessToken);
            return accessToken;
        } 
        else throw new RuntimeException("Failed to create access token");
    }


    public List<Transaction> getTransactions(String accesToken) throws IOException{     
        // Provide a cursor from your database if you've previously recieved one for the item leave null if this is your first sync call for this item. 
        // The first request will return a cursor.
        String cursor = null;

        // New transaction updates since "cursor"
        List<Transaction> added = new ArrayList<Transaction>();
        List<Transaction> modified = new ArrayList<Transaction>();
        List<RemovedTransaction> removed = new ArrayList<RemovedTransaction>();
        boolean hasMore = true;
        TransactionsSyncRequestOptions options = new TransactionsSyncRequestOptions().includePersonalFinanceCategory(true);
        Response<TransactionsSyncResponse> transactionResponse;

        // Iterate through each page of new transaction updates for item
        while(hasMore){
            TransactionsSyncRequest transactionRequest = new TransactionsSyncRequest()
                .accessToken(accessToken)
                .cursor(cursor)
                .options(options);

            System.out.println("getTransactions() Token: " + accessToken);
            System.out.println("getTransactions() Request: " + transactionRequest);

            transactionResponse = plaidClient.transactionsSync(transactionRequest).execute();

            // System.out.println("getTransactions() Body Before: " + transactionResponse.body() + '\n' + "hasMore: " + hasMore);

            // // Add this page of results if not null
            added.addAll(transactionResponse.body().getAdded());
            modified.addAll(transactionResponse.body().getModified());
            removed.addAll(transactionResponse.body().getRemoved());

            hasMore = transactionResponse.body().getHasMore();
            cursor = transactionResponse.body().getNextCursor();

            System.out.println("getTransactions() Body After: " + transactionResponse.body() + '\n' + "hasMore: " + hasMore);
        }

        //Return latest 3 transactions
        List<Transaction> transactions = new ArrayList<Transaction>();
        transactions.addAll(added);
        transactions.addAll(modified);
        transactions.sort(Comparator.comparing(Transaction::getDate).reversed());
        System.out.println("Number of transactions: " + transactions.size());
        // return new TransactionsSyncResponse().transactions(transactions.subList(0, 3));
        return transactions;
    }
}