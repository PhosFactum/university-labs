POSTGRESQL_URL = "postgresql://myuser:mypassword@localhost:5433/mydatabase?sslmode=disable"

migrate:
	migrate -database ${POSTGRESQL_URL}  -path migrations up


rollback_migrate:
	migrate -database ${POSTGRESQL_URL} -path migrations down

# migrate -database postgresql://myuser:mypassword@localhost:5433/mydatabase?sslmode=disable -path migrations up
