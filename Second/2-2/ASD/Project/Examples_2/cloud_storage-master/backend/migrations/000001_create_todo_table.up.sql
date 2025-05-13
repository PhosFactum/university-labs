CREATE TABLE Users
(
    telegram_id INT NOT NULL,
    username TEXT NOT NULL,
    
    PRIMARY KEY (telegram_id)
);

CREATE TABLE Files
(
    id SERIAL,
    
    description TEXT,
    file_size INT NOT NULL,
    filename TEXT NOT NULL,
    uploaded_at TIMESTAMP(0) WITHOUT TIME ZONE NOT NULL,
    user_id INT NOT NULL REFERENCES Users,
    message_id INT NOT NULL,

    PRIMARY KEY (id)
);
