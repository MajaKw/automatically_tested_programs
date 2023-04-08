--ZAD1
SELECT round(MIN(cena_netto + 0.01*vat*cena_netto), 2) as "min",
      round(MAX(cena_netto + 0.01*vat*cena_netto), 2) as "max"
FROM PRODUKTY
ORDER BY 1,2
----
--ZAD2
SELECT id_zamowienia, SUM(ilosc) as "ilosc"
FROM produkty_zamowienia
GROUP BY id_zamowienia
ORDER BY 1,2
----
--ZAD3
SELECT produkt
FROM produkty_zamowienia
GROUP BY produkt HAVING sum(ilosc) >= 50
ORDER BY 1
----
--ZAD4
SELECT kategoria, round(AVG(waga), 2) AS "waga"
FROM produkty
GROUP BY kategoria HAVING COUNT(kategoria) > 1
ORDER BY waga DESC, kategoria ASC
----
--ZAD5
SELECT kategoria, MIN(cena_netto), MAX(cena_netto),  MAX(cena_netto) - MIN(cena_netto) AS "(max-min)"
FROM produkty
GROUP BY kategoria
ORDER BY 1,2,3,4
----
--ZAD6
SELECT kategoria, SUM(CASE WHEN vat != 18 THEN 1 ELSE 0 END) AS "liczba produktow"
FROM produkty
GROUP BY kategoria
ORDER BY 1,2
----
--ZAD7
SELECT COUNT(kod_produktu)
FROM produkty
WHERE waga < 1000
ORDER BY 1
----
--ZAD8
SELECT SUM(cena_netto)
FROM produkty
HAVING MAX(cena_netto)>=300
----
--ZAD9
SELECT
CASE WHEN COUNT(DISTINCT adres_dostawy) = COUNT(adres_dostawy) THEN 'TAK'
ELSE 'NIE' END
FROM zamowienia
----
--ZAD10
SELECT id_klienta
FROM zamowienia
GROUP BY id_klienta HAVING COUNT(id_zamowienia) > 1
ORDER BY 1
----
--ZAD11
SELECT kategoria
FROM produkty
GROUP BY kategoria HAVING SUM(CASE WHEN rabat IS NOT NULL THEN 1 ELSE 0 END) = COUNT(produkty)
ORDER BY 1
----
--ZAD12
SELECT kategoria
FROM produkty
WHERE vat = 8
GROUP BY kategoria HAVING SUM(CASE WHEN rabat IS NOT NULL THEN 1 ELSE 0 END) = COUNT(produkty)
ORDER BY 1
----
--ZAD13
SELECT kategoria, ROUND(COALESCE(VARIANCE(cena_netto), 0), 2) as "wariancja",
      ROUND(COALESCE(STDDEV(cena_netto), 0), 2) AS "odchylenie standardowe"
FROM produkty
GROUP BY kategoria
ORDER BY 1,2,3
----
--ZAD14
SELECT COUNT(kod_produktu)
FROM produkty
WHERE kategoria = 'Artykuły papiernicze'
GROUP BY kategoria
----
--ZAD15a
SELECT CONCAT('{"', string_agg(numer_telefonu, '","'),'"}') AS "lista telefonów"
FROM klienci
WHERE numer_telefonu IS NOT NULL
----
--ZAD15b
SELECT CONCAT('{"', string_agg(numer_telefonu, '","' ORDER BY numer_telefonu), '"}') AS "lista telefonów"
FROM klienci
WHERE numer_telefonu IS NOT NULL
----
--ZAD16
SELECT produkt, COUNT(id_zamowienia)
FROM produkty_zamowienia
GROUP BY produkt
ORDER BY 2 DESC, 1 ASC
----
--ZAD18
SELECT COUNT(*)
FROM klienci
WHERE email LIKE '%@gmail.com'
----
--ZAD19
SELECT TO_CHAR(data_zlozenia, 'Month') as "Miesiac",
       COUNT(id_zamowienia) AS "Liczba zamowien"
FROM zamowienia
GROUP BY TO_CHAR(data_zlozenia, 'Month')
ORDER BY 1,2
----
--ZAD17
SELECT
      CASE WHEN nip IS NULL THEN 'Brak'
      ELSE 'Podany' END AS "NIP", COUNT (id_klienta) AS  "liczba klientow"
FROM klienci
GROUP BY CASE WHEN nip IS NULL THEN 'Brak'
      ELSE 'Podany' END
ORDER BY 1,2
----
