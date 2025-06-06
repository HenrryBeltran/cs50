SELECT DISTINCT p2.name
FROM stars AS s1
JOIN stars AS s2 ON s2.movie_id = s1.movie_id
JOIN people AS p1 ON s1.person_id = p1.id
JOIN people AS p2 ON s2.person_id = p2.id
JOIN movies ON s1.movie_id = movies.id
WHERE
    p1.name = 'Kevin Bacon' AND
    p1.birth = 1958 AND
    p2.name != 'Kevin Bacon';

