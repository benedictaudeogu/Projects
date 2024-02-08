package com.budget;


import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

import java.io.IOException;
import java.util.Arrays;
import java.util.HashMap;

import org.junit.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import com.plaid.client.ApiClient;
import com.plaid.client.model.ItemPublicTokenExchangeRequest;
import com.plaid.client.model.ItemPublicTokenExchangeResponse;
import com.plaid.client.model.Products;
import com.plaid.client.model.SandboxPublicTokenCreateRequest;
import com.plaid.client.model.SandboxPublicTokenCreateResponse;
import com.plaid.client.request.PlaidApi;
import com.budget.service.*;
import io.github.cdimascio.dotenv.Dotenv;
import retrofit2.Response;

@SpringBootTest
public class BudgetServiceTest{
	BudgetService budgetService = new BudgetService();
	
	@Test
	public void testCreatePlaidClient() throws IOException{
		// Mock Dotenv
        Dotenv dotenvMock = mock(Dotenv.class);
        when(dotenvMock.get("PLAID_CLIENT_ID")).thenReturn("mockClientId");
        when(dotenvMock.get("PLAID_SECRET")).thenReturn("mockSecret");
        when(dotenvMock.get("PLAID_ENV")).thenReturn("https://sandbox.plaid.com");
        
//        HashMap<String, String> apiKeys = new HashMap<>();
//        apiKeys.put("clientId", "mockClientId");
//        apiKeys.put("secret", "mockSecret");
//        ApiClient apiClient = new ApiClient(apiKeys);
//        apiClient.setPlaidAdapter(dotenvMock.get("PLAID_ENV"));
        
        // Mock ApiClient and plaidClient
        ApiClient apiClientMock = mock(ApiClient.class);
        apiClientMock.setPlaidAdapter(dotenvMock.get("PLAID_ENV"));
        PlaidApi plaidClientMock = mock(PlaidApi.class);
        when(apiClientMock.createService(PlaidApi.class)).thenReturn(plaidClientMock);
                
        // Call the method under test
        PlaidApi plaidClient = budgetService.createPlaidClient();
        
        // Assert that the result is not null
        assertNotNull(plaidClient);
        assertEquals(plaidClient, plaidClientMock);
        System.out.println(plaidClient);
        System.out.println(plaidClientMock);
	}
	
//	@Test
//	public void testgetSandboxAccessToken() throws IOException{
//		SandboxPublicTokenCreateRequest sandboxPublicRequestMock = mock(SandboxPublicTokenCreateRequest.class);
//		
//	}
	
/*
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
*/
}
