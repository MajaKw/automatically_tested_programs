--ZAD1
CREATE SEQUENCE seq START 10 MAXVALUE 99 INCREMENT BY 1
----
--ZAD3
CREATE UNIQUE INDEX ON transakcje(z_konta, na_konto, data_zlecenia)
----
--ZAD4
CREATE OR REPLACE VIEW wplaty_wyplaty AS
SELECT k.nr_konta AS "Konto", COUNT(DISTINCT t1.id) AS "Ilosc wyplat",
COUNT (DISTINCT t2.id) AS "Ilosc wplat"
FROM konta k LEFT JOIN transakcje t1 ON(t1.z_konta = k.nr_konta)
LEFT JOIN transakcje t2 ON (t2.na_konto = k.nr_konta)
GROUP BY k.nr_konta
----
--ZAD5
CREATE OR REPLACE VIEW wplaty_wyplaty AS
SELECT k.nr_konta AS "Konto", COUNT(DISTINCT t1.id) AS "Ilosc wyplat",
COUNT (DISTINCT t2.id) AS "Ilosc wplat"
FROM konta k LEFT JOIN transakcje t1 ON(t1.z_konta = k.nr_konta)
LEFT JOIN transakcje t2 ON (t2.na_konto = k.nr_konta)
GROUP BY k.nr_konta;
SELECT * FROM wplaty_wyplaty;
INSERT INTO transakcje VALUES(200, CURRENT_DATE, NULL, 1004, 500.00);
SELECT * FROM wplaty_wyplaty;
DROP VIEW wplaty_wyplaty
----
--ZAD7
CREATE FUNCTION oblicz_koszt(arg numeric(11,2)) RETURNS numeric(11,2) AS $$
BEGIN
RETURN ROUND(0.02*arg,2);
END;
$$ LANGUAGE plpgsql;
SELECT oblicz_koszt(kwota) FROM transakcje;
----
--ZAD8
CREATE FUNCTION bilans_kont() RETURNS TABLE
( konto numeric(11), suma_wplat numeric(11,2), suma_wyplat numeric(11,2) )
AS $$
BEGIN
RETURN QUERY
SELECT nr_konta,
(SELECT COALESCE(SUM(kwota),0) FROM transakcje
      WHERE nr_konta = na_konto),
(SELECT COALESCE(SUM(kwota), 0) FROM transakcje
      WHERE nr_konta = z_konta)
FROM konta;
END
$$ LANGUAGE plpgsql;
--ZAD6
CREATE FUNCTION oblicz_koszt(arg numeric(11,2)) RETURNS numeric(11,2) AS $$
BEGIN
RETURN ROUND(0.02*arg,2);
END;
$$ LANGUAGE plpgsql;
----
--ZAD9
CREATE FUNCTION bilans_kont() RETURNS TABLE
( konto numeric(11), suma_wplat numeric(11,2), suma_wyplat numeric(11,2) )
AS $$
BEGIN
RETURN QUERY
SELECT nr_konta,
(SELECT COALESCE(SUM(kwota),0) FROM transakcje
      WHERE nr_konta = na_konto),
(SELECT COALESCE(SUM(kwota), 0) FROM transakcje
      WHERE nr_konta = z_konta)
FROM konta;
END
$$ LANGUAGE plpgsql;
SELECT konto, suma_wplat - suma_wyplat AS "bilans" FROM bilans_kont();
----
--ZAD10a
CREATE FUNCTION silnia(n numeric) RETURNS numeric
AS $$
DECLARE
      silnia numeric:=1;
      i numeric:=1;
BEGIN
      LOOP
              IF i>n THEN EXIT;
              END IF;
              silnia:=silnia*i;
              i:=i+1;
      END LOOP;
RETURN silnia;
END;
$$ LANGUAGE plpgsql;
----
--ZAD10b
CREATE FUNCTION silnia(n numeric) RETURNS numeric
AS $$
BEGIN
      IF n<=1 THEN RETURN 1; END IF;
      RETURN n*silnia(n-1);
END;
$$ LANGUAGE plpgsql;
----
--ZAD11
CREATE FUNCTION bilans_kont() RETURNS TABLE
( konto numeric(11), suma_wplat numeric(11,2), suma_wyplat numeric(11,2) )
AS $$
BEGIN
RETURN QUERY
SELECT nr_konta,
(SELECT COALESCE(SUM(kwota),0) FROM transakcje
      WHERE nr_konta = na_konto),
