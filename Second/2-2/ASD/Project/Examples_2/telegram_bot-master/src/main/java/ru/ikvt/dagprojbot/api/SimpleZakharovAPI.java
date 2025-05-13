package ru.ikvt.dagprojbot.api;

import org.json.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.nio.charset.StandardCharsets;

public class SimpleZakharovAPI implements ZakharovAPI {

    private static final Logger LOGGER = LoggerFactory.getLogger(SimpleZakharovAPI.class);

    String prefix = "http://192.168.43.149:8080/v1/api";

    @Override
    public void authenticate( long userId, String username ) throws Exception {

        JSONObject authRequest = new JSONObject();
        authRequest.put("telegram_id", userId);
        authRequest.put("username", username);

        String jsonString = authRequest.toString();
        byte[] data = jsonString.getBytes( StandardCharsets.UTF_8 );

        HttpURLConnection connection = null;
        String endpoint = prefix + "/auth";
        try {
            URL url = new URL(endpoint);
            connection = (HttpURLConnection) url.openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/json");
            connection.setRequestProperty("Accept", "application/json");
            connection.setRequestProperty("Content-Length", String.valueOf( data.length ));

            try (OutputStream outputStream = connection.getOutputStream()) {
                outputStream.write( data, 0, data.length );
            } catch (IOException ex) {
                throw new Exception("Non OK HTTP Status. Something went wrong while connecting the server.");
            }

            if ( connection.getResponseCode() == HttpURLConnection.HTTP_OK ) {
                LOGGER.info("Authenticate. Authentication successful");
            }

        } catch (IOException ex) {
            LOGGER.error("Non OK HTTP Status. Something went wrong while connecting the server.");
        } finally {
            connection.disconnect();
            LOGGER.info("Authenticate. Connection interrupted.");
        }

    }

    @Override
    public void send( long userId, long messageId, String fileName, long size, String base64str ) throws Exception {

        JSONObject authRequest = new JSONObject();
        authRequest.put("file_size", size);
        authRequest.put("filename", fileName);
        // authRequest.put("uploaded_at", LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy:MM:dd mm:HH")));
        authRequest.put("message_id", messageId);
        authRequest.put("user_id", userId);
        authRequest.put("description", "<empty>");
        authRequest.put("file_body", base64str);

        String jsonString = authRequest.toString();
        byte[] data = jsonString.getBytes( StandardCharsets.UTF_8 );

        HttpURLConnection connection = null;
        String endpoint = prefix + "/send_file";
        try {
            URL url = new URL(endpoint);
            connection = (HttpURLConnection) url.openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/json");
            connection.setRequestProperty("Accept", "application/json");
            connection.setRequestProperty("Content-Length", String.valueOf( data.length ));

            try (OutputStream outputStream = connection.getOutputStream()) {
                outputStream.write( data, 0, data.length );
            } catch (IOException ex) {
                throw new Exception("Non OK HTTP Status. Something went wrong while connecting the server.");
            }

            if ( connection.getResponseCode() == HttpURLConnection.HTTP_OK ) {
                LOGGER.info("Send. File sent.");
            }

        } catch (IOException ex) {
            ex.printStackTrace();
        } finally {
            connection.disconnect();
            LOGGER.info("Send. Connection interrupted.");
        }

    }

    @Override
    public JSONObject getFilesData( long userId ) throws Exception {

        StringBuilder sb = new StringBuilder();

        HttpURLConnection connection = null;
        String endpoint = prefix + "/get_files/" + userId;
        try {
            URL url = new URL(endpoint);
            connection = (HttpURLConnection) url.openConnection();
            connection.setDoInput(true);
            connection.setRequestMethod("GET");
            connection.setRequestProperty("Content-Type", "application/json");
            connection.setRequestProperty("Accept", "application/json");

            try (InputStream inputStream = connection.getInputStream()) {
                BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
                String line;
                while ( (line = reader.readLine()) != null ) {
                    sb.append(line);
                }
            }

            if ( connection.getResponseCode() == HttpURLConnection.HTTP_OK ) {
                LOGGER.info("GetFilesData. Files data received.");
            } else {
                throw new Exception("Non OK HTTP Status. Something went wrong while connecting the server.");
            }

        } catch (IOException ex) {
            ex.printStackTrace();
        } finally {
            connection.disconnect();
            LOGGER.info("GetFilesData. Connection interrupted.");
        }

        return new JSONObject( sb.toString() );

    }

    @Override
    public JSONObject retrieve( long fileId ) throws Exception {

        StringBuilder sb = new StringBuilder();

        HttpURLConnection connection = null;
        String endpoint = prefix + "/get_file/" + fileId;
        try {
            URL url = new URL(endpoint);
            connection = (HttpURLConnection) url.openConnection();
            connection.setDoInput(true);
            connection.setRequestMethod("GET");
            connection.setRequestProperty("Content-Type", "application/json");
            connection.setRequestProperty("Accept", "application/json");

            try (InputStream inputStream = connection.getInputStream()) {
                BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
                String line;
                while ( (line = reader.readLine()) != null ) {
                    sb.append(line);
                }
            }

            if ( connection.getResponseCode() == HttpURLConnection.HTTP_OK ) {
                LOGGER.info("Get. File received.");
            } else {
                throw new Exception("Non OK HTTP Status. Something went wrong while connecting the server.");
            }

        } catch (IOException ex) {
            ex.printStackTrace();
        } finally {
            connection.disconnect();
            LOGGER.info("Get. Connection interrupted.");
        }

        return new JSONObject( sb.toString() );

    }

    @Override
    public void delete( long fileId ) throws Exception {

        HttpURLConnection connection = null;
        String endpoint = prefix + "/delete_file/" + fileId;
        try {
            URL url = new URL(endpoint);
            connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            connection.setRequestProperty("Content-Type", "application/json");
            connection.setRequestProperty("Accept", "application/json");

            if ( connection.getResponseCode() != HttpURLConnection.HTTP_OK ) {
                throw new Exception("Non OK HTTP Status. Something went wrong while connecting the server.");
            }

            LOGGER.info("Delete. File deleted.");

        } catch (IOException ex) {
            ex.printStackTrace();
        } finally {
            connection.disconnect();
            LOGGER.info("Delete. Connection interrupted.");
        }

    }

}