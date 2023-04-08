--ZAD1
SELECT nazwa FROM produkty
WHERE id_kategoria = (SELECT id_kategoria FROM produkty WHERE nazwa LIKE 'Piórnik duży')
----
--ZAD2
SELECT nazwa FROM produkty WHERE id_kategoria IN
(SELECT id_kategoria FROM kategorie WHERE nadkategoria IS NOT NULL)
----
--ZAD3c
SELECT k.nazwa FROM kategorie k
INNER JOIN produkty p USING (id_kategoria)
GROUP BY id_kategoria HAVING COUNT(kod_produktu) > 2
----
--ZAD3a
SELECT nazwa FROM kategorie WHERE id_kategoria IN
(SELECT id_kategoria FROM produkty GROUP BY id_kategoria
      HAVING COUNT(kod_produktu) > 2)
----
--ZAD5
SELECT * FROM kategorie k WHERE k.vat < ANY
      (SELECT vat FROM kategorie k2
       WHERE k2.nadkategoria = k.id_kategoria)
----
--ZAD6
SELECT z.id_zamowienia FROM zamowienia z
JOIN produkty_zamowienia pz USING(id_zamowienia)
GROUP BY id_zamowienia HAVING SUM(ilosc) >=
ALL(SELECT SUM(ilosc) FROM produkty_zamowienia
GROUP BY id_zamowienia)
----
--ZAD7
SELECT p.nazwa, COUNT(h.data_wprowadzenia) FROM produkty p JOIN historia_cen h USING(kod_produktu)
      WHERE EXTRACT(MONTH FROM data_wprowadzenia)=4 AND kod_produktu IN
      (SELECT kod_produktu FROM historia_cen
              WHERE 4=EXTRACT(MONTH FROM data_wprowadzenia)
              GROUP BY kod_produktu HAVING COUNT(data_wprowadzenia) > 1)
      GROUP BY (kod_produktu)
----
--ZAD4
SELECT * FROM rabaty
      WHERE data_do - data_od =  (SELECT MAX(data_do - data_od) FROM rabaty r2)
----
--ZAD3b
SELECT (SELECT k.nazwa FROM kategorie k WHERE k2.id_kategoria = k.id_kategoria)
FROM kategorie k2
    JOIN produkty p ON (p.id_kategoria = k2.id_kategoria)
GROUP BY k2.id_kategoria HAVING COUNT(kod_produktu) > 2;
----
--ZAD9
SELECT p.nazwa, ROUND(h.cena_netto + 0.01*vat*cena_netto, 2)
FROM historia_cen h
      JOIN produkty p USING (kod_produktu)
      JOIN  kategorie k USING (id_kategoria)
WHERE (h.kod_produktu, h.data_wprowadzenia) IN
      (SELECT h.kod_produktu, MAX(h.data_wprowadzenia) FROM historia_cen h
      GROUP BY h.kod_produktu)
----
--ZAD8
CREATE TEMPORARY TABLE result(kategoria varchar(250), nadkategoria varchar(250));
DO $$
DECLARE
      kat int;
      nad int;
      rec record;
      kat_name varchar(250);
      nad_name varchar(250);
BEGIN
FOR rec IN SELECT * FROM kategorie
      LOOP
      kat = rec.id_kategoria;
      nad = rec.nadkategoria;
              WHILE nad IS NOT NULL
              LOOP
                      kat = nad;
                      SELECT nadkategoria FROM kategorie WHERE id_kategoria = kat INTO nad;
              END LOOP;
      IF nad IS NULL THEN nad = kat; END IF;
      SELECT nazwa FROM kategorie WHERE id_kategoria = rec.id_kategoria INTO kat_name;
      SELECT nazwa FROM kategorie WHERE id_kategoria = nad INTO nad_name;
      INSERT INTO result VALUES(kat_name, nad_name);
      END LOOP;
END $$;
SELECT * FROM result;
DROP TABLE result;
----
--ZAD10
SELECT p.nazwa,
        ROUND(  (       (
        SELECT vat FROM kategorie k 
                WHERE p.id_kategoria = k.id_kategoria
        )*0.01 + 1)*
        (
        SELECT cena_netto FROM historia_cen h
                WHERE h.kod_produktu = p.kod_produktu
                AND h.data_wprowadzenia = MAX(h1.data_wprowadzenia)
        ), 2)
        -       CASE WHEN COUNT(id_rabatu) = 0 THEN 0
                ELSE  
        (
                SELECT COALESCE(SUM(znizka), 0) FROM rabaty
                WHERE id_rabatu IN
                        (
                        SELECT id_rabatu FROM rabaty_produkty
                        WHERE id_produktu = p.kod_produktu
                                AND
                                data_od < MAX(h1.data_wprowadzenia)
                                AND 
                                data_do > MAX(h1.data_wprowadzenia)
                        )
                )
                END AS "cena_brutto"
        FROM historia_cen h1
        JOIN produkty p USING(kod_produktu)
                LEFT JOIN rabaty_produkty rp ON(kod_produktu = id_produktu)
                LEFT JOIN rabaty r USING(id_rabatu)
GROUP BY p.kod_produktu
ORDER BY 1;
----
--ZAD11
SELECT id_zamowienia, ROUND( SUM(cena_netto * (1 + 0.01*vat) * ilosc), 2) AS "suma"
        FROM zamowienia
        JOIN produkty_zamowienia USING(id_zamowienia)
        JOIN produkty p ON(produkt = kod_produktu)
        JOIN historia_cen USING(kod_produktu)
        JOIN kategorie USING(id_kategoria)

WHERE data_wprowadzenia >= ALL (SELECT data_wprowadzenia FROM historia_cen
                                WHERE kod_produktu = p.kod_produktu
                                AND data_zlozenia >= data_wprowadzenia)
AND data_zlozenia >= data_wprowadzenia

GROUP BY id_zamowienia
ORDER BY 1
----
