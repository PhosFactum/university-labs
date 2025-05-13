package ru.ikvt.dagprojbot.boot;

import org.json.JSONArray;
import org.json.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.telegram.telegrambots.bots.TelegramLongPollingBot;
import org.telegram.telegrambots.meta.api.methods.GetFile;
import org.telegram.telegrambots.meta.api.methods.send.SendDocument;
import org.telegram.telegrambots.meta.api.methods.send.SendMessage;
import org.telegram.telegrambots.meta.api.objects.Document;
import org.telegram.telegrambots.meta.api.objects.File;
import org.telegram.telegrambots.meta.api.objects.InputFile;
import org.telegram.telegrambots.meta.api.objects.Update;
import org.telegram.telegrambots.meta.api.objects.replykeyboard.InlineKeyboardMarkup;
import org.telegram.telegrambots.meta.api.objects.replykeyboard.buttons.InlineKeyboardButton;
import org.telegram.telegrambots.meta.exceptions.TelegramApiException;
import ru.ikvt.dagprojbot.api.SimpleZakharovAPI;
import ru.ikvt.dagprojbot.api.ZakharovAPI;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.Base64;
import java.util.List;
import java.util.Objects;

public class DagaevProjectTelegramBot extends TelegramLongPollingBot {

    private static final Logger LOGGER = LoggerFactory.getLogger(DagaevProjectTelegramBot.class);

    private final String NAME;

    private final String TOKEN;

    private final ZakharovAPI API;

    public DagaevProjectTelegramBot( String name, String token ) {
        super(token);
        this.NAME = name;
        this.TOKEN = token;
        this.API = new SimpleZakharovAPI();
    }

    @Override
    public void onUpdateReceived( Update update ) {
        LOGGER.info("Event received.");
        if ( update.hasMessage() ) {
            try {
                onMessageReceived( update );
            } catch ( Exception ex ) {
                LOGGER.error("onMessageReceived. Something went wrong when connecting the server.");
            }
        } else if ( update.hasCallbackQuery() ) {
            try {
                onButtonClicked( update );
            } catch ( Exception ex ) {
                LOGGER.error("onButtonClicked. Something went wrong when connecting the server.");
            }
        }
    }

    private void onMessageReceived( Update update ) throws Exception {
        long chatId = update.getMessage().getChatId();
        LOGGER.info("Message detected in event received.");
        if ( update.getMessage().hasText() && !update.getMessage().hasDocument() ) {
            String action = update.getMessage().getText();
            switch ( action ) {
                case "/start":
                    LOGGER.info("/start operation is selected.");
                    auth( update );
                    listCommands( chatId );
                    break;
                case "/get_file":
                    LOGGER.info("/get_file operation is selected.");
                    preprocessKeyboard( update, CallbackResponseAction.GET );
                    break;
                case "/delete_file":
                    LOGGER.info("/delete_file operation is selected.");
                    preprocessKeyboard( update, CallbackResponseAction.DELETE );
                    break;
                case "/help":
                    LOGGER.info("/help operation is selected.");
                    listCommands( chatId );
                    break;
                default:
                    LOGGER.info("Unexpected command selected.");
                    notify( chatId, "Incorrect command. Choose one from the following list: " );
                    listCommands( chatId );
            }
        } else if ( update.getMessage().hasDocument() ) {
            LOGGER.info("/send_file operation is selected.");
            send( update );
            notify( chatId, "Uploaded." );
        }
    }

    private void onButtonClicked( Update update ) throws Exception {
        if ( update.hasCallbackQuery() ) {
            String[] callbackArray = update.getCallbackQuery().getData().split("-");
            long fileId = Long.parseLong( callbackArray[0] );
            long chatId = Long.parseLong( callbackArray[2] );
            CallbackResponseAction action =
                    ( Objects.equals(callbackArray[1], "download") ) ?
                            CallbackResponseAction.GET : CallbackResponseAction.DELETE;
            respondCallback( chatId, fileId, action );
            if ( action == CallbackResponseAction.GET ) {
                notify( chatId, "Downloaded." );
            } else {
                notify( chatId, "Deleted." );
            }
        }
    }

    private void auth( Update update ) throws Exception {
        long chatId = update.getMessage().getChatId();
        String username = update.getMessage().getFrom().getUserName();
        API.authenticate( chatId, username );
        notify( chatId, username + ", you're about to interact with this bot. " );
    }

    private void send( Update update ) throws Exception {
        long messageId = update.getMessage().getMessageId();
        long userId = update.getMessage().getFrom().getId();
        Document document = update.getMessage().getDocument();
        String fileName = document.getFileName();
        String base64str = getBase64str( document );
        long size = document.getFileSize();
        API.send( userId, messageId, fileName, size, base64str );
    }

    private void preprocessKeyboard( Update update, CallbackResponseAction action ) throws Exception {
        long userId = update.getMessage().getFrom().getId();
        long chatId = update.getMessage().getChatId();
        JSONObject files = API.getFilesData( userId );
        setButtons( chatId, files, action );
    }

