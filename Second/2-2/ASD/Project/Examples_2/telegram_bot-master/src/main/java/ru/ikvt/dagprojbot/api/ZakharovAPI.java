package ru.ikvt.dagprojbot.api;

import org.json.JSONArray;
import org.json.JSONObject;

public interface ZakharovAPI {

    void authenticate( long userId, String username ) throws Exception;

    void send( long userId, long messageId, String fileName, long size, String base64str ) throws Exception;

    JSONObject getFilesData( long userId ) throws Exception;

    JSONObject retrieve( long fileId ) throws Exception;

    void delete( long fileId ) throws Exception;

}
