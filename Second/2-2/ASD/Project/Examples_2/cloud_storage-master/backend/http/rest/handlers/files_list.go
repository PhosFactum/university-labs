package handlers

import (
	"net/http"
	"strconv"

	"github.com/fir1/rest-api/internal/cloud_storage/repository"
	cloudStorageService "github.com/fir1/rest-api/internal/cloud_storage/service"
	"github.com/gorilla/mux"
)

const OFFSET = 10

func (s service) FilesList() http.HandlerFunc {

	type response struct {
		Files []repository.FileHead `json:"files"`
	}

	return func(w http.ResponseWriter, r *http.Request) {
		vars := mux.Vars(r)

		// Try to decode the request body into the struct. If there is an error,
		// respond to the client with the error message and a 400 status code.

		var page, offset int

		page = 0
		if param := r.URL.Query().Get("page"); len(param) > 0 {
			page, _ = strconv.Atoi(param)
		}

		offset = OFFSET
		if param := r.URL.Query().Get("offset"); len(param) > 0 {
			offset, _ = strconv.Atoi(param)
		}

		user_id, err := strconv.Atoi(vars["user_id"])
		if err != nil {
			s.respond(w, err, 0)
			return
		}

		filesListResponse, err := s.cloudStorageService.GetFiles(r.Context(), cloudStorageService.GetFilesParams{
			User_id: user_id,
			Page:    page,
			Offset:  offset,
		})

		if err != nil {
			s.respond(w, err, 0)
			return
		}
		s.respond(w, response{Files: filesListResponse}, http.StatusOK)
	}
}
