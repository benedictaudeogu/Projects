package com.budget;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.jdbc.DataSourceAutoConfiguration;
import org.springframework.jdbc.core.JdbcTemplate;

@SpringBootApplication()
public class BudgetTrackerApplication implements CommandLineRunner{

	public static void main(String[] args) {
		SpringApplication.run(BudgetTrackerApplication.class, args);
	}

	@Autowired
    private JdbcTemplate jdbcTemplate;

    @Override
    public void run(String... args) throws Exception {
        String sql = "insert into users (username, password, email) values (?, ?, ?)";
        int result = jdbcTemplate.update(sql, "user_good", "pass_good", "123@test.com");
        if (result > 0) System.out.println("A new row has been inserted.");         
    }
}
