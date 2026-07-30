import tkinter as tk
from tkinter import ttk

# -----------------------------
# Données comptables
# -----------------------------

cash = 0
computer = 0
loan = 0
owner_capital = 0
revenue = 0

# -----------------------------
# Mise à jour de l'interface
# -----------------------------

def refresh():

    assets = cash + computer
    equity = owner_capital + revenue

    cash_var.set(f"${cash:,.2f}")
    computer_var.set(f"${computer:,.2f}")

    assets_var.set(f"${assets:,.2f}")

    loan_var.set(f"${loan:,.2f}")

    equity_var.set(f"${equity:,.2f}")

    equation_var.set(
        f"Actifs ({assets:,.2f}) = "
        f"Passifs ({loan:,.2f}) + "
        f"Capitaux propres ({equity:,.2f})"
    )

# -----------------------------
# Opérations comptables
# -----------------------------

def invest():
    global cash, owner_capital

    cash += 20000
    owner_capital += 20000
    refresh()


def buy_computer():
    global cash, computer

    if cash >= 3000:
        cash -= 3000
        computer += 3000

    refresh()


def take_loan():
    global cash, loan

    cash += 10000
    loan += 10000
    refresh()


def sell_services():
    global cash, revenue

    cash += 5000
    revenue += 5000
    refresh()

# -----------------------------
# Fenêtre
# -----------------------------

root = tk.Tk()
root.title("Simulation Comptable")
root.geometry("700x500")

title = tk.Label(
    root,
    text="Simulation de Comptabilité",
    font=("Arial", 18, "bold")
)

title.pack(pady=10)

# -----------------------------
# Boutons
# -----------------------------

buttons = tk.Frame(root)
buttons.pack()

ttk.Button(
    buttons,
    text="1. Investir 20 000 $",
    command=invest
).grid(row=0, column=0, padx=5, pady=5)

ttk.Button(
    buttons,
    text="2. Acheter ordinateur",
    command=buy_computer
).grid(row=0, column=1, padx=5)

ttk.Button(
    buttons,
    text="3. Emprunt bancaire",
    command=take_loan
).grid(row=0, column=2, padx=5)

ttk.Button(
    buttons,
    text="4. Vente de services",
    command=sell_services
).grid(row=0, column=3, padx=5)

# -----------------------------
# Variables
# -----------------------------

cash_var = tk.StringVar()
computer_var = tk.StringVar()
assets_var = tk.StringVar()

loan_var = tk.StringVar()

equity_var = tk.StringVar()

equation_var = tk.StringVar()

# -----------------------------
# Affichage
# -----------------------------

frame = ttk.LabelFrame(root, text="Bilan Comptable")
frame.pack(fill="both", expand=True, padx=20, pady=20)

ttk.Label(frame, text="Trésorerie :").grid(row=0, column=0, sticky="w", padx=10, pady=5)
ttk.Label(frame, textvariable=cash_var).grid(row=0, column=1)

ttk.Label(frame, text="Ordinateur :").grid(row=1, column=0, sticky="w", padx=10)
ttk.Label(frame, textvariable=computer_var).grid(row=1, column=1)

ttk.Label(frame, text="Total Actifs :").grid(row=2, column=0, sticky="w", padx=10)
ttk.Label(frame, textvariable=assets_var).grid(row=2, column=1)

ttk.Separator(frame, orient="horizontal").grid(
    row=3,
    column=0,
    columnspan=2,
    sticky="ew",
    pady=10
)

ttk.Label(frame, text="Prêt bancaire :").grid(row=4, column=0, sticky="w", padx=10)
ttk.Label(frame, textvariable=loan_var).grid(row=4, column=1)

ttk.Label(frame, text="Capitaux propres :").grid(row=5, column=0, sticky="w", padx=10)
ttk.Label(frame, textvariable=equity_var).grid(row=5, column=1)

ttk.Separator(frame, orient="horizontal").grid(
    row=6,
    column=0,
    columnspan=2,
    sticky="ew",
    pady=10
)

equation = tk.Label(
    frame,
    textvariable=equation_var,
    font=("Arial", 12, "bold"),
    fg="blue"
)

equation.grid(row=7, column=0, columnspan=2, pady=10)

refresh()

root.mainloop()
