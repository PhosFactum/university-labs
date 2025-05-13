package service

import (
	"context"
	"errors"

	"github.com/fir1/rest-api/internal/cloud_storage/model"
	"github.com/fir1/rest-api/pkg/db"
	"github.com/fir1/rest-api/pkg/erru"
)

func (s Service) GetFile(ctx context.Context, id int) (model.Files, error) {
	file, err := s.repo.FindFile(ctx, id)
	switch {
	case err == nil:
	case errors.As(err, &db.ErrObjectNotFound{}):
		return model.Files{}, erru.ErrArgument{Wrapped: errors.New("todo object not found")}
	default:
		return model.Files{}, err
	}
	return file, nil
}
