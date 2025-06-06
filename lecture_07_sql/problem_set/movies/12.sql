SELECT movies.title
FROM stars AS s1
JOIN stars AS s2 ON s1.movie_id = s2.movie_id
JOIN people AS p1 ON s1.person_id = p1.id
JOIN people AS p2 ON s2.person_id = p2.id
JOIN movies ON s1.movie_id = movies.id
WHERE p1.name = 'Bradley Cooper' AND p2.name = 'Jennifer Lawrence';



