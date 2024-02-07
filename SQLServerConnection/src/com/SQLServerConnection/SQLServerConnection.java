package com.SQLServerConnection;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class SQLServerConnection {
    public static void main(String[] args) {
        // Database credentials
        String url = "jdbc:sqlserver://localhost:1521;databaseName=SQLServerConnection";
        String user = "test123";
        String password = "test123";

        // Establishing the connection
        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            if (connection != null) {
                System.out.println("Connected to the database!");
                // Perform database operations here
            } else {
                System.out.println("Failed to make connection!");
            }
        } catch (SQLException e) {
            System.err.println("Connection failed! Error message: " + e.getMessage());
        }
    }
}

