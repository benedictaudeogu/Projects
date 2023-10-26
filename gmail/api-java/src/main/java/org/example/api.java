package org.example;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.file.Path;
import java.util.Collections;
import java.util.List;

import com.google.api.client.auth.oauth2.Credential;
import com.google.api.client.extensions.java6.auth.oauth2.AuthorizationCodeInstalledApp;
import com.google.api.client.extensions.jetty.auth.oauth2.LocalServerReceiver;
import com.google.api.client.googleapis.auth.oauth2.GoogleAuthorizationCodeFlow;
import com.google.api.client.googleapis.auth.oauth2.GoogleClientSecrets;
import com.google.api.client.http.javanet.NetHttpTransport;
import com.google.api.client.json.JsonFactory;
import com.google.api.client.json.gson.GsonFactory;
import com.google.api.client.util.store.FileDataStoreFactory;

public class api {
    private static final List<String> SCOPE = Collections.singletonList("https://mail.google.com/");
    private static final String TOKEN_FILE_PATH = "../../../../../token.pickle";
    private static final String CREDENTIALS_FILE_PATH = "../../../../../credentials.json";
    private static final JsonFactory JSON_FACTORY = GsonFactory.getDefaultInstance();

    public static void main(String[] args) throws IOException {
        authenticate();
        // getCredentials(null);
        // System.out.println("Hello world!");
    }

    public static void authenticate() {
        // token.pickle stores user's access and refresh tokens, created automatically when the authorization flow completes for the first time
        File f = new File(TOKEN_FILE_PATH);
        if(f.isFile()){
            System.out.println("token.pickle exists");
            // if exists, load credentials from token.pickle
            // try {
            //     Path path = Path.of(TOKEN_FILE_PATH);
            //     String content = Files.readString(path);
            //     System.out.println(content);
            // } 
            // catch (Exception e) {
            //     System.out.println("Error reading token.pickle");
            // }
        } 
        else {
            System.out.println("token.pickle does not exist");
        }
    }

    // private static Credential getCredentials(final NetHttpTransport HTTP_TRANSPORT) throws IOException {
    //     // Load client secrets.
    //     InputStream in = api.class.getResourceAsStream(CREDENTIALS_FILE_PATH);
    //     if (in == null) {
    //     throw new FileNotFoundException("Resource not found: " + CREDENTIALS_FILE_PATH);
    //     }
    //     GoogleClientSecrets clientSecrets = GoogleClientSecrets.load(JSON_FACTORY, new InputStreamReader(in));

    //     // Build flow and trigger user authorization request.
    //     GoogleAuthorizationCodeFlow flow = new GoogleAuthorizationCodeFlow.Builder(HTTP_TRANSPORT, JSON_FACTORY, clientSecrets, SCOPE)
    //         .setDataStoreFactory(new FileDataStoreFactory(new java.io.File(TOKEN_FILE_PATH)))
    //         .setAccessType("offline")
    //         .build();

    //     LocalServerReceiver receiver = new LocalServerReceiver.Builder().setPort(8888).build();
    //     Credential credential = new AuthorizationCodeInstalledApp(flow, receiver).authorize("user");
        
    //     return credential;
    // }       
}