    private void sendFile( long chatId, InputFile fileToSend ) {
        SendDocument sendDocument = new SendDocument();
        sendDocument.setChatId( String.valueOf(chatId) );
        sendDocument.setDocument( fileToSend );
        try {
            execute(sendDocument);
        } catch (Exception e) {
            LOGGER.error("Unable to send file to chat.");
        }
    }

    private InputFile recoverFile( String filename, String base64str ) {
        ByteArrayInputStream stream = null;
        try {
            byte[] data = Base64.getDecoder().decode(base64str);
            stream = new ByteArrayInputStream( data );
        } catch (IllegalArgumentException e) {
            LOGGER.error("Error occurred while decoding the base64 string.");
        }
        return new InputFile( stream, filename );
    }

    private void respondCallback( long chatId, long fileId, CallbackResponseAction action ) throws Exception {
        if ( action == CallbackResponseAction.GET ) {
            JSONObject json = API.retrieve( fileId );
            String filename = (String) json.get("filename");
            String base64str = (String) json.get("file_body");
            InputFile fileToSend = recoverFile( filename, base64str );
            sendFile( chatId, fileToSend );
        } else {
            API.delete( fileId );
        }
    }

    private void setButtons( long chatId, JSONObject files, CallbackResponseAction action ) {
        SendMessage sendMessage = new SendMessage();
        sendMessage.setChatId( chatId );
        String text = (action == CallbackResponseAction.GET) ? "download" : "delete";
        sendMessage.setText("Select the file you wish to " + text + ":");

        InlineKeyboardMarkup markup = new InlineKeyboardMarkup();
        List<List<InlineKeyboardButton>> keyboard = new ArrayList<>();
        List<InlineKeyboardButton> buttons = new ArrayList<>();

        JSONArray filesArray = files.getJSONArray("files");
        for ( Object obj : filesArray ) {
            InlineKeyboardButton button = new InlineKeyboardButton();
            JSONObject json = (JSONObject) obj;
            String buttonText = (String) json.get("filename");
            String callback = String.valueOf(json.get("id"));
            button.setText( callback + "-" + buttonText );
            button.setCallbackData( callback + "-" + text + "-" + chatId );
            buttons.add(button);
        }

        keyboard.add(buttons);
        markup.setKeyboard(keyboard);

        sendMessage.setReplyMarkup( markup );

        try {
            execute(sendMessage);
        } catch (Exception e) {
            LOGGER.error("Unable to display keyboard to chat.");
        }
    }

    private String getBase64str(Document document) {

        String base64str = null;
        HttpURLConnection connection = null;
        String fileId = document.getFileId();

        try {
            GetFile getFile = new GetFile();
            getFile.setFileId(fileId);
            File file = execute(getFile);
            String filePath = file.getFilePath();
            String endpoint = "https://api.telegram.org/file/bot" + TOKEN + "/" + filePath;
            try {
                URL url = new URL(endpoint);
                connection = (HttpURLConnection) url.openConnection();
                connection.setRequestMethod("GET");

                try (InputStream inputStream = connection.getInputStream()) {
                    ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
                    byte[] buffer = new byte[4096]; // 1024
                    int bytesRead;
                    while ( (bytesRead = inputStream.read(buffer)) != -1 ) {
                        byteArrayOutputStream.write(buffer, 0, bytesRead);
                    }
                    base64str = Base64
                            .getEncoder()
                            .encodeToString( byteArrayOutputStream.toByteArray() );
                    byteArrayOutputStream.close();
                }

                if (connection.getResponseCode() == HttpURLConnection.HTTP_OK) {
                    LOGGER.info("Successful bytes-base64str transforming.");
                } else {
                    LOGGER.error("Non OK HTTP Status. Something went wrong while connecting the server.");
                }

            } catch ( Exception ex ) {
                LOGGER.error("Something went wrong while connecting the server.");
            } finally {
                connection.disconnect();
                LOGGER.info("GetBase64String. Connection interrupted.");
            }
        } catch ( Exception ex ) {
            LOGGER.error("Something went wrong while preparing the file.");
        }

        return base64str;

    }

    private void listCommands( long chatId ) {
        notify( chatId, "Available commands to use: \n" +
                "/start - to authenticate yourself; \n" +
                "To send the file just attach it to the message with random or no text; \n" +
                "/get_file - to search a file by name; \n" +
                "/delete_file - to delete a file by name; \n" +
                "/help - to display command list." );
    }

    private void notify( long chatId, String text ) {
        SendMessage message = new SendMessage();
        message.setChatId(chatId);
        message.setText(text);
        try {
            execute(message);
        } catch (TelegramApiException e) {
            LOGGER.error("Unable to send message to chat.");
        }
    }

    @Override
    public String getBotUsername() {
        return NAME;
    }

}