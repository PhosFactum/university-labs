package handlers

import (
	"fmt"
	"net/http"
	"time"

	cloudStorageService "github.com/fir1/rest-api/internal/cloud_storage/service"
)

func (s service) SendFile() http.HandlerFunc {
	type request struct {
		Description string    `json:"description"`
		File_size   int       `json:"file_size"`
		Filename    string    `json:"filename"`
		Uploaded_at time.Time `json:"uploaded_at"`
		User_id     int       `json:"user_id"`
		Message_id  int       `json:"message_id"`
		File_body   string    `json:"file_body"`
	}

	type response struct {
		Message string `json:"message"`
	}

	return func(w http.ResponseWriter, r *http.Request) {
		fmt.Println(1)
		req := request{}
		// Try to decode the request body into the struct. If there is an error,
		// respond to the client with the error message and a 400 status code.
		err := s.decode(r, &req)
		if err != nil {
			s.respond(w, err, 0)
			return
		}
		s.cloudStorageService.CreateFile(r.Context(), cloudStorageService.CreateFileParams{
			Description: req.Description,
			File_size:   req.File_size,
			Filename:    req.Filename,
			Uploaded_at: req.Uploaded_at,
			User_id:     req.User_id,
			Message_id:  req.Message_id,
			File_body:   req.File_body,
		})
		s.respond(w, response{Message: "OK"}, http.StatusOK)
	}
}
