select title
from movies
where id in (select movie_id from stars where person_id in (select id from people where name = "Bradley Cooper"))
intersect select title from movies where id in(select movie_id from stars where person_id in(select id from people where name = "Jennifer Lawrence"))
 -- Mohammadreza_mokhtari_kia
