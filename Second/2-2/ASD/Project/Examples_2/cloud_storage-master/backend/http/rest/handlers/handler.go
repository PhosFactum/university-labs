package handlers

import (
	cloudStorageRepo "github.com/fir1/rest-api/internal/cloud_storage/repository"
	cloudStorageService "github.com/fir1/rest-api/internal/cloud_storage/service"
	"github.com/jmoiron/sqlx"
	"github.com/sirupsen/logrus"
)

type service struct {
	logger *logrus.Logger
	// router      *mux.Router
	cloudStorageService cloudStorageService.Service
}

func newHandler(lg *logrus.Logger, db *sqlx.DB) service {
	return service{
		logger:              lg,
		cloudStorageService: cloudStorageService.NewService(cloudStorageRepo.NewRepository(db)),
	}
}
