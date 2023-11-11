package com.budget.controller;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;

import com.budget.service.BudgetService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import com.plaid.client.model.AccountBalance;
import com.plaid.client.model.AccountBase;
import com.plaid.client.model.AccountsGetRequest;
import com.plaid.client.model.AccountsGetResponse;
import com.plaid.client.model.Institution;
import com.plaid.client.model.LinkTokenCreateResponse;
import com.plaid.client.model.Transaction;

import retrofit2.Response;

@RestController
@CrossOrigin(origins="http://localhost:3000")
public class BudgetController {
    @Autowired
    BudgetService budgetService;

    // homepath - 'http://localhost:8080/'
    @GetMapping("/")
    public void home(){}

    @GetMapping("/getLinkToken")
    public LinkTokenCreateResponse getDevAccessToken() throws IOException{
        return budgetService.getDevAccessToken();
    }

    @GetMapping("/getSandboxAccessToken")
    public String getSandboxAccessToken() throws IOException{
        return budgetService.getSandboxAccessToken();
    }

    @GetMapping("/getTransactions")
    public List<Transaction> getTransactions() throws IOException{
        return budgetService.getTransactions(budgetService.getAccessToken());
    }

    @GetMapping("/getInstitutions")
    public List<Institution> getInstitutions() throws IOException{
        return budgetService.getInstitutions();
    }

    @GetMapping("/getAccounts")
    public List<AccountBase> getAccounts() throws IOException{
        return budgetService.getAccounts();
    }

    @GetMapping("/getBalances")
    public HashMap<String, AccountBalance> getBalancesRefreshed() throws IOException{
        return budgetService.getBalancesRefreshed();
    }

    /* TODO: Combine initialization steps to only generate once each token */
}