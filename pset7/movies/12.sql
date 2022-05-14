SELECT title FROM
people JOIN stars on stars.person_id=people.id
JOIN movies on stars.movie_id = movies.id
WHERE name='Helena Bonham Carter'
INTERSECT
SELECT title FROM
people JOIN stars on stars.person_id=people.id
JOIN movies on stars.movie_id = movies.id
WHERE name='Johnny Depp'