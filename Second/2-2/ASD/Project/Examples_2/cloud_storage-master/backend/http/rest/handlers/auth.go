package handlers

import (
	"fmt"
	"net/http"

	cloudStorageService "github.com/fir1/rest-api/internal/cloud_storage/service"
)

func (s service) Auth() http.HandlerFunc {
	type request struct {
		Telegram_id int    `json:"telegram_id"`
		Username    string `json:"username"`
	}

	type response struct {
		Message string `json:"message"`
	}

	return func(w http.ResponseWriter, r *http.Request) {
		req := request{}
		// Try to decode the request body into the struct. If there is an error,
		// respond to the client with the error message and a 400 status code.
		err := s.decode(r, &req)
		if err != nil {
			fmt.Println(err)
			s.respond(w, err, 0)
			return
		}

		err = s.cloudStorageService.CreateUser(r.Context(), cloudStorageService.CreateParams{
			Telegram_id: req.Telegram_id,
			Username:    req.Username,
		})
		if err != nil {
			s.respond(w, err, 0)
			return
		}
		s.respond(w, response{Message: "OK"}, http.StatusOK)
	}
}
