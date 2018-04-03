############################################################################
# application.py
#
# Minor Programming
# Programming II
# Problem Set 6: Sentimental
# Najib el Moussaoui
#
# Runs application on server with a chart, showing a user's Twitter
# messages' positivity/negativity/neutrality percentages.
###########################################################################


from flask import Flask, redirect, render_template, request, url_for

import helpers
from analyzer import Analyzer
import os
import sys


app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/search")
def search():
    """Searches screen name and returns chart."""

    # validate screen_name
    screen_name = request.args.get("screen_name", "").strip('@')
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name)
    if tweets == None:
        return redirect(url_for("index"))

    # initialize scores (%) for chart
    positive, negative, neutral = 0.0, 0.0, 100.0

    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)

    # get 100 tweets from user
    tweets = helpers.get_user_timeline(screen_name, 100)

    # calculate total score for chart
    for tweet in tweets:
        score = analyzer.analyze(tweet)
        if score > 0.0:
            positive += 1
            neutral -= 1
        elif score < 0.0:
            negative += 1
            neutral -= 1

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
