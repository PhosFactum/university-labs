package ru.ikvt.dagprojbot.boot;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.telegram.telegrambots.meta.TelegramBotsApi;
import org.telegram.telegrambots.meta.exceptions.TelegramApiException;
import org.telegram.telegrambots.updatesreceivers.DefaultBotSession;

public class Main {

    private static final Logger LOGGER = LoggerFactory.getLogger(Main.class);

    public static void main(String[] args) {

        String name = "dagprojbot";
        String token = "7933878576:AAGd8YCQIfop1mI0lY3x1eeji_zKN55M1pQ";
        DagaevProjectTelegramBot bot = new DagaevProjectTelegramBot(name, token);
        try {
            TelegramBotsApi api = new TelegramBotsApi(DefaultBotSession.class);
            api.registerBot(bot);
            LOGGER.info("Bot is running.");
        } catch (TelegramApiException e) {
            LOGGER.error("Something went wrong while trying the bot to boot up");
            System.out.println( e.getMessage() );
        }

    }

}
