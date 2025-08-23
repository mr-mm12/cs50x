select count(title) from movies where id in(select movie_id from ratings where rating = 10.0)
 -- Mohammadreza_mokhtari_kia
