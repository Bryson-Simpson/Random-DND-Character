from pdfrw import PdfReader, PdfWriter, PdfString
import json, re
from pathlib import Path
from datetime import datetime

# --- Paths ---
BASE = Path(__file__).resolve().parents[1]   # project root (because script is in src/)
TEMPLATE = BASE / "input" / "5E_CharacterSheet_Fillable.pdf"
DATAFILE = BASE / "output" / "character.json"
OUTDIR = BASE / "output"
OUTDIR.mkdir(exist_ok=True)

# --- Load JSON ---
with open(DATAFILE, "r") as f:
    char_data = json.load(f)

# --- Output filename ---
char_name = char_data.get("CharacterName", "Character")
safe_name = re.sub(r'[^A-Za-z0-9_-]', "_", char_name)
OUTPUT = OUTDIR / f"{safe_name}_Sheet.pdf"
if OUTPUT.exists():
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    OUTPUT = OUTDIR / f"{safe_name}_Sheet_{timestamp}.pdf"

# --- Helpers ---
def norm(s: str) -> str:
    return s.strip()

def strip_plus(v):
    """Ensure no value starts with a + sign."""
    s = str(v)
    return s[1:] if s.startswith("+") else s

# --- Read template ---
pdf = PdfReader(str(TEMPLATE))

# Ensure PDF viewers regenerate appearances
if hasattr(pdf, "Root") and hasattr(pdf.Root, "AcroForm"):
    pdf.Root.AcroForm.update(dict(NeedAppearances=True))

# --- Fill PDF fields ---
skip_fields = {
    "Hit Point Maximum", "Current Hit Points", "Temporary Hit Points",
    "HPMax", "HPCurrent", "Speed"
}

for page in pdf.pages:
    if "/Annots" in page:
        for annot in page.Annots or []:
            if not getattr(annot, "T", None):
                continue

            raw = annot.T.to_unicode() if hasattr(annot.T, "to_unicode") else str(annot.T)
            key = norm(raw.strip("()"))

            # Skip HP & Speed fields
            if key in skip_fields:
                continue

            # Look up value in JSON
            if key in char_data:
                value = char_data[key]
            elif norm(key) in char_data:
                value = char_data[norm(key)]
            else:
                continue

            # Always write plain values, no + sign
            value = strip_plus(value)

            annot.V = PdfString.encode(value)
            annot.AP = None

# --- Write new PDF ---
PdfWriter().write(str(OUTPUT), pdf)
print(f"✅ Saved filled sheet as {OUTPUT}")
