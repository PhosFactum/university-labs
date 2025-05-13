package service

import (
	"context"
	"fmt"
	"time"

	"github.com/asaskevich/govalidator"
	"github.com/fir1/rest-api/internal/cloud_storage/model"
	"github.com/fir1/rest-api/pkg/erru"
)

type CreateParams struct {
	Telegram_id int    `valid:"required"`
	Username    string `valid:"required"`
}

type CreateFileParams struct {
	Description string
	File_size   int
	Filename    string
	Uploaded_at time.Time
	User_id     int
	Message_id  int
	File_body   string
}

func (s Service) CreateUser(ctx context.Context, params CreateParams) error {
	if _, err := govalidator.ValidateStruct(params); err != nil {
		return erru.ErrArgument{Wrapped: err}
	}

	tx, err := s.repo.Db.BeginTxx(ctx, nil)
	if err != nil {
		return err
	}
	// Defer a rollback in case anything fails.
	defer tx.Rollback()

	entity := model.Users{
		Telegram_id: params.Telegram_id,
		Username:    params.Username,
	}
	err = s.repo.Create(ctx, &entity)
	if err != nil {
		return err
	}

	err = tx.Commit()
	return err
}

func (s Service) CreateFile(ctx context.Context, params CreateFileParams) error {
	if _, err := govalidator.ValidateStruct(params); err != nil {
		return erru.ErrArgument{Wrapped: err}
	}

	tx, err := s.repo.Db.BeginTxx(ctx, nil)
	if err != nil {
		return err
	}
	// Defer a rollback in case anything fails.
	defer tx.Rollback()

	entity := model.Files{
		Description: params.Description,
		File_size:   params.File_size,
		Filename:    params.Filename,
		Uploaded_at: params.Uploaded_at,
		User_id:     params.User_id,
		Message_id:  params.Message_id,
		File_body:   params.File_body,
	}
	_, err = s.repo.CreateFile(ctx, entity)
	if err != nil {
		fmt.Println(err, "qwe")
		return err
	}

	err = tx.Commit()
	return err
}
