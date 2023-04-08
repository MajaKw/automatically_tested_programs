--ZAD1
CREATE TABLE zwierzeta(gatunek varchar(100) NOT NULL,
        jajorodny char(1) CHECK(jajorodny in ('T', 'N')) NOT NULL,
      liczba_konczyn numeric(2) NOT NULL,
         data_odkrycia DATE NOT NULL);
----
--ZAD2
CREATE TABLE klienci (pesel char(11) PRIMARY KEY, adres varchar(100), wiek numeric(2)
        NOT NULL, wspolpraca_od DATE NOT NULL)
----
--ZAD3
CREATE TABLE uczelnie(id_uczelni numeric(4) PRIMARY KEY,
        nazwa varchar(100) UNIQUE,
      adres varchar(100),
        budzet numeric(10,2) NOT NULL,
      zalozona DATE NOT NULL)
----
--ZAD4
CREATE TABLE ksiazki(id_ksiazki numeric(10) PRIMARY KEY,
      tytul varchar(100) NOT NULL,
      autorzy varchar(100),
      cena numeric(6,2),
      data_wydania DATE)
----
--ZAD5
CREATE TABLE pokoje(
      numer_pokoju numeric(3),
        id_zesp numeric(2)  REFERENCES zespoly,
        liczba_okien numeric(1),
      PRIMARY KEY(numer_pokoju)
        )
----
--ZAD10
CREATE TABLE zwierzeta(gatunek varchar(100) NOT NULL,
        jajorodny char(1) CHECK(jajorodny in ('T', 'N')) NOT NULL,
        liczba_konczyn numeric(2) NOT NULL,
         data_odkrycia DATE NOT NULL);
ALTER TABLE zwierzeta RENAME TO gatunki;
DROP TABLE  gatunki
----
--ZAD11
CREATE TABLE projekty(
      id_projektu numeric(4) PRIMARY KEY,
      opis_projektu char(20) NOT NULL UNIQUE,
      data_rozpoczecia  DATE DEFAULT CURRENT_DATE,
      data_zakonczenia DATE CHECK(data_zakonczenia > data_rozpoczecia),
      fundusz numeric(7,2)
)
----
--ZAD17
ALTER TABLE pracownicy DROP COLUMN imie
----
--ZAD7
CREATE TABLE szef_podwladny AS
       SELECT p2.nazwisko AS szef, p1.nazwisko AS podwladny
FROM pracownicy p1
        INNER JOIN pracownicy p2 ON (p1.id_szefa = p2.id_prac)

----
--ZAD6
CREATE TABLE plyty_cd(
kompozytor char(100) NOT NULL,
tytul_albumu char(100) NOT NULL,
data_nagrania DATE,
data_wydania DATE,
czas_trwania INTERVAL CHECK(czas_trwania < '82 minutes'),
CONSTRAINT un_ko_ty UNIQUE(kompozytor, tytul_albumu),
CHECK (data_nagrania < data_wydania)
)
----
--ZAD12
CREATE TABLE projekty(
        id_projektu numeric(4) PRIMARY KEY,
        opis_projektu char(20) NOT NULL UNIQUE,
        data_rozpoczecia  DATE DEFAULT CURRENT_DATE,
        data_zakonczenia DATE CHECK(data_zakonczenia > data_rozpoczecia),
        fundusz numeric(7,2)
);
CREATE TABLE przydzialy(
	id_projektu numeric(4) REFERENCES projekty,
	id_prac numeric(4) REFERENCES pracownicy,
	od DATE DEFAULT CURRENT_DATE,
	"do" DATE CHECK("do" > od),
	stawka numeric(7,2),
	rola char(20) CHECK(rola IN ('KIERUJACY', 'ANALITYK', 'PROGRAMISTA')),
	PRIMARY KEY(id_projektu, id_prac)

);
----
--ZAD8
CREATE TABLE plyty_cd(
kompozytor char(100) NOT NULL,
tytul_albumu char(100) NOT NULL,
data_nagrania DATE,
data_wydania DATE,
czas_trwania INTERVAL CHECK(czas_trwania < '82 minutes'),
CONSTRAINT un_ko_ty UNIQUE(kompozytor, tytul_albumu),
CHECK (data_nagrania < data_wydania)
);
ALTER TABLE plyty_cd DROP CONSTRAINT un_ko_ty;
ALTER TABLE plyty_cd ADD CONSTRAINT un_ko_ty PRIMARY KEY(kompozytor, tytul_albumu)
----
--ZAD9
CREATE TABLE plyty_cd(
kompozytor char(100) NOT NULL,
tytul_albumu char(100) NOT NULL,
data_nagrania DATE,
data_wydania DATE,
czas_trwania INTERVAL CHECK(czas_trwania < '82 minutes'),
CONSTRAINT un_ko_ty UNIQUE(kompozytor, tytul_albumu),
CHECK (data_nagrania < data_wydania)
);
ALTER TABLE plyty_cd DROP CONSTRAINT un_ko_ty;
ALTER TABLE plyty_cd ADD CONSTRAINT un_ko_ty PRIMARY KEY(kompozytor, tytul_albumu);
ALTER TABLE plyty_cd DROP CONSTRAINT un_ko_ty;
INSERT INTO plyty_cd (kompozytor, tytul_albumu) VALUES('a', 'b');
INSERT INTO plyty_cd (kompozytor, tytul_albumu) VALUES('a', 'b');
ALTER TABLE plyty_cd ADD CONSTRAINT un_ko_ty PRIMARY KEY(kompozytor, tytul_albumu);
----
--ZAD13
CREATE TABLE projekty(
        id_projektu numeric(4) PRIMARY KEY,
        opis_projektu char(20) NOT NULL UNIQUE,
        data_rozpoczecia  DATE DEFAULT CURRENT_DATE,
        data_zakonczenia DATE CHECK(data_zakonczenia > data_rozpoczecia),
        fundusz numeric(7,2)
);
CREATE TABLE przydzialy(
        id_projektu numeric(4) REFERENCES projekty,
        id_prac numeric(4) REFERENCES pracownicy,
        od DATE DEFAULT CURRENT_DATE,
        "do" DATE CHECK("do" > od),
        stawka numeric(7,2),
        rola char(20) CHECK(rola IN ('KIERUJACY', 'ANALITYK', 'PROGRAMISTA')),
        PRIMARY KEY(id_projektu, id_prac)

);
ALTER TABLE przydzialy ADD COLUMN godziny numeric;
----
--ZAD15
CREATE TABLE projekty(
        id_projektu numeric(4) PRIMARY KEY,
        opis_projektu char(20) NOT NULL UNIQUE,
        data_rozpoczecia  DATE DEFAULT CURRENT_DATE,
        data_zakonczenia DATE CHECK(data_zakonczenia > data_rozpoczecia),
        fundusz numeric(7,2)
);
ALTER TABLE projekty ALTER COLUMN opis_projektu TYPE char(30)
----
--ZAD18
CREATE TABLE pracownicy_zespoly AS (
    SELECT
        p.nazwisko AS "nazwisko", p.etat AS "etat",
	p.placa_pod * 12 AS "roczna_placa", z.nazwa AS "zespol",
	z.adres AS "adres_pracy"
FROM pracownicy P INNER JOIN zespoly z USING (id_zesp)
);
----
