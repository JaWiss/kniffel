import pandas as pd

# ==========================================
# Einstellungen
# ==========================================

INPUT_FILE = "first_run_data.csv"
OUTPUT_FILE = "averages.csv"

# Spalten, die zu jedem Spieler gehören
PLAYER_COLUMNS = [
    "Playername",
    "Playerstatus",
    "Einser",
    "Zweier",
    "Dreier",
    "Vierer",
    "Fünfer",
    "Sechser",
    "Oben",
    "Dreierpasch",
    "Viererpasch",
    "Full-House",
    "kleine-Straße",
    "große-Straße",
    "Kniffel",
    "Chance",
    "Unten",
    "Total",
]


# ==========================================
# CSV einlesen
# ==========================================

df = pd.read_csv(INPUT_FILE)


# ==========================================
# Spielerblöcke erkennen
# ==========================================

# Die ersten beiden Spalten sind date/time.
# Danach kommen jeweils 18 Spalten pro Spieler.

player_data = []

start_column = 2  # nach date und time

while start_column < len(df.columns):

    # Spalten des aktuellen Spielerblocks
    block = df.iloc[:, start_column:start_column + len(PLAYER_COLUMNS)].copy()

    if len(block.columns) < len(PLAYER_COLUMNS):
        break

    block.columns = PLAYER_COLUMNS

    player_data.append(block)

    start_column += len(PLAYER_COLUMNS)


# ==========================================
# Daten in langes Format umwandeln
# ==========================================

all_players = pd.concat(player_data, ignore_index=True)


# ==========================================
# Numerische Spalten definieren
# ==========================================

score_columns = [
    "Einser",
    "Zweier",
    "Dreier",
    "Vierer",
    "Fünfer",
    "Sechser",
    "Oben",
    "Dreierpasch",
    "Viererpasch",
    "Full-House",
    "kleine-Straße",
    "große-Straße",
    "Kniffel",
    "Chance",
    "Unten",
    "Total",
]


# Sicherstellen, dass die Werte numerisch sind
for column in score_columns:
    all_players[column] = pd.to_numeric(
        all_players[column],
        errors="coerce"
    )

    # -1 wird als 0 gewertet
    all_players.loc[all_players[column] == -1, column] = 0

# ==========================================
# Durchschnitt pro Spieler und Kategorie
# ==========================================

averages = (
    all_players
    .groupby("Playername")[score_columns]
    .mean()
    .round(2)
)


# ==========================================
# Ausgabe
# ==========================================

print("\nDurchschnittliche Punktzahlen:")
print(averages)

# Als CSV speichern
averages.to_csv(OUTPUT_FILE, encoding="utf-8-sig")

print(f"\nErgebnis wurde gespeichert als: {OUTPUT_FILE}")