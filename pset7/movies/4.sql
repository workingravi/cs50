--SELECT COUNT(title) FROM movies JOIN ratings on movies.id = ratings.movie_id WHERE ROUND(ratings.rating,1) = 10.0;
SELECT COUNT(title) FROM movies WHERE id IN
(SELECT movie_id FROM ratings WHERE rating = 10.0);