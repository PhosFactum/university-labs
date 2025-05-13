package service

import (
	"context"

	"github.com/fir1/rest-api/internal/cloud_storage/repository"
)

type GetFilesParams struct {
	User_id int
	Page    int
	Offset  int
}

func (s Service) GetFiles(ctx context.Context, params GetFilesParams) ([]repository.FileHead, error) {
	files, err := s.repo.ListFiles(ctx, params.User_id, params.Page, params.Offset)
	if err != nil {
		return []repository.FileHead{}, err
	}
	return files, nil
}
