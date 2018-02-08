from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Query user's purchased stock
    stocks = db.execute("SELECT * \
                         FROM shares \
                         WHERE id = :user_id",
                        user_id=session["user_id"][0]["id"])

    total_value = 0.0

    # Check the current price of each stock user bougth
    for stock in stocks:
        symbol = lookup(stock["symbol"])
        # Add current_price
        if symbol["name"]:
            stock["name"] = symbol["name"]
        stock["current_price"] = symbol["price"]
        stock["value"] = symbol["price"] * stock["shares"]
        total_value += stock["value"]

    # Query user's cash
    cash = db.execute("SELECT * \
                       FROM users \
                       WHERE id = :user_id",
                      user_id=session["user_id"][0]["id"])[0]["cash"]
    total_value += cash

    return render_template("index.html", stocks=stocks, cash=cash, total_value=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get stock name and shares from form
        stock = lookup(request.form.get("symbol"))
        shares = int(request.form.get("shares"))
        # Get symbol, price, total_value
        symbol = stock["symbol"]
        price = stock["price"]
        user_id = session["user_id"][0]["id"]

        # Ensure stock symbol was submitted and valid
        if not stock:
            return apology("must provide valid symbol", 403)
        # Ensure shares was submitted
        elif shares < 1:
            return apology("shares must be positive integer", 403)

        # Query database for current user's cash
        cash = db.execute("SELECT cash \
                           FROM users \
                           WHERE id = :user_id",
                          user_id=user_id)

        # If user can afford the purchase
        if cash[0]["cash"] >= price * shares:
            # update user's cash
            db.execute("UPDATE users \
                        SET cash = cash - :value \
                        WHERE id = :user_id",
                       value=price * shares,
                       user_id=user_id)
        else:
            return apology("Uncomplete purchase, you don't have enough money!")

        # Update the purchase history
        db.execute("INSERT INTO purchase (id, symbol, price, shares) \
                    VALUES (:user_id, :symbol, :price, :shares)",
                   user_id=user_id,
                   symbol=symbol,
                   price=price,
                   shares=shares)

        # Update user's shares
        db.execute("INSERT OR REPLACE INTO shares (id, symbol, shares) \
                    VALUES (:user_id, \
                            :symbol, COALESCE((SELECT shares FROM shares WHERE symbol = :symbol) + :shares, \
                            :shares))",
                   user_id=user_id,
                   symbol=symbol,
                   shares=shares)

        # Return to /
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get user's history
    stocks = db.execute("SELECT * \
                         FROM purchase \
                         WHERE id = :user_id",
                        user_id=session["user_id"][0]["id"])

    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * \
                           FROM users \
                           WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get stock name
        stock_name = request.form.get("symbol")
        if not stock_name:
            return apology("Missing stock symbol!")

        # returns a dict of {name, price, symbol}
        stock_quote = lookup(stock_name)

        # ensure the stock is valid
        if stock_quote:
            return render_template("quote.html", quote=stock_quote)
        # else return another apology
        else:
            return apology("Invalid stock name")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get username and password
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # No entry left blank
        if not username:
            return apology("Missing username!")
        elif not password:
            return apology("Missing password!")
        # Password should match confirmation
        elif not password == confirmation:
            return apology("Password doesn't match confirmation!")

        # If all valid
        hashcode = generate_password_hash(password)

        # Add to database
        result = db.execute("INSERT INTO users (username, hash) \
                             VALUES (:username, :hashcode)",
                            username=username,
                            hashcode=hashcode)
        # If username are not UNIQUE then db.execute will fail
        if not result:
            return apology("username already been used")

        # Sotre their id in session
        session["user_id"] = result

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"][0]["id"]
    stocks = db.execute("SELECT * \
                         FROM shares \
                         WHERE id = :user_id",
                        user_id=user_id)

    # User reached route via POST
    if request.method == "POST":

        # Get stock name to sell
        stock = request.form.get("symbol")
        if not stock:
            return apology("Invalid stock symbol")

        # How many shares to sell
        shares = int(request.form.get("shares"))
        if shares < 1:
            return apology("Shares must be positive integer")

        stock = lookup(stock)
        price = stock["price"]

        # Update purchase history
        db.execute("INSERT INTO purchase (id, symbol, price, shares) \
                    VALUES (:user_id, :symbol, :price, :shares)",
                   user_id=user_id,
                   symbol=stock["symbol"],
                   price=price,
                   shares=-shares)

        # Update user's shares
        db.execute("UPDATE shares \
                    SET shares = shares - :shares \
                    WHERE symbol = :symbol",
                   shares=shares,
                   symbol=stock["symbol"])

        # Update cash
        db.execute("UPDATE users \
                    SET cash = cash + :value \
                    WHERE id = :user_id",
                   value=price * shares,
                   user_id=user_id)

        # Redirect to index.html
        return redirect("/")

    # User reached route via GET
    else:
        # display form of stocks you hold
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
