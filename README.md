# Reversi
Gra Reversi, znana też pod nazwą Othello

Gra jest rozgrywana na 64-polowej planszy podzielonej na wiersze od 1 do 8 i kolumny od a do h. Pola nazywam, wskazując najpierw kolumnę a następnie wiersz.

W Reversi gra się dwustronnymi czarno-białymi pionami. Na każdym polu może być co najwyżej jeden pion. Jeśli pion w danej chwili jest odwrócony do góry stroną czarną, nazywamy go pionem czarnym, jeśli białą - jest pionem białym.

Partię gry w Reversi zaczyna się na planszy z pionami białymi na polach d4 i e5 oraz czarnymi na polach d5 i e4. Pozostałe pola są puste.

W grze bierze udział dwóch graczy, nazywanych Czarnym i Białym, od koloru pionów, którym się posługują. Grę rozpoczyna gracz Czarny.

Gracze wykonują, na przemian, po jednym ruchu polegającym na umieszczeniu na planszy piona swojego koloru. Jeśli na wszystkich polach w linii, czyli w wierszu, kolumnie lub przekątnej, między położonym właśnie pionem a innym pionem tego samego koloru, są piony w kolorze przeciwnym, zmieniają one kolor, czyli są odwracane. Położenie na planszy jednego piona może spowodować jednoczesną zmianę kilku linii pionów.

Ruch jest legalny tylko, gdy powoduje zmianę koloru co najmniej jednego piona na planszy. Jeśli w danej chwili gracz nie może wykonać legalnego ruchu, nie kładzie na planszy piona.

Choć nie jest to zgodne z regułami gry w Reversi, w moim programie pozwalam graczowi zrezygnować z ruchu nawet, gdy może wykonać ruch legalny.

Gra kończy się, gdy żaden z graczy nie może wykonać legalnego ruchu. Zwycięzcą zostaje gracz, który ma na planszy więcej pionów swojego koloru.

Program gra w Reversi jako gracz Biały.

Program pisze diagram początkowego stanu planszy. Następnie, w pętli, czyta kolejne polecenia gracza Czarnego, odpowiada na nie jako gracz Biały i pisze nowy diagram planszy.

Spośród ruchów gracza Białego program wybiera ten, po którym liczba białych pionów na planszy będzie największa. Gdyby wiele ruchów to maksimum osiągało, wybiera ruch na pole o niższym numerze wiersza a w ramach tego wiersza, pole we wcześniejszej kolumnie.

Postać danych
W kolejnych wierszach wejścia są polecenia użytkownika grającego jako gracz Czarny. Polecenie może być poprawne lub niepoprawne. Poprawne polecenie może być poleceniem rezygnacji z ruchu lub jego wykonania.

Wiersz o treści = to poprawne polecenie rezygnacji z ruchu. Wiersz z nazwą pola jest poprawnym poleceniem wykonania ruchu jeżeli, zgodnie z regułami gry w Reversi, ruch na to pole jest legalny.

Postać wyniku
Na wyjściu programu jest ciąg diagramów planszy, przedzielonych komunikatami z odpowiedzią na polecenia użytkownika.

Diagram opisuje każde pole za pomocą znaku

* - gdy pole jest puste,

* C gdy na polu jest pion czarny,

* B gdy na polu jest pion biały.

Znaki te są pogrupowane w wiersze i uporządkowane w kolejności rosnącego numeru wiersza a w wierszu, według rosnącej kolumny. W lewym górnym rogu diagramu jest więc pole a1. Na końcu każdego wiersza i pod każdą kolumną jest ich oznaczenie. Np. diagram stanu początkowego planszy ma postać

--------1

--------2

--------3

---BC---4

---CB---5

--------6

--------7

--------8

abcdefgh
Odpowiedź programu na polecenie użytkownika mieści się w jednym wierszu. Kończy się on, poprzedzoną spacją, oceną planszy. Ocena jest równa różnicy między liczbą czarnych i białych pionów.

Jeśli polecenie jest błędne, na początku odpowiedzi programu, przed oceną planszy, jest znak zapytania. W przeciwnym przypadku zapisany jest tam ruch gracza Czarnego i, po spacji, ruch gracza Białego. Rezygnację z ruchu będziemy zapisywać jako = a wykonanie ruchu, wskazując pole, na które położono pion.

Odpowiedź na polecenie jest więc słowem języka opisanego poniższą gramatyką bezkontekstową z symbolem początkowym S. Symbolami końcowymi tej gramatyki są znaki ujęte w apostrofy oraz n, które reprezentuje liczbę całkowitą zapisaną dziesiętnie.

S → R ' ' n

R → '?' | P ' ' P

P → '=' | K W

K → 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h'

W → '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8'

