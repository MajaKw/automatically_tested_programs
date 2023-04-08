--ZAD1
SELECT * FROM ZESPOLY ORDER BY 1,2,3
----
--ZAD2
SELECT * FROM PRACOWNICY ORDER BY 1,2,3,4,5,6,7,8,9
----
--ZAD3
SELECT nazwisko,etat,
placa_pod*12 AS placa_pod
FROM pracownicy
ORDER BY 1,2,3
----
--ZAD4
SELECT nazwisko, SUM(placa_pod + coalesce(placa_dod, 0)) AS placa_pod
FROM PRACOWNICY
GROUP BY id_prac
ORDER BY 1,2
----
--ZAD5
SELECT * FROM ZESPOLY
ORDER BY nazwa
----
--ZAD6
SELECT DISTINCT etat
FROM PRACOWNICY
ORDER BY 1
----
--ZAD7
SELECT * FROM PRACOWNICY
        WHERE etat = 'ASYSTENT'
ORDER BY 1,2,3,4,5,6,7,8,9
----
--ZAD8
SELECT * FROM PRACOWNICY
WHERE id_zesp IN (20,30)
ORDER BY 7 DESC
----
--ZAD9
SELECT * FROM PRACOWNICY
WHERE placa_pod BETWEEN 300 AND 1800
ORDER BY 1,2,3,4,5,6,7,8,9
----
--ZAD10
SELECT * FROM PRACOWNICY
WHERE nazwisko LIKE '%ski'
ORDER BY 1,2,3,4,5,6,7,8,9
----
--ZAD11
SELECT * FROM PRACOWNICY
WHERE placa_pod > 2000 AND id_szefa IS NOT NULL
ORDER BY 1,2,3,4,5,6,7,8,9
----
--ZAD12
SELECT nazwisko, zatrudniony, etat FROM PRACOWNICY
WHERE zatrudniony::text LIKE '1992%'
OR zatrudniony::text LIKE '1993%'
ORDER BY 1,2,3
----
--ZAD14
SELECT CONCAT(nazwisko, ' pracuje od ', zatrudniony, ' i zarabia ', placa_pod) AS "PROFESOROWIE"
FROM PRACOWNICY
WHERE etat = 'PROFESOR'
ORDER BY placa_pod DESC
----
--ZAD15
SELECT nazwisko, ROUND(placa_pod*1.15) AS placa_pod
        FROM pracownicy
ORDER BY nazwisko, placa_pod
----
--ZAD16
SELECT CONCAT (nazwisko, repeat('.', 40-char_length(nazwisko) - char_length(etat)) , etat)
AS "nazwisko i etat"
FROM pracownicy
ORDER BY id_prac
----
--ZAD17
SELECT CONCAT(substring(etat, 1,2), id_prac)
      AS "wygenerowany kod" , id_prac, nazwisko, etat
FROM pracownicy
ORDER BY 1,2,3,4
----
--ZAD18
SELECT nazwisko, REGEXP_REPLACE(nazwisko,'[k-mK-M]' , 'X', 'g') AS "zmienione_nazwisko"
FROM PRACOWNICY
ORDER BY nazwisko, zmienione_nazwisko
----
--ZAD19
SELECT nazwisko, TO_CHAR(zatrudniony, 'Month, DD YYYY') as "data_zatrudnienia"
FROM PRACOWNICY
WHERE id_zesp = 20
ORDER BY id_prac
----
--ZAD20
SELECT TO_CHAR(CURRENT_DATE, 'Day') AS "dzis"
----
--ZAD21
SELECT id_prac,
      CASE
      WHEN placa_pod > 1850 THEN 'wiecej'
      WHEN placa_pod < 1850 THEN 'mniej'
      ELSE 'rowna'
END AS placa_pod
FROM pracownicy
ORDER BY 1,2
----
--ZAD22
SELECT imie, nazwisko, placa_dod
FROM pracownicy
ORDER BY placa_dod DESC NULLS LAST, id_prac
----
--ZAD13
SELECT * FROM pracownicy
      WHERE COALESCE(placa_dod, 0) > 500
ORDER BY etat, nazwisko
----
