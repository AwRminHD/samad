all:
	gcc -I src/include -L src/lib -o main main.c sql/sqlite3.c sql/database.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf