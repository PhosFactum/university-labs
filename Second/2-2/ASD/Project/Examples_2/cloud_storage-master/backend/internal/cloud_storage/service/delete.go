package service

import (
	"context"
)

func (s Service) DeleteFile(ctx context.Context, id int) error {
	tx, err := s.repo.Db.BeginTxx(ctx, nil)
	if err != nil {
		return err
	}
	// Defer a rollback in case anything fails.
	defer tx.Rollback()
	err = s.repo.DeleteFile(ctx, id)
	if err != nil {
		return err
	}

	err = tx.Commit()
	return err
}
