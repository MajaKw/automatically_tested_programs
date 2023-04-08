--ZAD2
SELECT z.data_zlozenia, k.nazwa
FROM zamowienia z
INNER JOIN klienci k
ON z.id_klienta = k.id_klienta
WHERE k.nip IS NOT NULL
ORDER BY 1,2
----
--ZAD5
SELECT p.nazwa, p2.nazwa
FROM produkty p CROSS JOIN produkty p2
WHERE p.cena_netto + 0.01*p.vat*p.cena_netto > p2.cena_netto + 0.01*p2.vat*p2.cena_netto
ORDER BY 1,2
----
--ZAD6
SELECT k.nazwa, k.email
FROM klienci k
      INNER JOIN zamowienia z
ON k.id_klienta = z.id_klienta
WHERE  TO_CHAR(z.data_zlozenia, 'MM') = '03'
GROUP BY k.nazwa, k.email
ORDER BY 1,2
----
--ZAD7a
SELECT k.nazwa, k2.nazwa
FROM klienci k, rabaty_klientow rk, klienci k2
      WHERE k.id_klienta = rk.id_klienta
      AND k2.id_klienta = rk.id_polecajacego
ORDER BY 1,2
----
--ZAD1
SELECT p.nazwa, k.nazwa
FROM produkty p
CROSS JOIN klienci k
WHERE p.kategoria LIKE 'Artykuły%' AND k.email IS NOT NULL
ORDER BY 1, 2
----
--ZAD8
SELECT k.*
FROM klienci k
      LEFT JOIN rabaty_klientow rk
      ON k.id_klienta = rk.id_klienta
WHERE rk.id_klienta IS NULL
ORDER BY 1,2,3,4,5
----
--ZAD9
SELECT p.nazwa
FROM produkty p, rabaty_produktow rp
      WHERE p.kod_produktu = rp.produkt AND
      rp.min_ilosc = 1
ORDER BY 1
----
--ZAD4
SELECT k.nazwa AS "nazwa klienta",
      CASE WHEN COUNT(DISTINCT z.adres_dostawy) != 1 THEN 'TAK'
      ELSE 'NIE' END AS "rozne adresy"
FROM klienci k
INNER JOIN zamowienia z
ON k.id_klienta = z.id_klienta
GROUP BY k.id_klienta
ORDER BY 1,2
----
--ZAD10
SELECT k.*, z.id_zamowienia, SUM(ilosc * cena_netto) AS "cena_netto"
FROM klienci k
      INNER JOIN zamowienia z ON z.id_klienta = k.id_klienta
      INNER JOIN produkty_zamowienia pz ON z.id_zamowienia = pz.id_zamowienia
      INNER JOIN produkty p ON pz.produkt = p.kod_produktu
WHERE k.nazwa = 'Urząd Skarbowy w Radomiu'
GROUP BY z.id_zamowienia, k.id_klienta
ORDER BY "cena_netto" DESC, id_zamowienia ASC
----
--ZAD7b
SELECT k1.nazwa, k2.nazwa
FROM klienci k1
        LEFT OUTER JOIN  rabaty_klientow rb ON k1.id_klienta = rb.id_klienta
        LEFT OUTER JOIN  klienci k2 ON k2.id_klienta = rb.id_polecajacego
WHERE rb.id_rabatu IS NOT NULL
ORDER BY 1,2
----
--ZAD11
SELECT  z.id_zamowienia
FROM zamowienia z
      INNER JOIN klienci k ON z.id_klienta = k.id_klienta
      INNER JOIN rabaty_klientow rb ON k.id_klienta = rb.id_klienta
GROUP BY z.id_zamowienia
ORDER BY 1
----
--ZAD13
SELECT k.nazwa AS "klient", SUM(pz.ilosc) AS "ilosc produktow"
FROM klienci k
      INNER JOIN zamowienia z USING(id_klienta)
      INNER JOIN produkty_zamowienia pz USING(id_zamowienia)
      INNER JOIN produkty p ON pz.produkt = p.kod_produktu
WHERE p.waga > 1000 AND ilosc != 0
GROUP BY id_klienta
ORDER BY 1,2
----
--ZAD14
SELECT k.nazwa AS "klient", COUNT(z.id_zamowienia) AS "liczba zamowien"
FROM klienci k
      LEFT OUTER JOIN zamowienia z USING(id_klienta)
GROUP BY "klient", id_klienta
ORDER BY 2 DESC, 1 ASC
----
--ZAD16
SELECT
      CASE WHEN COUNT(rb1.id_polecajacego = rb2.id_klienta) != 1 THEN 'TAK'
      ELSE 'NIE' END
FROM rabaty_klientow rb1
      INNER JOIN rabaty_klientow rb2 ON rb1.id_klienta = rb2.id_polecajacego
----
--ZAD17
SELECT id_zamowienia, MAX(ilosc)
FROM produkty_zamowienia
GROUP BY id_zamowienia
ORDER BY 2 DESC, 1 ASC
----
--ZAD15
SELECT r.id_rabatu, znizka,
CASE WHEN rk.id_rabatu = r.id_rabatu THEN 'RABAT KLIENCKI'
ELSE 'RABAT PRODUKTU' END  AS "typ rabatu"

      FROM rabaty_klientow rk
      RIGHT JOIN rabaty r USING (id_rabatu)
      LEFT JOIN rabaty_produktow rp USING (id_rabatu)
ORDER BY 1
----
--ZAD3
SELECT DISTINCT nazwa FROM produkty
      JOIN produkty_zamowienia ON(kod_produktu = produkt)
      JOIN zamowienia USING (id_zamowienia)
WHERE adres_dostawy LIKE 'ul. Kubusia Puchatka%'
ORDER BY 1
----
--ZAD12
SELECT nazwa AS "klient",
      CASE WHEN COUNT(ilosc) != 0 THEN SUM(ilosc)
      ELSE '0' END AS "ilosc produktow"
FROM klienci
      LEFT JOIN zamowienia USING (id_klienta)
      LEFT JOIN  produkty_zamowienia USING (id_zamowienia)
GROUP BY id_klienta
ORDER BY 1,2
----
