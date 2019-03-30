################# HyperParamater Tuning ################## 

def tuning(X_train, Y_train, X_val, Y_val, classifier, params):
    '''
    Tunes hyperparameters by running the classifier trained using training data
    on the range of parameters given, and returns the parameters which give the
    best f1-score on test data
    '''
    #Combine training and validation into one set
    X = vstack([X_train,X_val])
    Y_train.extend(Y_val)
    Y = np.array(Y_train)
    
    #Mark the training-validation splits
    train_i = np.ones((X_train.shape[0],), dtype = int) * -1
    valid_i = np.zeros((X_val.shape[0],), dtype = int)
    split_fold = np.concatenate((train_i, valid_i))
    ps = PredefinedSplit(split_fold)
    
    param_search = GridSearchCV(classifier, params, scoring=metrics.make_scorer(metrics.f1_score, average='macro'), cv=ps, return_train_score=True)
    param_search.fit(X,Y)
    results = param_search.cv_results_
    best_params = param_search.best_params_
    
    #Plotting
    #test_scores = results.get('split0_test_score')
    #par_ranges = params.values()
    #plt.plot(par_ranges[0],test_scores,'r-')
    #plt.show
    
    
    return best_params, results

params_NB = {'alpha':np.linspace(0.001,0.01,100)}
best_alpha, results = tuning(X_trainf, Y_trainf, X_valf, Y_valf, BernoulliNB(), params_NB)