(SELECT COALESCE(SUM(kwota), 0) FROM transakcje
      WHERE nr_konta = z_konta)
FROM konta;
END
$$ LANGUAGE plpgsql;
CREATE SEQUENCE seq MAXVALUE 5000
START 1000 INCREMENT BY 10;
CREATE FUNCTION bonus_swiateczny(p numeric(11,2) DEFAULT 0.01)
RETURNS void AS $$
DECLARE
      value RECORD;
BEGIN
      FOR value IN SELECT * FROM bilans_kont()
      LOOP
      INSERT INTO transakcje VALUES((SELECT nextval('seq')),
      CURRENT_DATE, NULL, value.konto, ROUND(p*value.suma_wyplat, 2));
      END LOOP;
END;
$$ LANGUAGE plpgsql;
----
--ZAD12
CREATE OR REPLACE FUNCTION stan_konta(konto numeric(11), czas timestamp)
RETURNS numeric AS $$
DECLARE
      bilans numeric :=0;
      arr numeric;
BEGIN
      bilans = 0;
      FOR arr IN SELECT
      CASE WHEN z_konta = konto THEN (-1)*kwota
      WHEN na_konto = konto THEN kwota
      ELSE 0 END
      FROM transakcje
      WHERE czas >= data_zlecenia ORDER BY data_zlecenia ASC

      LOOP
      bilans = bilans + arr;
      IF bilans < 0 THEN RAISE EXCEPTION 'Wykryto ujemny bilans konta'; END IF;
      END LOOP;
RETURN bilans;
END;
$$ LANGUAGE plpgsql;
----
--ZAD13
CREATE OR REPLACE FUNCTION stan_konta(konto numeric(11), czas timestamp)
RETURNS numeric AS $$
DECLARE
      bilans numeric :=0;
      arr numeric;
BEGIN
      bilans = 0;
      FOR arr IN SELECT
      CASE WHEN z_konta = konto THEN (-1)*kwota
      WHEN na_konto = konto THEN kwota
      ELSE 0 END
      FROM transakcje
      WHERE czas >= data_zlecenia ORDER BY data_zlecenia ASC

      LOOP
      bilans = bilans + arr;
      IF bilans < 0 THEN RAISE EXCEPTION 'Wykryto ujemny bilans konta'; END IF;
      END LOOP;
RETURN bilans;
END;
$$ LANGUAGE plpgsql;


DROP FUNCTION IF EXISTS historia_konta;
CREATE OR REPLACE FUNCTION historia_konta(account numeric(11))
RETURNS TABLE (data timestamp, stan numeric(11,2)) AS $$
BEGIN
RETURN QUERY
SELECT t1.data_zlecenia,
        (
        SELECT stan_konta(account, t1.data_zlecenia)
        )
FROM transakcje t1
        WHERE z_konta = account OR na_konto = account
ORDER BY "data";

END
$$ LANGUAGE plpgsql
----
--ZAD14
CREATE OR REPLACE FUNCTION stan_konta(konto numeric(11), czas timestamp)
RETURNS numeric AS $$
DECLARE
      bilans numeric :=0;
      arr numeric;
BEGIN
      bilans = 0;
      FOR arr IN SELECT
      CASE WHEN z_konta = konto THEN (-1)*kwota
      WHEN na_konto = konto THEN kwota
      ELSE 0 END
      FROM transakcje
      WHERE czas >= data_zlecenia ORDER BY data_zlecenia ASC

      LOOP
      bilans = bilans + arr;
      IF bilans < 0 THEN RETURN -1; END IF;
      END LOOP;
RETURN bilans;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION moment_rozspojniajacy()
RETURNS timestamp AS $$
DECLARE
      k numeric;
      d timestamp;
BEGIN
      FOR d IN (
              SELECT data_zlecenia FROM transakcje
                      WHERE z_konta IS NOT NULL
              ORDER BY 1)
      LOOP
              SELECT z_konta FROM transakcje
                      WHERE data_zlecenia = d INTO k;

              IF (SELECT stan_konta(k, d)) < 0 THEN RETURN d; END IF;
      END LOOP;

      RETURN NULL;
END
$$ LANGUAGE plpgsql;
----
