--ZAD1
CREATE OR REPLACE FUNCTION cast_int(x varchar)
RETURNS int  AS $$
BEGIN
        RETURN x::int;
        EXCEPTION WHEN others THEN RETURN NULL;
END
$$ LANGUAGE plpgsql;
----
--ZAD2
SELECT CONCAT('{',array_to_string(translate(string_to_array(wynik::text, ',')::text, '()', '')::text[], ','), '}')
AS wynik FROM tab AS wynik
----
--ZAD4
CREATE OR REPLACE FUNCTION remove_duplicates(tab text)
RETURNS void AS $$
BEGIN

DELETE FROM tab t1
        WHERE t1.ctid NOT IN
                (
                SELECT MAX(ctid) FROM tab
                         GROUP BY a,b
                );

END;
$$ LANGUAGE plpgsql;
----
--ZAD5
CREATE OR REPLACE FUNCTION array_intersect(anyarray, anyarray)
RETURNS anyarray AS $$

        SELECT ARRAY
                (       SELECT UNNEST($1)
                        INTERSECT
                        SELECT UNNEST($2)
                )
$$ LANGUAGE SQL
----
--ZAD6
CREATE OR REPLACE FUNCTION array_sort(anyarray)
RETURNS anyarray AS $$
      SELECT ARRAY(SELECT unnest($1) ORDER BY 1);
$$ LANGUAGE SQL;
----
--ZAD7
SELECT *, (ctid::text::point)[1]::bigint as "numer" FROM tab
WHERE   (
      (ctid::text::point)[1]::bigint
      ) % 3 = 1
----
--ZAD8
SELECT * FROM zwierzeta
ORDER BY 
        CASE rodzaj
        WHEN 'pies' THEN 1
        WHEN 'kot' THEN 2
        END
, nazwa
----
--ZAD9
ALTER TABLE tab DROP CONSTRAINT tab_b_check;

ALTER TABLE tab ALTER COLUMN b
SET DATA TYPE boolean
USING CASE
        WHEN b = 'tak' THEN true
        ELSE false
END;
----
--ZAD10
SELECT table_name FROM information_schema.tables
        WHERE table_schema = 'public' AND table_type = 'BASE TABLE'
----
--ZAD11
CREATE OR REPLACE FUNCTION remove_all()
RETURNS void AS $$
DECLARE
        tbl name;
BEGIN
        FOR tbl IN
                (
                SELECT table_name FROM information_schema.tables
                WHERE table_schema = 'public' AND table_type = 'BASE TABLE'
                )
        LOOP
                EXECUTE 'DROP TABLE IF EXISTS ' ||tbl|| ' CASCADE';
        END LOOP;

END;
$$ LANGUAGE plpgsql;

SELECT remove_all();
----
--ZAD12
SELECT table_name AS "nazwa", pg_total_relation_size(table_name::regclass) AS "rozmiar"
FROM information_schema.tables
        WHERE table_schema = 'public' AND table_type = 'BASE TABLE'
----
