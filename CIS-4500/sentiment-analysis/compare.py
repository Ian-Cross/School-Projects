import sys, re
from time import time

import matplotlib.pyplot as plt
from pathlib import Path
import numpy as np

from sklearn.datasets import base
from sklearn.feature_extraction.text import TfidfVectorizer, CountVectorizer
from sklearn.feature_selection import SelectKBest, chi2, f_classif
from sklearn.model_selection import StratifiedKFold
from sklearn.naive_bayes import BernoulliNB
from sklearn.neighbors import KNeighborsClassifier, NearestCentroid
from sklearn.utils.extmath import density
from sklearn.utils import shuffle
from sklearn import metrics

# EMAIL RESULTS
# Micro avergaging for validation
# hyper parametes

data_train = None
data_validate = None
target_names = []
results = []

#Command line Arguments
use_bayes = False
use_centroid = False
use_neighbors = False
verbose = False
use_anova = False
use_chi2 = False
max_features = None
plot_results = False
data_files = None
num_splits = 5

def trim(s):
    #Trim string to fit on terminal (assuming 80-column display)
    return s if len(s) <= 200 else s[:197] + "..."


def benchmark(clf,X,y,feature_names):
    global target_names, num_splits
    clf_desc = str(clf).split('(')[0]
    if verbose:
        print('=' * 200)
        print("Training: ", clf)
    else:
        print("Training: ", clf_desc)

    t0 = time()
    skf = StratifiedKFold(n_splits=num_splits)
    bestModel = None
    for train, test in skf.split(X, y):
        X_train, X_test, y_train, y_test = X[train], X[test], y[train], y[test]
        clf.fit(X_train, y_train)
        train_time = time() - t0

        t0 = time()
        pred = clf.predict(X_test)
        test_time = time() - t0

        score = metrics.accuracy_score(y_test, pred)
        if bestModel is not None:
            if bestModel[0] < score:
                if verbose:
                    print("New best model")
                    print("-" * 200)
                bestModel = (score,clf,clf_desc, train_time, test_time, pred)
        else:
            if verbose:
                print("-" * 200)
                print("First model loaded")
                print("-" * 200)
            bestModel = (score,clf,clf_desc, train_time, test_time, pred)

        if verbose:
            print("train time: %0.3fs" % train_time)
            print("test time:  %0.3fs" % test_time)
            print("accuracy:   %0.3f" % score)
            print()

        if verbose:
            print("classification report:")
            print(metrics.classification_report(y_test, pred, target_names=target_names))
            print("-"*200)



    print("Best model accuracy %0.3f" % bestModel[0])
    print()

    return bestModel


def runBayes(X,y,X_validate,y_validate,feature_names,sel_method,num_features):
    global results
    if verbose:
        print('=' * 200)
        print("Naive Bayes (%s,%s)" % (sel_method,num_features))
    bNB = BernoulliNB(alpha=.01,binarize=None,fit_prior=False)
    bestModel = benchmark(bNB,X,y,feature_names)

    val_predict = bestModel[1].predict(X_validate)
    val_score = metrics.accuracy_score(y_validate, val_predict)
    print("Validating with best model validated with an accuracy of %0.3f" % val_score)
    print()

    results.append(tuple(j for i in (bestModel, (sel_method,num_features,val_score)) for j in (i if isinstance(i, tuple) else (i,))))


def runCentroid(X,y,X_validate,y_validate,feature_names,sel_method,num_features):
    global results
    if verbose:
        print('=' * 200)
        print("Nearest Centroid (Rocchio) (%s,%s)" % (sel_method,num_features))
    nCent = NearestCentroid()
    bestModel = benchmark(nCent,X,y,feature_names)

    val_predict = bestModel[1].predict(X_validate)
    val_score = metrics.accuracy_score(y_validate, val_predict)
    print("Validating with best model validated with an accuracy of %0.3f" % val_score)
    print()

    results.append(tuple(j for i in (bestModel, (sel_method,num_features, val_score)) for j in (i if isinstance(i, tuple) else (i,))))


def runNeighbors(X,y,X_validate,y_validate,feature_names,sel_method,num_features):
    global results
    if verbose:
        print('=' * 200)
        print("K Nearest neighbors (using 10 neighbors, %s,%s)" % (sel_method,num_features))
    kNN = KNeighborsClassifier(n_neighbors=10)
    bestModel = benchmark(kNN,X,y,feature_names)

    val_predict = bestModel[1].predict(X_validate)
    val_score = metrics.accuracy_score(y_validate, val_predict)
    print("Validating with best model validated with an accuracy of %0.3f" % val_score)
    print()

    results.append(tuple(j for i in (bestModel, (sel_method,num_features, val_score)) for j in (i if isinstance(i, tuple) else (i,))))


