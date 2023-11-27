from sample_data.json_loader import load_json_file
from domain.domain import Fluid, Drink

print("Loading sample data...")
fluids = load_json_file("sample_data/sample_fluids.json", Fluid)
drinks = load_json_file("sample_data/sample_drinks.json", Drink)
