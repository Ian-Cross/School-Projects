The project is broken into two parts:

The virtual environment must be activated before use of either program

analysis.py:
Is used to get basic analysis on the dataset.
Can be run using `python3 analysis` or the make file

Different options include:
-- --verbose: Add extra logging
-- --dataset: define where to look for a training dataset

compare.py:
Is used to run comparisons between 2 feature selection methods, 6 feature set sizes, and 3 classification techniques
Can be run using `python3 compare` or the make file.

This file need command line arguments to run, different options include
-- --verbose: Add extra logging
-- --dataset: define where to look for a training dataset
-- --feat-chi2: use the chi-sqaure feature selection method
-- --feat-anova: use the ANOVA f-test feature selection method
-- --max-features: define a number of features to use for classification
-- --clf-bayes: use the Bernoulli Naive Bayes classification technique
-- --clf-neighbors: use the k Nearest Neighbors classification technique
-- --clf-centroid: use the Nearest Centroid classification technique
-- --num-splits: defines the number of folds to use during cross validation
-- --plot-results: produce a graph of the results