def plotResults():
    global results
    # make some plots
    indices = np.arange(len(results))

    results = [[x[i] for x in results] for i in range(9)]

    score,clf,clf_names,training_time,test_time,prediction,sel_method,num_features, val_score = results

    training_time = np.array(training_time) / np.max(training_time)
    test_time = np.array(test_time) / np.max(test_time)

    plt.figure(figsize=(12, 8))
    plt.title("Score",fontsize=20)
    plt.barh(indices, score, .2, label="score", color='navy')
    # plt.barh(indices + .2, val_score, .1, label="validation score", color='lightblue')
    plt.barh(indices + .3, training_time, .2, label="training time", color='c')
    plt.barh(indices + .6, test_time, .2, label="test time", color='darkorange')
    plt.yticks(())
    plt.legend(loc='best')
    plt.subplots_adjust(left=.25)
    plt.subplots_adjust(top=.95)
    plt.subplots_adjust(bottom=.05)

    for i, c, s, f in zip(indices, clf_names,sel_method,num_features):
        plt.text(-.4, i, "%s (%s,%s)" % (c,s,f))

    plt.show()


def chi2Selection(X,y,X_validate,y_validate,feature_names,num_features = 500):
    global use_bayes, use_centroid, use_neighbors, verbose

    print("Extracting %d best features by a chi-squared test" % num_features)
    t0 = time()
    best = SelectKBest(chi2, k=num_features)
    X = best.fit_transform(X, y)
    X_validate = best.transform(X_validate)
    if feature_names:
        # keep selected feature names
        feature_names = [feature_names[i] for i
                         in best.get_support(indices=True)]
    if verbose:
        print("done in %fs" % (time() - t0))
        print()

    if feature_names:
        feature_names = np.asarray(feature_names)

    if use_bayes:
        runBayes(X,y,X_validate,y_validate,feature_names,"chi2",num_features)
    if use_centroid:
        runCentroid(X,y,X_validate,y_validate,feature_names,"chi2",num_features)
    if use_neighbors:
        runNeighbors(X,y,X_validate,y_validate,feature_names,"chi2",num_features)


def anovaSelection(X,y,X_validate,y_validate,feature_names,num_features = 500):
    global use_bayes, use_centroid, use_neighbors, verbose

    print("Extracting %d best features by an anova f-test" % num_features)

    t0 = time()
    best = SelectKBest(f_classif, k=num_features)
    X = best.fit_transform(X, y)
    X_validate = best.transform(X_validate)
    if feature_names:
        # keep selected feature names
        feature_names = [feature_names[i] for i
                         in best.get_support(indices=True)]
    if verbose:
        print("done in %fs" % (time() - t0))
        print()

    if feature_names:
        feature_names = np.asarray(feature_names)

    if use_bayes:
        runBayes(X,y,X_validate,y_validate,feature_names,"anova",num_features)
    if use_centroid:
        runCentroid(X,y,X_validate,y_validate,feature_names,"anova",num_features)
    if use_neighbors:
        runNeighbors(X,y,X_validate,y_validate,feature_names,"anova",num_features)


def size_mb(docs):
    return sum(len(s.encode('utf-8')) for s in docs) / 1e6


def featureExtraction():
    global data_train, data_validate
    # split a training set and a test set
    y, y_validate = data_train.target, data_validate.target

    print("Extracting features from the training data using a sparse vectorizer")
    t0 = time()

    vectorizer = TfidfVectorizer(stop_words='english')
    X = vectorizer.fit_transform(data_train.data)
    duration = time() - t0

    if verbose:
        print("done in %fs at %0.3fMB/s" % (duration, size_mb(data_train.data) / duration))
        print("n_samples: %d, n_features: %d" % X.shape)
        print()

    print("Extracting features from the test data using the same vectorizer")

    t0 = time()
    X_validate = vectorizer.transform(data_validate.data)
    duration = time() - t0

    if verbose:
        print("done in %fs at %0.3fMB/s" % (duration, size_mb(data_validate.data) / duration))
        print("n_samples: %d, n_features: %d" % X_validate.shape)
        print()

    # mapping from integer feature names to original token string
    feature_names = vectorizer.get_feature_names()

    if max_features is not None:
        if use_chi2:
            chi2Selection(X,y,X_validate,y_validate,feature_names,num_features=max_features)
        if use_anova:
            anovaSelection(X,y,X_validate,y_validate,feature_names,num_features=max_features)
    else:
        for k in range(500,3500,500):
            if use_chi2:
                chi2Selection(X,y,X_validate,y_validate,feature_names,num_features=k)
            if use_anova:
                anovaSelection(X,y,X_validate,y_validate,feature_names,num_features=k)


