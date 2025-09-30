# 🎲 D&D Random Character Generator

A fun project that generates random **Dungeons & Dragons 5e** characters
using both **C++** (for core logic) and **Python** (for automated PDF
sheet filling).

This project combines **random ability/class/race generation** with the
ability to **auto-fill a character sheet PDF**, so you can quickly roll
a playable character with one command.

------------------------------------------------------------------------

## ✨ Features

-   🎲 Random stat rolling (4d6 drop lowest).
-   🧙 Random selection of class, race, feat, and background.
-   📜 Outputs results to JSON for reusability.
-   📝 Automatically fills in a **5e character sheet PDF**.
-   🖥️ Cross-language project:
    -   **C++** → core random character generator.\
    -   **Python** → PDF sheet filling and utilities.

------------------------------------------------------------------------

## 📂 Project Structure

    DND Random Charater Generator/
    ├── src/
    │   ├── randomDNDclass.cpp   # C++ random generator
    │   └── fill_sheet.py        # Python PDF filler
    ├── include/                 # (Optional) C++ headers
    ├── input/                   # Input data (if used)
    ├── output/                  # Generated character sheets
    ├── README.md                # Project documentation
    └── ...

------------------------------------------------------------------------

## ⚙️ Setup

### 🔹 Requirements

-   **C++17 or newer** (e.g., g++, clang++)
-   **Python 3.9+**
-   Python libraries:
    -   `reportlab`
    -   `PyPDF2`
    -   `json`

Install Python dependencies:

``` bash
pip install -r requirements.txt
```

### 🔹 Build C++ Program

``` bash
g++ src/randomDNDclass.cpp -o randomDNDclass
```

### 🔹 Run Character Generator

``` bash
./randomDNDclass
```

This will generate a `character.json` file with all random stats.

### 🔹 Fill Character Sheet

``` bash
python3 src/fill_sheet.py
```

This takes `character.json` and fills in
`5E_CharacterSheet_Fillable.pdf`.

------------------------------------------------------------------------

## 🕹️ Usage Example

``` bash
./randomDNDclass
python3 src/fill_sheet.py
```

-   Output PDF will be saved to the `output/` folder.
-   Each run creates a **brand-new character**.

------------------------------------------------------------------------

## 🚀 Future Improvements

-   Add multiclassing support.
-   Expand race/feat/background lists.
-   Interactive CLI for user-driven character creation.
-   Export to other formats (Markdown, plain text).

------------------------------------------------------------------------

## 🤝 Contributing

Pull requests are welcome! If you'd like to add features (new races,
feats, UI improvements), fork the repo and submit a PR.

------------------------------------------------------------------------

## 📜 License

MIT License.\
Use freely for campaigns, one-shots, or just for fun!
