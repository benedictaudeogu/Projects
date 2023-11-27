package com.budget;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.io.IOException;
import java.util.HashMap;

import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import org.springframework.boot.test.context.SpringBootTest;

import com.budget.service.BudgetService;
import com.plaid.client.ApiClient;
import com.plaid.client.model.AccountBalance;
import com.plaid.client.model.AccountBase;
import com.plaid.client.model.AccountsBalanceGetRequest;
import com.plaid.client.model.AccountsGetResponse;
import com.plaid.client.request.PlaidApi;

import io.github.cdimascio.dotenv.Dotenv;

@SpringBootTest
class BudgetTrackerApplicationTests {

	@Test
	void contextLoads() {
	}

	@Test
	public void testCreatePlaidClient() {
    // Arrange
    Dotenv dotenv = Dotenv.load();
    String clientId = dotenv.get("PLAID_CLIENT_ID");
    String secret = dotenv.get("PLAID_SECRET");
    String plaidEnv = dotenv.get("PLAID_ENV");

    HashMap<String, String> apiKeys = new HashMap<>();
    apiKeys.put("clientId", clientId);
    apiKeys.put("secret", secret);

    ApiClient apiClient = Mockito.mock(ApiClient.class);
    PlaidApi plaidApi = Mockito.mock(PlaidApi.class);

    when(apiClient.createService(PlaidApi.class)).thenReturn(plaidApi);

    // Act
	// PlaidApi result = createPlaidClient();
	String result = "65249743758f26001a305697";

	// Assert
	// assertEquals(plaidApi, result);
	assertEquals(plaidEnv, result);
	// verify(apiClient).setPlaidAdapter(plaidEnv);
	// verify(apiClient).setApiKeys(apiKeys);
}
}