def readFile(file):
    content = ""
    for line in file.open():
        content += line + "\n"
    return content


def loadArgs():
    global use_bayes, use_centroid, use_neighbors, verbose, use_anova, use_chi2, max_features, plot_results, data_files, num_splits
    while len(sys.argv) != 0:
        arg = sys.argv.pop(0)
        if arg in ["--dataset","-ds"]:
            arg = sys.argv.pop(0)
            data_files = arg
        if arg in ["--clf-bayes","-cb"]:
            use_bayes = True
        if arg in ["--clf-neighbors","-cn"]:
            use_neighbors = True
        if arg in ["--clf-centroid","-cc"]:
            use_centroid = True
        if arg in ["--feat-anova","-fa"]:
            use_anova = True
        if arg in ["--feat-chi2","-f2"]:
            use_chi2 = True
        if arg in ["--plot-results","-pr"]:
            plot_results = True
        if arg in ["--num-splits","-ns"]:
            arg = sys.argv.pop(0)
            if arg.isnumeric():
                if int(arg) <= 1:
                    arg = 2
                print("Useing %d folds during cross validation" % int(arg))
                num_splits = int(arg)
            else:
                print("Bad command line argument for number of folds %s" % arg)
                exit(1)
        if arg in ["--max-features","-mf"]:
            arg = sys.argv.pop(0)
            if arg.isnumeric():
                print("Useing %d top features" % int(arg))
                max_features = int(arg)
            else:
                print("Bad command line argument for max features %s" % arg)
                exit(1)
        if arg in ["--verbose","-v"]:
            verbose = True

    if not use_anova and not use_chi2:
        print("\nPlease pick at least one feature extraction method. (anova f-test or chi2)\n")
        exit(1)

    if not use_bayes and not use_neighbors and not use_centroid:
        print("\nPlease pick at least one classification method. (Naive Bayes, K Nearest Neighbors, or Nearest Centroid)\n")
        exit(1)


def main():
    global data_train, data_validate, target_names, plot_results, verbose, data_files
    loadArgs()
    print("Loading datasets")
    pos_reviews = []
    pos_labels = []
    neg_reviews = []
    neg_labels = []

    if data_files is None:
        data_files = "dataset"

    try:
        for file_name in Path(data_files).iterdir():
            file = Path(file_name)
            if re.search("pos",str(file_name)):
                if file.is_dir():
                    for pos_file in file.iterdir():
                        pos_reviews.append(readFile(Path(pos_file)))
                        pos_labels.append(1)
                else:
                    raise AttributeError
            elif re.search("neg",str(file_name)):
                if file.is_dir():
                    for neg_file in file.iterdir():
                        neg_reviews.append(readFile(Path(neg_file)))
                        neg_labels.append(0)
                else:
                    raise AttributeError
    except AttributeError as e:
        print("\nIncluded datafile '%s' is not a directory, or does not contain a 'pos' & a 'neg' directory\n" % data_files)
        raise e
        exit(1)
    except Exception as e:
        print("Error occured")
        raise e
        exit(1)

    validation_size = int(len(pos_reviews)*0.15)

    test_reviews, test_labels = shuffle(neg_reviews[:validation_size] + pos_reviews[:validation_size],neg_labels[:validation_size] + pos_labels[:validation_size])
    train_reviews, train_labels = shuffle(neg_reviews[validation_size:] + pos_reviews[validation_size:],neg_labels[validation_size:] + pos_labels[validation_size:])
    data_validate = base.Bunch(data=test_reviews, target=np.asarray(test_labels))
    data_train = base.Bunch(data=train_reviews, target=np.asarray(train_labels))
    target_names = ['negative','positive']

    print('data loaded')

    if verbose:
        print("%d documents - %0.3fMB (training set)" % (
            len(data_train.data), size_mb(data_train.data)))
        print("%d documents - %0.3fMB (test set)" % (
            len(data_validate.data), size_mb(data_validate.data)))
        print("%d categories" % len(target_names))
        print()

    featureExtraction()

    best_model = (None,None,None,None,None,None,None,None,0)
    for model in results:
        if model[8] > best_model[8]:
            best_model = model
    print("\nThe best model combination has been identified as: %s feature selection, %s feature size, and %s classification technique. With a score of %0.3f (in training %0.3f)" %(best_model[6],best_model[7],best_model[2],best_model[8],best_model[0]))

    if plot_results:
        plotResults()


if __name__ == '__main__':
    main()
