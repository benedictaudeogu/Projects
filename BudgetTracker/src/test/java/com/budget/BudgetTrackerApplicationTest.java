package com.budget;

import static org.junit.Assert.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import org.junit.*;

import java.io.IOException;
import java.util.HashMap;

import org.junit.jupiter.api.Test;
import org.mockito.Mockito.*;
import org.springframework.boot.test.context.SpringBootTest;

import com.budget.service.BudgetService;
import com.plaid.client.ApiClient;
import com.plaid.client.model.AccountBalance;
import com.plaid.client.model.AccountBase;
import com.plaid.client.model.AccountsBalanceGetRequest;
import com.plaid.client.model.AccountsGetResponse;
import com.plaid.client.model.SandboxPublicTokenCreateRequest;
import com.plaid.client.request.PlaidApi;

import io.github.cdimascio.dotenv.Dotenv;

@SpringBootTest
public class BudgetTrackerApplicationTest{
	private static final Dotenv dotenv = Dotenv.load();
    private static final String CLIENT_ID = dotenv.get("PLAID_CLIENT_ID");
    private static final  String SECRET = dotenv.get("PLAID_SECRET");
    private static final  String PLAID_ENV = dotenv.get("PLAID_ENV");
	
	@Test
	public void testCreatePlaidClient() throws Throwable{
	    // Arrange
	    HashMap<String, String> apiKeys = new HashMap<>();
	    apiKeys.put("clientId", CLIENT_ID);
	    apiKeys.put("secret", SECRET);
	
	    ApiClient apiClient = mock(ApiClient.class);
	    PlaidApi plaidApi = mock(PlaidApi.class);
	
	    // Act
	    when(apiClient.createService(PlaidApi.class)).thenReturn(plaidApi);

		// Assert
		assertNotNull(plaidApi);
		
		// Print the contents if the assertion passes
        System.out.println("Contents of the result: " + plaidApi);
	}
	
	@Test
	public void testgetSandboxAccessToken() throws Throwable{
		//Arrange
		SandboxPublicTokenCreateRequest sandboxPublicRequest = mock(SandboxPublicTokenCreateRequest.class);
		
		//Act
		
		//Assert
		
		//Print the contents if the assertion passes
		System.out.println(sandboxPublicRequest);
	}
}
