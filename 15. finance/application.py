##############################################################################
# application.py
#
# Najib el Moussaoui
# Programmeren II
# pset7: finance
# Minor Programming
#
# Note: Sorry Emma! Ik heb er heel hard aan gewerkt, maar het is helaas niet
#       volledig :( Het is ook af en toe een best sloom / en indien het een
#       internal server error heeft, even opnieuw opstarten!
##############################################################################
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    """Implements a front page with portfolio."""
    user_data = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
    purchase_data = db.execute("SELECT symbol, SUM(amount) as sum, SUM(payment) AS pay \
    FROM purchases WHERE user_id = :id GROUP BY symbol", id=session["user_id"])

    for i in range(len(purchase_data)):
        lookitup = lookup(purchase_data[i]['symbol'])
        purchase_data[i]['current'] = lookitup['price']
        purchase_data[i]['value'] = purchase_data[i]['current'] * purchase_data[i]['sum']

    return render_template("index.html", stock=purchase_data, user=user_data[0], usd=usd)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""

    if request.method == "POST":

        # set variables
        stock = lookup(request.form.get("symbol"))
        amount = request.form.get("amount")
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        payment = float(amount) * float(stock["price"])

        # ensure requested share is valid
        if not stock:
            return apology("Invalid stock")
        elif ('.' or ',') in amount:
            return apology("Fill in a whole number of shares")
        elif not int(amount) > 0:
            return apology("Fill in a positive number of shares")
        elif cash[0]["cash"] < payment:
            return apology("Not enough funds to make transaction")
        else:
            db.execute("UPDATE users SET cash = cash - :payment WHERE id=:id", payment=payment, id=session["user_id"])
            db.execute("INSERT INTO purchases (symbol, amount, payment, user_id) \
                    VALUES(:symbol, :amount, :payment, :user_id)", \
                    symbol=stock["name"], amount=amount, payment=payment, user_id=session["user_id"])
            return render_template("buysucces.html")


    # if method is GET
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions."""

    # take data from database
    purchase_data = db.execute("SELECT * FROM purchases WHERE user_id = :id", id=session["user_id"])
    user_data = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])

    # send info to html template
    return render_template("history.html", transaction=purchase_data, user=user_data[0], usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        # get quote from form
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("Invalid symbol")
        else:
            return render_template("quoteme.html", share=quote)

    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    # forget any user_id
    session.clear()

    # register the user
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        elif not request.form.get("verify-password"):
            return apology("must confirm password")

        elif not request.form.get("password") == request.form.get("verify-password"):
            return apology("passwords must be identical")

        result = db.execute("INSERT INTO users (username, hash) \
                             VALUES(:username, :hash)", \
                             username=request.form.get("username"), \
                             hash=pwd_context.hash(request.form.get("password")))

        # store id within the session user_id after succesful registration
        session["user_id"] = result

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""

    if request.method == "POST":

        stock = lookup(request.form.get("symbol"))
        amount = request.form.get("amount")

        user_data = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
        purchase_data = db.execute("SELECT symbol, SUM(amount) as sum, SUM(payment) AS pay FROM purchases WHERE user_id = :id GROUP BY symbol", id=session["user_id"])

        gain = float(amount) * float(stock["price"])
        succes = False

        stock_to_sell = {}

        for i in range(len(purchase_data)):
            if purchase_data[i]['symbol'] == stock['name']:
                stock_to_sell = purchase_data[i]

        # ensure requested share is valid
        if not stock:
            return apology("Invalid stock")
        elif ('.' or ',') in amount:
            return apology("Fill in a whole number of shares")
        elif not int(amount) > 0:
            return apology("Fill in a positive number of shares")

        for i in range(len(purchase_data)):
            purchase_data[i]['current'] = lookup(purchase_data[i]['symbol'])['price']
            purchase_data[i]['value'] = purchase_data[i]['current'] * purchase_data[i]['sum']

        if int(amount) > stock_to_sell['sum']:
            return apology("Not enough shares to make transaction")
        if int(amount) == stock_to_sell['sum']:
            db.execute("DELETE FROM purchases WHERE user_id = :id AND symbol = :symbol", id=session["user_id"], symbol=stock_to_sell['symbol'] )
            return render_template("sellsucces.html")
        else:
            db.execute("UPDATE users SET cash = cash + :gain WHERE id=:id", gain=gain, id=session["user_id"])
            db.execute("INSERT INTO purchases (symbol, amount, payment, user_id) \
                    VALUES(:symbol, :amount, :gain, :user_id)", \
                    symbol=stock["name"], amount = - int(request.form.get('amount')), gain=gain, user_id=session["user_id"])
            return render_template("sellsucces.html")

    else:
        return render_template("sell.html")


