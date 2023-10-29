package com.budget.controller;

import java.io.IOException;
import java.util.List;

import com.budget.service.BudgetService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import com.plaid.client.model.Institution;
import com.plaid.client.model.LinkTokenCreateResponse;
import com.plaid.client.model.Transaction;

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
}
