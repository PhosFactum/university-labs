package handlers

import (
	"net/http"
	"strconv"
	"time"

	"github.com/gorilla/mux"
)

func (s service) GetFile() http.HandlerFunc {
	type response struct {
		Id          int       `json:"id"`
		Filename    string    `json:"filename"`
		File_size   int       `json:"file_size"`
		Uploaded_at time.Time `json:"uploaded_at"`
		File_body   string    `json:"file_body"`
	}
	return func(w http.ResponseWriter, r *http.Request) {
		vars := mux.Vars(r)

		id, _ := strconv.Atoi(vars["id"])

		getFileResponse, err := s.cloudStorageService.GetFile(r.Context(), id)
		if err != nil {
			s.respond(w, err, 0)
			return
		}
		s.respond(w, response{
			Id:          getFileResponse.Id,
			Filename:    getFileResponse.Filename,
			File_size:   getFileResponse.File_size,
			Uploaded_at: getFileResponse.Uploaded_at,
			File_body:   getFileResponse.File_body,
		}, http.StatusOK)
	}
}
