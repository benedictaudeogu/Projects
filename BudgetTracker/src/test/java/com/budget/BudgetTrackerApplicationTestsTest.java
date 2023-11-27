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
    PlaidApi result = createPlaidClient();

    // Assert
    assertEquals(plaidApi, result);
    verify(apiClient).setPlaidAdapter(plaidEnv);
    verify(apiClient).setApiKeys(apiKeys);
}@Test
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
    PlaidApi result = createPlaidClient();

    // Assert
    assertEquals(plaidApi, result);
    verify(apiClient).setPlaidAdapter(plaidEnv);
    verify(apiClient).setApiKeys(apiKeys);
}