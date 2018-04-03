############################################################################
# analyzer.py
#
# Minor Programming
# Programming II
# Problem Set 6: Sentimental
# Najib el Moussaoui
#
# Loads positive and negative words in arrays, and analyses
# Twitter messages on their positivity/negativity/neutrality.
###########################################################################

import nltk


class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize analyzer."""

        # initialize arrays to store words in
        self.positives = []
        self.negatives = []

        # open positive & negative word files
        negative_words = open(negatives)
        positive_words = open(positives)

        # loop over files and store words in appropriate arrays
        for line in positive_words:
            if not line.startswith(';') and not line.isspace():
                self.positives.append(line.rstrip())

        for line in negative_words:
            if not line.startswith(';') and not line.isspace():
                self.negatives.append(line.rstrip())

        # close files
        positive_words.close()
        negative_words.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning score."""

        # split tweets into separate tokens
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)

        # score counter per tweet
        score = 0

        # loop over words and assign score
        for word in tokens:
            if word.lower() in self.positives:
                score += 1
            elif word.lower() in self.negatives:
                score -= 1

        return score
        return 0
