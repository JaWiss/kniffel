import pandas as pd

# ==========================================
# Einstellungen
# ==========================================

INPUT_FILE = "second_run_data.csv"
OUTPUT_FILE = "averages_4.csv"

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

# Punktespalten
SCORE_COLUMNS = [
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
# Spielerblöcke auslesen
# ==========================================

player_data = []

# date und time stehen am Anfang
start_column = 2

while start_column < len(df.columns):

    block = df.iloc[
        :,
        start_column:start_column + len(PLAYER_COLUMNS)
    ].copy()

    if len(block.columns) < len(PLAYER_COLUMNS):
        break

    block.columns = PLAYER_COLUMNS
    player_data.append(block)

    start_column += len(PLAYER_COLUMNS)


# ==========================================
# Alle Spieler zusammenführen
# ==========================================

all_players = pd.concat(
    player_data,
    ignore_index=True
)


# ==========================================
# Werte vorbereiten
# ==========================================

for column in SCORE_COLUMNS:

    all_players[column] = pd.to_numeric(
        all_players[column],
        errors="coerce"
    )

    # -1 wird als 0 gewertet
    all_players.loc[
        all_players[column] == -1,
        column
    ] = 0


# ==========================================
# Statistiken berechnen
# ==========================================

minimums = (
    all_players
    .groupby("Playername")[SCORE_COLUMNS]
    .min()
)

averages = (
    all_players
    .groupby("Playername")[SCORE_COLUMNS]
    .mean()
)

maximums = (
    all_players
    .groupby("Playername")[SCORE_COLUMNS]
    .max()
)


# ==========================================
# Ergebnisse zusammenführen
# ==========================================

results = []

for player in averages.index:

    for column in SCORE_COLUMNS:

        results.append({
            "Playername": player,
            "Kategorie": column,
            "Minimum": minimums.loc[player, column],
            "Durchschnitt": round(
                averages.loc[player, column],
                2
            ),
            "Maximum": maximums.loc[player, column],
        })


result_df = pd.DataFrame(results)


# ==========================================
# Ausgabe im Terminal
# ==========================================

print("\nStatistiken:")
print(result_df.to_string(index=False))


# ==========================================
# CSV speichern
# ==========================================

result_df.to_csv(
    OUTPUT_FILE,
    index=False,
    encoding="utf-8-sig"
)

print(f"\nErgebnis wurde gespeichert als: {OUTPUT_FILE}")
