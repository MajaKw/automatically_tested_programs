--ZAD1
CREATE OR REPLACE FUNCTION check_pesel() RETURNS TRIGGER AS
$$
DECLARE
        nr_kontrol int;
BEGIN
      IF char_length(new.pesel)!=11 then raise exception 'Niepoprawny PESEL'; RETURN new; END IF;
        nr_kontrol = 0;
        nr_kontrol = nr_kontrol + 1*(substring(new.pesel, 1, 1)::int);
        nr_kontrol = nr_kontrol + 3*substring(new.pesel, 2, 1)::int;
        nr_kontrol = nr_kontrol + 7*substring(new.pesel, 3, 1)::int;
        nr_kontrol = nr_kontrol + 9*substring(new.pesel, 4, 1)::int;
        nr_kontrol = nr_kontrol + 1*substring(new.pesel, 5, 1)::int;
        nr_kontrol = nr_kontrol + 3*substring(new.pesel, 6, 1)::int;
        nr_kontrol = nr_kontrol + 7*substring(new.pesel, 7, 1)::int;
        nr_kontrol = nr_kontrol + 9*substring(new.pesel, 8, 1)::int;
        nr_kontrol = nr_kontrol + 1*substring(new.pesel, 9, 1)::int;
        nr_kontrol = nr_kontrol + 3*substring(new.pesel, 10, 1)::int;
        nr_kontrol = 10 - (nr_kontrol % 10);

        IF nr_kontrol != 1*substring(new.pesel, 11, 1)::int THEN RAISE EXCEPTION 'Niepoprawny PESEL'; END IF;
        RETURN new;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER pesel_trigger BEFORE INSERT OR UPDATE ON pacjenci
        FOR EACH ROW EXECUTE PROCEDURE check_pesel();
----
--ZAD2
CREATE OR REPLACE FUNCTION fill_date() RETURNS TRIGGER AS
$$
BEGIN
      IF new.data_zakonczenia IS NULL THEN
      new.data_zakonczenia = new.data_rozpoczecia + interval '30 minutes'; END IF;
      RETURN new;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_fill_date BEFORE INSERT ON wizyty
      FOR EACH ROW EXECUTE FUNCTION fill_date();
----
--ZAD3
CREATE OR REPLACE FUNCTION forbid_deletion() RETURNS TRIGGER AS
$$
BEGIN
      IF current_date-old.data_rozpoczecia < interval '5 years' THEN RETURN NULL;
      END IF;
      RETURN old;
END;
$$ LANGUAGE plpgsql;
CREATE TRIGGER trigger_forbid_deletion BEFORE DELETE ON wizyty FOR EACH ROW EXECUTE FUNCTION forbid_deletion();
----
--ZAD4
CREATE OR REPLACE FUNCTION correct_appointment() RETURNS TRIGGER AS
$$
DECLARE
      rec RECORD;
BEGIN
      IF new.data_zakonczenia-new.data_rozpoczecia > interval '1 hour' THEN RETURN NULL;
      END IF;
      FOR rec IN
              SELECT * FROM wizyty WHERE lekarz = new.lekarz
              LOOP
              IF (new.data_rozpoczecia < rec.data_zakonczenia AND new.data_rozpoczecia > rec.data_rozpoczecia)
              OR (new.data_zakonczenia > rec.data_rozpoczecia AND new.data_rozpoczecia < rec.data_zakonczenia)
              OR (new.data_rozpoczecia < rec.data_rozpoczecia AND new.data_zakonczenia > rec.data_zakonczenia)
              THEN RETURN NULL; END IF;
      END LOOP;
      RETURN new;
END;
$$ LANGUAGE plpgsql;
CREATE TRIGGER trigger_correct_appointment BEFORE INSERT ON wizyty
      FOR EACH ROW EXECUTE FUNCTION correct_appointment();
----
--ZAD5
CREATE TABLE lekarze_prowadzacy(
        pesel char(11) NOT NULL REFERENCES pacjenci,
        lekarz int NOT NULL REFERENCES lekarze,
        PRIMARY KEY(pesel, lekarz) );
CREATE OR REPLACE FUNCTION specjalization()
RETURNS TRIGGER AS $$
DECLARE
        doctor int;
BEGIN
doctor = (SELECT id_lekarza FROM specjalizacje LEFT JOIN lekarze_prowadzacy ON id_lekarza = lekarz
        WHERE specjalizacja = 'Medycyna rodzinna'
        GROUP BY id_lekarza
        ORDER BY COUNT(pesel), id_lekarza
        LIMIT 1);
INSERT INTO lekarze_prowadzacy VALUES (new.pesel, doctor);
RETURN new;
END;
$$ LANGUAGE plpgsql;
CREATE TRIGGER trigger_specjalization AFTER INSERT ON pacjenci
FOR EACH ROW EXECUTE FUNCTION specjalization();
----
--ZAD6
CREATE OR REPLACE VIEW pediatrzy AS
SELECT id, imie, nazwisko
FROM lekarze JOIN specjalizacje ON id = id_lekarza
WHERE specjalizacja = 'Pediatra';

CREATE RULE rule_pediatra AS ON INSERT TO pediatrzy
      DO ALSO(
      INSERT INTO lekarze VALUES(new.id, new.imie, new.nazwisko);
      INSERT INTO specjalizacje VALUES(new.id,'Pediatria');
      );
----
--ZAD7
CREATE OR REPLACE VIEW chirurdzy AS
SELECT id, imie, nazwisko
FROM lekarze JOIN specjalizacje ON id = id_lekarza
WHERE specjalizacja = 'Chirurgia';

CREATE RULE rule_chirurdzy AS ON DELETE TO chirurdzy
DO INSTEAD NOTHING;
----
--ZAD8
CREATE RULE forbid_deleting_chirurg
AS ON DELETE TO lekarze
WHERE 'Chirurgia' IN(SELECT specjalizacja FROM specjalizacje
        WHERE old.id = id_lekarza)
DO INSTEAD NOTHING;
----
--ZAD9
CREATE RULE  delete_appointments_info
AS ON DELETE TO pacjenci
DO ALSO(
DELETE FROM wizyty WHERE pacjent = old.pesel)
----
