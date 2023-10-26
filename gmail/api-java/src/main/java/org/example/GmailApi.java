package org.example;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Collections;
import java.util.List;

import com.google.api.services.gmail.Gmail;

public class GmailApi {
    private static final List<String> SCOPE = Collections.singletonList("https://mail.google.com/");
    private static final String TOKENS_DIRECTORY_PATH = "../../../../../token.pickle";
    private static final String CREDENTIALS_FILE_PATH = "../../../../../credentials.json";
    public static void main(String[] args) {
        authenticate();
        // find();
        // delete();
        // System.out.println("Hello world!");
    }

    public static void authenticate() {
        // token.pickle stores user's access and refresh tokens, created automatically when the authorization flow completes for the first time
        if(new File(TOKENS_DIRECTORY_PATH).exists() && !new File(TOKENS_DIRECTORY_PATH).isDirectory()){
            // if exists, load credentials from token.pickle
            System.out.println("token.pickle exists");
        } else {
            System.out.println("token.pickle does not exist");
        }
        
    }

    public static void find() {
        System.out.println("Finding...");
    }

    public static void delete() {
        System.out.println("Deleting...");
    }
}