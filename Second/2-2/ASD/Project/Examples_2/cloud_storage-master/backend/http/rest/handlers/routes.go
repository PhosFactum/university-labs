package handlers

import (
	"net/http"

	"github.com/gorilla/mux"
	"github.com/jmoiron/sqlx"
	"github.com/sirupsen/logrus"
)

func Register(r *mux.Router, lg *logrus.Logger, db *sqlx.DB) {
	handler := newHandler(lg, db)
	// adding logger middleware
	r.Use(handler.MiddlewareLogger())
	r.HandleFunc("/healthz", handler.Health())
	r.HandleFunc("/v1/api/auth", handler.Auth()).Methods(http.MethodPost)
	r.HandleFunc("/v1/api/get_file/{id}", handler.GetFile()).Methods(http.MethodGet)
	r.HandleFunc("/v1/api/delete_file/{id}", handler.Delete()).Methods(http.MethodDelete)
	r.HandleFunc("/v1/api/get_files/{user_id}", handler.FilesList()).Methods(http.MethodGet)
	r.HandleFunc("/v1/api/send_file", handler.SendFile()).Methods(http.MethodPost)
}
