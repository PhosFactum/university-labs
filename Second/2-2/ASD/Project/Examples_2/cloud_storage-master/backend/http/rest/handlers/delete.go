package handlers

import (
	"net/http"
	"strconv"

	"github.com/gorilla/mux"
)

func (s service) Delete() http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		vars := mux.Vars(r)

		id, err := strconv.Atoi(vars["id"])
		if err != nil {
			s.respond(w, err, 0)
			return
		}

		err = s.cloudStorageService.DeleteFile(r.Context(), id)
		if err != nil {
			s.respond(w, err, 0)
			return
		}
		s.respond(w, nil, http.StatusOK)
	}
}
