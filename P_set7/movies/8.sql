select name from
    movies join stars on movies.id = stars.movie_id join people
    on stars.person_id = people.id
where title = "Toy Story"
 -- Mohammadreza_mokhtari_kia
