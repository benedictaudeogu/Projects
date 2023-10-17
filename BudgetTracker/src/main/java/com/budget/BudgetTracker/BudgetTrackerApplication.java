package com.budget.BudgetTracker;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
@RequestMapping("/budget-tracker")
public class BudgetTrackerApplication implements CommandLineRunner{

	public static void main(String[] args) {
		SpringApplication.run(BudgetTrackerApplication.class, args);
	}

	@GetMapping()
	public String hello() {
		return "Test Response";
	}

	@Override
	public void run(String... args) throws Exception {
		System.out.println("*** Budget Tracker Application ***");
	}
}
