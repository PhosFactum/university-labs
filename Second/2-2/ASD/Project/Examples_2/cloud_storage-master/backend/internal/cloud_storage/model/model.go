package model

import "time"

type Users struct {
	Telegram_id int    `db:"telegram_id"`
	Username    string `db:"username"`
}

type Files struct {
	Id          int       `db:"id"`
	Description string    `db:"description"`
	File_size   int       `db:"file_size"`
	Filename    string    `db:"filename"`
	Uploaded_at time.Time `db:"uploaded_at"`
	User_id     int       `db:"user_id"`
	Message_id  int       `db:"message_id"`
	File_body   string    `db:"file_body"`
}
