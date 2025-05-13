package service

import "github.com/fir1/rest-api/internal/cloud_storage/repository"

type Service struct {
	repo repository.Repository
}

func NewService(r repository.Repository) Service {
	return Service{
		repo: r,
	}
}
