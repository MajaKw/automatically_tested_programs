--ZADc

DROP TABLE IF EXISTS publikacje;
DROP TABLE IF EXISTS typy;

CREATE TABLE typy(
              typ int PRIMARY KEY,
              opis varchar(100) NOT NULL
              );
INSERT INTO typy VALUES(1, 'czasopismo');
INSERT INTO typy VALUES(2, 'konferencja');

CREATE TABLE publikacje(
              nazwa varchar(100) NOT NULL,
              typ int NOT NULL REFERENCES typy,
              zrodlo int NOT NULL,
              rok numeric(4) NOT NULL,
              numer int NOT NULL,
              od int NOT NULL,
              "do" int NOT NULL,
              id serial PRIMARY KEY
              );

CREATE OR REPLACE FUNCTION control() RETURNS TRIGGER AS $$
BEGIN
        IF new.zrodlo NOT IN (SELECT id FROM czsopisma)
        AND new.zrodlo NOT IN(SELECT id FROM konferencje)
        THEN RETURN old;
        END IF;

        IF new.zrodlo = old.zrodlo AND new.rok = old.rok AND new.numer = old.numer
        AND ((new.od < old.do AND new.od > old.od)
              OR (new.do > old.od AND new.od < old.do)
              OR (new.od < old.od AND new.do > old.do)
        ) THEN RETURN old;
        ELSE RETURN new; END IF;

END
$$ LANGUAGE plpgsql;

CREATE TRIGGER pub_check BEFORE INSERT OR UPDATE ON publikacje
FOR EACH ROW EXECUTE PROCEDURE control();

--ZADb
DROP TABLE IF EXISTS czasopisma;
DROP TABLE IF EXISTS konferencje;

CREATE TABLE czasopisma(
              krotka_nazwa varchar(100) UNIQUE NOT NULL,
              pelna_nazwa varchar(100) NOT NULL,
              id serial PRIMARY KEY
              );

CREATE TABLE konferencje(
              nazwa varchar(100) NOT NULL,
              kraj varchar(100) NOT NULL,
              miejsce varchar(100) NOT NULL,
              rok numeric(4) NOT NULL,
              id serial PRIMARY KEY,
              UNIQUE(nazwa, rok)
              );
----
--ZAD2
CREATE OR REPLACE FUNCTION srednia(id int) RETURNS numeric AS
$$
DECLARE
      sum int;
      arr char[];
      i char;
      n int;
BEGIN
      sum = 0;
      n = 0;
      FOR arr IN SELECT notatka FROM notatki
              WHERE id_studenta = id
      LOOP
      FOREACH  i IN ARRAY arr
              LOOP
              IF i != '-' AND i != '+'
              THEN sum = sum + i::int; n = n + 1; END IF;
              END LOOP;
      END LOOP;
              IF n = 0 THEN RETURN NULL; END IF;
      RETURN ROUND(cast(sum as decimal)/n, 3);
END;
$$ LANGUAGE plpgsql;
----
