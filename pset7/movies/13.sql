SELECT title FROM



people JOIN stars on people.id = stars.person_id JOIN
movies on stars.movie_id = movies.id JOIN
ratings on movies.id = ratings.movie_id
WHERE name='Kevin Bacon'
