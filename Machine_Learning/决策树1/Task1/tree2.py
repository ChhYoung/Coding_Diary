from sklearn import tree
from sklearn.preprocessing import OneHotEncoder,LabelEncoder
from sklearn.externals.six import StringIO
import pandas as pd
import pydotplus

if __name__ == '__main__':

    """load the datatset"""

    with open('lenses.txt','r') as fr:
        lenses = [ line.strip().split('\t') for line in fr.readlines()]
    #print(lenses)
    # get all target in list-->  lense_target
    lenses_target = []
    for row in lenses:
        lenses_target.append(row[-1])
    #print(lenses_target)
    
    lenses_Label = ['age', 'prescript', 'astigmatic', 'tearRate']
    lenses_list = []
    lenses_dict = {}

    # get the result for each label then store them in a dict --> lenses_dict
    for each_label in lenses_Label:
        for row in lenses:
            lenses_list.append( row[lenses_Label.index(each_label)] )
        lenses_dict[each_label] = lenses_list
        lenses_list = []
    #print(lenses_dict)

    """ use one-hot encode to deal with each label's data  """

    # convert lenses_dict to pandas dataframe
    lenses_pd = pd.DataFrame(lenses_dict)
    #print(lenses_pd)

    le = LabelEncoder()
    for column in lenses_pd.columns:
        lenses_pd[column] = le.fit_transform(lenses_pd[column])
    #print(lenses_pd.keys())
    #print(lenses_target)
    """ create decision then use it  """
    clf = tree.DecisionTreeClassifier(max_depth=4)
    clf = clf.fit(lenses_pd.values.tolist(),lenses_target)


    """ plot"""
    dot_data = StringIO()
    tree.export_graphviz(clf, out_file = dot_data,                    
                        feature_names = lenses_pd.keys(),
                        class_names = clf.classes_,
                        filled=True, rounded=True,
                        special_characters=True)
    graph = pydotplus.graph_from_dot_data(dot_data.getvalue())
    graph.write_pdf("tree2.pdf") 

    print("Done!")





















